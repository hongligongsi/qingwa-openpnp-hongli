/* OpenPnP Hardware Bench v2.4.2 — standalone, dependency-free protocol engine. */
(function (root) {
  'use strict';
  const DEFAULTS = {
    version: 3, baud: 115200, timeout: 30000, settle: 2000, newline: 'LF',
    ack: '^ok\\b', error: '^(error|alarm|!!|echo:Unknown command|Resend:)',
    jog: 'G21\nG91\nG1 {axis}{distance} F{feed}\nG90',
    homeX: 'G28 X', homeY: 'G28 Y', homeZ: 'G28 Z', homeAll: 'G28',
    motorOff: 'M18', position: 'M114', stop: 'M410', stopRaw: false, sharedLights: true,
    lightTopOn: 'M150 S1 P{brightness} R{red} U{green} B{blue}', lightTopOff: 'M150 S1 P0', lightBottomOn: 'M150 S0 P{brightness} R{red} U{green} B{blue}', lightBottomOff: 'M150 S0 P0',
    pumpLeftOn: 'M106 P0 S255', pumpLeftOff: 'M107 P0', pumpRightOn: 'M106 P2 S255', pumpRightOff: 'M107 P2',
    valveLeftOn: 'M106 P1 S255', valveLeftOff: 'M107 P1', valveRightOn: 'M106 P3 S255', valveRightOff: 'M107 P3',
    nozzleLeftAxis: 'A', nozzleRightAxis: 'B', nozzleLeftCwPositive: true, nozzleRightCwPositive: true
  };
  function validate(c) {
    if (!c || typeof c !== 'object' || ![1,2,3].includes(c.version)) throw Error('不支持的配置格式');
    const result = {};
    for (const [key, original] of Object.entries(DEFAULTS)) {
      const value = c[key] === undefined ? original : c[key];
      if (typeof value !== typeof original) throw Error('配置类型错误：' + key);
      result[key] = value;
    }
    if (c.version === 1 && !result.stopRaw && result.stop.trim().toUpperCase() === 'M112') result.stop = 'M410';
    if(c.version<3 && ['lightTop','lightBottom'].every(k=>result[k+'On']==='M150 P45 R255 U255 B255'&&result[k+'Off']==='M150 P0'))for(const k of ['lightTopOn','lightTopOff','lightBottomOn','lightBottomOff'])result[k]=DEFAULTS[k];
    result.version = 3;
    for (const [key, min, max] of [['baud', 300, 3000000], ['timeout', 1000, 180000], ['settle', 0, 15000]]) {
      if (!Number.isInteger(result[key]) || result[key] < min || result[key] > max) throw Error('配置数值超出范围：' + key);
    }
    if (!['LF', 'CRLF', 'CR'].includes(result.newline)) throw Error('行结束符无效');
    if (![result.nozzleLeftAxis,result.nozzleRightAxis].every(a=>/^[AB]$/.test(a)) || result.nozzleLeftAxis===result.nozzleRightAxis) throw Error('左右吸嘴必须分别映射到 A / B 轴');
    for (const k of ['ack', 'error']) { if (!result[k].trim()) throw Error('响应表达式不能为空'); new RegExp(result[k], 'i'); }
    if (!['{axis}', '{distance}', '{feed}'].every(t => result.jog.includes(t))) throw Error('点动模板必须包含 {axis}、{distance}、{feed}');
    for (const [k, v] of Object.entries(result)) if (typeof v === 'string' && (v.length > 4096 || /[\x00-\x08\x0b\x0c\x0e-\x1f]/.test(v))) throw Error('配置包含非法字符或过长：' + k);
    return result;
  }
  function lines(command) {
    if (typeof command !== 'string' || !command.trim()) throw Error('请先在指令配置中填写此功能的指令');
    if (/\{[^}]*\}/.test(command)) throw Error('指令中还有未替换的占位符');
    if (/[\x00-\x08\x0b\x0c\x0e-\x1f]/.test(command)) throw Error('指令包含控制字符');
    const rows = command.split(/\r?\n/).map(s => s.trim()).filter(s => s && !s.startsWith(';'));
    if (!rows.length || rows.length > 64 || rows.some(s => s.length > 512)) throw Error('指令长度无效');
    return rows;
  }
  function jog(c, axis, distance, feed) {
    if (!['X', 'Y', 'Z'].includes(axis) || !Number.isFinite(distance) || Math.abs(distance) > 100 || distance === 0 || !Number.isFinite(feed) || feed <= 0 || feed > 10000) throw Error('点动参数无效');
    return c.jog.replaceAll('{axis}', axis).replaceAll('{distance}', String(Number(distance.toFixed(4)))).replaceAll('{feed}', String(feed));
  }
  function position(line) {
    const grbl = line.match(/(?:MPos|WPos):(-?[\d.]+),(-?[\d.]+),(-?[\d.]+)/i);
    if (grbl) { const xyz = grbl.slice(1).map(Number); return xyz.every(Number.isFinite) ? { X: xyz[0], Y: xyz[1], Z: xyz[2], source: /MPos:/i.test(line) ? '机器坐标回报' : '工作坐标回报' } : null; }
    // Ignore Marlin step-count suffix; never invent coordinates after homing.
    const main = line.split(/Count/i)[0], data = {};
    for (const a of ['X','Y','Z','A','B']) { const m = main.match(new RegExp('(?:^|\\s)' + a + ':\\s*(-?\\d+(?:\\.\\d+)?)', 'i')); if (m) data[a] = Number(m[1]); }
    return Object.keys(data).length ? { ...data, source: '控制器坐标回报' } : null;
  }
  function raw(text) {
    return text.replace(/\\x([0-9a-f]{2})/gi, (_, h) => String.fromCharCode(parseInt(h,16))).replace(/\\r/g,'\r').replace(/\\n/g,'\n');
  }
  function rotate(c, side, amount, feed, absolute=false) {
    if (!['Left','Right'].includes(side) || !Number.isFinite(amount) || Math.abs(amount)>360 || (!absolute && amount===0) || !Number.isFinite(feed) || feed<1 || feed>10000) throw Error('吸嘴角度或速度无效');
    const axis=c['nozzle'+side+'Axis'];
    if (!/^[AB]$/.test(axis)) throw Error('吸嘴轴映射无效');
    return `G21\n${absolute?'G90':'G91'}\nG1 ${axis}${Number(amount.toFixed(3))} F${feed}\nG90\nM400\n${c.position}`;
  }
  const PREFS = {version:1,mode:'demo',feed:1000,feedZ:300,xyStep:1,zStep:0.1,
    leftAngle:45,rightAngle:45,leftTarget:0,rightTarget:0,leftFeed:600,rightFeed:600,
    topRotation:0,bottomRotation:0,topMirror:false,bottomMirror:false,topCross:true,bottomCross:true,
    topDevice:'',bottomDevice:'',topDeviceLabel:'',bottomDeviceLabel:'',lightTopBrightness:45,lightBottomBrightness:45,lightTopColor:'#ffffff',lightBottomColor:'#ffffff',pumpLeftPercent:100,pumpRightPercent:100};
  function preferences(input={}) {
    if (!input || typeof input!=='object') input={};
    const p={...PREFS};
    for(const [key,value]of Object.entries(input)) if(key in p && typeof value===typeof p[key])p[key]=value;
    p.version=1;if(!['demo','serial'].includes(p.mode))p.mode='demo';
    for(const [key,min,max]of [['feed',1,10000],['feedZ',1,10000],['leftAngle',0.1,360],['rightAngle',0.1,360],['leftTarget',-360,360],['rightTarget',-360,360],['leftFeed',1,10000],['rightFeed',1,10000],['topRotation',-360,360],['bottomRotation',-360,360]])if(!Number.isFinite(p[key]) || p[key]<min || p[key]>max)p[key]=PREFS[key];
    for(const key of ['xyStep','zStep'])if(![0.1,1,5,10,100].includes(p[key]))p[key]=PREFS[key];
    for(const key of ['topDevice','bottomDevice','topDeviceLabel','bottomDeviceLabel'])if(p[key].length>512)p[key]='';
    for(const side of ['Top','Bottom']){const k='light'+side;if(!Number.isInteger(p[k+'Brightness'])||p[k+'Brightness']<0||p[k+'Brightness']>255)p[k+'Brightness']=45;if(!/^#[0-9a-f]{6}$/i.test(p[k+'Color']))p[k+'Color']='#ffffff';}
    for(const key of ['pumpLeftPercent','pumpRightPercent'])if(!Number.isInteger(p[key])||p[key]<0||p[key]>100)p[key]=100;
    return p;
  }
  function pump(c,key,percent,on=true){
    if(!['pumpLeft','pumpRight'].includes(key)||!Number.isInteger(percent)||percent<0||percent>100)throw Error('气泵占空比无效');
    const pwm=Math.round(percent*255/100);
    let command=c[key+(on&&pwm>0?'On':'Off')];
    if(on&&pwm>0){
      if(command.includes('{pwm}')||command.includes('{percent}'))command=command.replaceAll('{pwm}',String(pwm)).replaceAll('{percent}',String(percent));
      else if(/^\s*M106\b[^\r\n]*$/i.test(command)){const parts=command.split(';'),body=parts.shift().trim(),re=/(?:^|\s)S\s*\d+(?=\s|$)/i;command=(re.test(body)?body.replace(re,' S'+pwm):body+' S'+pwm)+(parts.length?' ;'+parts.join(';'):'');}
      else throw Error('自定义气泵开启指令需包含 {pwm} 或 {percent} 占位符');
    }
    lines(command);return {command:command.trim(),percent:on&&pwm>0?percent:0,pwm:on&&pwm>0?pwm:0};
  }
  function lighting(c,p,key,on){
    if(!['lightTop','lightBottom'].includes(key))throw Error('照明通道无效');
    p=preferences(p);const color=p[key+'Color'],values={brightness:p[key+'Brightness'],red:parseInt(color.slice(1,3),16),green:parseInt(color.slice(3,5),16),blue:parseInt(color.slice(5,7),16)};
    let command=c[key+(on?'On':'Off')];
    for(const [name,value]of Object.entries(values))command=command.replaceAll('{'+name+'}',String(value));
    // Existing literal M150 profiles retain selectors and extra arguments.
    if(on && /^\s*M150\b[^\r\n]*$/i.test(command))for(const [letter,value]of [['P',values.brightness],['R',values.red],['U',values.green],['B',values.blue]]){const re=new RegExp('(?:^|\\s)'+letter+'\\s*\\d+(?=\\s|$)','i');command=re.test(command)?command.replace(re,' '+letter+value):command+' '+letter+value;}
    lines(command);return command.trim();
  }
  function lightingPlan(c,p,key,on){
    if(!['lightTop','lightBottom','all'].includes(key))throw Error('照明通道无效');
    const keys=key==='all'||c.sharedLights?['lightTop','lightBottom']:[key],effective={...p};
    if(c.sharedLights){effective.lightBottomBrightness=p.lightTopBrightness;effective.lightBottomColor=p.lightTopColor;}
    const commands=keys.map(k=>lighting(c,effective,k,on));
    const states=Object.fromEntries(keys.map(k=>[k,on&&preferences(effective)[k+'Brightness']>0&&preferences(effective)[k+'Color'].toLowerCase()!=='#000000']));
    if(keys.length===1 && commands.some(cmd=>lines(cmd).some(line=>/^M150\b/i.test(line)&&!/(?:^|\s)S\s*[01](?=\s|$)/i.test(line))))states[key==='lightTop'?'lightBottom':'lightTop']=null;
    return {command:[...new Set(commands)].join('\n'),states};
  }
  function imageBounds(width,height,degrees) {
    const r=degrees*Math.PI/180,c=Math.abs(Math.cos(r)),s=Math.abs(Math.sin(r));
    return {width:Math.ceil(width*c+height*s-1e-8),height:Math.ceil(width*s+height*c-1e-8)};
  }
  function dialValue(dx,dy,max){
    if(!Number.isFinite(dx)||!Number.isFinite(dy)||!Number.isFinite(max)||max<=0||Math.hypot(dx,dy)<1)return null;
    let angle=(Math.atan2(dy,dx)*180/Math.PI-135+360)%360;
    if(angle>270)angle=angle<315?270:0;
    return Math.round(angle/270*max);
  }
  function endstop(line) {
    const m=line.match(/^\s*(?:echo:\s*)?([a-z][a-z0-9_]*)\s*:\s*(open|triggered)\s*$/i);
    return m?{name:m[1].toLowerCase(),triggered:m[2].toLowerCase()==='triggered'}:null;
  }
  async function discoverCameras(media, authorize=false) {
    let stream=null,authorizationError=null;
    try {
      if(authorize)try{stream=await media.getUserMedia({video:true,audio:false});}catch(e){authorizationError={name:e.name||'Error',message:e.message||String(e)};}
      // Enumerate while the temporary stream is live, including one-time permissions.
      const inputs=(await media.enumerateDevices()).filter(d=>d.kind==='videoinput');
      const devices=inputs.filter(d=>d.deviceId).map(d=>({deviceId:d.deviceId,label:d.label,groupId:d.groupId}));
      return {devices,hiddenCount:inputs.length-devices.length,authorizationError};
    } finally {stream?.getTracks().forEach(t=>t.stop());}
  }
  class Channel {
    constructor(write, config, log = () => {}) { this.write = write; this.config = config; this.log = log; this.pending = null; this.busy = false; this.halted = false; this.cancellations = 0; }
    receive(line) {
      this.log('rx', line);
      if (!this.pending) return;
      if (new RegExp(this.config.error, 'i').test(line)) this.pending.reject(Error('控制器报错：' + line));
      else if (this.pending.marker && (line.trim() === this.pending.marker || line.trim() === 'echo:' + this.pending.marker || line.trim() === 'echo: ' + this.pending.marker)) this.pending.seen = true;
      else if (new RegExp(this.config.ack, 'i').test(line) && (!this.pending.marker || this.pending.seen)) this.pending.resolve();
    }
    cancel(message = '操作已停止') { this.halted = true; ++this.cancellations; if (this.pending) this.pending.reject(Error(message)); }
    async synchronize(marker) {
      if (this.busy) throw Error('上一操作尚未结束');
      if (!/^BENCH_SYNC_[A-Z0-9_]+$/.test(marker)) throw Error('同步标记无效');
      this.busy = true;
      const generation = this.cancellations;
      let timer;
      const ack = new Promise((resolve,reject) => {
        timer = setTimeout(() => reject(Error('同步超时；控制器尚未恢复响应，运动保持锁定')), this.config.timeout);
        this.pending = {resolve,reject,marker,seen:false};
      });
      ack.catch(() => {});
      try {
        const row = 'M118 ' + marker;
        this.log('tx',row);
        await this.write(row + ({LF:'\n',CRLF:'\r\n',CR:'\r'}[this.config.newline]));
        await ack;
        if (generation !== this.cancellations) throw Error('恢复已取消');
        this.halted = false;
      } catch(e) { this.halted = true; throw e; }
      finally {clearTimeout(timer);this.pending=null;this.busy=false;}
    }
    async execute(command) {
      if (this.halted) throw Error('连接已锁定，请断开后重新连接');
      if (this.busy) throw Error('上一操作正在等待响应，请稍后再试');
      const rows = lines(command); this.busy = true;
      try {
        for (const row of rows) {
          if (this.halted) throw Error('操作已停止');
          let timer;
          const ack = new Promise((resolve, reject) => {
            timer = setTimeout(() => reject(Error('等待响应超时；连接已锁定，请检查设备后重新连接')), this.config.timeout);
            this.pending = { resolve, reject };
          });
          // Attach rejection handler before write; cancellation may arrive during it.
          ack.catch(() => {});
          try {
            this.log('tx', row);
            await this.write(row + ({ LF:'\n', CRLF:'\r\n', CR:'\r' }[this.config.newline]));
            await ack;
          } finally { clearTimeout(timer); this.pending = null; }
        }
      } catch (e) { this.halted = true; throw e; }
      finally { this.busy = false; }
    }
  }
  const api = { DEFAULTS, validate, lines, jog, position, raw, rotate, PREFS, preferences, pump, lighting, lightingPlan, imageBounds, dialValue, endstop, discoverCameras, Channel };
  if (typeof module !== 'undefined' && module.exports) module.exports = api;
  else root.Bench = api;
})(typeof globalThis !== 'undefined' ? globalThis : this);
