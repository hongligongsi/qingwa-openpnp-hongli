/* ============================================================
 *  青蛙硬件调试台 v3.0 — core.js 单元测试
 *  ------------------------------------------------------------
 *  运行方式：node --test core.test.js
 *  依赖：仅 Node.js 内置 test + assert 模块，无需 npm 安装任何包
 *  覆盖范围：配置校验、指令构造、Channel 状态机、坐标解析、照明/气路/吸嘴等
 *  ============================================================ */
'use strict';
const test = require('node:test');    // Node 内置测试框架
const assert = require('node:assert/strict');  // 严格相等断言
const Bench = require('./core.js');   // 被测模块

/* ---------- 配置校验 ---------- */
test('Marlin preset and config validation',()=>{
  // 验证默认配置可通过校验，气泵指令正确
  assert.equal(Bench.validate({...Bench.DEFAULTS}).pumpRightOn,'M106 P2 S255');
  // 校验：非法正则 → 抛错
  assert.throws(()=>Bench.validate({...Bench.DEFAULTS,ack:'['}));
  // 校验：超时超出范围 → 抛错
  assert.throws(()=>Bench.validate({...Bench.DEFAULTS,timeout:0}));
  // 校验：sharedLights 类型错误（布尔应是字符串 yes）→ 抛错
  assert.throws(()=>Bench.validate({...Bench.DEFAULTS,sharedLights:'yes'}));
  // 校验：点动模板缺占位符 → 抛错
  assert.throws(()=>Bench.validate({...Bench.DEFAULTS,jog:'G1'}));
  // 校验：空指令行、未替换占位符 → 抛错
  assert.throws(()=>Bench.lines(''));
  assert.throws(()=>Bench.lines('G1 X{X}'));
});

/* ---------- 点动指令构造 ---------- */
test('jog emits one relative axis and restores absolute mode',()=>{
  // Z 轴 -0.1mm，速度 600 → 生成完整序列
  assert.equal(Bench.jog(Bench.DEFAULTS,'Z',-0.1,600),'G21\nG91\nG1 Z-0.1 F600\nG90');
  // 校验：距离 Infinity / 速度 0 → 抛错
  assert.throws(()=>Bench.jog(Bench.DEFAULTS,'Z',Infinity,600));
  assert.throws(()=>Bench.jog(Bench.DEFAULTS,'X',1,0));
});

/* ---------- 坐标解析（Marlin / GRBL 两种格式） ---------- */
test('positions are parsed only from reports, ignoring step counts',()=>{
  // Marlin 风格：忽略 Count 步数后缀
  assert.deepEqual(Bench.position('X:12.30 Y:-4.00 Z:1.25 Count X:982 Y:1 Z:2'),{X:12.3,Y:-4,Z:1.25,source:'控制器坐标回报'});
  // ok 不是坐标行 → 返回 null
  assert.equal(Bench.position('ok'),null);
  // GRBL 风格 <Idle|MPos:1.2,3.4,5.6|FS:...> → 解析机器坐标
  assert.equal(Bench.position('<Idle|MPos:1.2,3.4,5.6|FS:0,0>').source,'机器坐标回报');
});

/* ---------- Channel 状态机：指令串行等待 ok ---------- */
test('commands wait for acknowledgement before next line',async()=>{
  const sent=[];const channel=new Bench.Channel(async s=>sent.push(s),Bench.DEFAULTS);
  const action=channel.execute('G91\nG1 X1 F600\nG90');
  // 第一条 G91 发出，等待 ok
  await new Promise(r=>setImmediate(r));assert.deepEqual(sent,['G91\n']);
  channel.receive('busy: processing');await new Promise(r=>setImmediate(r));assert.equal(sent.length,1);  // 中间的 busy 不触发下一条
  // ok → 第二条 G1 X1 F600 发出
  channel.receive('ok');await new Promise(r=>setImmediate(r));assert.equal(sent[1],'G1 X1 F600\n');
  // ok → 第三条 G90 发出
  channel.receive('ok');await new Promise(r=>setImmediate(r));assert.equal(sent[2],'G90\n');
  // 最终 ok → execute 完成，busy=false
  channel.receive('ok');await action;assert.equal(channel.busy,false);
});

/* ---------- Channel：控制器报错 → 整条批次终止 ---------- */
test('controller errors halt all remaining lines',async()=>{
  const sent=[];const channel=new Bench.Channel(async s=>sent.push(s),Bench.DEFAULTS);
  const action=channel.execute('G91\nG1 X1 F600\nG90');const rejection=assert.rejects(action,/控制器报错/);
  // 发出第一条 G91，收到 Error 后不再发后续
  channel.receive('Error: bad command');await rejection;assert.equal(sent.length,1);assert.equal(channel.halted,true);
  // halted 后继续 execute → 直接抛"连接已锁定"
  await assert.rejects(channel.execute('M114'),/连接已锁定/);
});

/* ---------- Channel：中途 cancel → 已发的不撤回，未发的不再发 ---------- */
test('cancel while waiting prevents subsequent motion',async()=>{
  const sent=[];const channel=new Bench.Channel(async s=>sent.push(s),Bench.DEFAULTS);
  const action=channel.execute('G91\nG1 X1 F600');const rejection=assert.rejects(action,/操作已停止/);
  channel.cancel();await rejection;channel.receive('ok');assert.equal(sent.length,1);  // 只发了第一条，后续被阻断
});

/* ---------- Channel：超时 → halted，新指令直接拒绝 ---------- */
test('timeout locks connection and concurrent commands are rejected',async()=>{
  const channel=new Bench.Channel(async()=>{},{...Bench.DEFAULTS,timeout:15});  // 15ms 超时（极短）
  const action=channel.execute('M114');const rejection=assert.rejects(action,/等待响应超时/);
  // timeout 期间尝试并发 → 抛"上一操作"
  await assert.rejects(channel.execute('G28'),/上一操作/);await rejection;assert.equal(channel.halted,true);
});

/* ---------- 原始字符转义 ---------- */
test('raw stop decodes explicit hex control bytes',()=>assert.equal(Bench.raw('\\x18'),String.fromCharCode(24)));

/* ---------- 旧版配置自动迁移 ---------- */
test('old default shutdown profiles migrate to quickstop while explicit v2 overrides remain',()=>{
  // v1 版本 stop=M112（必须复位）自动迁移到 M410（软急停）
  const old=Bench.validate({...Bench.DEFAULTS,version:1,stop:'M112'});
  assert.equal(old.version,3);assert.equal(old.stop,'M410');
  // 但用户显式设的 M112（非 v1 默认）保留原样
  assert.equal(Bench.validate({...Bench.DEFAULTS,stop:'M112'}).stop,'M112');
});

/* ---------- 急停：cancel 立即执行停机，未发的运动全部跳过 ---------- */
test('stop bypasses pending acknowledgement and never emits remaining movement',async()=>{
  const sent=[];const c=new Bench.Channel(async s=>sent.push(s),Bench.DEFAULTS);
  const action=c.execute('G91\nG1 X10 F1000\nG90');const rejection=assert.rejects(action,/软件急停/);
  // 发出 G91 后 cancel → 立即发 M410，不再发 G1 X10
  c.cancel('软件急停');await c.write('M410\n');await rejection;
  assert.deepEqual(sent,['G91\n','M410\n']);assert.equal(c.halted,true);
});

/* ---------- 急停恢复 synchronize：必须收到 M118 标记回显才解除 halted ---------- */
test('resume requires a fresh echo marker and following ack, ignoring stale ok',async()=>{
  const sent=[];const c=new Bench.Channel(async s=>sent.push(s),Bench.DEFAULTS);c.cancel();
  const sync=c.synchronize('BENCH_SYNC_TEST_1');
  // 中途的 ok / echo:enqueueing 都不算，必须收到 echo:BENCH_SYNC_TEST_1
  c.receive('ok');c.receive('echo:enqueueing M118 BENCH_SYNC_TEST_1');c.receive('ok');
  await new Promise(r=>setImmediate(r));assert.equal(c.halted,true);assert.equal(c.busy,true);  // 还在等待标记回显
  c.receive('echo:BENCH_SYNC_TEST_1');c.receive('ok');await sync;
  assert.equal(c.halted,false);assert.deepEqual(sent,['M118 BENCH_SYNC_TEST_1\n']);
  const query=c.execute('M114');c.receive('ok');await query;  // 恢复后可以继续发指令
});

/* ---------- 恢复期间再次急停 → 保持锁定 ---------- */
test('another stop during recovery keeps the channel latched',async()=>{
  const c=new Bench.Channel(async()=>{},Bench.DEFAULTS);c.cancel();
  const sync=c.synchronize('BENCH_SYNC_TEST_2');const rejection=assert.rejects(sync,/再次急停/);
  c.cancel('再次急停');c.receive('BENCH_SYNC_TEST_2');c.receive('ok');await rejection;assert.equal(c.halted,true);
});

/* ---------- 吸嘴旋转指令：相对 vs 绝对 ---------- */
test('nozzle rotation generates isolated relative and absolute rotary movement',()=>{
  // 相对：G91 G1 A-45 F600 → G90
  assert.equal(Bench.rotate(Bench.DEFAULTS,'Left',-45,600),'G21\nG91\nG1 A-45 F600\nG90\nM400\nM114');
  // 绝对：G90 G1 B90 F900 → G90（最终还是绝对模式）
  assert.equal(Bench.rotate(Bench.DEFAULTS,'Right',90,900,true),'G21\nG90\nG1 B90 F900\nG90\nM400\nM114');
  // 校验：角度超限、零相对角度、两吸嘴轴相同 → 抛错
  assert.throws(()=>Bench.rotate(Bench.DEFAULTS,'Left',361,600));
  assert.throws(()=>Bench.rotate(Bench.DEFAULTS,'Right',0,600));
  assert.throws(()=>Bench.validate({...Bench.DEFAULTS,nozzleLeftAxis:'B'}));
});

/* ---------- 坐标里包含 A/B 旋转轴 ---------- */
test('rotational positions are read alongside XYZ without reading step-count fields',()=>{
  const p=Bench.position('X:1 Y:2 Z:3 A:-45.25 B:90 Count A:222');
  assert.equal(p.A,-45.25);assert.equal(p.B,90);
});

/* ---------- 偏好 JSON 往返（所有字段都能正确序列化/反序列化） ---------- */
test('all preference fields survive a JSON save and reload',()=>{
  const p=Bench.preferences({...Bench.PREFS,mode:'serial',feed:1200,feedZ:400,xyStep:5,zStep:1,leftAngle:30,rightAngle:60,leftTarget:90,rightTarget:-45,leftFeed:900,rightFeed:1200,topRotation:30,bottomRotation:-90,topMirror:true,bottomCross:false,topDevice:'device-a',bottomDevice:'device-b',topDeviceLabel:'TOP USB',bottomDeviceLabel:'BOTTOM USB'});
  assert.deepEqual(Bench.preferences(JSON.parse(JSON.stringify(p))),p);
});

/* ---------- 偏好损坏值回退到默认 ---------- */
test('corrupted persisted values fall back to valid defaults',()=>{
  const p=Bench.preferences({feed:0,xyStep:123,topRotation:Infinity,topMirror:'true',mode:'invalid',leftAngle:-5});
  assert.equal(p.feed,1000);assert.equal(p.xyStep,1);assert.equal(p.topRotation,0);assert.equal(p.topMirror,false);assert.equal(p.mode,'demo');assert.equal(p.leftAngle,45);
});

/* ---------- 摄像头旋转后视野尺寸计算 ---------- */
test('rotated frame bounds preserve the whole camera image',()=>{
  assert.deepEqual(Bench.imageBounds(1280,720,0),{width:1280,height:720});
  assert.deepEqual(Bench.imageBounds(1280,720,90),{width:720,height:1280});
  assert.deepEqual(Bench.imageBounds(1280,720,-90),{width:720,height:1280});
  assert.deepEqual(Bench.imageBounds(1280,720,180),{width:1280,height:720});
});

/* ---------- 摄像头枚举：授权后能拿到所有设备，临时 stream 在退出前释放 ---------- */
test('camera discovery sees all three devices before releasing temporary permission',async()=>{
  let live=false;const media={getUserMedia:async()=>{live=true;return{getTracks:()=>[{stop:()=>{live=false;}}]};},enumerateDevices:async()=>live?['2M','FHD C3 Camera','Integrated Camera'].map((label,i)=>({kind:'videoinput',deviceId:String(i+1),label})):[{kind:'videoinput',deviceId:'2',label:'FHD C3 Camera'}]};
  const result=await Bench.discoverCameras(media,true);assert.equal(result.devices.length,3);assert.equal(live,false);assert.equal(result.authorizationError,null);
});

/* ---------- 摄像头授权失败但仍能枚举未授权设备 ---------- */
test('camera capture failure still enumerates other available devices',async()=>{
  const result=await Bench.discoverCameras({getUserMedia:async()=>{throw Object.assign(Error('busy'),{name:'NotReadableError'});},enumerateDevices:async()=>[{kind:'videoinput',deviceId:'other',label:'2M'},{kind:'videoinput',deviceId:'',label:''},{kind:'audioinput',deviceId:'mic'}]},true);
  assert.equal(result.devices.length,1);assert.equal(result.hiddenCount,1);assert.equal(result.authorizationError.name,'NotReadableError');
});

/* ---------- 摄像头枚举失败也要释放临时 stream ---------- */
test('failed camera enumeration releases temporary camera and passive scan never requests access',async()=>{
  let stopped=false;await assert.rejects(Bench.discoverCameras({getUserMedia:async()=>({getTracks:()=>[{stop:()=>{stopped=true;}}]}),enumerateDevices:async()=>{throw Error('enumeration failed');}},true));assert.equal(stopped,true);
  const result=await Bench.discoverCameras({getUserMedia:async()=>{throw Error('must not request');},enumerateDevices:async()=>[]});assert.equal(result.devices.length,0);assert.equal(result.authorizationError,null);
});

/* ---------- 限位 M119 解析 ---------- */
test('Marlin limit reports parse triggered, open and additional inputs without inventing states',()=>{
  assert.deepEqual(Bench.endstop('x_min: open'),{name:'x_min',triggered:false});
  assert.deepEqual(Bench.endstop('echo: Y_MAX: TRIGGERED'),{name:'y_max',triggered:true});
  assert.deepEqual(Bench.endstop('z2_min: TRIGGERED'),{name:'z2_min',triggered:true});
  assert.deepEqual(Bench.endstop('z_probe: open'),{name:'z_probe',triggered:false});
  // 不是限位行的返回 null
  for(const line of ['ok','Reporting endstop status','x_min: unknown','X:0 Y:0 Z:0','x_min: open extra'])assert.equal(Bench.endstop(line),null);
});

/* ---------- 照明独立模式：单路开/关 ---------- */
test('single lighting selects the requested strip and closes only that strip',()=>{
  const c={...Bench.DEFAULTS,sharedLights:false},p=Bench.preferences({lightTopBrightness:45,lightTopColor:'#ff8000'});
  assert.deepEqual(Bench.lightingPlan(c,p,'lightTop',true),{command:'M150 S1 P45 R255 U128 B0',states:{lightTop:true}});
  assert.deepEqual(Bench.lightingPlan(c,p,'lightBottom',false),{command:'M150 S0 P0',states:{lightBottom:false}});
});

/* ---------- 照明联控 vs 独立：联控下下灯用上灯参数 ---------- */
test('linked lighting uses upper settings for both strips while all independent uses each setting',()=>{
  const p=Bench.preferences({lightTopBrightness:100,lightTopColor:'#123456',lightBottomBrightness:55,lightBottomColor:'#abcdef'});
  // 联控：上灯 100% 红+绿+蓝 → 下灯也用 100%
  assert.equal(Bench.lightingPlan(Bench.DEFAULTS,p,'lightBottom',true).command,'M150 S1 P100 R18 U52 B86\nM150 S0 P100 R18 U52 B86');
  // 独立：上灯 100%，下灯 55% 各用各的颜色
  assert.equal(Bench.lightingPlan({...Bench.DEFAULTS,sharedLights:false},p,'all',true).command,'M150 S1 P100 R18 U52 B86\nM150 S0 P55 R171 U205 B239');
  // 全部关：两条 M150 P0
  assert.equal(Bench.lightingPlan(Bench.DEFAULTS,p,'all',false).command,'M150 S1 P0\nM150 S0 P0');
});

/* ---------- 照明偏好往返 + 零亮度/黑色永远不算开启 ---------- */
test('lighting settings save safely and zero brightness or black color never indicates light on',()=>{
  const p=Bench.preferences({lightTopBrightness:0,lightBottomColor:'#000000'});
  // 亮度 0 或颜色全黑 → states 里标为 false（虽然发了 on 的指令，但效果等于没亮）
  assert.equal(Bench.lightingPlan({...Bench.DEFAULTS,sharedLights:false},p,'lightTop',true).states.lightTop,false);
  assert.equal(Bench.lightingPlan({...Bench.DEFAULTS,sharedLights:false},p,'lightBottom',true).states.lightBottom,false);
  assert.deepEqual(Bench.preferences(JSON.parse(JSON.stringify(p))),p);
  assert.equal(Bench.preferences({lightTopBrightness:256,lightBottomColor:'invalid'}).lightTopBrightness,45);  // 越界回退到默认 45
});

/* ---------- 旧版 M150 模板迁移 + 用户自定义保留 ---------- */
test('legacy light defaults migrate once while custom commands and unselected off are preserved',()=>{
  const old={...Bench.DEFAULTS,version:2,lightTopOn:'M150 P45 R255 U255 B255',lightBottomOn:'M150 P45 R255 U255 B255',lightTopOff:'M150 P0',lightBottomOff:'M150 P0'};
  // v2 的 M150 P0 旧模板自动迁移成 M150 S1 P0（带上下灯选择参数）
  assert.equal(Bench.validate(old).lightTopOff,'M150 S1 P0');
  // 但用户自定义的模板保留原样
  const custom=Bench.validate({...old,lightTopOn:'M150 S1 P45 R255 U255 B255',sharedLights:false});
  assert.equal(custom.lightTopOff,'M150 P0');
  assert.deepEqual(Bench.lightingPlan(custom,Bench.PREFS,'lightTop',false).states,{lightTop:false,lightBottom:null});
  assert.equal(Bench.lighting(custom,{...Bench.PREFS,lightTopBrightness:70},'lightTop',true),'M150 S1 P70 R255 U255 B255');
});

/* ---------- 气泵 PWM 占空比转 M106 S 值 ---------- */
test('pump duty generates separate PWM outputs and zero always switches off',()=>{
  // 50% → S128（255/2=127.5 → 四舍五入 128）
  assert.deepEqual(Bench.pump(Bench.DEFAULTS,'pumpLeft',50),{command:'M106 P0 S128',percent:50,pwm:128});
  assert.equal(Bench.pump(Bench.DEFAULTS,'pumpRight',100).command,'M106 P2 S255');
  // 0% → 关泵指令 M107
  assert.equal(Bench.pump(Bench.DEFAULTS,'pumpLeft',0).command,'M107 P0');
  assert.equal(Bench.pump(Bench.DEFAULTS,'pumpRight',30,false).command,'M107 P2');
  // 校验：非气泵键、超限 → 抛错
  assert.throws(()=>Bench.pump(Bench.DEFAULTS,'valveLeft',50));assert.throws(()=>Bench.pump(Bench.DEFAULTS,'pumpLeft',101));
});

/* ---------- 气泵偏好往返 + 用户自定义模板占位符 ---------- */
test('pump preferences round trip and custom PWM commands are explicit',()=>{
  const p=Bench.preferences({pumpLeftPercent:55,pumpRightPercent:30});assert.deepEqual(Bench.preferences(JSON.parse(JSON.stringify(p))),p);
  assert.equal(Bench.preferences({pumpLeftPercent:-1,pumpRightPercent:NaN}).pumpLeftPercent,100);  // 越界回退到 100%
  // 标准 M106：自动替换 S 参数（支持分号注释）
  assert.equal(Bench.pump({...Bench.DEFAULTS,pumpLeftOn:'M106 P0 S255 ; pump'},'pumpLeft',40).command,'M106 P0 S102 ; pump');
  // 用户自定义模板：支持 {pwm} 占位符
  assert.equal(Bench.pump({...Bench.DEFAULTS,pumpLeftOn:'CUSTOM {pwm}'},'pumpLeft',40).command,'CUSTOM 102');
  // 用户自定义模板但没有 {pwm} → 抛错
  assert.throws(()=>Bench.pump({...Bench.DEFAULTS,pumpLeftOn:'CUSTOM'},'pumpLeft',40),/占位符/);
});

/* ---------- Dial 旋钮：270° 弧线 → 0~max 值 ---------- */
test('arc control maps the 270 degree sweep and clamps the bottom gap',()=>{
  // (dx, dy) 在不同象限 → 映射到 0~100 的值
  assert.equal(Bench.dialValue(-1,1,100),0);assert.equal(Bench.dialValue(0,-1,100),50);assert.equal(Bench.dialValue(1,1,100),100);
  // 角度超出 270° 范围 → 钳位到 0 或 100
  assert.equal(Bench.dialValue(-1,2,100),0);assert.equal(Bench.dialValue(1,2,100),100);
  // 中心位置或鼠标太近 → null（不触发）
  assert.equal(Bench.dialValue(0,0,255),null);assert.equal(Bench.dialValue(0,-1,255),128);
});

/* ---------- 100mm 步长预设 + 往返校验 ---------- */
test('100 mm steps persist and generate bounded single axis movement',()=>{
  const p=Bench.preferences({xyStep:100,zStep:100});assert.equal(p.xyStep,100);assert.equal(p.zStep,100);assert.deepEqual(Bench.preferences(JSON.parse(JSON.stringify(p))),p);
  assert.equal(Bench.jog(Bench.DEFAULTS,'X',100,1000),'G21\nG91\nG1 X100 F1000\nG90');
  assert.equal(Bench.jog(Bench.DEFAULTS,'Z',-100,300),'G21\nG91\nG1 Z-100 F300\nG90');
  assert.throws(()=>Bench.jog(Bench.DEFAULTS,'X',101,1000));  // 超过 ±100mm
});
