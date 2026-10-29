# hongli pnp 源码重建方案

> 背景：2.6 深度定制版的源码工作副本已找不到（本机无 E 盘，报告所指
> `E:/Documents/openpnp-2.6` 不存在）。本方案基于 2026-10-27 的实测对比得出：
> **源码可以完整重建**。

## 一、实测结论（为什么能重建）

对比基准：上游 `github.com/openpnp/openpnp` tag `2.6`
（已浅克隆到 `C:/Users/hongliwang/Desktop/openpnp-2.6-src`）
对比对象：`honglipnp/OpenPnP/app/openpnp-gui-0.0.1-alpha-SNAPSHOT.jar`（v1.0 产物）

| 指标 | 数值 | 含义 |
| --- | --- | --- |
| jar 顶层类数 | 724 | |
| 上游 2.6 源码类数 | 708 | |
| 定制新增类 | **16**（见下） | 需反编译恢复 |
| 上游有 / jar 没有 | **0** | **无任何裁剪**，基线就是干净的 tag 2.6 |

**结论：产物 = 上游 2.6 + 16 个新增类 + 若干修改过的类 + 定制资源。**
上游没被改掉任何类，所以重建的起点是纯上游源码，不需要"找回"被覆盖的原版。

## 二、16 个定制新增类（全部要反编译恢复）

| 类 | 对应需求 |
| --- | --- |
| `gui/OverviewPanel` | R1.3 总览页 |
| `gui/SmtezJobStyle` | R1 仿 smtez 风格（类名直接坐实了这条需求） |
| `gui/support/FeederNames` | R2.3 飞达类型中文名 |
| `gui/support/OneClickCalibration` | R4.4 一键校正 |
| `machine/reference/ReferenceFlyCapture` | FlyCapture 相机支持 |
| `machine/reference/wizards/FlyCaptureConfigurationWizard` | ↑ 配置界面 |
| `machine/reference/ReferenceSimultaneousVision` | R6.1 同拍 |
| `machine/reference/vision/SimultaneousBottomVision` | R6.1 同拍底层实现 |
| `machine/reference/wizards/SimultaneousVisionConfigurationWizard` | R6 同拍配置界面 |
| `machine/reference/feeder/As2Feeder` | R7.1 AS2 自动飞达 |
| `machine/reference/feeder/wizards/As2FeederConfigurationWizard` | ↑ 配置界面 |
| `machine/reference/feeder/FoolproofFeeder` | R7.2 蝌蚪飞达 |
| `machine/reference/feeder/wizards/FoolproofFeederConfigurationWizard` | ↑ 配置界面 |
| `model/IssueText` | R2.2 问题条目级翻译 |
| `vision/pipeline/CvPropertyNames` | R2.3 流水线中文化 |
| `vision/pipeline/CvStageNames` | R2.3 流水线中文化 |

另有一批**修改过的类**（约 57 个，明细见
`docs/software/OpenPnP定制版与原版差异.md`），需要逐个反编译后与上游 diff。

## 三、重建步骤

1. **反编译恢复新增类**：用 Vineflower（或 CFR）反编译 v1.0 jar 中上述 16 个类，
   人工校对后放回上游源码树对应包路径。反编译产物注释会丢失，需按
   《hongli-pnp-需求规格》和交互规格补注释。
2. **恢复修改过的类**：对差异文档列出的修改类，反编译 → 与上游源码 diff →
   把差异以补丁形式重放。**优先做 GUI 包**（MainFrame / JobPanel / JogControlsPanel
   等承载了 R1 / R4 / R5 的大部分改动）。
3. **资源文件直接从 jar 提取（无需反编译，是原样拷贝）**：
   - `org/openpnp/model/issues_zh_CN/` 11 个 txt（R2.2）
   - `org/openpnp/translations_zh_CN.properties`（R2.3）
   - 图标、配置模板等
4. **实现 R1.5 ThickSliderUI**：全新代码，按
   `docs/ThickSliderUI-交互规格.html` 编写，不依赖反编译。
5. **构建验证**：`mvn package` 后与 v1.0 jar 逐类比对（类清单应一致 +
   新增 ThickSliderUI），再走 jpackage + WiX 出安装包（R9）。

## 四、风险

- 反编译的修改类可能与上游 2.6 有编译不兼容的细节（泛型、内部类命名），
  需要逐个修复
- v1.0 产物构建于哪个上游 commit 无法精确考证（pom 只写了
  `0.0.1-alpha-SNAPSHOT`），以 tag 2.6 为基线最合理——类级对比 0 缺失支持这一判断
- 若曾有人手改过上游类后未记录，反编译 diff 能兜底发现

## 五、可直接复用的资产

| 资产 | 位置 | 用途 |
| --- | --- | --- |
| 上游 2.6 源码 | `C:/Users/hongliwang/Desktop/openpnp-2.6-src` | 重建基线 |
| v1.0 产物 jar | `honglipnp/OpenPnP/app/*.jar` | 反编译源 |
| 类级差异文档 | `docs/software/OpenPnP定制版与原版差异.md` | 修改类清单（16 新增 / 57 修改） |
| 需求规格 | `docs/hongli-pnp-需求规格.md` | 验收标准 |
| ThickSliderUI 规格 | `docs/ThickSliderUI-交互规格.html` | R1.5 直接照做 |
| 自带 JRE | `honglipnp/OpenPnP/runtime/bin/java.exe` | 反编译器运行环境 |
