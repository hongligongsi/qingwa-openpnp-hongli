'use strict';
const test = require('node:test');
const assert = require('node:assert/strict');
const Bench = require('./core.js');
test('Marlin preset and config validation',()=>{
  assert.equal(Bench.validate({...Bench.DEFAULTS}).pumpRightOn,'M106 P2 S255');
  assert.throws(()=>Bench.validate({...Bench.DEFAULTS,ack:'['}));
  assert.throws(()=>Bench.validate({...Bench.DEFAULTS,timeout:0}));
  assert.throws(()=>Bench.validate({...Bench.DEFAULTS,sharedLights:'yes'}));
  assert.throws(()=>Bench.validate({...Bench.DEFAULTS,jog:'G1'}));
  assert.throws(()=>Bench.lines(''));
  assert.throws(()=>Bench.lines('G1 X{X}'));
});
test('jog emits one relative axis and restores absolute mode',()=>{
  assert.equal(Bench.jog(Bench.DEFAULTS,'Z',-0.1,600),'G21\nG91\nG1 Z-0.1 F600\nG90');
  assert.throws(()=>Bench.jog(Bench.DEFAULTS,'Z',Infinity,600));
  assert.throws(()=>Bench.jog(Bench.DEFAULTS,'X',1,0));
});
test('positions are parsed only from reports, ignoring step counts',()=>{
  assert.deepEqual(Bench.position('X:12.30 Y:-4.00 Z:1.25 Count X:982 Y:1 Z:2'),{X:12.3,Y:-4,Z:1.25,source:'控制器坐标回报'});
  assert.equal(Bench.position('ok'),null);
  assert.equal(Bench.position('<Idle|MPos:1.2,3.4,5.6|FS:0,0>').source,'机器坐标回报');
});
test('commands wait for acknowledgement before next line',async()=>{
  const sent=[];const channel=new Bench.Channel(async s=>sent.push(s),Bench.DEFAULTS);
  const action=channel.execute('G91\nG1 X1 F600\nG90');
  await new Promise(r=>setImmediate(r));assert.deepEqual(sent,['G91\n']);
  channel.receive('busy: processing');await new Promise(r=>setImmediate(r));assert.equal(sent.length,1);
  channel.receive('ok');await new Promise(r=>setImmediate(r));assert.equal(sent[1],'G1 X1 F600\n');
  channel.receive('ok');await new Promise(r=>setImmediate(r));assert.equal(sent[2],'G90\n');
  channel.receive('ok');await action;assert.equal(channel.busy,false);
});
test('controller errors halt all remaining lines',async()=>{
  const sent=[];const channel=new Bench.Channel(async s=>sent.push(s),Bench.DEFAULTS);
  const action=channel.execute('G91\nG1 X1 F600\nG90');const rejection=assert.rejects(action,/控制器报错/);
  channel.receive('Error: bad command');await rejection;assert.equal(sent.length,1);assert.equal(channel.halted,true);
  await assert.rejects(channel.execute('M114'),/连接已锁定/);
});
test('cancel while waiting prevents subsequent motion',async()=>{
  const sent=[];const channel=new Bench.Channel(async s=>sent.push(s),Bench.DEFAULTS);
  const action=channel.execute('G91\nG1 X1 F600');const rejection=assert.rejects(action,/操作已停止/);
  channel.cancel();await rejection;channel.receive('ok');assert.equal(sent.length,1);
});
test('timeout locks connection and concurrent commands are rejected',async()=>{
  const channel=new Bench.Channel(async()=>{},{...Bench.DEFAULTS,timeout:15});
  const action=channel.execute('M114');const rejection=assert.rejects(action,/等待响应超时/);
  await assert.rejects(channel.execute('G28'),/上一操作/);await rejection;assert.equal(channel.halted,true);
});
test('raw stop decodes explicit hex control bytes',()=>assert.equal(Bench.raw('\\x18'),String.fromCharCode(24)));
test('old default shutdown profiles migrate to quickstop while explicit v2 overrides remain',()=>{
  const old=Bench.validate({...Bench.DEFAULTS,version:1,stop:'M112'});
  assert.equal(old.version,3);assert.equal(old.stop,'M410');
  assert.equal(Bench.validate({...Bench.DEFAULTS,stop:'M112'}).stop,'M112');
});
test('stop bypasses pending acknowledgement and never emits remaining movement',async()=>{
  const sent=[];const c=new Bench.Channel(async s=>sent.push(s),Bench.DEFAULTS);
  const action=c.execute('G91\nG1 X10 F1000\nG90');const rejection=assert.rejects(action,/软件急停/);
  c.cancel('软件急停');await c.write('M410\n');await rejection;
  assert.deepEqual(sent,['G91\n','M410\n']);assert.equal(c.halted,true);
});
test('resume requires a fresh echo marker and following ack, ignoring stale ok',async()=>{
  const sent=[];const c=new Bench.Channel(async s=>sent.push(s),Bench.DEFAULTS);c.cancel();
  const sync=c.synchronize('BENCH_SYNC_TEST_1');
  c.receive('ok');c.receive('echo:enqueueing M118 BENCH_SYNC_TEST_1');c.receive('ok');
  await new Promise(r=>setImmediate(r));assert.equal(c.halted,true);assert.equal(c.busy,true);
  c.receive('echo:BENCH_SYNC_TEST_1');c.receive('ok');await sync;
  assert.equal(c.halted,false);assert.deepEqual(sent,['M118 BENCH_SYNC_TEST_1\n']);
  const query=c.execute('M114');c.receive('ok');await query;
});
test('another stop during recovery keeps the channel latched',async()=>{
  const c=new Bench.Channel(async()=>{},Bench.DEFAULTS);c.cancel();
  const sync=c.synchronize('BENCH_SYNC_TEST_2');const rejection=assert.rejects(sync,/再次急停/);
  c.cancel('再次急停');c.receive('BENCH_SYNC_TEST_2');c.receive('ok');await rejection;assert.equal(c.halted,true);
});
test('nozzle rotation generates isolated relative and absolute rotary movement',()=>{
  assert.equal(Bench.rotate(Bench.DEFAULTS,'Left',-45,600),'G21\nG91\nG1 A-45 F600\nG90\nM400\nM114');
  assert.equal(Bench.rotate(Bench.DEFAULTS,'Right',90,900,true),'G21\nG90\nG1 B90 F900\nG90\nM400\nM114');
  assert.throws(()=>Bench.rotate(Bench.DEFAULTS,'Left',361,600));
  assert.throws(()=>Bench.rotate(Bench.DEFAULTS,'Right',0,600));
  assert.throws(()=>Bench.validate({...Bench.DEFAULTS,nozzleLeftAxis:'B'}));
});
test('rotational positions are read alongside XYZ without reading step-count fields',()=>{
  const p=Bench.position('X:1 Y:2 Z:3 A:-45.25 B:90 Count A:222');
  assert.equal(p.A,-45.25);assert.equal(p.B,90);
});
test('all preference fields survive a JSON save and reload',()=>{
  const p=Bench.preferences({...Bench.PREFS,mode:'serial',feed:1200,feedZ:400,xyStep:5,zStep:1,leftAngle:30,rightAngle:60,leftTarget:90,rightTarget:-45,leftFeed:900,rightFeed:1200,topRotation:30,bottomRotation:-90,topMirror:true,bottomCross:false,topDevice:'device-a',bottomDevice:'device-b',topDeviceLabel:'TOP USB',bottomDeviceLabel:'BOTTOM USB'});
  assert.deepEqual(Bench.preferences(JSON.parse(JSON.stringify(p))),p);
});
test('corrupted persisted values fall back to valid defaults',()=>{
  const p=Bench.preferences({feed:0,xyStep:123,topRotation:Infinity,topMirror:'true',mode:'invalid',leftAngle:-5});
  assert.equal(p.feed,1000);assert.equal(p.xyStep,1);assert.equal(p.topRotation,0);assert.equal(p.topMirror,false);assert.equal(p.mode,'demo');assert.equal(p.leftAngle,45);
});
test('rotated frame bounds preserve the whole camera image',()=>{
  assert.deepEqual(Bench.imageBounds(1280,720,0),{width:1280,height:720});
  assert.deepEqual(Bench.imageBounds(1280,720,90),{width:720,height:1280});
  assert.deepEqual(Bench.imageBounds(1280,720,-90),{width:720,height:1280});
  assert.deepEqual(Bench.imageBounds(1280,720,180),{width:1280,height:720});
});
test('camera discovery sees all three devices before releasing temporary permission',async()=>{
  let live=false;const media={getUserMedia:async()=>{live=true;return{getTracks:()=>[{stop:()=>{live=false;}}]};},enumerateDevices:async()=>live?['2M','FHD C3 Camera','Integrated Camera'].map((label,i)=>({kind:'videoinput',deviceId:String(i+1),label})):[{kind:'videoinput',deviceId:'2',label:'FHD C3 Camera'}]};
  const result=await Bench.discoverCameras(media,true);assert.equal(result.devices.length,3);assert.equal(live,false);assert.equal(result.authorizationError,null);
});
test('camera capture failure still enumerates other available devices',async()=>{
  const result=await Bench.discoverCameras({getUserMedia:async()=>{throw Object.assign(Error('busy'),{name:'NotReadableError'});},enumerateDevices:async()=>[{kind:'videoinput',deviceId:'other',label:'2M'},{kind:'videoinput',deviceId:'',label:''},{kind:'audioinput',deviceId:'mic'}]},true);
  assert.equal(result.devices.length,1);assert.equal(result.hiddenCount,1);assert.equal(result.authorizationError.name,'NotReadableError');
});
test('failed camera enumeration releases temporary camera and passive scan never requests access',async()=>{
  let stopped=false;await assert.rejects(Bench.discoverCameras({getUserMedia:async()=>({getTracks:()=>[{stop:()=>{stopped=true;}}]}),enumerateDevices:async()=>{throw Error('enumeration failed');}},true));assert.equal(stopped,true);
  const result=await Bench.discoverCameras({getUserMedia:async()=>{throw Error('must not request');},enumerateDevices:async()=>[]});assert.equal(result.devices.length,0);assert.equal(result.authorizationError,null);
});
test('Marlin limit reports parse triggered, open and additional inputs without inventing states',()=>{
  assert.deepEqual(Bench.endstop('x_min: open'),{name:'x_min',triggered:false});
  assert.deepEqual(Bench.endstop('echo: Y_MAX: TRIGGERED'),{name:'y_max',triggered:true});
  assert.deepEqual(Bench.endstop('z2_min: TRIGGERED'),{name:'z2_min',triggered:true});
  assert.deepEqual(Bench.endstop('z_probe: open'),{name:'z_probe',triggered:false});
  for(const line of ['ok','Reporting endstop status','x_min: unknown','X:0 Y:0 Z:0','x_min: open extra'])assert.equal(Bench.endstop(line),null);
});
test('single lighting selects the requested strip and closes only that strip',()=>{
  const c={...Bench.DEFAULTS,sharedLights:false},p=Bench.preferences({lightTopBrightness:45,lightTopColor:'#ff8000'});
  assert.deepEqual(Bench.lightingPlan(c,p,'lightTop',true),{command:'M150 S1 P45 R255 U128 B0',states:{lightTop:true}});
  assert.deepEqual(Bench.lightingPlan(c,p,'lightBottom',false),{command:'M150 S0 P0',states:{lightBottom:false}});
});
test('linked lighting uses upper settings for both strips while all independent uses each setting',()=>{
  const p=Bench.preferences({lightTopBrightness:100,lightTopColor:'#123456',lightBottomBrightness:55,lightBottomColor:'#abcdef'});
  assert.equal(Bench.lightingPlan(Bench.DEFAULTS,p,'lightBottom',true).command,'M150 S1 P100 R18 U52 B86\nM150 S0 P100 R18 U52 B86');
  assert.equal(Bench.lightingPlan({...Bench.DEFAULTS,sharedLights:false},p,'all',true).command,'M150 S1 P100 R18 U52 B86\nM150 S0 P55 R171 U205 B239');
  assert.equal(Bench.lightingPlan(Bench.DEFAULTS,p,'all',false).command,'M150 S1 P0\nM150 S0 P0');
});
test('lighting settings save safely and zero brightness or black color never indicates light on',()=>{
  const p=Bench.preferences({lightTopBrightness:0,lightBottomColor:'#000000'});
  assert.equal(Bench.lightingPlan({...Bench.DEFAULTS,sharedLights:false},p,'lightTop',true).states.lightTop,false);
  assert.equal(Bench.lightingPlan({...Bench.DEFAULTS,sharedLights:false},p,'lightBottom',true).states.lightBottom,false);
  assert.deepEqual(Bench.preferences(JSON.parse(JSON.stringify(p))),p);
  assert.equal(Bench.preferences({lightTopBrightness:256,lightBottomColor:'invalid'}).lightTopBrightness,45);
});
test('legacy light defaults migrate once while custom commands and unselected off are preserved',()=>{
  const old={...Bench.DEFAULTS,version:2,lightTopOn:'M150 P45 R255 U255 B255',lightBottomOn:'M150 P45 R255 U255 B255',lightTopOff:'M150 P0',lightBottomOff:'M150 P0'};
  assert.equal(Bench.validate(old).lightTopOff,'M150 S1 P0');
  const custom=Bench.validate({...old,lightTopOn:'M150 S1 P45 R255 U255 B255',sharedLights:false});
  assert.equal(custom.lightTopOff,'M150 P0');
  assert.deepEqual(Bench.lightingPlan(custom,Bench.PREFS,'lightTop',false).states,{lightTop:false,lightBottom:null});
  assert.equal(Bench.lighting(custom,{...Bench.PREFS,lightTopBrightness:70},'lightTop',true),'M150 S1 P70 R255 U255 B255');
});
test('pump duty generates separate PWM outputs and zero always switches off',()=>{
  assert.deepEqual(Bench.pump(Bench.DEFAULTS,'pumpLeft',50),{command:'M106 P0 S128',percent:50,pwm:128});
  assert.equal(Bench.pump(Bench.DEFAULTS,'pumpRight',100).command,'M106 P2 S255');
  assert.equal(Bench.pump(Bench.DEFAULTS,'pumpLeft',0).command,'M107 P0');
  assert.equal(Bench.pump(Bench.DEFAULTS,'pumpRight',30,false).command,'M107 P2');
  assert.throws(()=>Bench.pump(Bench.DEFAULTS,'valveLeft',50));assert.throws(()=>Bench.pump(Bench.DEFAULTS,'pumpLeft',101));
});
test('pump preferences round trip and custom PWM commands are explicit',()=>{
  const p=Bench.preferences({pumpLeftPercent:55,pumpRightPercent:30});assert.deepEqual(Bench.preferences(JSON.parse(JSON.stringify(p))),p);
  assert.equal(Bench.preferences({pumpLeftPercent:-1,pumpRightPercent:NaN}).pumpLeftPercent,100);
  assert.equal(Bench.pump({...Bench.DEFAULTS,pumpLeftOn:'M106 P0 S255 ; pump'},'pumpLeft',40).command,'M106 P0 S102 ; pump');
  assert.equal(Bench.pump({...Bench.DEFAULTS,pumpLeftOn:'CUSTOM {pwm}'},'pumpLeft',40).command,'CUSTOM 102');
  assert.throws(()=>Bench.pump({...Bench.DEFAULTS,pumpLeftOn:'CUSTOM'},'pumpLeft',40),/占位符/);
});
test('arc control maps the 270 degree sweep and clamps the bottom gap',()=>{
  assert.equal(Bench.dialValue(-1,1,100),0);assert.equal(Bench.dialValue(0,-1,100),50);assert.equal(Bench.dialValue(1,1,100),100);
  assert.equal(Bench.dialValue(-1,2,100),0);assert.equal(Bench.dialValue(1,2,100),100);
  assert.equal(Bench.dialValue(0,0,255),null);assert.equal(Bench.dialValue(0,-1,255),128);
});
test('100 mm steps persist and generate bounded single axis movement',()=>{
  const p=Bench.preferences({xyStep:100,zStep:100});assert.equal(p.xyStep,100);assert.equal(p.zStep,100);assert.deepEqual(Bench.preferences(JSON.parse(JSON.stringify(p))),p);
  assert.equal(Bench.jog(Bench.DEFAULTS,'X',100,1000),'G21\nG91\nG1 X100 F1000\nG90');
  assert.equal(Bench.jog(Bench.DEFAULTS,'Z',-100,300),'G21\nG91\nG1 Z-100 F300\nG90');
  assert.throws(()=>Bench.jog(Bench.DEFAULTS,'X',101,1000));
});
