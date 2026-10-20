/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
//#pragma once
//#error "Don't build with import-2.1.x configurations!"
//#error "Use the 'bugfix...' or 'release...' configurations matching your Marlin version."

/**
 * Configuration.h
 *
 * 基本设置包括：
 *
 * - 电子设备类型
 * - 温度传感器类型
 * - 打印机几何结构
 * - 限位开关配置
 * - LCD 控制器
 * - 附加功能
 *
 * 高级设置见 Configuration_adv.h
 */
#define CONFIGURATION_H_VERSION 02010300

//===========================================================================
//============================== 入门指南 ===================================
//===========================================================================

/**
 * 以下是一些有助于配置和校准机器的实用链接：
 *
 * 示例配置：     https://github.com/MarlinFirmware/Configurations/branches/all
 *
 * Průša 计算器：    https://blog.prusaprinters.org/calculator_3416/
 *
 * 校准指南：  https://reprap.org/wiki/Calibration
 *                      https://reprap.org/wiki/Triffid_Hunter%27s_Calibration_Guide
 *                      https://sites.google.com/site/repraplogphase/calibration-of-your-reprap
 *                      https://youtu.be/wAL9d7FgInk
 *
 * 校准件： https://www.thingiverse.com/thing:5573
 *                      https://www.thingiverse.com/thing:1278865
 */

// @section info

// 此构建的作者信息，将在启动和 M115 时打印到主机
#define STRING_CONFIG_H_AUTHOR "(none, default config)" // 修改者信息。
//#define CUSTOM_VERSION_FILE Version.h // 相对于根目录的路径（不带引号）

// @section machine

// 从 boards.h 中选择与你的硬件配置匹配的名称
#ifndef MOTHERBOARD
  #define MOTHERBOARD BOARD_OPULO_LUMEN_REV4
#endif

/**
 * 选择板上用于与主机通信的串口。
 * 这样可以（例如）将无线适配器连接到非默认的端口引脚。
 * 串口 -1 为 USB 模拟串口（如果可用）。
 * 注意：第一个串口（-1 或 0）始终由 Arduino 引导加载程序使用。
 *
 * :[-1, 0, 1, 2, 3, 4, 5, 6, 7]
 */
#define SERIAL_PORT -1

/**
 * 串口波特率
 * 这是所有串口的默认通信速度。
 * 在下方为其他串口设置默认波特率。
 *
 * 250000 在大多数情况下可用，但如果在主机打印期间经常出现丢包，
 * 可以尝试较低的速度。
 * 若要加快 SD 卡文件传输，可尝试最高 1000000。
 *
 * :[2400, 9600, 19200, 38400, 57600, 115200, 250000, 500000, 1000000]
 */
#define BAUDRATE 250000

//#define BAUD_RATE_GCODE     // 启用 G 代码 M575 以设置波特率

/**
 * 选择板上用于与主机通信的第二个串口。
 * 目前以太网 (-2) 仅在 Teensy 4.1 板上受支持。
 * :[-2, -1, 0, 1, 2, 3, 4, 5, 6, 7]
 */
//#define SERIAL_PORT_2 -1
//#define BAUDRATE_2 250000   // :[2400, 9600, 19200, 38400, 57600, 115200, 250000, 500000, 1000000] 启用以覆盖 BAUDRATE

/**
 * 选择板上用于与主机通信的第三个串口。
 * 目前仅支持 AVR、DUE、LPC1768/9 和 STM32/STM32F1
 * :[-1, 0, 1, 2, 3, 4, 5, 6, 7]
 */
//#define SERIAL_PORT_3 1
//#define BAUDRATE_3 250000   // :[2400, 9600, 19200, 38400, 57600, 115200, 250000, 500000, 1000000] 启用以覆盖 BAUDRATE

// 在 AT90USB 设备上启用蓝牙串口
//#define BLUETOOTH

// 显示在 LCD "就绪"消息和信息菜单中的名称
//#define CUSTOM_MACHINE_NAME "3D Printer"

// 打印机的唯一 ID，某些程序用它来区分不同的机器。
// 可自行选择，或使用 https://www.uuidgenerator.net/version4 等服务
//#define MACHINE_UUID "00000000-0000-0000-0000-000000000000"

// @section stepper drivers

/**
 * 步进电机驱动
 *
 * 这些设置允许 Marlin 调整步进电机驱动的时序，并为支持的驱动器
 * 启用高级选项。你也可以在 Configuration_adv.h 中覆盖时序选项。
 *
 * TMC2225 驱动请使用 TMC2208/TMC2208_STANDALONE，TMC2226 驱动请使用 TMC2209/TMC2209_STANDALONE。
 *
 * 选项：A4988, A5984, DRV8825, LV8729, TB6560, TB6600, TMC2100,
 *          TMC2130, TMC2130_STANDALONE, TMC2160, TMC2160_STANDALONE,
 *          TMC2208, TMC2208_STANDALONE, TMC2209, TMC2209_STANDALONE,
 *          TMC26X,  TMC26X_STANDALONE,  TMC2660, TMC2660_STANDALONE,
 *          TMC5130, TMC5130_STANDALONE, TMC5160, TMC5160_STANDALONE
 * :['A4988', 'A5984', 'DRV8825', 'LV8729', 'TB6560', 'TB6600', 'TMC2100', 'TMC2130', 'TMC2130_STANDALONE', 'TMC2160', 'TMC2160_STANDALONE', 'TMC2208', 'TMC2208_STANDALONE', 'TMC2209', 'TMC2209_STANDALONE', 'TMC26X', 'TMC26X_STANDALONE', 'TMC2660', 'TMC2660_STANDALONE', 'TMC5130', 'TMC5130_STANDALONE', 'TMC5160', 'TMC5160_STANDALONE']
 */
#define X_DRIVER_TYPE  TMC2209
#define Y_DRIVER_TYPE  TMC2209
#define Z_DRIVER_TYPE  TMC2209
//#define X2_DRIVER_TYPE A4988
//#define Y2_DRIVER_TYPE A4988
//#define Z2_DRIVER_TYPE A4988
//#define Z3_DRIVER_TYPE A4988
//#define Z4_DRIVER_TYPE A4988
#define I_DRIVER_TYPE  TMC2209
#define J_DRIVER_TYPE  TMC2209
#define K_DRIVER_TYPE  TMC2209
//#define U_DRIVER_TYPE  A4988
//#define V_DRIVER_TYPE  A4988
//#define W_DRIVER_TYPE  A4988
//#define E0_DRIVER_TYPE A4988
//#define E1_DRIVER_TYPE A4988
//#define E2_DRIVER_TYPE A4988
//#define E3_DRIVER_TYPE A4988
//#define E4_DRIVER_TYPE A4988
//#define E5_DRIVER_TYPE A4988
//#define E6_DRIVER_TYPE A4988
//#define E7_DRIVER_TYPE A4988

/**
 * 附加轴设置
 *
 * 为所有会旋转或摆动的轴定义 AXISn_ROTATES。
 * 旋转轴坐标以度表示。
 *
 * AXISn_NAME 定义在（大多数）G 代码命令中引用该轴所用的字母。
 * 按惯例，名称和作用通常为：
 *   'A' : 平行于 X 的旋转轴
 *   'B' : 平行于 Y 的旋转轴
 *   'C' : 平行于 Z 的旋转轴
 *   'U' : 平行于 X 的第二线性轴
 *   'V' : 平行于 Y 的第二线性轴
 *   'W' : 平行于 Z 的第二线性轴
 *
 * 无论这些设置如何，这些轴在内部均命名为 I、J、K、U、V、W。
 */
#ifdef I_DRIVER_TYPE
  #define AXIS4_NAME 'A' // :['A', 'B', 'C', 'U', 'V', 'W']
  #define AXIS4_ROTATES
#endif
#ifdef J_DRIVER_TYPE
  #define AXIS5_NAME 'B' // :['B', 'C', 'U', 'V', 'W']
  #define AXIS5_ROTATES
#endif
#ifdef K_DRIVER_TYPE
  #define AXIS6_NAME 'C' // :['C', 'U', 'V', 'W']
  #define AXIS6_ROTATES
#endif
#ifdef U_DRIVER_TYPE
  #define AXIS7_NAME 'U' // :['U', 'V', 'W']
  //#define AXIS7_ROTATES
#endif
#ifdef V_DRIVER_TYPE
  #define AXIS8_NAME 'V' // :['V', 'W']
  //#define AXIS8_ROTATES
#endif
#ifdef W_DRIVER_TYPE
  #define AXIS9_NAME 'W' // :['W']
  //#define AXIS9_ROTATES
#endif

// @section extruder

// 定义挤出机的数量
// :[0, 1, 2, 3, 4, 5, 6, 7, 8]
#define EXTRUDERS 0

// 一般预期的耗材直径（1.75、2.85、3.0 等）。用于体积挤出、耗材宽度传感器等。
#define DEFAULT_NOMINAL_FILAMENT_DIA 1.75

// 用于 Cyclops 或任何共用单个喷嘴的"多挤出机"配置。
//#define SINGLENOZZLE

// 换工具时保存并恢复温度和风扇转速。
// 用 M104/106/109 T... 为未选中的工具设置待机值。
#if ENABLED(SINGLENOZZLE)
  //#define SINGLENOZZLE_STANDBY_TEMP
  //#define SINGLENOZZLE_STANDBY_FAN
#endif

// @section multi-material

/**
 * 多材料单元（MMU）
 * 设置为以下预定义模型之一：
 *
 *   PRUSA_MMU1           : Průša MMU1（"多路复用器"版本）
 *   PRUSA_MMU2           : Průša MMU2
 *   PRUSA_MMU2S          : Průša MMU2S（需要带运动传感器的 MK3S 挤出机，EXTRUDERS = 5）
 *   EXTENDABLE_EMU_MMU2  : 可配置耗材数量的 MMU（ERCF、SMuFF 或类似的 Průša MMU2 兼容固件）
 *   EXTENDABLE_EMU_MMU2S : 可配置耗材数量的 MMUS（ERCF、SMuFF 或类似的 Průša MMU2 兼容固件）
 *
 * 需要 NOZZLE_PARK_FEATURE 以在 MMU 单元故障时停泊打印头。
 * 其他选项见 Configuration_adv.h。
 * :["PRUSA_MMU1", "PRUSA_MMU2", "PRUSA_MMU2S", "EXTENDABLE_EMU_MMU2", "EXTENDABLE_EMU_MMU2S"]
 */
//#define MMU_MODEL PRUSA_MMU2

// 使用单个步进电机的双挤出机
//#define SWITCHING_EXTRUDER
#if ENABLED(SWITCHING_EXTRUDER)
  #define SWITCHING_EXTRUDER_SERVO_NR 0
  #define SWITCHING_EXTRUDER_SERVO_ANGLES { 0, 90 } // E0、E1[, E2, E3] 的角度
  #if EXTRUDERS > 3
    #define SWITCHING_EXTRUDER_E23_SERVO_NR 1
  #endif
#endif

// 通过撞击工具头来切换挤出机。需要 EVENT_GCODE_TOOLCHANGE_#。
//#define MECHANICAL_SWITCHING_EXTRUDER

/**
 * 使用舵机升降一个（或两个）喷嘴的双喷嘴。
 * 可与 SWITCHING_EXTRUDER 组合使用。
 */
//#define SWITCHING_NOZZLE
#if ENABLED(SWITCHING_NOZZLE)
  #define SWITCHING_NOZZLE_SERVO_NR 0
  //#define SWITCHING_NOZZLE_E1_SERVO_NR 1          // 若使用两个舵机，此为第二个的编号
  #define SWITCHING_NOZZLE_SERVO_ANGLES { 0, 90 }   // E0、E1（单舵机）或降下/升起（双舵机）的角度
  #define SWITCHING_NOZZLE_SERVO_DWELL 2500         // 等待舵机完成物理动作的驻留时间
#endif

// 通过撞击工具头来切换喷嘴。需要 EVENT_GCODE_TOOLCHANGE_#。
//#define MECHANICAL_SWITCHING_NOZZLE

/**
 * 两个独立的 X 滑座，其挤出机通过电磁螺线管对接机构
 * 连接到运动部件。需要 SOL1_PIN 和 SOL2_PIN。
 */
//#define PARKING_EXTRUDER

/**
 * 两个独立的 X 滑座，其挤出机通过磁性对接机构
 * （仅靠运动、无螺线管）连接到运动部件
 *
 * 项目   : https://www.thingiverse.com/thing:3080893
 * 动作演示 : https://youtu.be/0xCEiG9VS3k
 *             https://youtu.be/Bqbcs0CU2FE
 */
//#define MAGNETIC_PARKING_EXTRUDER

#if EITHER(PARKING_EXTRUDER, MAGNETIC_PARKING_EXTRUDER)

  #define PARKING_EXTRUDER_PARKING_X { -78, 184 }     // 挤出机停泊的 X 位置
  #define PARKING_EXTRUDER_GRAB_DISTANCE 1            // (mm) 超出停泊点以抓取挤出机的移动距离

  #if ENABLED(PARKING_EXTRUDER)

    #define PARKING_EXTRUDER_SOLENOIDS_INVERT           // 若启用，通电时电磁铁不会磁化
    #define PARKING_EXTRUDER_SOLENOIDS_PINS_ACTIVE LOW  // LOW 或 HIGH 电平信号为线圈供电
    #define PARKING_EXTRUDER_SOLENOIDS_DELAY 250        // (ms) 磁场建立延时。为 0 或未定义时无延时。
    //#define MANUAL_SOLENOID_CONTROL                   // 使用 M380 S / M381 手动控制对接电磁铁

  #elif ENABLED(MAGNETIC_PARKING_EXTRUDER)

    #define MPE_FAST_SPEED      9000      // (mm/min) 到达最后距离点之前的移动速度
    #define MPE_SLOW_SPEED      4500      // (mm/min) 最后一段距离停泊并对接的速度
    #define MPE_TRAVEL_DISTANCE   10      // (mm) 最后距离点
    #define MPE_COMPENSATION       0      // 偏移补偿 -1、0、1（倍率），仅用于对接

  #endif

#endif

/**
 * 切换式工具头
 *
 * 支持可更换、可停泊的工具头，例如 E3D Tool Changer。
 * 工具头由舵机锁定。
 */
//#define SWITCHING_TOOLHEAD

/**
 * 磁性切换工具头
 *
 * 支持可更换、可停泊的工具头，采用磁性对接机构，
 * 仅靠运动、无需舵机。
 */
//#define MAGNETIC_SWITCHING_TOOLHEAD

/**
 * 电磁切换工具头
 *
 * 适用于 CoreXY / HBot 运动学的停泊。
 * 工具头停泊在边缘并由电磁铁固定。
 * 支持两个以上工具头。参见 https://youtu.be/JolbsAKTKf4
 */
//#define ELECTROMAGNETIC_SWITCHING_TOOLHEAD

#if ANY(SWITCHING_TOOLHEAD, MAGNETIC_SWITCHING_TOOLHEAD, ELECTROMAGNETIC_SWITCHING_TOOLHEAD)
  #define SWITCHING_TOOLHEAD_Y_POS          235         // (mm) 工具头停泊座的 Y 位置
  #define SWITCHING_TOOLHEAD_Y_SECURITY      10         // (mm) Y 轴安全距离
  #define SWITCHING_TOOLHEAD_Y_CLEAR         60         // (mm) X 轴无阻碍时距停泊座的最小距离
  #define SWITCHING_TOOLHEAD_X_POS          { 215, 0 }  // (mm) 挤出机停泊的 X 位置
  #if ENABLED(SWITCHING_TOOLHEAD)
    #define SWITCHING_TOOLHEAD_SERVO_NR       2         // 舵机接口的编号
    #define SWITCHING_TOOLHEAD_SERVO_ANGLES { 0, 180 }  // (degrees) 锁定/解锁的角度
  #elif ENABLED(MAGNETIC_SWITCHING_TOOLHEAD)
    #define SWITCHING_TOOLHEAD_Y_RELEASE      5         // (mm) Y 轴安全距离
    #define SWITCHING_TOOLHEAD_X_SECURITY   { 90, 150 } // (mm) X 轴安全距离 (T0,T1)
    //#define PRIME_BEFORE_REMOVE                       // 从停泊座释放前先预挤喷嘴
    #if ENABLED(PRIME_BEFORE_REMOVE)
      #define SWITCHING_TOOLHEAD_PRIME_MM           20  // (mm)   挤出机预挤长度
      #define SWITCHING_TOOLHEAD_RETRACT_MM         10  // (mm)   预挤后回抽的长度
      #define SWITCHING_TOOLHEAD_PRIME_FEEDRATE    300  // (mm/min) 挤出机预挤进给速度
      #define SWITCHING_TOOLHEAD_RETRACT_FEEDRATE 2400  // (mm/min) 挤出机回抽进给速度
    #endif
  #elif ENABLED(ELECTROMAGNETIC_SWITCHING_TOOLHEAD)
    #define SWITCHING_TOOLHEAD_Z_HOP          2         // (mm) 切换时 Z 轴抬升高度
  #endif
#endif

/**
 * "混色挤出机"
 *   - 新增 G 代码 M163 和 M164，用于设置并"提交"当前混合系数。
 *   - 扩展步进例程，按混合比例移动多个步进电机。
 *   - 可选支持 Repetier 固件的 'M164 S<index>'，提供虚拟工具。
 *   - 本实现最多支持两个混色挤出机。
 *   - 启用 DIRECT_MIXING_IN_G1 可在 G1 中混色（来自 Pia Taubert 的参考实现）。
 */
//#define MIXING_EXTRUDER
#if ENABLED(MIXING_EXTRUDER)
  #define MIXING_STEPPERS 2        // 混色挤出机中的步进电机数量
  #define MIXING_VIRTUAL_TOOLS 16  // 通过 M163 和 M164 使用虚拟工具方法
  //#define DIRECT_MIXING_IN_G1    // 允许在 G1 移动命令中使用 ABCDHI 混合系数
  //#define GRADIENT_MIX           // 支持 M166 和 LCD 的渐变混色
  //#define MIXING_PRESETS         // 为 2 或 3 个 MIXING_STEPPERS 分配 8 个默认 V-tool 预设
  #if ENABLED(GRADIENT_MIX)
    //#define GRADIENT_VTOOL       // 添加 M166 T 以将 V-tool 索引用作渐变别名
  #endif
#endif

// 挤出机的偏移量（若使用多个挤出机且依赖固件在切换时定位，请取消注释）。
// 0 号挤出机热端（默认挤出机）的偏移量必须为 X=0, Y=0。
// 其他热端的偏移量为其到 0 号挤出机热端的距离。
//#define HOTEND_OFFSET_X { 0.0, 20.00 } // (mm) 每个喷嘴的相对 X 偏移
//#define HOTEND_OFFSET_Y { 0.0, 5.00 }  // (mm) 每个喷嘴的相对 Y 偏移
//#define HOTEND_OFFSET_Z { 0.0, 0.00 }  // (mm) 每个喷嘴的相对 Z 偏移

// @section psu control

/**
 * 电源控制
 *
 * 启用该选项并将电源连接到 PS_ON_PIN。
 * 指定电源是高电平有效还是低电平有效。
 */
//#define PSU_CONTROL
//#define PSU_NAME "Power Supply"

#if ENABLED(PSU_CONTROL)
  //#define MKS_PWC                 // 使用 MKS PWC 附加模块
  //#define PS_OFF_CONFIRM          // 断电时显示确认对话框
  //#define PS_OFF_SOUND            // 断电时蜂鸣 1 秒
  #define PSU_ACTIVE_STATE LOW      // ATX 电源设为 'LOW'，X-Box 设为 'HIGH'

  //#define PSU_DEFAULT_OFF               // 保持断电，直到用 M80 直接开启
  //#define PSU_POWERUP_DELAY      250    // (ms) 电源预热到满功率的延时
  //#define LED_POWEROFF_TIMEOUT 10000    // (ms) 断电后延时这么长时间再关闭 LED

  //#define POWER_OFF_TIMER               // 启用 M81 D<seconds> 在延时后断电
  //#define POWER_OFF_WAIT_FOR_COOLDOWN   // 启用 M81 S，仅在冷却完成后断电

  //#define PSU_POWERUP_GCODE  "M355 S1"  // 通电后运行的 G 代码（例如打开机箱灯）
  //#define PSU_POWEROFF_GCODE "M355 S0"  // 断电前运行的 G 代码（例如关闭机箱灯）

  //#define AUTO_POWER_CONTROL      // 启用 PS_ON 引脚的自动控制
  #if ENABLED(AUTO_POWER_CONTROL)
    #define AUTO_POWER_FANS         // 风扇需要供电时开启电源
    #define AUTO_POWER_E_FANS
    #define AUTO_POWER_CONTROLLERFAN
    #define AUTO_POWER_CHAMBER_FAN
    #define AUTO_POWER_COOLER_FAN
    #define POWER_TIMEOUT              30 // (s) 机器空闲达到该时长后断电
    //#define POWER_OFF_DELAY          60 // (s) M81 命令后的断电延时。可让风扇多运行一段时间。
  #endif
  #if EITHER(AUTO_POWER_CONTROL, POWER_OFF_WAIT_FOR_COOLDOWN)
    //#define AUTO_POWER_E_TEMP        50 // (°C) 任一挤出机超过此温度时开启电源
    //#define AUTO_POWER_CHAMBER_TEMP  30 // (°C) 腔体超过此温度时开启电源
    //#define AUTO_POWER_COOLER_TEMP   26 // (°C) 冷却器超过此温度时开启电源
  #endif
#endif

//===========================================================================
//=============================== 温度设置 ==================================
//===========================================================================
// @section temperature

/**
 * --正常情况为 4.7kΩ 上拉电阻！-- 热端传感器可使用 1kΩ 上拉，但需使用正确的电阻和温度表
 *
 * 可用的温度传感器：
 *
 *  SPI RTD/热电偶板 - 重要：请阅读下方的注意事项！
 *  -------
 *    -5 : MAX31865 配 Pt100/Pt1000，2/3/4 线制（仅用于传感器 0-1）
 *                  注意：必须在下方取消注释/设置 MAX31865_*_OHMS_n 定义。
 *    -3 : MAX31855 配热电偶，-200°C 至 +700°C（仅用于传感器 0-1）
 *    -2 : MAX6675  配热电偶，0°C 至 +700°C（仅用于传感器 0-1）
 *
 *  注意：对于每个使用 SPI 热电偶的 TEMP_SENSOR_n，请确保在引脚文件中设置了 TEMP_n_CS_PIN。默认情况下，
 *        使用默认串行总线上的硬件 SPI。如果还设置了 TEMP_n_SCK_PIN 和 TEMP_n_MISO_PIN，
 *        则会改用这些端口上的软件 SPI。可以在 Configuration_adv.h 文件中强制使用默认总线上的硬件 SPI。
 *        目前尚不支持为各传感器使用独立的硬件 SPI 总线。
 *
 *  模拟热电偶板
 *  -------
 *    -4 : AD8495 配热电偶
 *    -1 : AD595  配热电偶
 *
 *  模拟热敏电阻 - 4.7kΩ 上拉 - 常规
 *  -------
 *     1 : 100kΩ  EPCOS - EPCOS 热敏电阻的最佳选择
 *   331 : 100kΩ  同 #1，但按 3.3V 缩放，用于 MEGA
 *   332 : 100kΩ  同 #1，但按 3.3V 缩放，用于 DUE
 *     2 : 200kΩ  ATC Semitec 204GT-2
 *   202 : 200kΩ  Copymaster 3D
 *     3 : ???Ω   Mendel-parts 热敏电阻
 *     4 : 10kΩ   通用热敏电阻 !! 切勿用于热端 - 高温下分辨率很差 !!
 *     5 : 100kΩ  ATC Semitec 104GT-2/104NT-4-R025H42G - 用于 ParCan、J-Head、E3D、SliceEngineering，300°C
 *   501 : 100kΩ  Zonestar - Tronxy X3A
 *   502 : 100kΩ  Zonestar - 用于 Zonestar Průša P802M 的热床
 *   503 : 100kΩ  Zonestar (Z8XM2) 热床热敏电阻
 *   504 : 100kΩ  Zonestar P802QR2 (Part# QWG-104F-B3950) 热端热敏电阻
 *   505 : 100kΩ  Zonestar P802QR2 (Part# QWG-104F-3950) 热床热敏电阻
 *   512 : 100kΩ  RPW-Ultra 热端
 *     6 : 100kΩ  EPCOS - 不如 #1 精确（使用福禄克热电偶制作）
 *     7 : 100kΩ  Honeywell 135-104LAG-J01
 *    71 : 100kΩ  Honeywell 135-104LAF-J01
 *     8 : 100kΩ  Vishay 0603 SMD NTCS0603E3104FXT
 *     9 : 100kΩ  GE Sensing AL03006-58.2K-97-G1
 *    10 : 100kΩ  RS PRO 198-961
 *    11 : 100kΩ  Keenovo 交流硅胶加热垫、大多数 Wanhao i3 机型 - beta 3950，1%
 *    12 : 100kΩ  Vishay 0603 SMD NTCS0603E3104FXT (#8) - 针对 Makibox 热床校准
 *    13 : 100kΩ  Hisens 最高 300°C - 用于 "Simple ONE" 和 "All In ONE" 热端 - beta 3950，1%
 *    15 : 100kΩ  针对 JGAurora A5 热端校准
 *    18 : 200kΩ  ATC Semitec 204GT-2 Dagoma.Fr - MKS_Base_DKU001327
 *    22 : 100kΩ  GTM32 Pro vB - 热端 - 4.7kΩ 上拉至 3.3V，220Ω 接模拟输入
 *    23 : 100kΩ  GTM32 Pro vB - 热床 - 4.7kΩ 上拉至 3.3v，220Ω 接模拟输入
 *    30 : 100kΩ  Kis3d 硅胶加热垫 200W/300W，配 6mm 精密铸造板 (EN AW 5083) NTC100K - beta 3950
 *    60 : 100kΩ  Maker's Tool Works Kapton 热床热敏电阻 - beta 3950
 *    61 : 100kΩ  Formbot/Vivedino 350°C 热敏电阻 - beta 3950
 *    66 : 4.7MΩ  Dyze Design / Trianglelab T-D500 500°C 高温热敏电阻
 *    67 : 500kΩ  SliceEngineering 450°C 热敏电阻
 *    68 : Dyze Design 的 PT100 放大板
 *    70 : 100kΩ  bq Hephestos 2
 *    75 : 100kΩ  通用硅胶加热垫，配 NTC100K MGB18-104F39050L32
 *  2000 : 100kΩ  Ultimachine Rambo TDK NTCG104LH104KT1 NTC100K 主板热敏电阻
 *
 *  模拟热敏电阻 - 1kΩ 上拉 - 非典型，需将 4.7kΩ 上拉电阻换成 1kΩ。
 *  -------                           （但精度更高，PID 更稳定）
 *    51 : 100kΩ  EPCOS (1kΩ 上拉)
 *    52 : 200kΩ  ATC Semitec 204GT-2 (1kΩ 上拉)
 *    55 : 100kΩ  ATC Semitec 104GT-2 - 用于 ParCan 和 J-Head（1kΩ 上拉）
 *
 *  模拟热敏电阻 - 10kΩ 上拉 - 非典型
 *  -------
 *    99 : 100kΩ  见于部分 Wanhao i3 机型，使用 10kΩ 上拉电阻
 *
 *  模拟 RTD（Pt100/Pt1000）
 *  -------
 *   110 : Pt100  配 1kΩ 上拉（非典型）
 *   147 : Pt100  配 4.7kΩ 上拉
 *  1010 : Pt1000 配 1kΩ 上拉（非典型）
 *  1022 : Pt1000 配 2.2kΩ 上拉
 *  1047 : Pt1000 配 4.7kΩ 上拉 (E3D)
 *    20 : Pt100  配 Ultimainboard V2.x 电路，主板 ADC 参考电压 = INA826 放大板供电电压。
 *                注意：(1) 必须使用无上拉的 ADC 输入。(2) 部分 INA826 放大器在 3.3V 下工作不可靠，建议改用传感器 147、110 或 21。
 *    21 : Pt100  配 Ultimainboard V2.x 电路，3.3V ADC 参考电压（STM32、LPC176x 等），INA826 放大板供电为 5V。
 *                注意：ADC 引脚不耐 5V。不推荐使用，因为超过 500°C 时可能损坏 CPU。
 *   201 : Pt100  配 Overlord 电路，与 Ultimainboard V2.x 类似
 *
 *  自定义/虚拟/其他温度传感器
 *  ------
 *     0 : 未使用
 *  1000 : 自定义 - 在 Configuration_adv.h 中指定参数
 *
 *   !!! 仅用于测试或开发。切勿用于生产机器。!!!
 *   998 : 虚拟温度表，始终读数为 25°C 或下方定义的温度。
 *   999 : 虚拟温度表，始终读数为 100°C 或下方定义的温度。
 *
 */
#define TEMP_SENSOR_0 0
#define TEMP_SENSOR_1 0
#define TEMP_SENSOR_2 0
#define TEMP_SENSOR_3 0
#define TEMP_SENSOR_4 0
#define TEMP_SENSOR_5 0
#define TEMP_SENSOR_6 0
#define TEMP_SENSOR_7 0
#define TEMP_SENSOR_BED 0
#define TEMP_SENSOR_PROBE 0
#define TEMP_SENSOR_CHAMBER 0
#define TEMP_SENSOR_COOLER 0
#define TEMP_SENSOR_BOARD 0
#define TEMP_SENSOR_REDUNDANT 0

// 虚拟热敏电阻的恒定温度读数，配合 998 和 999 使用
#define DUMMY_THERMISTOR_998_VALUE  25
#define DUMMY_THERMISTOR_999_VALUE 100

// 在 TEMP_SENSOR_0 / 1 上使用 MAX31865 传感器 (-5) 时的电阻值
#if TEMP_SENSOR_IS_MAX_TC(0)
  #define MAX31865_SENSOR_OHMS_0      100 // (Ω) 通常为 100 或 1000（PT100 或 PT1000）
  #define MAX31865_CALIBRATION_OHMS_0 430 // (Ω) Adafruit PT100 通常为 430；Adafruit PT1000 为 4300
#endif
#if TEMP_SENSOR_IS_MAX_TC(1)
  #define MAX31865_SENSOR_OHMS_1      100
  #define MAX31865_CALIBRATION_OHMS_1 430
#endif
#if TEMP_SENSOR_IS_MAX_TC(2)
  #define MAX31865_SENSOR_OHMS_2      100
  #define MAX31865_CALIBRATION_OHMS_2 430
#endif

#if HAS_E_TEMP_SENSOR
  #define TEMP_RESIDENCY_TIME         10  // (seconds) M109 中等待热端"稳定"的时间
  #define TEMP_WINDOW                  1  // (°C) 判定"达到温度"计时器的温度接近度
  #define TEMP_HYSTERESIS              3  // (°C) 视为"足够接近"目标的温度接近度
#endif

#if TEMP_SENSOR_BED
  #define TEMP_BED_RESIDENCY_TIME     10  // (seconds) M190 中等待热床"稳定"的时间
  #define TEMP_BED_WINDOW              1  // (°C) 判定"达到温度"计时器的温度接近度
  #define TEMP_BED_HYSTERESIS          3  // (°C) 视为"足够接近"目标的温度接近度
#endif

#if TEMP_SENSOR_CHAMBER
  #define TEMP_CHAMBER_RESIDENCY_TIME 10  // (seconds) M191 中等待腔体"稳定"的时间
  #define TEMP_CHAMBER_WINDOW          1  // (°C) 判定"达到温度"计时器的温度接近度
  #define TEMP_CHAMBER_HYSTERESIS      3  // (°C) 视为"足够接近"目标的温度接近度
#endif

/**
 * 冗余温度传感器（TEMP_SENSOR_REDUNDANT）
 *
 * 用一个温度传感器为另一路读数提供冗余。选择一个未使用的温度传感器，
 * 以及希望为其提供冗余的另一个传感器。如果两个热敏电阻的读数相差
 * TEMP_SENSOR_REDUNDANT_MAX_DIFF (°C)，打印将被中止。无论选中哪个传感器，
 * 其正常功能都会被禁用；例如选择热床传感器 (-1) 将禁用热床加热/监测。
 *
 * 选择源/目标时可使用：COOLER、PROBE、BOARD、CHAMBER、BED、E0、E1、E2、E3、E4、E5、E6、E7
 */
#if TEMP_SENSOR_REDUNDANT
  #define TEMP_SENSOR_REDUNDANT_SOURCE    E1  // 提供冗余读数的传感器。
  #define TEMP_SENSOR_REDUNDANT_TARGET    E0  // 被提供冗余读数的传感器。
  #define TEMP_SENSOR_REDUNDANT_MAX_DIFF  10  // (°C) 触发中止打印的温差。
#endif

// 低于此温度时加热器将被关闭，
// 因为这可能表明热敏电阻线缆断裂。
#define HEATER_0_MINTEMP   5
#define HEATER_1_MINTEMP   5
#define HEATER_2_MINTEMP   5
#define HEATER_3_MINTEMP   5
#define HEATER_4_MINTEMP   5
#define HEATER_5_MINTEMP   5
#define HEATER_6_MINTEMP   5
#define HEATER_7_MINTEMP   5
#define BED_MINTEMP        5
#define CHAMBER_MINTEMP    5

// 高于此温度时加热器将被关闭。
// 这可以保护元件免受过热，但不能防止短路和故障。
// （热敏电阻短路/故障保护请使用 MINTEMP。）
#define HEATER_0_MAXTEMP 275
#define HEATER_1_MAXTEMP 275
#define HEATER_2_MAXTEMP 275
#define HEATER_3_MAXTEMP 275
#define HEATER_4_MAXTEMP 275
#define HEATER_5_MAXTEMP 275
#define HEATER_6_MAXTEMP 275
#define HEATER_7_MAXTEMP 275
#define BED_MAXTEMP      150
#define CHAMBER_MAXTEMP  60

/**
 * 温度过冲
 * 在升温（及打印）过程中，温度经常会"过冲"目标值许多度
 * （尤其在 PID 调参之前）。目标温度设置得离 MAXTEMP 太近，
 * 必然触发 MAXTEMP 停机！使用这些值可以禁止设置过于接近 MAXTEMP 的温度。
 */
#define HOTEND_OVERSHOOT 15   // (°C) 禁止设置超过 MAXTEMP - OVERSHOOT 的温度
#define BED_OVERSHOOT    10   // (°C) 禁止设置超过 MAXTEMP - OVERSHOOT 的温度
#define COOLER_OVERSHOOT  2   // (°C) 禁止设置与限值相差小于 OVERSHOOT 的温度

//===========================================================================
//================================ PID 设置 =================================
//===========================================================================

// @section hotend temp

// 启用 PIDTEMP 进行 PID 控制，或启用 MPCTEMP 进行预测模型
// 温度控制。两者都禁用则为开关式加热。
#define PIDTEMP          // PID 调参指南见 https://reprap.org/wiki/PID_Tuning
//#define MPCTEMP        // ** 实验性功能 **

#define BANG_MAX 255     // 开关模式下限制喷嘴电流；255=满电流
#define PID_MAX BANG_MAX // PID 生效时限制喷嘴电流（见下方 PID_FUNCTIONAL_RANGE）；255=满电流
#define PID_K1 0.95      // 任意 PID 循环内的平滑因子

#if ENABLED(PIDTEMP)
  //#define PID_DEBUG             // 向串口打印 PID 调试数据。使用 'M303 D' 切换开关。
  //#define PID_PARAMS_PER_HOTEND // 为每个挤出机使用独立的 PID 参数（挤出机不匹配时有用）
                                  // 用 G 代码设置/获取：M301 E[挤出机编号, 0-2]

  #if ENABLED(PID_PARAMS_PER_HOTEND)
    // 根据你的配置，此处最多为每个热端指定一个值。
    // 若值较少，最后一个值将应用于其余热端。
    #define DEFAULT_Kp_LIST {  22.20,  22.20 }
    #define DEFAULT_Ki_LIST {   1.08,   1.08 }
    #define DEFAULT_Kd_LIST { 114.00, 114.00 }
  #else
    #define DEFAULT_Kp  22.20
    #define DEFAULT_Ki   1.08
    #define DEFAULT_Kd 114.00
  #endif
#endif

/**
 * 热端的模型预测控制（MPC）
 *
 * 用热端的物理模型来控制温度。配置得当时，
 * 其响应性和稳定性优于 PID，并且不再需要
 * PID_EXTRUSION_SCALING 和 PID_FAN_SCALING。使用 M306 T 自动调谐模型。
 * @section mpctemp
 */
#if ENABLED(MPCTEMP)
  //#define MPC_AUTOTUNE                              // 包含 MPC 自动调谐的方法（约占用 5664-5882 字节闪存）
  //#define MPC_EDIT_MENU                             // 在"高级设置"菜单中添加 MPC 编辑。约占用 1300 字节闪存
  //#define MPC_AUTOTUNE_MENU                         // 在"高级设置"菜单中添加 MPC 自动调谐。约占用 350 字节闪存

  #define MPC_MAX BANG_MAX                            // (0..255) MPC 生效时喷嘴的电流。
  #define MPC_HEATER_POWER { 40.0f }                  // (W) 加热棒功率。

  #define MPC_INCLUDE_FAN                             // 是否对风扇转速建模？

  // 由 M306 测得的物理常数
  #define MPC_BLOCK_HEAT_CAPACITY { 16.7f }           // (J/K) 加热块热容。
  #define MPC_SENSOR_RESPONSIVENESS { 0.22f }         // (K/s per ∆K) 传感器温度相对加热块的变化率。
  #define MPC_AMBIENT_XFER_COEFF { 0.068f }           // (W/K) 风扇关闭时加热块到室内空气的传热系数。
  #if ENABLED(MPC_INCLUDE_FAN)
    #define MPC_AMBIENT_XFER_COEFF_FAN255 { 0.097f }  // (W/K) 风扇全速时加热块到室内空气的传热系数。
  #endif

  // 对于一个风扇配多个热端的情况，MPC 需要知道如何应用风扇冷却效果。
  #if ENABLED(MPC_INCLUDE_FAN)
    //#define MPC_FAN_0_ALL_HOTENDS
    //#define MPC_FAN_0_ACTIVE_HOTEND
  #endif

  #define FILAMENT_HEAT_CAPACITY_PERMM { 5.6e-3f }    // 1.75mm PLA 为 0.0056 J/K/mm（2.85mm PLA 为 0.0149 J/K/mm）。
  //#define FILAMENT_HEAT_CAPACITY_PERMM { 3.6e-3f }  // 1.75mm PETG 为 0.0036 J/K/mm（2.85mm PETG 为 0.0094 J/K/mm）。

  // 高级选项
  #define MPC_SMOOTHING_FACTOR 0.5f                   // (0.0...1.0) 温度传感器噪声较大时可能需要更低的值以保持稳定。
  #define MPC_MIN_AMBIENT_CHANGE 1.0f                 // (K/s) 修正模型误差时建模的环境温度变化率。
  #define MPC_STEADYSTATE 0.5f                        // (K/s) 强制执行稳态逻辑的温度变化率。

  #define MPC_TUNING_POS { X_CENTER, Y_CENTER, 1.0f } // (mm) M306 自动调谐位置，理想为第一层高度时的热床中心。
  #define MPC_TUNING_END_Z 10.0f                      // (mm) M306 自动调谐结束时的 Z 位置。
#endif

//===========================================================================
//======================== PID > 热床温度控制 ===============================
//===========================================================================

/**
 * 热床 PID 加热
 *
 * 若启用此选项，请在下方设置 PID 常数。
 * 若禁用此选项，将使用开关式控制，BED_LIMIT_SWITCHING 可启用滞回。
 *
 * PID 频率将与挤出机 PWM 相同。
 * 若 PID_dT 为默认值且适合你的硬件/配置，即 7.689Hz，
 * 这对于驱动阻性负载的方波来说没问题，且不会显著
 * 影响 FET 发热。这对通过 Fotek SSR-10DA 固态继电器驱动 250W
 * 加热器同样适用。如果你的配置与此差别很大且你不了解
 * 相关问题，请在他人验证你的硬件可用之前不要使用热床 PID。
 * @section bed temp
 */
//#define PIDTEMPBED

//#define BED_LIMIT_SWITCHING

/**
 * 热床最大功率
 * 适用于所有热床控制方式（PID、开关式、带滞回的开关式）。
 * 设为小于 255 的任何值时，会对热床启用一种类似分压器的 PWM，
 * 所以除非你能接受热床上的 PWM，否则不要使用。（见启用 PIDTEMPBED 的说明）
 */
#define MAX_BED_POWER 255 // 限制热床占空比；255=满电流

#if ENABLED(PIDTEMPBED)
  //#define MIN_BED_POWER 0
  //#define PID_BED_DEBUG // 向串口打印热床 PID 调试数据。

  // 120V 250W 硅胶加热垫，4mm 硼硅玻璃（MendelMax 1.5+）
  // 由 FOPDT 模型得出 - kp=.39 Tp=405 Tdead=66，Tc 设为 79.2，激进系数 .15（对比 .1、1、10）
  #define DEFAULT_bedKp 10.00
  #define DEFAULT_bedKi .023
  #define DEFAULT_bedKd 305.4

  // 请自行整定："M303 E-1 C8 S90" 在热床 90 摄氏度下运行 8 个周期的自动调谐。
#endif // PIDTEMPBED

//===========================================================================
//======================== PID > 腔体温度控制 ===============================
//===========================================================================

/**
 * 腔体 PID 加热
 *
 * 若启用此选项，请在下方设置 PID 常数。
 * 若禁用此选项，将使用开关式控制，CHAMBER_LIMIT_SWITCHING 可启用
 * 滞回。
 *
 * PID 频率将与挤出机 PWM 相同。
 * 若 PID_dT 为默认值且适合你的硬件/配置，即 7.689Hz，
 * 这对于驱动阻性负载的方波来说没问题，且不会显著
 * 影响 FET 发热。这对通过 Fotek SSR-10DA 固态继电器驱动 200W
 * 加热器同样适用。如果你的配置与此差别很大且你不了解
 * 相关问题，请在他人验证你的硬件可用之前不要使用腔体 PID。
 * @section chamber temp
 */
//#define PIDTEMPCHAMBER
//#define CHAMBER_LIMIT_SWITCHING

/**
 * 腔体最大功率
 * 适用于所有腔体控制方式（PID、开关式、带滞回的开关式）。
 * 设为小于 255 的任何值时，会对腔体加热器启用一种类似分压器的 PWM，
 * 所以除非你能接受加热器上的 PWM，否则不要使用。（见启用 PIDTEMPCHAMBER 的说明）
 */
#define MAX_CHAMBER_POWER 255 // 限制腔体加热器占空比；255=满电流

#if ENABLED(PIDTEMPCHAMBER)
  #define MIN_CHAMBER_POWER 0
  //#define PID_CHAMBER_DEBUG // 向串口打印腔体 PID 调试数据。

  // Lasko "MyHeat Personal Heater"（200W）改装 Fotek SSR-10DA，仅控制加热元件，
  // 并放置在创想三维打印机的小型围帐内。
  //
  #define DEFAULT_chamberKp 37.04
  #define DEFAULT_chamberKi 1.40
  #define DEFAULT_chamberKd 655.17
  // M309 P37.04 I1.04 D655.17

  // 请自行整定："M303 E-2 C8 S50" 在腔体 50 摄氏度下运行 8 个周期的自动调谐。
#endif // PIDTEMPCHAMBER

#if ANY(PIDTEMP, PIDTEMPBED, PIDTEMPCHAMBER)
  //#define PID_OPENLOOP          // 将 PID 置于开环。M104/M140 设置 0 到 PID_MAX 的输出功率
  //#define SLOW_PWM_HEATERS      // 极低频率的 PWM（约 0.125Hz=8s），最小状态时间约 1s，适用于由继电器驱动的加热器
  #define PID_FUNCTIONAL_RANGE 10 // 若目标温度与实际温度之差
                                  // 大于 PID_FUNCTIONAL_RANGE，则 PID 将被关闭，加热器将被设为最小/最大。

  //#define PID_EDIT_MENU         // 在"高级设置"菜单中添加 PID 编辑。约占用 700 字节闪存
  //#define PID_AUTOTUNE_MENU     // 在"高级设置"菜单中添加 PID 自动调谐。约占用 250 字节闪存
#endif

// @section safety

/**
 * 温度低于 EXTRUDE_MINTEMP 时禁止挤出。
 * 可添加 M302 设置最低挤出温度，和/或开启、
 * 关闭冷挤出保护。
 *
 * *** 强烈建议保持此选项启用！***
 */
#define PREVENT_COLD_EXTRUSION
#define EXTRUDE_MINTEMP 170

/**
 * 防止单次挤出长度超过 EXTRUDE_MAXLENGTH。
 * 注意：对于 Bowden（远程）挤出机，请将此值设得足够大，以便进行装料/卸料。
 */
#define PREVENT_LENGTHY_EXTRUDE
#define EXTRUDE_MAXLENGTH 200

//===========================================================================
//============================ 热失控保护 ===================================
//===========================================================================

/**
 * 热保护为你的打印机提供防止损坏和火灾的额外保障。
 * Marlin 始终包含安全的最小/最大温度范围，
 * 可防止热敏电阻线缆断裂或断开造成的问题。
 *
 * 问题所在：如果热敏电阻脱落，它会报告远低于实际值的
 * 室温温度，固件将持续
 * 开启加热器。
 *
 * 如果出现"Thermal Runaway"（热失控）或"Heating failed"（加热失败）错误，
 * 可在 Configuration_adv.h 中调整相关细节。
 */

#define THERMAL_PROTECTION_HOTENDS // 为所有挤出机启用热保护
#define THERMAL_PROTECTION_BED     // 为热床启用热保护
#define THERMAL_PROTECTION_CHAMBER // 为加热腔体启用热保护
#define THERMAL_PROTECTION_COOLER  // 为激光冷却启用热保护

//===========================================================================
//=============================== 机械设置 ==================================
//===========================================================================

// @section machine

// 启用下方选项之一以使用 CoreXY、CoreXZ 或 CoreYZ 运动学，
// 可为常规顺序或反转顺序
//#define COREXY
//#define COREXZ
//#define COREYZ
//#define COREYX
//#define COREZX
//#define COREZY
//#define MARKFORGED_XY  // MarkForged。参见 https://reprap.org/forum/read.php?152,504042
//#define MARKFORGED_YX

// 为具备无限 "Z" 轴运动的皮带式打印机启用
//#define BELTPRINTER

// 为绘制仪（Polargraph）运动学启用
//#define POLARGRAPH
#if ENABLED(POLARGRAPH)
  #define POLARGRAPH_MAX_BELT_LEN  1035.0 // (mm) 皮带完全伸展时的长度。可用 M665 H 覆盖。
  #define DEFAULT_SEGMENTS_PER_SECOND 5   // 基于时长的移动分段
  #define PEN_UP_DOWN_MENU                // 在 MarlinUI 菜单中添加"抬笔"和"落笔"
#endif

// @section delta

// 为 DELTA 运动学启用并在下方进行配置
//#define DELTA
#if ENABLED(DELTA)

  // 用多条直线逼近增量臂曲线（线性插值）。
  // 这是在可见转角（分段数不足）
  // 与处理器过载（过多昂贵的 sqrt 调用）之间的权衡。
  #define DEFAULT_SEGMENTS_PER_SECOND 200

  // 归位后向下移动到 XY 运动不受约束的高度
  //#define DELTA_HOME_TO_SAFE_ZONE

  // Delta 校准菜单
  // 在 MarlinUI 菜单中添加三点校准。
  // 参见 http://minow.blogspot.com/index.html#4918805519571907051
  //#define DELTA_CALIBRATION_MENU

  // G33 Delta 自动校准。启用 EEPROM_SETTINGS 以保存结果。
  //#define DELTA_AUTO_CALIBRATION

  #if ENABLED(DELTA_AUTO_CALIBRATION)
    // 默认探针点数量 : n*n (1 -> 7)
    #define DELTA_CALIBRATION_DEFAULT_POINTS 4
  #endif

  #if EITHER(DELTA_AUTO_CALIBRATION, DELTA_CALIBRATION_MENU)
    // 纸张测试探底的步进量
    #define PROBE_MANUALLY_STEP 0.05      // (mm)
  #endif

  // 打印表面直径/2 减去不可到达的空间（避免与立柱碰撞）。
  #define PRINTABLE_RADIUS       140.0    // (mm)

  // 最大可到达区域
  #define DELTA_MAX_RADIUS       140.0    // (mm)

  // 斜推杆上两孔的中心距。
  #define DELTA_DIAGONAL_ROD 250.0        // (mm)

  // 热床与喷嘴 Z 归位位置之间的距离
  #define DELTA_HEIGHT 250.00             // (mm) 此值请通过 G33 自动校准获取

  #define DELTA_ENDSTOP_ADJ { 0.0, 0.0, 0.0 } // 这些值请通过 G33 自动校准获取

  // 效应器居中时斜推杆所跨越的水平距离。
  #define DELTA_RADIUS 124.0              // (mm) 此值请通过 G33 自动校准获取

  // 各塔的微调修正
  // X 塔和 Y 塔的角度修正 / 旋转 XYZ 使 Z 塔角度 = 0
  // 从打印机上方俯视，以逆时针方向度量（单位：度）
  #define DELTA_TOWER_ANGLE_TRIM { 0.0, 0.0, 0.0 } // 这些值请通过 G33 自动校准获取

  // Delta 半径与斜杆长度修正 (mm)
  //#define DELTA_RADIUS_TRIM_TOWER { 0.0, 0.0, 0.0 }
  //#define DELTA_DIAGONAL_ROD_TRIM_TOWER { 0.0, 0.0, 0.0 }
#endif

// @section scara

/**
 * MORGAN_SCARA 由 QHARLEY 于 2012-2013 年在南非开发。
 * 2014 年 6 月由 JCERNY 实现并稍作改进。
 *
 * Mostly Printed SCARA 是 Tyler Williams 的开源设计。参见：
 *   https://www.thingiverse.com/thing:2487048
 *   https://www.thingiverse.com/thing:1241491
 */
//#define MORGAN_SCARA
//#define MP_SCARA
#if EITHER(MORGAN_SCARA, MP_SCARA)
  // 如果运动不平滑，请尝试降低此值
  #define DEFAULT_SEGMENTS_PER_SECOND 200

  // 内外支撑臂的长度。请精确测量臂长。
  #define SCARA_LINKAGE_1 150       // (mm)
  #define SCARA_LINKAGE_2 150       // (mm)

  // SCARA 塔架偏移（塔架相对热床零点的位置）
  // 此值需足够准确，因为它定义了热床在 SCARA 空间中的位置。
  #define SCARA_OFFSET_X  100       // (mm)
  #define SCARA_OFFSET_Y  -56       // (mm)

  #if ENABLED(MORGAN_SCARA)

    //#define DEBUG_SCARA_KINEMATICS
    #define FEEDRATE_SCALING        // 在运行中将 XY 进给速度从 mm/s 实时换算为度/s

    // 中心附近机械臂无法到达的半径区域
    #define MIDDLE_DEAD_ZONE_R   0  // (mm)

    #define THETA_HOMING_OFFSET  0  // 根据《校准指南》和 M360 / M114 计算得出。参见 http://reprap.harleystudio.co.za/?page_id=1073
    #define PSI_HOMING_OFFSET    0  // 根据《校准指南》和 M364 / M114 计算得出。参见 http://reprap.harleystudio.co.za/?page_id=1073

  #elif ENABLED(MP_SCARA)

    #define SCARA_OFFSET_THETA1  12 // degrees
    #define SCARA_OFFSET_THETA2 131 // degrees

  #endif

#endif

// @section tpara

// 启用以使用 TPARA 运动学，并在下方进行配置
//#define AXEL_TPARA
#if ENABLED(AXEL_TPARA)
  #define DEBUG_TPARA_KINEMATICS
  #define DEFAULT_SEGMENTS_PER_SECOND 200

  // 内外支撑臂的长度。请精确测量臂长。
  #define TPARA_LINKAGE_1 120       // (mm)
  #define TPARA_LINKAGE_2 120       // (mm)

  // SCARA 塔架偏移（塔架相对热床零点的位置）
  // 此值需足够准确，因为它定义了热床在 SCARA 空间中的位置。
  #define TPARA_OFFSET_X    0       // (mm)
  #define TPARA_OFFSET_Y    0       // (mm)
  #define TPARA_OFFSET_Z    0       // (mm)

  #define FEEDRATE_SCALING        // 在运行中将 XY 进给速度从 mm/s 实时换算为度/s

  // 中心附近机械臂无法到达的半径区域
  #define MIDDLE_DEAD_ZONE_R   0  // (mm)

  // 根据《校准指南》和 M360 / M114 计算得出。参见 http://reprap.harleystudio.co.za/?page_id=1073
  #define THETA_HOMING_OFFSET  0
  #define PSI_HOMING_OFFSET    0
#endif

// @section polar

/**
 * POLAR 运动学
 *  由 Kadir ilkimen 为 PolarBear CNC 和 babyBear 开发
 *  https://github.com/kadirilkimen/Polar-Bear-Cnc-Machine
 *  https://github.com/kadirilkimen/babyBear-3D-printer
 *
 * 极坐标机型可以有多种配置。
 * 此运动学仅兼容以下配置：
 *        X : 独立直线轴
 *   Y 或 B : 极坐标
 *        Z : 独立直线轴
 *
 * 例如，PolarBear 采用 CoreXZ 加极坐标 Y 或 B。
 *
 * 极坐标轴在中心/原点附近的运动问题：
 *
 * 3D 打印：
 * 靠近极坐标轴中心的运动会比其他运动耗时更长。
 * 由于喷嘴内的压力，这段短暂的时间会造成更多材料沉积。
 *
 * 当前的运动学与进给速度缩放通过让运动尽可能快来应对该问题。
 * 这对慢速运动有效，但对快速运动效果不佳。需要实现更复杂的
 * 挤出补偿。
 *
 * 理想情况下，它应能预判中心附近的长距离旋转即将发生并会导致
 * 不必要的沉积，从而提前补偿挤出量。
 *
 * 激光切割：
 * 同样的问题也会出现在激光雕刻中。由于在中心点旋转耗时，
 * 材料很可能会被烧蚀得过多。因此激光切割操作也需实现类似的
 * 补偿。
 *
 * 铣削：
 * 这对切割/铣削操作应该不成问题。
 */
//#define POLAR
#if ENABLED(POLAR)
  #define DEFAULT_SEGMENTS_PER_SECOND 180   // 如果运动不平滑，请尝试降低此值
  #define PRINTABLE_RADIUS 82.0f            // (mm) X 轴最大行程

  // 落在 POLAR_FAST_RADIUS 以内的运动将被赋予尽可能高的进给速度，
  // 以补偿与近原点运动问题相关的不必要沉积。
  #define POLAR_FAST_RADIUS 3.0f            // (mm)

  // 刀具无法到达的半径。
  // 当刀具未与极坐标轴中心完全对齐时需要设置。
  #define POLAR_CENTER_OFFSET 0.0f          // (mm)

  #define FEEDRATE_SCALING                  // 在运行中将 XY 进给速度从 mm/s 实时换算为度/s
#endif

// @section machine

// 关节型机器人（机械臂）。关节直接映射到轴，无运动学变换。
//#define ARTICULATED_ROBOT_ARM

// 用于热线切割机：两根水平平行轴 (X, I)，丝线两端的高度
// 由平行轴 (Y, J) 控制。关节直接映射到轴（无运动学变换）。
//#define FOAMCUTTER_XYUV

//===========================================================================
//============================== 限位开关设置 ===========================
//===========================================================================

// @section endstops

// 在此处指定所有连接到限位开关或探针的限位插座。
// 几乎所有打印机每轴使用一个。探针会占用一个或多个
// 额外插座。非限位、非探针用途的插座请保持未定义。
#define USE_XMIN_PLUG
#define USE_YMIN_PLUG
#define USE_ZMIN_PLUG
#define USE_IMIN_PLUG
#define USE_JMIN_PLUG
#define USE_KMIN_PLUG
//#define USE_UMIN_PLUG
//#define USE_VMIN_PLUG
//#define USE_WMIN_PLUG
//#define USE_XMAX_PLUG
//#define USE_YMAX_PLUG
//#define USE_ZMAX_PLUG
//#define USE_IMAX_PLUG
//#define USE_JMAX_PLUG
//#define USE_KMAX_PLUG
//#define USE_UMAX_PLUG
//#define USE_VMAX_PLUG
//#define USE_WMAX_PLUG

// 为所有限位开关启用上拉，以防止引脚悬空
#define ENDSTOPPULLUPS
#if DISABLED(ENDSTOPPULLUPS)
  // 禁用 ENDSTOPPULLUPS 以逐个设置上拉
  //#define ENDSTOPPULLUP_XMIN
  //#define ENDSTOPPULLUP_YMIN
  //#define ENDSTOPPULLUP_ZMIN
  //#define ENDSTOPPULLUP_IMIN
  //#define ENDSTOPPULLUP_JMIN
  //#define ENDSTOPPULLUP_KMIN
  //#define ENDSTOPPULLUP_UMIN
  //#define ENDSTOPPULLUP_VMIN
  //#define ENDSTOPPULLUP_WMIN
  //#define ENDSTOPPULLUP_XMAX
  //#define ENDSTOPPULLUP_YMAX
  //#define ENDSTOPPULLUP_ZMAX
  //#define ENDSTOPPULLUP_IMAX
  //#define ENDSTOPPULLUP_JMAX
  //#define ENDSTOPPULLUP_KMAX
  //#define ENDSTOPPULLUP_UMAX
  //#define ENDSTOPPULLUP_VMAX
  //#define ENDSTOPPULLUP_WMAX
  //#define ENDSTOPPULLUP_ZMIN_PROBE
#endif

// 为所有限位开关启用下拉，以防止引脚悬空
//#define ENDSTOPPULLDOWNS
#if DISABLED(ENDSTOPPULLDOWNS)
  // 禁用 ENDSTOPPULLDOWNS 以逐个设置下拉
  //#define ENDSTOPPULLDOWN_XMIN
  //#define ENDSTOPPULLDOWN_YMIN
  //#define ENDSTOPPULLDOWN_ZMIN
  //#define ENDSTOPPULLDOWN_IMIN
  //#define ENDSTOPPULLDOWN_JMIN
  //#define ENDSTOPPULLDOWN_KMIN
  //#define ENDSTOPPULLDOWN_UMIN
  //#define ENDSTOPPULLDOWN_VMIN
  //#define ENDSTOPPULLDOWN_WMIN
  //#define ENDSTOPPULLDOWN_XMAX
  //#define ENDSTOPPULLDOWN_YMAX
  //#define ENDSTOPPULLDOWN_ZMAX
  //#define ENDSTOPPULLDOWN_IMAX
  //#define ENDSTOPPULLDOWN_JMAX
  //#define ENDSTOPPULLDOWN_KMAX
  //#define ENDSTOPPULLDOWN_UMAX
  //#define ENDSTOPPULLDOWN_VMAX
  //#define ENDSTOPPULLDOWN_WMAX
  //#define ENDSTOPPULLDOWN_ZMIN_PROBE
#endif

/**
 * 限位开关“触发”状态
 * 设置为适用于各限位开关的状态（HIGH 或 LOW）。
 */
#define X_MIN_ENDSTOP_HIT_STATE HIGH
#define X_MAX_ENDSTOP_HIT_STATE HIGH
#define Y_MIN_ENDSTOP_HIT_STATE HIGH
#define Y_MAX_ENDSTOP_HIT_STATE HIGH
#define Z_MIN_ENDSTOP_HIT_STATE LOW
#define Z_MAX_ENDSTOP_HIT_STATE HIGH
#define I_MIN_ENDSTOP_HIT_STATE LOW
#define I_MAX_ENDSTOP_HIT_STATE HIGH
#define J_MIN_ENDSTOP_HIT_STATE LOW
#define J_MAX_ENDSTOP_HIT_STATE HIGH
#define K_MIN_ENDSTOP_HIT_STATE LOW
#define K_MAX_ENDSTOP_HIT_STATE HIGH
#define U_MIN_ENDSTOP_HIT_STATE HIGH
#define U_MAX_ENDSTOP_HIT_STATE HIGH
#define V_MIN_ENDSTOP_HIT_STATE HIGH
#define V_MAX_ENDSTOP_HIT_STATE HIGH
#define W_MIN_ENDSTOP_HIT_STATE HIGH
#define W_MAX_ENDSTOP_HIT_STATE HIGH
#define Z_MIN_PROBE_ENDSTOP_HIT_STATE HIGH

// 如果所有已启用的限位开关引脚都支持中断，请启用此功能。
// 这样就无需轮询中断引脚，可节省大量 CPU 周期。
//#define ENDSTOP_INTERRUPTS_FEATURE

/**
 * 限位开关噪声阈值
 *
 * 如果探针或限位开关因噪声而误触发，请启用此功能。
 *
 * - 较高的值可能影响某些热床探针的重复性或精度。
 * - 要消除噪声，可在开关两端并联一个 100nF 瓷片电容。
 * - 对于安装在基于 Makerbot 设计的 PCB 上的常见微动开关，
 *   无需此功能，它们本身已带有 100nF 电容。
 *
 * :[2,3,4,5,6,7]
 */
//#define ENDSTOP_NOISE_THRESHOLD 2

// 在归位移动期间检查限位开关是否卡住或断开。
//#define DETECT_BROKEN_ENDSTOP

//=============================================================================
//============================== 运动设置 ============================
//=============================================================================
// @section motion

/**
 * 默认设置
 *
 * 这些设置可通过 M502 重置
 *
 * 注意：如果启用了 EEPROM，已保存的值将覆盖这些设置。
 */

/**
 * 启用此选项后，每个 E 轴步进电机可以为以下运动参数
 * 单独设置各自的系数。如果给出的系数少于
 * 挤出机总数，则最后一个值适用于其余挤出机。
 */
//#define DISTINCT_E_FACTORS

/**
 * 默认每单位轴步数（直线轴=steps/mm，旋转轴=steps/°）
 * 可用 M92 覆盖
 *                                      X, Y, Z [, I [, J [, K...]]], E0 [, E1[, E2...]]
 */
#define DEFAULT_AXIS_STEPS_PER_UNIT   { 320, 320, 40, 4.44, 4.44, 40 }

/**
 * 默认最大进给速度（直线轴=mm/s，旋转轴=°/s）
 * 可用 M203 覆盖
 *                                      X, Y, Z [, I [, J [, K...]]], E0 [, E1[, E2...]]
 */
#define DEFAULT_MAX_FEEDRATE          { 1000, 1000, 500, 50000, 50000, 5000 }

//#define LIMITED_MAX_FR_EDITING        // 限制通过 M203 或 LCD 编辑不超过 DEFAULT_MAX_FEEDRATE * 2
#if ENABLED(LIMITED_MAX_FR_EDITING)
  #define MAX_FEEDRATE_EDIT_VALUES    { 600, 600, 10, 50 } // ...或者自行设置编辑上限
#endif

/**
 * 默认最大加速度（速度随时间的变化）(直线轴=mm/(s^2)，旋转轴=°/(s^2))
 * （加速运动的最大起始速度）
 * 可用 M201 覆盖
 *                                      X, Y, Z [, I [, J [, K...]]], E0 [, E1[, E2...]]
 */
#define DEFAULT_MAX_ACCELERATION      { 2000, 2000, 2000, 3000, 3000, 3000 }

//#define LIMITED_MAX_ACCEL_EDITING     // 限制通过 M201 或 LCD 编辑不超过 DEFAULT_MAX_ACCELERATION * 2
#if ENABLED(LIMITED_MAX_ACCEL_EDITING)
  #define MAX_ACCEL_EDIT_VALUES       { 6000, 6000, 200, 20000 } // ...或者自行设置编辑上限
#endif

/**
 * 默认加速度（速度随时间的变化）(直线轴=mm/(s^2)，旋转轴=°/(s^2))
 * 可用 M204 覆盖
 *
 *   M204 P    加速度
 *   M204 R    回抽加速度
 *   M204 T    空移加速度
 *   M204 I    角加速度
 *   M204 J    角空移加速度
 */
#define DEFAULT_ACCELERATION                  2000  // 打印移动时 X、Y、Z ... 与 E 的加速度
#define DEFAULT_RETRACT_ACCELERATION          3000  // 回抽时 E 的加速度
#define DEFAULT_TRAVEL_ACCELERATION           2000  // 空移（非打印）移动时 X、Y、Z ... 的加速度
#if ENABLED(AXIS4_ROTATES)
  #define DEFAULT_ANGULAR_ACCELERATION        3000  // 仅旋转的打印移动时 I、J、K 的加速度
  #define DEFAULT_ANGULAR_TRAVEL_ACCELERATION 3000  // 仅旋转的空移（非打印）移动时 I、J、K 的加速度
#endif

/**
 * 默认 Jerk 限制 (mm/s)
 * 可用 M205 X Y Z . . . E 覆盖
 *
 * “Jerk”指定需要加速才能达到的最小速度变化量。
 * 在改变速度和方向时，如果差值小于
 * 此处设置的值，则可瞬间完成。
 */
//#define CLASSIC_JERK
#if ENABLED(CLASSIC_JERK)
  #define DEFAULT_XJERK 10.0
  #define DEFAULT_YJERK 10.0
  #define DEFAULT_ZJERK  0.3
  //#define DEFAULT_IJERK  0.3
  //#define DEFAULT_JJERK  0.3
  //#define DEFAULT_KJERK  0.3
  //#define DEFAULT_UJERK  0.3
  //#define DEFAULT_VJERK  0.3
  //#define DEFAULT_WJERK  0.3

  //#define TRAVEL_EXTRA_XYJERK 0.0     // 所有空移移动的额外 Jerk 余量

  //#define LIMITED_JERK_EDITING        // 限制通过 M205 或 LCD 编辑不超过 DEFAULT_aJERK * 2
  #if ENABLED(LIMITED_JERK_EDITING)
    #define MAX_JERK_EDIT_VALUES { 20, 20, 0.6, 10 } // ...或者自行设置编辑上限
  #endif
#endif

#define DEFAULT_EJERK    5.0  // 可能会被线性进阶（Linear Advance）功能使用

/**
 * 转角偏差系数（Junction Deviation）
 *
 * 参见：
 *   https://reprap.org/forum/read.php?1,739819
 *   https://blog.kyneticcnc.com/2018/10/computing-junction-deviation-for-marlin.html
 */
#if DISABLED(CLASSIC_JERK)
  #define JUNCTION_DEVIATION_MM 0.013 // (mm) 距实际转角边缘的距离
  #define JD_HANDLE_SMALL_SEGMENTS    // 使用曲率估算，而不仅是转角角度
                                      // 来处理转角较大（> 135°）的小分段（< 1mm）。
#endif

/**
 * S 曲线加速度
 *
 * 此选项通过对移动加速度拟合 Bézier 曲线来消除打印过程中的振动，
 * 从而产生更平滑的方向变化。
 *
 * 参见 https://github.com/synthetos/TinyG/wiki/Jerk-Controlled-Motion-Explained
 */
//#define S_CURVE_ACCELERATION

//===========================================================================
//============================= Z 探针选项 =============================
//===========================================================================
// @section probes

//
// 参见 https://marlinfw.org/docs/configuration/probes.html
//

/**
 * 如果探针连接到 Z-MIN 引脚，请启用此选项。
 * 探针将取代 Z-MIN 限位开关并用于 Z 轴归位。
 * （自动启用 USE_PROBE_FOR_Z_HOMING。）
 */
#define Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN

// 强制使用探针进行 Z 轴归位
//#define USE_PROBE_FOR_Z_HOMING

/**
 * Z_MIN_PROBE_PIN
 *
 * 仅当探针无法连接到所选 MOTHERBOARD 的
 * 默认 Z_MIN_PROBE_PIN 时才覆盖此引脚。
 *
 *  - 最简单的方法是使用空闲的限位插座。
 *  - 有源（通常为电感式）传感器请使用 5V。
 *
 *  - 对于简单开关...
 *    - 常闭型 (NC) 另需连接到 GND。
 *    - 常开型 (NO) 另需连接到 5V。
 */
//#define Z_MIN_PROBE_PIN -1

/**
 * 探针类型
 *
 * 内六角扳手探针、舵机探针、Z 滑橇探针、FIX_MOUNTED_PROBE 等。
 * 启用其中一项以使用下方的自动热床调平。
 */

/**
 * “手动探针”提供了一种不使用探针进行“自动”热床调平的方法。
 * 反复使用 G29，通过移动命令（或启用 LCD_BED_LEVELING 时通过 LCD 控制器）
 * 在每个点调整 Z 高度。
 */
//#define PROBE_MANUALLY

/**
 * 固定式探针无需展开，或需要手动展开。
 *   （例如电感式探针或基于喷嘴的探针开关。）
 */
//#define FIX_MOUNTED_PROBE

/**
 * 将喷嘴用作探针，例如导电喷嘴系统
 * 或压电智能效应器。
 */
//#define NOZZLE_AS_PROBE

/**
 * Z 舵机探针，例如安装在旋转臂上的限位开关。
 */
//#define Z_PROBE_SERVO_NR 0
#ifdef Z_PROBE_SERVO_NR
  //#define Z_SERVO_ANGLES { 70, 0 }      // Z 舵机展开与收起的角度
  //#define Z_SERVO_MEASURE_ANGLE 45      // 若舵机展开后须先移动到“空闲”位置再测量，请启用
  //#define Z_SERVO_INTERMEDIATE_STOW     // 在各点之间收起探针
  //#define Z_SERVO_DEACTIVATE_AFTER_STOW // 探针收起后停用舵机
#endif

/**
 * BLTouch 探针使用霍尔效应传感器并模拟舵机。
 */
//#define BLTOUCH

/**
 * MDD 出品的 MagLev V4 探针
 *
 * 该探针通过给内置电磁铁通电来展开并激活。
 */
//#define MAGLEV4
#if ENABLED(MAGLEV4)
  //#define MAGLEV_TRIGGER_PIN 11     // 设置为所连接的数字输出引脚
  #define MAGLEV_TRIGGER_DELAY 15     // 更改此值有导致线圈过热的风险
#endif

/**
 * hotends.fr 出品的 Touch-MI 探针
 *
 * 该探针通过将 X 轴移动到热床边缘的磁铁来展开并激活。
 * 默认假设磁铁在左侧，并通过归位动作激活。如果磁铁
 * 在右侧，请启用并设置 TOUCH_MI_DEPLOY_XPOS 为展开位置。
 *
 * 还需要：BABYSTEPPING、BABYSTEP_ZPROBE_OFFSET、Z_SAFE_HOMING，
 *                且 Z_HOMING_HEIGHT 至少为 10。
 */
//#define TOUCH_MI_PROBE
#if ENABLED(TOUCH_MI_PROBE)
  #define TOUCH_MI_RETRACT_Z 0.5                  // 探针回缩的高度
  //#define TOUCH_MI_DEPLOY_XPOS (X_MAX_BED + 2)  // 适用于磁铁在热床右侧的情况
  //#define TOUCH_MI_MANUAL_DEPLOY                // 用于手动展开（LCD 菜单）
#endif

// 通过电磁铁引脚 (SOL1_PIN) 展开和收起的探针
//#define SOLENOID_PROBE

// 滑橇式探针，例如 Charles Bell 设计的那种。
//#define Z_PROBE_SLED
//#define SLED_DOCKING_OFFSET 5  // X 轴拾取滑橇所需额外移动的距离。0 通常即可，如有需要可适当加大。

// 通过移动 X 轴展开的探针，例如 Marty Rice 为 Wilson II 设计的齿条齿轮探针。
//#define RACK_AND_PINION_PROBE
#if ENABLED(RACK_AND_PINION_PROBE)
  #define Z_PROBE_DEPLOY_X  X_MIN_POS
  #define Z_PROBE_RETRACT_X X_MAX_POS
#endif

/**
 * 磁吸式探针
 * 适用于 Euclid、Klicky、Klackender 等探针。
 */
//#define MAG_MOUNTED_PROBE
#if ENABLED(MAG_MOUNTED_PROBE)
  #define PROBE_DEPLOY_FEEDRATE (133*60)  // (mm/min) 探针展开速度
  #define PROBE_STOW_FEEDRATE   (133*60)  // (mm/min) 探针收起速度

  #define MAG_MOUNTED_DEPLOY_1 { PROBE_DEPLOY_FEEDRATE, { 245, 114, 30 } }  // 移动到停靠架侧面并装上探针
  #define MAG_MOUNTED_DEPLOY_2 { PROBE_DEPLOY_FEEDRATE, { 210, 114, 30 } }  // 将探针移离停靠架
  #define MAG_MOUNTED_DEPLOY_3 { PROBE_DEPLOY_FEEDRATE, {   0,   0,  0 } }  // 如有需要的额外移动
  #define MAG_MOUNTED_DEPLOY_4 { PROBE_DEPLOY_FEEDRATE, {   0,   0,  0 } }  // 如有需要的额外移动
  #define MAG_MOUNTED_DEPLOY_5 { PROBE_DEPLOY_FEEDRATE, {   0,   0,  0 } }  // 如有需要的额外移动
  #define MAG_MOUNTED_STOW_1   { PROBE_STOW_FEEDRATE,   { 245, 114, 20 } }  // 移动到停靠架
  #define MAG_MOUNTED_STOW_2   { PROBE_STOW_FEEDRATE,   { 245, 114,  0 } }  // 将探针放到取下装置旁
  #define MAG_MOUNTED_STOW_3   { PROBE_STOW_FEEDRATE,   { 230, 114,  0 } }  // 侧向移动以取下探针
  #define MAG_MOUNTED_STOW_4   { PROBE_STOW_FEEDRATE,   { 210, 114, 20 } }  // 侧向移动以取下探针
  #define MAG_MOUNTED_STOW_5   { PROBE_STOW_FEEDRATE,   {   0,   0,  0 } }  // 如有需要的额外移动
#endif

// Duet Smart Effector（适用于 Delta 打印机）- https://bit.ly/2ul5U7J
// 定义该引脚后，可使用 M672 设置/重置探针灵敏度。
//#define DUET_SMART_EFFECTOR
#if ENABLED(DUET_SMART_EFFECTOR)
  #define SMART_EFFECTOR_MOD_PIN  -1  // 将 GPIO 引脚连接到 Smart Effector 的 MOD 引脚
#endif

/**
 * 使用 StallGuard2 以喷嘴探测热床。
 * 需要支持 stallGuard 的 Trinamic 步进电机驱动。
 * 注意：这可能会损坏带有 Z 丝杆的机器。
 *          配置此功能时务必格外小心。
 */
//#define SENSORLESS_PROBING

/**
 * 常见于多款 Kossel Delta 打印机上的内六角扳手式可伸缩 Z 探针 - https://reprap.org/wiki/Kossel#Automatic_bed_leveling_probe
 * 通过触碰 Z 轴皮带来展开。向下按压探针即可收回。
 */
//#define Z_PROBE_ALLEN_KEY
#if ENABLED(Z_PROBE_ALLEN_KEY)
  // 在 G29 上展开和收回弹簧式触碰探针的 2 或 3 组坐标，
  // 适用于未定义舵机触碰探针的情况。请根据你的打印机/探针酌情取消注释。

  #define Z_PROBE_ALLEN_KEY_DEPLOY_1 { 30.0, PRINTABLE_RADIUS, 100.0 }
  #define Z_PROBE_ALLEN_KEY_DEPLOY_1_FEEDRATE XY_PROBE_FEEDRATE

  #define Z_PROBE_ALLEN_KEY_DEPLOY_2 { 0.0, PRINTABLE_RADIUS, 100.0 }
  #define Z_PROBE_ALLEN_KEY_DEPLOY_2_FEEDRATE (XY_PROBE_FEEDRATE)/10

  #define Z_PROBE_ALLEN_KEY_DEPLOY_3 { 0.0, (PRINTABLE_RADIUS) * 0.75, 100.0 }
  #define Z_PROBE_ALLEN_KEY_DEPLOY_3_FEEDRATE XY_PROBE_FEEDRATE

  #define Z_PROBE_ALLEN_KEY_STOW_1 { -64.0, 56.0, 23.0 } // 将探针移动到工作位置
  #define Z_PROBE_ALLEN_KEY_STOW_1_FEEDRATE XY_PROBE_FEEDRATE

  #define Z_PROBE_ALLEN_KEY_STOW_2 { -64.0, 56.0, 3.0 } // 将其向下压
  #define Z_PROBE_ALLEN_KEY_STOW_2_FEEDRATE (XY_PROBE_FEEDRATE)/10

  #define Z_PROBE_ALLEN_KEY_STOW_3 { -64.0, 56.0, 50.0 } // 将其抬起以脱离
  #define Z_PROBE_ALLEN_KEY_STOW_3_FEEDRATE XY_PROBE_FEEDRATE

  #define Z_PROBE_ALLEN_KEY_STOW_4 { 0.0, 0.0, 50.0 }
  #define Z_PROBE_ALLEN_KEY_STOW_4_FEEDRATE XY_PROBE_FEEDRATE

#endif // Z_PROBE_ALLEN_KEY

/**
 * 喷嘴到探针的偏移 { X, Y, Z }
 *
 * X 和 Y 偏移
 *   使用卡尺或直尺测量喷嘴尖端到探针中心点
 *   在 X 和 Y 轴方向上的距离。
 *
 * Z 偏移
 * - Z 偏移请填入你已知的最佳值，并在运行时加以调整。
 * - 常见探针在喷嘴下方触发，其 Z 偏移为负值。
 * - 在喷嘴高度以上触发的探针虽少见但确实存在。使用此类探针时，
 *   请仔细设置 Z_CLEARANCE_DEPLOY_PROBE 和 Z_CLEARANCE_BETWEEN_PROBES，
 *   以避免探测过程中发生碰撞。
 *
 * 调谐与调整
 * -  探针偏移可在运行时通过 'M851'、LCD 菜单、babystepping 等方式调整。
 * -  可使用 PROBE_OFFSET_WIZARD（configuration_adv.h）来设置 Z 偏移。
 *
 * 假设工作区为常见朝向：
 *  - 探针在喷嘴右侧：X 偏移为正
 *  - 探针在喷嘴左侧：X 偏移为负
 *  - 探针在喷嘴后方：Y 偏移为正
 *  - 探针在喷嘴前方：Y 偏移为负
 *
 * 一些示例：
 *   #define NOZZLE_TO_PROBE_OFFSET { 10, 10, -1 }   // 示例 "1"
 *   #define NOZZLE_TO_PROBE_OFFSET {-10,  5, -1 }   // 示例 "2"
 *   #define NOZZLE_TO_PROBE_OFFSET {  5, -5, -1 }   // 示例 "3"
 *   #define NOZZLE_TO_PROBE_OFFSET {-15,-10, -1 }   // 示例 "4"
 *
 *     +-- BACK ---+
 *     |    [+]    |
 *   L |        1  | R <-- 示例 "1"（右+，后+）
 *   E |  2        | I <-- 示例 "2"（左-，后+）
 *   F |[-]  N  [+]| G <-- 喷嘴
 *   T |       3   | H <-- 示例 "3"（右+，前-）
 *     | 4         | T <-- 示例 "4"（左-，前-）
 *     |    [-]    |
 *     O-- FRONT --+
 */
#define NOZZLE_TO_PROBE_OFFSET { 10, 10, 0 }

// 启用并设置为使用指定工具进行探测。禁用则允许使用任意工具。
#define PROBING_TOOL 0
#ifdef PROBING_TOOL
  //#define PROBE_TOOLCHANGE_NO_MOVE  // 探针换刀时不产生移动
#endif

// 大多数探针应远离热床边缘，但
// 使用 NOZZLE_AS_PROBE 时可设为负值以获得更大的探测区域。
#define PROBING_MARGIN 10

// 两次探测之间 X 和 Y 轴的移动速度 (mm/min)
#define XY_PROBE_FEEDRATE (133*60)

// 双重探测（MULTIPLE_PROBING == 2）时首次接近的进给速度 (mm/min)
#define Z_PROBE_FEEDRATE_FAST (4*60)

// 每个点“精确”探测时的进给速度 (mm/min)
#define Z_PROBE_FEEDRATE_SLOW (Z_PROBE_FEEDRATE_FAST / 2)

/**
 * 探针激活开关
 * 用于指示探针正确展开的开关，或在小车靠近
 * 热床时触发的光电开关。
 */
//#define PROBE_ACTIVATION_SWITCH
#if ENABLED(PROBE_ACTIVATION_SWITCH)
  #define PROBE_ACTIVATION_SWITCH_STATE LOW // 表示探针处于激活状态的电平
  //#define PROBE_ACTIVATION_SWITCH_PIN PC6 // 覆盖默认引脚
#endif

/**
 * 每次探测前先对探针去皮（确定零点）。
 * 对于需要剔除线缆拉拽小车等因素影响的
 * 应变片或压电传感器很有用。
 */
//#define PROBE_TARE
#if ENABLED(PROBE_TARE)
  #define PROBE_TARE_TIME  200    // (ms) 保持去皮引脚电平的时间
  #define PROBE_TARE_DELAY 200    // (ms) 去皮后的延迟
  #define PROBE_TARE_STATE HIGH   // 去皮时写入引脚的状态
  //#define PROBE_TARE_PIN PA5    // 覆盖默认引脚
  #if ENABLED(PROBE_ACTIVATION_SWITCH)
    //#define PROBE_TARE_ONLY_WHILE_INACTIVE  // 若 PROBE_ACTIVATION_SWITCH 处于激活状态，则去皮/探测失败
  #endif
#endif

/**
 * 探针启用 / 禁用
 * 探针仅在启用后才会输出触发信号。
 */
//#define PROBE_ENABLE_DISABLE
#if ENABLED(PROBE_ENABLE_DISABLE)
  //#define PROBE_ENABLE_PIN -1   // 在此处覆盖默认引脚
#endif

/**
 * 多次探测
 *
 * 探测 2 次或更多次可能会获得更好的结果。
 * 使用 EXTRA_PROBING 时，较离群的读数将被忽略。
 *
 * 总数为 2 时进行快/慢两次探测并取加权平均。
 * 总数为 3 或更多时增加慢速探测次数并取平均值。
 */
//#define MULTIPLE_PROBING 2
//#define EXTRA_PROBING    1

/**
 * Z 探针在展开、收起以及在探测点之间移动时需要留出间隙，
 * 以免撞到热床或其他硬件。
 * 舵机式探针需要额外空间供旋转臂转动。
 * 电感式探针需要预留空间以免过早触发。
 *
 * 使用这些设置指定抬起探针（或降低热床）的距离 (mm)。
 * 此处设置的值会叠加在任何通过 NOZZLE_TO_PROBE_OFFSET、M851 或 LCD
 * 设置的（负）探针 Z 偏移之上。
 * 此处仅接受 >= 1 的整数值。
 *
 * 示例：`M851 Z-5` 且 CLEARANCE 为 4  =>  热床到喷嘴 9mm。
 *     但：`M851 Z+1` 且 CLEARANCE 为 2  =>  热床到喷嘴 2mm。
 */
#define Z_CLEARANCE_DEPLOY_PROBE   10 // 展开/收起时的 Z 间隙
//#define Z_CLEARANCE_BETWEEN_PROBES  5 // 探测点之间的 Z 间隙
#define Z_CLEARANCE_MULTI_PROBE     5 // 多次探测之间的 Z 间隙
//#define Z_AFTER_PROBING           5 // 探测完成后的 Z 位置

#define Z_PROBE_LOW_POINT          -2 // 停止前可越过触发点向下到达的最远距离

// 为 M851 提供调整 Z 探针偏移的范围
#define Z_PROBE_OFFSET_RANGE_MIN -20
#define Z_PROBE_OFFSET_RANGE_MAX 20

// 启用 M48 重复性测试以检验探针精度
//#define Z_MIN_PROBE_REPEATABILITY_TEST

// 展开/收起探针前暂停，等待用户确认
//#define PAUSE_BEFORE_DEPLOY_STOW
#if ENABLED(PAUSE_BEFORE_DEPLOY_STOW)
  //#define PAUSE_PROBE_DEPLOY_WHEN_TRIGGERED // 用于手动展开的内六角扳手探针
#endif

/**
 * 如果探测似乎不可靠，请启用以下一项或多项。
 * 可在探测期间禁用加热器/风扇，以尽量减少电气
 * 噪声。也可加入延迟，让噪声和振动平息下来。
 * 这些选项对 BLTouch 探针最为有用，但也可能改善
 * 电感式探针和压电传感器的读数。
 */
//#define PROBING_HEATERS_OFF       // 探测时关闭加热器
#if ENABLED(PROBING_HEATERS_OFF)
  //#define WAIT_FOR_BED_HEATER     // 两次探测之间等待热床重新升温（以提高精度）
  //#define WAIT_FOR_HOTEND         // 两次探测之间等待热端重新升温（提高精度并防止冷挤出）
#endif
//#define PROBING_FANS_OFF          // 探测时关闭风扇
//#define PROBING_ESTEPPERS_OFF     // 探测时关闭所有挤出机步进电机
//#define PROBING_STEPPERS_OFF      // 探测时关闭所有步进电机（保持位置所需的除外，包括挤出机）
//#define DELAY_BEFORE_PROBING 200  // (ms) 防止振动误触发压电传感器

// 探测前要求喷嘴/热床达到最低温度
//#define PREHEAT_BEFORE_PROBING
#if ENABLED(PREHEAT_BEFORE_PROBING)
  #define PROBING_NOZZLE_TEMP 120   // (°C) 目前仅对 E0 生效
  #define PROBING_BED_TEMP     50
#endif

// 步进电机使能引脚反相（低电平有效）用 0，非反相（高电平有效）用 1
// :{ 0:'Low', 1:'High' }
#define X_ENABLE_ON 0
#define Y_ENABLE_ON 0
#define Z_ENABLE_ON 0
#define E_ENABLE_ON 0 // 适用于所有挤出机
#define I_ENABLE_ON 0
#define J_ENABLE_ON 0
#define K_ENABLE_ON 0
//#define U_ENABLE_ON 0
//#define V_ENABLE_ON 0
//#define W_ENABLE_ON 0

// 轴步进电机不运行时立即禁用。
// 警告：电机关闭后可能丢失位置精度！
//#define DISABLE_X
//#define DISABLE_Y
//#define DISABLE_Z
//#define DISABLE_I
//#define DISABLE_J
//#define DISABLE_K
//#define DISABLE_U
//#define DISABLE_V
//#define DISABLE_W

// 关闭提示可能降低精度的显示闪烁
//#define DISABLE_REDUCED_ACCURACY_WARNING

// @section extruder

//#define DISABLE_E               // 不运行时禁用挤出机
#define DISABLE_OTHER_EXTRUDERS   // 仅保持当前活动的挤出机启用

// @section motion

// 反转步进电机方向。如果某轴方向错误，请修改此值（或将电机接头反插）。
#define INVERT_X_DIR true
#define INVERT_Y_DIR false
#define INVERT_Z_DIR false
#define INVERT_I_DIR true
#define INVERT_J_DIR true
#define INVERT_K_DIR false
//#define INVERT_U_DIR false
//#define INVERT_V_DIR false
//#define INVERT_W_DIR false

// @section extruder

// 直驱挤出机 v9 设为 true，齿轮减速挤出机设为 false。
#define INVERT_E0_DIR false
#define INVERT_E1_DIR false
#define INVERT_E2_DIR false
#define INVERT_E3_DIR false
#define INVERT_E4_DIR false
#define INVERT_E5_DIR false
#define INVERT_E6_DIR false
#define INVERT_E7_DIR false

// @section homing

//#define NO_MOTION_BEFORE_HOMING // 在所有轴归位前禁止移动。另请启用 HOME_AFTER_DEACTIVATE 以获得额外安全保障。
//#define HOME_AFTER_DEACTIVATE   // 步进电机失能后要求重新归位。另请启用 NO_MOTION_BEFORE_HOMING 以获得额外安全保障。

/**
 * 如果步进电机失能后 Z 轴会自行移动，请设置 Z_IDLE_HEIGHT。
 *  - 若喷嘴向热床坠落，请使用较小的值（如 Z_MIN_POS）。
 *  - 若热床远离喷嘴下坠，请使用较大的值（如 Z_MAX_POS）。
 */
//#define Z_IDLE_HEIGHT Z_HOME_POS

//#define Z_HOMING_HEIGHT  4      // (mm) 归位 (G28) 前的最小 Z 高度，以保证热床、夹具等上方的 Z 向间隙
                                  // 请确保在 Z_MAX_POS 之上留有这么多间隙，以免刮蹭。

#define Z_AFTER_HOMING  31.5      // (mm) Z 归位后移动到的高度

// 归位时限位开关的方向；1=MAX，-1=MIN
// :[-1,1]
#define X_HOME_DIR -1
#define Y_HOME_DIR -1
#define Z_HOME_DIR -1
#define I_HOME_DIR 0
#define J_HOME_DIR 0
#define K_HOME_DIR 0
//#define U_HOME_DIR -1
//#define V_HOME_DIR -1
//#define W_HOME_DIR -1

// @section geometry

// 可打印区域的尺寸
#define X_BED_SIZE 433
#define Y_BED_SIZE 487

// 归位后的行程限制（直线轴=mm，旋转轴=°），对应限位开关位置。
#define X_MIN_POS 0
#define Y_MIN_POS 0
#define Z_MIN_POS 0
#define X_MAX_POS X_BED_SIZE
#define Y_MAX_POS Y_BED_SIZE
#define Z_MAX_POS 63
#define I_MIN_POS 0
#define I_MAX_POS 720
#define J_MIN_POS 0
#define J_MAX_POS 720
#define K_MIN_POS 0
#define K_MAX_POS 10000
//#define U_MIN_POS 0
//#define U_MAX_POS 50
//#define V_MIN_POS 0
//#define V_MAX_POS 50
//#define W_MIN_POS 0
//#define W_MAX_POS 50

/**
 * 软件限位开关
 *
 * - 防止移动超出设定的机器边界。
 * - 如有需要，可单独禁用某些轴。
 * - X 和 Y 仅适用于笛卡尔机器人。
 * - 使用 'M211' 开/关软件限位开关或查看当前状态
 */

// 最小软件限位开关将运动限制在最小坐标范围内
#define MIN_SOFTWARE_ENDSTOPS
#if ENABLED(MIN_SOFTWARE_ENDSTOPS)
  #define MIN_SOFTWARE_ENDSTOP_X
  #define MIN_SOFTWARE_ENDSTOP_Y
  #define MIN_SOFTWARE_ENDSTOP_Z
  #define MIN_SOFTWARE_ENDSTOP_I
  #define MIN_SOFTWARE_ENDSTOP_J
  #define MIN_SOFTWARE_ENDSTOP_K
  #define MIN_SOFTWARE_ENDSTOP_U
  #define MIN_SOFTWARE_ENDSTOP_V
  #define MIN_SOFTWARE_ENDSTOP_W
#endif

// 最大软件限位开关将运动限制在最大坐标范围内
#define MAX_SOFTWARE_ENDSTOPS
#if ENABLED(MAX_SOFTWARE_ENDSTOPS)
  #define MAX_SOFTWARE_ENDSTOP_X
  #define MAX_SOFTWARE_ENDSTOP_Y
  #define MAX_SOFTWARE_ENDSTOP_Z
  #define MAX_SOFTWARE_ENDSTOP_I
  #define MAX_SOFTWARE_ENDSTOP_J
  #define MAX_SOFTWARE_ENDSTOP_K
  #define MAX_SOFTWARE_ENDSTOP_U
  #define MAX_SOFTWARE_ENDSTOP_V
  #define MAX_SOFTWARE_ENDSTOP_W
#endif

#if EITHER(MIN_SOFTWARE_ENDSTOPS, MAX_SOFTWARE_ENDSTOPS)
  //#define SOFT_ENDSTOPS_MENU_ITEM  // 从 LCD 启用/禁用软件限位开关
#endif

/**
 * 耗材断料传感器
 * 使用机械式或光电限位开关检测耗材是否存在。
 *
 * 重要：只有当 Marlin 知道打印任务正在运行时，断料才会触发。
 * Marlin 在以下情况下知道打印任务正在运行：
 *  1. 通过 M24 启动介质（存储卡）上的打印任务。
 *  2. 打印任务计时器已通过 M75 启动。
 *  3. 加热器已开启且 PRINTJOB_TIMER_AUTOSTART 已启用。
 *
 * 基于 RAMPS 的主板使用 SERVO3_PIN 作为第一个断料传感器。
 * 其他主板可能需要定义 FIL_RUNOUT_PIN、FIL_RUNOUT2_PIN 等。
 */
//#define FILAMENT_RUNOUT_SENSOR
#if ENABLED(FILAMENT_RUNOUT_SENSOR)
  #define FIL_RUNOUT_ENABLED_DEFAULT true // 启动时启用该传感器。可用 M412 加 M500 覆盖。
  #define NUM_RUNOUT_SENSORS   1          // 传感器数量，每个挤出机最多一个。需为每个传感器定义对应的 FIL_RUNOUT#_PIN。

  #define FIL_RUNOUT_STATE     LOW        // 表示耗材不存在的引脚电平。
  #define FIL_RUNOUT_PULLUP               // 为断料引脚使用内部上拉。
  //#define FIL_RUNOUT_PULLDOWN           // 为断料引脚使用内部下拉。
  //#define WATCH_ALL_RUNOUT_SENSORS      // 在任一触发传感器上执行断料脚本，而不仅针对当前挤出机。
                                          // 对于 MIXING_EXTRUDER 会自动启用此功能。

  // 如果各断料传感器不同，可单独覆盖
  //#define FIL_RUNOUT1_STATE LOW
  //#define FIL_RUNOUT1_PULLUP
  //#define FIL_RUNOUT1_PULLDOWN

  //#define FIL_RUNOUT2_STATE LOW
  //#define FIL_RUNOUT2_PULLUP
  //#define FIL_RUNOUT2_PULLDOWN

  //#define FIL_RUNOUT3_STATE LOW
  //#define FIL_RUNOUT3_PULLUP
  //#define FIL_RUNOUT3_PULLDOWN

  //#define FIL_RUNOUT4_STATE LOW
  //#define FIL_RUNOUT4_PULLUP
  //#define FIL_RUNOUT4_PULLDOWN

  //#define FIL_RUNOUT5_STATE LOW
  //#define FIL_RUNOUT5_PULLUP
  //#define FIL_RUNOUT5_PULLDOWN

  //#define FIL_RUNOUT6_STATE LOW
  //#define FIL_RUNOUT6_PULLUP
  //#define FIL_RUNOUT6_PULLDOWN

  //#define FIL_RUNOUT7_STATE LOW
  //#define FIL_RUNOUT7_PULLUP
  //#define FIL_RUNOUT7_PULLDOWN

  //#define FIL_RUNOUT8_STATE LOW
  //#define FIL_RUNOUT8_PULLUP
  //#define FIL_RUNOUT8_PULLDOWN

  // 断料时执行的命令。
  // 使用多个断料传感器时，可在命令中用 %c 占位符表示当前工具（如 "M600 T%c"）
  // 注意：执行 'M412 H1' 后由主机处理断料，此脚本不再生效。
  #define FILAMENT_RUNOUT_SCRIPT "M600"

  // 检测到断料后，先继续打印这段长度的耗材
  // 再执行断料脚本。适用于传感器位于
  // 送料管末端的情况。每个传感器需要 4 字节 SRAM，外加 4 字节开销。
  //#define FILAMENT_RUNOUT_DISTANCE_MM 25

  #ifdef FILAMENT_RUNOUT_DISTANCE_MM
    // 启用此选项可使用码盘，在耗材移动时
    // 翻转断料引脚。（务必将 FILAMENT_RUNOUT_DISTANCE_MM
    // 设置得足够大，以避免误报。）
    //#define FILAMENT_MOTION_SENSOR

    #if ENABLED(FILAMENT_MOTION_SENSOR)
      //#define FILAMENT_SWITCH_AND_MOTION
      #if ENABLED(FILAMENT_SWITCH_AND_MOTION)
        #define NUM_MOTION_SENSORS   1          // 传感器数量，每个挤出机最多一个。需为每个传感器定义对应的 FIL_MOTION#_PIN。
        //#define FIL_MOTION1_PIN    -1

        // 如果各运动传感器不同，可单独覆盖
        //#define FIL_MOTION1_STATE LOW
        //#define FIL_MOTION1_PULLUP
        //#define FIL_MOTION1_PULLDOWN

        //#define FIL_MOTION2_STATE LOW
        //#define FIL_MOTION2_PULLUP
        //#define FIL_MOTION2_PULLDOWN

        //#define FIL_MOTION3_STATE LOW
        //#define FIL_MOTION3_PULLUP
        //#define FIL_MOTION3_PULLDOWN

        //#define FIL_MOTION4_STATE LOW
        //#define FIL_MOTION4_PULLUP
        //#define FIL_MOTION4_PULLDOWN

        //#define FIL_MOTION5_STATE LOW
        //#define FIL_MOTION5_PULLUP
        //#define FIL_MOTION5_PULLDOWN

        //#define FIL_MOTION6_STATE LOW
        //#define FIL_MOTION6_PULLUP
        //#define FIL_MOTION6_PULLDOWN

        //#define FIL_MOTION7_STATE LOW
        //#define FIL_MOTION7_PULLUP
        //#define FIL_MOTION7_PULLDOWN

        //#define FIL_MOTION8_STATE LOW
        //#define FIL_MOTION8_PULLUP
        //#define FIL_MOTION8_PULLDOWN
      #endif
    #endif
  #endif
#endif

//===========================================================================
//=============================== 热床调平 ==============================
//===========================================================================
// @section calibrate

/**
 * 从以下选项中选择一个以启用 G29 热床调平。G29 的参数
 * 和行为会随你的选择而变化。
 *
 *  如果使用探针进行 Z 归位，请同时启用 Z_SAFE_HOMING！
 *
 * - AUTO_BED_LEVELING_3POINT
 *   在热床上探测 3 个任意点（不共线）
 *   由你指定这 3 个点的 XY 坐标。
 *   结果是一个倾斜平面。最适合平整的热床。
 *
 * - AUTO_BED_LEVELING_LINEAR
 *   在网格中探测多个点。
 *   由你指定矩形范围和采样点密度。
 *   结果是一个倾斜平面。最适合平整的热床。
 *
 * - AUTO_BED_LEVELING_BILINEAR
 *   在网格中探测多个点。
 *   由你指定矩形范围和采样点密度。
 *   结果是一个网格，最适合较大或不平整的热床。
 *
 * - AUTO_BED_LEVELING_UBL（统一热床调平）
 *   一套综合性的热床调平系统，结合了其他系统的功能与优点。
 *   UBL 还集成了网格生成、网格校验
 *   和网格编辑系统。
 *
 * - MESH_BED_LEVELING
 *   手动探测网格
 *   结果是一个网格，适合较大或不平整的热床。（参见 BILINEAR。）
 *   对于没有探针的机器，网格调平提供了一种分步调平的方法，
 *   可以在每个网格点手动调整 Z 高度。
 *   配合 LCD 控制器时，整个过程会逐步引导。
 */
//#define AUTO_BED_LEVELING_3POINT
//#define AUTO_BED_LEVELING_LINEAR
//#define AUTO_BED_LEVELING_BILINEAR
//#define AUTO_BED_LEVELING_UBL
//#define MESH_BED_LEVELING

/**
 * 通常 G28 结束时会禁用调平。启用以下选项之一，
 * 可恢复之前的调平状态，或在 G28 完成后
 * 立即启用调平。
 */
//#define RESTORE_LEVELING_AFTER_G28
//#define ENABLE_LEVELING_AFTER_G28

/**
 * 自动调平需要预热
 */
//#define PREHEAT_BEFORE_LEVELING
#if ENABLED(PREHEAT_BEFORE_LEVELING)
  #define LEVELING_NOZZLE_TEMP 120   // (°C) 目前仅对 E0 生效
  #define LEVELING_BED_TEMP     50
#endif

/**
 * 热床距离传感器
 *
 * 以 0.01mm 的精度测量热床到喷嘴的距离。
 * 有关此传感器的信息见 https://github.com/markniu/Bed_Distance_sensor
 * 使用 I2C 端口，因此需要 I2C 库 markyue/Panda_SoftMasterI2C。
 */
//#define BD_SENSOR

/**
 * 启用 G28、G29、M48 等命令的详细日志。
 * 使用命令 'M111 S32' 开启。
 * 注意：需要大量 PROGMEM！
 */
//#define DEBUG_LEVELING_FEATURE

#if ANY(MESH_BED_LEVELING, AUTO_BED_LEVELING_UBL, PROBE_MANUALLY)
  // 设置手动调整开始时的高度
  #define MANUAL_PROBE_START_Z 0.2  // (mm) 注释掉即可使用上次测量的高度
#endif

#if ANY(MESH_BED_LEVELING, AUTO_BED_LEVELING_BILINEAR, AUTO_BED_LEVELING_UBL)
  /**
   * 逐渐减小调平修正量，直到达到设定高度，
   * 此后移动将与机器 XY 平面保持水平。
   * 该高度可用 M420 Z<高度> 设置
   */
  #define ENABLE_LEVELING_FADE_HEIGHT
  #if ENABLED(ENABLE_LEVELING_FADE_HEIGHT)
    #define DEFAULT_LEVELING_FADE_HEIGHT 10.0 // (mm) 默认淡出高度。
  #endif

  /**
   * 添加一个作用于规划器层面所有移动的 Z 偏移（M424 Z）。
   * 使用 G29 时该 Z 偏移会自动设为中间值。
   */
  //#define GLOBAL_MESH_Z_OFFSET

  /**
   * 对于笛卡尔机器，不再在网格边界处分段移动，
   * 而是像 Delta 一样把移动拆分为短段。这比边到边的
   * 直线移动更贴合热床的轮廓。
   */
  #define SEGMENT_LEVELED_MOVES
  #define LEVELED_SEGMENT_LENGTH 5.0 // (mm) 所有分段的长度（最后一段除外）

  /**
   * 启用 G26 网格校验图案工具。
   */
  //#define G26_MESH_VALIDATION
  #if ENABLED(G26_MESH_VALIDATION)
    #define MESH_TEST_NOZZLE_SIZE    0.4  // (mm) 主喷嘴直径。
    #define MESH_TEST_LAYER_HEIGHT   0.2  // (mm) G26 的默认层高。
    #define MESH_TEST_HOTEND_TEMP  205    // (°C) G26 的默认喷嘴温度。
    #define MESH_TEST_BED_TEMP      60    // (°C) G26 的默认热床温度。
    #define G26_XY_FEEDRATE         20    // (mm/s) G26 XY 移动的进给速度。
    #define G26_XY_FEEDRATE_TRAVEL 100    // (mm/s) G26 XY 空移的进给速度。
    #define G26_RETRACT_MULTIPLIER   1.0  // 网格测试元素之间默认使用的 G26 Q（回抽）值。
  #endif

#endif

#if EITHER(AUTO_BED_LEVELING_LINEAR, AUTO_BED_LEVELING_BILINEAR)

  // 设置每个维度的网格点数。
  #define GRID_MAX_POINTS_X 3
  #define GRID_MAX_POINTS_Y GRID_MAX_POINTS_X

  // 沿 Y 轴探测，每完成一列后推进 X
  //#define PROBE_Y_FIRST

  #if ENABLED(AUTO_BED_LEVELING_BILINEAR)

    // 超出探测网格后是否延续推断的倾斜？
    // 默认保持最近边缘的高度。
    //#define EXTRAPOLATE_BEYOND_GRID

    //
    // 使用 Catmull-Rom 方法细分网格。
    // 合成中间点以生成更精细的网格。
    //
    //#define ABL_BILINEAR_SUBDIVISION
    #if ENABLED(ABL_BILINEAR_SUBDIVISION)
      // 探测点之间的细分数量
      #define BILINEAR_SUBDIVISIONS 3
    #endif

  #endif

#elif ENABLED(AUTO_BED_LEVELING_UBL)

  //===========================================================================
  //========================= 统一热床调平 ============================
  //===========================================================================

  //#define MESH_EDIT_GFX_OVERLAY   // 编辑网格时显示图形叠加

  #define MESH_INSET 1              // 将网格边界设为热床的内缩区域
  #define GRID_MAX_POINTS_X 10      // 每轴不要超过 15 个点，受实现限制。
  #define GRID_MAX_POINTS_Y GRID_MAX_POINTS_X

  //#define UBL_HILBERT_CURVE       // 使用希尔伯特分布以减少多点探测时的空移

  //#define UBL_TILT_ON_MESH_POINTS         // 配合 G29 J 使用最近的网格点以获得更好的 Z 基准
  //#define UBL_TILT_ON_MESH_POINTS_3POINT  // 配合 G29 J0（三点）使用最近的网格点

  #define UBL_MESH_EDIT_MOVES_Z     // 高级用户偏好喷嘴不做移动
  #define UBL_SAVE_ACTIVE_ON_M500   // M500 时将当前激活的网格保存到当前槽位

  //#define UBL_Z_RAISE_WHEN_OFF_MESH 2.5 // 喷嘴超出网格时使用此值
                                          // 作为 Z 高度修正值。

  //#define UBL_MESH_WIZARD         // 连续运行多条命令以获得完整网格

  /**
   * 障碍物位置范围内不允许探测。
   */
  //#define AVOID_OBSTACLES
  #if ENABLED(AVOID_OBSTACLES)
    #define CLIP_W  23  // 热床压片宽度，应比其物理尺寸多留几毫米
    #define CLIP_H  14  // 热床压片高度，应比其物理尺寸多留几毫米

    // 障碍物矩形，定义为 { X1, Y1, X2, Y2 }
    #define OBSTACLE1 { (X_BED_SIZE) / 4     - (CLIP_W) / 2,                       0, (X_BED_SIZE) / 4     + (CLIP_W) / 2, CLIP_H }
    #define OBSTACLE2 { (X_BED_SIZE) * 3 / 4 - (CLIP_W) / 2,                       0, (X_BED_SIZE) * 3 / 4 + (CLIP_W) / 2, CLIP_H }
    #define OBSTACLE3 { (X_BED_SIZE) / 4     - (CLIP_W) / 2, (Y_BED_SIZE) - (CLIP_H), (X_BED_SIZE) / 4     + (CLIP_W) / 2, Y_BED_SIZE }
    #define OBSTACLE4 { (X_BED_SIZE) * 3 / 4 - (CLIP_W) / 2, (Y_BED_SIZE) - (CLIP_H), (X_BED_SIZE) * 3 / 4 + (CLIP_W) / 2, Y_BED_SIZE }

    // G29 J 的探测网格必须内缩。这没有问题，
    // 因为它仅用于为网格本身计算线性变换。
    #define G29J_MESH_TILT_MARGIN ((CLIP_H) + 1)
  #endif

#elif ENABLED(MESH_BED_LEVELING)

  //===========================================================================
  //=================================== 网格 ==================================
  //===========================================================================

  #define MESH_INSET 10          // 将网格边界设为热床的内缩区域
  #define GRID_MAX_POINTS_X 3    // 每轴不要超过 7 个点，受实现限制。
  #define GRID_MAX_POINTS_Y GRID_MAX_POINTS_X

  //#define MESH_G28_REST_ORIGIN // 所有轴归位后（'G28' 或 'G28 XYZ'）Z 停在 Z_MIN_POS

#endif // BED_LEVELING

/**
 * 为 ABL 或 MBL 添加热床调平子菜单。
 * 若启用手动探测，则包含引导式流程。
 */
//#define LCD_BED_LEVELING

#if ENABLED(LCD_BED_LEVELING)
  #define MESH_EDIT_Z_STEP  0.025 // (mm) 手动探测 Z 轴时的步进量。
  #define LCD_PROBE_Z_RANGE 4     // (mm) 以 Z_MIN_POS 为中心的 Z 调整范围，用于 LCD 调整
  //#define MESH_EDIT_MENU        // 添加编辑网格点的菜单
#endif

// 添加菜单项，在热床四角之间移动以手动调整热床
//#define LCD_BED_TRAMMING

#if ENABLED(LCD_BED_TRAMMING)
  #define BED_TRAMMING_INSET_LFRB { 30, 30, 30, 30 } // (mm) 左、前、右、后的内缩量
  #define BED_TRAMMING_HEIGHT      0.0        // (mm) 校平点处喷嘴的 Z 高度
  #define BED_TRAMMING_Z_HOP       4.0        // (mm) 校平点之间喷嘴的 Z 高度
  //#define BED_TRAMMING_INCLUDE_CENTER       // 最后一个角之后移动到中心
  //#define BED_TRAMMING_USE_PROBE
  #if ENABLED(BED_TRAMMING_USE_PROBE)
    #define BED_TRAMMING_PROBE_TOLERANCE 0.1  // (mm)
    #define BED_TRAMMING_VERIFY_RAISED        // 调整触发探针后，重新探测以验证
    //#define BED_TRAMMING_AUDIO_FEEDBACK
  #endif

  /**
   * 校平角点顺序
   *
   * 设置 2 或 4 个点。若给出 2 个点，第 3 个点为对边中点。
   *
   *  LF  左-前        RF  右-前
   *  LB  左-后        RB  右-后
   *
   * 示例：
   *
   *      默认           {LF,RB,LB,RF}         {LF,RF}           {LB,LF}
   *  LB --------- RB   LB --------- RB    LB --------- RB   LB --------- RB
   *  |  4       3  |   | 3         2 |    |     <3>     |   | 1           |
   *  |             |   |             |    |             |   |          <3>|
   *  |  1       2  |   | 1         4 |    | 1         2 |   | 2           |
   *  LF --------- RF   LF --------- RF    LF --------- RF   LF --------- RF
   */
  #define BED_TRAMMING_LEVELING_ORDER { LF, RF, RB, LB }
#endif

/**
 * G29 探测结束时执行的命令。
 * 用于回抽探针或将 Z 探针移开。
 */
//#define Z_PROBE_END_SCRIPT "G1 Z10 F12000\nG1 X15 Y330\nG1 Z0.5\nG1 Z10"

// @section homing

// 热床中心位于 (X=0, Y=0)
//#define BED_CENTER_AT_0_0

// 手动设置归位位置。留空这些定义则使用自动设置。
// 对于 DELTA，这是笛卡尔打印空间的顶部中心。
//#define MANUAL_X_HOME_POS 0
//#define MANUAL_Y_HOME_POS 0
//#define MANUAL_Z_HOME_POS 0
//#define MANUAL_I_HOME_POS 0
//#define MANUAL_J_HOME_POS 0
//#define MANUAL_K_HOME_POS 0
//#define MANUAL_U_HOME_POS 0
//#define MANUAL_V_HOME_POS 0
//#define MANUAL_W_HOME_POS 0

/**
 * 使用 "Z Safe Homing"（Z 安全归位）以避免在热床区域外用 Z 探针归位。
 *
 * - 在 Z 归位前先将 Z 探针（或喷嘴）移动到预定义的 XY 点。
 * - 仅当 XY 位置已知且可信时才允许 Z 归位。
 * - 如果步进电机驱动进入休眠，Z 归位前可能需要重新进行 XY 归位。
 */
#define Z_SAFE_HOMING

#if ENABLED(Z_SAFE_HOMING)
  #define Z_SAFE_HOMING_X_POINT 0  // Z 归位的 X 点
  #define Z_SAFE_HOMING_Y_POINT 0  // Z 归位的 Y 点
  //#define Z_SAFE_HOMING_POINT_ABSOLUTE  // Z 归位位置忽略归位偏移（M206）
#endif

// 归位速度（直线轴=mm/min，旋转轴=°/min）
#define HOMING_FEEDRATE_MM_M { (200*60), (200*60), (50*60), (50*60), (50*60), (50*60) }

// 验证归位移动时限位开关被触发
#define VALIDATE_HOMING_ENDSTOPS

// @section calibrate

/**
 * 热床偏斜补偿
 *
 * 此功能修正 XYZ 轴的错位。
 *
 * 按以下步骤测量 XY 平面内的热床偏斜：
 *  1. 打印一个测试方块（例如 https://www.thingiverse.com/thing:2563185）
 *  2. 对 XY_DIAG_AC 测量 A 到 C 的对角线
 *  3. 对 XY_DIAG_BD 测量 B 到 D 的对角线
 *  4. 对 XY_SIDE_AD 测量 A 到 D 的边
 *
 * Marlin 会根据这些测量值自动计算偏斜系数。
 * 偏斜系数也可以手动计算并设置：
 *
 *  - 计算 AB     : SQRT(2*AC*AC+2*BD*BD-4*AD*AD)/2
 *  - XY_SKEW_FACTOR : TAN(PI/2-ACOS((AC*AC-AB*AB-AD*AD)/(2*AB*AD)))
 *
 * 如有需要，对 XZ 和 YZ 执行相同的步骤。
 * 参考下图：
 *
 *    Y                     Z                     Z
 *    ^     B-------C       ^     B-------C       ^     B-------C
 *    |    /       /        |    /       /        |    /       /
 *    |   /       /         |   /       /         |   /       /
 *    |  A-------D          |  A-------D          |  A-------D
 *    +-------------->X     +-------------->X     +-------------->Y
 *     XY_SKEW_FACTOR        XZ_SKEW_FACTOR        YZ_SKEW_FACTOR
 */
//#define SKEW_CORRECTION

#if ENABLED(SKEW_CORRECTION)
  // 在此输入所有长度测量值：
  #define XY_DIAG_AC 282.8427124746
  #define XY_DIAG_BD 282.8427124746
  #define XY_SIDE_AD 200

  // 或者，直接设置 XY 偏斜系数：
  //#define XY_SKEW_FACTOR 0.0

  //#define SKEW_CORRECTION_FOR_Z
  #if ENABLED(SKEW_CORRECTION_FOR_Z)
    #define XZ_DIAG_AC 282.8427124746
    #define XZ_DIAG_BD 282.8427124746
    #define YZ_DIAG_AC 282.8427124746
    #define YZ_DIAG_BD 282.8427124746
    #define YZ_SIDE_AD 200

    // 或者，直接设置 Z 偏斜系数：
    //#define XZ_SKEW_FACTOR 0.0
    //#define YZ_SKEW_FACTOR 0.0
  #endif

  // 启用此选项后可用 M852 在运行时设置偏斜
  //#define SKEW_CORRECTION_GCODE
#endif

//=============================================================================
//============================= 附加功能 ===========================
//=============================================================================

// @section eeprom

/**
 * EEPROM
 *
 * 持久化存储，可在重启后保留可配置的设置。
 *
 *   M500 - 将设置保存到 EEPROM。
 *   M501 - 从 EEPROM 读取设置。（即丢弃未保存的更改）
 *   M502 - 将设置恢复为"出厂"默认值。（之后执行 M500 以初始化 EEPROM。）
 */
//#define EEPROM_SETTINGS     // 通过 M500 和 M501 进行持久化存储
//#define DISABLE_M503        // 可节省约 2700 字节闪存。发布版本请禁用！
#define EEPROM_CHITCHAT       // 对 EEPROM 命令给出反馈。禁用以节省 PROGMEM。
#define EEPROM_BOOT_SILENT    // 让 M503 保持安静，仅在首次加载时报错
#if ENABLED(EEPROM_SETTINGS)
  //#define EEPROM_AUTO_INIT  // 出错时自动初始化 EEPROM。
  //#define EEPROM_INIT_NOW   // 新固件首次启动时初始化 EEPROM。
#endif

// @section host

//
// 主机保活
//
// 启用后，当 Marlin 无法接受命令时，
// 会每隔几秒向主机发送一条忙碌状态消息。
//
#define HOST_KEEPALIVE_FEATURE        // 如果你的主机不喜欢保活消息，请禁用此项
#define DEFAULT_KEEPALIVE_INTERVAL 2  // "busy" 消息之间的秒数。可用 M113 设置。
#define BUSY_WHILE_HEATING            // 某些主机在加热期间也要求 "busy" 消息

// @section units

//
// G20/G21 英寸模式支持
//
//#define INCH_MODE_SUPPORT

//
// M149 设置温度单位支持
//
//#define TEMPERATURE_UNITS_SUPPORT

// @section temperature

//
// 预热常量 - 无需修改即可支持多达 10 组
//
#define PREHEAT_1_LABEL       "PLA"
#define PREHEAT_1_TEMP_HOTEND 180
#define PREHEAT_1_TEMP_BED     70
#define PREHEAT_1_TEMP_CHAMBER 35
#define PREHEAT_1_FAN_SPEED     0 // 数值范围 0 到 255

#define PREHEAT_2_LABEL       "ABS"
#define PREHEAT_2_TEMP_HOTEND 240
#define PREHEAT_2_TEMP_BED    110
#define PREHEAT_2_TEMP_CHAMBER 35
#define PREHEAT_2_FAN_SPEED     0 // 数值范围 0 到 255

// @section motion

/**
 * 喷嘴停靠
 *
 * 在空闲或 G27 时将喷嘴停靠到给定的 XYZ 位置。
 *
 * "P" 参数控制对 Z 轴执行的动作：
 *
 *    P0  （默认）若 Z 低于停靠 Z 高度则抬起喷嘴。
 *    P1  始终将喷嘴抬升至 Z 停靠高度。
 *    P2  将喷嘴抬升 Z 停靠量，上限为 Z_MAX_POS。
 */
//#define NOZZLE_PARK_FEATURE

#if ENABLED(NOZZLE_PARK_FEATURE)
  // 以 { X, Y, Z_raise } 的形式指定停靠位置
  #define NOZZLE_PARK_POINT { (X_MIN_POS + 10), (Y_MAX_POS - 10), 20 }
  #define NOZZLE_PARK_MOVE          0   // 停靠运动：0 = XY 移动，1 = 仅 X，2 = 仅 Y，3 = 先 X 后 Y，4 = 先 Y 后 X
  #define NOZZLE_PARK_Z_RAISE_MIN   2   // (mm) Z 抬升量至少为此距离
  #define NOZZLE_PARK_XY_FEEDRATE 100   // (mm/s) X 和 Y 轴的进给速度（Delta 的 Z 轴也使用此值）
  #define NOZZLE_PARK_Z_FEEDRATE    5   // (mm/s) Z 轴的进给速度（Delta 打印机不使用）
#endif

/**
 * 清洁喷嘴功能
 *
 * 添加 G12 命令以执行喷嘴清洁过程。
 *
 * 参数：
 *   P  图案
 *   S  擦拭次数 / 重复次数
 *   T  三角形数量（仅 P1）
 *
 * 图案：
 *   P0  直线（默认）。此过程需要在热床固定位置
 *       放置海绵类材料。"S" 指定起点/终点之间
 *       的擦拭次数（即往返动作）。
 *
 *   P1  在 (X0, Y0) 与 (X1, Y1) 之间呈之字形移动，"T" 指定
 *       之字形三角形的数量。"S" 定义擦拭次数。
 *       之字形沿较窄的方向进行。
 *       例如，"G12 P1 S1 T3" 将执行：
 *
 *          --
 *         |  (X0, Y1) |     /\        /\        /\     | (X1, Y1)
 *         |           |    /  \      /  \      /  \    |
 *       A |           |   /    \    /    \    /    \   |
 *         |           |  /      \  /      \  /      \  |
 *         |  (X0, Y0) | /        \/        \/        \ | (X1, Y0)
 *          --         +--------------------------------+
 *                       |________|_________|_________|
 *                           T1        T2        T3
 *
 *   P2  以 NOZZLE_CLEAN_CIRCLE_MIDDLE 为中心的圆形图案。
 *       "R" 指定半径。"S" 指定擦拭次数。
 *       开始前，喷嘴先移动到 NOZZLE_CLEAN_START_POINT。
 *
 *   注意事项：结束时的 Z 应与起始 Z 相同。
 */
//#define NOZZLE_CLEAN_FEATURE

#if ENABLED(NOZZLE_CLEAN_FEATURE)
  // 图案重复次数的默认值
  #define NOZZLE_CLEAN_STROKES  12

  // 三角形数量的默认值
  #define NOZZLE_CLEAN_TRIANGLES  3

  // 以 { { X, Y, Z }, { X, Y, Z } } 的形式为每个工具指定位置
  // 双热端系统可使用 { {  -20, (Y_BED_SIZE / 2), (Z_MIN_POS + 1) },  {  420, (Y_BED_SIZE / 2), (Z_MIN_POS + 1) }}
  #define NOZZLE_CLEAN_START_POINT { {  30, 30, (Z_MIN_POS + 1) } }
  #define NOZZLE_CLEAN_END_POINT   { { 100, 60, (Z_MIN_POS + 1) } }

  // 圆形图案的半径
  #define NOZZLE_CLEAN_CIRCLE_RADIUS 6.5
  // 圆形图案的圆弧分段数
  #define NOZZLE_CLEAN_CIRCLE_FN 10
  // 圆心点
  #define NOZZLE_CLEAN_CIRCLE_MIDDLE NOZZLE_CLEAN_START_POINT

  // 清洁后将喷嘴移回初始位置
  #define NOZZLE_CLEAN_GOBACK

  // 对于始终位于龙门高度（因而无需 Z 移动）的挤出/清洁站
  //#define NOZZLE_CLEAN_NO_Z

  // 对于安装在 X 轴上的挤出/清洁站
  //#define NOZZLE_CLEAN_NO_Y

  // 清洁所需的最低热端温度
  #define NOZZLE_CLEAN_MIN_TEMP 170
  //#define NOZZLE_CLEAN_HEATUP       // 加热喷嘴而不是跳过擦拭

  // 显式擦拭 G 代码脚本，适用于不带参数的 G12。
  //#define WIPE_SEQUENCE_COMMANDS "G1 X-17 Y25 Z10 F4000\nG1 Z1\nM114\nG1 X-17 Y25\nG1 X-17 Y95\nG1 X-17 Y25\nG1 X-17 Y95\nG1 X-17 Y25\nG1 X-17 Y95\nG1 X-17 Y25\nG1 X-17 Y95\nG1 X-17 Y25\nG1 X-17 Y95\nG1 X-17 Y25\nG1 X-17 Y95\nG1 Z15\nM400\nG0 X-10.0 Y-9.0"

#endif

// @section host

/**
 * 打印任务计时器
 *
 * 在 M104/M109/M140/M190/M141/M191 时自动启动和停止打印任务计时器。
 * 只有当热床/腔室目标温度低于 BED_MINTEMP/CHAMBER_MINTEMP 时，
 * 打印任务计时器才会停止。
 *
 *   M104 （热端，不等待）- 高温 = 无动作，     低温 = 停止计时器
 *   M109 （热端，等待）  - 高温 = 启动计时器， 低温 = 停止计时器
 *   M140 （热床，不等待）- 高温 = 无动作，     低温 = 停止计时器
 *   M190 （热床，等待）  - 高温 = 启动计时器， 低温 = 无动作
 *   M141 （腔室，不等待）- 高温 = 无动作，     低温 = 停止计时器
 *   M191 （腔室，等待）  - 高温 = 启动计时器， 低温 = 无动作
 *
 * 对于 M104/M109，高温指超过 EXTRUDE_MINTEMP / 2 的任何温度。
 * 对于 M140/M190，高温指超过 BED_MINTEMP 的任何温度。
 * 对于 M141/M191，高温指超过 CHAMBER_MINTEMP 的任何温度。
 *
 * 还可以使用以下命令控制计时器：
 *
 *   M75 - 启动打印任务计时器
 *   M76 - 暂停打印任务计时器
 *   M77 - 停止打印任务计时器
 */
#define PRINTJOB_TIMER_AUTOSTART

// @section stats

/**
 * 打印计数器
 *
 * 跟踪统计数据，例如：
 *
 *  - 总打印任务数
 *  - 总成功打印任务数
 *  - 总失败打印任务数
 *  - 总打印时间
 *
 * 使用 M78 查看当前统计数据。
 */
//#define PRINTCOUNTER
#if ENABLED(PRINTCOUNTER)
  #define PRINTCOUNTER_SAVE_INTERVAL 60 // (minutes) 打印期间的 EEPROM 保存间隔。设为 0 则在打印结束时保存统计数据。
#endif

// @section security

/**
 * 密码
 *
 * 为打印机设置一个数字密码，可在以下情况要求输入：
 *
 *  - 打印机启动时
 *  - 打开"从介质打印"菜单时
 *  - SD 卡打印完成或中止时
 *
 * 可使用以下 G 代码：
 *
 *  M510 - 锁定打印机。阻止除 M511 之外的所有命令。
 *  M511 - 解锁打印机。
 *  M512 - 设置、更改和删除密码。
 *
 * 如果忘记密码而被锁在门外，你需要用禁用该功能的
 * 固件重新刷机、重置 EEPROM，然后（可选）再刷入
 * 启用该功能的固件。
 */
//#define PASSWORD_FEATURE
#if ENABLED(PASSWORD_FEATURE)
  #define PASSWORD_LENGTH 4                 // (#) 位数（1-9）。建议 3 或 4 位
  #define PASSWORD_ON_STARTUP
  #define PASSWORD_UNLOCK_GCODE             // 使用 M511 P<密码> 命令解锁。禁用以防暴力破解。
  #define PASSWORD_CHANGE_GCODE             // 使用 M512 P<旧密码> S<新密码> 更改密码。
  //#define PASSWORD_ON_SD_PRINT_MENU       // 这并不能阻止 G 代码运行
  //#define PASSWORD_AFTER_SD_PRINT_END
  //#define PASSWORD_AFTER_SD_PRINT_ABORT
  //#include "Configuration_Secure.h"       // 包含 PASSWORD_DEFAULT_VALUE 的外部文件
#endif

//=============================================================================
//============================= LCD 和 SD 支持 ============================
//=============================================================================

// @section interface

/**
 * LCD 语言
 *
 * 选择要在 LCD 上显示的语言。可用语言如下：
 *
 *   en, an, bg, ca, cz, da, de, el, el_CY, es, eu, fi, fr, gl, hr, hu, it,
 *   jp_kana, ko_KR, nl, pl, pt, pt_br, ro, ru, sk, sv, tr, uk, vi, zh_CN, zh_TW
 *
 * :{ 'en':'English', 'an':'Aragonese', 'bg':'Bulgarian', 'ca':'Catalan', 'cz':'Czech', 'da':'Danish', 'de':'German', 'el':'Greek (Greece)', 'el_CY':'Greek (Cyprus)', 'es':'Spanish', 'eu':'Basque-Euskera', 'fi':'Finnish', 'fr':'French', 'gl':'Galician', 'hr':'Croatian', 'hu':'Hungarian', 'it':'Italian', 'jp_kana':'Japanese', 'ko_KR':'Korean (South Korea)', 'nl':'Dutch', 'pl':'Polish', 'pt':'Portuguese', 'pt_br':'Portuguese (Brazilian)', 'ro':'Romanian', 'ru':'Russian', 'sk':'Slovak', 'sv':'Swedish', 'tr':'Turkish', 'uk':'Ukrainian', 'vi':'Vietnamese', 'zh_CN':'Chinese (Simplified)', 'zh_TW':'Chinese (Traditional)' }
 */
#define LCD_LANGUAGE en

/**
 * LCD 字符集
 *
 * 注意：此选项不适用于图形显示屏。
 *
 * 所有字符型 LCD 都提供 ASCII 以及以下一种
 * 语言扩展：
 *
 *  - JAPANESE ... 最常见
 *  - WESTERN  ... 带更多重音字符
 *  - CYRILLIC ... 用于俄语
 *
 * 确定控制器上安装的语言扩展的方法：
 *
 *  - 将 LCD_LANGUAGE 设为 'test' 后编译并上传
 *  - 点击控制器查看 LCD 菜单
 *  - LCD 将显示日文、西文或西里尔文本
 *
 * 参见 https://marlinfw.org/docs/development/lcd_language.html
 *
 * :['JAPANESE', 'WESTERN', 'CYRILLIC']
 */
#define DISPLAY_CHARSET_HD44780 JAPANESE

/**
 * 信息屏样式（0:经典，1:Průša）
 *
 * :[0:'Classic', 1:'Průša']
 */
#define LCD_INFO_SCREEN_STYLE 0

/**
 * SD 卡
 *
 * SD 卡支持默认禁用。如果你的控制器带有 SD 卡槽，
 * 必须取消注释以下选项，否则无法使用。
 */
//#define SDSUPPORT

/**
 * SD 卡：启用 CRC
 *
 * 在 SD 通信中使用 CRC 校验和重试。
 */
//#define SD_CHECK_AND_RETRY

/**
 * LCD 菜单项
 *
 * 禁用所有菜单，仅显示状态屏，或者
 * 只移除一些多余的菜单项以回收空间。
 */
//#define NO_LCD_MENUS
//#define SLIM_LCD_MENUS

//
// 编码器设置
//
// 此选项覆盖产生一步所需的默认编码器脉冲数。
// 高分辨率编码器应增大此值。
//
//#define ENCODER_PULSES_PER_STEP 4

//
// 使用此选项可覆盖在下一个/上一个菜单项之间
// 移动所需的步进信号数量。
//
//#define ENCODER_STEPS_PER_MENU_ITEM 1

/**
 * 编码器方向选项
 *
 * 请先在两个选项都禁用的情况下测试编码器的行为。
 *
 *  数值编辑和菜单导航都反向？启用 REVERSE_ENCODER_DIRECTION。
 *  仅菜单导航反向？         启用 REVERSE_MENU_DIRECTION。
 *  仅数值编辑反向？         启用这两个选项。
 */

//
// 此选项在所有地方反转编码器方向。
//
//  如果顺时针导致数值减小，请设置此选项
//
//#define REVERSE_ENCODER_DIRECTION

//
// 此选项用于导航 LCD 菜单时反转编码器方向。
//
//  如果顺时针通常向下移动，此项将使其向上移动。
//  如果顺时针通常向上移动，此项将使其向下移动。
//
//#define REVERSE_MENU_DIRECTION

//
// 此选项反转选择屏幕的编码器方向。
//
//  如果顺时针旋转通常向左移动，此选项会使其向右移动。
//  如果顺时针旋转通常向右移动，此选项会使其向左移动。
//
//#define REVERSE_SELECT_DIRECTION

//
// 编码器 EMI 噪声滤波器
//
// 此选项增加编码器采样次数，以滤除由 EMI 噪声引起的幻影编码器点击。
//
//#define ENCODER_NOISE_FILTER
#if ENABLED(ENCODER_NOISE_FILTER)
  #define ENCODER_SAMPLES 10
#endif

//
// 单轴归位
//
// 在 LCD 菜单中添加单轴归位选项（归位 X、归位 Y 和归位 Z）。
//
//#define INDIVIDUAL_AXIS_HOMING_MENU
//#define INDIVIDUAL_AXIS_HOMING_SUBMENU

//
// 扬声器/蜂鸣器
//
// 如果你有一个可以发出音调的扬声器，请在此启用。
// 默认情况下，Marlin 假定你使用的是固定频率的蜂鸣器。
//
//#define SPEAKER

//
// UI 反馈声音的持续时间和频率。
// 将这些值设为 0 可禁用 LCD 菜单中的声音反馈。
//
// 注意：使用以下 G 代码测试音频输出：
//  M300 S<频率 Hz> P<持续时间 ms>
//
//#define LCD_FEEDBACK_FREQUENCY_DURATION_MS 2
//#define LCD_FEEDBACK_FREQUENCY_HZ 5000

//=============================================================================
//======================== LCD / 控制器选择 =========================
//========================   （字符型 LCD）   =========================
//=============================================================================
// @section lcd

//
// RepRapDiscount Smart Controller。
// https://reprap.org/wiki/RepRapDiscount_Smart_Controller
//
// 注意：通常与白色 PCB 一起出售。
//
//#define REPRAP_DISCOUNT_SMART_CONTROLLER

//
// GT2560 (YHCB2004) LCD 显示屏
//
// 需要 Testato、Koepel 的 softwarewire 库以及
// Andriy Golovnya 的 LiquidCrystal_AIP31068 库。
//
//#define YHCB2004

//
// 原装 RADDS LCD 显示屏+编码器+SD 卡读卡器
// http://doku.radds.org/dokumentation/lcd-display/
//
//#define RADDS_DISPLAY

//
// ULTIMAKER 控制器。
//
//#define ULTIMAKERCONTROLLER

//
// Thingiverse 上的 ULTIPANEL。
//
//#define ULTIPANEL

//
// 来自 T3P3 的 PanelOne（通过 RAMPS 1.4 AUX2/AUX3）
// https://reprap.org/wiki/PanelOne
//
//#define PANEL_ONE

//
// GADGETS3D G3D LCD/SD 控制器
// https://reprap.org/wiki/RAMPS_1.3/1.4_GADGETS3D_Shield_with_Panel
//
// 注意：通常与蓝色 PCB 一起出售。
//
//#define G3D_PANEL

//
// RigidBot 面板 V1.0
// http://www.inventapart.com/
//
//#define RIGIDBOT_PANEL

//
// Makeboard 3D 打印机配件 3D 打印机迷你显示屏 1602 迷你控制器
// https://www.aliexpress.com/item/32765887917.html
//
//#define MAKEBOARD_MINI_2_LINE_DISPLAY_1602

//
// ANET 和 Tronxy 20x4 控制器
//
//#define ZONESTAR_LCD            // 需要将 ADC_KEYPAD_PIN 分配给模拟引脚。
                                  // 已知此 LCD 容易受电气干扰影响，
                                  // 导致显示乱码。按下任意按钮即可恢复。
                                  // 这是一块带 5 个模拟按钮的 LCD2004 显示屏。

//
// 通用 16x2、16x4、20x2 或 20x4 字符型 LCD。
//
//#define ULTRA_LCD

//=============================================================================
//======================== LCD / 控制器选择 =========================
//=====================   （I2C 和移位寄存器 LCD）   =====================
//=============================================================================

//
// 控制器类型：I2C
//
// 注意：这些控制器需要安装 Arduino 的 LiquidCrystal_I2C
// 库。更多信息请见：https://github.com/kiyoshigawa/LiquidCrystal_I2C
//

//
// Elefu RA 板控制面板
// https://web.archive.org/web/20140823033947/http://www.elefu.com/index.php?route=product/product&product_id=53
//
//#define RA_CONTROL_PANEL

//
// Sainsmart (YwRobot) LCD 显示屏
//
// 这些显示屏需要 F.Malpartida 的 LiquidCrystal_I2C 库
// https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home
//
//#define LCD_SAINSMART_I2C_1602
//#define LCD_SAINSMART_I2C_2004

//
// 通用 LCM1602 LCD 适配器
//
//#define LCM1602

//
// 带状态 LED 的 PANELOLU2 LCD，
// 编码器和点击输入相互独立。
//
// 注意：此控制器需要 Arduino 的 LiquidTWI2 库 v1.2.3 或更高版本。
// 更多信息请见：https://github.com/lincomatic/LiquidTWI2
//
// 注意：PANELOLU2 编码器的点击输入既可以直接连接到
// 引脚（若 BTN_ENC 定义为 != -1），也可以通过 I2C 读取（当 BTN_ENC == -1 时）。
//
//#define LCD_I2C_PANELOLU2

//
// 带状态 LED 的 Panucatt VIKI LCD，
// 集成点击与左/右/上/下按钮，编码器输入独立。
//
//#define LCD_I2C_VIKI

//
// 控制器类型：移位寄存器面板
//

//
// 来自 https://goo.gl/aJJ4sH 的两线非锁存 LCD SR
// LCD 配置：https://reprap.org/wiki/SAV_3D_LCD
//
//#define SAV_3DLCD

//
// 使用 74HC4094 带选通信号的三线 SR LCD
// https://github.com/mikeshub/SailfishLCD
// 直接使用 Sailfish 的代码
//
//#define FF_INTERFACEBOARD

//
// 配 Marlin UI 的 TFT GLCD 面板
// 面板通过 SPI 或 I2C 接口连接到主板。
// 见 https://github.com/Serhiy-K/TFTGLCDAdapter
//
//#define TFTGLCD_PANEL_SPI
//#define TFTGLCD_PANEL_I2C

//=============================================================================
//=======================   LCD / 控制器选择  =======================
//=========================      （图形 LCD）      ========================
//=============================================================================

//
// 控制器类型：图形 128x64 (DOGM)
//
// 重要：图形显示屏需要 U8glib 库！
//            https://github.com/olikraus/U8glib_Arduino
//
// 注意：如果 LCD 无响应，你可能需要反转插头方向。
//

//
// RepRapDiscount 全图形智能控制器
// https://reprap.org/wiki/RepRapDiscount_Full_Graphic_Smart_Controller
//
//#define REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER

//
// K.3D 全图形智能控制器
//
//#define K3D_FULL_GRAPHIC_SMART_CONTROLLER

//
// ReprapWorld 图形 LCD
// https://reprapworld.com/electronics/3d-printer-modules/autonomous-printing/graphical-lcd-screen-v1-0/
//
//#define REPRAPWORLD_GRAPHICAL_LCD

//
// 如果你有 Panucatt Devices 的
// Viki 2.0 或带图形 LCD 的 mini Viki，请启用以下选项之一。
// https://www.panucatt.com
//
//#define VIKI2
//#define miniVIKI

//
// Alfawise Ex8 打印机 LCD，标记为 WYH L12864 COG
//
//#define WYH_L12864

//
// MakerLab 带图形控制器和 SD 支持
// 的迷你面板 - https://reprap.org/wiki/Mini_panel
//
//#define MINIPANEL

//
// MaKr3d 带图形控制器和 SD 支持的 Makr-Panel。
// https://reprap.org/wiki/MaKr3d_MaKrPanel
//
//#define MAKRPANEL

//
// Adafruit ST7565 全图形控制器。
// https://github.com/eboston/Adafruit-ST7565-Full-Graphic-Controller/
//
//#define ELB_FULL_GRAPHIC_CONTROLLER

//
// BQ LCD 智能控制器，
// 随 BQ Hephestos 2 和 Witbox 2 默认附带。
//
//#define BQ_LCD_SMART_CONTROLLER

//
// Cartesio UI
// http://mauk.cc/webshop/cartesio-shop/electronics/user-interface
//
//#define CARTESIO_UI

//
// 配图形 LCD 的 Melzi 卡 LCD
//
//#define LCD_FOR_MELZI

//
// 来自 Ultimaker 2 打印机的原装 Ulticontroller，带 SSD1309 I2C 显示屏和编码器
// https://github.com/Ultimaker/Ultimaker2/tree/master/1249_Ulticontroller_Board_(x1)
//
//#define ULTI_CONTROLLER

//
// 带图形控制器和 SD 支持的 MKS MINI12864
// https://reprap.org/wiki/MKS_MINI_12864
//
//#define MKS_MINI_12864

//
// MKS MINI12864 V3 是 FYSETC_MINI_12864_2_1 的别名。A/B 型。NeoPixel RGB 背光。
//
//#define MKS_MINI_12864_V3

//
// 带图形控制器和 SD 支持的 MKS LCD12864A/B。引脚布局与 MKS_MINI_12864 相同。
// https://www.aliexpress.com/item/33018110072.html
//
//#define MKS_LCD12864A
//#define MKS_LCD12864B

//
// FYSETC 版本的 MINI12864 图形控制器，带 SD 支持
// https://wiki.fysetc.com/Mini12864_Panel/
//
//#define FYSETC_MINI_12864_X_X    // C/D/E/F 型。默认无可调 RGB 背光
//#define FYSETC_MINI_12864_1_2    // C/D/E/F 型。简易 RGB 背光（常亮）
//#define FYSETC_MINI_12864_2_0    // A/B 型。低调 RGB 背光
//#define FYSETC_MINI_12864_2_1    // A/B 型。NeoPixel RGB 背光
//#define FYSETC_GENERIC_12864_1_1 // 更大的显示屏，仅有基本的开/关背光。

//
// BigTreeTech Mini 12864 V1.0 是 FYSETC_MINI_12864_2_1 的别名。A/B 型。NeoPixel RGB 背光。
//
//#define BTT_MINI_12864_V1

//
// 创想三维 CR-10 的原装显示屏
// https://www.aliexpress.com/item/32833148327.html
//
// 使用单个 10 针连接器，与 RAMPS 兼容。
// （适用于想更换 Melzi 创想主板但保留显示屏的 CR-10 用户）
//
//#define CR10_STOCKDISPLAY

//
// Ender-2 原装显示屏，MKS_MINI_12864 的变体
//
//#define ENDER2_STOCKDISPLAY

//
// ANET 和 Tronxy 图形控制器
//
// Anet A6 上使用的 Anet 128x64 全图形 LCD，带旋转编码器，
// 是 RepRapDiscount 全图形显示屏的克隆版，但
// 引脚/接线不同（见 pins_ANET_10.h）。启用以下选项之一。
//
//#define ANET_FULL_GRAPHICS_LCD
//#define ANET_FULL_GRAPHICS_LCD_ALT_WIRING

//
// 带 SD 的 AZSMZ 12864 LCD
// https://www.aliexpress.com/item/32837222770.html
//
//#define AZSMZ_12864

//
// Silvergate GLCD 控制器
// https://github.com/android444/Silvergate
//
//#define SILVER_GATE_GLCD_CONTROLLER

//
// 带 SD 的 eMotion Tech LCD
// https://www.reprap-france.com/produit/1234568748-ecran-graphique-128-x-64-points-2-1
//
//#define EMOTION_TECH_LCD

//=============================================================================
//==============================  OLED 显示屏  ==============================
//=============================================================================

//
// SSD1306 OLED 全图形通用显示屏
//
//#define U8GLIB_SSD1306

//
// SAV OLEd LCD 模块支持，使用基于 SSD1306 或 SH1106 的 LCD 模块
//
//#define SAV_3DGLCD
#if ENABLED(SAV_3DGLCD)
  #define U8GLIB_SSD1306
  //#define U8GLIB_SH1106
#endif

//
// TinyBoy2 128x64 OLED / 编码器面板
//
//#define OLED_PANEL_TINYBOY2

//
// MKS OLED 1.3" 128×64 全图形控制器
// https://reprap.org/wiki/MKS_12864OLED
//
// 小巧但非常锐利的 OLED 显示屏
//
//#define MKS_12864OLED          // 使用 SH1106 控制器（默认）
//#define MKS_12864OLED_SSD1306  // 使用 SSD1306 控制器

//
// Zonestar OLED 128×64 全图形控制器
//
//#define ZONESTAR_12864LCD           // 图形（DOGM），带 ST7920 控制器
//#define ZONESTAR_12864OLED          // 1.3" OLED，带 SH1106 控制器（默认）
//#define ZONESTAR_12864OLED_SSD1306  // 0.96" OLED，带 SSD1306 控制器

//
// Einstart S OLED SSD1306
//
//#define U8GLIB_SH1106_EINSTART

//
// Overlord OLED 显示屏/控制器，带 i2c 蜂鸣器和 LED
//
//#define OVERLORD_OLED

//
// FYSETC OLED 2.42" 128×64 全图形控制器，带 WS2812 RGB
// 购买地址：https://www.aliexpress.com/item/4000345255731.html
//#define FYSETC_242_OLED_12864   // 使用 SSD1309 控制器

//
// K.3D SSD1309 OLED 2.42" 128×64 全图形控制器
//
//#define K3D_242_OLED_CONTROLLER   // 软件 SPI

//=============================================================================
//========================== 可扩展 UI 显示屏 ===========================
//=============================================================================

/**
 * 带 DWIN OS 的 DGUS 触摸显示屏。（选择其一。）
 *
 * ORIGIN (Marlin DWIN_SET)
 *  - 下载 https://github.com/coldtobi/Marlin_DGUS_Resources
 *  - 将下载的 DWIN_SET 文件夹复制到 SD 卡。
 *  - 产品：https://www.aliexpress.com/item/32993409517.html
 *
 * FYSETC（供应商默认）
 *  - 下载 https://github.com/FYSETC/FYSTLCD-2.0
 *  - 将下载的 SCREEN 文件夹复制到 SD 卡。
 *  - 产品：https://www.aliexpress.com/item/32961471929.html
 *
 * HIPRECY（供应商默认）
 *  - 下载 https://github.com/HiPrecy/Touch-Lcd-LEO
 *  - 将下载的 DWIN_SET 文件夹复制到 SD 卡。
 *
 * MKS (MKS-H43)（供应商默认）
 *  - 下载 https://github.com/makerbase-mks/MKS-H43
 *  - 将下载的 DWIN_SET 文件夹复制到 SD 卡。
 *  - 产品：https://www.aliexpress.com/item/1005002008179262.html
 *
 * RELOADED (T5UID1)
 *  - 下载 https://github.com/Neo2003/DGUS-reloaded/releases
 *  - 将下载的 DWIN_SET 文件夹复制到 SD 卡。
 *
 * IA_CREALITY (T5UID1)
 *  - 下载 https://github.com/InsanityAutomation/Marlin/raw/CrealityDwin_2.0/TM3D_Combined480272_Landscape_V7.7z
 *  - 将下载的 DWIN_SET 文件夹复制到 SD 卡。
 *
 * CREALITY_TOUCH
 *  - CR-6 原装触摸屏。带触摸功能的 DWIN 显示屏。
 *
 * 为 Marlin 刷写 DGUS 显示屏：
 *  - 将 SD 卡格式化为 FAT32，分配单元大小为 4kb。
 *  - 按你的显示屏类型下载指定文件。
 *  - 将 microSD 卡插入显示屏背面。
 *  - 启动显示屏并等待更新完成。
 *
 * :[ 'ORIGIN', 'FYSETC', 'HYPRECY', 'MKS', 'RELOADED', 'IA_CREALITY' ]
 */
//#define DGUS_LCD_UI ORIGIN
#if DGUS_UI_IS(MKS)
  #define USE_MKS_GREEN_UI
#elif DGUS_UI_IS(IA_CREALITY)
  //#define LCD_SCREEN_ROTATE 90          // 竖屏模式或 800x480 显示屏
  //#define IA_CREALITY_BOOT_DELAY 1500   // (ms)
#endif

//
// Malyan M200/M300 打印机的触摸屏 LCD
//
//#define MALYAN_LCD

//
// FTDI EVE (FT800/FT810) 显示屏的触摸 UI
// 所有配置选项见 Configuration_adv.h。
//
//#define TOUCH_UI_FTDI_EVE

//
// Anycubic Chiron 的触摸屏 LCD
//
//#define ANYCUBIC_LCD_CHIRON

//
// Anycubic i3 Mega 的触摸屏 LCD
//
//#define ANYCUBIC_LCD_I3MEGA
#if ENABLED(ANYCUBIC_LCD_I3MEGA)
  //#define ANYCUBIC_LCD_GCODE_EXT  // 为兼容 DGUS 克隆屏，在菜单条目中添加 ".gcode"
#endif

//
// Anycubic Vyper 的触摸屏 LCD
//
//#define ANYCUBIC_LCD_VYPER

//
// 320x240 Nextion 2.8" 串行 TFT 电阻式触摸屏 NX3224T028
//
//#define NEXTION_TFT

//
// Escher3D 的 PanelDue 触摸控制器
// http://escher3d.com/pages/order/products/product2.php
//
//#define PANELDUE

//
// 第三方或厂商定制的控制器界面。
// 源码应安装到 'src/lcd/extui' 中。
//
//#define EXTENSIBLE_UI

#if ENABLED(EXTENSIBLE_UI)
  //#define EXTUI_LOCAL_BEEPER // 允许外接显示屏使用本地蜂鸣器引脚
#endif

//=============================================================================
//=============================== 图形 TFT ==============================
//=============================================================================

/**
 * 特定 TFT 型号预设。启用以下选项之一，
 * 或启用 TFT_GENERIC 并设置子选项。
 */

//
// 480x320, 3.5"，MKS 的 SPI 显示屏，带旋转编码器
// 通常与 MKS Robin Nano V2 和 V3 配对使用
//
//#define MKS_TS35_V2_0

//
// 320x240, 2.4"，MKS 的 FSMC 显示屏
// 通常与 MKS Robin Nano V1.2 配对使用
//
//#define MKS_ROBIN_TFT24

//
// 320x240, 2.8"，MKS 的 FSMC 显示屏
// 通常与 MKS Robin Nano V1.2 配对使用
//
//#define MKS_ROBIN_TFT28

//
// 320x240, 3.2"，MKS 的 FSMC 显示屏
// 通常与 MKS Robin Nano V1.2 配对使用
//
//#define MKS_ROBIN_TFT32

//
// 480x320, 3.5"，MKS 的 FSMC 显示屏
// 通常与 MKS Robin Nano V1.2 配对使用
//
//#define MKS_ROBIN_TFT35

//
// 480x272, 4.3"，MKS 的 FSMC 显示屏
//
//#define MKS_ROBIN_TFT43

//
// 320x240, 3.2"，MKS 的 FSMC 显示屏
// 通常与 MKS Robin 配对使用
//
//#define MKS_ROBIN_TFT_V1_1R

//
// 480x320, 3.5"，Tronxy 的 FSMC 原装显示屏
//
//#define TFT_TRONXY_X5SA

//
// 480x320, 3.5"，AnyCubic 的 FSMC 原装显示屏
//
//#define ANYCUBIC_TFT35

//
// 320x240, 2.8"，Longer/Alfawise 的 FSMC 原装显示屏
//
//#define LONGER_LK_TFT28

//
// 320x240, 2.8"，ET4 的 FSMC 原装显示屏
//
//#define ANET_ET4_TFT28

//
// 480x320, 3.5"，ET5 的 FSMC 原装显示屏
//
//#define ANET_ET5_TFT35

//
// 1024x600, 7"，BIQU-BX 的 RGB 原装显示屏，带旋转编码器
//
//#define BIQU_BX_TFT70

//
// 480x320, 3.5"，BIQU B1 SE 系列的 SPI 原装显示屏，带旋转编码器
//
//#define BTT_TFT35_SPI_V1_0

//
// 通用 TFT，带详细选项
//
//#define TFT_GENERIC
#if ENABLED(TFT_GENERIC)
  // :[ 'AUTO', 'ST7735', 'ST7789', 'ST7796', 'R61505', 'ILI9328', 'ILI9341', 'ILI9488' ]
  #define TFT_DRIVER AUTO

  // 接口。启用以下选项之一：
  //#define TFT_INTERFACE_FSMC
  //#define TFT_INTERFACE_SPI

  // TFT 分辨率。启用以下选项之一：
  //#define TFT_RES_320x240
  //#define TFT_RES_480x272
  //#define TFT_RES_480x320
  //#define TFT_RES_1024x600
#endif

/**
 * TFT UI - 用户界面选择。启用以下选项之一：
 *
 *   TFT_CLASSIC_UI - 模拟 DOGM - 128x64 放大显示
 *   TFT_COLOR_UI   - Marlin 默认菜单，触控友好，充分利用 TFT 性能
 *   TFT_LVGL_UI    - 使用 LVGL 的现代 UI
 *
 *   对于 LVGL_UI，还需将构建目录中的 'assets' 文件夹与
 *   编译好的固件一起复制到 SD 卡根目录。
 */
//#define TFT_CLASSIC_UI
//#define TFT_COLOR_UI
//#define TFT_LVGL_UI

#if ENABLED(TFT_COLOR_UI)
  /**
   * Color_UI 的 TFT 字体。选择以下之一：
   *
   * NOTOSANS  - 默认字体，带抗锯齿。支持拉丁扩展和非拉丁字符。
   * UNIFONT   - 轻量字体，无抗锯齿。支持拉丁扩展和非拉丁字符。
   * HELVETICA - 轻量字体，无抗锯齿。仅支持基本拉丁字符 (0x0020-0x007F) 和拉丁-1 补充字符 (0x0080-0x00FF)。
   */
  #define TFT_FONT  NOTOSANS

  //#define TFT_SHARED_IO   // I/O 在 TFT 显示屏与其他设备之间共享。禁用异步数据传输。
#endif

#if ENABLED(TFT_LVGL_UI)
  //#define MKS_WIFI_MODULE // MKS WiFi 模块
#endif

/**
 * TFT 旋转。设置为以下值之一：
 *
 *   TFT_ROTATE_90,  TFT_ROTATE_90_MIRROR_X,  TFT_ROTATE_90_MIRROR_Y,
 *   TFT_ROTATE_180, TFT_ROTATE_180_MIRROR_X, TFT_ROTATE_180_MIRROR_Y,
 *   TFT_ROTATE_270, TFT_ROTATE_270_MIRROR_X, TFT_ROTATE_270_MIRROR_Y,
 *   TFT_MIRROR_X, TFT_MIRROR_Y, TFT_NO_ROTATION
 */
//#define TFT_ROTATION TFT_NO_ROTATION

//=============================================================================
//============================  其他控制器  ============================
//=============================================================================

//
// Ender-3 v2 原装显示屏。带旋转编码器的 DWIN 显示屏。
//
//#define DWIN_CREALITY_LCD           // Creality UI
//#define DWIN_LCD_PROUI              // MRiscoC 的 Pro UI
//#define DWIN_CREALITY_LCD_JYERSUI   // Jacob Myers 的 Jyers UI
//#define DWIN_MARLINUI_PORTRAIT      // MarlinUI（竖屏方向）
//#define DWIN_MARLINUI_LANDSCAPE     // MarlinUI（横屏方向）

//
// 触摸屏设置
//
//#define TOUCH_SCREEN
#if ENABLED(TOUCH_SCREEN)
  #define BUTTON_DELAY_EDIT      50 // (ms) 编辑界面的按钮重复延迟
  #define BUTTON_DELAY_MENU     250 // (ms) 菜单界面的按钮重复延迟

  //#define DISABLE_ENCODER         // 禁用点击编码器（如有）
  //#define TOUCH_IDLE_SLEEP_MINS 5 // (minutes) 一段时间无操作后显示屏休眠。用 M255 S 设置。

  #define TOUCH_SCREEN_CALIBRATION

  //#define TOUCH_CALIBRATION_X 12316
  //#define TOUCH_CALIBRATION_Y -8981
  //#define TOUCH_OFFSET_X        -43
  //#define TOUCH_OFFSET_Y        257
  //#define TOUCH_ORIENTATION TOUCH_LANDSCAPE

  #if BOTH(TOUCH_SCREEN_CALIBRATION, EEPROM_SETTINGS)
    #define TOUCH_CALIBRATION_AUTO_SAVE // 自动将成功的校准值保存到 EEPROM
  #endif

  #if ENABLED(TFT_COLOR_UI)
    //#define SINGLE_TOUCH_NAVIGATION
  #endif
#endif

//
// RepRapWorld REPRAPWORLD_KEYPAD v1.1
// https://reprapworld.com/products/electronics/ramps/keypad_v1_0_fully_assembled/
//
//#define REPRAPWORLD_KEYPAD
//#define REPRAPWORLD_KEYPAD_MOVE_STEP 10.0 // (mm) 每次按键移动的距离

//
// EasyThreeD ET-4000+，带按钮输入和状态 LED
//
//#define EASYTHREED_UI

//=============================================================================
//=============================== 附加功能 ==============================
//=============================================================================

// @section fans

// 设置用户可控风扇的数量。禁用则使用主板定义的所有风扇。
// :[1,2,3,4,5,6,7,8]
//#define NUM_M106_FANS 1

// 使用软件 PWM 驱动风扇，如同加热器一样。这使用极低的频率，
// 不像硬件 PWM 那样令人烦躁。另一方面，如果该频率
// 过低，你还应增大 SOFT_PWM_SCALE。
#define FAN_SOFT_PWM

// 每增加 1，软件 PWM 频率翻倍，
// 影响加热器，以及启用 FAN_SOFT_PWM 时的风扇。
// 但是，每增加一次，控制分辨率减半；
// 值为 0 时，有 128 个有效控制档位。
// :[0,1,2,3,4,5,6,7]
#define SOFT_PWM_SCALE 0

// 如果 SOFT_PWM_SCALE 设置为大于 0 的值，可以使用抖动
// 来缓解由此导致的分辨率损失。启用后，
// 部分 PWM 周期会被拉伸，使平均占空比
// 达到期望值。
//#define SOFT_PWM_DITHER

// @section extras

// 支持 BariCUDA 糊状挤出机
//#define BARICUDA

// @section lights

// 显示热端和热床温度的温度状态 LED。
// 如果所有热端、热床温度及目标温度均低于 54C，
// 则蓝色 LED 亮起。否则红色 LED 亮起。（1C 滞回）
//#define TEMP_STAT_LEDS

// 支持 BlinkM/CyzRgb
//#define BLINKM

// 支持 PCA9632 PWM LED 驱动器
//#define PCA9632

// 支持 PCA9533 PWM LED 驱动器
//#define PCA9533

/**
 * RGB LED / LED 灯带控制
 *
 * 启用对连接到 5V 数字引脚的 RGB LED 的支持，或
 * 连接到数字引脚控制的 MOSFET 的 RGB 灯带的支持。
 *
 * 添加 M150 命令用于设置 LED（或 LED 灯带）颜色。
 * 如果引脚支持 PWM（如 4、5、6、11），则可以设置
 * 0 到 255 范围内的亮度值。
 * 对于 NeoPixel LED，还提供整体亮度参数。
 *
 *  === 警告 ===
 *  LED 灯带在 PWM 线路和 LED 之间需要一颗 MOSFET 芯片，
 *  因为 Arduino 无法承受 LED 所需的电流。
 *  不遵循此预防措施可能会烧毁你的 Arduino！
 *
 *  注意：需要独立的 5V 电源！NeoPixel LED 所需的电流
 *  超出了 Arduino 5V 线性稳压器的输出能力。
 *
 *  要求 PWM 频率在 50 <> 100Hz 之间（请检查 HAL 或变体）
 *  如有可能，使用 FAST_PWM_FAN 来降低风扇噪声。
 */

// LED 类型。以下两个选项只能启用一个：
//#define RGB_LED
//#define RGBW_LED

#if EITHER(RGB_LED, RGBW_LED)
  //#define RGB_LED_R_PIN 34
  //#define RGB_LED_G_PIN 43
  //#define RGB_LED_B_PIN 35
  //#define RGB_LED_W_PIN -1
#endif

#if ANY(RGB_LED, RGBW_LED, PCA9632)
  //#define RGB_STARTUP_TEST              // 对于 PWM 引脚，在所有颜色之间渐变
  #if ENABLED(RGB_STARTUP_TEST)
    #define RGB_STARTUP_TEST_INNER_MS 10  // (ms) 减小或增大渐变速度
  #endif
#endif

// 支持 Adafruit NeoPixel LED 驱动器
#define NEOPIXEL_LED
#if ENABLED(NEOPIXEL_LED)
  #define NEOPIXEL_TYPE           NEO_GRB // NEO_GRBW, NEO_RGBW, NEO_GRB, NEO_RBG 等。
                                          // 见 https://github.com/adafruit/Adafruit_NeoPixel/blob/master/Adafruit_NeoPixel.h
  //#define NEOPIXEL_PIN                4 // LED 驱动引脚
  #define NEOPIXEL2_TYPE    NEOPIXEL_TYPE
  //#define NEOPIXEL2_PIN               5
  #define NEOPIXEL_PIXELS               8 // 灯带中的 LED 数量。（禁用 NEOPIXEL2_SEPARATE 时为最长的灯带。）
  #define NEOPIXEL_IS_SEQUENTIAL          // 温度变化时逐个点亮 LED 的顺序显示。禁用则所有 LED 同时变化。
  #define NEOPIXEL_BRIGHTNESS         255 // 初始亮度 (0-255)
  #define NEOPIXEL_STARTUP_TEST           // 启动时循环显示各种颜色

  // 支持用 M150 S1 ... 控制的第二个 Adafruit NeoPixel LED 驱动器
  #define NEOPIXEL2_SEPARATE
  #if ENABLED(NEOPIXEL2_SEPARATE)
    #define NEOPIXEL2_PIXELS            8 // 第二条灯带中的 LED 数量
    #define NEOPIXEL2_BRIGHTNESS      255 // 初始亮度 (0-255)
    #define NEOPIXEL2_STARTUP_TEST        // 启动时循环显示各种颜色
    #define NEOPIXEL_M150_DEFAULT      -1 // M150 不带 'S' 时使用的默认灯带。用 -1 默认设置全部。
  #else
    //#define NEOPIXEL2_INSERIES          // 默认行为是 NeoPixel 2 串联
  #endif

  // 将部分 NeoPixel LED 用于静态（背景）照明
  //#define NEOPIXEL_BKGD_INDEX_FIRST   0 // 第一个背景 LED 的索引
  //#define NEOPIXEL_BKGD_INDEX_LAST    5 // 最后一个背景 LED 的索引
  //#define NEOPIXEL_BKGD_COLOR         { 255, 255, 255, 0 }  // R, G, B, W
  //#define NEOPIXEL_BKGD_TIMEOUT_COLOR {  25,  25,  25, 0 }  // R, G, B, W
  //#define NEOPIXEL_BKGD_ALWAYS_ON       // 其他 NeoPixel 关闭时保持背光常亮
#endif

/**
 * 打印机事件 LED
 *
 * 打印过程中，LED 将反映打印机状态：
 *
 *  - 随着热床接近目标温度，从蓝色渐变为紫色
 *  - 随着热端达到温度，从紫色渐变为红色
 *  - 变为白色以照亮工作台面
 *  - 打印完成后变为绿色
 *  - 打印完成且用户按下按钮后熄灭
 */
#if ANY(BLINKM, RGB_LED, RGBW_LED, PCA9632, PCA9533, NEOPIXEL_LED)
  //#define PRINTER_EVENT_LEDS
#endif

// @section servos

/**
 * 舵机数量
 *
 * 对于某些与舵机相关的选项，NUM_SERVOS 将被自动设置。
 * 如果有需要手动控制的额外舵机，请手动设置此值。
 * 设为 0 可关闭舵机支持。
 */
#define NUM_SERVOS 2 // 注意：M280-M282 命令的舵机索引从 0 开始

// (ms) 下一次移动开始前的延迟，以给舵机留出到达目标角度的时间。
// 300ms 是一个不错的值，但你可以尝试更短的延迟。
// 如果舵机无法到达请求的位置，请增大该值。
#define SERVO_DELAY { 300 , 300 }

// 仅在运动期间给舵机上电，否则保持断电以防止抖动
//#define DEACTIVATE_SERVOS_AFTER_MOVE

// 用 M281 编辑舵机角度，用 M500 保存到 EEPROM
//#define EDITABLE_SERVO_ANGLES

// 用 M282 禁用舵机，在空闲时降低功耗、噪声和热量
#define SERVO_DETACH_GCODE

// 支持 RS485 控制
#define RS485_ENABLED
#define RS485_BUS_BUFFER_SIZE 128
#define RS485_SERIAL_PORT 1