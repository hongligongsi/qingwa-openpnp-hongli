# OpenPnP 定制版（lfpnp_v1.0）与原版差异详解

> 分析对象：`lfpnp_v1.0/OpenPnP/app/openpnp-gui-0.0.1-alpha-SNAPSHOT.jar`（2026-10-23 构建，Maven + JDK 17）
> 对比基线：GitHub `openpnp/openpnp` 主线源码
> 方法：解包 jar 反编译（CFR）逐文件 diff + class 常量池扫描 + 原版源码逐行比对
>
> 结论速览：**新增 16 个类、修改 57 个类、删除 0 个类**——纯增量改造，原版功能全部保留。

---

## 一、UI 重设计（肉眼可见的区别）

### 1. 全新顶部操作栏（`MainFrame.buildTopBar()`，原版无此代码）

原版是传统 Swing 菜单栏 + 工具栏布局；定制版改为：

- **左侧圆角操作卡片**：5 个大按钮常驻顶栏——启动/暂停/继续、单步、停止、启停机器、**重复贴片**
- **中部导航按钮条**：9 个中文图标按钮，一键切换页签——
  总览 / 任务 / 元件库 / 封装库 / 视觉 / 飞达 / 机器配置 / 问题 / 运行日志
- 菜单栏保留但移到顶栏右上角（去边框融入背景）

### 2. 卡片化视觉风格

新增 `RoundedPanel` 组件：相机区、机器控制区、页签区全部套上 **8px 圆角白色卡片 + 细描边**，
页面用浅灰底色，替代原版 Swing 默认平铺风格。

### 3. 新增「总览」仪表盘页（`OverviewPanel`，全新类，第一个页签）

- 贴装进度（完成 / 总数）与实时速度曲线（120 点平滑，每秒刷新）
- 完成率环形图（绿/蓝/红三态）
- **底部相机快照画廊**：可选 1/2/3/4/6/8/9/16 分格，保留 240 帧历史快照

### 4. `SmtezJobStyle` 统一样式类

任务页按钮、表格、分区标题（如「PCB」）统一重绘，形成一致的 SMT 操作台观感。

---

## 二、新增功能（16 个新类）

| 功能 | 实现 | 说明 |
|------|------|------|
| **同拍（并行底视）** | `ReferenceSimultaneousVision` + `SimultaneousBottomVision` + 配置向导 | 选组 → 几何过滤 → 共享 Z 高度 → **双相机并行拍照** → 逐件解算偏移；单件视觉失败自动回退为逐个对准，不中断整批 |
| **一键校正** | `OneClickCalibration`（⚠️ 安装说明未提及） | 五连标定一条龙：主基准点+相机位置/旋转 → 副基准点+三维标定 → 吸嘴尖视觉校准 → 相机→吸嘴精确偏移 → 皮带间隙校正；执行前自动检查回零/前置标定，完成后弹出成功/跳过/失败汇总 |
| **拼板阵列即时刷新** | `JobPanel` 新增阵列区 | 输入 X/Y 数量与间距 → 防抖定时器**即时**生成带 `-arr` 标记的拼板副本并刷新任务（原版需手动复制单板再改位号） |
| **导入贴片列表** | `JobPlacementsPanel` 新按钮 | 从贴片文件把元件列表导入当前单板；已有元件时询问**追加 / 覆盖 / 取消** |
| **重复贴片** | `repeatPlacementAction` + 顶栏按钮 | 重新取料并贴装上一次贴装的元件（补贴场景） |
| **贴完后 / 异常指令** | `GcodeDriver.CommandType` 新增 3 枚举 | `JOB_FINISHED_COMMAND`（贴完后）、`JOB_ERROR_COMMAND`（异常状态）、`REPEAT_PLACEMENT_COMMAND`（重复贴片前）——贴片机可向固件发完成/报警信号（如青蛙贴片机蜂鸣、灯带联动） |
| **新飞达类型** | `As2Feeder`（AS2 自动飞达）、`FoolproofFeeder`（**蝌蚪飞达**）+ 各自向导 + `FeederNames` 注册 | 扩展支持第三方送料器 |
| **FlyCapture 驱动保留** | `ReferenceFlyCapture` + 向导 | 原版主线已删除的老式 FireWire 相机驱动，此版本保留（说明基线为较早的原版快照） |

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
| `mappings` | 空 | `NozzleCameraMapping`：吸嘴名 ↔ 相机名映射列表 |

**入组条件**（`selectGroup`，全部满足才并入同拍组）：
吸嘴已吸当前元件 · 与组内同 Head · 非旋转对齐模式 · 已装吸嘴尖 · 元件高度已知 ·
底视全局及该元件均已启用 · PreRotate 条件满足 · **该元件映射的相机未被组内占用**（一个相机一拍一个元件）。

### 2.2 AS2 自动飞达协议（即插即用）

- 走 GcodeDriver 串口发指令 **`M600 N<飞达编号> F<进给格数>`**（feedCount 默认 4）
- 首次使用时**自动创建**名为 `AS2` 的 GcodeDriver + ReferenceActuator
  （`ACTUATE_STRING_COMMAND = {StringValue}`），零手工配置
- 可选 `moveBeforeFeed`：先移动吸嘴到拾取位再触发送料

### 2.3 蝌蚪飞达（FoolproofFeeder）

`feed()` 为**空操作**——零动作手动/外部送料型飞达，只提供拾取位置管理与防误触发，
适合料盘、托盘等不需要机器送料的场景。

### 2.4 底视识别模式（原版无此 UI）

`BottomVisionSettingsConfigurationWizard` 新增 `RecognitionMode` 六档选择：
**STANDARD / LENGTH_WIDTH（长宽）/ POLARITY（极性）/ LARGE（大元件）/ NONE / CUSTOM（自定义）**。

### 2.5 「问题 & 解决方案」汉化引擎（`IssueText`，全新类）

原版该面板大量文案是运行时拼接的英文，无法用 properties 资源翻译。定制版的方案：

- 内置 **11 个词典文件**（`issues_zh_CN/` 下 axis / gcode / calibration / camera / head /
  kinematic / nozzletip / actuator / vision / scripting / misc，共 **225 条规则**）
- 每行格式「英文原文 ⇥ 中文译文」；以 `~` 开头的行是**正则规则**，支持 `$1` 反向引用，
  如 `~^Calibrate backlash compensation for axis (.+)\.$` → `为轴 $1 标定齿隙补偿`
- 仅当系统语言为中文时激活，先查精确映射、再用正则兜底，未命中文本原样返回

此外 `CalibrationSolutions` 本身也有**实质逻辑改动**（非纯翻译）：新增「Speed factor control」
标定速度调节、校准运动模式流程调整等。

---

## 三、汉化（57 个原有类被修改）

1. **视觉流水线约 45 个 stage 全部汉化**：MatchTemplate、ThresholdAdaptive、DetectCirclesHough、
   SimpleOcr、MaskHsv 等——流水线编辑器里 stage 名、参数描述全部中文
   （中文名注册在新增的 `CvStageNames` / `CvPropertyNames`）
2. **核心 GUI 汉化 + 功能修改**：`JobPanel`、`JobPlacementsPanel`、`PartsPanel`、`MainFrame`、
   `CameraPanel`、`MachineControlsPanel`
3. **底视对齐改造**：`ReferenceBottomVision` 新增识别模式（`RecognitionMode`），与同拍功能联动
4. **翻译文件**：`translations_zh_CN.properties` 从原版 1947 行增至 2017 行（+71 行：
   飞达类型中文名、GcodeDriver 指令类型中文名等）
5. **问题 & 解决方案面板**：`IssueText` + `CalibrationSolutions$1` 承载中文文案

---

## 四、其他

- **删除类 0 个**：原版功能零裁剪；图标/脚本/声音等资源文件与原版一致
- 配置目录独立为 `.lfpnp`（原版 `.openpnp2`），同机可与官方版共存
- 汉化策略为「资源文件 + 硬编码」双轨：通用界面走 translations 资源，定制功能直接硬编码中文

*本文档由 jar 反编译比对自动分析生成，类级结论 100% 确定，个别实现细节以反编译代码为准。*
