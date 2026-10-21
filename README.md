<p align="center">
  
  <b>🐸 青蛙贴片机 固件 · qingwa-pnp-marlin</b>  

  
  基于 Marlin 2.1.x + Opulo LumenPnP REV5 主板的贴片机专用固件
  
</p>

<p align="center">
  
  <a href="LICENSE"><img src="https://img.shields.io/badge/Code-GPL--3.0-blue.svg" alt="Code: GPL-3.0"></a>
  
  <a href="#-致谢与许可证"><img src="https://img.shields.io/badge/HW-CERN--OHL--W%202.0-green.svg" alt="Hardware: CERN-OHL-W 2.0"></a>
  
  <a href="#-致谢与许可证"><img src="https://img.shields.io/badge/Docs-CC%20BY--SA%204.0-blueviolet.svg" alt="Docs: CC BY-SA 4.0"></a>
  
  <img src="https://img.shields.io/badge/Marlin-2.1.x-important.svg" alt="Marlin 2.1.x">
  
  <img src="https://img.shields.io/badge/Board-LumenPnP%20REV5-success.svg" alt="LumenPnP REV5">
  
  <img src="https://img.shields.io/badge/MCU-STM32F407VET6-informational.svg" alt="STM32F407VET6">
  
  <img src="https://img.shields.io/badge/Build-PlatformIO-orange.svg" alt="PlatformIO">
  
</p>

<p align="center"><strong>简体中文</strong> | <a href="README.en.md">English</a></p>

---

## 目录

- [📖 项目简介](#-项目简介)
- [🧩 系统架构：一套源码，两种固件](#-系统架构一套源码两种固件)
- [✨ 功能特性](#-功能特性)
- [🧱 硬件与引脚](#-硬件与引脚)
- [🏗 目录结构](#-目录结构)
- [🚀 快速上手](#-快速上手)
- [⚙️ 构建与烧录](#-构建与烧录)
- [🔧 配置修改与版本管理](#-配置修改与版本管理)
- [🧰 常用 G 代码](#-常用-g-代码)
- [🎛 常用调整速查：速度 / 电流 / 灯亮度](#-常用调整速查速度--电流--灯亮度)
- [🛠 常见问题](#-常见问题)
- [🤝 致谢与许可证](#-致谢与许可证)

---

## 📖 项目简介

本项目是 **「青蛙贴片机」专用固件**。它并非 3D 打印机固件，而是把一个通用开源固件
  
**Marlin** 改造为 **SMT 贴片机（Pick-and-Place）的运动控制器固件**。

### 这台机器由什么组成？

一台完整的青蛙贴片机包含两大部分，**各自运行一套独立但同源的固件**：

1. **主板（Motherboard）** —— 机器的"大脑 + 四肢"。
     
   基于 **Opulo LumenPnP Motherboard REV05**（MCU：STMicroelectronics
     
   **STM32F407VET6**，ARM Cortex-M4，512 KB Flash / 192 KB SRAM），
     
   负责机头的 X/Y 定位、Z 轴升降、双电机同步（X/Y2）、限位检测、
     
   相机/光源/真空等外设控制。它就是本仓库的**默认构建目标**。
2. **飞达（Feeder，电动送料器）** —— 负责把元件编带按格推进到取料位。
     
   每台飞达内部有一块 **Opulo 飞达主控板（REV3 或 REV4）**，同样运行 Marlin，
     
   用旋转轴驱动拨爪轮完成送带动作。飞达固件用本仓库里的
     
   `rev*-feeder-config` 配置快照构建（详见下文教程）。

固件通过 USB 串口接收 G 代码 / 状态查询，可与 OpenPnP 等上位机软件配合完成
  
自动贴装流程。上位机把**主板和每 这个台飞达视为独立的串口设备**分别下发指令。

> 该仓库从上游 **Marlin 2.1.x** 与 **Opulo LumenPnP** 开源硬件/软件生态定制而来，
>   
> 保留了 Marlin 强大的运动规划与 HAL 分层结构，并加入了 Opulo 主板定义与多版本配置。

### 主板固件裁掉了什么？

为达到"纯运动控制"目标，本固件在配置层面移除了 3D 打印相关逻辑：

| 项目          | 本固件                               |
| ----------- | --------------------------------- |
| `EXTRUDERS` | `0`（无挤出机）                         |
| 温度传感器       | 全部关闭（无加热/热床/风扇温控）                 |
| 轴定义         | X / Y / Y2 / Z / I / J 六路步进       |
| 驱动类型        | 全部 TMC2209（单线 UART）               |
| 串口          | USB CDC（`SERIAL_PORT -1`）@ 250000 |

---

## 🧩 系统架构：一套源码，两种固件

本仓库**只维护一份 Marlin 源码**，主板固件和飞达固件都从它构建——
  
两者唯一的区别是编译时套用的**配置文件**（`Configuration.h` /
  
`Configuration_adv.h`）和**构建环境（env）**&#x4E0D;同：

```
                        ┌──────────────────────────────┐
                        │   上位机 OpenPnP / 手动 G 代码  │
                        └──────┬───────────────┬───────┘
                     USB 串口   │               │   USB 串口（每台飞达一个口）
                               ▼               ▼
                    ┌─────────────────┐   ┌─────────────────┐
                    │  主板固件        │   │  飞达固件 ×N      │
                    │  REV5 主控       │   │  REV3/REV4 主控  │
                    │  env: REV5      │   │  env: REV3/REV4 │
                    │  配置: Marlin/根 │   │  配置: rev*-feeder-config/ │
                    ├─────────────────┤   ├─────────────────┤
                    │ · X/Y/Y2 机头定位│   │ · 旋转轴驱动拨爪轮│
                    │ · Z 轴升降       │   │ · 送带/退带      │
                    │ · 限位/DIAG 检测 │   │ · EXTRUDERS 0   │
                    │ · 相机/灯带/真空 │   │   （无加热）     │
                    └─────────────────┘   └─────────────────┘
```

**两种固件怎么选？**

| 你要刷的目标         | 用哪个 env                             | 用哪套配置                                 |
| -------------- | ----------------------------------- | ------------------------------------- |
| 贴片机主板（REV05）   | `Opulo_Lumen_REV5`（默认，直接 `pio run`） | `Marlin/` 根目录（无需任何操作）                 |
| 飞达（REV4 主控）    | `Opulo_Lumen_REV4`                  | `rev4-v3.0 / v3.1 / v3.1-pwm-aux` 三选一 |
| 飞达（REV3 主控，旧款） | `Opulo_Lumen_REV3`                  | `rev3-feeder-config`                  |

飞达配置四选一的依据（看飞达硬件版本和需求）：

- `rev4-v3.0-feeder-config`：v3.0 硬件，送带速度较保守（200 mm/s）；
- `rev4-v3.1-feeder-config`：v3.1 硬件，送带速度提升到 1000 mm/s；
- `rev4-v3.1-feeder-pwm-aux-config`：同 v3.1，额外开启 `FAST_PWM_FAN`
    
  （AUX 风扇 31.4 kHz 高频驱动，消除啸叫）；
- `rev3-feeder-config`：REV3 主控旧款飞达（与 REV4 系列引脚/功能差异较大）。

---

## ✨ 功能特性

- **六轴独立步进**：X / Y / Y2 / Z / I / J 各轴独立 STEP/DIR/EN 引脚与单线 TMC UART
    
  回读（软串口 19200 baud），全轴 **TMC2209**。
- **失速 / 堵转检测信号（DIAG）**：六轴 DIAG 引脚直接引出，可接入上位机做堵转判断。
- **纯运动 / IO 控制器**：`EXTRUDERS 0`、全部温度传感器关闭，3D 打印热管理路径被裁掉，
    
  中断与定时器资源优先保证运动控制。
- **完善的板载外设定义**：
  - X / Y / Z 三路限位开关
  - 4 路风扇 / 驱动输出（`FAN0`–`FAN3`）、蜂鸣器
  - 双路 **NeoPixel** RGB 灯带（`PC7` / `PC8`）
  - 8 脚 **AUX** 扩展口：3×PWM + 1×模拟输入 + I²C（SCL/SDA）
  - **RS485** 收发使能脚（用于外部送料器 / 通讯板）
  - 4 个 ID 引脚（`PD0`–`PD3`），支持硬件版本识别
- **参数存储**：板级预留 SRAM EEPROM 仿真（8 KB），但 `EEPROM_SETTINGS`
  默认**未启用**，`M500` 不生效——详见「常用 G 代码 → 参数保存」。
- **G 代码兼容**：完整保留 Marlin 的 G/M 命令体系与快速解析器。
- **多硬件版本配置快照**：REV3 / REV4 + 各代送料器（v3.0 / v3.1 / PWM-AUX）配置保留，
    
  便于对照、回归与硬件升级。
- **继承 Marlin 2.1 生态**：HAL 分层（本仓库重点使用 STM32 HAL）、PlatformIO 一键构建、
    
  官方 CI 工作流、Auto Build 脚本。

---

## 🧱 硬件与引脚

### 主板信息

| 项            | 值                                      |
| ------------ | -------------------------------------- |
| 固件上报主板名      | `LumenPnP Motherboard REV05`           |
| 固件上报机器名      | `LumenPnP`                             |
| MCU          | STM32F407VET6（ARM Cortex-M4 @ 168 MHz） |
| Flash / SRAM | 512 KB / 192 KB                        |
| 驱动接口         | 6 × TMC2209（单线 UART 回读）                |

### 完整引脚表（来自 `Marlin/src/pins/stm32f4/pins_OPULO_LUMEN_REV5.h`）

所有引脚都在这一份头文件里定义，"当前状态"指本固件配置下是否实际启用。

**① 步进电机（6 路 TMC2209，单线 UART）**

| 轴 | STEP | DIR | ENABLE | UART（TX=RX） | DIAG | 状态 |
|----|------|-----|--------|---------------|------|------|
| X | `PB15` | `PB14` | `PD9` | `PD8` | `PB10` | 启用 |
| Y | `PE15` | `PE14` | `PB13` | `PB12` | `PB11` | 启用 |
| Y2 | `PD6` | `PD7` | `PA3` | `PA2` | `PC12` | 启用（双 Y 同步） |
| Z | `PE7` | `PB1` | `PE9` | `PE8` | `PB5` | 启用 |
| A（I 轴） | `PC4` | `PA4` | `PB0` | `PC5` | `PC10` | 启用（旋转） |
| B（J 轴） | `PE11` | `PE10` | `PE13` | `PE12` | `PC11` | 启用（旋转） |

UART 为**单线半双工**：TX 与 RX 定义成同一引脚，靠 TMC2209 的 PDN_UART 通讯，
波特率固定 `19200`（降低速率换可靠性）。注意 Y2 是**实际启用**的
（`Configuration.h` 中 `Y2_DRIVER_TYPE TMC2209`），所以整机是 6 个电机而非 5 个。

**② 限位开关与归位方式**

| 轴 | 引脚 | 说明 |
|----|------|------|
| X 最小端 | `PC6` | 实体限位开关 |
| Y 最小端 | `PD15` | 实体限位开关 |
| Z 最小端 | `PD14` | 实体限位开关 |

`SENSORLESS_HOMING`（无传感器归位）当前为关闭状态，因此 DIAG 引脚虽已接线，
归位仍走实体开关。想启用需打开该宏并调整 `X/Y_STALL_SENSITIVITY`。

**③ 风扇 / 蜂鸣器 / 灯带**

| 功能 | 引脚 | 状态 |
|------|------|------|
| FAN0（`M106 P0`） | `PB8` | 启用（`FAN_COUNT` = 4） |
| FAN1（`M106 P1`） | `PB9` | 启用 |
| FAN2（`M106 P2`） | `PE5` | 启用 |
| FAN3（`M106 P3`） | `PE6` | 启用 |
| 控制器风扇（自动） | `PE2` | 启用，任一电机使能即转 |
| 蜂鸣器 | `PA7` | 启用（`SPEAKER`） |
| NeoPixel 灯带 | `PC7` | 启用，18 颗，`NEO_GRB` |
| 第二路 NeoPixel | `PC8` | 启用，18 颗；`M150 S1 ...` 可单独控制 |

**④ 总线接口**

| 总线 | 引脚 | 用途 |
|------|------|------|
| SPI | MISO `PB4` / MOSI `PB5` / SCK `PB3` | 备用 TMC SPI 模式（本板走 UART，未使用） |
| I²C | SDA `PB7` / SCL `PB6` | 接 I²C 外设，同时引到 AUX 口 |
| RS485 | 发送使能 `PD11` / 接收使能 `PD12` | 飞达等外设通信 |

> ⚠️ `PB5` 被复用为 `Z_DIAG_PIN` 与 `MOSI_PIN`。本板 TMC 走 UART 不用 SPI，
> 因此不冲突；若要外接 SPI 设备，Z 轴的无传感器归位需另择引脚。

**⑤ 板级识别与系统引脚**

| 功能 | 引脚 | 说明 |
|------|------|------|
| 板版本 ID | `PD0` / `PD1` / `PD2` / `PD3` | 需先设输入上拉再读（文件末尾有 `M42`/`M43` 示例） |
| 通用 IO（AUX 控制） | `PD13` | 可写可读 |
| USB | `PA11` / `PA12` | 芯片固定，虚拟串口 |
| SWD 调试 | `PA13` / `PA14` | ST-Link 烧录 / 调试 |
| EEPROM | 无外置芯片 | SRAM 模拟，8 KB（`MARLIN_EEPROM_SIZE 0x2000`，但 `EEPROM_SETTINGS` 未启用） |

**⑥ 尚未分配的引脚**

`PA0`、`PA1`、`PA8`–`PA10`、`PB2`（BOOT1）、`PC1`–`PC3`、`PC9`、
`PC13`–`PC15`、`PD4`、`PD5`、`PD10`、`PE0`、`PE1`、`PE3`、`PE4`
在引脚文件中均未被占用，二次开发（增加传感器、气缸电磁阀等）可从这些里挑选。

### 运动学与行程参数（来自 `Marlin/Configuration.h`）

| 参数        | 值                                     | 说明                                   |
| --------- | ------------------------------------- | ------------------------------------ |
| 步进精度      | `320, 320, 40, 4.44, 4.44` 步/mm       | X / Y / Z / I / J                    |
| X 行程      | 0 – 433 mm                            | 归位到最小端（`X_HOME_DIR -1`）              |
| Y 行程      | 0 – 487 mm                            | 归位到最小端                               |
| Z 行程      | 0 – 63 mm                             | 归位到最小端，归位后抬到 21 mm（`Z_AFTER_HOMING`） |
| I / J 行程  | 0 – 720（旋转量，单位度）                      | 不参与归位（`I/J_HOME_DIR 0`）              |
| 默认速度      | `7000, 7000, 1000, 50000, 50000` mm/s | X / Y / Z / I / J                    |
| X/Y/Y2 联动 | X + Y + Y2 双电机同步                      | 龙门结构，Y2 跟随 Y                         |

> I / J 为**旋转轴**（配置中 `AXIS4_ROTATES` / `AXIS5_ROTATES`），
>   
> 在 G 代码中分别用字母 **`A`** / **`B`** 引用，范围 0–720°（约两圈）；
>   
> 可用 `M114` 查询位置、`G1 A90` 试转。Y2 是 Y 的第二路驱动（TMC2209 独立
>   
> STEP/DIR/EN），用于龙门双电机同步。

### 与 OpenPnP 上位机对接要点

- **接口**：USB CDC 虚拟串口（`SERIAL_PORT -1`），无需波特率匹配但对齐
    
  `250000` 亦可；
- **识别**：连接后发送 `M115`，应回报机器名 `LumenPnP` 与固件版本；
- **运动指令**：标准 `G0/G1` + `G28` 归位 + `M119` 限位查询，
    
  完整兼容 Marlin 命令集；
- **参数保存**：⚠️ 本固件**未启用 `EEPROM_SETTINGS`**，`M500` 会回
  `EEPROM disabled`，`M92` / `M906` 等运行时改动只在本次上电生效，重启即回到
  编译值。需要掉电保存请打开 `Configuration.h` 的 `EEPROM_SETTINGS` 后重新编译
  （板级已定义 `SRAM_EEPROM_EMULATION` 与 8 KB 空间，可直接启用）；
- 每台飞达在上位机中是**独立串口设备**（各自刷飞达固件）。

### REV05 AUX 扩展口（8 脚）

```
             _________
      3.3V  |  1   2  |  GND
    PWM1 PA5|  3   4  | PC0 A1 (模拟输入)
    PWM2 PA6|  5   6  | SCL
    PWM3 PA15| 7   8  | SDA
             ---------
```

---

## 🏗 目录结构

本仓库包含**两套固件程序**，共用同一份 Marlin 源码，靠「配置文件 + 构建环境（env）」区分：

| 程序           | 目标硬件                             | 主控芯片          | 构建 env                 | 配置来源                                  |
| ------------ | -------------------------------- | ------------- | ---------------------- | ------------------------------------- |
| **主板固件**     | LumenPnP Motherboard REV5（贴片机主板） | STM32F407VET6 | `Opulo_Lumen_REV5`（默认） | `Marlin/` 根目录激活配置（快照见 `rev5-config/`） |
| **飞达固件**     | 电动送料器（Feeder）REV4 主控             | STM32F407VET6 | `Opulo_Lumen_REV4`     | `Marlin/rev4-*-feeder-config/` 三选一    |
| **飞达固件（旧款）** | 电动送料器（Feeder）REV3 主控             | STM32F407VET6 | `Opulo_Lumen_REV3`     | `Marlin/rev3-feeder-config/`          |

三块板的板级定义（引脚 / 时钟 / 上传协议）分别在
  
`buildroot/share/PlatformIO/boards/marlin_opulo_lumen_rev{3,4,5}.json`，
  
引脚定义在 `Marlin/src/pins/stm32f4/pins_OPULO_LUMEN_REV{3,4,5}.h`。

```text
qingwa-pnp-marlin/
├── .devcontainer/              # VS Code 开发容器（构建环境一键起）
├── .github/                    # GitHub CI / 社区配置（test-builds 等工作流）
├── .trellis/                   # AI 辅助开发工作流脚手架（可选）
├── .workbuddy/                 # AI 协作工作日志与项目记忆（不参与构建）
├── .openpnp2/                  # OpenPnP 上位机配置（随仓库走，23 个文件）
│   ├── machine.xml             #   机器配置：轴 / 相机 / 吸嘴 / 驱动 / 光照
│   ├── parts.xml  packages.xml #   元件库与封装定义
│   ├── boards.xml  panels.xml  #   板卡与拼板定义
│   ├── vision-settings.xml     #   视觉识别参数
│   └── scripts/                #   OpenPnP 脚本示例（JavaScript / Python）
│                               #   log / backups / snapshots 已被 .gitignore 排除
├── Marlin/                     # ⭐ 固件源码与配置（核心，两套程序共用）
│   ├── Configuration.h         #   当前激活配置 = 主板 REV5
│   ├── Configuration_adv.h     #   进阶配置
│   ├── config.ini              #   Marlin 编译期配置（ini 语法，默认未启用）
│   ├── Makefile                #   供 pio/arduino 的 make 入口
│   ├── Version.h               #   版本字符串（构建期覆盖用）
│   │
│   │   ── 主板（Motherboard）配置 ──
│   ├── rev5-config/            #   REV5 主板配置快照（与激活配置对照/归档）
│   │
│   │   ── 飞达（Feeder）配置，四选一 ──
│   ├── rev3-feeder-config/     #   飞达 REV3 主控（旧款送料器）
│   ├── rev4-v3.0-feeder-config/#   飞达 REV4 主控 + 送料器 v3.0（慢速参数）
│   ├── rev4-v3.1-feeder-config/#   飞达 REV4 主控 + 送料器 v3.1（快速参数）
│   ├── rev4-v3.1-feeder-pwm-aux-config/  # 同 v3.1，另开 FAST_PWM_FAN（AUX 风扇 31.4 kHz）
│   │
│   └── src/                    #   Marlin 核心源码（两套程序共用，不区分板型）
│       ├── MarlinCore.cpp|.h   #     固件入口
│       ├── HAL/                #     硬件抽象层（STM32 等）
│       ├── core/               #     boards.h 主板编号 / 宏
│       ├── pins/               #     各板引脚定义
│       │   └── stm32f4/pins_OPULO_LUMEN_REV5.h   # ← REV5 引脚（另有 REV3/REV4）
│       ├── module/             #     planner / stepper / endstop …
│       ├── gcode/              #     G/M 代码解析与执行
│       ├── feature/ libs/ lcd/ sd/ inc/ tests/
├── buildroot/                  # PlatformIO 板级支持 / 脚本 / 测试
│   ├── share/PlatformIO/
│   │   ├── boards/             #   板级 JSON：marlin_opulo_lumen_rev3/4/5.json
│   │   └── scripts/            #   configuration.py 等构建脚本
│   ├── scripts/                #   ⭐ 配置校验工具（改完 Configuration*.h 必跑）
│   │   ├── check-config-i18n.py          # 注释结构 + schema（2444 项基线）比对
│   │   ├── check-config-code-intact.py   # ARM 预处理输出比对，证明功能等价
│   │   ├── config-schema-baseline.json   # schema 基线快照
│   │   └── README-config-i18n.md         # 两个脚本的用法说明
│   ├── share/vscode/auto_build.py                #   Auto Build（PIO Build）
│   └── tests/                  #   make tests-all-local 等自动化测试
├── config/  docker/  docs/     # 文档 / Docker / dev 文档（Bresenham、Serial…）
├── ini/                        # PlatformIO 环境矩阵（按芯片分类）
│   └── stm32f4.ini             #   内含 [env:Opulo_Lumen_REV3] / REV4 / REV5
├── .editorconfig  .gitattributes
├── platformio.ini              # ⭐ PlatformIO 工程入口（default_envs = Opulo_Lumen_REV5）
├── Makefile                    # make 快捷入口
├── marlin.code-workspace       # VS Code 多根工作区
├── process-palette.json        # VS Code「Process Palette」→ PIO Build 命令定义
├── LICENSE                     # 代码 GPL-3.0；硬件/文档许可见「致谢与许可证」
├── m300_editor/                # 🎵 网页版 M300 蜂鸣器旋律编辑器（含教程与截图）
└── README.md / README.en.md    # 多语言说明（中文默认）
```

### 两套程序的配置差异要点

- **主板固件（REV5）**：驱动贴片机的 X/Y 运动轴、限位、相机/光源接口等，
    
  是本仓库的默认构建目标。
- **飞达固件（REV3/REV4）**：`EXTRUDERS 0`（无挤出/热端），
    
  并将 `AXIS4/AXIS5/AXIS6` 声明为**旋转轴**（`AXISn_ROTATES`），
    
  用于驱动送料拨爪轮；送带速度参数因硬件代次而不同。
- 四套飞达配置之间的实质差异很小：
  - `rev4-v3.0` vs `rev4-v3.1`：仅送带速度参数
      
    （`DEFAULT_MAX_FEEDRATE` 200→1000 mm/s、`HOMING_FEEDRATE` 100→200 mm/min）；
  - `rev4-v3.1-pwm-aux` vs `rev4-v3.1`：仅多开 `FAST_PWM_FAN`
      
    （`FAST_PWM_FAN_FREQUENCY 31400`，AUX 风扇高频静音）；
  - `rev3` 与 `rev4` 系列差异较大（不同主控代次，引脚与功能集不同）。



---

## 🚀 快速上手

从零开始把一台贴片机主板跑起来，只需 5 步（约 15 分钟，首次编译除外）：

### 第 1 步：安装构建环境

1. 安装 [VS Code](https://code.visualstudio.com/) 与
   [PlatformIO IDE 扩展](https://marketplace.visualstudio.com/items?itemName=PlatformIO.platformio-ide)
   （它会自动装好 PlatformIO Core 和 STM32 工具链）；
   或者只装命令行的 [PlatformIO Core](https://docs.platformio.org/en/latest/core/installation.html)。
2. 克隆本仓库：
   ```bash
   git clone https://github.com/hongligongsi/qingwa-openpnp-hongli.git
   cd qingwa-openpnp-hongli
   ```

### 第 2 步：编译主板固件

不用改任何东西——默认配置就是 REV5 主板：

```bash
pio run
```

首次编译会下载依赖库并全量构建，耗时数分钟；之后增量编译很快。
编译成功的标志是输出 `SUCCESS` 和固件体积统计（Flash 应约 22%、RAM 约 7%），
产物位于 `.pio/build/Opulo_Lumen_REV5/firmware.bin`（与 `.elf`）。

### 第 3 步：让主板进入烧录模式

主板出厂时 STM32 自带 **DFU 引导程序**（USB 设备 ID `0483:df11`）：

1. 按住主板上的 **BOOT0** 按键不放；
2. 短按一下 **RESET**，再松开 BOOT0；
3. 插上 USB 线连接电脑——设备管理器（Windows）或 `lsusb`（Linux）里应出现
   `STM32 BOOTLOADER`。

> 如果主板已刷过本固件且 DFU 触发正常，也可直接 `pio run -t upload`，
> PlatformIO 会自动检测 DFU 设备。

### 第 4 步：烧录

```bash
pio run -e Opulo_Lumen_REV5 -t upload
```

看到 `File downloaded successfully` 即成功，拔插 USB 复位后固件即运行。

### 第 5 步：连接验证

```bash
# 打开串口监视（注意波特率 250000）
pio device monitor -b 250000
```

发送以下命令验证：

```gcode
M115            ; 回报固件版本与机器名（应含 LumenPnP）
M119            ; 查询限位状态
G28             ; 全轴归位（先确认限位接线正确再执行！）
```

一切正常后，就可以在 OpenPnP 里把机器接入了。

**飞达呢？** 飞达固件的构建/烧录流程相同，只是要换配置和 env——
完整步骤见下一节「构建与烧录 → 程序二」。

---

## ⚙️ 构建与烧录

### 环境准备

- 安装 [PlatformIO Core](https://docs.platformio.org/en/latest/core/installation.html)，
  推荐用 **VS Code + PlatformIO IDE** 或 Marlin 的 **Auto Build** 插件/脚本
  （`buildroot/share/vscode/auto_build.py`，或 `process-palette.json` 定义的
  「PIO Build」命令）。
- 默认构建目标已经设为 **REV5 主板**，无需额外选择。

### 程序一：主板固件（REV5，默认）

`Marlin/` 根目录的 `Configuration.h` / `Configuration_adv.h` 就是激活的主板配置，
直接构建即可：

```bash
# 编译（默认 env 即 Opulo_Lumen_REV5）
pio run

# 明确指定目标
pio run -e Opulo_Lumen_REV5

# 烧录
pio run -e Opulo_Lumen_REV5 -t upload

# 串口监视（250000 baud）
pio device monitor -b 250000
```

> 若修改了 `Configuration.h` 等配置，直接重新 `pio run` 即可；PlatformIO 会自动重建。

### 程序二：飞达固件（REV3 / REV4）

飞达与主板**共用同一份源码**，构建时把对应的飞达配置快照套用到 `Marlin/`
根目录，再切换 env 编译。以 REV4 + 送料器 v3.1 为例：

```bash
# 1) 备份当前主板配置
cp Marlin/Configuration.h    /tmp/mb_Configuration.h
cp Marlin/Configuration_adv.h /tmp/mb_Configuration_adv.h

# 2) 套用飞达配置（四选一，见上表）
cp Marlin/rev4-v3.1-feeder-config/Configuration*.h Marlin/

# 3) 编译飞达固件（产物在 .pio/build/Opulo_Lumen_REV4/）
pio run -e Opulo_Lumen_REV4

# 4) 烧录到飞达主控
pio run -e Opulo_Lumen_REV4 -t upload

# 5) 还原主板配置
cp /tmp/mb_Configuration.h    Marlin/Configuration.h
cp /tmp/mb_Configuration_adv.h Marlin/Configuration_adv.h
```

> - 换配置后首次编译会全量重建（不同配置的头文件依赖不同），属正常现象。
> - 改用 `rev3-feeder-config` 时对应 `-e Opulo_Lumen_REV3`；
>   改用 `rev4-v3.0-feeder-config` 或 `rev4-v3.1-feeder-pwm-aux-config` 时
>   仍用 `-e Opulo_Lumen_REV4`。
> - 提交代码前记得还原主板配置，保持 `Marlin/` 根目录始终是 REV5。

### 烧录方式详解

主板和飞达主控都是 STM32F407VET6，板级定义支持 4 种烧录协议
（`stlink` / `dfu` / `jlink` / `blackmagic`），默认使用 **DFU**：

**方式 A：DFU（推荐，只需一根 USB 线）**

```bash
# 1. 按住 BOOT0 → 短按 RESET → 松开 BOOT0，进入 DFU 模式
#    （Windows 设备管理器应出现 "STM32 BOOTLOADER"）
# 2. 烧录
pio run -e Opulo_Lumen_REV5 -t upload          # 主板
pio run -e Opulo_Lumen_REV4 -t upload          # 飞达（配置同上已套用）
# 3. 拔插 USB 复位，固件即运行
```

若 DFU 设备识别异常，也可手动用 `dfu-util`：

```bash
dfu-util -a 0 -d 0483:df11 -D .pio/build/Opulo_Lumen_REV5/firmware.bin -s 0x08000000:leave
```

**方式 B：ST-Link（调试器，适合变砖救援）**

```bash
pio run -e Opulo_Lumen_REV5 -t upload --upload-protocol stlink
```

需要 4 根线：SWDIO / SWCLK / GND / 3.3V 接到板载 SWD 排针。
固件损坏导致无法进 DFU 时，ST-Link 是唯一可靠的恢复手段。

### 跑官方测试（可选）

```bash
make tests-all-local            # 本机跑全部测试
make tests-single-local TEST_TARGET=Opulo_Lumen_REV5
```

---

## 🔧 配置修改与版本管理

### 配置文件的组织方式

- **`Marlin/Configuration.h` / `Configuration_adv.h`**：当前仓库实际使用的激活配置
  （对应 REV5 **主板**，即默认构建目标）。
- **`Marlin/rev5-config/`**：主板配置快照，与激活配置保持**逐字节一致**
  （2026-10-20 刷新）。**约定：每次修改主板配置并提交后，同步刷新该快照**：
  ```bash
  cp Marlin/Configuration.h    Marlin/rev5-config/Configuration.h
  cp Marlin/Configuration_adv.h Marlin/rev5-config/Configuration_adv.h
  ```
- **`Marlin/rev3-*` / `rev4-*` 目录**：**飞达（Feeder）**固件的配置快照，
  按主控代次与送料器硬件版本分四套（见「目录结构」一节的对照表）；
  构建飞达固件时取出套用（步骤见「构建与烧录 → 程序二」）。
- **`Marlin/config.ini`**：Marlin 的 ini 编译期配置入口
  （`[config:minimal/basic/advanced]`）。默认未启用（`ini_use_config = none`）；
  如需用 ini 方式维护配置可开启并按需组合。

### 如何安全地修改配置（教程）

想改运动参数（速度、加速度、电流）是最常见的需求，照下面做即可：

1. **编辑配置**。绝大多数参数在 `Marlin/Configuration.h`，进阶项在
   `Configuration_adv.h`。例如把 X/Y 默认速度从 7000 提到 8000 mm/s
   （轴序：X / Y / Z / I / J）：

   ```cpp
   #define DEFAULT_MAX_FEEDRATE {8000, 8000, 1000, 50000, 50000}  // (mm/s)
   ```

2. **重新编译**：`pio run`。配置改动会触发增量重建。

3. **参数生效方式二选一**：
   - 烧录新固件后，参数已是编译默认值；本固件未启用 EEPROM，改过的参数重启即复位
     （若已启用 `EEPROM_SETTINGS`，此时应执行 `M502` + `M500`）；
   - 或不重刷固件，直接在串口发 `M203 X8000 Y8000` 临时调整（本固件未启用 EEPROM，
     重启后会回到编译值）。

4. **同步快照**（改的是主板配置时）：把激活配置拷入 `rev5-config/`，
   保持快照与现状一致（命令见上文「配置文件的组织方式」）。

**⚠️ 修改注释时千万注意**：配置文件里的部分注释是**机器可读的**，
被 `schema.py` 解析用于生成配置元数据，改动它们会导致构建失败或配置项丢失：

| 不能动的注释 | 原因 |
|---|---|
| `// @section xxx` | 章节分组键，翻译/改名会导致整段归类错位 |
| `// :[0, 1, 2, 3]`、`// :{...}` | 选项列表，必须单行完整 |
| `(mm)`、`(°C)`、`(seconds)` 等括号单位 | 会被提取为 units 字段 |
| 温度传感器条目行（` -5 : MAX31865 ...`） | 每条必须独占一行 |
| 字符串字面量、宏名、G 代码命令 | 直接影响固件行为 |

改完配置建议跑一遍仓库自带的回归校验（详见
`buildroot/scripts/README-config-i18n.md`）：

```bash
python buildroot/scripts/check-config-i18n.py          # 注释结构 + 预处理 + schema
python buildroot/scripts/check-config-code-intact.py --ref HEAD  # 代码零改动确认
```

### 关于本仓库固件版本基线

- 源码基线：**Marlin 2.1.x**（配置文件版本 `CONFIGURATION_H_VERSION 02010300`），
  保留上游 `import-2.1.x`/`bugfix-2.1.x` 演进结构。

---

## 🧰 常用 G 代码

本固件保留 Marlin 的 G/M 指令集，但**并非全部都被编译进来**——贴片机没有挤出机、
加热、探针、SD 卡和显示屏，相关指令在编译阶段就被裁掉了。下表用三种标记区分：

- ✅ 可用
- ⚠️ 可用但受限（见备注）
- ❌ 本固件未编译（发送会得到 `Unknown command`）

### 一、连接与状态查询

| 指令 | 状态 | 说明 |
|------|------|------|
| `M115` | ✅ | 固件信息与能力集，上位机连机第一步 |
| `M114` | ✅ | 报告当前坐标（X/Y/Z 毫米 + A/B 角度） |
| `M119` | ✅ | 三个限位开关的当前电平 |
| `M122` | ✅ | 六路 TMC2209 全量状态：电流、微步、连接错误计数 |
| `M105` | ⚠️ | 无温度传感器，回传值为空/0 |
| `M503` | ✅ | 打印内存中的全部可调参数（不读 EEPROM） |
| `M111` | ❌ | 调试等级，非开发模式未编译 |
| `M31` | ❌ | 无 SD 卡 |

### 二、运动控制

| 指令 | 状态 | 说明 |
|------|------|------|
| `G0` / `G1` | ✅ | 直线移动（贴片机的主力指令） |
| `G2` / `G3` | ✅ | 圆弧插补（`ARC_SUPPORT` 已开） |
| `G4` | ✅ | 延时，`G4 P500` = 停 500 ms |
| `G28` | ✅ | 归位，可限定轴：`G28 X Y` |
| `G92` | ✅ | 设定当前位置为指定坐标（不改实际位置） |
| `M92` | ✅ | 设置每单位步数（运行时生效，重启丢失） |
| `M201` / `M203` | ✅ | 最大加速度 / 最大速度 |
| `M204` | ✅ | 加速度：`P` 打印、`T` 空移、`R` 回抽 |
| `M205` | ✅ | 高级设置，本固件用 `J`（Junction Deviation）|
| `M206` / `M428` | ✅ | 原点偏移 / 用当前位置反推原点偏移 |
| `M211` | ✅ | 软限位开关与查询 |
| `M220` | ✅ | 速度倍率百分比，`M220 S50` 降速一半 |
| `M400` | ✅ | 等待队列中所有运动执行完 |
| `M410` | ✅ | 立即急停并清空运动队列 |
| `M17` / `M18` / `M84` | ✅ | 使能 / 释放电机，`M84 S30` 设 30 s 空闲释放 |
| `M120` / `M121` | ✅ | 限位常开检测 / 关闭 |
| `M221` | ❌ | 流量倍率，无挤出机 |
| `G29` / `G30` / `G38` | ❌ | 无探针、无调平 |
| `G10` / `G11` | ❌ | 回抽相关，无挤出机 |
| `G5` / `G60` / `G61` | ❌ | 贝塞尔 / 位置存档未启用 |
| `M290` / `M600` | ❌ | 微步进 / 换料暂停，均未编译 |

### 三、TMC2209 驱动调节

| 指令 | 状态 | 说明 |
|------|------|------|
| `M906` | ✅ | 设电流（mA RMS）：`M906 X800 Y1000` |
| `M122` | ✅ | 查询驱动状态；`M122 X` 只看单轴 |
| `M569` | ✅ | StealthChop 开关：`M569 S1 Z` 开、`S0` 关 |
| `M912` – `M915` | ❌ | 预报警、混合阈值、StallGuard，相关功能未启用 |

### 四、引脚直控（贴片机专属玩法）

| 指令 | 状态 | 说明 |
|------|------|------|
| `M42` | ✅ | 写引脚：`M42 P<编号> S<0-255>`；`I` 设输入、`T` 设上拉 |
| `M43` | ✅ | 读引脚 / 列引脚；**不带参数会打印全部引脚编号对照表** |
| `M43 E1` | ✅ | 实时监视限位状态，调试归位最有用 |
| `M43 T` | ✅ | 批量翻转输出引脚 |

> ⚠️ `M42`/`M43` 里的 `P` 是 **Marlin 内部引脚编号**，不是 GPIO 名字。
> 拿不准时先发一次 `M43` 列出编号，再去对 `PD0`、`PA5` 这些名字。

### 五、风扇 / 灯带 / 蜂鸣器

| 指令 | 状态 | 说明 |
|------|------|------|
| `M106 P<0-3> S<0-255>` | ✅ | 四路风扇调速（PB8 / PB9 / PE5 / PE6） |
| `M107 P<0-3>` | ✅ | 关对应风扇 |
| `M150 R.. U.. B..` | ✅ | NeoPixel 颜色，`U` 是绿色通道（`G` 被 G 代码占用） |
| `M150 P<0-255>` | ✅ | **亮度**：`P0` 关灯、`P127` 半亮、只写 `P` = 255 全亮 |
| `M150 S0` / `S1` | ✅ | 只控第一路（`PC7`）/ 第二路（`PC8`）；不带 `S` 时两路同时设 |
| `M150 I<n>` | ✅ | 只改第 n 颗灯珠（`I` 是索引，`P` 是亮度） |
| `M300 S<Hz> P<ms>` | ✅ | 蜂鸣，`M300 S523 P200` 发 C5 音 |
| `M300 S0` | ✅ | 立即静音，调试时很好用 |

### 六、参数保存（本固件的坑）

| 指令 | 状态 | 说明 |
|------|------|------|
| `M503` | ✅ | 报告当前内存中的参数（随时可用） |
| `M502` | ✅ | 把内存参数恢复成固件编译时的默认值 |
| `M500` | ⚠️ | **回 `EEPROM disabled`**，因为 `EEPROM_SETTINGS` 未启用 |
| `M501` | ⚠️ | 无 EEPROM 可读，等效于重置并报告 |

想让 `M92`、`M906`、`M201` 这些改完能掉电保存，需要先在 `Configuration.h`
打开 `EEPROM_SETTINGS` 再重新编译烧录（板级已备好 SRAM 仿真与 8 KB 空间）。

### 七、典型调试顺序

```gcode
M115                    ; 1. 确认连上的是 LumenPnP
M119                    ; 2. 手推各轴压限位，看状态是否翻转
G28                     ; 3. 归位
G92 X0 Y0 Z0 A0 B0      ; 4. 当前位置设为原点（或直接 G28 后即可）
G0 X50 Y50 F3000        ; 5. 低速试走一段
M114                    ; 6. 核对实际坐标是否吻合
M122                    ; 7. 检查驱动有无连接错误
M300 S523 P150          ; 8. 试蜂鸣
M150 R0 U255 B0         ; 9. 试灯带（绿，默认全亮）
M84                     ; 10. 释放电机
```

**飞达固件（另刷）的常用指令**——飞达把三个送带轮定义为旋转轴
`A` / `B` / `C`（角度制），送带/退带就是转动它们：

```gcode
G1 A45 F2000            ; A 轮正转 45°（推进一格编带）
G1 A-45 F2000           ; A 轮反转（退带）
M114                    ; 查询当前各轴位置（旋转轴单位为度）
```

完整命令表见 [Marlin G-code 文档](https://marlinfw.org/docs/gcode/M000-M001.html)。

---

## 🎛 常用调整速查：速度 / 电流 / 灯亮度

这三样都能在**三个不同层次**修改，改错地方会"看起来改了却没效果"。先记住分工：

| 层次 | 管什么 | 要重编译吗 |
|------|--------|------------|
| OpenPnP（`.openpnp2/machine.xml`） | 实际下发的 `F` 值、每次连机重发的电流 | ❌ |
| Marlin 固件（`Configuration*.h`） | 安全上限、上电默认值 | ✅ |
| 运行时 G 代码（串口 / 脚本） | 临时生效，重启还原 | ❌ |

> 前提：本固件 **`EEPROM_SETTINGS` 未启用**（见 FAQ），所以任何 `M9xx` / `M2xx`
> 运行时改动都**不会掉电保存**。

### 一、改机器速度

**最关键的一点：OpenPnP 发的是 `G1 ... F200`，这个 `F` 值来自 OpenPnP 的轴
Feedrate，不是固件。** 固件的 `DEFAULT_MAX_FEEDRATE`（7000 mm/s）只是安全上限——
把它改大机器不会变快，改小反而会截断你的指令。

| 想改什么 | 改哪里 |
|----------|--------|
| 实际移动速度 | OpenPnP → Machine Setup → Axes → `x` / `y` / `z1` → **Feedrate** |
| 实际加速度 | 同一页的 **Acceleration** |
| 固件安全上限 | `Configuration.h` 的 `DEFAULT_MAX_FEEDRATE` / `DEFAULT_MAX_ACCELERATION`，或运行时 `M203` / `M201` |
| 临时整体降速 | 串口发 `M220 S50`（降到一半），`M220 S100` 恢复 |

当前这套配置的实测值（读自 `.openpnp2/machine.xml`）：

| 轴 | Feedrate | Acceleration |
|----|----------|--------------|
| `x` | 200 mm/s | 1500 mm/s² |
| `y` | 200 mm/s | 1500 mm/s² |
| `z1` | 300 mm/s | 1200 mm/s² |
| `a` / `b`（旋转） | 50000 °/s | 500 |

**调参建议**：X/Y 的 200 mm/s 已经不慢（12 m/min），贴片的真正瓶颈通常在
**加速段和 Z 行程**，不在巡航速度。先把加速度往上试（1500 → 2500 → 3000），
收益比单纯拉 Feedrate 明显；Feedrate 拉太高反而容易丢步、定位不准。

改完在 OpenPnP 里**重连一次**（或重启软件）让新参数生效。

### 二、改电机电流

**最省事的办法：改 OpenPnP 的连接脚本，不用碰固件。**

因为 EEPROM 没启用，固件里的电流值重启就丢——但这份 `machine.xml` 的
`CONNECT_COMMAND` 每次连机都会重发电流：

```gcode
M906 Y1000 X900   ; 设置 Y/X 电机电流
M906 A200 B200    ; 设置 L/R（旋转 A/B）电机电流
```

改这两行即可（单位 **mA RMS**）。要设 Z 轴就加一句 `M906 Z800`。注意 `A` / `B`
就是固件里的 I/J 旋转轴（`AXIS4_NAME 'A'`、`AXIS5_NAME 'B'`）。

编译期默认值在 `Configuration_adv.h`：

| 宏 | 当前值 | 对应轴 |
|----|--------|--------|
| `X_CURRENT` | 800 mA | X |
| `Y_CURRENT` | 1000 mA | Y（双电机同步） |
| `Z_CURRENT` | 800 mA | Z |
| `I_CURRENT` | 200 mA | 旋转 A（OpenPnP 里叫 `a`） |
| `J_CURRENT` | 200 mA | 旋转 B（OpenPnP 里叫 `b`） |

⚠️ **别乱加**：TMC2209 长时间超过 **1200 mA** 会明显发烫，散热不好会触发
热保护丢步。旋转轴 200 mA 是有意压低的（负载轻）；如果旋转打滑再往上加，
**一次加 100 mA** 试探。

### 三、改环灯亮度

环形灯走 `M150`：**亮度是 `P`（0–255），颜色是 `R` / `U` / `B`**（`U` = 绿，
因为 `G` 被 G 代码占用）。

| 目的 | 命令 |
|------|------|
| 全白最亮 | `M150 P255 R255 U255 B255` |
| 降到约 40%，保持颜色 | `M150 K P102` |
| 暖白（长时间作业更舒服） | `M150 P255 R255 U180 B80` |
| 关灯 | `M150 P0` |
| 只控第二路灯带 | `M150 S1 P255 R255 U255 B255` |

⚠️ 单独发 `M150 P102` 会把颜色一起清零（等于不亮），要保色调光必须加 `K`。

**在 OpenPnP 里固定亮度**：Machine Setup → 执行器 `LED` → 开命令
`M150 P255 R255 U255 B255`，把 `P255` 改小（如 `M150 P120 R255 U255 B255`），
以后每次点灯都是这个亮度，不必手发命令。

### 四、直接改固件（编译期）

**改固件不是调速度的首选办法**——因为 OpenPnP 连上后会把好几个值覆盖掉：

| OpenPnP 什么时候发什么 | 覆盖了固件哪个值 |
|------------------------|------------------|
| 每次移动前都发 `M204 S<加速度>`（`MOVE_TO_COMMAND`） | `DEFAULT_ACCELERATION` / `DEFAULT_TRAVEL_ACCELERATION` |
| 每次连机发 `M906 X.. Y..` 与 `M906 A.. B..` | `X_CURRENT` 一直到 `J_CURRENT` |
| 点灯时发 `M150 P..` | `NEOPIXEL_BRIGHTNESS` 只在不发 M150 时有效 |

所以改固件真正解决问题的，是下面这四类：

1. **改安全上限** —— 上限决定"最多能跑多快/多猛"，OpenPnP 设得再高也会被截断
2. **固件独有项** —— 微步 `_MICROSTEPS`、归位速度、行程、软限位，OpenPnP 管不到
3. **脱机运行** —— 不接上位机、用串口或脚本直接跑时，编译值就是唯一依据
4. **让参数可保存** —— 打开 `EEPROM_SETTINGS` 后，`M906` / `M203` 才能掉电保留

#### 速度（`Marlin/Configuration.h`）

| 宏 | 行 | 当前值 | 作用 |
|----|----|--------|------|
| `DEFAULT_MAX_FEEDRATE` | 1363 | `{7000,7000,1000,50000,50000}` | X/Y/Z/I/J 速度**上限**（mm/s、°/s） |
| `DEFAULT_MAX_ACCELERATION` | 1377 | `{15000,15000,10000,10000,10000}` | 加速度**硬上限** |
| `DEFAULT_ACCELERATION` | 1396 | `2000` | 缺省加速度（会被 OpenPnP 的 `M204 S` 覆盖） |
| `DEFAULT_TRAVEL_ACCELERATION` | 1399 | `2500` | 空移加速度（同上会被覆盖） |
| `JUNCTION_DEVIATION_MM` | 1449 | `0.013` | 拐角偏差，越小越贴路径、越慢 |
| `DEFAULT_AXIS_STEPS_PER_UNIT` | 1355 | `{320,320,40,4.44,4.44}` | 步/mm，只有改微步或换皮带轮才动它 |
| `HOMING_FEEDRATE_MM_M` | 2462 | `{150,150,150,50,50}×60` | 归位速度（mm/min） |

想让 OpenPnP 里能把加速度设到 3000，`DEFAULT_MAX_ACCELERATION` 就必须 ≥ 3000
（现在 15000，够用）。**哪天在 OpenPnP 里设了 20000 却感觉没变快，就是被这里的
15000 截断了。**

#### 电流（`Marlin/Configuration_adv.h`）

| 宏 | 行 | 当前 | 轴 |
|----|----|------|-----|
| `X_CURRENT` | 2850 | 800 mA | X |
| `Y_CURRENT` | 2870 | 1000 mA | Y |
| `Z_CURRENT` | 2890 | 800 mA | Z |
| `I_CURRENT` | 2930 | 200 mA | 旋转 A |
| `J_CURRENT` | 2940 | 200 mA | 旋转 B |

直接改数字即可，单位 mA RMS。**Y2 没有独立宏**，它是 `Y2_CURRENT Y_CURRENT`，
改 Y 就同时改了双 Y 龙门。

#### 灯亮度（`Marlin/Configuration.h`）

| 宏 | 行 | 当前 | 作用 |
|----|----|------|------|
| `NEOPIXEL_BRIGHTNESS` | 3758 | `255` | 第一路（`PC7`）上电初始亮度 |
| `NEOPIXEL2_BRIGHTNESS` | 3765 | `255` | 第二路（`PC8`）上电初始亮度 |
| `NEOPIXEL_STARTUP_TEST` | 3759 | 启用 | 上电闪一遍红绿蓝，嫌烦可注释掉 |

注意这两行亮度只决定**没人发 `M150` 时**的亮度。OpenPnP 一点灯就发
`M150 P255 ...`，照样满亮——想在 OpenPnP 里常态暗一些，还是改执行器的 `P` 值。

#### 改完必做四步

```bash
# 1. 同步存档（两份配置必须逐字节一致）
cp Marlin/Configuration.h Marlin/Configuration_adv.h Marlin/rev5-config/

# 2. 校验注释结构与 schema（基线 2444 项）
python buildroot/scripts/check-config-i18n.py

# 3. 确认没改坏代码（可选，只在怀疑动了代码行时跑）
python buildroot/scripts/check-config-code-intact.py --ref HEAD

# 4. 编译并烧录（默认 DFU）
pio run -e Opulo_Lumen_REV5 -t upload
```

只编译不烧录用 `pio run -e Opulo_Lumen_REV5`，产物在
`.pio/build/Opulo_Lumen_REV5/firmware.bin`。

#### 改配置的三条铁律

1. **只改数字，别动结构**：`// @section`、`:[...]` 选项列表、`(mm)` 这类括号单位
   都是 `schema.py` 的解析依据，动了轻则配置项丢失、重则构建直接报错
2. **改微步要同步改步数**：`X_MICROSTEPS` 从 64 改成 32，`DEFAULT_AXIS_STEPS_PER_UNIT`
   的 X 也得从 320 改成 160，否则走 1 mm 会变成 2 mm
3. **电流别贪多**：TMC2209 长期超过 1200 mA 会明显发烫并丢步，一次加 100 mA 试探

### 五、哪些改动重启就没了

| 改动方式 | 要重编译？ | 掉电保留？ |
|----------|-----------|-----------|
| OpenPnP 轴 Feedrate / Acceleration | ❌ | ✅ |
| OpenPnP 连接脚本里的 `M906` | ❌ | ✅（每次连机重发） |
| OpenPnP 执行器 `LED` 的亮度 | ❌ | ✅ |
| 串口发 `M203` / `M201` / `M204` | ❌ | ❌ |
| 串口发 `M906` | ❌ | ❌ |
| 串口发 `M150` | ❌ | ❌ |
| 改 `Configuration*.h` 后重编烧录 | ✅ | ✅ |

> 想让运行时 `M906` 也能保存，需要打开 `Configuration.h` 的 `EEPROM_SETTINGS`
> 再重编（板级已备好 8 KB SRAM 仿真）。

---

## 🛠 常见问题

<details>
<summary><b>烧录后没有串口？</b></summary>

确认使用 USB 数据线连接 STM32 的 USB 口；首次可能需要安装驱动
（Windows 下 STM32 USB CDC 驱动）。设备管理器/`ls /dev/tty*` 应能出现新串口，
波特率使用 `250000`。
</details>

<details>
<summary><b>如何确认刷入的固件版本/配置？</b></summary>

上位机发送 `M115`，会回传固件信息（包含版本字符串与机器名 LumenPnP）。
</details>

<details>
<summary><b>为什么没有温控/挤出？</b></summary>

贴片机不需要 3D 打印的挤出与加热功能。本固件在 `Configuration.h` 里
`EXTRUDERS 0` 且所有温度传感器关闭，属预期行为，而非故障。
</details>

<details>
<summary><b>怎么区分手上的飞达该刷哪套配置？</b></summary>

看两个信息：① 飞达主控板丝印是 REV3 还是 REV4（决定 env）；② 送料器机构
硬件版本是 v3.0 / v3.1（决定速度参数配置）。v3.0 用
`rev4-v3.0-feeder-config`（慢速保守），v3.1 用 `rev4-v3.1-feeder-config`；
若 AUX 风扇有啸叫想消除，改用 `rev4-v3.1-feeder-pwm-aux-config`（仅多开
`FAST_PWM_FAN`，31.4 kHz）。不确定时先刷 v3.1 版本，参数偏保守不影响验证。
</details>

<details>
<summary><b>飞达能单独连接电脑调试吗？</b></summary>

可以。飞达固件同样使用 USB CDC 串口（`SERIAL_PORT -1`，250000 baud），
用 USB 线把飞达主控接到电脑后 `pio device monitor -b 250000`，
发 `M115` 应回报飞达固件信息。每台飞达在上位机里是一个独立串口设备。
刷飞达固件的完整流程见「构建与烧录 → 程序二」。
</details>

<details>
<summary><b>按了 BOOT0 + RESET 仍找不到 DFU 设备？</b></summary>

依次排查：① 确认按住 BOOT0 的时机是**上电/复位瞬间**（先按住 BOOT0 再按
RESET）；② 换一根确定支持数据的 USB 线；③ Linux 下确认有 `dfu-util` 权限
（udev 规则或 sudo）；④ 若仍无法进入 DFU，说明引导程序可能被覆盖，
用 **ST-Link** 方式重刷（见「烧录方式详解」）。
</details>

<details>
<summary><b>改了配置注释后构建报错 / 配置项丢失？</b></summary>

大概率是动了**机器可读注释**（`@section` 标记、`:[...]` 选项列表、
括号单位、传感器条目等，详见「配置修改与版本管理」的注意事项表）。
对照 git 恢复误改的行：`git diff Marlin/Configuration.h`，
再跑 `python buildroot/scripts/check-config-i18n.py` 确认 schema 项数
恢复到 2444 项基线。
</details>

<details>
<summary><b>M500 报 EEPROM disabled，参数存不下来？</b></summary>

`Configuration.h` 里的 `EEPROM_SETTINGS` 目前是注释状态（`// #define EEPROM_SETTINGS`），
所以 EEPROM 相关代码整体不参与编译：`M500` 只会回 `EEPROM disabled`，
`M92` / `M906` / `M201` 这类运行时改动重启即丢失。
板级其实已经备好 SRAM 仿真空间（`SRAM_EEPROM_EMULATION`，8 KB），
需要掉电保存就打开该宏重新编译烧录；只想看当前生效的参数，发 `M503` 即可。
</details>

<details>
<summary><b>环形灯怎么调亮调暗、换颜色？</b></summary>

环形灯是 WS2812 灯带，接在主板 `PC7`（`NEOPIXEL_PIN`，18 颗，`NEO_GRB`），
由 `M150` 控制。**亮度用 `P`，颜色用 `R` / `U` / `B`**——`U` 是绿色通道，
因为 `G` 已被 G 代码占用。

| 目的 | 命令 |
|------|------|
| 全白最亮 | `M150 P255 R255 U255 B255` |
| 只看亮度 40%（保持当前颜色） | `M150 K P102` |
| 暖白（偏黄，适合作业照明） | `M150 P255 R255 U180 B80` |
| 关灯 | `M150 P0` |
| 只控第一路 / 第二路 | `M150 S0 ...` / `M150 S1 ...` |

⚠️ **两个容易踩的坑：**

1. **`P` 是亮度（0–255），不是灯珠数量。** 想只改第 n 颗灯珠要用 `I<n>`。
2. **单独发 `M150 P102` 会把颜色清零**（没写的通道默认 0，等于不亮）。
   要保色改亮度，加 `K`：`M150 K P102`；否则就把三个颜色一起写全。

不带 `S` 时两路灯带（`PC7` + `PC8`）一起设置；你的机器若只接了环灯，
第二路挂了灯珠才会看到反应。

**在 OpenPnP 里固定亮度**：机器配置 → 执行器 `LED` → 开命令
`M150 P255 R255 U255 B255`、关命令 `M150 P0`。把开命令里的 `P255` 改小
（如 `M150 P120 R255 U255 B255`）就能每次点灯都用同一个不刺眼的亮度，
不用每次手发命令。

> 亮度只改发光强度、不改色温。视觉识别过曝时优先降 `P`，别直接关灯——
> 关灯后元件轮廓反而会消失。另外 `NEOPIXEL_STARTUP_TEST` 是开着的，
> 上电会循环闪一遍红绿蓝，这是自检，不是故障。
</details>

<details>
<summary><b>开机蜂鸣器声音怎么设置？</b></summary>

开机音在 `Marlin/Configuration_adv.h` 的 `STARTUP_COMMANDS` 中定义（主板配置
约 3855 行），本质是开机时自动执行的一串 `M300` 蜂鸣 G 代码：

```
#define STARTUP_COMMANDS "M300 S2000 P100\nG4 P900\nM300 S2000 P100\n..." \
                         "...\nM300 S2500 P1000"
```

- `S<频率>`：蜂鸣音调（Hz）；`P<时长>`：持续时间（ms）；`G4 P<ms>`：音符间隔。
- 想换节奏/音调，直接改这串命令即可；想换成旋律，可用固件里注释掉的三音
  示例：`"M300 S523 P150\nM300 S659 P150\nM300 S784 P300"`（C5-E5-G5）。
- 前提条件：`Configuration.h` 中需启用 `SPEAKER`（主板配置已启用），否则
  `M300` 的 `S` 变频参数不生效；蜂鸣器引脚由
  `pins_OPULO_LUMEN_REV5.h` 的 `BEEPER_PIN PA7` 定义。
- 想在屏幕菜单里加静音开关：启用 `Configuration_adv.h` 中的
  `SOUND_MENU_ITEM`；`SOUND_ON_DEFAULT` 控制默认是否发声。调试时也可
  直接发 `M300 S0 P0` 临时静音测试。

改完记得重新编译烧录（开机音是编译期写死的，不能运行时保存）。

> 💡 **不想手敲 G-code？** 仓库自带一个网页版
> **[M300 蜂鸣器旋律编辑器](m300_editor/README.md)**（`m300_editor/index.html`），
> 支持可视化编辑音符、实时预览播放、自定义波形试听，可一键导入/导出
> `STARTUP_COMMANDS` 格式的 G-code。详见
> [m300_editor/README.md](m300_editor/README.md)。
</details>

<details>
<summary><b>M300 蜂鸣器旋律编辑器怎么用？</b></summary>

仓库自带一个纯网页工具 `m300_editor/index.html`，用于在电脑上可视化编辑开机蜂鸣旋律。

**打开方式：**
- 双击 `m300_editor/index.html` 直接用浏览器打开；或
- 在项目根目录运行 `python -m http.server 8765`，访问
  `http://127.0.0.1:8765/m300_editor/index.html`。

**典型流程：**
1. 把固件 `STARTUP_COMMANDS` 引号里的 G-code 粘贴到页面底部导入框，
   点「⬆ 从下方导入」，音符列表会自动填入频率和时长。
2. 在表格里增删改音符（频率 Hz / 时长 ms），或直接点上方预设旋律
   （简单蜂鸣 / 摩斯节奏 / Do-Mi-Sol / 开机旋律等）。
3. 点「▶ 播放」实时试听；点时间轴上的色块可单独试听单个音符。
4. 满意后点「⬇ 导出 G-code」→「📋 复制」，粘贴回
   `Configuration_adv.h` 的 `STARTUP_COMMANDS` 引号内，重新编译烧录。

**关于自定义波形：** 编辑器支持手绘波形 / 谐波滑块调节，但这只用于
**电脑端预览听感**。实际固件的压电蜂鸣器只能输出方波，M300 指令只
控制频率和时长，不支持自定义波形。

> 完整教程（含界面截图）见
> [m300_editor/README.md](m300_editor/README.md)。
</details>

---

## 🤝 致谢与许可证

本项目不是一个独立作品——它的每一层都建在别人的开源工作上，而这些上游项目
用的是**三种不同的许可证**。先弄清"哪部分内容归哪个许可"，再看每一条对你实际
意味着什么。

### 谁的肩膀，什么许可

| 上游项目 | 在本项目中的角色 | 许可证 | 本仓库含其内容 |
|----------|------------------|--------|----------------|
| [Marlin](https://github.com/MarlinFirmware/Marlin)（Scott Lahteine 及社区） | 固件本体：运动规划、G 代码解析、STM32 HAL、TMC 驱动框架 | **GPL-3.0** | ✅ 整个 `Marlin/` |
| [Opulo LumenPnP](https://github.com/opulo-inc/) 硬件设计 | REV5 主板原理图 / PCB / BOM、板级引脚定义 | **CERN-OHL-W 2.0** | ⚠️ 仅引脚与板级常量 |
| Opulo LumenPnP 软件 | 飞达固件、上位机配套脚本、配置模板 | **MPL 2.0** | ⚠️ `.openpnp2/` 配置 |
| Opulo LumenPnP 文档 | 装配、接线、校准说明 | **CC BY-SA 4.0** | ⚠️ 本 README 参考并改编 |
| [OpenPnP](https://openpnp.org/) | 上位机 | GPL-3.0 | ❌ 单独安装 |
| [TMCStepper](https://github.com/teemuatlut/TMCStepper)、[Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)、STM32duino | TMC2209 寄存器、灯带驱动、STM32 底层 | 各自许可（见 `.pio/libdeps` 内 LICENSE） | 经依赖引入 |
| [PlatformIO](https://platformio.org/) | 构建系统与 ARM 工具链 | Apache-2.0 | ❌ 工具链 |

> **适用范围以各上游仓库的 LICENSE 文件为准**；上表是按 Opulo 公开的授权说明整理，
> 上游若调整过版本，以其最新声明为优先。

三种 copyleft 的"传染范围"差别很大，一句话记住：

> **GPL 管整个程序 → MPL 只管单个文件 → CERN-OHL-W 管你改过的设计文件 → CC BY-SA 管改编后的文档。**

### 硬件设计：CERN-OHL-W 2.0

LumenPnP 的硬件（REV5 主板、飞达、结构件）以
[CERN Open Hardware Licence v2 – Weakly Reciprocal](https://ohwr.org/cern_ohl_w_v2.txt)
发布。名字里的 **W（Weakly，弱互惠）** 是关键——它只对**你改过的那部分**生效。

| 义务 | 具体要求 |
|------|----------|
| 保留署名 | 保留原作者（Opulo）的名字与版权声明，不得删除 |
| 标注修改 | 改动过的设计文件需说明"已修改"及修改日期 |
| 开源修改 | 你改过的设计文件（原理图、PCB、BOM、结构图）分发时必须仍以 CERN-OHL-W 2.0 提供 |
| 提供获取途径 | 分发实物产品时须附"源码位置"（Source Location）——能拿到设计文件的地址 |
| 不附加限制 | 不能对下游再设限制（如禁止对方继续改进、要求付费才给文件） |
| 无担保 | 原作者不对你的使用或改造承担责任 |

**"弱互惠"到底意味着什么**——这是最容易误解的地方：

- ✅ **可以直接拿来生产和销售**：用这套开源硬件做产品、卖整机完全允许，制造工艺、
  供应链、成本结构等商业信息**都不需要公开**
- ✅ **可以把自己的部分闭源**：你在开源设计上新增的**独立模块**（自研扩展板、
  自研治具）可以闭源，只要它与开源部分的**接口明确**（连接器、排针定义、通信协议）
- ⚠️ **改过的文件必须开源**：如果你直接修改了开源设计文件（改走线、换 BOM 里的料），
  **那个改完的文件**必须开源——"只改了一点点"不是豁免理由
- ❌ **不能把开源设计"藏"进闭源产品**：不能把 CERN-OHL-W 的设计文件当自己闭源
  设计的一部分分发，也不能声称整个产品都是自研

> 本仓库**不包含** LumenPnP 的硬件设计文件，只在
> `Marlin/src/pins/stm32f4/pins_OPULO_LUMEN_REV5.h` 中引用引脚定义与板级常量。
> 要修改硬件，请从 [opulo-inc/lumenpnp](https://github.com/opulo-inc/lumenpnp)
> 取原始设计文件，并遵守上述条款。

### 上游软件：MPL 2.0

Opulo 的软件部分以 [Mozilla Public License 2.0](https://www.mozilla.org/en-US/MPL/2.0/)
发布。MPL 是**文件级（per-file）** copyleft——它的边界是"文件"，不是"程序"。

| 义务 | 具体要求 |
|------|----------|
| 保留署名 | 保留原作者名字、版权与许可声明 |
| 开源修改 | 你修改过的 MPL 文件，分发时必须继续以 MPL 2.0 提供 |
| 告知获取方式 | 分发可执行形式时，须说明如何取得对应源码 |
| 专利授权 | MPL 2.0 授予你使用其中专利技术的权利；但**你若就相关专利起诉原作者，这项授权立即终止** |
| 无担保 | 按"现状"提供 |

**与闭源代码结合是明确允许的：**

- ✅ 可以把 MPL 代码与闭源代码链接、打包进同一个产品分发
- ✅ 你自己写的那部分可以闭源、可以商业销售
- ⚠️ 但**改过的 MPL 文件本身**仍需开源——不能因为"整体是闭源产品"就把它藏起来
- 📌 边界很清楚：**文件是你改的 → 开源；没改的 → 保持原样即可**

MPL 2.0 与 GPL 兼容（未声明 "Incompatible With Secondary Licenses" 时），
MPL 文件可以并入 GPL-3.0 的大作品，但该文件及其修改仍受 MPL 约束。

> 本仓库 `.openpnp2/` 收录了 OpenPnP 的机器配置，其中部分内容可能源自 Opulo
> 提供的模板。做商业产品前，建议分清哪些文件是原始模板、哪些是自己的参数。

### 文档：CC BY-SA 4.0

LumenPnP 的官方文档、装配与校准指南以
[CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/deed.zh-hans) 发布。
本仓库的中英双份 README 编写时参考并改编了这些材料，因此**文档部分同样以
CC BY-SA 4.0 提供**。

| 义务 | 具体要求 |
|------|----------|
| BY — 署名 | 注明原作者（Opulo / LumenPnP） |
| BY — 注明来源 | 附原作品链接 |
| BY — 注明许可与修改 | 说明采用 CC BY-SA 4.0，并说明是否做过修改 |
| SA — 同许可 | 你的**改编作品**须以相同许可发布，不能附加更严格的条款 |
| 商业使用 | ✅ 允许，包括印成手册随整机出售 |

**四种常见场景，边界在哪：**

| 你的做法 | 是否需以 CC BY-SA 发布 |
|----------|------------------------|
| 翻译、改写、重排结构后用作自己的说明书 | ✅ 需要，且必须署名 Opulo |
| 只做格式转换（转 Word、改排版），内容基本不变 | ✅ 需要——分发这个 Word 就是在"分享"该作品 |
| 作为**独立章节**汇编进自己的大手册，其余章节自写 | ⚠️ 仅该章节需 CC BY-SA，大手册其他部分可另行许可 |
| 仅公司内部使用，不对外分享 | ❌ 不需要——CC 许可的义务只在"分享"时触发 |

> 关于"同许可"的范围有个常见误解：CC BY-SA 4.0 要求同许可的是**改编作品
> （Adapted Material）本身**，而不是把它汇编进去的整本大作品。所以"用了
> CC BY-SA 的一段说明，整个软件源码都得 CC BY-SA"并不成立——软件代码与文档
> 是两类作品，各自适用各自的许可。

### 本仓库固件代码：GPL-3.0

`Marlin/` 的改造部分与 `buildroot/scripts/` 下的校验工具以 **GNU GPL v3.0**
发布，全文见 [LICENSE](LICENSE)。它是强传染性（copyleft）许可，分发时
（无论免费还是收费）需履行：

| 义务 | 具体要求 |
|------|----------|
| 提供源码 | 分发固件（含烧录进机器出售）时，必须向接收者提供**完整对应源码**，含构建脚本与配置文件——只给二进制不够 |
| 保留声明 | 不得删除原有版权、许可与免责声明 |
| 标注修改 | 修改过的文件需说明"已修改"及修改时间（GPLv3 §5a） |
| 同一许可 | 衍生作品整体仍须以 GPL-3.0 分发，不能改成更宽松或更严格的条款 |
| 不得附加限制 | 不能对接收者行使 GPL 授予的权利再加限制（如额外收费授权、禁止逆向） |
| 无担保 | 按"现状"提供，作者不承担质量与损害责任 |
| 专利授权 | 贡献者自动向使用者授予其必要专利许可（GPLv3 §11） |

一句话：**自己用、改、卖整机都可以，但一旦对外分发固件，源码必须跟着走。**

### 本项目自己做了什么

以下改动版权归本项目贡献者（代码部分随 GPL-3.0，文档部分随 CC BY-SA 4.0）：

- **配置层汉化与原位修复**：`Configuration.h` / `Configuration_adv.h` 全量中文注释，
  以及主板 + 四套飞达配置的结构修复（魔法注释、schema 兼容）
- **文档体系**：中英双份 README（架构、引脚、构建、调试、G 代码、FAQ）、配置校验说明
- **校验工具**：`buildroot/scripts/check-config-i18n.py`、
  `check-config-code-intact.py` 及 schema 基线
- **M300 蜂鸣器旋律编辑器**：`m300_editor/`（纯前端单页，无外部依赖）
- **开机音与默认参数调整**

### Built With LumenPnP 丝印

如果你用 LumenPnP 生产 PCB，Opulo 欢迎你在板子上加一个 **"Built With LumenPnP"**
标记——丝印文字、贴纸、Logo 都行，位置自定。

这是**授权许可，不是义务**：加不加都不影响你基于本设计进行商用，也不需要额外
申请。对做整机或代工的团队来说，这个标记也算是对上游开源工作的一种回馈。

### 非官方声明

本项目是**社区改造版本**，并非 Marlin 官方发布，也不是 Opulo 官方固件。
"Marlin" 为 MarlinFirmware 的项目名称，"LumenPnP" 为 Opulo 的产品名称，
此处仅作事实性引用，不代表任何官方背书或关联。

### 交流与反馈

本固件供 **青蛙贴片机** 项目使用与学习交流。问题、建议或改造分享欢迎：

- **Bilibili：@青蛙贴片机**（评论区留言最快）
- 本仓库 **Issue**
