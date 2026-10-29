/* 青蛙硬件调试台 v3.0 — 协议引擎（纯前端、无依赖）
 *
 *  本文件是调试台的"协议层"核心，负责：
 *   - G-code 指令的构造与参数校验（点动、回零、照明、气路、吸嘴旋转等）
 *   - 控制器返回文本的解析（坐标回报 M114、限位检测 M119 等）
 *   - Channel 类：异步指令执行队列，带超时、取消、急停恢复等状态机
 *   - 照明/气路 PWM 占空比计算、旋转轴角度换算、摄像头视野尺寸计算等工具函数
 *
 *  设计目标：所有硬件指令经过统一校验和序列化后才会下发，避免参数越界或模板留空
 *  运行环境：浏览器（通过 window.Bench 暴露）+ Node.js（单元测试时通过 module.exports）
 */
(function (root) {
  'use strict';

  /* ========================================================================
   *  一、默认配置（DEFAULTS）
   *  包含波特率、超时、行结束符、各类 G-code 模板、照明/气路参数、吸嘴轴映射等。
   *  用户在"⚙ 指令配置"面板里能改的所有字段都来自这里。
   *  ======================================================================== */
  const DEFAULTS = {
    version: 3,              // 配置格式版本号（升级时用于向后兼容旧配置）
    baud: 115200,            // 串口波特率
    timeout: 30000,          // 单条指令等待响应的超时时间（毫秒）
    settle: 2000,            // 连接后等待控制器稳定的时间（毫秒）
    newline: 'LF',           // 行结束符：LF / CRLF / CR
    ack: '^ok\\b',           // 确认响应正则：Marlin 返回 "ok" 表示指令执行成功
    error: '^(error|alarm|!!|echo:Unknown command|Resend:)',  // 错误响应正则
    // 点动指令模板：先设绝对单位 (G21)，再设相对模式 (G91)，再走 (G1)，最后恢复绝对模式 (G90)
    jog: 'G21\nG91\nG1 {axis}{distance} F{feed}\nG90',
    // 回零指令：X/Y/Z 单轴和全部回零（Marlin 标准 G-code）
    homeX: 'G28 X', homeY: 'G28 Y', homeZ: 'G28 Z', homeAll: 'G28',
    motorOff: 'M18',         // 关闭电机（保持位置锁定但断电）
    position: 'M114',        // 查询当前坐标
    stop: 'M410',            // 软件急停指令
    stopRaw: false,          // 急停指令是否使用原始字符（支持 \xHH 转义，不追加换行）
    sharedLights: true,      // 联控模式：上下灯共用上灯参数，分别发送
    // 照明指令：M150 参数 S=0/1 选择上下灯，P=亮度，R/U/B=RGB
    lightTopOn: 'M150 S1 P{brightness} R{red} U{green} B{blue}',
    lightTopOff: 'M150 S1 P0',
    lightBottomOn: 'M150 S0 P{brightness} R{red} U{green} B{blue}',
    lightBottomOff: 'M150 S0 P0',
    // 气泵指令：M106=开（PWM），M107=关；P0=左泵、P1=左阀、P2=右泵、P3=右阀
    pumpLeftOn: 'M106 P0 S255', pumpLeftOff: 'M107 P0',
    pumpRightOn: 'M106 P2 S255', pumpRightOff: 'M107 P2',
    valveLeftOn: 'M106 P1 S255', valveLeftOff: 'M107 P1',
    valveRightOn: 'M106 P3 S255', valveRightOff: 'M107 P3',
    // 吸嘴轴映射：A / B 轴分别驱动左右吸嘴旋转
    nozzleLeftAxis: 'A', nozzleRightAxis: 'B',
    nozzleLeftCwPositive: true, nozzleRightCwPositive: true  // 顺时针对应正方向（false 则反向）
  };

  /* ========================================================================
   *  二、配置校验函数
   *  validate(c) — 对用户/导入的配置进行完整校验并填充默认值
   *  - 版本兼容：v1→v3 自动升级（旧 M112 急停换成 M410，旧照明指令换成新模板）
   *  - 类型检查、数值范围、正则表达式语法校验
   *  - 行结束符、吸嘴轴唯一性、模板占位符完整性等业务规则
   *  ======================================================================== */
  function validate(c) {
    if (!c || typeof c !== 'object' || ![1,2,3].includes(c.version)) throw Error('不支持的配置格式');
    const result = {};
    // 逐项合并：用户有值用用户的，缺省用默认值；同时校验类型一致
    for (const [key, original] of Object.entries(DEFAULTS)) {
      const value = c[key] === undefined ? original : c[key];
      if (typeof value !== typeof original) throw Error('配置类型错误：' + key);
      result[key] = value;
    }
    // v1 版本迁移：M112 会进入必须复位的停机状态，自动改成软急停 M410
    if (c.version === 1 && !result.stopRaw && result.stop.trim().toUpperCase() === 'M112') result.stop = 'M410';
    // v2→v3 迁移：旧版 M150 照明指令（没有分灯选择参数 S）自动换成新模板
    if(c.version<3 && ['lightTop','lightBottom'].every(k=>result[k+'On']==='M150 P45 R255 U255 B255'&&result[k+'Off']==='M150 P0'))for(const k of ['lightTopOn','lightTopOff','lightBottomOn','lightBottomOff'])result[k]=DEFAULTS[k];
    result.version = 3;  // 统一升级到最新版本

    // 数值范围校验
    for (const [key, min, max] of [['baud', 300, 3000000], ['timeout', 1000, 180000], ['settle', 0, 15000]]) {
      if (!Number.isInteger(result[key]) || result[key] < min || result[key] > max) throw Error('配置数值超出范围：' + key);
    }
    if (!['LF', 'CRLF', 'CR'].includes(result.newline)) throw Error('行结束符无效');
    // 左右吸嘴必须分别映射到不同的轴（A / B）
    if (![result.nozzleLeftAxis,result.nozzleRightAxis].every(a=>/^[AB]$/.test(a)) || result.nozzleLeftAxis===result.nozzleRightAxis) throw Error('左右吸嘴必须分别映射到 A / B 轴');
    // 正则表达式必须能成功编译
    for (const k of ['ack', 'error']) { if (!result[k].trim()) throw Error('响应表达式不能为空'); new RegExp(result[k], 'i'); }
    // 点动模板必须包含三个占位符
    if (!['{axis}', '{distance}', '{feed}'].every(t => result.jog.includes(t))) throw Error('点动模板必须包含 {axis}、{distance}、{feed}');
    // 字符串字段上限 4KB，禁止 ASCII 控制字符（0x00-0x1F 除了 0x09 制表符）
    for (const [k, v] of Object.entries(result)) if (typeof v === 'string' && (v.length > 4096 || /[\x00-\x08\x0b\x0c\x0e-\x1f]/.test(v))) throw Error('配置包含非法字符或过长：' + k);
    return result;
  }

  /* ========================================================================
   *  三、指令行预处理
   *  lines(command) — 将多行指令字符串拆分为独立、干净的指令行数组
   *  - 按换行符拆分、去首尾空格、丢弃注释行（; 开头）、丢弃空行
   *  - 最终 1~64 行，每行 ≤512 字符
   *  调用时机：所有 G-code 指令发送前都会先过这道检查
   *  ======================================================================== */
  function lines(command) {
    if (typeof command !== 'string' || !command.trim()) throw Error('请先在指令配置中填写此功能的指令');
    if (/\{[^}]*\}/.test(command)) throw Error('指令中还有未替换的占位符');
    if (/[\x00-\x08\x0b\x0c\x0e-\x1f]/.test(command)) throw Error('指令包含控制字符');
    const rows = command.split(/\r?\n/).map(s => s.trim()).filter(s => s && !s.startsWith(';'));
    if (!rows.length || rows.length > 64 || rows.some(s => s.length > 512)) throw Error('指令长度无效');
    return rows;
  }

  /* ========================================================================
   *  四、轴运动：点动
   *  jog(c, axis, distance, feed) — 根据配置的点动模板构造一条完整的 G-code 序列
   *  参数校验：
   *   - axis 只能是 X / Y / Z
   *   - distance 范围 (-100, 100)，不能为 0（没意义）
   *   - feed 范围 (0, 10000]
   *  返回：带换行的 G-code 多行字符串，包含切换绝对/相对模式和恢复的完整序列
   *  ======================================================================== */
  function jog(c, axis, distance, feed) {
    if (!['X', 'Y', 'Z'].includes(axis) || !Number.isFinite(distance) || Math.abs(distance) > 100 || distance === 0 || !Number.isFinite(feed) || feed <= 0 || feed > 10000) throw Error('点动参数无效');
    return c.jog.replaceAll('{axis}', axis).replaceAll('{distance}', String(Number(distance.toFixed(4)))).replaceAll('{feed}', String(feed));
  }

  /* ========================================================================
   *  五、坐标解析
   *  position(line) — 从 M114 返回的一行文本中提取 X / Y / Z / A / B 坐标
   *  支持两种格式：
   *   1. GRBL 风格：MPos:10.000,20.000,30.000（机器坐标）/ WPos:...（工作坐标）
   *   2. Marlin 风格：X:10.00 Y:20.00 Z:30.00 A:0.00 B:0.00
   *  返回：{X, Y, Z, source: '...'} 或 null（解析失败）
   *  ======================================================================== */
  function position(line) {
    // GRBL 风格优先尝试
    const grbl = line.match(/(?:MPos|WPos):(-?[\d.]+),(-?[\d.]+),(-?[\d.]+)/i);
    if (grbl) { const xyz = grbl.slice(1).map(Number); return xyz.every(Number.isFinite) ? { X: xyz[0], Y: xyz[1], Z: xyz[2], source: /MPos:/i.test(line) ? '机器坐标回报' : '工作坐标回报' } : null; }
    // Marlin 风格：忽略 Count 后缀（步数统计），只解析实际坐标字段
    const main = line.split(/Count/i)[0], data = {};
    for (const a of ['X','Y','Z','A','B']) { const m = main.match(new RegExp('(?:^|\\s)' + a + ':\\s*(-?\\d+(?:\\.\\d+)?)', 'i')); if (m) data[a] = Number(m[1]); }
    return Object.keys(data).length ? { ...data, source: '控制器坐标回报' } : null;
  }

  /* ========================================================================
   *  六、原始字符转义
   *  raw(text) — 将配置里的转义序列还原成真实字符
   *  支持：\xHH 十六进制字符、\r \n 回车换行
   *  用途：急停指令的 stopRaw 模式下发原始字节
   *  ======================================================================== */
  function raw(text) {
    return text.replace(/\\x([0-9a-f]{2})/gi, (_, h) => String.fromCharCode(parseInt(h,16))).replace(/\\r/g,'\r').replace(/\\n/g,'\n');
  }

  /* ========================================================================
   *  七、吸嘴旋转
   *  rotate(c, side, amount, feed, absolute) — 构造旋转轴 G-code 序列
   *  参数：
   *   - side: 'Left' / 'Right'（映射到配置里的 A / B 轴）
   *   - amount: 角度，-360~360°
   *   - feed: 旋转速度，1~10000
   *   - absolute: true=G90 绝对定位；false=G91 相对增量（默认）
   *  返回：G21 → G90/G91 → G1 → G90 → M400 → M114 完整序列
   *  ======================================================================== */
  function rotate(c, side, amount, feed, absolute=false) {
    if (!['Left','Right'].includes(side) || !Number.isFinite(amount) || Math.abs(amount)>360 || (!absolute && amount===0) || !Number.isFinite(feed) || feed<1 || feed>10000) throw Error('吸嘴角度或速度无效');
    const axis=c['nozzle'+side+'Axis'];
    if (!/^[AB]$/.test(axis)) throw Error('吸嘴轴映射无效');
    return `G21\n${absolute?'G90':'G91'}\nG1 ${axis}${Number(amount.toFixed(3))} F${feed}\nG90\nM400\n${c.position}`;
  }

  /* ========================================================================
   *  八、UI 偏好默认值（PREFS）
   *  与 DEFAULTS 不同，PREFS 存的是**用户界面状态**：当前速度、步长、亮度、颜色、
   *  摄像头旋转角度/镜像/十字线、PWM 百分比等。不涉及协议层。
   *  preferences(input) — 合并用户偏好并做边界校验，返回合法的完整偏好对象
   *  ======================================================================== */
  const PREFS = {version:1,mode:'demo',feed:1000,feedZ:300,xyStep:1,zStep:0.1,
    leftAngle:45,rightAngle:45,leftTarget:0,rightTarget:0,leftFeed:600,rightFeed:600,
    topRotation:0,bottomRotation:0,topMirror:false,bottomMirror:false,topCross:true,bottomCross:true,
    topDevice:'',bottomDevice:'',topDeviceLabel:'',bottomDeviceLabel:'',lightTopBrightness:45,lightBottomBrightness:45,lightTopColor:'#ffffff',lightBottomColor:'#ffffff',pumpLeftPercent:100,pumpRightPercent:100};
  function preferences(input={}) {
    if (!input || typeof input!=='object') input={};
    const p={...PREFS};
    for(const [key,value]of Object.entries(input)) if(key in p && typeof value===typeof p[key])p[key]=value;
    p.version=1;if(!['demo','serial'].includes(p.mode))p.mode='demo';
    // 数值范围校验
    for(const [key,min,max]of [['feed',1,10000],['feedZ',1,10000],['leftAngle',0.1,360],['rightAngle',0.1,360],['leftTarget',-360,360],['rightTarget',-360,360],['leftFeed',1,10000],['rightFeed',1,10000],['topRotation',-360,360],['bottomRotation',-360,360]])if(!Number.isFinite(p[key]) || p[key]<min || p[key]>max)p[key]=PREFS[key];
    // 步长只允许预设值（避免奇怪的小数）
    for(const key of ['xyStep','zStep'])if(![0.1,1,5,10,100].includes(p[key]))p[key]=PREFS[key];
    for(const key of ['topDevice','bottomDevice','topDeviceLabel','bottomDeviceLabel'])if(p[key].length>512)p[key]='';
    // 照明亮度 0~255，颜色必须是合法 #RRGGBB
    for(const side of ['Top','Bottom']){const k='light'+side;if(!Number.isInteger(p[k+'Brightness'])||p[k+'Brightness']<0||p[k+'Brightness']>255)p[k+'Brightness']=45;if(!/^#[0-9a-f]{6}$/i.test(p[k+'Color']))p[k+'Color']='#ffffff';}
    // 气泵占空比 0~100
    for(const key of ['pumpLeftPercent','pumpRightPercent'])if(!Number.isInteger(p[key])||p[key]<0||p[key]>100)p[key]=100;
    return p;
  }

  /* ========================================================================
   *  九、气泵 PWM 构造
   *  pump(c, key, percent, on) — 根据占空比百分比构造 M106/M107 指令
   *  percent 0~100 → PWM 0~255
   *  智能处理：如果用户自定义的 M106 指令里已有 S 参数就替换，没有就追加
   *  ======================================================================== */
  function pump(c,key,percent,on=true){
    if(!['pumpLeft','pumpRight'].includes(key)||!Number.isInteger(percent)||percent<0||percent>100)throw Error('气泵占空比无效');
    const pwm=Math.round(percent*255/100);
    let command=c[key+(on&&pwm>0?'On':'Off')];
    if(on&&pwm>0){
      // 优先支持用户自定义占位符 {pwm} {percent}
      if(command.includes('{pwm}')||command.includes('{percent}'))command=command.replaceAll('{pwm}',String(pwm)).replaceAll('{percent}',String(percent));
      // 如果是标准 M106 指令，自动替换/追加 S 参数
      else if(/^\s*M106\b[^\r\n]*$/i.test(command)){const parts=command.split(';'),body=parts.shift().trim(),re=/(?:^|\s)S\s*\d+(?=\s|$)/i;command=(re.test(body)?body.replace(re,' S'+pwm):body+' S'+pwm)+(parts.length?' ;'+parts.join(';'):'');}
      else throw Error('自定义气泵开启指令需包含 {pwm} 或 {percent} 占位符');
    }
    lines(command);return {command:command.trim(),percent:on&&pwm>0?percent:0,pwm:on&&pwm>0?pwm:0};
  }

  /* ========================================================================
   *  十、照明指令构造
   *  lighting(c, p, key, on) — 把亮度/颜色参数填入 M150 模板
   *  lightingPlan(c, p, key, on) — 联控/单控模式调度
   *  联控模式下：上下灯共用上灯参数，分别发送两条 M150（S=1 上灯，S=0 下灯）
   *  ======================================================================== */
  function lighting(c,p,key,on){
    if(!['lightTop','lightBottom'].includes(key))throw Error('照明通道无效');
    p=preferences(p);const color=p[key+'Color'],values={brightness:p[key+'Brightness'],red:parseInt(color.slice(1,3),16),green:parseInt(color.slice(3,5),16),blue:parseInt(color.slice(5,7),16)};
    let command=c[key+(on?'On':'Off')];
    for(const [name,value]of Object.entries(values))command=command.replaceAll('{'+name+'}',String(value));
    // 内置 M150 模板自动处理：有 P/R/U/B 参数就替换值，没有就追加
    if(on && /^\s*M150\b[^\r\n]*$/i.test(command))for(const [letter,value]of [['P',values.brightness],['R',values.red],['U',values.green],['B',values.blue]]){const re=new RegExp('(?:^|\\s)'+letter+'\\s*\\d+(?=\\s|$)','i');command=re.test(command)?command.replace(re,' '+letter+value):command+' '+letter+value;}
    lines(command);return command.trim();
  }
  function lightingPlan(c,p,key,on){
    if(!['lightTop','lightBottom','all'].includes(key))throw Error('照明通道无效');
    const keys=key==='all'||c.sharedLights?['lightTop','lightBottom']:[key],effective={...p};
    // 联控模式下，下灯参数跟随上灯
    if(c.sharedLights){effective.lightBottomBrightness=p.lightTopBrightness;effective.lightBottomColor=p.lightTopColor;}
    const commands=keys.map(k=>lighting(c,effective,k,on));
    // 判断哪些通道实际点亮（亮度 > 0 且颜色不是全黑）
    const states=Object.fromEntries(keys.map(k=>[k,on&&preferences(effective)[k+'Brightness']>0&&preferences(effective)[k+'Color'].toLowerCase()!=='#000000']));
    // 如果某条 M150 指令缺少 S 参数，说明用户自定义模板有问题，对应的另一侧设为未知
    if(keys.length===1 && commands.some(cmd=>lines(cmd).some(line=>/^M150\b/i.test(line)&&!/(?:^|\s)S\s*[01](?=\s|$)/i.test(line))))states[key==='lightTop'?'lightBottom':'lightTop']=null;
    return {command:[...new Set(commands)].join('\n'),states};
  }

  /* ========================================================================
   *  十一、摄像头相关工具
   *  imageBounds(w, h, degrees) — 计算旋转后需要的显示区域尺寸
   *  dialValue(dx, dy, max) — 根据鼠标拖动向量计算圆形步长选择器当前选中的值
   *  discoverCameras(media, authorize) — 枚举浏览器可访问的视频设备列表
   *  ======================================================================== */
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
  async function discoverCameras(media, authorize=false) {
    let stream=null,authorizationError=null;
    try {
      // 可选：先申请一次摄像头权限，这样 enumerateDevices 能拿到 label 和 deviceId
      if(authorize)try{stream=await media.getUserMedia({video:true,audio:false});}catch(e){authorizationError={name:e.name||'Error',message:e.message||String(e)};}
      // 临时 stream 存活期间枚举所有视频输入设备
      const inputs=(await media.enumerateDevices()).filter(d=>d.kind==='videoinput');
      const devices=inputs.filter(d=>d.deviceId).map(d=>({deviceId:d.deviceId,label:d.label,groupId:d.groupId}));
      return {devices,hiddenCount:inputs.length-devices.length,authorizationError};
    } finally {stream?.getTracks().forEach(t=>t.stop());}
  }

  /* ========================================================================
   *  十二、限位检测解析
   *  endstop(line) — 从 M119 返回的一行文本中提取开关名和触发状态
   *  Marlin 返回格式示例：echo:  X-max:  open / X-min: triggered
   *  ======================================================================== */
  function endstop(line) {
    const m=line.match(/^\s*(?:echo:\s*)?([a-z][a-z0-9_]*)\s*:\s*(open|triggered)\s*$/i);
    return m?{name:m[1].toLowerCase(),triggered:m[2].toLowerCase()==='triggered'}:null;
  }

  /* ========================================================================
   *  十三、Channel 类 — 串口异步通信状态机
   *  -------------------------------------------------------------
   *  核心设计：所有 G-code 发送都经过 Channel.execute()，保证：
   *   1. 串行执行（不并发发指令），Marlin 协议不支持并发
   *   2. 每条指令等待 "ok" / 错误正则匹配后才发下一条
   *   3. 超时锁定连接（避免控制器死锁时界面假死）
   *   4. cancel() 急停：halted=true 后阻止后续所有 execute()
   *   5. synchronize() 恢复：发唯一 M118 标记，等待控制器 echo 回显后解除 halted
   *
   *  外部调用顺序：
   *    write(line + newline) → 发 G-code
   *    receive(line)         → 控制器返回文本时喂进来，它会自动匹配 pending
   *  ======================================================================== */
  class Channel {
    // write: 实际向串口写数据的回调；config: 校验后的配置对象；log: 日志回调
    constructor(write, config, log = () => {}) { this.write = write; this.config = config; this.log = log; this.pending = null; this.busy = false; this.halted = false; this.cancellations = 0; }

    // 收到控制器一行文本时调用：匹配 ack / error，解除等待中的 pending
    receive(line) {
      this.log('rx', line);
      if (!this.pending) return;
      if (new RegExp(this.config.error, 'i').test(line)) this.pending.reject(Error('控制器报错：' + line));
      // M118 同步标记：同时匹配 "echo:标记" 和纯 "标记" 两种格式
      else if (this.pending.marker && (line.trim() === this.pending.marker || line.trim() === 'echo:' + this.pending.marker || line.trim() === 'echo: ' + this.pending.marker)) this.pending.seen = true;
      else if (new RegExp(this.config.ack, 'i').test(line) && (!this.pending.marker || this.pending.seen)) this.pending.resolve();
    }

    // 取消当前操作：将连接锁定为 halted 状态，后续指令会直接抛错
    cancel(message = '操作已停止') { this.halted = true; ++this.cancellations; if (this.pending) this.pending.reject(Error(message)); }

    // 急停后恢复：发唯一同步标记，等控制器 echo 回来 → halted=false
    // 原理：M118 是安全的查询指令，不影响运动；如果控制器能 echo 回来说明它还活着
    async synchronize(marker) {
      if (this.busy) throw Error('上一操作尚未结束');
      if (!/^BENCH_SYNC_[A-Z0-9_]+$/.test(marker)) throw Error('同步标记无效');
      this.busy = true;
      const generation = this.cancellations;  // 记录取消序号，防止同步被旧 cancel 干扰
      let timer;
      const ack = new Promise((resolve,reject) => {
        timer = setTimeout(() => reject(Error('同步超时；控制器尚未恢复响应，运动保持锁定')), this.config.timeout);
        this.pending = {resolve,reject,marker,seen:false};
      });
      ack.catch(() => {});  // 防止 UnhandledPromiseRejection
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

    // 执行指令（主入口）：将多行指令逐行串行发送并等待每条的 ok
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
          ack.catch(() => {});  // 防止 UnhandledPromiseRejection
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

  // 暴露公共 API：浏览器挂到 window.Bench，Node.js 挂到 module.exports（供单元测试）
  const api = { DEFAULTS, validate, lines, jog, position, raw, rotate, PREFS, preferences, pump, lighting, lightingPlan, imageBounds, dialValue, endstop, discoverCameras, Channel };
  if (typeof module !== 'undefined' && module.exports) module.exports = api;
  else root.Bench = api;
})(typeof globalThis !== 'undefined' ? globalThis : this);
