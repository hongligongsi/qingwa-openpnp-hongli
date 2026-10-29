'use strict';
const $ = id => document.getElementById(id);
function applyTheme(theme) {
  document.documentElement.dataset.theme = theme;
  const light = theme === 'light';
  $('theme-toggle').textContent = light ? '☾ 黑暗模式' : '☀ 明亮模式';
  $('theme-toggle').setAttribute('aria-pressed', String(light));
  $('theme-toggle').title = '当前：' + (light ? '明亮模式' : '黑暗模式');
}
applyTheme(document.documentElement.dataset.theme || 'dark');
$('theme-toggle').addEventListener('click', () => {
  const theme = document.documentElement.dataset.theme === 'light' ? 'dark' : 'light';
  applyTheme(theme);
  try { localStorage.setItem('lumen-bench-theme', theme); } catch { $('settings-status').textContent='主题保存失败，请导出全部设置备份'; }
});
let config;
try { config = Bench.validate(JSON.parse(localStorage.getItem('lumen-bench-config') || 'null')); }
catch { config = { ...Bench.DEFAULTS }; }
let channel = null, port = null, reader = null, writer = null, readTask = null;
let connected = false, connecting = false, closing = false, opBusy = false, session = 0, toastTimer;
let demoPos = { X:0, Y:0, Z:0 }, demoRelative = false;
let lastPosition = null;
let prefs;
try { prefs=Bench.preferences(JSON.parse(localStorage.getItem('lumen-bench-preferences')||'{}')); } catch { prefs=Bench.preferences(); }
let xyStep = prefs.xyStep, zStep = prefs.zStep, pendingImport = null;
let motionStopped = false, stopBusy = false, stopDelivered = false, recoveryBusy = false, requiresHome = false;
const states = {}, logEntries = [], cameraSlots = {};
const pumpApplied={pumpLeft:null,pumpRight:null};
let endstopRequest=null;
function renderEndstops(entries=[]) {
  const list=$('endstop-states');list.replaceChildren();
  const rows=[...entries];
  for(const a of ['x','y','z'])if(!rows.some(r=>new RegExp('^'+a+'(?:\\d+)?_').test(r.name)))rows.push({name:a.toUpperCase()+' 限位',triggered:null});
  for(const item of rows){const row=document.createElement('div');row.className='endstop-card '+(item.triggered===null?'unknown':item.triggered?'triggered':'open');const name=document.createElement('b'),status=document.createElement('span');name.textContent=item.name;status.textContent=item.triggered===null?'未回报':item.triggered?'● 已触发':'○ 未触发';row.append(name,status);list.append(row);}
}
function resetEndstops(){endstopRequest=null;renderEndstops();$('endstop-status').textContent='尚未检测 · 点击按钮读取当前状态';}
const outputs = [
  ['lightTop','顶部照明','上摄像头环形灯','☀'],['lightBottom','底部照明','下摄像头环形灯','☀'],
  ['pumpLeft','左气泵','P0 · MOS1','◉'],['pumpRight','右气泵','P2 · MOS3','◉'],
  ['valveLeft','左阀门','P1 · MOS2','◇'],['valveRight','右阀门','P3 · MOS4','◇']
];
function outputIcon(kind){
  const paths=kind==='light'?'<path d="M18 29c0-4-7-5-7-14a13 13 0 0 1 26 0c0 9-7 10-7 14v4H18z"/><path d="M19 38h10m-8 5h6M24 2V0M6 8l-3-3m39 3 3-3M5 20H1m46 0h-4"/><path class="icon-fill" d="M18 29c0-4-7-5-7-14a13 13 0 0 1 26 0c0 9-7 10-7 14z"/>':kind==='pump'?'<rect x="10" y="12" width="28" height="26" rx="6"/><path d="M17 12V6h14v6M10 22H3v10h7m28-10h7v10h-7M15 42h18"/><circle cx="24" cy="25" r="8"/><path d="M20 25h8m-4-4v8"/><circle class="icon-fill" cx="24" cy="25" r="8"/>':'<path d="M3 24h9m24 0h9M12 15v18l24-18v18zM24 24V10m-9 0h18m-5-4v8"/><path class="icon-fill" d="M12 15v18l24-18v18z"/>';
  return `<svg viewBox="0 -2 48 48" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true">${paths}</svg>`;
}
function savePreferences() {
  prefs=Bench.preferences(prefs);
  try {localStorage.setItem('lumen-bench-preferences',JSON.stringify(prefs));localStorage.setItem('lumen-bench-config',JSON.stringify(config));localStorage.setItem('lumen-bench-theme',document.documentElement.dataset.theme);$('settings-status').textContent='设置已自动保存 · 本地运行';return true;}
  catch { $('settings-status').textContent='保存失败，请导出全部设置备份';return false; }
}
function applyPreferences(next) {
  prefs=Bench.preferences(next);xyStep=prefs.xyStep;zStep=prefs.zStep;
  $('mode').value=prefs.mode;$('feed').value=prefs.feed;$('feed-z').value=prefs.feedZ;
  $('xy-step-display').textContent=xyStep;$('xy-step-foot').textContent=xyStep+' mm';$('z-step-foot').textContent=zStep+' mm';
  document.querySelectorAll('[data-step]').forEach(b=>{const selected=Number(b.dataset.step)===(b.dataset.group==='xy'?xyStep:zStep);b.classList.toggle('selected',selected);b.setAttribute('aria-pressed',String(selected));});
  document.querySelectorAll('[data-ring]').forEach(r=>r.classList.toggle('selected-ring',Number(r.dataset.ring)===xyStep));
  for(const side of ['left','right'])for(const suffix of ['Angle','Target','Feed'])$(side+'-'+suffix.toLowerCase()).value=prefs[side+suffix];
  for(const key of ['top','bottom']){
    $('rotation-'+key).value=prefs[key+'Rotation'];$('mirror-'+key).checked=prefs[key+'Mirror'];$('cross-toggle-'+key).checked=prefs[key+'Cross'];
    const select=$('device-'+key),id=prefs[key+'Device'];
    if(id && ![...select.options].some(o=>o.value===id))select.add(new Option((prefs[key+'DeviceLabel']||'已保存的摄像头')+' · 等待授权',id));
    if(id)select.value=id;applyCameraView(key);
  }
  for(const key of ['lightTop','lightBottom']){$(key+'-brightness').value=prefs[key+'Brightness'];$(key+'-color').value=prefs[key+'Color'];}
  for(const key of ['pumpLeft','pumpRight']){$(key+'-pwm').value=prefs[key+'Percent'];renderPumpSettings(key);}
  renderLightSettings();
}
function renderPumpSettings(key){
  $(key+'-percent').textContent=prefs[key+'Percent']+'%';
  syncDial($(key+'-pwm'));
  try{$(key+'-preview').textContent=Bench.pump(config,key,prefs[key+'Percent']).command;}catch(e){$(key+'-preview').textContent=e.message;}
}
function setPump(key,on){try{const plan=Bench.pump(config,key,prefs[key+'Percent'],on);run(plan.command,()=>{states[key]=plan.pwm>0;pumpApplied[key]=plan.percent;renderStates();});}catch(e){toast(e.message);}}
function syncDial(input){
  const dial=input.closest('.dial-control');if(!dial)return;
  const ratio=Number(input.value)/Number(input.max),a=(135+270*ratio)*Math.PI/180;
  dial.querySelector('.dial-value-arc').style.strokeDashoffset=100*(1-ratio);
  const dot=dial.querySelector('.dial-knob');dot.setAttribute('cx',50+40*Math.cos(a));dot.setAttribute('cy',50+40*Math.sin(a));
  dial.classList.toggle('disabled',input.disabled);dial.setAttribute('data-value',input.value);
}
function mountDial(key,inputId,valueId,title){
  const input=$(inputId),row=document.querySelector(`[data-output="${key}"]`).closest('.io-row'),button=row.querySelector('.device-toggle'),value=$(valueId),dial=document.createElement('div');dial.className='dial-control '+(key.startsWith('light')?'light-dial':'pump-dial');
  dial.innerHTML='<svg class="dial-svg" viewBox="0 0 100 100" aria-hidden="true"><path class="dial-track-arc" d="M21.716 78.284 A40 40 0 1 1 78.284 78.284" pathLength="100"/><path class="dial-value-arc" d="M21.716 78.284 A40 40 0 1 1 78.284 78.284" pathLength="100"/><circle class="dial-knob" r="4.5"/></svg>';
  row.prepend(dial);dial.append(input,button,value);input.setAttribute('aria-label',title);input.classList.add('dial-native-input');
  let pointer=null,startValue=null;
  const update=e=>{if(input.disabled)return;const rect=dial.getBoundingClientRect(),dx=e.clientX-rect.left-rect.width/2,dy=e.clientY-rect.top-rect.height/2;if(Math.hypot(dx,dy)<rect.width*.24)return;const v=Bench.dialValue(dx,dy,Number(input.max));if(v!==null){input.value=v;input.dispatchEvent(new Event('input',{bubbles:true}));}};
  dial.addEventListener('pointerdown',e=>{if(e.button!==0||input.disabled||e.target.closest('button')||e.target===input)return;e.preventDefault();pointer=e.pointerId;startValue=input.value;dial.setPointerCapture(pointer);update(e);});
  dial.addEventListener('pointermove',e=>{if(pointer===e.pointerId)update(e);});
  const finish=(e,cancel)=>{if(pointer!==e.pointerId)return;pointer=null;if(cancel){input.value=startValue;input.dispatchEvent(new Event('input',{bubbles:true}));}else input.dispatchEvent(new Event('change',{bubbles:true}));};
  dial.addEventListener('pointerup',e=>finish(e,false));dial.addEventListener('pointercancel',e=>finish(e,true));
  input.addEventListener('input',()=>syncDial(input));syncDial(input);
}
function renderLightSettings(){
  document.querySelectorAll('[data-light-mode]').forEach(b=>{const selected=(b.dataset.lightMode==='linked')===config.sharedLights;b.classList.toggle('active',selected);b.setAttribute('aria-pressed',String(selected));});
  for(const key of ['lightTop','lightBottom']){const effective={...prefs};if(config.sharedLights&&key==='lightBottom'){effective.lightBottomBrightness=prefs.lightTopBrightness;effective.lightBottomColor=prefs.lightTopColor;}
    $(key+'-brightness').value=effective[key+'Brightness'];$(key+'-color').value=effective[key+'Color'];
    $(key+'-value').textContent=effective[key+'Brightness']+' / 255';
    const disabled=opBusy||recoveryBusy||!!channel?.halted||(config.sharedLights&&key==='lightBottom');
    $(key+'-brightness').disabled=disabled;$(key+'-color').disabled=disabled;
    document.querySelectorAll(`[data-light-color="${key}"]`).forEach(b=>{const selected=b.dataset.color===effective[key+'Color'].toLowerCase();b.disabled=disabled;b.classList.toggle('selected',selected);b.setAttribute('aria-pressed',String(selected));});
    syncDial($(key+'-brightness'));
    try{$(key+'-preview').textContent=Bench.lighting(config,effective,key,true);}catch(e){$(key+'-preview').textContent=e.message;}
  }
  $('light-settings-note').textContent=config.sharedLights?'联控用上灯参数。点击图标开关；已开启时，调节完成后同步两灯。':'点击图标开关；已开启时，调节完成后更新亮度和颜色。';
}
function toast(message) { $('toast').textContent = message; $('toast').classList.add('show'); clearTimeout(toastTimer); toastTimer = setTimeout(() => $('toast').classList.remove('show'), 5500); }
function log(type, message) {
  const time = new Date().toLocaleTimeString('zh-CN', { hour12:false });
  logEntries.push(`${time} ${type.toUpperCase()} ${message}`); if (logEntries.length > 2000) logEntries.shift();
  const row = document.createElement('div'); row.className = 'log-line ' + type;
  const clock = document.createElement('time'); clock.textContent = time;
  const badge = document.createElement('span'); badge.className='type'; badge.textContent = ({tx:'TX →',rx:'RX ←',info:'·',error:'!'}[type]);
  const content = document.createElement('span'); content.textContent = message;
  row.append(clock,badge,content); $('log').append(row);
  if ($('log').children.length > 500) $('log').firstElementChild.remove();
  $('log').scrollTop = $('log').scrollHeight;
}
function download(name, content, type='text/plain') {
  const url = URL.createObjectURL(new Blob([content], {type})); const a=document.createElement('a'); a.href=url;a.download=name;a.click();setTimeout(() => URL.revokeObjectURL(url),1000);
}
function stamp() { const d=new Date(); return `${d.getFullYear()}${String(d.getMonth()+1).padStart(2,'0')}${String(d.getDate()).padStart(2,'0')}-${String(d.getHours()).padStart(2,'0')}${String(d.getMinutes()).padStart(2,'0')}${String(d.getSeconds()).padStart(2,'0')}`; }
function resetState() {
  resetEndstops();
  for (const [key] of outputs) states[key] = null;
  pumpApplied.pumpLeft=pumpApplied.pumpRight=null;
  lastPosition=null; for (const a of ['X','Y','Z']) $('pos-'+a).textContent='—';
  for(const side of ['left','right'])if($('nozzle-pos-'+side))$('nozzle-pos-'+side).textContent='—';
  $('position-source').textContent='坐标尚未读取'; renderStates();
}
function renderStates() {
  for (const [key,title] of outputs) {
    const node=$('state-'+key); node.textContent=states[key] === null ? '未知' : states[key] ? '已开' : '已关'; node.classList.toggle('on',states[key]===true);
    if(key.startsWith('pump')){if(states[key]===true&&pumpApplied[key]!==null)node.textContent='已开 · '+pumpApplied[key]+'%';renderPumpSettings(key);}
    document.querySelectorAll(`[data-output="${key}"]`).forEach(b=>{b.classList.toggle('active',states[key]===true);b.setAttribute('aria-pressed',states[key]===null?'mixed':String(states[key]));b.setAttribute('aria-label',`${title}：${states[key]===null?'状态未知':states[key]?'已开启':'已关闭'}，点击${states[key]===true?'关闭':'开启'}`);b.title=b.getAttribute('aria-label');});
  }
  $('light-mode').textContent=config.sharedLights ? '上下联动' : '独立指令';
  renderLightSettings();
}
function render() {
  const mode=$('mode').value, locked = !connected || connecting || closing || opBusy || recoveryBusy || channel?.halted || (mode==='serial' && !$('armed').checked);
  document.querySelectorAll('[data-hardware]').forEach(b=>b.disabled=!!locked || (requiresHome && (!!b.dataset.axis || !!b.dataset.nozzle || b.closest('#command-form') !== null)));
  document.querySelectorAll('[data-endstops]').forEach(b=>b.disabled=!connected||connecting||closing||opBusy||recoveryBusy||!!channel?.halted);
  document.querySelectorAll('[data-light-mode]').forEach(b=>b.disabled=connecting||closing||opBusy||recoveryBusy||!!channel?.halted);
  for(const key of ['pumpLeft','pumpRight']){$(key+'-pwm').disabled=opBusy||recoveryBusy||!!channel?.halted;syncDial($(key+'-pwm'));}
  renderLightSettings();
  $('stop-notice').hidden = !motionStopped && !requiresHome;
  $('stop-message').textContent = motionStopped ? (stopBusy ? '停止请求发送中；连接保持' : !stopDelivered ? '停止请求写入失败；运动已锁定，请使用物理急停。' : !canResume() ? '连接保持；自定义停机指令需人工检查，M112 需要复位主控。' : '已发送停止请求；连接保持。检查机器后解除急停，再全部回零。') : '控制已恢复；坐标需重新确认，请先全部回零。';
  $('resume-control').hidden = !motionStopped;
  $('resume-control').disabled = !connected || connecting || closing || stopBusy || !stopDelivered || opBusy || recoveryBusy || !canResume();
  $('resume-control').textContent = recoveryBusy ? '同步控制器…' : '解除急停';
  $('connect').disabled = connected || connecting || closing;
  $('disconnect').disabled = !connected || closing;
  $('mode').disabled = connected || connecting || closing;
  $('baud').disabled = connected || connecting || closing;
  $('armed').disabled=mode==='demo' || !connected || channel?.halted || opBusy;
  $('arm-note').hidden=mode!=='serial';
  const needsControl=mode==='serial' && connected && !closing && !$('armed').checked;
  $('arm-note').classList.toggle('control-reminder',needsControl);
  $('armed').closest('label').classList.toggle('control-needed',needsControl);
  $('arm-note').textContent=needsControl?'设备已连接：请勾选“允许硬件控制”后，才能控制电机、照明和气路动作。':mode==='serial' && $('armed').checked?'硬件控制已启用；断开连接不会关闭机器输出。':'连接真实设备后，请先勾选“允许硬件控制”才能控制设备动作。启用前核对指令配置及 P0–P3 接线，关闭 OpenPnP 以释放串口。';
  $('settings-open').disabled=connecting || closing;
  $('connect').textContent=connecting?'正在连接…':mode==='demo'?'连接演示设备':'选择 USB 串口';
  $('connection-status').textContent=closing?'● 正在断开':connecting?'● 正在连接':!connected?'● 未连接':motionStopped?'● 已连接 · 急停锁定':channel?.halted?'● 已连接 · 通信异常':mode==='demo'?'● 演示已连接':'● 串口已连接';
  $('connection-status').className='badge'+(connected?(mode==='demo'?' demo':' connected'):'');
  $('operation-status').textContent=motionStopped?'急停锁定 · 连接保持':channel?.halted?'通信异常 · 运动锁定':opBusy||recoveryBusy?'等待控制器确认…':requiresHome?'请先全部回零':connected?'就绪':'等待连接';
  document.body.classList.toggle('busy',opBusy);
}
for (const a of ['X','Y','Z']) {
  const row=document.createElement('div');row.className='axis-readout';
  row.innerHTML=`<span class="axis-name">${a}</span><div class="coordinate"><span id="pos-${a}">—</span><small>mm</small></div>`;
  $('axis-readouts').append(row);
}
$('axes').innerHTML=`<div class="jog-layout">
  <div class="xy-area"><div class="controller-caption"><span>XY 平面</span><small>独立轴点动</small></div>
    <div class="xy-pad">
      <button id="stop" class="emergency-icon" aria-label="软件急停" title="快速停止电机运动，保持串口连接"><svg viewBox="0 0 40 40" aria-hidden="true"><path d="M12 2H28L38 12V28L28 38H12L2 28V12Z"/><rect x="13" y="13" width="14" height="14" rx="2"/></svg><span>急停</span></button>
      <svg class="dial-art" viewBox="0 0 320 320" aria-hidden="true"><defs><radialGradient id="dial-bg"><stop offset="0" stop-color="#17283a"/><stop offset="1" stop-color="#101925"/></radialGradient></defs><circle cx="160" cy="160" r="140" fill="url(#dial-bg)" stroke="#35485c"/><circle class="dial-ring" data-ring="100" cx="160" cy="160" r="141"/><circle class="dial-ring" data-ring="10" cx="160" cy="160" r="126"/><circle class="dial-ring" data-ring="5" cx="160" cy="160" r="99"/><circle class="dial-ring selected-ring" data-ring="1" cx="160" cy="160" r="72"/><circle class="dial-ring" data-ring="0.1" cx="160" cy="160" r="45"/><path d="M49 49L271 271M271 49L49 271" stroke="#1b2938" stroke-width="12"/><path d="M49 49L271 271M271 49L49 271" stroke="#35485c" stroke-width="1"/></svg>
      <button class="dial-home home-x" data-command="homeX" data-hardware aria-label="X 回零"><span>⌂</span><b>X</b></button>
      <button class="dial-home home-y" data-command="homeY" data-hardware aria-label="Y 回零"><span>⌂</span><b>Y</b></button>
      <button class="dial-home home-all" data-command="homeAll" data-hardware aria-label="全部回零"><span>⌂</span><b>全部</b></button>
      <button class="direction dir-up" data-axis="Y" data-sign="1" data-hardware aria-label="Y 轴正向点动"><span>▲</span><b>+Y</b></button>
      <button class="direction dir-right" data-axis="X" data-sign="1" data-hardware aria-label="X 轴正向点动"><span>▶</span><b>+X</b></button>
      <button class="direction dir-down" data-axis="Y" data-sign="-1" data-hardware aria-label="Y 轴负向点动"><span>▼</span><b>−Y</b></button>
      <button class="direction dir-left" data-axis="X" data-sign="-1" data-hardware aria-label="X 轴负向点动"><span>◀</span><b>−X</b></button>
      <div class="dial-center"><span>XY</span><b id="xy-step-display">1</b><small>mm / 次</small></div>
      ${[0.1,1,5,10,100].map((s,i)=>`<button class="dial-step step-${i} ${s===1?'selected':''}" data-step="${s}" data-group="xy" aria-label="XY 步长 ${s} mm" aria-pressed="${s===1}">${s}</button>`).join('')}
    </div><div class="controller-footnote"><i></i><span>XY 步长</span><b id="xy-step-foot">1 mm</b></div>
  </div>
  <div class="z-area"><div class="controller-caption"><span>Z 轴</span><small>垂直</small></div><div class="z-track">
    <button class="z-home" data-command="homeZ" data-hardware aria-label="Z 回零">⌂ <b>Z</b></button>
    <button class="direction z-up" data-axis="Z" data-sign="1" data-hardware aria-label="Z 轴正向点动"><span>▲</span><b>+Z</b></button>
    <div class="z-steps">${[100,10,5,1,0.1].map(s=>`<button class="z-step ${s===0.1?'selected':''}" data-step="${s}" data-group="z" aria-label="Z 步长 ${s} mm" aria-pressed="${s===0.1}">${s}</button>`).join('')}</div>
    <button class="direction z-down" data-axis="Z" data-sign="-1" data-hardware aria-label="Z 轴负向点动"><span>▼</span><b>−Z</b></button>
  </div><div class="controller-footnote"><b id="z-step-foot">0.1 mm</b></div></div>
</div>`;
for(const [side,name,axis]of [['left','左吸嘴 · N1','A'],['right','右吸嘴 · N2','B']]){
  const box=document.createElement('div');box.className='nozzle-card';
  box.innerHTML=`<div class="nozzle-heading"><b>${name}</b><span><small id="nozzle-axis-${side}">${axis}</small> <strong id="nozzle-pos-${side}">—</strong> °</span></div><div class="nozzle-inputs"><label>每次角度 °<input id="${side}-angle" type="number" min="0.1" max="360" step="0.1" value="45"></label><label>速度 °/min<input id="${side}-feed" type="number" min="1" max="10000" value="600"></label></div><div class="nozzle-presets">${[15,45,90,180].map(v=>`<button data-nozzle-preset="${side}" data-angle="${v}">${v}°</button>`).join('')}</div><div class="action-row"><button data-nozzle="${side}" data-direction="cw" data-hardware>↻ 顺时针</button><button data-nozzle="${side}" data-direction="ccw" data-hardware>↺ 逆时针</button></div><div class="nozzle-target"><label>绝对角度 °<input id="${side}-target" type="number" min="-360" max="360" step="0.1" value="0"></label><button data-nozzle="${side}" data-direction="absolute" data-hardware>转到角度</button></div></div>`;
  $('nozzles').append(box);
}
for (const [key,title,subtitle] of outputs) {
  const row=document.createElement('div');row.className='io-row';
  const kind=key.startsWith('light')?'light':key.startsWith('pump')?'pump':'valve';
  row.innerHTML=`<button class="device-toggle ${kind}" data-output="${key}" data-hardware aria-pressed="mixed" aria-label="${title}：状态未知，点击开启">${outputIcon(kind)}</button><span class="io-title">${title}<small>${subtitle}</small></span><span id="state-${key}" class="io-state">未知</span>`;
  $(key.startsWith('light')?'lights':'pneumatics').append(row);
}
for(const key of ['pumpLeft','pumpRight']){
  const row=document.querySelector(`[data-output="${key}"]`).closest('.io-row');row.classList.add('pump-row');
  const controls=document.createElement('div');controls.className='pump-settings';controls.innerHTML=`<label>占空比 <span id="${key}-percent">100%</span><input id="${key}-pwm" type="range" min="0" max="100" step="1" value="100"></label><code id="${key}-preview"></code>`;row.append(controls);
  $(key+'-pwm').addEventListener('input',()=>{prefs[key+'Percent']=Number($(key+'-pwm').value);savePreferences();renderPumpSettings(key);});
  $(key+'-pwm').addEventListener('change',()=>{if(states[key]===true)setPump(key,true);});
  mountDial(key,key+'-pwm',key+'-percent',key==='pumpLeft'?'左气泵 PWM 占空比':'右气泵 PWM 占空比');
}
for(const key of ['lightTop','lightBottom']){
  const controls=document.createElement('div');controls.className='light-settings';
  controls.innerHTML=`<label>亮度 P <span id="${key}-value">45 / 255</span><input id="${key}-brightness" type="range" min="0" max="255" step="1" value="45"></label><label>颜色 RGB<input id="${key}-color" type="color" value="#ffffff"></label><div class="light-color-presets" role="group" aria-label="${key==='lightTop'?'上灯':'下灯'}快捷颜色">${[['白','#ffffff'],['红','#ff0000'],['绿','#00ff00'],['蓝','#0000ff']].map(([name,color])=>`<button data-light-color="${key}" data-color="${color}" aria-label="${name}色" aria-pressed="false" style="--preset-color:${color}"><i aria-hidden="true"></i>${name}</button>`).join('')}</div><code id="${key}-preview" class="light-preview"></code>`;
  document.querySelector(`[data-output="${key}"]`).closest('.io-row').append(controls);
  for(const suffix of ['brightness','color'])$(key+'-'+suffix).addEventListener('input',()=>{const f=$(key+'-'+suffix);if(f.value&&f.validity.valid){prefs[key+(suffix==='brightness'?'Brightness':'Color')]=suffix==='brightness'?Number(f.value):f.value;savePreferences();renderLightSettings();}});
  for(const suffix of ['brightness','color'])$(key+'-'+suffix).addEventListener('change',()=>{if(config.sharedLights?states.lightTop===true||states.lightBottom===true:states[key]===true)setLighting(key,true);});
  mountDial(key,key+'-brightness',key+'-value',key==='lightTop'?'上灯亮度':'下灯亮度');
  controls.querySelectorAll('[data-light-color]').forEach(b=>b.addEventListener('click',()=>{$(key+'-color').value=b.dataset.color;$(key+'-color').dispatchEvent(new Event('input',{bubbles:true}));$(key+'-color').dispatchEvent(new Event('change',{bubbles:true}));}));
}
document.querySelectorAll('[data-light-mode]').forEach(b=>b.addEventListener('click',()=>{config.sharedLights=b.dataset.lightMode==='linked';savePreferences();renderStates();render();}));
function setLighting(key,on){
  try{const plan=Bench.lightingPlan(config,prefs,key,on);run(plan.command,()=>{Object.assign(states,plan.states);renderStates();});}catch(e){toast(e.message);}
}
function acceptLine(line, sourceChannel) {
  if(endstopRequest?.channel===sourceChannel){const state=Bench.endstop(line);if(state)endstopRequest.entries.set(state.name,state);}
  sourceChannel.receive(line);
  const p=Bench.position(line);
  if(p && (!motionStopped || recoveryBusy)) { lastPosition={...(lastPosition||{}),...p}; for(const a of ['X','Y','Z']) if(p[a]!==undefined) $('pos-'+a).textContent=p[a].toFixed(3);for(const side of ['left','right']){const a=config['nozzle'+(side==='left'?'Left':'Right')+'Axis'];if(p[a]!==undefined)$('nozzle-pos-'+side).textContent=p[a].toFixed(2);} $('position-source').textContent=($('mode').value==='demo'?'演示坐标 · ':p.source+' · ')+new Date().toLocaleTimeString('zh-CN',{hour12:false})+(requiresHome?' · 需全部回零确认':''); }
}
async function readSerial(sourcePort, sourceChannel, token) {
  let buffer='', decoder=new TextDecoder();
  const sourceReader=sourcePort.readable.getReader(); reader=sourceReader;
  try {
    while(connected && session===token) {
      const {value,done}=await sourceReader.read(); if(done)break;
      buffer+=decoder.decode(value,{stream:true});
      const rows=buffer.split(/[\r\n]/);buffer=rows.pop();
      for(const row of rows) if(row.trim() && session===token) acceptLine(row.trim(),sourceChannel);
      if(buffer.length>16384) throw Error('串口接收行过长，请检查波特率和行结束符');
    }
    if(connected && !closing && session===token) throw Error('串口读取已结束');
  } catch(e) { if(!closing && session===token){sourceChannel.cancel('串口连接中断');$('armed').checked=false;log('error',e.message);toast('串口连接中断，请断开后重连');render();} }
  finally { sourceReader.releaseLock(); if(reader===sourceReader)reader=null; }
}
function simulate(row, demoChannel, token) {
  const code=row.trim().split(';')[0].trim();
  if(/^G91\b/i.test(code))demoRelative=true;
  if(/^G90\b/i.test(code))demoRelative=false;
  if(/^G[01]\b/i.test(code))for(const a of ['X','Y','Z','A','B']){const m=code.match(new RegExp(a+'(-?\\d+(?:\\.\\d+)?)','i'));if(m)demoPos[a]= (demoRelative?demoPos[a]:0)+Number(m[1]);}
  if(/^G28\b/i.test(code)){const axes=['X','Y','Z'].filter(a=>new RegExp('\\b'+a+'\\b','i').test(code));for(const a of axes.length?axes:['X','Y','Z'])demoPos[a]=0;}
  setTimeout(()=>{
    if(session!==token || !connected || (demoChannel.halted && !/^M118\b/i.test(code)))return;
    if(/^M118\b/i.test(code))acceptLine(code.replace(/^M118\s+/i,''),demoChannel);
    if(/^M114\b/i.test(code))acceptLine(`X:${demoPos.X.toFixed(3)} Y:${demoPos.Y.toFixed(3)} Z:${demoPos.Z.toFixed(3)} A:${demoPos.A.toFixed(3)} B:${demoPos.B.toFixed(3)}`,demoChannel);
    if(/^M115\b/i.test(code))acceptLine('FIRMWARE_NAME:Marlin (演示响应，未读取硬件)',demoChannel);
    if(/^M119\b/i.test(code)){acceptLine('Reporting endstop status',demoChannel);for(const line of ['x_min: open','y_min: TRIGGERED','z_min: open'])acceptLine(line,demoChannel);}
    acceptLine('ok',demoChannel);
  },80);
}
$('connect').addEventListener('click', async()=>{
  connecting=true;motionStopped=false;stopBusy=false;$('armed').checked=false;resetState();render(); const token=++session;
  try {
    config.baud=Number($('baud').value);
    if($('mode').value==='serial') {
      if(!navigator.serial)throw Error('当前浏览器不支持 Web Serial，请使用 Chrome / Edge 并通过 localhost 打开');
      port=await navigator.serial.requestPort();
      const openOptions={baudRate:config.baud,dataBits:8,stopBits:1,parity:'none',flowControl:'none',bufferSize:8192};
      try {await port.open(openOptions);}
      catch(openError) {
        // 上一次断开若未完全关闭，同一串口对象会残留"已打开"状态：先补关再重试一次。
        log('error','串口打开失败（'+openError.message+'），尝试自动恢复…');
        let recovered=false;
        try {await port.close();await port.open(openOptions);recovered=true;}catch{}
        if(!recovered)throw Error('无法打开串口：'+openError.message+'；请重新插拔 USB 线、关闭 OpenPnP 后重试');
        log('info','串口已恢复打开');
      }
      writer=port.writable.getWriter();
      channel=new Bench.Channel(data=>writer.write(new TextEncoder().encode(data)), {...config},log);
      connected=true;readTask=readSerial(port,channel,token);
      log('info',`USB 串口已打开 · ${config.baud} baud；等待主控启动 ${config.settle} ms`);
      await new Promise(resolve=>setTimeout(resolve,config.settle));
      if(!channel || channel.halted)throw Error('连接已被断开或串口异常，请重新连接');
      log('info','就绪；核对配置后勾选“允许硬件控制”，连接时不自动发送指令');
      toast('设备已连接，请勾选“允许硬件控制”后再控制设备动作');
    } else {
      demoPos={X:0,Y:0,Z:0,A:0,B:0};demoRelative=false;
      channel=new Bench.Channel(async data=>simulate(data,channel,token),{...config},log);connected=true;log('info','演示设备已连接；所有设备响应均为模拟');
    }
  } catch(e) { log('error',e.message);toast(e.message);if(port)await disconnect(); }
  finally {connecting=false;render();}
});
function withTimeout(promise, ms, message) { return Promise.race([promise, new Promise((_, reject) => setTimeout(() => reject(Error(message)), ms))]); }
async function closeSerialPort(target) {
  for (let attempt = 1; attempt <= 2; attempt++) {
    try { await withTimeout(target.close(), 3000, '串口关闭等待超时'); return true; }
    catch (e) { if (attempt < 2) await new Promise(resolve => setTimeout(resolve, 300)); else log('error', '串口关闭失败：' + e.message); }
  }
  return false;
}
async function disconnect() {
  if(closing)return;closing=true;connected=false;motionStopped=false;stopBusy=false;++session;channel?.cancel('设备已断开');$('armed').checked=false;resetState();render();
  const target=port;let closed=true;
  try {
    // 每一步独立兜底：任何一步失败都不再跳过 port.close()，避免串口泄漏导致重连失败。
    if(reader){try{await reader.cancel();}catch(e){log('error','取消串口读取：'+e.message);}}
    if(readTask){try{await readTask;}catch(e){log('error','读取任务结束：'+e.message);}}
    if(writer){try{writer.releaseLock();}catch(e){log('error','释放写入锁：'+e.message);}writer=null;}
    if(target)closed=await closeSerialPort(target);
  }
  finally {port=null;reader=null;writer=null;readTask=null;channel=null;closing=false;log('info',closed?'连接已断开；硬件输出状态未作更改':'连接已断开；串口未能完全关闭，若重连失败请重新插拔 USB 或刷新页面');if(!closed)toast('串口未能完全关闭；若重连失败，请重新插拔 USB 线或刷新页面');render();}
}
$('disconnect').addEventListener('click',disconnect);
$('mode').addEventListener('change',()=>{$('armed').checked=false;resetState();render();});
$('armed').addEventListener('change',()=>{log('info',$('armed').checked?'硬件控制已启用':'硬件控制已禁用');render();});
async function run(command, success, readOnly=false) {
  if(!connected || connecting || closing || !channel || channel.halted || opBusy || recoveryBusy || (!readOnly && $('mode').value==='serial' && !$('armed').checked)){toast('请先连接并启用控制，或等待当前操作结束');return false;}
  const current=channel, token=session;opBusy=true;render();
  try {await current.execute(command);if(token===session && !current.halted){success?.();log('info','指令已确认');return true;}return false;}
  catch(e){if(token===session && !motionStopped){log('error',e.message);toast(e.message);resetState();$('armed').checked=false;}}
  finally{opBusy=false;render();}
}
async function queryEndstops(){
  if(!connected||connecting||closing||opBusy||recoveryBusy||!channel||channel.halted)return;
  const request={channel,token:session,entries:new Map()};endstopRequest=request;renderEndstops();$('endstop-status').textContent='正在读取 M119…';
  const ok=await run('M119',()=>{const entries=[...request.entries.values()];renderEndstops(entries);$('endstop-status').textContent=entries.length?`${$('mode').value==='demo'?'演示数据 · 非物理反馈':'控制器回报'} · ${new Date().toLocaleTimeString('zh-CN',{hour12:false})} · ${entries.length} 个输入`:'未收到有效限位状态，不能判定为未触发；请查看日志';},true);
  if(endstopRequest===request)endstopRequest=null;
  if(!ok && request.token===session){renderEndstops();$('endstop-status').textContent='检测未完成 · 状态未知，请查看日志';}
}
function motionCommand(key){ const base=config[key];Bench.lines(base);return base+'\nM400\n'+config.position; }
document.addEventListener('click',e=>{
  const b=e.target.closest('button');if(!b || b.disabled)return;
  if(b.hasAttribute('data-endstops'))queryEndstops();
  else if(b.dataset.step) {
    const group=b.dataset.group, value=Number(b.dataset.step);
    if(group==='xy'){xyStep=value;$('xy-step-display').textContent=value;$('xy-step-foot').textContent=value+' mm';document.querySelectorAll('[data-ring]').forEach(r=>r.classList.toggle('selected-ring',Number(r.dataset.ring)===value));}else{zStep=value;$('z-step-foot').textContent=value+' mm';}
    document.querySelectorAll(`[data-group="${group}"]`).forEach(step=>{const selected=Number(step.dataset.step)===value;step.classList.toggle('selected',selected);step.setAttribute('aria-pressed',String(selected));});
    prefs[group==='xy'?'xyStep':'zStep']=value;savePreferences();
  } else if(b.dataset.nozzlePreset){const side=b.dataset.nozzlePreset;$(side+'-angle').value=b.dataset.angle;prefs[side+'Angle']=Number(b.dataset.angle);savePreferences();}
  else if(b.dataset.nozzle){
    try{if(requiresHome)throw Error('急停后请先全部回零');const side=b.dataset.nozzle,S=side==='left'?'Left':'Right',absolute=b.dataset.direction==='absolute';const angle=Number($(side+(absolute?'-target':'-angle')).value),feed=Number($(side+'-feed').value);if(!absolute && angle<=0)throw Error('每次转动角度必须大于 0');const sign=(b.dataset.direction==='cw'?1:-1)*(config['nozzle'+S+'CwPositive']?1:-1);run(Bench.rotate(config,S,absolute?angle:angle*sign,feed,absolute));}catch(err){toast(err.message);}
  } else if(b.dataset.axis) {
    try {if(requiresHome)throw Error('急停后请先全部回零');const axis=b.dataset.axis, step=axis==='Z'?zStep:xyStep, feed=Number($(axis==='Z'?'feed-z':'feed').value);const command=Bench.jog(config,axis,step*Number(b.dataset.sign),feed);run(command+'\nM400\n'+config.position);}
    catch(err){toast(err.message);}
  } else if(b.dataset.command) {
    try {const key=b.dataset.command;run(key.startsWith('home')?motionCommand(key):config[key],()=>{if(key==='homeAll'){requiresHome=false;$('position-source').textContent=$('position-source').textContent.replace(' · 需全部回零确认','');render();}});}
    catch(err){toast(err.message);}
  } else if(b.dataset.literal) run(b.dataset.literal);
  else if(b.dataset.output) {
    const key=b.dataset.output,on=states[key]!==true;
    if(key.startsWith('light'))setLighting(key,on);
    else if(key.startsWith('pump'))setPump(key,on);
    else run(config[key+(on?'On':'Off')],()=>{states[key]=on;renderStates();});
  }
});
$('command-form').addEventListener('submit',e=>{e.preventDefault();if(requiresHome){toast('急停后请先全部回零，再使用手动指令');return;}run($('manual-command').value,()=>{for(const [k]of outputs)states[k]=null;renderStates();$('manual-command').value='';});});
function canResume(){return !config.stopRaw && config.stop.trim().toUpperCase()==='M410';}
$('stop').addEventListener('click',async()=>{
  const current=channel;if(!current || closing || connecting){toast('当前没有可发送急停的连接；如需停止硬件请使用物理急停');return;}
  motionStopped=true;requiresHome=true;stopBusy=true;stopDelivered=false;current.cancel('软件急停');$('armed').checked=false;
  lastPosition=null;for(const a of ['X','Y','Z'])$('pos-'+a).textContent='—';$('position-source').textContent='停止请求已发送，坐标需重新回零确认';
  for(const side of ['left','right'])$('nozzle-pos-'+side).textContent='—';
  render();log('error','软件急停：取消剩余指令，保持串口连接');
  const token=session, stopGeneration=current.cancellations;
  try{
    if(!config.stop.trim())throw Error('未配置急停指令；请使用物理急停');
    const ending={LF:'\n',CRLF:'\r\n',CR:'\r'}[config.newline];
    const data=config.stopRaw?Bench.raw(config.stop):Bench.lines(config.stop).join(ending)+ending;
    log('tx','优先停止 → '+config.stop);await current.write(data);
    if(token!==session || stopGeneration!==current.cancellations)return;
    stopDelivered=true;
    toast(canResume()?'停止请求已发送；串口保持连接，检查机器后可解除急停':'停止请求已发送；自定义停机指令可能需要复位主控');
    log('info',$('mode').value==='demo'?'演示运动已停止；连接保持':'停止指令已写入串口；请确认机器实际停止');
  }catch(e){log('error',e.message);toast(e.message);}
  finally{if(token===session && stopGeneration===current.cancellations){stopBusy=false;render();}}
});
$('resume-control').addEventListener('click',async()=>{
  if(!connected || !motionStopped || stopBusy || !stopDelivered || opBusy || recoveryBusy || !canResume())return;
  const current=channel,token=session;recoveryBusy=true;render();
  try{
    const marker='BENCH_SYNC_'+Date.now().toString(36).toUpperCase()+'_'+Math.random().toString(36).slice(2,9).toUpperCase();
    await current.synchronize(marker);
    await current.execute('G90\n'+config.position);
    if(token!==session || current.halted)return;
    motionStopped=false;
    $('armed').checked=$('mode').value==='serial';
    toast('已解除急停，连接保持；请先全部回零');log('info','同步完成，急停已解除；旧指令不重放，需全部回零');
  }catch(e){if(token===session){current.halted=true;log('error',e.message);toast(e.message);}}
  finally{recoveryBusy=false;render();}
});
$('clear-log').addEventListener('click',()=>{$('log').replaceChildren();logEntries.length=0;});
$('export-log').addEventListener('click',()=>download('lumenpnp-log-'+stamp()+'.txt',`LumenPnP Hardware Bench v2.4.3\n模式：${$('mode').value}\n`+logEntries.join('\n')));
// Configuration editor. Saving and importing never execute hardware commands.
const configLabels={baud:'波特率',timeout:'每条指令响应超时（ms）',settle:'连接启动等待（ms）',newline:'行结束符（LF / CRLF / CR）',ack:'确认响应正则',error:'错误响应正则',jog:'点动模板 · {axis} {distance} {feed}',homeX:'X 单轴回零',homeY:'Y 单轴回零',homeZ:'Z 单轴回零',homeAll:'全部回零',motorOff:'关闭电机',position:'查询坐标',stop:'软件急停指令',stopRaw:'急停使用原始字符（支持 \\xHH，不追加换行）',sharedLights:'联控：使用上灯参数，分别发送上下灯指令',nozzleLeftAxis:'左吸嘴轴（A / B）',nozzleRightAxis:'右吸嘴轴（A / B）',nozzleLeftCwPositive:'左吸嘴顺时针对应正方向（取消则反向）',nozzleRightCwPositive:'右吸嘴顺时针对应正方向（取消则反向）'};
for(const [key,title]of outputs){configLabels[key+'On']=title+' · 开';configLabels[key+'Off']=title+' · 关';}
function configForm(c) {
  $('config-fields').replaceChildren();
  for(const [key,label]of Object.entries(configLabels)){
    const wrapper=document.createElement('label');wrapper.textContent=label;
    const field=document.createElement(typeof c[key]==='string'&&!['ack','error','newline'].includes(key)?'textarea':'input');field.dataset.config=key;
    if(typeof c[key]==='boolean'){field.type='checkbox';field.checked=c[key];wrapper.className='check wide';}
    else {field.value=c[key];if(typeof c[key]==='number')field.type='number';}
    if(key==='jog')wrapper.className='wide';wrapper.append(field);$('config-fields').append(wrapper);
  }
}
function readConfigForm(){const c={...config};document.querySelectorAll('[data-config]').forEach(f=>{const k=f.dataset.config;c[k]=typeof Bench.DEFAULTS[k]==='boolean'?f.checked:typeof Bench.DEFAULTS[k]==='number'?Number(f.value):f.value;});return Bench.validate(c);}
function installConfig(next){
  config=Bench.validate(next);for(const side of ['left','right'])$('nozzle-axis-'+side).textContent=config['nozzle'+(side==='left'?'Left':'Right')+'Axis'];try{localStorage.setItem('lumen-bench-config',JSON.stringify(config));}catch{toast('配置已应用，但浏览器无法保存；请导出 JSON 备份');}
  if(![...$('baud').options].some(o=>Number(o.value)===config.baud))$('baud').add(new Option(config.baud,config.baud));$('baud').value=config.baud;resetState();
}
$('settings-open').addEventListener('click',()=>{pendingImport=null;configForm(config);const locked=connected||connecting||closing;$('settings-form').querySelectorAll('input,textarea,button[type="submit"],#config-reset,#config-import').forEach(f=>f.disabled=locked);$('settings').showModal();if(locked)toast('设备已连接；可以查看和导出配置，修改前请断开');});
$('settings-close').addEventListener('click',()=>$('settings').close());
$('settings-form').addEventListener('submit',e=>{e.preventDefault();if(connected||connecting||closing)return;try{installConfig(readConfigForm());if(pendingImport){for(const key of ['top','bottom'])stopCamera(key);applyPreferences(pendingImport.preferences);applyTheme(pendingImport.theme);localStorage.setItem('lumen-bench-theme',pendingImport.theme);pendingImport=null;}const saved=savePreferences();$('settings').close();render();toast(saved?'全部设置已保存':'保存失败，请导出全部设置备份');}catch(e){toast(e.message);}});
$('config-reset').addEventListener('click',()=>{if(!connected){pendingImport=null;configForm({...Bench.DEFAULTS});}});
$('config-export').addEventListener('click',()=>{try{const bundle={type:'lumen-bench-settings',version:1,config:readConfigForm(),preferences:pendingImport?.preferences||Bench.preferences(prefs),theme:pendingImport?.theme||document.documentElement.dataset.theme};download('lumenpnp-settings-'+stamp()+'.json',JSON.stringify(bundle,null,2),'application/json');}catch(e){toast(e.message);}});
$('config-import').addEventListener('change',async e=>{const file=e.target.files[0];try{if(connected||connecting||closing)throw Error('请先断开设备');if(!file)return;if(file.size>65536)throw Error('配置文件过大');const data=JSON.parse(await file.text());if(data.type==='lumen-bench-settings'){if(data.version!==1 || !data.preferences || !['light','dark'].includes(data.theme))throw Error('全部设置文件格式无效');configForm(Bench.validate(data.config));pendingImport={preferences:Bench.preferences(data.preferences),theme:data.theme};}else{configForm(Bench.validate(data));pendingImport=null;}toast('设置已载入编辑区，请检查后保存');}catch(err){toast(err.message);}finally{e.target.value='';}});
// Two independent USB camera streams; browser permission is requested only on click.
for(const [key,title,code]of [['top','上摄像头 · PCB 视角','TOP / DOWNWARD'],['bottom','下摄像头 · 吸嘴视角','BOTTOM / UPWARD']]){
  cameraSlots[key]={stream:null,token:0};const box=document.createElement('div');box.className='camera';
  box.innerHTML=`<div class="camera-title">${title}<small>USB CAMERA</small></div><div id="frame-${key}" class="camera-frame"><video id="video-${key}" autoplay muted playsinline></video><div id="placeholder-${key}" class="placeholder"><span>⌾</span>等待摄像头连接</div><div id="cross-${key}" class="crosshair"></div><div class="frame-label">${code}</div></div><div class="camera-controls"><select id="device-${key}" aria-label="${title}设备"><option value="">先授权 / 刷新摄像头</option></select><button id="camera-start-${key}">开启</button><button id="camera-stop-${key}">关闭</button><button id="snapshot-${key}">截图</button><label class="camera-rotation">旋转 °<input id="rotation-${key}" type="number" min="-360" max="360" step="1" value="0" aria-label="${title}旋转角度"></label><label class="check"><input type="checkbox" id="mirror-${key}">镜像</label><label class="check"><input type="checkbox" id="cross-toggle-${key}" checked>十字线</label></div><div class="camera-status" id="camera-status-${key}">未开启 · 可同时显示两路画面</div>`;
  $('cameras').append(box);
  $('camera-start-'+key).addEventListener('click',()=>startCamera(key));
  $('camera-stop-'+key).addEventListener('click',()=>stopCamera(key));
  $('mirror-'+key).addEventListener('change',()=>{prefs[key+'Mirror']=$('mirror-'+key).checked;applyCameraView(key);savePreferences();});
  $('cross-toggle-'+key).addEventListener('change',()=>{prefs[key+'Cross']=$('cross-toggle-'+key).checked;applyCameraView(key);savePreferences();});
  $('rotation-'+key).addEventListener('input',()=>{const f=$('rotation-'+key);if(f.value.trim() && f.validity.valid){prefs[key+'Rotation']=Number(f.value);applyCameraView(key);savePreferences();}});
  $('device-'+key).addEventListener('change',()=>{const f=$('device-'+key);prefs[key+'Device']=f.value;prefs[key+'DeviceLabel']=f.selectedOptions[0]?.textContent||'';savePreferences();});
  $('video-'+key).addEventListener('loadedmetadata',()=>applyCameraView(key));
  new ResizeObserver(()=>applyCameraView(key)).observe($('frame-'+key));
  $('snapshot-'+key).addEventListener('click',()=>{
    const v=$('video-'+key);if(!v.videoWidth || !cameraSlots[key].stream){toast('请先开启摄像头');return;}
    const angle=prefs[key+'Rotation'],bounds=Bench.imageBounds(v.videoWidth,v.videoHeight,angle);
    const canvas=document.createElement('canvas');canvas.width=bounds.width;canvas.height=bounds.height;const ctx=canvas.getContext('2d');
    ctx.translate(canvas.width/2,canvas.height/2);ctx.rotate(angle*Math.PI/180);if(prefs[key+'Mirror'])ctx.scale(-1,1);ctx.drawImage(v,-v.videoWidth/2,-v.videoHeight/2);ctx.setTransform(1,0,0,1,0,0);
    if($('cross-toggle-'+key).checked){ctx.strokeStyle='#49d6b2';ctx.lineWidth=1;ctx.beginPath();ctx.moveTo(canvas.width/2,0);ctx.lineTo(canvas.width/2,canvas.height);ctx.moveTo(0,canvas.height/2);ctx.lineTo(canvas.width,canvas.height/2);ctx.stroke();}
    canvas.toBlob(blob=>{if(blob)download('lumenpnp-'+key+'-'+stamp()+'.png',blob,'image/png');},'image/png');
  });
}
function stopCamera(key){const slot=cameraSlots[key];++slot.token;slot.stream?.getTracks().forEach(t=>t.stop());slot.stream=null;$('video-'+key).srcObject=null;$('placeholder-'+key).hidden=false;$('camera-status-'+key).textContent='摄像头已关闭';$('camera-start-'+key).disabled=false;}
function applyCameraView(key){
  const v=$('video-'+key),frame=$('frame-'+key);if(!v || !frame)return;
  const angle=prefs[key+'Rotation'],w=v.videoWidth||1280,h=v.videoHeight||720,b=Bench.imageBounds(w,h,angle);
  const fit=Math.min(frame.clientWidth/b.width,frame.clientHeight/b.height);
  v.style.width=(w*fit)+'px';v.style.height=(h*fit)+'px';v.style.left='50%';v.style.top='50%';
  v.style.transform=`translate(-50%,-50%) rotate(${angle}deg) scaleX(${prefs[key+'Mirror']?-1:1})`;
  $('cross-'+key).hidden=!prefs[key+'Cross'];
}
let cameraScanGeneration=0,cameraRefreshBusy=false;
async function cameraList(authorize=false){
  const generation=++cameraScanGeneration;
  if(!navigator.mediaDevices?.enumerateDevices)throw Error('摄像头 API 不可用，请用桌面 Chrome / Edge 通过 localhost 或 HTTPS 打开');
  const result=await Bench.discoverCameras(navigator.mediaDevices,authorize);
  if(generation!==cameraScanGeneration)return result;
  const {devices,hiddenCount,authorizationError}=result;
  for(const key of ['top','bottom']){
    const select=$('device-'+key),saved=prefs[key+'Device'],label=prefs[key+'DeviceLabel'];select.replaceChildren();
    devices.forEach((d,i)=>select.add(new Option(d.label||'摄像头 '+(i+1),d.deviceId)));
    const sameName=label?devices.filter(d=>d.label===label):[];
    const match=devices.find(d=>d.deviceId===saved)||(sameName.length===1?sameName[0]:null);
    if(match){select.value=match.deviceId;prefs[key+'Device']=match.deviceId;prefs[key+'DeviceLabel']=match.label||label;}
    else if(saved){select.add(new Option((label||'已保存的摄像头')+' · 未找到 / 未授权',saved));select.value=saved;}
    else if(devices.length){select.selectedIndex=key==='bottom'&&devices.length>1?1:0;prefs[key+'Device']=select.value;prefs[key+'DeviceLabel']=devices[select.selectedIndex].label;}
    else select.add(new Option('先授权 / 刷新摄像头',''));
  }
  let permission='未知';
  try{permission=(await navigator.permissions.query({name:'camera'})).state;}catch{}
  if(generation!==cameraScanGeneration)return result;
  const detail=devices.map((d,i)=>`${i+1}. ${d.label||'未授权名称'} [${d.deviceId.slice(0,12)}…]`).join('；');
  const warning=authorizationError?`；授权 / 打开失败：${authorizationError.name}，检查站点权限或摄像头占用`:devices.length<2?'；仅少于 2 个设备，请检查浏览器和 Windows 摄像头权限':'';
  $('camera-discovery').textContent=`浏览器可选择 ${devices.length} 个摄像头 · 权限 ${permission}${hiddenCount?` · ${hiddenCount} 个设备未提供 ID`:''}${warning}`;
  log(authorizationError?'error':'info',`摄像头枚举：${devices.length} 个可选择，${hiddenCount} 个无 ID，权限 ${permission}${detail?'；'+detail:''}${authorizationError?`；${authorizationError.name}: ${authorizationError.message}`:''}`);
  savePreferences();
  return result;
}
$('camera-refresh').addEventListener('click',async()=>{
  cameraRefreshBusy=true;$('camera-refresh').disabled=true;
  try{const active=Object.values(cameraSlots).some(s=>s.stream?.active);const result=await cameraList(!active);toast(result.authorizationError?'授权 / 打开失败，已继续刷新可见设备；请查看日志':`已刷新：${result.devices.length} 个摄像头`);}
  catch(e){$('camera-discovery').textContent='摄像头列表刷新失败：'+e.message;toast('摄像头：'+e.message);log('error','摄像头列表刷新失败：'+e.message);}finally{cameraRefreshBusy=false;$('camera-refresh').disabled=false;}
});
let cameraDeviceTimer;
navigator.mediaDevices?.addEventListener('devicechange',()=>{
  clearTimeout(cameraDeviceTimer);cameraDeviceTimer=setTimeout(()=>{if(!cameraRefreshBusy)cameraList().catch(e=>log('error','设备变化刷新失败：'+e.message));},300);
});
document.addEventListener('visibilitychange',()=>{if(document.visibilityState==='visible'&&!cameraRefreshBusy)cameraList().catch(e=>log('error','摄像头刷新失败：'+e.message));});
async function startCamera(key){
  stopCamera(key);const slot=cameraSlots[key],token=slot.token;$('camera-start-'+key).disabled=true;$('camera-status-'+key).textContent='正在打开摄像头…';
  try{
    if(!navigator.mediaDevices?.getUserMedia)throw Error('请通过 localhost 或 HTTPS 打开');
    const device=$('device-'+key).value;const other=cameraSlots[key==='top'?'bottom':'top'].stream?.getVideoTracks()[0]?.getSettings().deviceId;
    if(device && other===device)throw Error('该设备已用于另一路画面，请选择另一摄像头');
    const stream=await navigator.mediaDevices.getUserMedia({video:{...(device?{deviceId:{exact:device}}:{}),width:{ideal:1280},height:{ideal:720}},audio:false});
    if(token!==slot.token){stream.getTracks().forEach(t=>t.stop());return;}
    if(other && stream.getVideoTracks()[0]?.getSettings().deviceId===other){stream.getTracks().forEach(t=>t.stop());throw Error('选中了另一路正在使用的设备，请先刷新列表并选择另一摄像头');}
    slot.stream=stream;const v=$('video-'+key);v.srcObject=stream;await v.play();
    if(token!==slot.token)return;
    $('placeholder-'+key).hidden=true;const track=stream.getVideoTracks()[0],settings=track.getSettings();$('camera-status-'+key).textContent=`${settings.width} × ${settings.height} · ${track.label}`;
    track.addEventListener('ended',()=>{if(token===slot.token){stopCamera(key);$('camera-status-'+key).textContent='摄像头已中断，请检查 USB 连接';}});
    prefs[key+'Device']=settings.deviceId||device;prefs[key+'DeviceLabel']=track.label;applyCameraView(key);await cameraList();savePreferences();
  }catch(e){if(token===slot.token){stopCamera(key);$('camera-status-'+key).textContent='打开失败：'+e.message;toast('摄像头打开失败：'+e.message);}}
  finally{if(token===slot.token)$('camera-start-'+key).disabled=false;}
}
window.addEventListener('beforeunload',()=>{channel?.cancel();for(const key of ['top','bottom'])cameraSlots[key].stream?.getTracks().forEach(t=>t.stop());});
installConfig(config);applyPreferences(prefs);render();
for(const [id,key]of [['feed','feed'],['feed-z','feedZ'],['left-angle','leftAngle'],['right-angle','rightAngle'],['left-target','leftTarget'],['right-target','rightTarget'],['left-feed','leftFeed'],['right-feed','rightFeed']])$(id).addEventListener('input',()=>{const f=$(id);if(f.value.trim() && f.validity.valid){prefs[key]=Number(f.value);savePreferences();}});
$('mode').addEventListener('change',()=>{prefs.mode=$('mode').value;savePreferences();});
$('baud').addEventListener('change',()=>{config.baud=Number($('baud').value);savePreferences();});
if(navigator.mediaDevices?.enumerateDevices)cameraList().catch(e=>{$('camera-discovery').textContent='摄像头枚举失败：'+e.message;log('error',e.message);});
else $('camera-discovery').textContent='摄像头 API 不可用，请用桌面 Chrome / Edge 打开 localhost 页面';
log('info','调试台已就绪 · 已加载保存的设置 · 请先连接');
