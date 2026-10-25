# OpenPnP 定制版（lfpnp_v1.0）与原版差异详解

> **分析对象**：`lfpnp_v1.0/OpenPnP/app/openpnp-gui-0.0.1-alpha-SNAPSHOT.jar`
> （11.3 MB，含 724 个类，构建于 2026-10-23 11:19，Maven Jar Plugin 3.2.0 + JDK 17）
> **对比基线**：GitHub `openpnp/openpnp` 主线源码（708 个类）
> **分析方法**：解包 jar → CFR 反编译逐文件 diff + class 常量池中文扫描 + 原版源码逐行比对
>
> **结论速览**：新增 **16** 个类、修改 **57** 个类、删除 **0** 个类——纯增量改造，原版功能全部保留。

---

## 一、UI 重设计（肉眼可见的区别）

### 1.1 全新顶部操作栏（`MainFrame.buildTopBar()`，原版无此代码）

原版是传统 Swing 菜单栏 + 工具栏布局；定制版重构为单条顶栏：

**左侧操作卡片**（`RoundedPanel(20, 白底, 无边框)`，流式布局）——5 个大按钮常驻：

| 按钮 | 绑定动作 |
|------|----------|
| 启动/暂停/继续 | `jobPanel.startPauseResumeJobAction` |
| 单步 | `jobPanel.stepJobAction` |
| 停止 | `jobPanel.stopJobAction` |
| 启动/停止机器 | `machineControlsPanel.startStopMachineAction` |
| **重复贴片** | `jobPanel.repeatPlacementAction`（新增功能直达入口） |

按钮规格：图标上、文字下，11 pt 加粗，前景 `#333333`，无边框填充，72×48 px。

**中部导航按钮条**——9 个中文图标按钮，点击即切换对应页签（tab 索引 0~8）：

| 导航按钮 | 切换页签 | 图标 |
|----------|----------|------|
| 总览 | tab 0（**新增页**） | captureCamera |
| 任务 | tab 1 | start |
| 元件库 | tab 2 | footprintQuad |
| 封装库 | tab 3 | footprintBga |
| 视觉 | tab 4 | centerCamera |
| 飞达 | tab 5 | feeder |
| 机器配置 | tab 6 | driver |
| 问题 | tab 7 | errorAlert |
| 运行日志 | tab 8 | info |

按钮规格：64×48 px，未选中 `#5F5F5F`、选中 `#1F1F1F`（`NAV_IDLE` 常量控制高亮切换）。

**右上角**：原版菜单栏整体搬入顶栏（`setJMenuBar(null)` 后嵌入，去边框融入背景）。

### 1.2 卡片化视觉风格（Material Design 配色）

新增 `RoundedPanel` 组件，三块区域全部卡片化（8 px 圆角 + 白底 + `#DDDDDD` 细描边）：

| 卡片 | 内容 |
|------|------|
| 相机+说明卡片 | `panelCameraAndInstructions` |
| 机器控制卡片 | `MachineControlsPanel` |
| 页签卡片 | 所有功能页签 |

页面背景统一浅灰 `#E4E4E4`（`BG`），替代原版 Swing 默认平铺金属风。

### 1.3 新增「总览」仪表盘页（`OverviewPanel`，全新类，第一个页签）

- **贴装进度 + 实时速度双折线**：每秒采样一次，120 点滚动窗口，速度做指数平滑
- **完成率环形图**：绿 `#4CAF50` / 蓝 `#2196F3` / 红 `#F44336` 三态（标准 Material 色）
- **底部相机快照画廊**：1/2/3/4/6/8/9/16 分格下拉可选，环形缓冲保留 240 帧历史快照
- 统计基于 `placementsCompleted / placementsTotal`，定时器 1000 ms 刷新

### 1.4 `SmtezJobStyle` 统一样式类 + 表格筛选行

任务页的按钮、表格、分区标题（如「PCB」灰底标题栏 `#F7F7F7` + 底边线 `#DDDDDD`）
统一由该类重绘，形成一致的 SMT 操作台观感。色板：主绿 `#4CAF50`、主红 `#E50000` 系、
深灰 `#333333`。

**此外它还实现了新功能——表格筛选行**（`installFilterRow`）：在表格表头下插入一行
**每列一个输入框**，任意一列输入关键字即时过滤表格行（元件库、贴装列表等表格均适用），
原版无此功能。

---

## 二、新增功能（16 个新类）

### 2.0 新增类完整清单

| 类 | 归属功能 |
|----|----------|
| `machine.reference.ReferenceSimultaneousVision` | 同拍配置模型 |
| `machine.reference.vision.SimultaneousBottomVision` | 同拍对齐算法 |
| `machine.reference.wizards.SimultaneousVisionConfigurationWizard`（含 `MappingTableModel` 内部类） | 同拍配置界面（吸嘴↔相机映射表） |
| `gui.support.OneClickCalibration` | 一键校正 |
| `machine.reference.feeder.As2Feeder` | AS2 自动飞达 |
| `machine.reference.feeder.wizards.As2FeederConfigurationWizard` | AS2 配置界面 |
| `machine.reference.feeder.FoolproofFeeder` | 蝌蚪飞达 |
| `machine.reference.feeder.wizards.FoolproofFeederConfigurationWizard` | 蝌蚪飞达配置界面 |
| `gui.support.FeederNames` | 飞达类型中文名注册 |
| `model.IssueText` | 问题&解决方案翻译引擎 |
| `gui.OverviewPanel` | 总览仪表盘 |
| `gui.SmtezJobStyle` | SMT 界面样式 + 表格筛选行 |
| `vision.pipeline.CvStageNames` / `CvPropertyNames` | 视觉流水线 stage 中文名注册 |
| `machine.reference.ReferenceFlyCapture` + `wizards.FlyCaptureConfigurationWizard` | FlyCapture 老相机驱动（原版主线已删，基线较老保留） |

### 2.1 同拍功能配置项与算法细节

**配置项**（machine.xml `simultaneousVision` 节点）：

| 项 | 默认值 | 含义 |
|----|--------|------|
| `settleMode` | `FixedDelay` | 拍照稳定方式三档：`FixedDelay` 固定延时 / `PerCamera` 按相机 / `Code` 指令确认 |
| `settleDelayMs` | 250 ms | 固定延时模式的等待时间 |
| `captureTimeoutMs` | 3000 ms | 并行拍照超时 |
| `maxPositionError` | 0.5 mm | 组员几何容差（超出者不并入同组） |
| `fixedVisionHeight` | 0 mm | 强制统一拍照高度 |
| `fallbackToSequential` | true | 同拍失败自动回退逐件对准 |
| `mappings` | 空 | `NozzleCameraMapping`：吸嘴名 ↔ 相机名映射列表（XML 两个属性 `nozzle` / `camera`） |

**入组条件**（`selectGroup`，全部满足才并入同拍组）：
吸嘴已吸当前元件 · 与组内同 Head · 非旋转对齐模式（`isAligningRotationMode`）· 已装吸嘴尖 ·
元件高度已知 · 底视全局及该元件均已启用 · PreRotate 条件满足 ·
**该元件映射的相机未被组内占用**（一个相机一拍一个元件）。

**对齐流程**（`alignGroup`）：构建上下文 → 几何过滤 → 决定共享 Z 高度（统一拍照高度）
→ 定位全部轴 → 按稳定模式等待 → `parallelCapture` 并行拍照（关光/拍/开光逐台处理）
→ 逐件解算 `alignmentOffsets`；单件视觉失败记录告警后回退，不拖垮整批。

### 2.2 AS2 自动飞达协议（即插即用）

- 走 GcodeDriver 串口发指令 **`M600 N<飞达编号> F<进给格数>`**（`feederNumber` 默认 1、`feedCount` 默认 4）
- 首次使用时**自动创建**名为 `AS2` 的 GcodeDriver（确认正则 `^ok.*`、错误正则 `^error.*`）
  + `ReferenceActuator`（`ACTUATE_STRING_COMMAND = {StringValue}`），零手工配置
- 执行器先在吸嘴所在 Head 上找，找不到再到机器级找
- 可选 `moveBeforeFeed`：先移动吸嘴到拾取位再触发送料

### 2.3 蝌蚪飞达（FoolproofFeeder）

`feed()` 为**空操作**——零动作手动/外部送料型飞达，只提供拾取位置管理与防误触发
（支持 Normal / SkipNext 送料选项），适合料盘、托盘等不需要机器送料的场景。

### 2.4 底视识别模式（原版无此 UI）

`BottomVisionSettingsConfigurationWizard` 新增 `RecognitionMode` 六档选择：
**STANDARD（标准）/ LENGTH_WIDTH（长宽）/ POLARITY（极性）/ LARGE（大元件）/ NONE（不识别）/ CUSTOM（自定义）**。

### 2.5 「问题 & 解决方案」汉化引擎（`IssueText`，全新类）

原版该面板大量文案是运行时拼接的英文，无法用 properties 资源翻译。定制版的方案：

- 内置 **11 个词典文件**（`org/openpnp/model/issues_zh_CN/`），有效规则 **173 条**：

  | 词典 | 规则数 | 覆盖内容 |
  |------|--------|----------|
  | gcode.txt | 61 | GcodeDriver 配置界面（最大头） |
  | axis.txt | 35 | 轴/运动/齿隙补偿 |
  | camera.txt | 19 | 相机标定 |
  | vision.txt | 13 | 底视/上视 |
  | kinematic.txt | 10 | 运动学 |
  | actuator.txt | 9 | 执行器 |
  | calibration.txt | 9 | 标定 |
  | head.txt | 7 | 贴装头 |
  | misc.txt | 4 | 杂项 |
  | nozzletip.txt | 4 | 吸嘴尖 |
  | scripting.txt | 2 | 脚本 |

- 每行格式「英文原文 ⇥ 中文译文」；以 `~` 开头的行是**正则规则**，支持 `$1` 反向引用，
  如 `~^Calibrate backlash compensation for axis (.+)\.$` → `为轴 $1 标定齿隙补偿`
- 仅当系统语言为中文时激活（`Locale.getDefault()` 判断），先查精确映射、再用正则兜底，
  未命中文本原样返回
- 文本转义支持 `\n` / `\t`

此外 `CalibrationSolutions` 本身也有**实质逻辑改动**（非纯翻译，911 行 vs 原版 1327 行）：
新增「Speed factor control」标定速度调节、校准运动模式流程调整、新增 VisionSolution 等。

### 2.6 一键校正调用链（实现细节）

| 步骤 | 前置检查 | 调用 |
|------|----------|------|
| ① 主基准点+相机标定 | 主基准点位置已设置 | 移相机至基准点 → `VisionSolutions.autoCalibrateCamera`（自动标定）→ `centerInOnSubjectLocation`（居中）→ 回写基准点位置与直径 |
| ② 副基准点+三维标定 | 副基准点位置已设置 | 同上，但启用 3D 模式（相机高度标定） |
| ③ 吸嘴尖视觉校准 | 吸嘴尖已装载且启用视觉校准 | 逐嘴尖跑视觉校准，未装载自动跳过 |
| ④ 相机→吸嘴精确偏移 | 主基准点已设置、有可校准吸嘴 | 走 `CalibrationSolutions` 精确偏移流程 |
| ⑤ 皮带间隙校正 | 主基准点就绪 + 轴启用软限位 | 仅处理 X/Y 控制器轴且默认挂载件为**朝下相机**的轴 → `CalibrationSolutions.calibrateAxisBacklash` |

每步独立捕获异常，结果分「成功 / 跳过 / 失败」三色汇总展示，任一步失败不中断后续步骤。
执行前确认对话框列出全部五步，并检查机器已回零、默认贴装头/下视相机存在。

### 2.7 重复贴片与作业状态指令（实现细节）

**重复贴片**（`ReferencePnpJobProcessor.prepareRepeatLastPlacement`）：
优先取本次作业**最后贴装的那个元件**（`lastPlacedJobPlacement`）；若没有，则扫描所有板
找出**已标记贴装完成**的最后一个元件 → 重建只含该元件的作业队列 → 作为单件作业执行一遍。
要求作业处于停止状态（否则报「作业未停止，请先停止作业再重复贴片」）。

**作业状态指令触发点**（`ReferencePnpJobProcessor.step()`）：
- 作业正常完成（`currentStep == null`）→ `JOB_FINISHED_COMMAND`
- 任一步抛异常 → `JOB_ERROR_COMMAND`
- `sendJobStateGcode` **广播给所有 GcodeDriver**（多个驱动都会收到）
- 对青蛙贴片机：可在 Marlin 侧为这两条指令挂宏，实现贴完蜂鸣 / 报警灯带联动

### 2.8 总览仪表盘实现方式

图表全部为 **Graphics2D 手绘**（未引入 JFreeChart），`OverviewPanel` 内含 4 个内部类：
- `$ChartPanel`：双折线（完成率 % + 平滑速度），速度做指数平滑
  `smooth = 0.7×旧值 + 0.3×瞬时值`，每秒 `Timer` 推送一个采样点，120 点滚动窗口
- 环形图：`fillOval` 双圆叠加绘制，中央显示百分比
- `$SnapshotGallery` + `$ThumbTile`：底部相机快照缩略图墙（1~16 分格、240 帧环形缓冲）
- `$CardPanel`：卡片容器

### 2.9 同拍在作业流程中的挂载点

改在 `ReferencePnpJobProcessor` 的**对齐（align）环节**内挂载（`trySimultaneousAlign`）：

1. 对齐器必须是 `ReferenceBottomVision` 且机器为 `ReferenceMachine`、同拍配置已启用
2. 从剩余待对齐元件（Processing 状态、未完成、未同拍过）中选同拍组；
   **组不足 2 个 → 直接放弃，走原版单件对齐**
3. `alignGroup` 成功后把完成的元件记入 `simultaneousDone` 集合（防重复对齐），状态栏提示
   「Simultaneous align: N nozzles captured in one shot.」
4. 同拍整体异常只 `Logger.warn`，**自动落回**原版逐件对齐循环（含视觉重试），作业不中断

### 2.10 「单板文件浏览修复」的具体内容

原版 `viewerAction` 每次点开都新建一个 `PlacementsHolderLocationViewerDialog`，
反复开关会堆积多个窗口。定制版改为**单实例复用**：
窗口已存在则只更新数据并 `setExtendedState(0)` 恢复正常大小；窗口关闭时把
`jobViewer` 引用置空，下次重新创建。

### 2.11 拼板阵列即时刷新（实现细节）

`JobPanel` 新增阵列控件组：X/Y 数量、X/Y 间距、启用复选框。

- 每次输入触发 **350 ms 防抖定时器**（`arrayRebuildTimer`，不重复触发）后重建
- 用**签名字符串**（`arraySignature`）与 `appliedArraySignature` 比对，参数没变就不重复重建
- 生成的拼板副本以 `-arr` 标记位号（`ARRAY_ID_MARKER`），支持与原板区分
- `arrayParamsTouched` 记录用户是否动过参数（避免覆盖手动编辑）

### 2.12 导入贴片列表（实现细节）

`JobPlacementsPanel` 新增「导入贴片列表」按钮，走原版 `BoardImporter` 扩展机制：

1. 必须先在任务中选中一块单板（否则提示错误）
2. 选择导入器 → 弹文件对话框 → 解析出 `Board` 对象
3. 当前单板已有元件时弹三选项：**合并 / 替换 / 取消**（默认取消）
4. 「替换」先 `removeAllPlacements` 再导入；按 placement ID 去重合并

---

## 三、汉化（57 个原有类被修改）

### 3.1 视觉流水线 45 个 stage 全部汉化

流水线编辑器里 stage 名、参数名、参数描述全部中文（中文名注册在新增的
`CvStageNames` / `CvPropertyNames`）。完整名单（按中文字符密度排序，前 15）：

`DetectRectlinearSymmetry`(910) · `MaskHsv`(525) · `DetectCircularSymmetry`(501) ·
`SimpleOcr`(336) · `AffineWarp`(232) · `CreateFootprintTemplateImage`(182) ·
`ImageRead`(179) · `MinAreaRect`(175) · `FilterRects`(171) · `ReadPartTemplateImage`(149) ·
`DetectRectangleHough`(134) · `MatchTemplate`(123) · `DetectCirclesHough`(108) ·
`ThresholdAdaptive`(105) · `HistogramEqualizeAdaptive`(97)……

其余 30 个：BlurGaussian、BlurMedian、ClosestModel、ComposeResult、ConvertColor、
CreateModelTemplateImage、CreateShapeTemplateImage、DilateModel、DrawContours、
DrawEllipses、DrawImageCenter、DrawRotatedRects、AffineUnwarp、FilterContours、
DetectFixedCirclesHough、DetectLinesHough、HistogramEqualize、ImageCapture、
MaskCircle、MaskModel、MaskPolygon、MatchPartTemplate、MatchPartsTemplate、
OrientRotatedRects、ParameterBool、ParameterNumeric、SelectSingleRect、
SimpleBlobDetector、SizeCheck、WritePartTemplateImage。

### 3.2 核心 GUI / 机器类修改清单（12 个）

| 类 | 中文密度 | 改动内容 |
|----|----------|----------|
| `ReferenceBottomVision` | 117 | 新增识别模式枚举、与同拍联动、汉化 |
| `PartsPanel` | 91 | 元件库汉化 + 筛选行 |
| `JobPanel` | 83 | 拼板阵列、重复贴片、界面汉化 |
| `BottomVisionSettingsConfigurationWizard` | 55 | 识别模式选择界面 |
| `JobPlacementsPanel` | 49 | 导入贴片列表、汉化 |
| `MainFrame` | 24 | 顶栏重构、汉化 |
| `PlacementsHolderLocationsTableModel` | 19 | 任务板/拼板列表汉化 |
| `CameraPanel` | 17 | 相机视图汉化 |
| `StagesTableModel` | 8 | 流水线 stage 表格汉化 |
| `FiducialVisionSettingsConfigurationWizard` | 8 | 基准点视觉设置汉化 |
| `ReferenceMachine` | 6 | 挂载 `getSimultaneousVision()` |
| `MachineControlsPanel` | 6 | 机器控制汉化 |

### 3.3 翻译文件

`translations_zh_CN.properties` 从原版 1947 行增至 2017 行（**+71 行**），主要两类：
- **飞达类型中文名 21 条**（`Feeder.Type.*`）：编带飞达、托盘飞达、拖拽飞达、散料飞达、
  堆料飞达、拨杆飞达、推拉式飞达、旋转托盘飞达、多通道自动飞达、管装飞达、
  AS2 自动飞达、**蝌蚪飞达**、Bamboo 视觉飞达、百叶式飞达、Neoden4 飞达、Photon 飞达、
  Rapid 飞达、Schultz 飞达、Schultz 多通道飞达、高级散料飞达、自动飞达
- **GcodeDriver 指令类型中文 30+ 条**（`GcodeDriver.CommandType.*`）：连接指令、启用/禁用指令、
  回零指令、拾取/贴放指令、以及新指令「贴完后指令」「异常状态指令」等

### 3.4 汉化双轨策略

- **通用界面**：走 `translations_zh_CN.properties` 资源（原版机制，社区翻译+定制补充）
- **定制功能**：直接在新增类中硬编码中文字符串（同拍向导、一键校正、导入对话框等）
- **动态拼接文本**：走 `IssueText` 词典引擎（原版机制覆盖不了的第三轨）

---

## 四、其他

- **删除类 0 个**：原版功能零裁剪；图标/脚本/声音等资源文件与原版一致
  （仅 logo iconset 文件名略有差异）
- 配置目录独立为 `.lfpnp`（原版 `.openpnp2`），同机可与官方版共存；
  安装版与绿色版共用 `.lfpnp`，覆盖升级不丢配置
- 作业错误还支持 `Job.Error` 脚本钩子（`scriptJobError`），与状态指令互补

## 五、对青蛙贴片机的实际意义

1. **`JOB_FINISHED_COMMAND` / `JOB_ERROR_COMMAND`**：Marlin 侧挂宏 → 贴完蜂鸣、
   灯带变绿（正常）/ 变红（异常），主板 MOS 泵阀输出可联动
2. **一键校正**：新手免去看原版文档逐步标定，「先回零 → 点一键校正」即可完成全机标定
3. **同拍**：双吸嘴一次拍照对齐两颗料，贴装节奏显著加快
4. **AS2 `M600` 协议**：接第三方送料器只需串口，无需改 OpenPnP 配置

---

*本文档由 jar 反编译比对自动分析生成（CFR 0.152 + GitHub API 源码比对）。
类级结论 100% 确定；行数/中文密度为常量池统计值；个别实现细节以反编译代码为准。*
