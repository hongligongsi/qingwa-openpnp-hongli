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
// #pragma once
// #error "Don't build with import-2.1.x configurations!"
// #error "Use the 'bugfix...' or 'release...' configurations matching your
// Marlin version."

/**
 * Configuration.h
 *
 * 基本设置如下：
 *
 * - 电子器件类型
 * - 温度传感器类型
 * - 打印机几何结构
 * - 限位开关配置
 * - LCD 控制器
 * - 额外功能
 *
 * 高级设置可在 Configuration_adv.h 中找到
 */
#define CONFIGURATION_H_VERSION 02010300

//===========================================================================
//============================= 入门指南 =============================
//===========================================================================

/**
 * 以下是一些有助于您配置和校准机器的实用链接：
 *
 * 示例配置:     https://github.com/MarlinFirmware/Configurations/branches/all
 *
 * Průša 计算器:    https://blog.prusaprinters.org/calculator_3416/
 *
 * 校准指南:  https://reprap.org/wiki/Calibration
 *                      https://reprap.org/wiki/Triffid_Hunter%27s_Calibration_Guide
 *                      https://sites.google.com/site/repraplogphase/calibration-of-your-reprap
 *                      https://youtu.be/wAL9d7FgInk
 *
 * 校准模型: https://www.thingiverse.com/thing:5573
 *                      https://www.thingiverse.com/thing:1278865
 */

// @section info

// 本次构建的作者信息，在启动时和 M115 中打印到主机
#define STRING_CONFIG_H_AUTHOR "(none, default config)" // 修改者。
// #define CUSTOM_VERSION_FILE Version.h // 相对于根目录的路径（不加引号）

// @section machine

// 从 boards.h 中选择与您的配置匹配的名称
#ifndef MOTHERBOARD
#define MOTHERBOARD BOARD_OPULO_LUMEN_REV5
#endif

/**
 * 选择主板上用于与主机通信的串口。
 * 这样可以将无线适配器（例如）连接到非默认端口引脚。
 * 串口 -1 为 USB 模拟串口（如果可用）。
 * 注意：第一个串口（-1 或 0）总是被 Arduino 引导程序使用。
 *
 * :[-1, 0, 1, 2, 3, 4, 5, 6, 7]
 */
#define SERIAL_PORT -1

/**
 * 串口波特率
 * 这是所有串口的默认通信速度。
 * 在下方为其他串口设置默认波特率。
 *
 * 250000 在大多数情况下可用，但如果主机打印时经常掉线，
 * 可以尝试较低速度。
 * 最高可尝试 1000000 以加快 SD 文件传输。
 *
 * :[2400, 9600, 19200, 38400, 57600, 115200, 250000, 500000, 1000000]
 */
#define BAUDRATE 250000

// #define BAUD_RATE_GCODE     // 启用 G-code M575 设置波特率

/**
 * 选择主板上用于与主机通信的辅助串口。
 * 目前以太网 (-2) 仅在 Teensy 4.1 主板上受支持。
 * :[-2, -1, 0, 1, 2, 3, 4, 5, 6, 7]
 */
// #define SERIAL_PORT_2 -1
// #define BAUDRATE_2 250000   // :[2400, 9600, 19200, 38400, 57600, 115200, 250000, 500000, 1000000] 启用可覆盖 BAUDRATE

/**
 * 选择主板上用于与主机通信的第三个串口。
 * 目前仅支持 AVR、DUE、LPC1768/9 和 STM32/STM32F1
 * :[-1, 0, 1, 2, 3, 4, 5, 6, 7]
 */
// #define SERIAL_PORT_3 1
// #define BAUDRATE_3 250000   // :[2400, 9600, 19200, 38400, 57600, 115200, 250000, 500000, 1000000] 启用可覆盖 BAUDRATE

// 在 AT90USB 设备上启用蓝牙串口
// #define BLUETOOTH

// 显示在 LCD "Ready" 消息和信息菜单中的名称
// #define CUSTOM_MACHINE_NAME "3D Printer"

// 打印机唯一 ID，供某些程序区分不同机器。
// 自行选择，或使用类似 https://www.uuidgenerator.net/version4 的服务
// #define MACHINE_UUID "00000000-0000-0000-0000-000000000000"

// @section stepper drivers

/**
 * 步进电机驱动
 *
 * 这些设置让 Marlin 可以调整步进电机驱动的时序，并为支持相应功能的
 * 驱动启用高级选项。你也可以在 Configuration_adv.h 中覆盖时序选项。
 *
 * TMC2225 驱动请用 TMC2208/TMC2208_STANDALONE，
 * TMC2226 驱动请用 TMC2209/TMC2209_STANDALONE。
 *
 * 可选值: A4988, A5984, DRV8825, LV8729, TB6560, TB6600, TMC2100,
 *          TMC2130, TMC2130_STANDALONE, TMC2160, TMC2160_STANDALONE,
 *          TMC2208, TMC2208_STANDALONE, TMC2209, TMC2209_STANDALONE,
 *          TMC26X,  TMC26X_STANDALONE,  TMC2660, TMC2660_STANDALONE,
 *          TMC5130, TMC5130_STANDALONE, TMC5160, TMC5160_STANDALONE
 * :['A4988', 'A5984', 'DRV8825', 'LV8729', 'TB6560', 'TB6600', 'TMC2100', 'TMC2130', 'TMC2130_STANDALONE', 'TMC2160', 'TMC2160_STANDALONE', 'TMC2208', 'TMC2208_STANDALONE', 'TMC2209', 'TMC2209_STANDALONE', 'TMC26X', 'TMC26X_STANDALONE', 'TMC2660', 'TMC2660_STANDALONE', 'TMC5130', 'TMC5130_STANDALONE', 'TMC5160', 'TMC5160_STANDALONE']
 */
#define X_DRIVER_TYPE TMC2209
#define Y_DRIVER_TYPE TMC2209
#define Z_DRIVER_TYPE TMC2209
// #define X2_DRIVER_TYPE A4988
#define Y2_DRIVER_TYPE TMC2209
// #define Z2_DRIVER_TYPE A4988
// #define Z3_DRIVER_TYPE A4988
// #define Z4_DRIVER_TYPE A4988
#define I_DRIVER_TYPE TMC2209
#define J_DRIVER_TYPE TMC2209
// #define K_DRIVER_TYPE  TMC2209
// #define U_DRIVER_TYPE  A4988
// #define V_DRIVER_TYPE  A4988
// #define W_DRIVER_TYPE  A4988
// #define E0_DRIVER_TYPE A4988
// #define E1_DRIVER_TYPE A4988
// #define E2_DRIVER_TYPE A4988
// #define E3_DRIVER_TYPE A4988
// #define E4_DRIVER_TYPE A4988
// #define E5_DRIVER_TYPE A4988
// #define E6_DRIVER_TYPE A4988
// #define E7_DRIVER_TYPE A4988

/**
 * 附加轴设置
 *
 * 为所有会旋转或摆动的轴定义 AXISn_ROTATES。
 * 旋转轴的坐标以度为单位表示。
 *
 * AXISn_NAME 定义在（大多数）G 代码命令中用于引用该轴的字母。
 * 按惯例各名称与角色通常为：'A'：平行于 X 的旋转轴
 * 'B'：平行于 Y 的旋转轴　'C'：平行于 Z 的旋转轴
 * 'U'：平行于 X 的第二线性轴　'V'：平行于 Y 的第二线性轴
 * 'W'：平行于 Z 的第二线性轴
 *
 * 无论这些设置如何，轴在内部统一命名为 I、J、K、U、V、W。
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
// #define AXIS7_ROTATES
#endif
#ifdef V_DRIVER_TYPE
#define AXIS8_NAME 'V' // :['V', 'W']
// #define AXIS8_ROTATES
#endif
#ifdef W_DRIVER_TYPE
#define AXIS9_NAME 'W' // :['W']
// #define AXIS9_ROTATES
#endif

// @section extruder

// 定义挤出机数量
// :[0, 1, 2, 3, 4, 5, 6, 7, 8]
#define EXTRUDERS 0

// 通常预期的耗材直径（1.75、2.85、3.0 ...）。用于体积挤出、
// 耗材宽度传感器等功能。
#define DEFAULT_NOMINAL_FILAMENT_DIA 1.75

// 用于 Cyclops 或任何共用单个喷嘴的「多挤出机」方案。
// #define SINGLENOZZLE

// 换刀时保存并恢复温度与风扇转速。
// 用 M104/106/109 T... 将未选中的工具设为待机状态。
#if ENABLED(SINGLENOZZLE)
// #define SINGLENOZZLE_STANDBY_TEMP
// #define SINGLENOZZLE_STANDBY_FAN
#endif

// @section multi-material

/**
 * 多料单元
 * 设置为下列预定义型号之一：
 *
 *   PRUSA_MMU1           : Průša MMU1（"多路复用"版本）
 *   PRUSA_MMU2           : Průša MMU2
 *   PRUSA_MMU2S          : Průša MMU2S（需配 MK3S 挤出机并带运动传感器，
 * EXTRUDERS = 5）　EXTENDABLE_EMU_MMU2  : 耗材数量可配置的 MMU
 * （ERCF、SMuFF 或类似且兼容 Průša MMU2 固件的方案）
 *   EXTENDABLE_EMU_MMU2S : 耗材数量可配置的 MMUS（ERCF、SMuFF
 * 或类似且兼容 Průša MMU2 固件的方案）
 *
 * 需要 NOZZLE_PARK_FEATURE，以便 MMU 单元故障时能停放打印头。
 * 更多选项见 Configuration_adv.h。
 * :["PRUSA_MMU1", "PRUSA_MMU2", "PRUSA_MMU2S", "EXTENDABLE_EMU_MMU2", "EXTENDABLE_EMU_MMU2S"]
 */
// #define MMU_MODEL PRUSA_MMU2

// 使用单个步进电机的双挤出机
// #define SWITCHING_EXTRUDER
#if ENABLED(SWITCHING_EXTRUDER)
#define SWITCHING_EXTRUDER_SERVO_NR 0
#define SWITCHING_EXTRUDER_SERVO_ANGLES {0, 90} // E0、E1[, E2、E3] 的角度
#if EXTRUDERS > 3
#define SWITCHING_EXTRUDER_E23_SERVO_NR 1
#endif
#endif

// 通过碰撞工具头来切换挤出机。需要 EVENT_GCODE_TOOLCHANGE_#。
// #define MECHANICAL_SWITCHING_EXTRUDER

/**
 * 双喷嘴方案，用舵机抬起/降下其中一个（或两个）喷嘴。
 * 可与 SWITCHING_EXTRUDER 组合使用。
 */
// #define SWITCHING_NOZZLE
#if ENABLED(SWITCHING_NOZZLE)
#define SWITCHING_NOZZLE_SERVO_NR 0
// #define SWITCHING_NOZZLE_E1_SERVO_NR 1          // 使用两个舵机时，
// 第二个舵机的编号
#define SWITCHING_NOZZLE_SERVO_ANGLES                                          \
  {0, 90} // E0、E1 的角度（单舵机）或抬起/降下角度（双舵机）
#define SWITCHING_NOZZLE_SERVO_DWELL                                           \
  2500 // 等待舵机完成实际动作的停留时间
#endif

// 通过碰撞工具头来切换喷嘴。需要 EVENT_GCODE_TOOLCHANGE_#。
// #define MECHANICAL_SWITCHING_NOZZLE

/**
 * 两个独立的 X 滑架，各自带挤出机，通过电磁铁对接机构连接到运动部件。
 * 需要 SOL1_PIN 和 SOL2_PIN。
 */
// #define PARKING_EXTRUDER

/**
 * 两个独立的 X 滑架，各自带挤出机，通过磁吸对接机构（靠运动位移实现，
 * 不使用电磁铁）连接到运动部件
 *
 * 项目   : https://www.thingiverse.com/thing:3080893
 * 运动演示 : https://youtu.be/0xCEiG9VS3k
 *             https://youtu.be/Bqbcs0CU2FE
 */
// #define MAGNETIC_PARKING_EXTRUDER

#if EITHER(PARKING_EXTRUDER, MAGNETIC_PARKING_EXTRUDER)

#define PARKING_EXTRUDER_PARKING_X                                             \
  {-78, 184} // 挤出机停靠的 X 位置
#define PARKING_EXTRUDER_GRAB_DISTANCE                                         \
  1 // (mm) 越过停靠点移动以抓取挤出机所需的距离

#if ENABLED(PARKING_EXTRUDER)

#define PARKING_EXTRUDER_SOLENOIDS_INVERT // 启用后，施加电压时
                                          // 电磁铁不会被磁化
#define PARKING_EXTRUDER_SOLENOIDS_PINS_ACTIVE                                 \
  LOW // 引脚为 LOW 或 HIGH 信号时使线圈通电
#define PARKING_EXTRUDER_SOLENOIDS_DELAY                                       \
  250 // (ms) 磁场建立延迟。为 0 或未定义时不延迟。
// #define MANUAL_SOLENOID_CONTROL                   // 手动控制
// 对接电磁铁，使用 M380 S / M381

#elif ENABLED(MAGNETIC_PARKING_EXTRUDER)

#define MPE_FAST_SPEED                                                         \
  9000 // (mm/min) 最后距离点之前的移动速度
#define MPE_SLOW_SPEED                                                         \
  4500 // (mm/min) 停靠对接时最后一段距离的移动速度
#define MPE_TRAVEL_DISTANCE 10 // (mm) 最后距离点
#define MPE_COMPENSATION                                                       \
  0 // 偏移补偿 -1、0、1（倍数），仅用于对接

#endif

#endif

/**
 * 可切换工具头
 *
 * 支持可更换、可停靠的工具头，例如
 * E3D Tool Changer。工具头由舵机锁定。
 */
// #define SWITCHING_TOOLHEAD

/**
 * 磁性可切换工具头
 *
 * 支持可更换、可停靠的工具头，使用磁性
 * 对接机构，通过运动实现，无需舵机。
 */
// #define MAGNETIC_SWITCHING_TOOLHEAD

/**
 * 电磁可切换工具头
 *
 * 用于 CoreXY / HBot 运动学的停靠。
 * 工具头停靠在一侧，并由电磁铁固定。
 * 支持 2 个以上的工具头。参见 https://youtu.be/JolbsAKTKf4
 */
// #define ELECTROMAGNETIC_SWITCHING_TOOLHEAD

#if ANY(SWITCHING_TOOLHEAD, MAGNETIC_SWITCHING_TOOLHEAD,                       \
        ELECTROMAGNETIC_SWITCHING_TOOLHEAD)
#define SWITCHING_TOOLHEAD_Y_POS 235     // (mm) 工具头停靠位的 Y 坐标
#define SWITCHING_TOOLHEAD_Y_SECURITY 10 // (mm) Y 轴安全距离
#define SWITCHING_TOOLHEAD_Y_CLEAR                                             \
  60 // (mm) 距停靠位保证 X 轴无阻挡的最小距离
#define SWITCHING_TOOLHEAD_X_POS                                               \
  {215, 0} // (mm) 挤出机停靠的 X 位置
#if ENABLED(SWITCHING_TOOLHEAD)
#define SWITCHING_TOOLHEAD_SERVO_NR 2 // 舵机接口编号
#define SWITCHING_TOOLHEAD_SERVO_ANGLES                                        \
  {0, 180} // (degrees) 锁定与解锁的角度
#elif ENABLED(MAGNETIC_SWITCHING_TOOLHEAD)
#define SWITCHING_TOOLHEAD_Y_RELEASE 5 // (mm) Y 轴安全距离
#define SWITCHING_TOOLHEAD_X_SECURITY                                          \
  {90, 150} // (mm) X 轴安全距离 (T0,T1)
// #define PRIME_BEFORE_REMOVE                       // 脱离停靠位前先
// 给喷嘴润湿
#if ENABLED(PRIME_BEFORE_REMOVE)
#define SWITCHING_TOOLHEAD_PRIME_MM 20   // (mm)   挤出机润湿长度
#define SWITCHING_TOOLHEAD_RETRACT_MM 10 // (mm)   润湿后的回抽长度
#define SWITCHING_TOOLHEAD_PRIME_FEEDRATE                                      \
  300 // (mm/min) 挤出机润湿进给速度
#define SWITCHING_TOOLHEAD_RETRACT_FEEDRATE                                    \
  2400 // (mm/min) 挤出机回抽进给速度
#endif
#elif ENABLED(ELECTROMAGNETIC_SWITCHING_TOOLHEAD)
#define SWITCHING_TOOLHEAD_Z_HOP 2 // (mm) 切换时的 Z 轴抬升量
#endif
#endif

/**
 * "混合挤出机"
 *   - 增加 G 代码 M163 和 M164，用于设置并“提交”当前的混合比例。
 *   - 扩展步进例程，使多个步进电机按混合比例成比例
 * 移动。
 *   - 可选支持 Repetier 固件的 'M164 S<index>'，以支持
 * 虚拟工具。
 *   - 本实现最多支持两个混合挤出机。
 *   - 启用 DIRECT_MIXING_IN_G1 以支持 M165 以及在 G1 中混合（来自 Pia Taubert 的
 * 参考实现）。
 */
// #define MIXING_EXTRUDER
#if ENABLED(MIXING_EXTRUDER)
#define MIXING_STEPPERS 2 // 混合挤出机中的步进电机数量
#define MIXING_VIRTUAL_TOOLS                                                   \
  16 // 使用 M163 和 M164 的虚拟工具方法
// #define DIRECT_MIXING_IN_G1    // 允许在 G1 移动命令中使用 ABCDHI
//  混合系数
// #define GRADIENT_MIX           // 支持使用
//  M166 和 LCD 进行渐变混合
// #define MIXING_PRESETS         // 分配 8 个默认
// V-tool 预设，供 2 或 3 个 MIXING_STEPPERS 使用
#if ENABLED(GRADIENT_MIX)
// #define GRADIENT_VTOOL       // 增加 M166 T，把 V-tool 索引当作
// 渐变别名
#endif
#endif

// 挤出机的偏移量（若使用多个挤出机并依赖固件
// 在切换时完成定位，则取消注释）。对挤出机 0 的热端
// （默认挤出机），偏移量必须为 X=0、Y=0。对其他热端，
// 则是它们到挤出机 0 热端的距离。
// #define HOTEND_OFFSET_X { 0.0, 20.00 } // (mm) 每个喷嘴的相对 X 偏移量
//  喷嘴
// #define HOTEND_OFFSET_Y { 0.0, 5.00 }  // (mm) 每个喷嘴的相对 Y 偏移量
//  喷嘴
// #define HOTEND_OFFSET_Z { 0.0, 0.00 }  // (mm) 每个喷嘴的相对 Z 偏移量
// 喷嘴

// @section psu control

/**
 * 电源控制
 *
 * 启用电源并将其连接到 PS_ON_PIN。
 * 指定电源是高电平有效（active HIGH）还是低电平有效（active LOW）。
 */
// #define PSU_CONTROL
// #define PSU_NAME "Power Supply"

#if ENABLED(PSU_CONTROL)
// #define MKS_PWC                 // 使用 MKS PWC 附加板
// #define PS_OFF_CONFIRM          // 关机时弹出确认对话框
// #define PS_OFF_SOUND            // 关机时蜂鸣 1s
#define PSU_ACTIVE_STATE LOW // ATX 用 'LOW'，X-Box 用 'HIGH'

// #define PSU_DEFAULT_OFF               // 保持关机状态，直到用 M80
//  直接开启
// #define PSU_POWERUP_DELAY      250    // (ms) 电源升至
//  满功率的延迟
// #define LED_POWEROFF_TIMEOUT 10000    // (ms)
// 断电后延迟该时长再关闭 LED

// #define POWER_OFF_TIMER               // 启用 M81 D<seconds> 以延时
//  关机
// #define POWER_OFF_WAIT_FOR_COOLDOWN   // 启用 M81 S，仅在冷却
// 结束后才关机

// #define PSU_POWERUP_GCODE  "M355 S1"  // 上电后运行的 G 代码（例如：
//  打开机箱灯）
// #define PSU_POWEROFF_GCODE "M355 S0"  // 断电前运行的 G 代码（例如：
// 关闭机箱灯）

// #define AUTO_POWER_CONTROL      // 启用对 PS_ON 引脚的自动控制
#if ENABLED(AUTO_POWER_CONTROL)
#define AUTO_POWER_FANS // 需要为风扇供电时开启电源
#define AUTO_POWER_E_FANS
#define AUTO_POWER_CONTROLLERFAN
#define AUTO_POWER_CHAMBER_FAN
#define AUTO_POWER_COOLER_FAN
#define POWER_TIMEOUT                                                          \
  30 // (s) 机器空闲达到该时长后断电
// #define POWER_OFF_DELAY          60 // (s) 执行 M81 命令后的断电延迟，
// 可让风扇多运行一段时间。
#endif
#if EITHER(AUTO_POWER_CONTROL, POWER_OFF_WAIT_FOR_COOLDOWN)
// #define AUTO_POWER_E_TEMP        50 // (°C) 任一挤出机温度超过
//  此值时开启电源
// #define AUTO_POWER_CHAMBER_TEMP  30 // (°C) 腔体温度超过
//  此值时开启电源
// #define AUTO_POWER_COOLER_TEMP   26 // (°C)
// 冷却器温度超过此值时开启电源
#endif
#endif

//===========================================================================
//================================= 温度设置 ================================
//===========================================================================
// @section temperature

/**
 * --NORMAL IS 4.7kΩ PULLUP!-- 热端传感器可使用 1kΩ 上拉，需配用
 * 正确的电阻值和查表
 *
 * Temperature sensors available:
 *
 *  SPI RTD/热电偶板 - 重要：请阅读下方的说明！
 *  -------
 *    -5 : MAX31865 with Pt100/Pt1000, 2, 3, or 4-wire  (only for sensors 0-1)
 *  注意：必须取消注释或设置下方的 MAX31865_*_OHMS_n 宏定义。
 *    -3 : MAX31855 with Thermocouple, -200°C to +700°C (only for sensors 0-1)
 *    -2 : MAX6675  with Thermocouple, 0°C to +700°C    (only for sensors 0-1)
 *
 *  注意：请在引脚文件中为每个使用 SPI 热电偶的 TEMP_SENSOR_n 设置 TEMP_n_CS_PIN。默认情况下，
 *        使用默认串行总线上的硬件 SPI。若你还设置了 TEMP_n_SCK_PIN 和 TEMP_n_MISO_PIN，
 *        则将改用这些端口上的软件 SPI。你可以在 Configuration_adv.h 文件中
 *        强制在默认总线上使用硬件 SPI。目前尚不支持为传感器使用独立的硬件 SPI 总线。
 *
 *  模拟热电偶板
 *  -------
 *    -4 : AD8495 with Thermocouple
 *    -1 : AD595  with Thermocouple
 *
 *  模拟热敏电阻 - 4.7kΩ 上拉 - 常规
 *  -------
 *     1 : 100kΩ  EPCOS - Best choice for EPCOS thermistors
 *   331 : 100kΩ  Same as #1, but 3.3V scaled for MEGA
 *   332 : 100kΩ  Same as #1, but 3.3V scaled for DUE
 *     2 : 200kΩ  ATC Semitec 204GT-2
 *   202 : 200kΩ  Copymaster 3D
 *     3 : ???Ω   Mendel-parts thermistor
 *     4 : 10kΩ   Generic Thermistor !! DO NOT use for a hotend - it gives bad resolution at high temp. !!
 *     5 : 100kΩ  ATC Semitec 104GT-2/104NT-4-R025H42G - Used in ParCan, J-Head, and E3D, SliceEngineering 300°C
 *   501 : 100kΩ  Zonestar - Tronxy X3A
 *   502 : 100kΩ  Zonestar - used by hot bed in Zonestar Průša P802M
 *   503 : 100kΩ  Zonestar (Z8XM2) Heated Bed thermistor
 *   504 : 100kΩ  Zonestar P802QR2 (Part# QWG-104F-B3950) Hotend Thermistor
 *   505 : 100kΩ  Zonestar P802QR2 (Part# QWG-104F-3950) Bed Thermistor
 *   512 : 100kΩ  RPW-Ultra hotend
 *     6 : 100kΩ  EPCOS - Not as accurate as table #1 (created using a fluke thermocouple)
 *     7 : 100kΩ  Honeywell 135-104LAG-J01
 *    71 : 100kΩ  Honeywell 135-104LAF-J01
 *     8 : 100kΩ  Vishay 0603 SMD NTCS0603E3104FXT
 *     9 : 100kΩ  GE Sensing AL03006-58.2K-97-G1
 *    10 : 100kΩ  RS PRO 198-961
 *    11 : 100kΩ  Keenovo AC silicone mats, most Wanhao i3 machines - beta 3950, 1%
 *    12 : 100kΩ  Vishay 0603 SMD NTCS0603E3104FXT (#8) - calibrated for Makibox hot bed
 *    13 : 100kΩ  Hisens up to 300°C - for "Simple ONE" & "All In ONE" hotend - beta 3950, 1%
 *    15 : 100kΩ  Calibrated for JGAurora A5 hotend
 *    18 : 200kΩ  ATC Semitec 204GT-2 Dagoma.Fr - MKS_Base_DKU001327
 *    22 : 100kΩ  GTM32 Pro vB - hotend - 4.7kΩ pullup to 3.3V and 220Ω to analog input
 *    23 : 100kΩ  GTM32 Pro vB - bed - 4.7kΩ pullup to 3.3v and 220Ω to analog input
 *    30 : 100kΩ  Kis3d Silicone heating mat 200W/300W with 6mm precision cast plate (EN AW 5083) NTC100K - beta 3950
 *    60 : 100kΩ  Maker's Tool Works Kapton Bed Thermistor - beta 3950
 *    61 : 100kΩ  Formbot/Vivedino 350°C Thermistor - beta 3950
 *    66 : 4.7MΩ  Dyze Design / Trianglelab T-D500 500°C High Temperature Thermistor
 *    67 : 500kΩ  SliceEngineering 450°C Thermistor
 *    68 : PT100 amplifier board from Dyze Design
 *    70 : 100kΩ  bq Hephestos 2
 *    75 : 100kΩ  Generic Silicon Heat Pad with NTC100K MGB18-104F39050L32
 *  2000 : 100kΩ  Ultimachine Rambo TDK NTCG104LH104KT1 NTC100K motherboard Thermistor
 *
 *  模拟热敏电阻 - 1kΩ 上拉 - 非标准，需要将 4.7kΩ 上拉更换为 1kΩ。
 *  -------                           （可获得更高的精度和更稳定的 PID）
 *    51 : 100kΩ  EPCOS (1kΩ pullup)
 *    52 : 200kΩ  ATC Semitec 204GT-2 (1kΩ pullup)
 *    55 : 100kΩ  ATC Semitec 104GT-2 - Used in ParCan & J-Head (1kΩ pullup)
 *
 *  模拟热敏电阻 - 10kΩ 上拉 - 非标准
 *  -------
 *    99 : 100kΩ  Found on some Wanhao i3 machines with a 10kΩ pull-up resistor
 *
 *  模拟 RTD (Pt100/Pt1000)
 *  -------
 *   110 : Pt100  with 1kΩ pullup (atypical)
 *   147 : Pt100  with 4.7kΩ pullup
 *  1010 : Pt1000 with 1kΩ pullup (atypical)
 *  1022 : Pt1000 with 2.2kΩ pullup
 *  1047 : Pt1000 with 4.7kΩ pullup (E3D)
 *    20 : Pt100  with circuit in the Ultimainboard V2.x with mainboard ADC reference voltage = INA826 amplifier-board supply voltage.
 *  注意：(1) 必须使用无上拉的 ADC 输入。(2) 部分 INA826 放大器在 3.3V 下不可靠，建议改用传感器 147、110 或 21。
 *    21 : Pt100  with circuit in the Ultimainboard V2.x with 3.3v ADC reference voltage (STM32, LPC176x....) and 5V INA826 amplifier board supply.
 *  注意：ADC 引脚不耐 5V。不推荐使用，因为温度超过 500°C 可能损坏 CPU。
 *   201 : Pt100  with circuit in Overlord, similar to Ultimainboard V2.x
 *
 *  自定义/虚拟/其他温度传感器
 *  ------
 *     0 : not used
 *  1000 : Custom - Specify parameters in Configuration_adv.h
 *
 *   !!! 这些仅供测试或开发使用。生产机器请勿使用 !!!
 *   998 : Dummy Table that ALWAYS reads 25°C or the temperature defined below.
 *   999 : Dummy Table that ALWAYS reads 100°C or the temperature defined below.
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

// 虚拟热敏电阻的恒定温度读数，供 998 和 999 使用
#define DUMMY_THERMISTOR_998_VALUE 25
#define DUMMY_THERMISTOR_999_VALUE 100

// 在 TEMP_SENSOR_0 / 1 上使用 MAX31865 传感器 (-5) 时的电阻值
#if TEMP_SENSOR_IS_MAX_TC(0)
#define MAX31865_SENSOR_OHMS_0                                                 \
  100 // (Ω) 通常为 100 或 1000（PT100 或 Pt1000）
#define MAX31865_CALIBRATION_OHMS_0                                            \
  430 // (Ω) Adafruit PT100 通常为 430；Adafruit Pt1000 为 4300
#endif
#if TEMP_SENSOR_IS_MAX_TC(1)
#define MAX31865_SENSOR_OHMS_1 100
#define MAX31865_CALIBRATION_OHMS_1 430
#endif
#if TEMP_SENSOR_IS_MAX_TC(2)
#define MAX31865_SENSOR_OHMS_2 100
#define MAX31865_CALIBRATION_OHMS_2 430
#endif

#if HAS_E_TEMP_SENSOR
#define TEMP_RESIDENCY_TIME                                                    \
  10 // (seconds) M109 中等待热端“稳定”的时间
#define TEMP_WINDOW                                                            \
  1 // (°C) “达到温度”计时器的温度接近范围
#define TEMP_HYSTERESIS                                                        \
  3 // (°C) 视为与目标“足够接近”的温度偏差
#endif

#if TEMP_SENSOR_BED
#define TEMP_BED_RESIDENCY_TIME                                                \
  10 // (seconds) M190 中等待热床“稳定”的时间
#define TEMP_BED_WINDOW                                                        \
  1 // (°C) “达到温度”计时器的温度接近范围
#define TEMP_BED_HYSTERESIS                                                    \
  3 // (°C) 视为与目标“足够接近”的温度偏差
#endif

#if TEMP_SENSOR_CHAMBER
#define TEMP_CHAMBER_RESIDENCY_TIME                                            \
  10 // (seconds) M191 中等待腔体“稳定”的时间
#define TEMP_CHAMBER_WINDOW                                                    \
  1 // (°C) “达到温度”计时器的温度接近范围
#define TEMP_CHAMBER_HYSTERESIS                                                \
  3 // (°C) 视为与目标“足够接近”的温度偏差
#endif

/**
 * 冗余温度传感器 (TEMP_SENSOR_REDUNDANT)
 *
 * 将一个温度传感器用作另一个读数的冗余传感器。选择一个未使用的
 * 温度传感器，以及你希望它为其提供冗余的另一个传感器。如果
 * 两个热敏电阻相差 TEMP_SENSOR_REDUNDANT_MAX_DIFF (°C)，则打印
 * 将被中止。被选中的传感器其正常功能
 * 将被禁用；例如选择热床传感器 (-1) 会禁用热床
 * 加热/监控。
 *
 * 选择源/目标可用: COOLER, PROBE, BOARD, CHAMBER, BED, E0, E1,
 * E2, E3, E4, E5, E6, E7
 */
#if TEMP_SENSOR_REDUNDANT
#define TEMP_SENSOR_REDUNDANT_SOURCE                                           \
  E1 // 提供冗余读数的传感器。
#define TEMP_SENSOR_REDUNDANT_TARGET                                           \
  E0 // 我们为其提供冗余读数的传感器。
#define TEMP_SENSOR_REDUNDANT_MAX_DIFF                                         \
  10 // (°C) 触发打印中止的温度差
#endif

// 低于此温度时加热器将关闭，
// 因为这很可能表示热敏电阻导线已损坏。
#define HEATER_0_MINTEMP 5
#define HEATER_1_MINTEMP 5
#define HEATER_2_MINTEMP 5
#define HEATER_3_MINTEMP 5
#define HEATER_4_MINTEMP 5
#define HEATER_5_MINTEMP 5
#define HEATER_6_MINTEMP 5
#define HEATER_7_MINTEMP 5
#define BED_MINTEMP 5
#define CHAMBER_MINTEMP 5

// 高于此温度时加热器将关闭。
// 这可以防止元件过热，但无法防止短路和
// 故障。（请使用 MINTEMP 防止热敏电阻短路/故障。）
#define HEATER_0_MAXTEMP 275
#define HEATER_1_MAXTEMP 275
#define HEATER_2_MAXTEMP 275
#define HEATER_3_MAXTEMP 275
#define HEATER_4_MAXTEMP 275
#define HEATER_5_MAXTEMP 275
#define HEATER_6_MAXTEMP 275
#define HEATER_7_MAXTEMP 275
#define BED_MAXTEMP 150
#define CHAMBER_MAXTEMP 60

/**
 * 温度过冲
 * 在升温过程中（以及打印时），温度常常会“超出”目标
 * 好几度（尤其在 PID 调参之前）。将目标温度
 * 设得离 MAXTEMP 太近必然会导致 MAXTEMP 停机！用这些
 * 数值来禁止温度被设得离 MAXTEMP 太近。
 */
#define HOTEND_OVERSHOOT 15 // (°C) 禁止温度超过 MAXTEMP - OVERSHOOT
#define BED_OVERSHOOT 10    // (°C) 禁止温度超过 MAXTEMP - OVERSHOOT
#define COOLER_OVERSHOOT 2  // (°C) 禁止温度与 MAXTEMP 相差小于 OVERSHOOT

//===========================================================================
//=============================== PID 设置 ==================================
//===========================================================================

// @section hotend temp

// 启用 PIDTEMP 以进行 PID 控制，或启用 MPCTEMP 进行基于预测模型的
// 温度控制。bang-bang 加热时两者都要禁用。
#define PIDTEMP // 参见 PID 调参指南：
                // https://reprap.org/wiki/PID_Tuning
// #define MPCTEMP        // ** 实验性 **

#define BANG_MAX                                                               \
  255 // bang-bang 模式下限制流向喷嘴的电流；255=满电流
#define PID_MAX                                                                \
  BANG_MAX          // PID 生效时限制流向喷嘴的电流（参见
                    // 下方的 PID_FUNCTIONAL_RANGE）；255=满电流
#define PID_K1 0.95 // 任一 PID 回路内的平滑系数

#if ENABLED(PIDTEMP)
// #define PID_DEBUG             // 将 PID 调试数据输出到串口。使用
//  'M303 D' 切换启用状态。
// #define PID_PARAMS_PER_HOTEND // 使用独立的
// PID 参数（当挤出机不一致时很有用）
//  用 G 代码设置/获取：M301 E[挤出机编号, 0-2]

#if ENABLED(PID_PARAMS_PER_HOTEND)
// 按你的设置，在此为每个热端指定最多一个值。
// 如果给定的值较少，最后一个值将适用于其余热端。
#define DEFAULT_Kp_LIST {22.20, 22.20}
#define DEFAULT_Ki_LIST {1.08, 1.08}
#define DEFAULT_Kd_LIST {114.00, 114.00}
#else
#define DEFAULT_Kp 22.20
#define DEFAULT_Ki 1.08
#define DEFAULT_Kd 114.00
#endif
#endif

/**
 * 热端的模型预测控制
 *
 * 使用热端的物理模型来控制温度。正确配置时，
 * 它比 PID 具有更好的响应性和稳定性，并且还
 * 免去了对 PID_EXTRUSION_SCALING 和 PID_FAN_SCALING 的需求。用 M306 T
 * 自动整定模型。
 * @section mpctemp
 */
#if ENABLED(MPCTEMP)
// #define MPC_AUTOTUNE                              // 加入 MPC 自动整定的实现方法
//  （约 5664-5882 字节闪存）
// #define MPC_EDIT_MENU // 把 MPC 编辑加入 "Advanced Settings" 菜单
// （约 1300 字节闪存）
// #define MPC_AUTOTUNE_MENU                         // 把 MPC 自动整定加入 "Advanced Settings"
// 菜单。（约 350 字节闪存）

#define MPC_MAX BANG_MAX // (0..255) MPC 启用时流向喷嘴的电流。
#define MPC_HEATER_POWER {40.0f} // (W) 加热棒功率。

#define MPC_INCLUDE_FAN // 是否将风扇转速纳入模型？

// 从 M306 测得的物理常量
#define MPC_BLOCK_HEAT_CAPACITY {16.7f} // (J/K) 加热块热容。
#define MPC_SENSOR_RESPONSIVENESS                                              \
  {0.22f} // (K/s per ∆K) 传感器温度相对加热块的变化速率。
#define MPC_AMBIENT_XFER_COEFF                                                 \
  {0.068f} // (W/K) 加热块到室内空气的传热系数，
           // 风扇关闭时。
#if ENABLED(MPC_INCLUDE_FAN)
#define MPC_AMBIENT_XFER_COEFF_FAN255                                          \
  {0.097f} // (W/K) 加热块到室内空气的传热系数，
           // 风扇全速时。
#endif

// 对于单风扇配多热端，MPC 需要知道如何施加风扇的
// 冷却效果。
#if ENABLED(MPC_INCLUDE_FAN)
// #define MPC_FAN_0_ALL_HOTENDS
// #define MPC_FAN_0_ACTIVE_HOTEND
#endif

#define FILAMENT_HEAT_CAPACITY_PERMM                                           \
  {5.6e-3f} // 1.75mm PLA 为 0.0056 J/K/mm（2.85mm PLA 为 0.0149 J/K/mm）。
// #define FILAMENT_HEAT_CAPACITY_PERMM { 3.6e-3f }  // 1.75mm 为 0.0036 J/K/mm
// （2.85mm PETG 为 0.0094 J/K/mm）。

// 高级选项
#define MPC_SMOOTHING_FACTOR                                                   \
  0.5f // (0.0...1.0) 噪声较大的温度传感器可能需要更小的值以
       // 获得稳定。
#define MPC_MIN_AMBIENT_CHANGE                                                 \
  1.0f // (K/s) 修正模型不准确时建模的环境温度变化率
       // 模型。
#define MPC_STEADYSTATE                                                        \
  0.5f // (K/s) 强制稳态逻辑所需的温度变化率。

#define MPC_TUNING_POS { X_CENTER, Y_CENTER, 1.0f } // (mm) M306 自动整定位置，理想为第一层高度处的热床中心。
#define MPC_TUNING_END_Z 10.0f // (mm) M306 自动整定的最终 Z 位置。
#endif

//===========================================================================
//============================ PID > 热床温度控制 ===========================
//===========================================================================

/**
 * PID 热床加热
 *
 * 启用此选项时，请在下方设置 PID 常数。
 * 禁用此选项时将使用 bang-bang，并由 BED_LIMIT_SWITCHING
 * 启用迟滞。
 *
 * PID 频率将与挤出机 PWM 相同。
 * 如果 PID_dT 为默认值且与硬件/配置相符，那意味着
 * 7.689Hz，这足以驱动电阻负载上的方波，且不会明显影响
 * FET 加热。这在搭配
 * Fotek SSR-10DA 固态继电器驱动 250W 加热器时同样适用。如果你的配置
 * 与此有很大差异，且你不了解其中的问题，请在他人验证你的硬件
 * 真正可用之前不要使用热床 PID，
 * 直到确认硬件可以正常工作。
 * @section bed temp
 */
// #define PIDTEMPBED

// #define BED_LIMIT_SWITCHING

/**
 * 最大热床功率
 * 适用于所有形式的热床控制（PID、bang-bang 以及带迟滞的
 * bang-bang）。当设为低于 255 的任何值时，会启用一种作用于
 * 热床的分压式 PWM，因此除非你可以接受在热床上使用 PWM，
 * 否则请不要使用它。（参见启用 PIDTEMPBED 的说明）
 */
#define MAX_BED_POWER 255 // 限制热床的占空比；255=满电流

#if ENABLED(PIDTEMPBED)
// #define MIN_BED_POWER 0
// #define PID_BED_DEBUG // 将热床 PID 调试数据输出到串口。

// 4mm 硼硅玻璃（MendelMax 1.5+）中的 120V 250W 硅胶加热器
// 来自 FOPDT 模型 - kp=.39 Tp=405 Tdead=66，Tc 设为 79.2，激进系数
// 为 .15（相比 .1、1、10）
#define DEFAULT_bedKp 10.00
#define DEFAULT_bedKi .023
#define DEFAULT_bedKd 305.4

// 自行测试："M303 E-1 C8 S90" 可在热床上以 90°C
// 运行 8 个周期的自动整定。
#endif // PIDTEMPBED

//===========================================================================
//============================ PID > 腔体温度控制 ===========================
//===========================================================================

/**
 * PID 腔体加热
 *
 * 启用此选项时，请在下方设置 PID 常数。
 * 禁用此选项时将使用 bang-bang，并由
 * CHAMBER_LIMIT_SWITCHING 启用迟滞。
 *
 * PID 频率将与挤出机 PWM 相同。
 * 如果 PID_dT 为默认值且与硬件/配置相符，那意味着
 * 7.689Hz，这足以驱动电阻负载上的方波，且不会明显影响
 * FET 加热。这在搭配
 * Fotek SSR-10DA 固态继电器驱动 200W 加热器时同样适用。如果你的配置
 * 与此有很大差异，且你不了解其中的问题，请在他人验证你的硬件
 * 真正可用之前不要使用腔体 PID，
 * 直到确认硬件可以正常工作。
 * @section chamber temp
 */
// #define PIDTEMPCHAMBER
// #define CHAMBER_LIMIT_SWITCHING

/**
 * 最大腔体功率
 * 适用于所有形式的腔体控制（PID、bang-bang 以及带迟滞的
 * bang-bang）。当设为低于 255 的任何值时，会启用一种作用于
 * 腔体加热器的分压式 PWM，因此除非你可以接受在加热器上使用 PWM，
 * 否则请不要使用它。（参见启用 PIDTEMPCHAMBER 的说明）
 */
#define MAX_CHAMBER_POWER                                                      \
  255 // 限制腔体加热器的占空比；255=满电流

#if ENABLED(PIDTEMPCHAMBER)
#define MIN_CHAMBER_POWER 0
// #define PID_CHAMBER_DEBUG // 将腔体 PID 调试数据输出到串口。

// Lasko "MyHeat Personal Heater" (200w) 改装加装 Fotek SSR-10DA，
// 只控制加热元件，并放置在小型 Creality 打印机
// 外壳罩内。
//
#define DEFAULT_chamberKp 37.04
#define DEFAULT_chamberKi 1.40
#define DEFAULT_chamberKd 655.17
// M309 P37.04 I1.04 D655.17

// 自行测试："M303 E-2 C8 S50" 可在腔体上以 50°C
// 运行 8 个周期的自动整定。
#endif // PIDTEMPCHAMBER

#if ANY(PIDTEMP, PIDTEMPBED, PIDTEMPCHAMBER)
// #define PID_OPENLOOP          // 将 PID 置于开环模式。M104/M140 设置
//  输出功率从 0 到 PID_MAX
// #define SLOW_PWM_HEATERS      // 使用频率极低的
// PWM（约 0.125Hz=8s），最小状态时间约 1s，
// 适用于由继电器驱动的加热器
#define PID_FUNCTIONAL_RANGE                                                   \
  10 // 如果目标温度与实际温度之差超过
     // PID_FUNCTIONAL_RANGE，则 PID 将被关闭，
     // 加热器将被设为最小/最大值。

// #define PID_EDIT_MENU         // 在 "Advanced Settings" 菜单中加入 PID 编辑
//  。（约占用 700 字节 flash）
// #define PID_AUTOTUNE_MENU     // 加入 PID
// 自动整定到 "Advanced Settings" 菜单。（约占用 250 字节 flash）
#endif

// @section safety

/**
 * 如果温度低于 EXTRUDE_MINTEMP 则禁止挤出。
 * 添加 M302 可设置最低挤出温度，并可开启或关闭
 * 冷挤出保护。
 *
 * *** 强烈建议保持此选项启用！ ***
 */
#define PREVENT_COLD_EXTRUSION
#define EXTRUDE_MINTEMP 170

/**
 * 防止单次挤出长度超过 EXTRUDE_MAXLENGTH。
 * 注意：对于 Bowden 挤出机，请把该值设得足够大以允许装卸料。
 */
#define PREVENT_LENGTHY_EXTRUDE
#define EXTRUDE_MAXLENGTH 200

//===========================================================================
//=============================== 温度失控保护 ==============================
//===========================================================================

/**
 * 温度保护为打印机提供额外的保护，避免损坏
 * 和起火。Marlin 始终内置安全的最低和最高温度范围，
 * 可防止热敏电阻导线断裂或脱落。
 *
 * 问题在于：如果热敏电阻脱落，它会读出
 * 室内空气低得多的温度，固件会继续
 * 保持加热器开启。
 *
 * 如果出现 "Thermal Runaway" 或 "Heating failed" 错误，
 * 可以在 Configuration_adv.h 中调整相关参数
 */

#define THERMAL_PROTECTION_HOTENDS // 为所有
                                   // 挤出机启用温度保护
#define THERMAL_PROTECTION_BED // 为加热热床启用温度保护
#define THERMAL_PROTECTION_CHAMBER // 为加热
                                   // 腔体启用温度保护
#define THERMAL_PROTECTION_COOLER  // 为激光
                                   // 冷却启用温度保护

//===========================================================================
//=================================== 机械设置 ==============================
//===========================================================================

// @section machine

// 为 CoreXY、CoreXZ 或 CoreYZ 运动学启用下面其中之一，
// 可按通常顺序，也可以反向
// #define COREXY
// #define COREXZ
// #define COREYZ
// #define COREYX
// #define COREZX
// #define COREZY
// #define MARKFORGED_XY  // MarkForged。参见
//  https://reprap.org/forum/read.php?152,504042
// #define MARKFORGED_YX

// 用于带无限 "Z" 运动的皮带式打印机
// #define BELTPRINTER

// 用于 Polargraph 运动学
// #define POLARGRAPH
#if ENABLED(POLARGRAPH)
#define POLARGRAPH_MAX_BELT_LEN                                                \
  1035.0 // (mm) 完全伸展时的皮带长度。可用 M665 H 覆盖。
#define DEFAULT_SEGMENTS_PER_SECOND 5 // 按时间对运动进行分段
#define PEN_UP_DOWN_MENU // 在 MarlinUI 菜单中加入 "Pen Up" 和 "Pen Down"
#endif

// @section delta

// 用于 DELTA 运动学并在下文配置
// #define DELTA
#if ENABLED(DELTA)

// 用许多直线段构成 DELTA 曲线（线性插值）。
// 这是在可见折角（分段不足）
// 与处理器过载（过多昂贵的 sqrt 调用）之间的权衡。
#define DEFAULT_SEGMENTS_PER_SECOND 200

// 归位后下移到 XY 运动不受限的高度
// #define DELTA_HOME_TO_SAFE_ZONE

// DELTA 校准菜单
// 在 MarlinUI 菜单中加入三点校准。
// 参见 http://minow.blogspot.com/index.html#4918805519571907051
// #define DELTA_CALIBRATION_MENU

// G33 DELTA 自动校准。启用 EEPROM_SETTINGS 以保存结果。
// #define DELTA_AUTO_CALIBRATION

#if ENABLED(DELTA_AUTO_CALIBRATION)
// 默认探针点数量 : n*n (1 -> 7)
#define DELTA_CALIBRATION_DEFAULT_POINTS 4
#endif

#if EITHER(DELTA_AUTO_CALIBRATION, DELTA_CALIBRATION_MENU)
// 纸质测试的探测步长
#define PROBE_MANUALLY_STEP 0.05 // (mm)
#endif

// 打印面直径的一半减去不可达空间（避免与
// 立柱碰撞）。
#define PRINTABLE_RADIUS 140.0 // (mm)

// 最大可达范围
#define DELTA_MAX_RADIUS 140.0 // (mm)

// 斜向推杆上孔位之间的中心距。
#define DELTA_DIAGONAL_ROD 250.0 // (mm)

// 热床与喷嘴 Z 归位位置之间的距离
#define DELTA_HEIGHT 250.00 // (mm) 此值可从 G33 自动校准获得

#define DELTA_ENDSTOP_ADJ                                                      \
  {0.0, 0.0, 0.0} // 这些值可从 G33 自动校准获得

// 效应器居中时斜向推杆跨越的水平距离。
#define DELTA_RADIUS 124.0 // (mm) 此值可从 G33 自动校准获得

// 各塔的微调
// X 和 Y 塔的角度修正 / 旋转 XYZ 使 Z 塔角度 = 0
// 以从打印机上方俯视逆时针方向测量的度数计
#define DELTA_TOWER_ANGLE_TRIM                                                 \
  {0.0, 0.0, 0.0} // 这些值可从 G33 自动校准获得

// DELTA 半径和斜向推杆的微调 (mm)
// #define DELTA_RADIUS_TRIM_TOWER { 0.0, 0.0, 0.0 }
// #define DELTA_DIAGONAL_ROD_TRIM_TOWER { 0.0, 0.0, 0.0 }
#endif

// @section scara

/**
 * MORGAN_SCARA 由 QHARLEY 于 2012-2013 年在南非开发。
 * 由 JCERNY 于 2014 年 6 月实现并略作改进。
 *
 * Mostly Printed SCARA 是 Tyler Williams 的开源设计。参见：
 *   https://www.thingiverse.com/thing:2487048
 *   https://www.thingiverse.com/thing:1241491
 */
// #define MORGAN_SCARA
// #define MP_SCARA
#if EITHER(MORGAN_SCARA, MP_SCARA)
// 如果运动不流畅，可尝试降低该值
#define DEFAULT_SEGMENTS_PER_SECOND 200

// 内外支撑臂的长度。请精确测量臂长。
#define SCARA_LINKAGE_1 150 // (mm)
#define SCARA_LINKAGE_2 150 // (mm)

// SCARA 塔偏移（塔相对热床零位的位置）
// 该值需要足够准确，因为它定义了打印床在 SCARA 坐标系中的
// 位置。
#define SCARA_OFFSET_X 100 // (mm)
#define SCARA_OFFSET_Y -56 // (mm)

#if ENABLED(MORGAN_SCARA)

// #define DEBUG_SCARA_KINEMATICS
#define FEEDRATE_SCALING // 实时将 XY 进给速度从 mm/s 换算为
                         // 度/s

// 机械臂无法到达的中心半径
#define MIDDLE_DEAD_ZONE_R 0 // (mm)

#define THETA_HOMING_OFFSET                                                    \
  0 // 根据校准指南和 M360 / M114 计算。参见
    // http://reprap.harleystudio.co.za/?page_id=1073
#define PSI_HOMING_OFFSET                                                      \
  0 // 根据校准指南和 M364 / M114 计算。参见
    // http://reprap.harleystudio.co.za/?page_id=1073

#elif ENABLED(MP_SCARA)

#define SCARA_OFFSET_THETA1 12  // 度
#define SCARA_OFFSET_THETA2 131 // 度

#endif

#endif

// @section tpara

// 用于 TPARA 运动学并在下文配置
// #define AXEL_TPARA
#if ENABLED(AXEL_TPARA)
#define DEBUG_TPARA_KINEMATICS
#define DEFAULT_SEGMENTS_PER_SECOND 200

// 内外支撑臂的长度。请精确测量臂长。
#define TPARA_LINKAGE_1 120 // (mm)
#define TPARA_LINKAGE_2 120 // (mm)

// SCARA 塔偏移（塔相对热床零位的位置）
// 该值需要足够准确，因为它定义了打印床在 SCARA 坐标系中的
// 位置。
#define TPARA_OFFSET_X 0 // (mm)
#define TPARA_OFFSET_Y 0 // (mm)
#define TPARA_OFFSET_Z 0 // (mm)

#define FEEDRATE_SCALING // 实时将 XY 进给速度从 mm/s 换算为
                         // 度/s

// 机械臂无法到达的中心半径
#define MIDDLE_DEAD_ZONE_R 0 // (mm)

// 根据校准指南和 M360 / M114 计算。参见
// http://reprap.harleystudio.co.za/?page_id=1073
#define THETA_HOMING_OFFSET 0
#define PSI_HOMING_OFFSET 0
#endif

// @section polar

/**
 * POLAR 运动学
 *  由 Kadir ilkimen 为 PolarBear CNC 和 babyBear 开发
 *  https://github.com/kadirilkimen/Polar-Bear-Cnc-Machine
 *  https://github.com/kadirilkimen/babyBear-3D-printer
 *
 * 极坐标机器可以有多种配置。
 * 此运动学仅兼容以下配置：
 *        X : 独立直线轴
 *   Y or B : 极坐标轴
 *        Z : 独立直线轴
 *
 * 例如，PolarBear 采用 CoreXZ 加上极坐标 Y 或 B 轴。
 *
 * 极坐标轴靠近中心/原点时的运动问题：
 *
 * 3D 打印：
 * 非常靠近极坐标轴中心的运动会比其他的耗时更长。
 * 这段短暂延迟会因喷嘴内的压力而导致
 * 更多的材料堆积。
 *
 * 目前的运动学和进给速度缩放通过让运动
 * 尽可能快地进行处理。它对慢速运动有效，但对快速运动
 * 效果不佳。必须实现更复杂的挤出补偿
 * 机制。
 *
 * 理想情况下，它应该能估计到前方存在靠近中心的长时间旋转，
 * 并会造成多余的堆积。因此它可以提前补偿挤出
 * 量。
 *
 * 激光切割：
 * 同样的问题也会影响激光雕刻。由于它花时间
 * 在中心点旋转，更有可能烧蚀掉比应该烧蚀更多的
 * 材料。因此激光切割操作也会实现类似的
 * 补偿。
 *
 * 铣削：
 * 对于切削/铣削操作，这不应成为问题。
 */
// #define POLAR
#if ENABLED(POLAR)
#define DEFAULT_SEGMENTS_PER_SECOND                                            \
  180                          // 如果运动不流畅，可尝试降低该值
#define PRINTABLE_RADIUS 82.0f // (mm) X 轴的最大行程

// 落在 POLAR_FAST_RADIUS 之内的运动会获得尽可能高的
// 进给速度，以补偿靠近原点运动问题所致的
// 多余堆积。
#define POLAR_FAST_RADIUS 3.0f // (mm)

// 工具无法到达的半径。
// 当工具未与极坐标轴中心完全对齐时需要此值。
#define POLAR_CENTER_OFFSET 0.0f // (mm)

#define FEEDRATE_SCALING // 实时将 XY 进给速度从 mm/s 换算为
                         // 度/s
#endif

// @section machine

// 关节式机器人（机械臂）。关节直接映射到各轴，无
// 运动学。
// #define ARTICULATED_ROBOT_ARM

// 用于热丝切割机，其中两条平行的水平轴（X, I）的高度
// 由两条平行轴（Y, J）控制。关节直接
// 映射到各轴（无运动学）。
// #define FOAMCUTTER_XYUV

//===========================================================================
//================================ 限位开关设置 =============================
//===========================================================================

// @section endstops

// 在此指定连接到限位开关或探针的所有限位开关接口。
// 几乎所有打印机每个轴都会用一个。探针会使用一个或
// 多个额外的接口。用于非限位开关且非探针用途的接口
// 请保持未定义。
#define USE_XMIN_PLUG
#define USE_YMIN_PLUG
#define USE_ZMIN_PLUG
#define USE_IMIN_PLUG
#define USE_JMIN_PLUG
#define USE_KMIN_PLUG
// #define USE_UMIN_PLUG
// #define USE_VMIN_PLUG
// #define USE_WMIN_PLUG
// #define USE_XMAX_PLUG
// #define USE_YMAX_PLUG
// #define USE_ZMAX_PLUG
// #define USE_IMAX_PLUG
// #define USE_JMAX_PLUG
// #define USE_KMAX_PLUG
// #define USE_UMAX_PLUG
// #define USE_VMAX_PLUG
// #define USE_WMAX_PLUG

// 为所有限位开关启用上拉，防止状态悬空
#define ENDSTOPPULLUPS
#if DISABLED(ENDSTOPPULLUPS)
// 禁用 ENDSTOPPULLUPS 以单独设置上拉
// #define ENDSTOPPULLUP_XMIN
// #define ENDSTOPPULLUP_YMIN
// #define ENDSTOPPULLUP_ZMIN
// #define ENDSTOPPULLUP_IMIN
// #define ENDSTOPPULLUP_JMIN
// #define ENDSTOPPULLUP_KMIN
// #define ENDSTOPPULLUP_UMIN
// #define ENDSTOPPULLUP_VMIN
// #define ENDSTOPPULLUP_WMIN
// #define ENDSTOPPULLUP_XMAX
// #define ENDSTOPPULLUP_YMAX
// #define ENDSTOPPULLUP_ZMAX
// #define ENDSTOPPULLUP_IMAX
// #define ENDSTOPPULLUP_JMAX
// #define ENDSTOPPULLUP_KMAX
// #define ENDSTOPPULLUP_UMAX
// #define ENDSTOPPULLUP_VMAX
// #define ENDSTOPPULLUP_WMAX
// #define ENDSTOPPULLUP_ZMIN_PROBE
#endif

// 为所有限位开关启用下拉，防止状态悬空
// #define ENDSTOPPULLDOWNS
#if DISABLED(ENDSTOPPULLDOWNS)
// 禁用 ENDSTOPPULLDOWNS 以单独设置下拉
// #define ENDSTOPPULLDOWN_XMIN
// #define ENDSTOPPULLDOWN_YMIN
// #define ENDSTOPPULLDOWN_ZMIN
// #define ENDSTOPPULLDOWN_IMIN
// #define ENDSTOPPULLDOWN_JMIN
// #define ENDSTOPPULLDOWN_KMIN
// #define ENDSTOPPULLDOWN_UMIN
// #define ENDSTOPPULLDOWN_VMIN
// #define ENDSTOPPULLDOWN_WMIN
// #define ENDSTOPPULLDOWN_XMAX
// #define ENDSTOPPULLDOWN_YMAX
// #define ENDSTOPPULLDOWN_ZMAX
// #define ENDSTOPPULLDOWN_IMAX
// #define ENDSTOPPULLDOWN_JMAX
// #define ENDSTOPPULLDOWN_KMAX
// #define ENDSTOPPULLDOWN_UMAX
// #define ENDSTOPPULLDOWN_VMAX
// #define ENDSTOPPULLDOWN_WMAX
// #define ENDSTOPPULLDOWN_ZMIN_PROBE
#endif

/**
 * 限位开关“触发”状态
 * 设置适用于每个限位开关的状态（HIGH 或 LOW）。
 */
#define X_MIN_ENDSTOP_HIT_STATE LOW
#define X_MAX_ENDSTOP_HIT_STATE HIGH
#define Y_MIN_ENDSTOP_HIT_STATE LOW
#define Y_MAX_ENDSTOP_HIT_STATE HIGH
#define Z_MIN_ENDSTOP_HIT_STATE HIGH
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
// 这样无需轮询中断引脚，可节省大量 CPU 周期。
// #define ENDSTOP_INTERRUPTS_FEATURE

/**
 * 限位开关噪声阈值
 *
 * 如果探针或限位开关因噪声而误触发，请启用。
 *
 * - 数值越大，某些热床探针的重复性或精度可能受影响。
 * - 为消除噪声，请在开关两端并联一个 100nF 陶瓷电容。
 * - 对于安装在 PCB 上、基于 Makerbot 设计的普通微动开关，
 *   本功能并非必需，因为它们已经带有 100nF 电容。
 *
 * :[2,3,4,5,6,7]
 */
// #define ENDSTOP_NOISE_THRESHOLD 2

// 归位移动过程中检测卡死或断开的限位开关。
// #define DETECT_BROKEN_ENDSTOP

//=============================================================================
//============================== 运动设置 ============================
//=============================================================================
// @section motion

/**
 * 默认设置
 *
 * 这些设置可以通过 M502 复位
 *
 * 注意：如果启用了 EEPROM，保存的值将覆盖这些设置。
 */

/**
 * 启用此选项后，每个 E 步进电机可以为以下运动设置拥有各自的
 * 系数。如果给出的系数数量少于挤出机总数，
 * 则其余的挤出机都使用最后一个值。
 */
// #define DISTINCT_E_FACTORS

/**
 * 默认每单位轴步数 (linear=steps/mm, rotational=steps/°)
 * 用 M92 覆盖
 *                                      X, Y, Z [, I [, J [, K...]]], E0 [, E1[,
 * E2...]]
 */
#define DEFAULT_AXIS_STEPS_PER_UNIT {320, 320, 40, 4.44, 4.44}

/**
 * 默认最大进给速度 (linear=mm/s, rotational=°/s)
 * 用 M203 覆盖
 *                                      X, Y, Z [, I [, J [, K...]]], E0 [, E1[,
 * E2...]]
 */
#define DEFAULT_MAX_FEEDRATE {7000, 7000, 1000, 50000, 50000}

// #define LIMITED_MAX_FR_EDITING        // 通过 M203 或 LCD 将编辑上限限制为
// DEFAULT_MAX_FEEDRATE * 2
#if ENABLED(LIMITED_MAX_FR_EDITING)
#define MAX_FEEDRATE_EDIT_VALUES                                               \
  {600, 600, 10, 50} // ...或设置你自己的编辑上限
#endif

/**
 * 默认最大加速度（随时间的速度变化） (linear=mm/(s^2),
 * rotational=°/(s^2)) （加速移动的最大起始速度）。覆盖命令为
 * M201 X, Y, Z [, I [, J [, K...]]], E0 [, E1[, E2...]]
 */
#define DEFAULT_MAX_ACCELERATION {15000, 15000, 10000, 10000, 10000}

// #define LIMITED_MAX_ACCEL_EDITING     // 通过 M201 或 LCD 将编辑上限限制为
// DEFAULT_MAX_ACCELERATION * 2
#if ENABLED(LIMITED_MAX_ACCEL_EDITING)
#define MAX_ACCEL_EDIT_VALUES                                                  \
  {6000, 6000, 200, 20000} // ...或设置你自己的编辑上限
#endif

/**
 * 默认加速度（随时间的速度变化） (linear=mm/(s^2),
 * rotational=°/(s^2)) 用 M204 覆盖
 *
 *   M204 P    加速度
 *   M204 R    回抽加速度
 *   M204 T    空移加速度
 *   M204 I    角加速度
 *   M204 J    角空移加速度
 */
#define DEFAULT_ACCELERATION                                                   \
  2000 // X, Y, Z ... 以及打印移动的 E 加速度
#define DEFAULT_RETRACT_ACCELERATION 3000 // 回抽时的 E 加速度
#define DEFAULT_TRAVEL_ACCELERATION                                            \
  2500 // X, Y, Z ... 空移（非打印）移动的加速度
#if ENABLED(AXIS4_ROTATES)
#define DEFAULT_ANGULAR_ACCELERATION                                           \
  3000 // I, J, K 在仅旋转的打印移动中的加速度
#define DEFAULT_ANGULAR_TRAVEL_ACCELERATION                                    \
  3000 // I, J, K 在仅旋转的空移（非打印）移动中的加速度
#endif

/**
 * 默认加加速度限制 (mm/s)
 * 用 M205 X Y Z . . . E 覆盖
 *
 * "加加速度"表示需要施加加速度的最小速度变化量。
 * 当改变速度和方向时，如果差值小于这里设定的数值，
 * 就可能会瞬间完成。
 */
// #define CLASSIC_JERK
#if ENABLED(CLASSIC_JERK)
#define DEFAULT_XJERK 10.0
#define DEFAULT_YJERK 10.0
#define DEFAULT_ZJERK 0.3
// #define DEFAULT_IJERK  0.3
// #define DEFAULT_JJERK  0.3
// #define DEFAULT_KJERK  0.3
// #define DEFAULT_UJERK  0.3
// #define DEFAULT_VJERK  0.3
// #define DEFAULT_WJERK  0.3

// #define TRAVEL_EXTRA_XYJERK 0.0     // 所有空移移动额外允许的
// 加加速度

// #define LIMITED_JERK_EDITING        // 通过 M205 或 LCD 将编辑上限限制为
// DEFAULT_aJERK * 2
#if ENABLED(LIMITED_JERK_EDITING)
#define MAX_JERK_EDIT_VALUES                                                   \
  {20, 20, 0.6, 10} // ...或设置你自己的编辑上限
#endif
#endif

#define DEFAULT_EJERK 5.0 // 可供 Linear Advance 使用

/**
 * 结点偏差系数
 *
 * 参见：
 *   https://reprap.org/forum/read.php?1,739819
 *   https://blog.kyneticcnc.com/2018/10/computing-junction-deviation-for-marlin.html
 */
#if DISABLED(CLASSIC_JERK)
#define JUNCTION_DEVIATION_MM 0.013 // (mm) 与实际结点边缘的距离
#define JD_HANDLE_SMALL_SEGMENTS // 对于小线段 (< 1mm) 且
                                 // 结点角较大 (> 135°) 时，使用曲率估算
                                 // 而不仅仅使用结点角。
#endif

/**
 * S 曲线加速度
 *
 * 此选项通过为移动加速度拟合贝塞尔曲线来消除打印过程中的振动，
 * 从而使方向变化更加平滑。
 *
 * 参见 https://github.com/synthetos/TinyG/wiki/Jerk-Controlled-Motion-Explained
 */
// #define S_CURVE_ACCELERATION

//===========================================================================
//============================= Z 轴探针选项 =============================
//===========================================================================
// @section probes

//
// 参见 https://marlinfw.org/docs/configuration/probes.html
//

/**
 * 如果探针连接到 Z-MIN 引脚，请启用此选项。
 * 探针将取代 Z-MIN 限位开关，用于 Z 轴归位。
 * （自动启用 USE_PROBE_FOR_Z_HOMING。）
 */
#define Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN

// 强制使用探针进行 Z 轴归位
// #define USE_PROBE_FOR_Z_HOMING

/**
 * Z_MIN_PROBE_PIN
 *
 * 仅当探针无法连接到所选 MOTHERBOARD 的默认
 * Z_MIN_PROBE_PIN 时，才需要覆盖此引脚。
 *
 *  - 最简单的做法是使用空闲的限位开关接口。
 *  - 有源（通常是电感式）传感器请使用 5V。
 *
 *  - 对于简单开关...
 *    - 常闭 (NC) 也要连接到 GND。
 *    - 常开 (NO) 也要连接到 5V。
 */
// #define Z_MIN_PROBE_PIN -1

/**
 * 探针类型
 *
 * 六角扳手探针、舵机探针、Z 滑架探针、FIX_MOUNTED_PROBE 等。
 * 启用其中之一即可使用下面的自动热床调平功能。
 */

/**
 * "手动探针"让你无需探针也能进行"自动"热床调平。
 * 反复使用 G29，用移动命令（或在启用 LCD_BED_LEVELING 时用 LCD 控制器）
 * 调整每个点位的 Z 高度。
 */
// #define PROBE_MANUALLY

/**
 * 固定式探针要么无法自动展开，要么需要手动展开。
 *   （例如电感式探针或基于喷嘴的探针开关。）
 */
// #define FIX_MOUNTED_PROBE

/**
 * 将喷嘴用作探针，例如在导电喷嘴系统
 * 或压电式智能执行器中。
 */
// #define NOZZLE_AS_PROBE

/**
 * Z 轴舵机探针，例如装在旋转臂上的限位开关。
 */
// #define Z_PROBE_SERVO_NR 0
#ifdef Z_PROBE_SERVO_NR
// #define Z_SERVO_ANGLES { 70, 0 }      // Z 舵机展开和收回角度
// #define Z_SERVO_MEASURE_ANGLE 45      // 如果舵机必须移动到某个
//  "自由" 位置才能在展开后测量
// #define Z_SERVO_INTERMEDIATE_STOW
//  // 在各测量点之间收回探针
// #define Z_SERVO_DEACTIVATE_AFTER_STOW // 探针收回时停用舵机
#endif
/**
 * BLTouch 探针使用霍尔传感器，并模拟一个舵机。
 */
// #define BLTOUCH

/**
 * MDD 的 MagLev V4 探针
 *
 * 此探针通过给内置电磁铁供电来展开并激活。
 */
// #define MAGLEV4
#if ENABLED(MAGLEV4)
// #define MAGLEV_TRIGGER_PIN 11     // 设置为已连接的数字输出
#define MAGLEV_TRIGGER_DELAY 15 // 修改此值可能导致线圈过热
#endif

/**
 * hotends.fr 的 Touch-MI 探针
 *
 * 此探针通过将 X 轴移动到热床边缘的磁铁处来展开并激活。
 * 默认假定磁铁在左侧，并通过
 * 归位动作激活。如果磁铁在右侧，请启用并把
 * TOUCH_MI_DEPLOY_XPOS 设置为展开位置。
 *
 * 另外还需要：BABYSTEPPING, BABYSTEP_ZPROBE_OFFSET, Z_SAFE_HOMING,
 *                以及 Z_HOMING_HEIGHT 不小于 10。
 */
// #define TOUCH_MI_PROBE
#if ENABLED(TOUCH_MI_PROBE)
#define TOUCH_MI_RETRACT_Z 0.5 // 探针回抽时的高度
// #define TOUCH_MI_DEPLOY_XPOS (X_MAX_BED + 2)  // 用于磁铁位于热床右侧
//  的情况
// #define TOUCH_MI_MANUAL_DEPLOY                // 用于手动
// 展开（LCD 菜单）
#endif

// 使用电磁铁引脚 (SOL1_PIN) 展开和收回的探针
// #define SOLENOID_PROBE

// 类似 Charles Bell 设计的滑架式探针。
// #define Z_PROBE_SLED
// #define SLED_DOCKING_OFFSET 5  // X 轴需要额外移动的距离
// 以拾取滑架。0 就足够了，但如果你愿意
// 也可以设得更大。

// 通过移动 X 轴展开的探针，例如 Marty Rice 设计的
// Wilson II 齿条齿轮式探针。
// #define RACK_AND_PINION_PROBE
#if ENABLED(RACK_AND_PINION_PROBE)
#define Z_PROBE_DEPLOY_X X_MIN_POS
#define Z_PROBE_RETRACT_X X_MAX_POS
#endif

/**
 * 磁性安装式探针
 * 适用于 Euclid、Klicky、Klackender 等探针。
 */
// #define MAG_MOUNTED_PROBE
#if ENABLED(MAG_MOUNTED_PROBE)
#define PROBE_DEPLOY_FEEDRATE (133 * 60) // (mm/min) 探针展开速度
#define PROBE_STOW_FEEDRATE (133 * 60)   // (mm/min) 探针收回速度

#define MAG_MOUNTED_DEPLOY_1                                                   \
  {PROBE_DEPLOY_FEEDRATE, {245, 114, 30}} // 移动到侧边停靠位并接上探针
#define MAG_MOUNTED_DEPLOY_2                                                   \
  {PROBE_DEPLOY_FEEDRATE, {210, 114, 30}} // 将探针移离停靠位
#define MAG_MOUNTED_DEPLOY_3                                                   \
  {PROBE_DEPLOY_FEEDRATE, {0, 0, 0}} // 如有需要可额外移动
#define MAG_MOUNTED_DEPLOY_4                                                   \
  {PROBE_DEPLOY_FEEDRATE, {0, 0, 0}} // 如有需要可额外移动
#define MAG_MOUNTED_DEPLOY_5                                                   \
  {PROBE_DEPLOY_FEEDRATE, {0, 0, 0}} // 如有需要可额外移动
#define MAG_MOUNTED_STOW_1 {PROBE_STOW_FEEDRATE, {245, 114, 20}} // 移动到停靠位
#define MAG_MOUNTED_STOW_2                                                     \
  {PROBE_STOW_FEEDRATE, {245, 114, 0}} // 将探针放到移除器旁
#define MAG_MOUNTED_STOW_3                                                     \
  {PROBE_STOW_FEEDRATE, {230, 114, 0}} // 侧向移动以移除探针
#define MAG_MOUNTED_STOW_4                                                     \
  {PROBE_STOW_FEEDRATE, {210, 114, 20}} // 侧向移动以移除探针
#define MAG_MOUNTED_STOW_5                                                     \
  {PROBE_STOW_FEEDRATE, {0, 0, 0}} // 如有需要可额外移动
#endif

// Duet Smart Effector（用于 delta 打印机） - https://bit.ly/2ul5U7J
// 定义该引脚后，可用 M672 设置/复位探针灵敏度。
// #define DUET_SMART_EFFECTOR
#if ENABLED(DUET_SMART_EFFECTOR)
#define SMART_EFFECTOR_MOD_PIN                                                 \
  -1 // 将一个 GPIO 引脚连接到 Smart Effector 的 MOD 引脚
#endif

/**
 * 使用 StallGuard2 以喷嘴探测热床。
 * 需要支持 stallGuard 的 Trinamic 步进电机驱动。
 * 注意：这可能会损坏使用 Z 轴丝杠的机器。
 *          设置此功能时请务必格外小心。
 */
// #define SENSORLESS_PROBING

/**
 * 许多 Kossel delta 打印机上常见的六角扳手可回缩 Z 探针 -
 * https://reprap.org/wiki/Kossel#Automatic_bed_leveling_probe 展开方式为
 * 触碰 Z 轴同步带。回缩方式为向下压探针。
 */
// #define Z_PROBE_ALLEN_KEY
#if ENABLED(Z_PROBE_ALLEN_KEY)
// 如果没有定义舵机驱动的触点探针，请为 G29 部署和回收弹簧加载式
// 触点探针提供 2 或 3 组坐标。请根据你的打印机/探针
// 情况取消相应的注释。

#define Z_PROBE_ALLEN_KEY_DEPLOY_1 {30.0, PRINTABLE_RADIUS, 100.0}
#define Z_PROBE_ALLEN_KEY_DEPLOY_1_FEEDRATE XY_PROBE_FEEDRATE

#define Z_PROBE_ALLEN_KEY_DEPLOY_2 {0.0, PRINTABLE_RADIUS, 100.0}
#define Z_PROBE_ALLEN_KEY_DEPLOY_2_FEEDRATE (XY_PROBE_FEEDRATE) / 10

#define Z_PROBE_ALLEN_KEY_DEPLOY_3 {0.0, (PRINTABLE_RADIUS) * 0.75, 100.0}
#define Z_PROBE_ALLEN_KEY_DEPLOY_3_FEEDRATE XY_PROBE_FEEDRATE

#define Z_PROBE_ALLEN_KEY_STOW_1                                               \
  {-64.0, 56.0, 23.0} // 将探针移动到指定位置
#define Z_PROBE_ALLEN_KEY_STOW_1_FEEDRATE XY_PROBE_FEEDRATE

#define Z_PROBE_ALLEN_KEY_STOW_2 {-64.0, 56.0, 3.0} // 向下压入
#define Z_PROBE_ALLEN_KEY_STOW_2_FEEDRATE (XY_PROBE_FEEDRATE) / 10

#define Z_PROBE_ALLEN_KEY_STOW_3 {-64.0, 56.0, 50.0} // 向上抬起以脱离
#define Z_PROBE_ALLEN_KEY_STOW_3_FEEDRATE XY_PROBE_FEEDRATE

#define Z_PROBE_ALLEN_KEY_STOW_4 {0.0, 0.0, 50.0}
#define Z_PROBE_ALLEN_KEY_STOW_4_FEEDRATE XY_PROBE_FEEDRATE

#endif // Z_PROBE_ALLEN_KEY

/**
 * 喷嘴到探针的偏移 { X, Y, Z }
 *
 * X 和 Y 偏移
 *   用卡尺或直尺测量喷嘴尖端到
 *   探针中心点在 X 和 Y 轴上的距离。
 *
 * Z 偏移
 * - Z 偏移请先使用你已知的最佳数值，并在运行时调整。
 * - 常见探针在喷嘴下方触发，因此 Z 偏移为
 * 负值。
 * - 在喷嘴高度之上触发的探针并不常见，但也确实存在。使用
 * 这类探针时，请仔细设置 Z_CLEARANCE_DEPLOY_PROBE 和
 * Z_CLEARANCE_BETWEEN_PROBES，以避免探测过程中发生碰撞。
 *
 * 微调与调整
 * -  探针偏移可以在运行时通过 'M851'、LCD 菜单、
 * 微动步进等方式进行调整。
 * -  PROBE_OFFSET_WIZARD (configuration_adv.h) 可用于设置 Z
 * 偏移。
 *
 * 假设采用常规的工作区域方向：
 *  - 探针在喷嘴右侧时，X 偏移为正值
 *  - 探针在喷嘴左侧时，X 偏移为负值
 *  - 探针在喷嘴后方时，Y 偏移为正值
 *  - 探针在喷嘴前方时，Y 偏移为负值
 *
 * 一些示例：
 *   #define NOZZLE_TO_PROBE_OFFSET { 10, 10, -1 }   // 示例 "1"
 *   #define NOZZLE_TO_PROBE_OFFSET {-10,  5, -1 }   // 示例 "2"
 *   #define NOZZLE_TO_PROBE_OFFSET {  5, -5, -1 }   // 示例 "3"
 *   #define NOZZLE_TO_PROBE_OFFSET {-15,-10, -1 }   // 示例 "4"
 *
 *     +-- BACK ---+
 *     |    [+]    |
 *   L |        1  | R <-- 示例 "1"（右+, 后+）
 *   E |  2        | I <-- 示例 "2"（左-, 后+）
 *   F |[-]  N  [+]| G <-- 喷嘴
 *   T |       3   | H <-- 示例 "3"（右+, 前-）
 *     | 4         | T <-- 示例 "4"（左-, 前-）
 *     |    [-]    |
 *     O-- FRONT --+
 */
#define NOZZLE_TO_PROBE_OFFSET {10, 10, 0}

// 启用并设置以使用特定工具进行探测。禁用则允许使用任意工具。
#define PROBING_TOOL 0
#ifdef PROBING_TOOL
// #define PROBE_TOOLCHANGE_NO_MOVE  // 探测换刀时抑制运动
#endif

// 大多数探针应远离热床边缘，但
// 使用 NOZZLE_AS_PROBE 时，为获得更大的探测区域，此值可以为负。
#define PROBING_MARGIN 10

// 探测之间 X 和 Y 轴的移动速度 (mm/min)
#define XY_PROBE_FEEDRATE (133 * 60)

// 双重探测时首次接近的进给速度 (mm/min)
// (MULTIPLE_PROBING == 2)
#define Z_PROBE_FEEDRATE_FAST (4 * 60)

// 每个点位的"精确"探测进给速度 (mm/min)
#define Z_PROBE_FEEDRATE_SLOW (Z_PROBE_FEEDRATE_FAST / 2)

/**
 * 探针激活开关
 * 用于指示探针是否正确展开的开关，或在小车靠近热床时触发的
 * 光学开关。
 */
// #define PROBE_ACTIVATION_SWITCH
#if ENABLED(PROBE_ACTIVATION_SWITCH)
#define PROBE_ACTIVATION_SWITCH_STATE LOW // 表示探针处于激活状态的状态值
// #define PROBE_ACTIVATION_SWITCH_PIN PC6 // 覆盖默认引脚
#endif

/**
 * 每次探测前先对探针去皮（确定零点）。
 * 适用于需要排除电缆拉扯小车等影响的应变计或
 * 压电传感器。
 */
// #define PROBE_TARE
#if ENABLED(PROBE_TARE)
#define PROBE_TARE_TIME 200   // (ms) 保持去皮引脚的时间
#define PROBE_TARE_DELAY 200  // (ms) 去皮后的延迟
#define PROBE_TARE_STATE HIGH // 去皮时写入引脚的状态
// #define PROBE_TARE_PIN PA5    // 覆盖默认引脚
#if ENABLED(PROBE_ACTIVATION_SWITCH)
// #define PROBE_TARE_ONLY_WHILE_INACTIVE  // 如果
// PROBE_ACTIVATION_SWITCH 处于激活状态，则去皮/探测失败
#endif
#endif

/**
 * 探针启用/禁用
 * 只有启用后探针才会提供触发信号。
 */
// #define PROBE_ENABLE_DISABLE
#if ENABLED(PROBE_ENABLE_DISABLE)
// #define PROBE_ENABLE_PIN -1   // 在此覆盖默认引脚
#endif

/**
 * 多次探测
 *
 * 探测 2 次或更多次可能得到更好的结果。
 * 使用 EXTRA_PROBING 时，偏离常规的读数将被忽略。
 *
 * 总数为 2 时进行快速/慢速探测并取加权平均。
 * 总数为 3 或更多时会增加慢速探测次数，并取平均值。
 */
// #define MULTIPLE_PROBING 2
// #define EXTRA_PROBING    1

/**
 * Z 探针在展开、收回以及在探测点之间移动时需要留出间隙，
 * 以免撞到热床和其他硬件。
 * 舵机安装的探针需要额外空间供摆臂旋转。
 * 电感式探针需要空间以免提前触发。
 *
 * 用这些设置指定抬起探针（或降低热床）的距离 (mm)。这里设定的值
 * 会叠加在通过 NOZZLE_TO_PROBE_OFFSET、M851 或 LCD 设置的
 * （可能为负的）探针 Z 偏移之上。
 * 此处只允许大于等于 1 的整数值。
 *
 * 示例：`M851 Z-5` 且 CLEARANCE 为 4  =>  喷嘴距热床 9mm。
 *     但是：`M851 Z+1` 且 CLEARANCE 为 2  =>  喷嘴距热床 2mm。
 */
#define Z_CLEARANCE_DEPLOY_PROBE 10 // 展开/收回时的 Z 间隙
// #define Z_CLEARANCE_BETWEEN_PROBES  5 // 探测点之间的 Z 间隙
#define Z_CLEARANCE_MULTI_PROBE 5 // 多次探测之间的 Z 间隙
// #define Z_AFTER_PROBING           5 // 探测完成后的 Z 位置

#define Z_PROBE_LOW_POINT                                                      \
  -2 // 停止前越过触发点的最大下行距离

// 为 M851 给出 Z 探针偏移的调整范围
#define Z_PROBE_OFFSET_RANGE_MIN -20
#define Z_PROBE_OFFSET_RANGE_MAX 20

// 启用 M48 重复性测试以测试探针精度
// #define Z_MIN_PROBE_REPEATABILITY_TEST

// 展开/收回前暂停，等待用户确认
// #define PAUSE_BEFORE_DEPLOY_STOW
#if ENABLED(PAUSE_BEFORE_DEPLOY_STOW)
// #define PAUSE_PROBE_DEPLOY_WHEN_TRIGGERED // 用于手动展开的六角扳手探针
#endif

/**
 * 如果探测结果不可靠，请启用以下一项或多项。
 * 探测期间可以关闭加热器和/或风扇，以尽量减少电气
 * 噪声。也可以加入延时，让噪声和振动稳定下来。
 * 这些选项对 BLTouch 探针最为有用，但也可能改善
 * 电感式探针和压电传感器的读数。
 */
// #define PROBING_HEATERS_OFF       // 探测时关闭加热器
#if ENABLED(PROBING_HEATERS_OFF)
// #define WAIT_FOR_BED_HEATER     // 在探测之间等待热床重新升温
//  （以提高精度）
// #define WAIT_FOR_HOTEND         // 等待
// 热端在探测之间重新升温（以提高精度并防止冷
// 挤出）
#endif
// #define PROBING_FANS_OFF          // 探测时关闭风扇
// #define PROBING_ESTEPPERS_OFF     // 探测时关闭所有挤出机步进
//  电机
// #define PROBING_STEPPERS_OFF      // 探测时关闭所有步进电机（除非
// 需要保持位置）（包括挤出机）
// #define DELAY_BEFORE_PROBING 200  // (ms) 防止振动触发压电
// 传感器

// 探测前要求喷嘴和/或热床达到最低温度
// #define PREHEAT_BEFORE_PROBING
#if ENABLED(PREHEAT_BEFORE_PROBING)
#define PROBING_NOZZLE_TEMP 120 // (°C) 目前仅适用于 E0
#define PROBING_BED_TEMP 50
#endif

// 反转步进电机使能引脚（低电平有效）用 0，不反转（高电平
// 有效）用 1
// :{ 0:'Low', 1:'High' }
#define X_ENABLE_ON 0
#define Y_ENABLE_ON 0
#define Z_ENABLE_ON 0
#define E_ENABLE_ON 0 // 适用于所有挤出机
#define I_ENABLE_ON 0
#define J_ENABLE_ON 0
#define K_ENABLE_ON 0
// #define U_ENABLE_ON 0
// #define V_ENABLE_ON 0
// #define W_ENABLE_ON 0

// 当某个轴步进电机不步进时立即禁用它。
// 警告：电机关闭时有可能丢失位置精度！
// #define DISABLE_X
// #define DISABLE_Y
// #define DISABLE_Z
// #define DISABLE_I
// #define DISABLE_J
// #define DISABLE_K
// #define DISABLE_U
// #define DISABLE_V
// #define DISABLE_W

// 关闭提示可能降低精度的闪烁显示
// #define DISABLE_REDUCED_ACCURACY_WARNING

// @section extruder

// #define DISABLE_E               // 不步进时禁用挤出机
#define DISABLE_OTHER_EXTRUDERS // 只保持当前活动的挤出机启用

// @section motion

// 反转步进电机方向。如果某个轴方向不对，
// 请更改（或交换）电机连接器。
#define INVERT_X_DIR true
#define INVERT_Y_DIR false
#define INVERT_Z_DIR false
#define INVERT_I_DIR true
#define INVERT_J_DIR true
#define INVERT_K_DIR false
// #define INVERT_U_DIR false
// #define INVERT_V_DIR false
// #define INVERT_W_DIR false

// @section extruder

// 直驱挤出机 v9 设为 true，齿轮挤出机设为 false。
#define INVERT_E0_DIR false
#define INVERT_E1_DIR false
#define INVERT_E2_DIR false
#define INVERT_E3_DIR false
#define INVERT_E4_DIR false
#define INVERT_E5_DIR false
#define INVERT_E6_DIR false
#define INVERT_E7_DIR false

// @section homing

// #define NO_MOTION_BEFORE_HOMING // 在所有轴完成归位前禁止移动。
// 另外请启用 HOME_AFTER_DEACTIVATE 以提高安全性。
// #define HOME_AFTER_DEACTIVATE   // 步进电机被禁用后需要重新归位。
// 另外请启用 NO_MOTION_BEFORE_HOMING 以提高安全性。

/**
 * 如果步进电机被禁用时 Z 轴会自行移动，请设置 Z_IDLE_HEIGHT。
 *  - 如果喷嘴会落到热床上，请使用较小的值（即 Z_MIN_POS）。
 *  - 如果热床会下落并远离喷嘴，请使用较大的值
 *  （即 Z_MAX_POS）。
 */
// #define Z_IDLE_HEIGHT Z_HOME_POS

// #define Z_HOMING_HEIGHT  4      // (mm) 归位 (G28) 前的最小 Z 高度
// 以保证热床上方、夹具等的 Z 间隙 ...
//  请确保 Z_MAX_POS 之上留有这么大间隙，以免刮擦。

#define Z_AFTER_HOMING 21 // (mm) Z 轴归位后移动到的高度

// 归位时限位开关的方向；1=MAX，-1=MIN
// :[-1,1]
#define X_HOME_DIR -1
#define Y_HOME_DIR -1
#define Z_HOME_DIR -1
#define I_HOME_DIR 0
#define J_HOME_DIR 0
#define K_HOME_DIR 0
// #define U_HOME_DIR -1
// #define V_HOME_DIR -1
// #define W_HOME_DIR -1

// @section geometry

// 可打印区域的大小
#define X_BED_SIZE 433
#define Y_BED_SIZE 487

// 归位后的行程限制（直线=mm，旋转=°），对应于
// 限位开关位置。
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
// #define U_MIN_POS 0
// #define U_MAX_POS 50
// #define V_MIN_POS 0
// #define V_MAX_POS 50
// #define W_MIN_POS 0
// #define W_MAX_POS 50

/**
 * 软件限位开关
 *
 * - 防止移动超出设定的机器边界。
 * - 如有需要，可以单独禁用各个轴。
 * - X 和 Y 仅适用于笛卡尔机型。
 * - 使用 'M211' 开启/关闭软件限位开关或报告当前状态
 */

// 最小软件限位开关将运动限制在最小坐标边界内
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

// 最大软件限位开关将运动限制在最大坐标边界内
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
// #define SOFT_ENDSTOPS_MENU_ITEM  // 在 LCD 上启用/禁用软件限位
// 开关
#endif

/**
 * 耗材断料传感器
 * 使用机械式或光电式限位开关检测耗材是否存在。
 *
 * 重要：只有当 Marlin 知道正在打印任务时，断料才会触发。
 * Marlin 在以下情况下知道正在打印任务：
 *  1. 使用 M24 从介质启动打印任务。
 *  2. 使用 M75 启动了打印任务计时器。
 *  3. 加热器已开启且启用了 PRINTJOB_TIMER_AUTOSTART。
 *
 * 基于 RAMPS 的主板使用 SERVO3_PIN 作为第一个断料传感器。
 * 其他主板可能需要定义 FIL_RUNOUT_PIN、FIL_RUNOUT2_PIN 等。
 */
// #define FILAMENT_RUNOUT_SENSOR
#if ENABLED(FILAMENT_RUNOUT_SENSOR)
#define FIL_RUNOUT_ENABLED_DEFAULT                                             \
  true // 启动时启用传感器。可用 M412 后接 M500 覆盖。
#define NUM_RUNOUT_SENSORS                                                     \
  1 // 传感器数量，每个挤出机最多一个。为每一个
    // 定义一个 FIL_RUNOUT#_PIN。

#define FIL_RUNOUT_STATE                                                       \
  LOW                     // 表示耗材不存在的引脚状态。
#define FIL_RUNOUT_PULLUP // 为断料检测引脚使用内部上拉。
// #define FIL_RUNOUT_PULLDOWN           // 为耗材断料检测引脚使用内部
//  下拉。
// #define WATCH_ALL_RUNOUT_SENSORS      // 执行断料处理脚本
// 在任意传感器触发时执行，而不只是当前活动的挤出机。
//  对于 MIXING_EXTRUDER 会自动启用。

// 如果各断料传感器不同，可分别覆盖
// #define FIL_RUNOUT1_STATE LOW
// #define FIL_RUNOUT1_PULLUP
// #define FIL_RUNOUT1_PULLDOWN

// #define FIL_RUNOUT2_STATE LOW
// #define FIL_RUNOUT2_PULLUP
// #define FIL_RUNOUT2_PULLDOWN

// #define FIL_RUNOUT3_STATE LOW
// #define FIL_RUNOUT3_PULLUP
// #define FIL_RUNOUT3_PULLDOWN

// #define FIL_RUNOUT4_STATE LOW
// #define FIL_RUNOUT4_PULLUP
// #define FIL_RUNOUT4_PULLDOWN

// #define FIL_RUNOUT5_STATE LOW
// #define FIL_RUNOUT5_PULLUP
// #define FIL_RUNOUT5_PULLDOWN

// #define FIL_RUNOUT6_STATE LOW
// #define FIL_RUNOUT6_PULLUP
// #define FIL_RUNOUT6_PULLDOWN

// #define FIL_RUNOUT7_STATE LOW
// #define FIL_RUNOUT7_PULLUP
// #define FIL_RUNOUT7_PULLDOWN

// #define FIL_RUNOUT8_STATE LOW
// #define FIL_RUNOUT8_PULLUP
// #define FIL_RUNOUT8_PULLDOWN

// 耗材断料时执行的命令。
// 使用多个断料传感器时，可在命令中用 %c 占位符表示当前工具
// （例如 "M600 T%c"）。注意：在 'M412 H1' 之后由主机处理耗材
// 断料，此脚本不再适用。
#define FILAMENT_RUNOUT_SCRIPT "M600"

// 检测到断料后，继续打印该长度的耗材
// 然后再执行断料脚本。适用于安装在送料管末端的
// 传感器。每个传感器需要 4 字节 SRAM，另有 4 字节额外开销。
// #define FILAMENT_RUNOUT_DISTANCE_MM 25

#ifdef FILAMENT_RUNOUT_DISTANCE_MM
// 启用此选项可使用编码盘，在耗材移动时切换断料检测引脚。
// （请确保 FILAMENT_RUNOUT_DISTANCE_MM 设置得
// 足够大，以避免误触发。）
// #define FILAMENT_MOTION_SENSOR

#if ENABLED(FILAMENT_MOTION_SENSOR)
// #define FILAMENT_SWITCH_AND_MOTION
#if ENABLED(FILAMENT_SWITCH_AND_MOTION)
#define NUM_MOTION_SENSORS                                                     \
  1 // 传感器数量，每个挤出机最多一个。为每一个
    // 定义一个 FIL_MOTION#_PIN。
// #define FIL_MOTION1_PIN    -1

// 如果各运动传感器不同，可分别覆盖
// #define FIL_MOTION1_STATE LOW
// #define FIL_MOTION1_PULLUP
// #define FIL_MOTION1_PULLDOWN

// #define FIL_MOTION2_STATE LOW
// #define FIL_MOTION2_PULLUP
// #define FIL_MOTION2_PULLDOWN

// #define FIL_MOTION3_STATE LOW
// #define FIL_MOTION3_PULLUP
// #define FIL_MOTION3_PULLDOWN

// #define FIL_MOTION4_STATE LOW
// #define FIL_MOTION4_PULLUP
// #define FIL_MOTION4_PULLDOWN

// #define FIL_MOTION5_STATE LOW
// #define FIL_MOTION5_PULLUP
// #define FIL_MOTION5_PULLDOWN

// #define FIL_MOTION6_STATE LOW
// #define FIL_MOTION6_PULLUP
// #define FIL_MOTION6_PULLDOWN

// #define FIL_MOTION7_STATE LOW
// #define FIL_MOTION7_PULLUP
// #define FIL_MOTION7_PULLDOWN

// #define FIL_MOTION8_STATE LOW
// #define FIL_MOTION8_PULLUP
// #define FIL_MOTION8_PULLDOWN
#endif
#endif
#endif
#endif

//===========================================================================
//=============================== 热床调平 ==============================
//===========================================================================
// @section calibrate

/**
 * 从下面的选项中选择一个以启用 G29 热床调平。G29 的参数
 * 和行为会随你的选择而改变。
 *
 *  如果使用探针进行 Z 轴归位，请同时启用 Z_SAFE_HOMING！
 *
 * - AUTO_BED_LEVELING_3POINT
 *   在热床上探测 3 个任意点（不共线）
 *   你需要指定全部 3 个点的 XY 坐标。
 *   结果是一个倾斜的平面。适合平整的热床。
 *
 * - AUTO_BED_LEVELING_LINEAR
 *   以网格方式探测多个点。
 *   你需要指定矩形范围和采样点密度。
 *   结果是一个倾斜的平面。适合平整的热床。
 *
 * - AUTO_BED_LEVELING_BILINEAR
 *   以网格方式探测多个点。
 *   你需要指定矩形范围和采样点密度。
 *   结果是一个网格，适合较大或不平整的热床。
 *
 * - AUTO_BED_LEVELING_UBL（统一热床调平）
 *   一套综合性的热床调平系统，结合了其他系统的
 *   特点与优势。UBL 还集成了网格生成、网格
 *   验证和网格编辑系统。
 *
 * - MESH_BED_LEVELING
 *   手动探测网格
 *   结果是一个网格，适合较大或不平整的热床。（参见 BILINEAR。）
 *   对于没有探针的机器，网格调平提供了一种分步调平的方法，
 * 你可以手动调整每个网格点的 Z 高度。配有 LCD 控制器时，
 * 该流程会一步步引导你。
 */
// #define AUTO_BED_LEVELING_3POINT
// #define AUTO_BED_LEVELING_LINEAR
// #define AUTO_BED_LEVELING_BILINEAR
// #define AUTO_BED_LEVELING_UBL
// #define MESH_BED_LEVELING

/**
 * 通常 G28 完成后调平处于禁用状态。启用以下选项之一
 * 可以恢复之前的调平状态，或在 G28 之后立即
 * 始终启用调平。
 */
// #define RESTORE_LEVELING_AFTER_G28
// #define ENABLE_LEVELING_AFTER_G28

/**
 * 自动调平需要预热
 */
// #define PREHEAT_BEFORE_LEVELING
#if ENABLED(PREHEAT_BEFORE_LEVELING)
#define LEVELING_NOZZLE_TEMP 120 // (°C) 目前仅适用于 E0
#define LEVELING_BED_TEMP 50
#endif

/**
 * 热床距离传感器
 *
 * 以 0.01mm 的精度测量热床到喷嘴的距离。
 * 有关此传感器的更多信息，请参见
 * https://github.com/markniu/Bed_Distance_sensor ，它使用 I2C 接口，因此需要
 * I2C 库 markyue/Panda_SoftMasterI2C。
 */
// #define BD_SENSOR

/**
 * 启用 G28、G29、M48 等命令的详细日志。
 * 使用命令 'M111 S32' 开启。
 * 注意：会占用大量 PROGMEM！
 */
// #define DEBUG_LEVELING_FEATURE

#if ANY(MESH_BED_LEVELING, AUTO_BED_LEVELING_UBL, PROBE_MANUALLY)
// 设置手动调整的起始高度
#define MANUAL_PROBE_START_Z                                                   \
  0.2 // (mm) 注释掉此项可使用上次测得的高度
#endif

#if ANY(MESH_BED_LEVELING, AUTO_BED_LEVELING_BILINEAR, AUTO_BED_LEVELING_UBL)
/**
 * 逐渐减小调平修正量，直到达到设定的高度，
 * 此时运动将与机器的 XY 平面保持平行。
 * 高度可以用 M420 Z<height> 设置
 */
#define ENABLE_LEVELING_FADE_HEIGHT
#if ENABLED(ENABLE_LEVELING_FADE_HEIGHT)
#define DEFAULT_LEVELING_FADE_HEIGHT 10.0 // (mm) 默认淡出高度。
#endif

/**
 * 添加在规划层级应用于所有移动的 Z 偏移 (M424 Z)。
 * 该 Z 偏移会在 G29 时自动设置为中间值。
 */
// #define GLOBAL_MESH_Z_OFFSET

/**
 * 对于笛卡尔机型，不要在网格边界处分割移动，
 * 而是像 Delta 一样把移动拆成短小的分段。这样比从边到边的直线移动
 * 更贴合热床的轮廓。
 */
#define SEGMENT_LEVELED_MOVES
#define LEVELED_SEGMENT_LENGTH                                                 \
  5.0 // (mm) 所有分段的长度（最后一段除外）

/**
 * 启用 G26 网格验证图案工具。
 */
// #define G26_MESH_VALIDATION
#if ENABLED(G26_MESH_VALIDATION)
#define MESH_TEST_NOZZLE_SIZE 0.4  // (mm) 主喷嘴直径。
#define MESH_TEST_LAYER_HEIGHT 0.2 // (mm) G26 的默认层高。
#define MESH_TEST_HOTEND_TEMP 205  // (°C) G26 的默认喷嘴温度。
#define MESH_TEST_BED_TEMP 60      // (°C) G26 的默认热床温度。
#define G26_XY_FEEDRATE 20         // (mm/s) G26 XY 移动的进给速度。
#define G26_XY_FEEDRATE_TRAVEL 100 // (mm/s) G26 XY 空移的进给速度。
#define G26_RETRACT_MULTIPLIER                                                 \
  1.0 // G26 Q（回抽）默认为网格测试元素之间使用。
#endif

#endif

#if EITHER(AUTO_BED_LEVELING_LINEAR, AUTO_BED_LEVELING_BILINEAR)

// 设置每个方向的网格点数量。
#define GRID_MAX_POINTS_X 3
#define GRID_MAX_POINTS_Y GRID_MAX_POINTS_X

// 沿 Y 轴探测，每列结束后 X 轴前移
// #define PROBE_Y_FIRST

#if ENABLED(AUTO_BED_LEVELING_BILINEAR)

// 在探测网格之外，是否延续推算出的倾斜？
// 默认保持最近边缘的高度。
// #define EXTRAPOLATE_BEYOND_GRID

//
// 使用 Catmull-Rom 方法对网格进行细分。
// 生成中间点以得到更精细的网格。
//
// #define ABL_BILINEAR_SUBDIVISION
#if ENABLED(ABL_BILINEAR_SUBDIVISION)
// 探测点之间的细分数
#define BILINEAR_SUBDIVISIONS 3
#endif

#endif

#elif ENABLED(AUTO_BED_LEVELING_UBL)

//===========================================================================
//========================= 统一热床调平 ============================
//===========================================================================

// #define MESH_EDIT_GFX_OVERLAY   // 编辑网格时显示图形
// 叠加层

#define MESH_INSET 1 // 将网格边界设为热床的内缩区域
#define GRID_MAX_POINTS_X                                                      \
  10 // 每个轴不要超过 15 个点，受实现所限。
#define GRID_MAX_POINTS_Y GRID_MAX_POINTS_X

// #define UBL_HILBERT_CURVE       // 探测多个点时使用希尔伯特分布以减少移动
// 距离

// #define UBL_TILT_ON_MESH_POINTS         // 使用最近的网格点配合 G29 J
//  以获得更好的 Z 基准
// #define UBL_TILT_ON_MESH_POINTS_3POINT  // 使用最近的
// 网格点配合 G29 J0（3 点）

#define UBL_MESH_EDIT_MOVES_Z   // 高级用户希望编辑网格时
                                // 喷嘴不移动
#define UBL_SAVE_ACTIVE_ON_M500 // 在 M500 时把当前活动的网格保存到当前
                                // 槽位中

// #define UBL_Z_RAISE_WHEN_OFF_MESH 2.5 // 当喷嘴离开网格时，
// 使用此值
//  作为 Z 高度修正值。

// #define UBL_MESH_WIZARD         // 连续运行若干命令以获得完整的
// 网格

/**
 * 不允许在障碍物所在位置进行探测。
 */
// #define AVOID_OBSTACLES
#if ENABLED(AVOID_OBSTACLES)
#define CLIP_W                                                                 \
  23 // Bed clip width, should be padded a few mm over its physical size
#define CLIP_H                                                                 \
  14 // Bed clip height, should be padded a few mm over its physical size

// 障碍物矩形定义为 { X1, Y1, X2, Y2 }
#define OBSTACLE1                                                              \
  {(X_BED_SIZE) / 4 - (CLIP_W) / 2, 0, (X_BED_SIZE) / 4 + (CLIP_W) / 2, CLIP_H}
#define OBSTACLE2                                                              \
  {(X_BED_SIZE) * 3 / 4 - (CLIP_W) / 2, 0,                                     \
   (X_BED_SIZE) * 3 / 4 + (CLIP_W) / 2, CLIP_H}
#define OBSTACLE3                                                              \
  {(X_BED_SIZE) / 4 - (CLIP_W) / 2, (Y_BED_SIZE) - (CLIP_H),                   \
   (X_BED_SIZE) / 4 + (CLIP_W) / 2, Y_BED_SIZE}
#define OBSTACLE4                                                              \
  {(X_BED_SIZE) * 3 / 4 - (CLIP_W) / 2, (Y_BED_SIZE) - (CLIP_H),               \
   (X_BED_SIZE) * 3 / 4 + (CLIP_W) / 2, Y_BED_SIZE}

// G29 J 要求探测网格内缩。没有问题，因为它
// 只用于为网格本身计算线性变换。
#define G29J_MESH_TILT_MARGIN ((CLIP_H) + 1)
#endif

#elif ENABLED(MESH_BED_LEVELING)

//===========================================================================
//=================================== 网格 ==================================
//===========================================================================

#define MESH_INSET 10 // 将网格边界设为热床的内缩区域
#define GRID_MAX_POINTS_X                                                      \
  3 // 每个轴不要超过 7 个点，代码实现有此限制。
#define GRID_MAX_POINTS_Y GRID_MAX_POINTS_X

// #define MESH_G28_REST_ORIGIN // 所有轴归位后（'G28' 或 'G28 XYZ'）
// 将 Z 停在 Z_MIN_POS

#endif // BED_LEVELING

/**
 * 为 ABL 或 MBL 添加热床调平子菜单。
 * 若启用手动探测，则包含引导流程。
 */
// #define LCD_BED_LEVELING

#if ENABLED(LCD_BED_LEVELING)
#define MESH_EDIT_Z_STEP 0.025 // (mm) 手动探测 Z 轴时的步进距离。
#define LCD_PROBE_Z_RANGE                                                      \
  4 // (mm) 以 Z_MIN_POS 为中心的 Z 轴范围，用于在 LCD 上调整 Z
// #define MESH_EDIT_MENU        // 添加编辑网格点的菜单
#endif

// 添加菜单项，用于在热床各角之间移动以手动调整热床
// #define LCD_BED_TRAMMING

#if ENABLED(LCD_BED_TRAMMING)
#define BED_TRAMMING_INSET_LFRB                                                \
  {30, 30, 30, 30}              // (mm) 左、前、右、后内缩量
#define BED_TRAMMING_HEIGHT 0.0 // (mm) 校平（用水平螺丝校准）时喷嘴的 Z 高度
#define BED_TRAMMING_Z_HOP                                                     \
  4.0 // (mm) 校平（用水平螺丝校准）各点之间喷嘴的 Z 高度
// #define BED_TRAMMING_INCLUDE_CENTER       // 在最后一个角之后移动到
//  中心
// #define BED_TRAMMING_USE_PROBE
#if ENABLED(BED_TRAMMING_USE_PROBE)
#define BED_TRAMMING_PROBE_TOLERANCE 0.1 // (mm)
#define BED_TRAMMING_VERIFY_RAISED       // 调整后触发探针，
                                         // 重新探测以验证
// #define BED_TRAMMING_AUDIO_FEEDBACK
#endif

/**
 * 角点调平顺序
 *
 * 设置 2 个或 4 个点。给出 2 个点时，第 3 个点为
 * 对边的中点。
 *
 *  LF  左前      RF  右前
 *  LB  左后      RB  右后
 *
 * 示例：
 *
 *      默认          {LF,RB,LB,RF}         {LF,RF}           {LB,LF}
 *  LB --------- RB   LB --------- RB    LB --------- RB   LB --------- RB
 *  |  4       3  |   | 3         2 |    |     <3>     |   | 1           |
 *  |             |   |             |    |             |   |          <3>|
 *  |  1       2  |   | 1         4 |    | 1         2 |   | 2           |
 *  LF --------- RF   LF --------- RF    LF --------- RF   LF --------- RF
 */
#define BED_TRAMMING_LEVELING_ORDER {LF, RF, RB, LB}
#endif

/**
 * G29 探测结束时执行的命令。
 * 可用于回抽或把 Z 探针移开。
 */
// #define Z_PROBE_END_SCRIPT "G1 Z10 F12000\nG1 X15 Y330\nG1 Z0.5\nG1 Z10"

// @section homing

// 热床中心位于 (X=0, Y=0)
// #define BED_CENTER_AT_0_0

// 手动设置归位位置。保持未定义则使用自动设置。
// 对 DELTA 而言，这是笛卡尔打印空间的顶部中心。
// #define MANUAL_X_HOME_POS 0
// #define MANUAL_Y_HOME_POS 0
// #define MANUAL_Z_HOME_POS 0
// #define MANUAL_I_HOME_POS 0
// #define MANUAL_J_HOME_POS 0
// #define MANUAL_K_HOME_POS 0
// #define MANUAL_U_HOME_POS 0
// #define MANUAL_V_HOME_POS 0
// #define MANUAL_W_HOME_POS 0

/**
 * 使用“Z 安全归位”可避免在 Z 探针位于热床区域之外时归位。
 *
 * - 在 Z 归位前将 Z 探针（或喷嘴）移动到指定的 XY 点。
 * - 仅当 XY 位置已知且可信时才允许 Z 归位。
 * - 如果步进电机驱动进入睡眠，Z 归位前可能需要再次进行 XY 归位。
 */
#define Z_SAFE_HOMING

#if ENABLED(Z_SAFE_HOMING)
#define Z_SAFE_HOMING_X_POINT 0 // Z 归位使用的 X 点
#define Z_SAFE_HOMING_Y_POINT 0 // Z 归位使用的 Y 点
// #define Z_SAFE_HOMING_POINT_ABSOLUTE  // Z 归位位置忽略
// 归位偏移（M206）
#endif

// 归位速度（直线=mm/min，旋转=°/min）
#define HOMING_FEEDRATE_MM_M                                                   \
  {(150 * 60), (150 * 60), (150 * 60), (50 * 60), (50 * 60)}

// 校验归位移动时限位开关是否被触发
#define VALIDATE_HOMING_ENDSTOPS

// @section calibrate

/**
 * 热床倾斜补偿
 *
 * 此功能用于修正 XYZ 轴之间的错位。
 *
 * 按以下步骤测量 XY 平面内的热床倾斜：
 *  1. 打印一个测试方块（例如 https://www.thingiverse.com/thing:2563185）
 *  2. 对于 XY_DIAG_AC，测量 A 到 C 的对角线
 *  3. 对于 XY_DIAG_BD，测量 B 到 D 的对角线
 *  4. 对于 XY_SIDE_AD，测量 A 到 D 的边长
 *
 * Marlin 会根据这些测量值自动计算倾斜系数。
 * 倾斜系数也可以手动计算并设置：
 *
 *  - 计算 AB     : SQRT(2*AC*AC+2*BD*BD-4*AD*AD)/2
 *  - XY_SKEW_FACTOR : TAN(PI/2-ACOS((AC*AC-AB*AB-AD*AD)/(2*AB*AD)))
 *
 * 如有需要，可对 XZ 和 YZ 采用相同的流程。
 * 可参考以下示意图：
 *
 *    Y                     Z                     Z
 *    ^     B-------C       ^     B-------C       ^     B-------C
 *    |    /       /        |    /       /        |    /       /
 *    |   /       /         |   /       /         |   /       /
 *    |  A-------D          |  A-------D          |  A-------D
 *    +-------------->X     +-------------->X     +-------------->Y
 *     XY_SKEW_FACTOR        XZ_SKEW_FACTOR        YZ_SKEW_FACTOR
 */
// #define SKEW_CORRECTION

#if ENABLED(SKEW_CORRECTION)
// 在此输入所有长度测量值：
#define XY_DIAG_AC 282.8427124746
#define XY_DIAG_BD 282.8427124746
#define XY_SIDE_AD 200

// 或者直接设置 XY 倾斜系数：
// #define XY_SKEW_FACTOR 0.0

// #define SKEW_CORRECTION_FOR_Z
#if ENABLED(SKEW_CORRECTION_FOR_Z)
#define XZ_DIAG_AC 282.8427124746
#define XZ_DIAG_BD 282.8427124746
#define YZ_DIAG_AC 282.8427124746
#define YZ_DIAG_BD 282.8427124746
#define YZ_SIDE_AD 200

// 或者直接设置 Z 倾斜系数：
// #define XZ_SKEW_FACTOR 0.0
// #define YZ_SKEW_FACTOR 0.0
#endif

// 启用此选项以便用 M852 在运行时设置倾斜
// #define SKEW_CORRECTION_GCODE
#endif

//=============================================================================
//============================= 附加功能 ===========================
//=============================================================================

// @section eeprom

/**
 * EEPROM
 *
 * 掉电后仍能保留可配置设置的持久化存储。
 *
 *   M500 - 将设置保存到 EEPROM。
 *   M501 - 从 EEPROM 读取设置。（即丢弃未保存的更改）
 *   M502 - 将设置恢复为“出厂”默认值。（随后用 M500 初始化
 * EEPROM。）
 */
// #define EEPROM_SETTINGS     // 通过 M500 和 M501 实现的持久化存储
// #define DISABLE_M503        // 可节省约 2700 字节 flash。发布版请
// 禁用！
#define EEPROM_CHITCHAT    // 对 EEPROM 命令给出反馈。禁用以节省
                           // PROGMEM。
#define EEPROM_BOOT_SILENT // 保持 M503 静默，仅在首次加载时
                           // 报错
#if ENABLED(EEPROM_SETTINGS)
// #define EEPROM_AUTO_INIT  // 出错时自动初始化 EEPROM。
// #define EEPROM_INIT_NOW   // 全新编译后首次启动时初始化 EEPROM。
#endif

// @section host

//
// 主机保活
//
// 启用后，当 Marlin 无法接受命令时，会每隔几秒向主机
// 发送一次忙状态消息。
//
#define HOST_KEEPALIVE_FEATURE // 如果你的主机不希望收到保活消息，请
                               // 禁用此项
#define DEFAULT_KEEPALIVE_INTERVAL                                             \
  2 // "busy" 消息之间的间隔秒数。用 M113 设置。
#define BUSY_WHILE_HEATING // 有些主机即使在加热期间也要求收到 "busy"
                           // 消息

// @section units

//
// G20/G21 英寸模式支持
//
// #define INCH_MODE_SUPPORT

//
// M149 设置温度单位支持
//
// #define TEMPERATURE_UNITS_SUPPORT

// @section temperature

//
// 预热常量 - 无需修改即可支持最多 10 组
//
#define PREHEAT_1_LABEL "PLA"
#define PREHEAT_1_TEMP_HOTEND 180
#define PREHEAT_1_TEMP_BED 70
#define PREHEAT_1_TEMP_CHAMBER 35
#define PREHEAT_1_FAN_SPEED 0 // 取值范围 0 到 255

#define PREHEAT_2_LABEL "ABS"
#define PREHEAT_2_TEMP_HOTEND 240
#define PREHEAT_2_TEMP_BED 110
#define PREHEAT_2_TEMP_CHAMBER 35
#define PREHEAT_2_FAN_SPEED 0 // 取值范围 0 到 255

// @section motion

/**
 * 喷嘴停放
 *
 * 空闲时或执行 G27 时，将喷嘴停放到指定的 XYZ 位置。
 *
 * “P”参数控制对 Z 轴施加的动作：
 *
 *    P0  （默认）如果 Z 低于停放 Z，则抬起喷嘴。
 *    P1  始终将喷嘴抬升到停放 Z 高度。
 *    P2  将喷嘴抬升停放 Z 的量，并以 Z_MAX_POS 为上限。
 */
// #define NOZZLE_PARK_FEATURE

#if ENABLED(NOZZLE_PARK_FEATURE)
// 按 { X, Y, Z_raise } 指定停放位置
#define NOZZLE_PARK_POINT {(X_MIN_POS + 10), (Y_MAX_POS - 10), 20}
#define NOZZLE_PARK_MOVE                                                       \
  0 // 停放移动：0 = XY 移动，1 = 仅 X，2 = 仅 Y，3 = 先 X 后 Y，4 = 先 Y
    // 后 X
#define NOZZLE_PARK_Z_RAISE_MIN                                                \
  2 // (mm) 始终至少将 Z 抬升此距离
#define NOZZLE_PARK_XY_FEEDRATE                                                \
  100 // (mm/s) X 和 Y 轴的进给速度（delta 的 Z 轴也用此值）
#define NOZZLE_PARK_Z_FEEDRATE                                                 \
  5 // (mm/s) Z 轴的进给速度（delta 打印机不使用）
#endif

/**
 * 喷嘴清洁功能
 *
 * 增加 G12 命令，用于执行喷嘴清洁流程。
 *
 * 参数：
 *   P  图案
 *   S  行程数 / 重复次数
 *   T  三角形数量（仅 P1）
 *
 * 图案：
 *   P0  直线（默认）。该流程需要在热床的固定位置放置海绵类
 *       材料。“S”指定起点与终点之间的行程数（即往返
 *       次数）。
 *
 *   P1  在 (X0, Y0) 与 (X1, Y1) 之间走之字形，“T”指定要执行的
 *       之字形三角数量。“S”定义行程次数。
 *       之字形在较窄的那个维度上完成。
 *       例如，“G12 P1 S1 T3”将执行：
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
 *   P2  以 NOZZLE_CLEAN_CIRCLE_MIDDLE 为圆心的圆形图案。
 *       “R”指定半径。“S”指定行程次数。
 *       开始之前，喷嘴会移动到 NOZZLE_CLEAN_START_POINT。
 *
 *   注意事项：结束时的 Z 应与开始时的 Z 相同。
 */
// #define NOZZLE_CLEAN_FEATURE

#if ENABLED(NOZZLE_CLEAN_FEATURE)
// 图案默认重复次数
#define NOZZLE_CLEAN_STROKES 12

// 三角形默认数量
#define NOZZLE_CLEAN_TRIANGLES 3

// 按 { { X, Y, Z }, { X, Y, Z } } 指定每个工具的位置
// 双热端系统可使用 { {  -20, (Y_BED_SIZE / 2), (Z_MIN_POS + 1) },  {
// 420, (Y_BED_SIZE / 2), (Z_MIN_POS + 1) }}
#define NOZZLE_CLEAN_START_POINT                                               \
  {                                                                            \
    {                                                                          \
      30, 30, (Z_MIN_POS + 1)                                                  \
    }                                                                          \
  }
#define NOZZLE_CLEAN_END_POINT                                                 \
  {                                                                            \
    {                                                                          \
      100, 60, (Z_MIN_POS + 1)                                                 \
    }                                                                          \
  }

// 圆形图案半径
#define NOZZLE_CLEAN_CIRCLE_RADIUS 6.5
// 圆形图案的分段数
#define NOZZLE_CLEAN_CIRCLE_FN 10
// 圆心点
#define NOZZLE_CLEAN_CIRCLE_MIDDLE NOZZLE_CLEAN_START_POINT

// 清洁后把喷嘴移回初始位置
#define NOZZLE_CLEAN_GOBACK

// 适用于始终处于龙门高度（因此没有 Z 移动）的排料/清洁站
// #define NOZZLE_CLEAN_NO_Z

// 适用于安装在 X 轴上的排料/清洁站
// #define NOZZLE_CLEAN_NO_Y

// 清洁所需的热端最低温度
#define NOZZLE_CLEAN_MIN_TEMP 170
// #define NOZZLE_CLEAN_HEATUP       // 加热喷嘴而不是跳过
// 擦拭

// 显式擦拭 G 代码脚本适用于不带参数的 G12。
// #define WIPE_SEQUENCE_COMMANDS "G1 X-17 Y25 Z10 F4000\nG1 Z1\nM114\nG1 X-17 Y25\nG1 X-17 Y95\nG1 X-17 Y25\nG1 X-17 Y95\nG1 X-17 Y25\nG1 X-17 Y95\nG1 X-17 Y25\nG1 X-17 Y95\nG1 X-17 Y25\nG1 X-17 Y95\nG1 X-17 Y25\nG1 X-17 Y95\nG1 Z15\nM400\nG0 X-10.0 Y-9.0"

#endif

// @section host

/**
 * 打印任务计时器
 *
 * 在 M104/M109/M140/M190/M141/M191 时自动启动和停止打印任务计时器。
 * 只有当热床/腔体的目标温度低于 BED_MINTEMP/CHAMBER_MINTEMP 时，
 * 打印任务计时器才会被停止。
 *
 *   M104 (热端, 不等待) - 高温 = 无，         低温 = 停止计时
 *   M109 (热端, 等待)   - 高温 = 启动计时，   低温 = 停止计时
 *   M140 (热床, 不等待) - 高温 = 无，         低温 = 停止计时
 *   M190 (热床, 等待)   - 高温 = 启动计时，   低温 = 无
 *   M141 (腔体, 不等待) - 高温 = 无，         低温 = 停止计时
 *   M191 (腔体, 等待)   - 高温 = 启动计时，   低温 = 无
 *
 * 对 M104/M109，高温指高于 EXTRUDE_MINTEMP / 2 的温度。
 * 对 M140/M190，高温指高于 BED_MINTEMP 的温度。
 * 对 M141/M191，高温指高于 CHAMBER_MINTEMP 的温度。
 *
 * 也可以用以下命令控制计时器：
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
 * 统计如下数据：
 *
 *  - 打印任务总数
 *  - 成功打印任务总数
 *  - 失败打印任务总数
 *  - 累计打印时间
 *
 * 用 M78 查看当前统计。
 */
// #define PRINTCOUNTER
#if ENABLED(PRINTCOUNTER)
#define PRINTCOUNTER_SAVE_INTERVAL                                             \
  60 // (minutes) 打印过程中的 EEPROM 保存间隔。值为 0 时将在
     // 打印结束时保存统计数据。
#endif

// @section security

/**
 * 密码
 *
 * 为打印机设置一个数字密码，可在以下情况要求输入：
 *
 *  - 打印机启动时
 *  - 打开“从存储介质打印”菜单时
 *  - SD 打印完成或中止时
 *
 * 可使用以下 G 代码：
 *
 *  M510 - 锁定打印机。除 M511 外屏蔽所有命令。
 *  M511 - 解锁打印机。
 *  M512 - 设置、更改和清除密码。
 *
 * 如果忘记密码而被锁在门外，需要在禁用该功能的情况下重新刷写
 * 固件、重置 EEPROM，然后（可选）在启用该功能的情况下
 * 再次刷写固件。
 */
// #define PASSWORD_FEATURE
#if ENABLED(PASSWORD_FEATURE)
#define PASSWORD_LENGTH 4 // (#) 数字位数 (1-9)。推荐 3 或 4
#define PASSWORD_ON_STARTUP
#define PASSWORD_UNLOCK_GCODE // 用 M511 P<password> 命令解锁。
                              // 禁用此项可防止暴力破解。
#define PASSWORD_CHANGE_GCODE // 用 M512 P<old> S<new> 更改密码。
// #define PASSWORD_ON_SD_PRINT_MENU       // 这并不能阻止 G 代码
//  执行
// #define PASSWORD_AFTER_SD_PRINT_END
// #define PASSWORD_AFTER_SD_PRINT_ABORT
// #include "Configuration_Secure.h"       // 含有 PASSWORD_DEFAULT_VALUE 的外部文件
#endif

//=============================================================================
//============================= LCD 和 SD 支持 ============================
//=============================================================================

// @section interface

/**
 * LCD 语言
 *
 * 选择 LCD 上显示的语言。可用语言如下：
 *
 *   en, an, bg, ca, cz, da, de, el, el_CY, es, eu, fi, fr, gl, hr, hu, it,
 *   jp_kana, ko_KR, nl, pl, pt, pt_br, ro, ru, sk, sv, tr, uk, vi, zh_CN, zh_TW
 *
 * :{ 'en':'English', 'an':'Aragonese', 'bg':'Bulgarian', 'ca':'Catalan', 'cz':'Czech', 'da':'Danish', 'de':'German', 'el':'Greek (Greece)', 'el_CY':'Greek (Cyprus)', 'es':'Spanish', 'eu':'Basque-Euskera', 'fi':'Finnish', 'fr':'French', 'gl':'Galician', 'hr':'Croatian', 'hu':'Hungarian', 'it':'Italian', 'jp_kana':'Japanese', 'ko_KR':'Korean (South Korea)', 'nl':'Dutch', 'pl':'Polish', 'pt':'Portuguese', 'pt_br':'Portuguese (Brazilian)', 'ro':'Romanian', 'ru':'Russian', 'sk':'Slovak', 'sv':'Swedish', 'tr':'Turkish', 'uk':'Ukrainian', 'vi':'Vietnamese', 'zh_CN':'Chinese (Simplified)', 'zh_TW':'Chinese (Traditional)' }
 */
#define LCD_LANGUAGE zh_CN

/**
 * LCD 字符集
 *
 * 注意：此选项不适用于图形显示屏。
 *
 * 所有字符型 LCD 都提供 ASCII 以及以下某一种
 * 语言扩展：
 *
 *  - JAPANESE ... 最常见
 *  - WESTERN  ... 带更多带音标字符
 *  - CYRILLIC ... 用于俄语
 *
 * 要确定你的控制器上安装的是哪种语言扩展：
 *
 *  - 将 LCD_LANGUAGE 设为 'test' 编译并上传
 *  - 点击控制器以查看 LCD 菜单
 *  - LCD 将显示日文、西文或西里尔文
 *
 * 参见 https://marlinfw.org/docs/development/lcd_language.html
 *
 * :['JAPANESE', 'WESTERN', 'CYRILLIC']
 */
#define DISPLAY_CHARSET_HD44780 JAPANESE

/**
 * 信息屏样式 (0:Classic, 1:Průša)
 *
 * :[0:'Classic', 1:'Průša']
 */
#define LCD_INFO_SCREEN_STYLE 0

/**
 * SD 卡
 *
 * 默认禁用 SD 卡支持。如果你的控制器有 SD 卡槽，
 * 必须取消下面这个选项的注释，否则不会起作用。
 */
// #define SDSUPPORT

/**
 * SD 卡：启用 CRC
 *
 * 对 SD 通信使用 CRC 校验和重试。
 */
// #define SD_CHECK_AND_RETRY

/**
 * LCD 菜单项
 *
 * 禁用所有菜单、只显示状态屏，或者
 * 只移除一些多余的菜单项以节省空间。
 */
// #define NO_LCD_MENUS
// #define SLIM_LCD_MENUS

//
// 编码器设置
//
// 此选项覆盖产生一个步进所需的默认编码器脉冲数。
// 高分辨率编码器应增大该值。
//
// #define ENCODER_PULSES_PER_STEP 4

//
// 用此选项覆盖在菜单项之间前后移动所需的
// 步进信号数。
//
// #define ENCODER_STEPS_PER_MENU_ITEM 1

/**
 * 编码器方向选项
 *
 * 先在两个选项都禁用的情况下测试编码器的行为。
 *
 *  值编辑和菜单导航都反了？启用 REVERSE_ENCODER_DIRECTION。
 *  仅菜单导航反了？        启用 REVERSE_MENU_DIRECTION。
 *  仅值编辑反了？          启用两个选项。
 */

//
// 此选项在所有位置反转编码器方向。
//
//  如果顺时针会让数值减小，请启用此选项
//
// #define REVERSE_ENCODER_DIRECTION

//
// 此选项反转浏览 LCD 菜单时的编码器方向。
//
//  如果顺时针通常是向下，这会变成向上。
//  如果顺时针通常是向上，这会变成向下。
//
// #define REVERSE_MENU_DIRECTION

//
// 此选项反转选择屏幕时的编码器方向。
//
//  如果顺时针通常是向左，这会变成向右。
//  如果顺时针通常是向右，这会变成向左。
//
// #define REVERSE_SELECT_DIRECTION

//
// 编码器 EMI 噪声滤波
//
// 此选项增加编码器采样次数，以滤除 EMI 噪声造成的
// 虚假编码器点击。
//
// #define ENCODER_NOISE_FILTER
#if ENABLED(ENCODER_NOISE_FILTER)
#define ENCODER_SAMPLES 10
#endif

//
// 单轴归位
//
// 在 LCD 菜单中添加单轴归位项
// （X 轴归位、Y 轴归位和 Z 轴归位）。
//
// #define INDIVIDUAL_AXIS_HOMING_MENU
// #define INDIVIDUAL_AXIS_HOMING_SUBMENU

//
// 扬声器/蜂鸣器
//
// 如果你有能发声的扬声器，请在此启用。
// 默认 Marlin 假定你有一个固定频率的蜂鸣器。
//
#define SPEAKER

//
// UI 反馈音效的时长和频率。
// 将这两项设为 0 可禁用 LCD 菜单中的声音反馈。
//
// 注意：用以下 G 代码测试音频输出：
//  M300 S<frequency Hz> P<duration ms>
//
// #define LCD_FEEDBACK_FREQUENCY_DURATION_MS 2
// #define LCD_FEEDBACK_FREQUENCY_HZ 5000

//=============================================================================
//======================== LCD / 控制器选择 =========================
//========================   （字符型 LCD）   =========================
//=============================================================================
// @section lcd

//
// RepRapDiscount 智能控制器。
// https://reprap.org/wiki/RepRapDiscount_Smart_Controller
//
// 注意：通常配白色 PCB 出售。
//
// #define REPRAP_DISCOUNT_SMART_CONTROLLER

//
// GT2560 (YHCB2004) LCD 显示屏
//
// 需要 Testato、Koepel 的 softwarewire 库，以及
// Andriy Golovnya 的 LiquidCrystal_AIP31068 库。
//
// #define YHCB2004

//
// 最初的 RADDS LCD 显示屏 + 编码器 + SD 读卡器
// http://doku.radds.org/dokumentation/lcd-display/
//
// #define RADDS_DISPLAY

//
// ULTIMAKER 控制器。
//
// #define ULTIMAKERCONTROLLER

//
// Thingiverse 上的 ULTIPANEL。
//
// #define ULTIPANEL

//
// 来自 T3P3 的 PanelOne（通过 RAMPS 1.4 AUX2/AUX3）
// https://reprap.org/wiki/PanelOne
//
// #define PANEL_ONE

//
// GADGETS3D G3D LCD/SD 控制器
// https://reprap.org/wiki/RAMPS_1.3/1.4_GADGETS3D_Shield_with_Panel
//
// 注意：通常配蓝色 PCB 出售。
//
// #define G3D_PANEL

//
// RigidBot 面板 V1.0
// http://www.inventapart.com/
//
// #define RIGIDBOT_PANEL

//
// Makeboard 3D 打印机配件 3D 打印机迷你显示屏 1602 迷你控制器
// https://www.aliexpress.com/item/32765887917.html
//
// #define MAKEBOARD_MINI_2_LINE_DISPLAY_1602

//
// ANET 和 Tronxy 20x4 控制器
//
// #define ZONESTAR_LCD            // 需要把 ADC_KEYPAD_PIN 分配到
// 一个模拟引脚。
// 已知这种 LCD 容易受到电气干扰，
// 导致显示混乱。按任意按键即可恢复。
// 这是一款带 5 个模拟按键的 LCD2004 显示屏。

//
// 通用 16x2、16x4、20x2 或 20x4 字符型 LCD。
//
// #define ULTRA_LCD

//=============================================================================
//======================== LCD / 控制器选择 =========================
//=====================   （I2C 和移位寄存器 LCD）   =====================
//=============================================================================

//
// 控制器类型：I2C
//
// 注意：这些控制器需要安装 Arduino 的
// LiquidCrystal_I2C 库。更多信息：
// https://github.com/kiyoshigawa/LiquidCrystal_I2C
//

//
// Elefu RA 板控制面板
// https://web.archive.org/web/20140823033947/http://www.elefu.com/index.php?route=product/product&product_id=53
//
// #define RA_CONTROL_PANEL

//
// Sainsmart (YwRobot) LCD 显示屏
//
// 这些需要 F.Malpartida 的 LiquidCrystal_I2C 库
// https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home
//
// #define LCD_SAINSMART_I2C_1602
// #define LCD_SAINSMART_I2C_2004

//
// 通用 LCM1602 LCD 适配板
//
// #define LCM1602

//
// 带状态 LED 的 PANELOLU2 LCD，
// 编码器与按键输入相互独立。
//
// 注意：此控制器需要 Arduino 的 LiquidTWI2 库 v1.2.3 或更高版本。
// 更多信息：https://github.com/lincomatic/LiquidTWI2
//
// 注意：PANELOLU2 的编码器按键输入既可以直接连接到某个
// 引脚（当 BTN_ENC 定义为 != -1 时），也可以通过 I2C 读取（当 BTN_ENC == -1 时）。
//
// #define LCD_I2C_PANELOLU2

//
// 带状态 LED 的 Panucatt VIKI LCD，
// 集成了按键与 L/R/U/D 按钮，编码器输入相互独立。
//
// #define LCD_I2C_VIKI

//
// 控制器类型：移位寄存器面板
//

//
// 来自 https://goo.gl/aJJ4sH 的 2 线无锁存 LCD 移位寄存器
// LCD 配置：https://reprap.org/wiki/SAV_3D_LCD
//
// #define SAV_3DLCD

//
// 使用 74HC4094 实现选通的三线 SR LCD
// https://github.com/mikeshub/SailfishLCD
// 直接使用 Sailfish 的代码
//
// #define FF_INTERFACEBOARD

//
// 带 Marlin UI 的 TFT GLCD 面板
// 面板通过 SPI 或 I2C 接口连接到主板。
// 参见 https://github.com/Serhiy-K/TFTGLCDAdapter
//
// #define TFTGLCD_PANEL_SPI
// #define TFTGLCD_PANEL_I2C

//=============================================================================
//=======================   LCD / 控制器选择  =======================
//=========================      （图形 LCD）      ========================
//=============================================================================

//
// 控制器类型：图形 128x64 (DOGM)
//
// 重要：图形显示需要 U8glib 库！
//            https://github.com/olikraus/U8glib_Arduino
//
// 注意：如果 LCD 无响应，可能需要反接插头。
//

//
// RepRapDiscount 全图形智能控制器
// https://reprap.org/wiki/RepRapDiscount_Full_Graphic_Smart_Controller
//
// #define REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER

//
// K.3D 全图形智能控制器
//
// #define K3D_FULL_GRAPHIC_SMART_CONTROLLER

//
// ReprapWorld 图形 LCD
// https://reprapworld.com/electronics/3d-printer-modules/autonomous-printing/graphical-lcd-screen-v1-0/
//
// #define REPRAPWORLD_GRAPHICAL_LCD

//
// 如果你使用的是 Panucatt Devices
// Viki 2.0 或带图形 LCD 的 mini Viki，请启用其中一项
// https://www.panucatt.com
//
// #define VIKI2
// #define miniVIKI

//
// 标有 WYH L12864 COG 的 Alfawise Ex8 打印机 LCD
//
// #define WYH_L12864

//
// 带图形控制器和 SD 支持的 MakerLab 迷你面板 -
// https://reprap.org/wiki/Mini_panel
//
// #define MINIPANEL

//
// MaKr3d Makr-Panel，带图形控制器和 SD 支持。
// https://reprap.org/wiki/MaKr3d_MaKrPanel
//
// #define MAKRPANEL

//
// Adafruit ST7565 全图形控制器。
// https://github.com/eboston/Adafruit-ST7565-Full-Graphic-Controller/
//
// #define ELB_FULL_GRAPHIC_CONTROLLER

//
// BQ LCD 智能控制器，默认随
// BQ Hephestos 2 和 Witbox 2 一起出货。
//
// #define BQ_LCD_SMART_CONTROLLER

//
// Cartesio UI
// http://mauk.cc/webshop/cartesio-shop/electronics/user-interface
//
// #define CARTESIO_UI

//
// 用于 Melzi Card 的图形 LCD
//
// #define LCD_FOR_MELZI

//
// Ultimaker 2 打印机原装的 Ulticontroller，带 SSD1309 I2C 显示屏和
// 编码器
// https://github.com/Ultimaker/Ultimaker2/tree/master/1249_Ulticontroller_Board_(x1)
//
// #define ULTI_CONTROLLER

//
// 带图形控制器和 SD 支持的 MKS MINI12864
// https://reprap.org/wiki/MKS_MINI_12864
//
// #define MKS_MINI_12864

//
// MKS MINI12864 V3 是 FYSETC_MINI_12864_2_1 的别名。A/B 型。NeoPixel
// RGB 背光。
//
// #define MKS_MINI_12864_V3

//
// 带图形控制器和 SD 支持的 MKS LCD12864A/B。遵循
// MKS_MINI_12864 引脚定义。https://www.aliexpress.com/item/33018110072.html
//
// #define MKS_LCD12864A
// #define MKS_LCD12864B

//
// 带 SD 支持的 MINI12864 图形控制器的 FYSETC 版本
// https://wiki.fysetc.com/Mini12864_Panel/
//
// #define FYSETC_MINI_12864_X_X    // C/D/E/F 型。默认没有可调的
//  RGB 背光
// #define FYSETC_MINI_12864_1_2    // C/D/E/F 型。简单 RGB
//  背光（始终开启）
// #define FYSETC_MINI_12864_2_0    // A/B 型。低调的
//  RGB 背光
// #define FYSETC_MINI_12864_2_1    // A/B 型。NeoPixel RGB
//  背光
// #define FYSETC_GENERIC_12864_1_1 // 更大的显示屏，仅带简易
// ON/OFF 背光。

//
// BigTreeTech Mini 12864 V1.0 是 FYSETC_MINI_12864_2_1 的别名。A/B 型。
// NeoPixel RGB 背光。
//
// #define BTT_MINI_12864_V1

//
// Creality CR-10 原装显示屏
// https://www.aliexpress.com/item/32833148327.html
//
// 它兼容 RAMPS，使用单路 10 针连接器。
// （适用于想更换 Melzi Creality 板，
// 但仍想保留显示屏的 CR-10 用户）
//
// #define CR10_STOCKDISPLAY

//
// Ender-2 原装显示屏，MKS_MINI_12864 的变体
//
// #define ENDER2_STOCKDISPLAY

//
// ANET 与 Tronxy 图形控制器
//
// Anet A6 所用的带旋转编码器的 Anet 128x64 全图形 LCD
// 它是 RepRapDiscount 全图形显示屏的仿制品，但
// 引脚/接线不同（见 pins_ANET_10.h）。请启用其中之一。
//
// #define ANET_FULL_GRAPHICS_LCD
// #define ANET_FULL_GRAPHICS_LCD_ALT_WIRING

//
// 带 SD 的 AZSMZ 12864 LCD
// https://www.aliexpress.com/item/32837222770.html
//
// #define AZSMZ_12864

//
// Silvergate GLCD 控制器
// https://github.com/android444/Silvergate
//
// #define SILVER_GATE_GLCD_CONTROLLER

//
// 带 SD 的 eMotion Tech LCD
// https://www.reprap-france.com/produit/1234568748-ecran-graphique-128-x-64-points-2-1
//
// #define EMOTION_TECH_LCD

//=============================================================================
//==============================  OLED 显示屏  ==============================
//=============================================================================

//
// SSD1306 OLED 全图形通用显示屏
//
// #define U8GLIB_SSD1306

//
// 支持 SAV OLEd LCD 模块，可使用基于 SSD1306 或 SH1106 的 LCD 模块
//
// #define SAV_3DGLCD
#if ENABLED(SAV_3DGLCD)
#define U8GLIB_SSD1306
// #define U8GLIB_SH1106
#endif

//
// TinyBoy2 128x64 OLED / 编码器面板
//
// #define OLED_PANEL_TINYBOY2

//
// MKS OLED 1.3" 128×64 全图形控制器
// https://reprap.org/wiki/MKS_12864OLED
//
// 小巧但非常清晰的 OLED 显示屏
//
// #define MKS_12864OLED          // 使用 SH1106 控制器（默认）
// #define MKS_12864OLED_SSD1306  // 使用 SSD1306 控制器

//
// Zonestar OLED 128×64 全图形控制器
//
// #define ZONESTAR_12864LCD           // 采用 ST7920 的图形 (DOGM)
//  控制器
// #define ZONESTAR_12864OLED          // 1.3" OLED，采用 SH1106
//  控制器（默认）
// #define ZONESTAR_12864OLED_SSD1306  // 0.96" OLED，采用
// SSD1306 控制器

//
// Einstart S OLED SSD1306
//
// #define U8GLIB_SH1106_EINSTART

//
// 带 i2c 蜂鸣器和 LED 的 Overlord OLED 显示屏/控制器
//
// #define OVERLORD_OLED

//
// 带 WS2812 RGB 的 FYSETC OLED 2.42" 128×64 全图形控制器
// 购买地址：https://www.aliexpress.com/item/4000345255731.html
// #define FYSETC_242_OLED_12864   // 使用 SSD1309 控制器

//
// K.3D SSD1309 OLED 2.42" 128×64 全图形控制器
//
// #define K3D_242_OLED_CONTROLLER   // 软件 SPI

//=============================================================================
//========================== 可扩展 UI 显示屏 ===========================
//=============================================================================

/**
 * 带 DWIN OS 的 DGUS 触摸显示屏。（选择其一）
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
 *  - 下载
 * https://github.com/InsanityAutomation/Marlin/raw/CrealityDwin_2.0/TM3D_Combined480272_Landscape_V7.7z
 *  - 将下载的 DWIN_SET 文件夹复制到 SD 卡。
 *
 * CREALITY_TOUCH
 *  - CR-6 原装触摸屏。带触摸功能的 DWIN 显示屏。
 *
 * 使用 DGUS 显示屏为 Marlin 刷写固件：
 *  - 将 SD 卡格式化为 FAT32，分配单元大小为 4kb。
 *  - 按你的显示屏类型下载对应文件。
 *  - 将 microSD 卡插入显示屏背面。
 *  - 启动显示屏并等待更新完成。
 *
 * :[ 'ORIGIN', 'FYSETC', 'HYPRECY', 'MKS', 'RELOADED', 'IA_CREALITY' ]
 */
// #define DGUS_LCD_UI ORIGIN
#if DGUS_UI_IS(MKS)
#define USE_MKS_GREEN_UI
#elif DGUS_UI_IS(IA_CREALITY)
// #define LCD_SCREEN_ROTATE 90          // 竖屏模式或 800x480 显示屏
// #define IA_CREALITY_BOOT_DELAY 1500   // (ms)
#endif

//
// Malyan M200/M300 打印机的触摸 LCD
//
// #define MALYAN_LCD

//
// FTDI EVE (FT800/FT810) 显示屏的触摸 UI
// 全部配置选项请参见 Configuration_adv.h。
//
// #define TOUCH_UI_FTDI_EVE

//
// Anycubic Chiron 的触摸 LCD
//
// #define ANYCUBIC_LCD_CHIRON

//
// Anycubic i3 Mega 的触摸 LCD
//
// #define ANYCUBIC_LCD_I3MEGA
#if ENABLED(ANYCUBIC_LCD_I3MEGA)
// #define ANYCUBIC_LCD_GCODE_EXT  // 在菜单项后添加 ".gcode" 以兼容 DGUS
// 克隆版
#endif

//
// Anycubic Vyper 的触摸 LCD
//
// #define ANYCUBIC_LCD_VYPER

//
// 320x240 Nextion 2.8" 串行 TFT 电阻式触摸屏 NX3224T028
//
// #define NEXTION_TFT

//
// Escher3D 的 PanelDue 触摸控制器
// http://escher3d.com/pages/order/products/product2.php
//
// #define PANELDUE

//
// 第三方或厂商定制的控制器接口。
// 源码应安装在 'src/lcd/extui' 中。
//
// #define EXTENSIBLE_UI

#if ENABLED(EXTENSIBLE_UI)
// #define EXTUI_LOCAL_BEEPER // 允许在外接显示屏上使用
// 本地蜂鸣器引脚
#endif

//=============================================================================
//=============================== 图形 TFT ==============================
//=============================================================================

/**
 * 特定 TFT 型号预设。请启用以下选项之一，
 * 或启用 TFT_GENERIC 并设置子选项。
 */

//
// 来自 MKS 的 480x320、3.5" 带旋转编码器的 SPI 显示屏
// 通常与 MKS Robin Nano V2 和 V3 搭配使用
//
// #define MKS_TS35_V2_0

//
// 来自 MKS 的 320x240、2.4" FSMC 显示屏
// 通常与 MKS Robin Nano V1.2 搭配使用
//
// #define MKS_ROBIN_TFT24

//
// 来自 MKS 的 320x240、2.8" FSMC 显示屏
// 通常与 MKS Robin Nano V1.2 搭配使用
//
// #define MKS_ROBIN_TFT28

//
// 来自 MKS 的 320x240、3.2" FSMC 显示屏
// 通常与 MKS Robin Nano V1.2 搭配使用
//
// #define MKS_ROBIN_TFT32

//
// 来自 MKS 的 480x320、3.5" FSMC 显示屏
// 通常与 MKS Robin Nano V1.2 搭配使用
//
// #define MKS_ROBIN_TFT35

//
// 来自 MKS 的 480x272、4.3" FSMC 显示屏
//
// #define MKS_ROBIN_TFT43

//
// 来自 MKS 的 320x240、3.2" FSMC 显示屏
// 通常与 MKS Robin 搭配使用
//
// #define MKS_ROBIN_TFT_V1_1R

//
// 来自 Tronxy 的 480x320、3.5" FSMC 原装显示屏
//
// #define TFT_TRONXY_X5SA

//
// 来自 AnyCubic 的 480x320、3.5" FSMC 原装显示屏
//
// #define ANYCUBIC_TFT35

//
// 来自 Longer/Alfawise 的 320x240、2.8" FSMC 原装显示屏
//
// #define LONGER_LK_TFT28

//
// 来自 ET4 的 320x240、2.8" FSMC 原装显示屏
//
// #define ANET_ET4_TFT28

//
// 来自 ET5 的 480x320、3.5" FSMC 原装显示屏
//
// #define ANET_ET5_TFT35

//
// 来自 BIQU-BX 的 1024x600、7" 带旋转编码器的 RGB 原装显示屏
//
// #define BIQU_BX_TFT70

//
// 来自 BIQU B1 SE 系列的 480x320、3.5" 带旋转编码器的 SPI 原装显示屏
//
// #define BTT_TFT35_SPI_V1_0

//
// 通用 TFT，提供详细选项
//
// #define TFT_GENERIC
#if ENABLED(TFT_GENERIC)
// :[ 'AUTO', 'ST7735', 'ST7789', 'ST7796', 'R61505', 'ILI9328', 'ILI9341', 'ILI9488' ]
#define TFT_DRIVER AUTO

// 接口。启用以下选项之一：
// #define TFT_INTERFACE_FSMC
// #define TFT_INTERFACE_SPI

// TFT 分辨率。启用以下选项之一：
// #define TFT_RES_320x240
// #define TFT_RES_480x272
// #define TFT_RES_480x320
// #define TFT_RES_1024x600
#endif

/**
 * TFT UI - 用户界面选择。启用以下选项之一：
 *
 *   TFT_CLASSIC_UI - 模拟的 DOGM - 128x64 放大显示
 *   TFT_COLOR_UI   - Marlin 默认菜单，触摸友好，支持完整的 TFT 功能
 * TFT_LVGL_UI    - 使用 LVGL 的现代化 UI
 *
 *   对于 LVGL_UI，还需将编译目录中的 'assets' 文件夹复制到
 *   SD 卡根目录，并连同编译好的固件一起复制。
 */
// #define TFT_CLASSIC_UI
// #define TFT_COLOR_UI
// #define TFT_LVGL_UI

#if ENABLED(TFT_COLOR_UI)
/**
 * Color_UI 使用的 TFT 字体。请从以下选项中选择：
 *
 * NOTOSANS  - 带抗锯齿的默认字体。支持拉丁扩展字符和
 * 非拉丁字符。UNIFONT   - 轻量字体，无抗锯齿。
 * 支持拉丁扩展字符和非拉丁字符。HELVETICA - 轻量
 * 字体，无抗锯齿。仅支持基本拉丁文 (0x0020-0x007F) 和 Latin-1
 * 补充字符 (0x0080-0x00FF)。
 */
#define TFT_FONT NOTOSANS

// #define TFT_SHARED_IO   // I/O 由 TFT 显示屏与其他
// 设备共享。禁用异步数据传输。
#endif

#if ENABLED(TFT_LVGL_UI)
// #define MKS_WIFI_MODULE // MKS WiFi 模块
#endif

/**
 * TFT 旋转。设置为以下值之一：
 *
 *   TFT_ROTATE_90,  TFT_ROTATE_90_MIRROR_X,  TFT_ROTATE_90_MIRROR_Y,
 *   TFT_ROTATE_180, TFT_ROTATE_180_MIRROR_X, TFT_ROTATE_180_MIRROR_Y,
 *   TFT_ROTATE_270, TFT_ROTATE_270_MIRROR_X, TFT_ROTATE_270_MIRROR_Y,
 *   TFT_MIRROR_X, TFT_MIRROR_Y, TFT_NO_ROTATION
 */
// #define TFT_ROTATION TFT_NO_ROTATION

//=============================================================================
//============================  其他控制器  ============================
//=============================================================================

//
// Ender-3 v2 原装显示屏。带旋转编码器的 DWIN 显示屏。
//
// #define DWIN_CREALITY_LCD           // Creality UI
// #define DWIN_LCD_PROUI              // MRiscoC 制作的 Pro UI
// #define DWIN_CREALITY_LCD_JYERSUI   // Jacob Myers 制作的 Jyers UI
// #define DWIN_MARLINUI_PORTRAIT      // MarlinUI（竖屏方向）
// #define DWIN_MARLINUI_LANDSCAPE     // MarlinUI（横屏方向）

//
// 触摸屏设置
//
// #define TOUCH_SCREEN
#if ENABLED(TOUCH_SCREEN)
#define BUTTON_DELAY_EDIT 50  // (ms) 编辑界面的按键重复延迟
#define BUTTON_DELAY_MENU 250 // (ms) 菜单的按键重复延迟

// #define DISABLE_ENCODER         // 如果存在编码器，禁用点击编码器
// #define TOUCH_IDLE_SLEEP_MINS 5 // (minutes) 一段时间无操作后
// 显示屏进入休眠。使用 M255 S 设置。

#define TOUCH_SCREEN_CALIBRATION

// #define TOUCH_CALIBRATION_X 12316
// #define TOUCH_CALIBRATION_Y -8981
// #define TOUCH_OFFSET_X        -43
// #define TOUCH_OFFSET_Y        257
// #define TOUCH_ORIENTATION TOUCH_LANDSCAPE

#if BOTH(TOUCH_SCREEN_CALIBRATION, EEPROM_SETTINGS)
#define TOUCH_CALIBRATION_AUTO_SAVE // 自动保存校准成功的数值
                                    // 到 EEPROM
#endif

#if ENABLED(TFT_COLOR_UI)
// #define SINGLE_TOUCH_NAVIGATION
#endif
#endif

//
// RepRapWorld REPRAPWORLD_KEYPAD v1.1
// https://reprapworld.com/products/electronics/ramps/keypad_v1_0_fully_assembled/
//
// #define REPRAPWORLD_KEYPAD
// #define REPRAPWORLD_KEYPAD_MOVE_STEP 10.0 // (mm) 每次按键
// 的移动距离

//
// 带按键输入和状态 LED 的 EasyThreeD ET-4000+
//
// #define EASYTHREED_UI

//=============================================================================
//=============================== 附加功能 ==============================
//=============================================================================

// @section fans

// 设置用户可控风扇的数量。禁用此项则使用板上定义的所有风扇。
// :[1,2,3,4,5,6,7,8]
// #define NUM_M106_FANS 1

// 像驱动加热器一样使用软件 PWM 驱动风扇。这使用非常低的频率，
// 不像硬件 PWM 那样令人烦躁。但另一方面，
// 如果该频率过低，你还应增大 SOFT_PWM_SCALE。
// #define FAN_SOFT_PWM

// 此值每增加 1，软件 PWM 频率就会翻倍，
// 从而影响加热器，以及启用 FAN_SOFT_PWM 时的风扇。
// 但每增加一次，控制分辨率就会减半；
// 值为 0 时，有 128 个有效控制位置。
// :[0,1,2,3,4,5,6,7]
#define SOFT_PWM_SCALE 0

// 如果 SOFT_PWM_SCALE 设置为大于 0 的值，可以使用抖动
// 来缓解相关的分辨率损失。启用后，
// 部分 PWM 周期会被拉长，使平均占空比
// 达到所需值。
// #define SOFT_PWM_DITHER

// @section extras

// 支持 BariCUDA 膏料挤出机
// #define BARICUDA

// @section lights

// 显示热端和热床温度的温度状态 LED。
// 如果所有热端、热床温度和目标温度都低于 54C，
// 则蓝色 LED 点亮；否则红色 LED 点亮。(1C 迟滞)
// #define TEMP_STAT_LEDS

// 支持 BlinkM/CyzRgb
// #define BLINKM

// 支持 PCA9632 PWM LED 驱动器
// #define PCA9632

// 支持 PCA9533 PWM LED 驱动器
// #define PCA9533

/**
 * RGB LED / LED 灯带控制
 *
 * 启用对连接到 5V 数字引脚的 RGB LED 的支持，或
 * 对连接到由数字引脚控制的 MOSFET 的 RGB 灯带的支持。
 *
 * 增加 M150 命令用于设置 LED（或 LED 灯带）的颜色。
 * 如果引脚支持 PWM（例如 4、5、6、11），则可将亮度值
 * 设置在 0 到 255 之间。
 * 对于 NeoPixel LED，还可以设置整体亮度参数。
 *
 *  === 注意 ===
 *  LED 灯带需要在 PWM 线与 LED 之间加装 MOSFET 芯片，
 *  因为 Arduino 无法承受 LED 所需的电流。
 *  不遵守此注意事项可能会损坏你的 Arduino！
 *
 *  注意：需要单独的 5V 电源！NeoPixel LED 需要
 *  比 Arduino 5V 线性稳压器所能提供的更大的电流。
 *
 *  需要 50 <> 100Hz 之间的 PWM 频率（检查 HAL 或变体）
 *  如果可能，使用 FAST_PWM_FAN 以降低风扇噪音。
 */

// LED 类型。启用以下两个选项中的一个：
// #define RGB_LED
// #define RGBW_LED

#if EITHER(RGB_LED, RGBW_LED)
// #define RGB_LED_R_PIN 34
// #define RGB_LED_G_PIN 43
// #define RGB_LED_B_PIN 35
// #define RGB_LED_W_PIN -1
#endif

#if ANY(RGB_LED, RGBW_LED, PCA9632)
// #define RGB_STARTUP_TEST              // 对于 PWM 引脚，
// 在所有颜色之间做渐变
#if ENABLED(RGB_STARTUP_TEST)
#define RGB_STARTUP_TEST_INNER_MS 10 // (ms) 减小或增大渐变速度
#endif
#endif

// 支持 Adafruit NeoPixel LED 驱动器
#define NEOPIXEL_LED
#if ENABLED(NEOPIXEL_LED)
#define NEOPIXEL_TYPE                                                          \
  NEO_GRB // NEO_GRBW, NEO_RGBW, NEO_GRB, NEO_RBG 等
          // 参见
          // https://github.com/adafruit/Adafruit_NeoPixel/blob/master/Adafruit_NeoPixel.h
// #define NEOPIXEL_PIN                4 // LED 驱动引脚
#define NEOPIXEL2_TYPE NEOPIXEL_TYPE
// #define NEOPIXEL2_PIN               5
#define NEOPIXEL_PIXELS                                                        \
  18 // 灯带中 LED 的数量。（最长灯带适用于
     // NEOPIXEL2_SEPARATE 未启用的情形。）
#define NEOPIXEL_IS_SEQUENTIAL  // 温度变化时按顺序显示 -
                                // 逐个显示 LED。禁用后可一次更改所有
                                // LED。
#define NEOPIXEL_BRIGHTNESS 255 // 初始亮度 (0-255)
#define NEOPIXEL_STARTUP_TEST   // 启动时循环显示各颜色

// 支持第二个由 M150 S1 ... 控制的 Adafruit NeoPixel LED 驱动器
#define NEOPIXEL2_SEPARATE
#if ENABLED(NEOPIXEL2_SEPARATE)
#define NEOPIXEL2_PIXELS 18      // 第二条灯带中的 LED 数量
#define NEOPIXEL2_BRIGHTNESS 255 // 初始亮度 (0-255)
#define NEOPIXEL2_STARTUP_TEST   // 启动时循环显示各颜色
#define NEOPIXEL_M150_DEFAULT                                                  \
  -1 // M150 不带 'S' 时的默认灯带。用 -1 表示全部默认设置。
#else
// #define NEOPIXEL2_INSERIES          // 默认行为是 NeoPixel 2
// 并联
#endif

// 使用部分 NeoPixel LED 作为静态（背景）照明
// #define NEOPIXEL_BKGD_INDEX_FIRST   0 // 第一个背景 LED 的索引
// #define NEOPIXEL_BKGD_INDEX_LAST    5 // 最后一个背景 LED 的索引
// #define NEOPIXEL_BKGD_COLOR         { 255, 255, 255, 0 }  // R, G, B, W
// #define NEOPIXEL_BKGD_TIMEOUT_COLOR {  25,  25,  25, 0 }  // R, G, B, W
// #define NEOPIXEL_BKGD_ALWAYS_ON       // 当其他
// NeoPixel 关闭时保持背光常亮
#endif

/**
 * 打印机事件 LED
 *
 * 打印过程中，LED 会反映打印机状态：
 *
 *  - 随着热床达到目标温度，颜色由蓝渐变为紫
 *  - 随着热端达到温度，颜色由紫渐变为红
 *  - 变为白色以照亮工作台面
 *  - 打印完成后变为绿色
 *  - 打印完成且用户按下按钮后熄灭
 */
#if ANY(BLINKM, RGB_LED, RGBW_LED, PCA9632, PCA9533, NEOPIXEL_LED)
// #define PRINTER_EVENT_LEDS
#endif

// @section servos

/**
 * 舵机数量
 *
 * 对于某些与舵机相关的选项，NUM_SERVOS 会自动设置。
 * 如果有需要手动控制的额外舵机，请手动设置此项。
 * 设为 0 可关闭舵机支持。
 */
#define NUM_SERVOS 2 // 注意：M280-M282 命令的舵机索引从 0 开始

// (ms) 下一次移动开始前的延时，
// 给舵机时间转到目标角度。300ms 是不错的值，
// 但可以尝试更短的延时。如果舵机无法到达要求的位置，请增大该值。
#define SERVO_DELAY {300, 300}

// 只在移动过程中为舵机供电，否则保持关闭以防止抖动
// #define DEACTIVATE_SERVOS_AFTER_MOVE

// 用 M281 编辑舵机角度，用 M500 保存到 EEPROM
// #define EDITABLE_SERVO_ANGLES

// 用 M282 禁用舵机，以减少功耗、噪音和发热
// （舵机不使用时）
#define SERVO_DETACH_GCODE

// 支持 RS485 控制
#define RS485_ENABLED
#define RS485_BUS_BUFFER_SIZE 128
#define RS485_SERIAL_PORT 1