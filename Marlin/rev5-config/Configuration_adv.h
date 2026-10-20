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
#pragma once

/**
 * Configuration_adv.h
 *
 * 高级设置。
 * 仅在完全清楚自己在做什么时才修改这些设置。
 * 部分设置若配置不当可能损坏打印机！
 *
 * 基础设置见 Configuration.h
 */
#define CONFIGURATION_ADV_H_VERSION 02010300

// @section develop

/**
 * 配置导出
 *
 * 随构建一起导出配置。（参见 signature.py）
 * 输出文件随构建一同保存（例如 .pio/build/mega2560）。
 *
 * 参见 `build_all_examples --ini` 作为 config.ini 归档的示例。
 *
 *  1 = marlin_config.json - 包含配置的字典。
 *      该文件也会为 CONFIGURATION_EMBEDDING 生成。
 *  2 = config.ini - PlatformIO 预处理所用的文件格式。
 *  3 = schema.json - 完整的配置模式。(13 = pattern groups)
 *  4 = schema.yml - 完整的配置模式。
 */
//#define CONFIG_EXPORT 2 // :[1:'JSON', 2:'config.ini', 3:'schema.json', 4:'schema.yml']

//===========================================================================
//=============================     温度设置     ============================
//===========================================================================
// @section temperature

/**
 * 热电偶传感器对噪声相当敏感。任何在传感器导线上引入的噪声，
 * 例如与步进电机导线并行敷设所产生的噪声，
 * 都可能使热电偶传感器报出虚假错误。此值表示在错误
 * 被上报之前允许连续出现的错误次数。
 * 这让我们可以忽略间歇性错误状况，同时
 * 仍能检测到真正的故障，真正的故障应表现为
 * 来自传感器的持续错误流。
 *
 * 将此值设为 0 表示一出现首个错误即报错。
 */
#define THERMOCOUPLE_MAX_ERRORS 15

//
// 自定义热敏电阻 1000 参数
//
#if TEMP_SENSOR_0 == 1000
  #define HOTEND0_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define HOTEND0_RESISTANCE_25C_OHMS   100000 // 25C 时的阻值
  #define HOTEND0_BETA                    3950 // Beta 值
  #define HOTEND0_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_1 == 1000
  #define HOTEND1_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define HOTEND1_RESISTANCE_25C_OHMS   100000 // 25C 时的阻值
  #define HOTEND1_BETA                    3950 // Beta 值
  #define HOTEND1_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_2 == 1000
  #define HOTEND2_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define HOTEND2_RESISTANCE_25C_OHMS   100000 // 25C 时的阻值
  #define HOTEND2_BETA                    3950 // Beta 值
  #define HOTEND2_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_3 == 1000
  #define HOTEND3_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define HOTEND3_RESISTANCE_25C_OHMS   100000 // 25C 时的阻值
  #define HOTEND3_BETA                    3950 // Beta 值
  #define HOTEND3_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_4 == 1000
  #define HOTEND4_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define HOTEND4_RESISTANCE_25C_OHMS   100000 // 25C 时的阻值
  #define HOTEND4_BETA                    3950 // Beta 值
  #define HOTEND4_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_5 == 1000
  #define HOTEND5_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define HOTEND5_RESISTANCE_25C_OHMS   100000 // 25C 时的阻值
  #define HOTEND5_BETA                    3950 // Beta 值
  #define HOTEND5_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_6 == 1000
  #define HOTEND6_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define HOTEND6_RESISTANCE_25C_OHMS   100000 // 25C 时的阻值
  #define HOTEND6_BETA                    3950 // Beta 值
  #define HOTEND6_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_7 == 1000
  #define HOTEND7_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define HOTEND7_RESISTANCE_25C_OHMS   100000 // 25C 时的阻值
  #define HOTEND7_BETA                    3950 // Beta 值
  #define HOTEND7_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_BED == 1000
  #define BED_PULLUP_RESISTOR_OHMS        4700 // 上拉电阻
  #define BED_RESISTANCE_25C_OHMS       100000 // 25C 时的阻值
  #define BED_BETA                        3950 // Beta 值
  #define BED_SH_C_COEFF                     0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_CHAMBER == 1000
  #define CHAMBER_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define CHAMBER_RESISTANCE_25C_OHMS   100000 // 25C 时的阻值
  #define CHAMBER_BETA                    3950 // Beta 值
  #define CHAMBER_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_COOLER == 1000
  #define COOLER_PULLUP_RESISTOR_OHMS     4700 // 上拉电阻
  #define COOLER_RESISTANCE_25C_OHMS    100000 // 25C 时的阻值
  #define COOLER_BETA                     3950 // Beta 值
  #define COOLER_SH_C_COEFF                  0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_PROBE == 1000
  #define PROBE_PULLUP_RESISTOR_OHMS      4700 // 上拉电阻
  #define PROBE_RESISTANCE_25C_OHMS     100000 // 25C 时的阻值
  #define PROBE_BETA                      3950 // Beta 值
  #define PROBE_SH_C_COEFF                   0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_BOARD == 1000
  #define BOARD_PULLUP_RESISTOR_OHMS      4700 // 上拉电阻
  #define BOARD_RESISTANCE_25C_OHMS     100000 // 25C 时的阻值
  #define BOARD_BETA                      3950 // Beta 值
  #define BOARD_SH_C_COEFF                   0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_REDUNDANT == 1000
  #define REDUNDANT_PULLUP_RESISTOR_OHMS  4700 // 上拉电阻
  #define REDUNDANT_RESISTANCE_25C_OHMS 100000 // 25C 时的阻值
  #define REDUNDANT_BETA                  3950 // Beta 值
  #define REDUNDANT_SH_C_COEFF               0 // Steinhart-Hart C 系数
#endif

/**
 * 热电偶选项 — 适用于 MAX6675 (-2)、MAX31855 (-3) 和 MAX31865 (-5)。
 */
//#define TEMP_SENSOR_FORCE_HW_SPI                // 忽略 SCK/MOSI/MISO 引脚；使用 CS 与默认 SPI 总线。
//#define MAX31865_SENSOR_WIRES_0 2               // (2-4) 连接到 MAX31865 主板的探针导线数量。
//#define MAX31865_SENSOR_WIRES_1 2
//#define MAX31865_SENSOR_WIRES_2 2

//#define MAX31865_50HZ_FILTER                    // 使用 50Hz 滤波器而非默认的 60Hz。
//#define MAX31865_USE_READ_ERROR_DETECTION       // 将数值尖峰（1 秒内 20°C 变化）视为读取错误。

//#define MAX31865_USE_AUTO_MODE                  // 读取比单次模式更快更频繁；偏置电压始终开启；对 RTD 温度有轻微影响。
//#define MAX31865_MIN_SAMPLING_TIME_MSEC     100 // (ms) 单次模式：最小读取间隔。通过让传感器更长时间断电来减轻偏置电压影响。
//#define MAX31865_IGNORE_INITIAL_FAULTY_READS 10 // 忽略部分读取故障（保留温度读数），以规避某个可能的问题 (#23439)。

//#define MAX31865_WIRE_OHMS_0              0.95f // 对于两线制，设置导线电阻以获得更准确的读数。
//#define MAX31865_WIRE_OHMS_1              0.0f
//#define MAX31865_WIRE_OHMS_2              0.0f

/**
 * Hephestos 2 24V 热床升级套件。
 * https://store.bq.com/en/heated-bed-kit-hephestos2
 */
//#define HEPHESTOS2_HEATED_BED_KIT
#if ENABLED(HEPHESTOS2_HEATED_BED_KIT)
  #define HEATER_BED_INVERTING true
#endif

//
// 热床 Bang-Bang（开关式）控制选项
//
#if DISABLED(PIDTEMPBED)
  #define BED_CHECK_INTERVAL 5000   // (ms) bang-bang 控制中两次检查之间的间隔
  #if ENABLED(BED_LIMIT_SWITCHING)
    #define BED_HYSTERESIS 2        // (°C) 仅当 ABS(T-target) > BED_HYSTERESIS 时才设置相应的加热器状态
  #endif
#endif

//
// 加热腔体选项
//
#if DISABLED(PIDTEMPCHAMBER)
  #define CHAMBER_CHECK_INTERVAL 5000   // (ms) bang-bang 控制中两次检查之间的间隔
  #if ENABLED(CHAMBER_LIMIT_SWITCHING)
    #define CHAMBER_HYSTERESIS 2        // (°C) 仅当 ABS(T-target) > CHAMBER_HYSTERESIS 时才设置相应的加热器状态
  #endif
#endif

#if TEMP_SENSOR_CHAMBER
  //#define HEATER_CHAMBER_PIN      P2_04   // 必须的加热器开关引脚（示例：SKR 1.4 Turbo HE1 插座）
  //#define HEATER_CHAMBER_INVERTING false
  //#define FAN1_PIN                   -1   // 移除引脚 P2_04 上的风扇信号（示例：SKR 1.4 Turbo HE1 插座）

  //#define CHAMBER_FAN               // 为腔体启用风扇
  #if ENABLED(CHAMBER_FAN)
    //#define CHAMBER_FAN_INDEX   2   // 用作腔体风扇的风扇索引。（默认：第一个未使用的风扇）
    #define CHAMBER_FAN_MODE      2   // 风扇控制模式：0=静态；1=温度高于目标时线性增加；2=V 形曲线；3=类似 1 但风扇始终开启。
    #if CHAMBER_FAN_MODE == 0
      #define CHAMBER_FAN_BASE  255   // 腔体风扇 PWM (0-255)
    #elif CHAMBER_FAN_MODE == 1
      #define CHAMBER_FAN_BASE  128   // 腔体风扇基础 PWM (0-255)；腔体温度高于目标时开启
      #define CHAMBER_FAN_FACTOR 25   // 每高于目标 1°C 的 PWM 增量
    #elif CHAMBER_FAN_MODE == 2
      #define CHAMBER_FAN_BASE  128   // 腔体风扇最小 PWM (0-255)
      #define CHAMBER_FAN_FACTOR 25   // 每偏离目标 1°C 的 PWM 增量
    #elif CHAMBER_FAN_MODE == 3
      #define CHAMBER_FAN_BASE  128   // 腔体风扇基础 PWM (0-255)
      #define CHAMBER_FAN_FACTOR 25   // 每高于目标 1°C 的 PWM 增量
    #endif
  #endif

  //#define CHAMBER_VENT              // 为腔体启用舵机控制的通风口
  #if ENABLED(CHAMBER_VENT)
    #define CHAMBER_VENT_SERVO_NR  1  // 通风舵机的索引
    #define HIGH_EXCESS_HEAT_LIMIT 5  // 高于目标温度多少即视为腔体存在多余热量
    #define LOW_EXCESS_HEAT_LIMIT  3
    #define MIN_COOLING_SLOPE_TIME_CHAMBER_VENT 20
    #define MIN_COOLING_SLOPE_DEG_CHAMBER_VENT 1.5
  #endif
#endif

//
// 激光冷却器选项
//
#if TEMP_SENSOR_COOLER
  #define COOLER_MINTEMP           8  // (°C)
  #define COOLER_MAXTEMP          26  // (°C)
  #define COOLER_DEFAULT_TEMP     16  // (°C)
  #define TEMP_COOLER_HYSTERESIS   1  // (°C) 被视为与目标“足够接近”的温度偏差范围
  #define COOLER_PIN               8  // 激光冷却器开关引脚，用于控制冷却元件（如 TEC、通过继电器控制的外部制冷机）的电源
  #define COOLER_INVERTING     false
  #define TEMP_COOLER_PIN         15  // 激光/冷却器温度传感器引脚。需要 ADC。
  #define COOLER_FAN                  // 为冷却器启用风扇，风扇编号 0、1、2、3 等。
  #define COOLER_FAN_INDEX         0  // 风扇编号 0、1、2 等。例如
  #if ENABLED(COOLER_FAN)
    #define COOLER_FAN_BASE      100  // 冷却器风扇基础 PWM (0-255)；冷却器温度高于目标时开启
    #define COOLER_FAN_FACTOR     25  // 每高于目标 1°C 的 PWM 增量
  #endif
#endif

//
// 主板传感器选项
//
#if TEMP_SENSOR_BOARD
  #define THERMAL_PROTECTION_BOARD   // 若主板传感器超出下面的温度范围则停止打印机。
  #define BOARD_MINTEMP           8  // (°C)
  #define BOARD_MAXTEMP          70  // (°C)
  #ifndef TEMP_BOARD_PIN
    //#define TEMP_BOARD_PIN -1      // 主板温度传感器引脚，若未在引脚文件中设置。
  #endif
#endif

/**
 * 温度保护为打印机提供额外保护，防止其损坏和起火。
 * Marlin 始终包含安全的最低与最高温度范围，
 * 用以防范热敏电阻导线断裂或断开。
 *
 * 问题：若热敏电阻脱落，它会报告
 * 低得多的室内空气温度，而固件
 * 仍会让加热器保持开启。
 *
 * 解决方案：一旦温度达到目标，即开始监测。若
 * 温度长时间（期间）远低于目标（滞回），
 * 固件将出于安全考虑停止机器。
 *
 * 若“温度失控”出现误报，请增大
 * THERMAL_PROTECTION_HYSTERESIS 和/或 THERMAL_PROTECTION_PERIOD
 */
#if ENABLED(THERMAL_PROTECTION_HOTENDS)
  #define THERMAL_PROTECTION_PERIOD 40        // 秒
  #define THERMAL_PROTECTION_HYSTERESIS 4     // 摄氏度

  //#define ADAPTIVE_FAN_SLOWING              // 温度下降时减慢模型冷却风扇
  #if ENABLED(ADAPTIVE_FAN_SLOWING)
    //#define REPORT_ADAPTIVE_FAN_SLOWING     // 向控制台报告风扇减速活动
    #if EITHER(MPCTEMP, PIDTEMP)
      //#define TEMP_TUNING_MAINTAIN_FAN      // 在 M303 或 M306 T 期间不降低风扇转速
    #endif
  #endif

  /**
   * 每当 M104、M109 或 M303 提高目标温度时，
   * 固件将等待 WATCH_TEMP_PERIOD 到期。若温度
   * 未上升 WATCH_TEMP_INCREASE 度，则机器停机并
   * 需要硬复位。该检测会在任何 M104/M109/M303 时重新开始，但仅当
   * 当前温度足够低于目标、足以进行可靠
   * 检测时才会如此。
   *
   * 若“加热失败”出现误报，请增大 WATCH_TEMP_PERIOD
   * 和/或减小 WATCH_TEMP_INCREASE。WATCH_TEMP_INCREASE 不应设为
   * 低于 2。
   */
  #define WATCH_TEMP_PERIOD  40               // 秒
  #define WATCH_TEMP_INCREASE 2               // 摄氏度
#endif

/**
 * 热床的温度保护参数与上述挤出机的相同。
 */
#if ENABLED(THERMAL_PROTECTION_BED)
  #define THERMAL_PROTECTION_BED_PERIOD        20 // 秒
  #define THERMAL_PROTECTION_BED_HYSTERESIS     2 // 摄氏度

  /**
   * 如上所述，只是针对热床 (M140/M190/M303)。
   */
  #define WATCH_BED_TEMP_PERIOD                60 // 秒
  #define WATCH_BED_TEMP_INCREASE               2 // 摄氏度
#endif

/**
 * 加热腔体的温度保护参数。
 */
#if ENABLED(THERMAL_PROTECTION_CHAMBER)
  #define THERMAL_PROTECTION_CHAMBER_PERIOD    20 // 秒
  #define THERMAL_PROTECTION_CHAMBER_HYSTERESIS 2 // 摄氏度

  /**
   * 加热腔体监测设置 (M141/M191)。
   */
  #define WATCH_CHAMBER_TEMP_PERIOD            60 // 秒
  #define WATCH_CHAMBER_TEMP_INCREASE           2 // 摄氏度
#endif

/**
 * 激光冷却器的温度保护参数。
 */
#if ENABLED(THERMAL_PROTECTION_COOLER)
  #define THERMAL_PROTECTION_COOLER_PERIOD     10 // 秒
  #define THERMAL_PROTECTION_COOLER_HYSTERESIS  3 // 摄氏度

  /**
   * 激光冷却监测设置 (M143/M193)。
   */
  #define WATCH_COOLER_TEMP_PERIOD             60 // 秒
  #define WATCH_COOLER_TEMP_INCREASE            3 // 摄氏度
#endif

#if ANY(THERMAL_PROTECTION_HOTENDS, THERMAL_PROTECTION_BED, THERMAL_PROTECTION_CHAMBER, THERMAL_PROTECTION_COOLER)
  /**
   * 温度保护偏差监测 - 实验性功能
   * 温度传感器卡死时停机。
   *
   * 此功能可能导致某些热稳定的系统停机。务必在各种
   * 条件下进行充分测试。若出现误报请禁用。
   *
   * 此功能确保温度传感器定期更新。若传感器损坏或“卡死”，
   * 或 Marlin 停止读取它们，温度将保持不变而加热器可能仍在供电！
   * 此功能仅监测温度变化，因此应能捕获任何软硬件问题。
   *
   * 默认使用上述 THERMAL_PROTECTION_*_PERIOD 常量作为时间窗口，在此窗口内
   * 必须至少发生一次温度变化，以表明传感器轮询正常。若任何被监测的
   * 加热器温度在此期间完全不变（甚至没有微小变化），则
   * 触发温度故障错误并停止打印机。
   *
   * 非常稳定的加热器可能产生误报并停机。此时可尝试稍微增大
   * 相应的 THERMAL_PROTECTION_*_PERIOD 常量。请记住，不应让不受控的加热
   * 持续超过一两分钟。
   *
   * 禁用此功能前，请务必区分误报与真正的传感器问题。若
   * 重启后加热器温度甚至略高于预期，可能存在真正的
   * 温度故障。请在上位机中查看温度曲线是否有异常突起。
   */
  //#define THERMAL_PROTECTION_VARIANCE_MONITOR
  #if ENABLED(THERMAL_PROTECTION_VARIANCE_MONITOR)
    // 偏差检测窗口，用于覆盖上述 THERMAL_PROTECTION...PERIOD 设置。
    // 请注意，某些加热器升温比其他的快。
    //#define THERMAL_PROTECTION_VARIANCE_MONITOR_PERIOD 30  // (s) 覆盖所有监测周期
  #endif
#endif

#if ENABLED(PIDTEMP)
  // 向加热器功率添加一个与挤出速度成正比的额外项。
  // 恰当的 Kc 值应恰好提供足够功率来熔化增加的材料体积。
  //#define PID_EXTRUSION_SCALING
  #if ENABLED(PID_EXTRUSION_SCALING)
    #define DEFAULT_Kc (100) // 加热功率 = Kc * e_speed
    #define LPQ_MAX_LEN 50
  #endif

  /**
   * 向加热器功率添加一个与风扇转速成正比的额外项。
   * 恰当的 Kf 值应恰好提供足够功率来补偿冷却风扇造成的功率损失。
   * 你可以直接用 DEFAULT_Kf 值添加一个恒定补偿，
   * 也可按照下面的说明获得与转速相关的补偿。
   *
   * 恒定补偿（仅在风扇转速为 0% 和 100% 时使用）
   * ---------------------------------------------------------------------
   * Kf 值的良好起点来自以下计算：
   *   kf = (power_fan * eff_fan) / power_heater * 255
   * 其中 eff_fan 介于 0.0 和 1.0 之间，取决于风扇效率以及喷嘴/加热器处的气流。
   *
   * 示例：
   *   加热器：40W，风扇：0.1A * 24V = 2.4W，eff_fan = 0.8
   *   Kf = (2.4W * 0.8) / 40W * 255 = 12.24
   *
   * 与风扇转速相关的补偿
   * --------------------------------
   * 1. 要找到合适的 Kf 值，设置挤出机温度，等待稳定，然后开启风扇（100%）。
   *    确保 PID_FAN_SCALING_LIN_FACTOR 为 0 且未启用 PID_FAN_SCALING_ALTERNATIVE_DEFINITION。
   *    若看到温度下降，重复测试，缓慢增大 Kf 值，直到温度
   *    不再下降。若开启风扇后温度超调，则 Kf 值过大。
   * 2. 记录风扇转速 100% 时的 Kf 值
   * 3. 确定 PID_FAN_SCALING_MIN_SPEED 的合适值，约为风扇开始转动的转速。
   * 4. 针对此风扇转速重复步骤 1 和 2。
   * 5. 启用 PID_FAN_SCALING_ALTERNATIVE_DEFINITION，并将确定的两个 Kf 值填入
   *    PID_FAN_SCALING_AT_FULL_SPEED 和 PID_FAN_SCALING_AT_MIN_SPEED。将最小转速填入 PID_FAN_SCALING_MIN_SPEED
   */
  //#define PID_FAN_SCALING
  #if ENABLED(PID_FAN_SCALING)
    //#define PID_FAN_SCALING_ALTERNATIVE_DEFINITION
    #if ENABLED(PID_FAN_SCALING_ALTERNATIVE_DEFINITION)
      // 此替代定义用于简化配置。
      // 只需确定全速 (255) 时的 Kf 和 PID_FAN_SCALING_MIN_SPEED。
      // DEFAULT_Kf 与 PID_FAN_SCALING_LIN_FACTOR 将据此计算。

      #define PID_FAN_SCALING_AT_FULL_SPEED 13.0        //=PID_FAN_SCALING_LIN_FACTOR*255+DEFAULT_Kf
      #define PID_FAN_SCALING_AT_MIN_SPEED   6.0        //=PID_FAN_SCALING_LIN_FACTOR*PID_FAN_SCALING_MIN_SPEED+DEFAULT_Kf
      #define PID_FAN_SCALING_MIN_SPEED     10.0        // 启用 PID_FAN_SCALING 的最低风扇转速

      #define DEFAULT_Kf (255.0*PID_FAN_SCALING_AT_MIN_SPEED-PID_FAN_SCALING_AT_FULL_SPEED*PID_FAN_SCALING_MIN_SPEED)/(255.0-PID_FAN_SCALING_MIN_SPEED)
      #define PID_FAN_SCALING_LIN_FACTOR (PID_FAN_SCALING_AT_FULL_SPEED-DEFAULT_Kf)/255.0

    #else
      #define PID_FAN_SCALING_LIN_FACTOR (0)             // 冷却造成的功率损失 = Kf * (fan_speed)
      #define DEFAULT_Kf 10                              // 加到 PID 调节器上的常量值
      #define PID_FAN_SCALING_MIN_SPEED 10               // 启用 PID_FAN_SCALING 的最低风扇转速
    #endif
  #endif
#endif

/**
 * 自动温度模式
 *
 * 根据规划的 E 轴移动动态调整挤出机目标温度。
 *
 * （与 PID_EXTRUSION_SCALING 不同，后者通过额外的 kC 值跟踪 E 轴移动并调整
 *  PID 行为。）
 *
 * Autotemp 计算方式为 (mintemp + factor * mm_per_sec)，上限为 maxtemp。
 *
 * 使用 M104/M109 F<factor> S<mintemp> B<maxtemp> 启用 Autotemp 模式。
 * 发送不带 F 参数的 M104/M109（或在 AUTOTEMP_PROPORTIONAL 下用 F0）以禁用。
 */
#define AUTOTEMP
#if ENABLED(AUTOTEMP)
  #define AUTOTEMP_OLDWEIGHT    0.98  // 用于加权之前读数的系数 (0.0 < 值 < 1.0)
  #define AUTOTEMP_MIN          210
  #define AUTOTEMP_MAX          250
  #define AUTOTEMP_FACTOR       0.1f
  // 默认在 M104/M109 时使用此处设置的比例开启 AUTOTEMP
  //#define AUTOTEMP_PROPORTIONAL
  #if ENABLED(AUTOTEMP_PROPORTIONAL)
    #define AUTOTEMP_MIN_P      0 // (°C) 加到目标温度上
    #define AUTOTEMP_MAX_P      5 // (°C) 加到目标温度上
    #define AUTOTEMP_FACTOR_P   1 // 默认应用此 F 参数（可被 M104/M109 F 覆盖）
  #endif
#endif

// 显示温度 ADC 值
// 启用后 M105 将包含从温度传感器读取的 ADC 值。
//#define SHOW_TEMP_ADC_VALUES

/**
 * 高温热敏电阻支持
 *
 * 能承受高温的热敏电阻在室温和更低温度下往往难以获得
 * 良好读数。这意味着 TEMP_SENSOR_X_RAW_LO_TEMP
 * 很可能在预热过程中加热元件刚开启时被触发，
 * 从而作为安全措施引发 MINTEMP 错误
 * 并强制停止一切。
 * 为规避此限制，我们允许设置一个预热时间（在此期间
 * 不会触发 MINTEMP 错误），并添加一个 min_temp 缓冲区来处理
 * 异常读数。
 *
 * 若要为你的挤出机热敏电阻启用此功能，
 * 请取消注释并在下面的常量中设置大于 0 的值
 */

// 在触发 MINTEMP 错误之前，允许连续出现
// 低温错误的次数。（不应超过 10。）
//#define MAX_CONSECUTIVE_LOW_TEMPERATURE_ERROR_ALLOWED 0

/**
 * 挤出机在开始检查温度之前进行预热的毫秒数。
 * 此值不应设为挤出机达到目标温度所需的时间，
 * 而应设为达到热敏电阻可读取的最低温度所需的时间。
 * 越低越好/越安全。
 * 通常不应超过 30 秒 (30000)
 */
//#define PREHEAT_TIME_HOTEND_MS 0
//#define PREHEAT_TIME_BED_MS 0

// @section extruder

/**
 * 挤出机缺料预防。
 * 若机器空闲且温度高于 MINTEMP，
 * 则每隔几秒挤出一些耗材。
 */
//#define EXTRUDER_RUNOUT_PREVENT
#if ENABLED(EXTRUDER_RUNOUT_PREVENT)
  #define EXTRUDER_RUNOUT_MINTEMP 190
  #define EXTRUDER_RUNOUT_SECONDS 30
  #define EXTRUDER_RUNOUT_SPEED 1500  // (mm/min)
  #define EXTRUDER_RUNOUT_EXTRUDE 5   // (mm)
#endif

/**
 * 挤出机空闲超时
 * 防止喷嘴中的耗材碳化并造成严重堵塞。
 */
//#define HOTEND_IDLE_TIMEOUT
#if ENABLED(HOTEND_IDLE_TIMEOUT)
  #define HOTEND_IDLE_TIMEOUT_SEC (5*60)    // (seconds) 无挤出机移动以触发保护的时间
  #define HOTEND_IDLE_MIN_TRIGGER   180     // (°C) 启用挤出机保护的最低温度
  #define HOTEND_IDLE_NOZZLE_TARGET   0     // (°C) 超时后喷嘴的安全温度
  #define HOTEND_IDLE_BED_TARGET      0     // (°C) 超时后热床的安全温度
#endif

// @section temperature

// AD595 / AD8495 传感器的校准，用于调整温度测量。
// 最终温度计算公式为 (measuredTemp * GAIN) + OFFSET。
#define TEMP_SENSOR_AD595_OFFSET  0.0
#define TEMP_SENSOR_AD595_GAIN    1.0
#define TEMP_SENSOR_AD8495_OFFSET 0.0
#define TEMP_SENSOR_AD8495_GAIN   1.0

/**
 * 控制器风扇
 * 用于冷却步进电机驱动器和 MOSFET。
 *
 * 只要启用任何驱动器，风扇就会自动开启，
 * 并在驱动器关闭后不久关闭（或降至怠速）。
 */
#define USE_CONTROLLER_FAN
#if ENABLED(USE_CONTROLLER_FAN)
  #define CONTROLLER_FAN_PIN  PE2          // 为控制器风扇设置自定义引脚
  //#define CONTROLLER_FAN2_PIN -1          // 为第二个控制器风扇设置自定义引脚
  //#define CONTROLLER_FAN_USE_Z_ONLY       // 启用此选项后仅考虑 Z 轴
  //#define CONTROLLER_FAN_IGNORE_Z         // 忽略 Z 步进电机。在禁用步进电机超时时很有用。
  #define CONTROLLERFAN_SPEED_MIN         0 // (0-255) 最低转速。（若低于此值则关闭风扇。）
  #define CONTROLLERFAN_SPEED_ACTIVE    255 // (0-255) 工作转速，启用任何电机时使用
  #define CONTROLLERFAN_SPEED_IDLE        0 // (0-255) 怠速，电机关闭时使用
  #define CONTROLLERFAN_IDLE_TIME        120 // (seconds) 关闭电机后风扇继续运行的额外时间

  // 使用 TEMP_SENSOR_BOARD 作为启用控制器风扇的触发条件
  //#define CONTROLLER_FAN_MIN_BOARD_TEMP 40  // (°C) 主板达到此温度时开启风扇

  //#define CONTROLLER_FAN_EDITABLE         // 启用 M710 可配置设置
  #if ENABLED(CONTROLLER_FAN_EDITABLE)
    #define CONTROLLER_FAN_MENU             // 启用控制器风扇子菜单
  #endif
#endif

/**
 * 风扇启动加速
 * 当模型冷却或控制器风扇首次启动时，先以某个转速
 * 运行一小段时间使其可靠转动，再设置为请求转速。
 * （在带 FAN_SOFT_PWM 的 Sanguinololu 上无效。）
 */
//#define FAN_KICKSTART_TIME  100  // (ms)
//#define FAN_KICKSTART_POWER 180  // 64-255

// 某些冷却器可能需要非零的“关闭”状态。
//#define FAN_OFF_PWM  1

/**
 * PWM 风扇缩放
 *
 * 定义 PWM 风扇的最小/最大转速（通过 M106 设置）。
 *
 * 启用这些选项后，M106 的 0-255 取值范围将被缩放到一个子集，
 * 以确保风扇有足够功率转动，或以更高电流驱动
 * 低电流风扇（例如用 12V/24V 驱动 5V/12V 风扇）。
 * 值 0 始终关闭风扇。
 *
 * 定义其中一个或两个以覆盖默认的 0-255 范围。
 */
//#define FAN_MIN_PWM 50
//#define FAN_MAX_PWM 128

/**
 * 风扇快速 PWM
 *
 * 内部使用 PWM 模式、预分频值和 TOP 分辨率的组合
 * 来产生尽可能接近目标频率的频率。
 *
 * FAST_PWM_FAN_FREQUENCY
 *   将其设置为所需频率。
 *   对于 AVR，若未定义则默认为 F = F_CPU/(2*255*1)
 *   即在 16MHz 微控制器上 F = 31.4kHz，或在 20MHz 微控制器上 F = 39.2kHz。
 *   对于非 AVR，若未定义则默认为 F = 1Khz。
 *   此 F 值仅用于在缺少配置时保护硬件，
 *   并非在用户未意识到必须专门设置频率以支持目标主板时补全配置。
 *
 *   注意：设置极低频率（< 10 Hz）可能导致意外的定时器行为。
 *         设置极高频率可能损坏硬件。
 *
 * USE_OCR2A_AS_TOP [默认未定义]
 *   使用 TIMER2 进行 PWM 的主板存在限制，导致 TIMER2 上仅有少数可选频率：
 *   16MHz 单片机：[62.5kHz, 31.4kHz (默认), 7.8kHz, 3.92kHz, 1.95kHz, 977Hz, 488Hz, 244Hz, 60Hz, 122Hz, 30Hz]
 *   20MHz 单片机：[78.1kHz, 39.2kHz (默认), 9.77kHz, 4.9kHz, 2.44kHz, 1.22kHz, 610Hz, 305Hz, 153Hz, 76Hz, 38Hz]
 *   启用 USE_OCR2A_AS_TOP 可获得更大范围。但请注意，此选项会阻止
 *   引脚 OC2A 上的 PWM。仅在不需要 0C2A 上的 PWM 时使用。（检查原理图。）
 *   USE_OCR2A_AS_TOP 会牺牲占空比控制分辨率以换取更宽的频率范围。
 */
#define FAST_PWM_FAN    // 提高风扇 PWM 频率。可消除 PWM 噪声，但会增加 FET/Arduino 的发热
#if ENABLED(FAST_PWM_FAN)
  #define FAST_PWM_FAN_FREQUENCY 31400  // 在此定义以覆盖下面的默认值
  //#define USE_OCR2A_AS_TOP
  #ifndef FAST_PWM_FAN_FREQUENCY
    #ifdef __AVR__
      #define FAST_PWM_FAN_FREQUENCY ((F_CPU) / (2 * 255 * 1))
    #else
      #define FAST_PWM_FAN_FREQUENCY 1000U
    #endif
  #endif
#endif

/**
 * 将其中一个 PWM 风扇用作冗余模型冷却风扇
 */
//#define REDUNDANT_PART_COOLING_FAN 2  // 与 FAN 0 同步的风扇索引。

// @section extruder

/**
 * 挤出机散热风扇
 *
 * 挤出机自动风扇会在其挤出机温度
 * 超过 EXTRUDER_AUTO_FAN_TEMPERATURE 时自动开启。
 *
 * 主板的引脚文件指定了推荐引脚。可在此覆盖，
 * 或设为 -1 完全禁用。
 *
 * 多个挤出机可分配到同一引脚，此时
 * 任何所选挤出机超过阈值时风扇都会开启。
 */
#define E0_AUTO_FAN_PIN -1
#define E1_AUTO_FAN_PIN -1
#define E2_AUTO_FAN_PIN -1
#define E3_AUTO_FAN_PIN -1
#define E4_AUTO_FAN_PIN -1
#define E5_AUTO_FAN_PIN -1
#define E6_AUTO_FAN_PIN -1
#define E7_AUTO_FAN_PIN -1
#define CHAMBER_AUTO_FAN_PIN -1
#define COOLER_AUTO_FAN_PIN -1

#define EXTRUDER_AUTO_FAN_TEMPERATURE 50
#define EXTRUDER_AUTO_FAN_SPEED 255   // 255 == 全速
#define CHAMBER_AUTO_FAN_TEMPERATURE 30
#define CHAMBER_AUTO_FAN_SPEED 255
#define COOLER_AUTO_FAN_TEMPERATURE 18
#define COOLER_AUTO_FAN_SPEED 255

/**
 * 挤出机散热风扇转速计
 *
 * 定义一个或多个转速计引脚以启用风扇转速
 * 监测，并通过 M123 上报风扇转速。
 *
 * 注意：仅适用于 7000 RPM 以下的风扇。
 */
//#define FOURWIRES_FANS      // 安装 4 线 PWM 风扇时配合 AUTO_FAN 使用
//#define E0_FAN_TACHO_PIN -1
//#define E0_FAN_TACHO_PULLUP
//#define E0_FAN_TACHO_PULLDOWN
//#define E1_FAN_TACHO_PIN -1
//#define E1_FAN_TACHO_PULLUP
//#define E1_FAN_TACHO_PULLDOWN
//#define E2_FAN_TACHO_PIN -1
//#define E2_FAN_TACHO_PULLUP
//#define E2_FAN_TACHO_PULLDOWN
//#define E3_FAN_TACHO_PIN -1
//#define E3_FAN_TACHO_PULLUP
//#define E3_FAN_TACHO_PULLDOWN
//#define E4_FAN_TACHO_PIN -1
//#define E4_FAN_TACHO_PULLUP
//#define E4_FAN_TACHO_PULLDOWN
//#define E5_FAN_TACHO_PIN -1
//#define E5_FAN_TACHO_PULLUP
//#define E5_FAN_TACHO_PULLDOWN
//#define E6_FAN_TACHO_PIN -1
//#define E6_FAN_TACHO_PULLUP
//#define E6_FAN_TACHO_PULLDOWN
//#define E7_FAN_TACHO_PIN -1
//#define E7_FAN_TACHO_PULLUP
//#define E7_FAN_TACHO_PULLDOWN

/**
 * 模型冷却风扇多路复用器
 *
 * 此功能允许对风扇输出进行数字多路复用。
 * 多路复用器在换刀时自动切换。
 * 在下方设置 FANMUX[012]_PINs，可支持最多 2、4 或 8 路复用风扇。
 */
#define FANMUX0_PIN -1
#define FANMUX1_PIN -1
#define FANMUX2_PIN -1

/**
 * M355 机箱灯开关 / 亮度
 */
//#define CASE_LIGHT_ENABLE
#if ENABLED(CASE_LIGHT_ENABLE)
  //#define CASE_LIGHT_PIN 4                  // 如有需要覆盖默认引脚
  #define INVERT_CASE_LIGHT false             // 若引脚为 LOW 时机箱灯亮，设为 true
  #define CASE_LIGHT_DEFAULT_ON true          // 设置上电默认开启
  #define CASE_LIGHT_DEFAULT_BRIGHTNESS 105   // 设置上电默认亮度 (0-255，需 PWM 引脚)
  //#define CASE_LIGHT_NO_BRIGHTNESS          // 禁用亮度控制。用于非 PWM 照明。
  //#define CASE_LIGHT_MAX_PWM 128            // 限制 PWM 占空比 (0-255)
  //#define CASE_LIGHT_MENU                   // 在 LCD 菜单中添加机箱灯选项
  #if ENABLED(NEOPIXEL_LED)
    //#define CASE_LIGHT_USE_NEOPIXEL         // 使用 NeoPixel LED 作为机箱灯
  #endif
  #if EITHER(RGB_LED, RGBW_LED)
    //#define CASE_LIGHT_USE_RGB_LED          // 使用 RGB / RGBW LED 作为机箱灯
  #endif
  #if EITHER(CASE_LIGHT_USE_NEOPIXEL, CASE_LIGHT_USE_RGB_LED)
    #define CASE_LIGHT_DEFAULT_COLOR { 255, 255, 255, 255 } // { 红, 绿, 蓝, 白 }
  #endif
#endif

// @section homing

// 若希望即使不在归位时限流开关也保持（默认）开启，
// 启用此选项。可随时用 M120、M121 覆盖。
//#define ENDSTOPS_ALWAYS_ON_DEFAULT

// @section extras

//#define Z_LATE_ENABLE // 在最后时刻才启用 Z。若 Z 驱动器过热则需要此选项。

// 使用外部闭环控制器。如有需要可在此覆盖引脚。
//#define EXTERNAL_CLOSED_LOOP_CONTROLLER
#if ENABLED(EXTERNAL_CLOSED_LOOP_CONTROLLER)
  //#define CLOSED_LOOP_ENABLE_PIN        -1
  //#define CLOSED_LOOP_MOVE_COMPLETE_PIN -1
#endif

/**
 * 双 X 滑架
 *
 * 此设置有两个可独立移动的 X 滑架，各自配有一个挤出机。
 * 滑架可用于用两种颜色或材料打印物体，或在
 * “复制模式”下同时打印两个相同或 X 镜像的物体。
 * 未使用的滑架会自动停放以防漏料。
 * X1 为左滑架，X2 为右滑架。它们在 X 轴的两端停放和归位。
 * 默认 X2 步进电机分配到主板上第一个未使用的 E 插座。
 *
 * 可用 M605 S<mode> 选择以下双 X 滑架模式：
 *
 *   0 : (FULL_CONTROL) 切片器完全控制两个 X 滑架，只要支持双 X 滑架
 *       即可获得最佳移动效果。(M605 S0)
 *
 *   1 : (AUTO_PARK) 固件在换刀时自动停放和收回 X 滑架，
 *       因此无需额外的切片器支持。(M605 S1)
 *
 *   2 : (DUPLICATION) 固件使第二个 X 滑架和挤出机与第一个
 *       X 滑架和挤出机同步移动，同时打印同一物体的 2 份副本。
 *       用 M605 S2 X[offs] R[deg] 设置恒定 X 偏移和温度差，
 *       随后用 M605 S2 启动复制移动。
 *
 *   3 : (MIRRORED) 受 Formbot/Vivedino 启发的镜像模式，第二个挤出机复制
 *       第一个的移动，但第二个挤出机在 X 轴上反向。
 *       用 M605 S2 X[offs] R[deg] 设置初始 X 偏移和温度差，
 *       随后用 M605 S3 启动镜像移动。
 */
//#define DUAL_X_CARRIAGE
#if ENABLED(DUAL_X_CARRIAGE)
  #define X1_MIN_POS X_MIN_POS    // 设为 X_MIN_POS
  #define X1_MAX_POS X_BED_SIZE   // 最大坐标，使 X1 滑架不会撞到停放的 X2 滑架
  #define X2_MIN_POS    80        // 最小坐标，使 X2 滑架不会撞到停放的 X1 滑架
  #define X2_MAX_POS   353        // X2 滑架的最大位置，通常也是归位位置
  #define X2_HOME_DIR    1        // 设为 1。X2 滑架始终向最大限位开关位置归位
  #define X2_HOME_POS X2_MAX_POS  // X2 默认归位位置。设为 X2_MAX_POS。
                                  // 注意：双 X 滑架用 M218 T1 Xn 覆盖 X2_HOME_POS。
                                  // 这样无需重新编译即可重新校准限位开关距离。
                                  // 记得在切片器中将第二个挤出机的 X 偏移设为 0。

  // 这是默认上电模式，之后可用 M605 S<mode> 更改。
  #define DEFAULT_DUAL_X_CARRIAGE_MODE DXC_AUTO_PARK_MODE

  // 复制模式下的默认 X 偏移（通常设为打印床宽度的一半）
  #define DEFAULT_DUPLICATION_X_OFFSET 100

  // M605 模式切换命令后执行的默认操作。通常为 G28X 以应用新模式。
  //#define EVENT_GCODE_IDEX_AFTER_MODECHANGE "G28X"
#endif

/**
 * 多步进电机 / 多限位开关
 *
 * 定义 X2_DRIVER_TYPE 时，表示 X 和 X2 电机协同工作。
 * 以下关于 X 的说明也适用于 Y 和 Z 的多步进电机设置。
 * 限位开关偏移可用 'M666 X<offset> Y<offset> Z<offset>' 修改并存入 EEPROM。
 *
 * - 若 X2 电机需要与 X 相反的 DIR 信号，启用 INVERT_X2_VS_X_DIR。
 *
 * - 若第二个电机有自己的限位开关（带可调偏移），启用 X_DUAL_ENDSTOPS。
 *
 *   - 额外的限位开关会包含在 'M119' 的输出中。
 *
 *   - 将 X_DUAL_ENDSTOP_ADJUSTMENT 设为 X2 限位开关的已知误差。
 *     在 'G28' / 'G28 X' 时应用于 X2 电机。
 *     通过归位 X 并测量误差获得偏移。
 *     也可用 'M666 X<offset>' 设置，并用 'M500' 存入 EEPROM。
 *
 *   - 用 X2_USE_ENDSTOP 按名称设置限位开关插座。(_XMIN_, _XMAX_, _YMIN_, _YMAX_, _ZMIN_, _ZMAX_)
 */
#if HAS_X2_STEPPER && DISABLED(DUAL_X_CARRIAGE)
  //#define INVERT_X2_VS_X_DIR        // X2 方向信号与 X 相反
  //#define X_DUAL_ENDSTOPS           // X2 有自己的限位开关
  #if ENABLED(X_DUAL_ENDSTOPS)
    #define X2_USE_ENDSTOP    _XMAX_  // X2 限位开关主板插座。别忘了启用 USE_*_PLUG。
    #define X2_ENDSTOP_ADJUSTMENT  0  // X2 相对于 X 限位开关的偏移
  #endif
#endif

#if HAS_DUAL_Y_STEPPERS
  #define INVERT_Y2_VS_Y_DIR        // Y2 方向信号与 Y 相反
  //#define Y_DUAL_ENDSTOPS           // Y2 有自己的限位开关
  #if ENABLED(Y_DUAL_ENDSTOPS)
    #define Y2_USE_ENDSTOP    _YMAX_  // Y2 限位开关主板插座。别忘了启用 USE_*_PLUG。
    #define Y2_ENDSTOP_ADJUSTMENT  0  // Y2 相对于 Y 限位开关的偏移
  #endif
#endif

//
// 多 Z 步进电机
//
#ifdef Z2_DRIVER_TYPE
  //#define INVERT_Z2_VS_Z_DIR        // Z2 方向信号与 Z 相反

  //#define Z_MULTI_ENDSTOPS          // 其他 Z 轴有自己的限位开关
  #if ENABLED(Z_MULTI_ENDSTOPS)
    #define Z2_USE_ENDSTOP   _XMAX_   // Z2 限位开关主板插座。别忘了启用 USE_*_PLUG。
    #define Z2_ENDSTOP_ADJUSTMENT 0   // Z2 相对于 Z 限位开关的偏移
  #endif
  #ifdef Z3_DRIVER_TYPE
    //#define INVERT_Z3_VS_Z_DIR      // Z3 方向信号与 Z 相反
    #if ENABLED(Z_MULTI_ENDSTOPS)
      #define Z3_USE_ENDSTOP   _YMAX_ // Z3 限位开关主板插座。别忘了启用 USE_*_PLUG。
      #define Z3_ENDSTOP_ADJUSTMENT 0 // Z3 相对于 Z 限位开关的偏移
    #endif
  #endif
  #ifdef Z4_DRIVER_TYPE
    //#define INVERT_Z4_VS_Z_DIR      // Z4 方向信号与 Z 相反
    #if ENABLED(Z_MULTI_ENDSTOPS)
      #define Z4_USE_ENDSTOP   _ZMAX_ // Z4 限位开关主板插座。别忘了启用 USE_*_PLUG。
      #define Z4_ENDSTOP_ADJUSTMENT 0 // Z4 相对于 Z 限位开关的偏移
    #endif
  #endif
#endif

// 用两个同步步进电机驱动 E 轴
//#define E_DUAL_STEPPER_DRIVERS
#if ENABLED(E_DUAL_STEPPER_DRIVERS)
  //#define INVERT_E1_VS_E0_DIR       // E 方向信号相反
#endif

// 用 M380 激活当前挤出机上的电磁阀。用 M381 全部禁用。
// 为每个带电磁阀的挤出机定义 SOL0_PIN、SOL1_PIN 等。
//#define EXT_SOLENOID

// @section homing

/**
 * 归位流程
 * 归位 (G28) 向限位开关方向执行无限位移动，以确定
 * 工具头相对于工作空间的位置。
 */

#define SENSORLESS_BACKOFF_MM  { 5, 5, 0, 0, 0, 0 }  // (linear=mm, rotational=°) 无感归位前从限位开关回退的距离

#define HOMING_BUMP_MM      { 10, 10, 2, 2, 2 } // (linear=mm, rotational=°) 首次撞击后从限位开关回退的距离
#define HOMING_BUMP_DIVISOR { 2, 2, 4, 4, 4 } // 再次撞击速度除数（除以归位进给速度）

//#define HOMING_BACKOFF_POST_MM { 5, 5, 0, 0, 0, 0 }  // (linear=mm, rotational=°) 归位后从限位开关回退的距离

//#define QUICK_HOME                            // 若 G28 包含 XY，先做一次对角移动
//#define HOME_Y_BEFORE_X                     // 若 G28 包含 XY，先归位 Y 再归位 X
//#define HOME_Z_FIRST                        // 先归位 Z。需要 Z-MIN 限位开关（而非探针）。
//#define CODEPENDENT_XY_HOMING               // 若 X/Y 不先归位 Y/X 就无法归位

// @section bltouch

#if ENABLED(BLTOUCH)
  /**
   * 建议使用默认值；若有特殊用途，可使用以下定义
   * 不要启用探针可能不理解的设置。克隆品可能无法识别
   * 高级命令。
   *
   * 注意：若探针未伸出，请执行“复位”和“自检”，然后检查
   *       棕、红、橙线的接线。
   *
   * 注意：若探针的触发信号未被识别，通常是因为
   *       黑线和白线需要对调。它们不像真正的开关那样“可互换”。
   *       因此请先检查接线。
   *
   * 适用于所有 BLTouch 及克隆探针的设置：
   */

  // 安全：探针需要时间来识别命令。
  //         最小命令延迟 (ms)。如有需要请启用并增大。
  //#define BLTOUCH_DELAY 500

  /**
   * 适用于 BLTOUCH Classic 1.2、1.3 或 BLTouch Smart 1.0、2.0、2.2、3.0、3.1 及大多数克隆品的设置：
   */

  // 功能：伸出后切换到 SW 模式。可使输出脉冲更长。在某些
  //          特殊情况下有用，例如有噪声或滤波的输入配置。
  //#define BLTOUCH_FORCE_SW_MODE

  /**
   * BLTouch Smart 3.0 和 3.1 的设置
   * 概述：
   *   - 电压模式：5V 和 OD（开漏 - “逻辑电压无关”）输出模式
   *   - 高速模式
   *   - 禁用 LCD 电压选项
   */

  /**
   * 危险：除非连接到 5V 兼容控制器，否则不要启用 5V 模式！
   * V3.0 或 3.1：在 Marlin 启动时将默认模式设为 5V 模式。
   * 若禁用，3.0 上硬编码默认为 OD 模式
   * 启动时 Marlin 会将其 EEPROM 与此值比较。若所选模式
   * 不同，将在初始化时完成一次模式设置的 EEPROM 写入。
   * 无论如何，使用下方选项强制向 V3.1 探针写入 EEPROM。
   */
  //#define BLTOUCH_SET_5V_MODE

  // 安全：在 LCD 菜单中启用电压模式设置。
  //#define BLTOUCH_LCD_VOLTAGE_MENU

  /**
   * 安全：连接电压模式未知的探针时启用。
   * V3.0：在 Marlin 启动时将探针设为上方所选模式。3.0 上的 5V 模式需要此项
   * V3.1：在 Marlin 启动时强制将模式未知的探针设为所选模式（= 写入探针 EEPROM）
   * 为延长探针寿命，使用一次后请关闭并重新烧录。
   */
  //#define BLTOUCH_FORCE_MODE_SET

  /**
   * 启用“高速”探测选项。
   * 危险：若探针有时失灵请禁用。仅适用于稳定且调试良好的系统。
   * 此功能为 Z 轴移动极快的 Delta 机设计；但高速笛卡尔机
   * 可能也能使用。若机器无法足够快地抬起 Z，BLTouch 可能进入报警状态。
   *
   * 在此设置默认状态，可用 'M401 S' 或界面更改，M500 保存，M502 复位。
   */
  //#define BLTOUCH_HS_MODE true

  #ifdef BLTOUCH_HS_MODE
    // 探针 Z 偏移 (M851 Z) 是探针触发时的高度。
    // 此值必须足够大，以使探针针不接触热床并防止
    // 其被热床夹卡住。
    #define BLTOUCH_HS_EXTRA_CLEARANCE    7 // 额外 Z 间隙
  #endif

#endif // BLTOUCH

// @section calibration

/**
 * Z 步进电机自动校准
 * 添加 G34 命令，使用热床探针对多个 Z 步进电机进行校准。
 */
//#define Z_STEPPER_AUTO_ALIGN
#if ENABLED(Z_STEPPER_AUTO_ALIGN)
  /**
   * 定义 Z1、Z2 [, Z3 [, Z4]] 的探针 X、Y 位置
   * 这些位置是相对于机器的，不会随 M206 归位偏移而移动！
   * 若未定义，将使用探针限位。
   * 可用 'M422 S<index> X<pos> Y<pos>' 覆盖。
   */
  //#define Z_STEPPER_ALIGN_XY { {  10, 190 }, { 100,  10 }, { 190, 190 } }

  /**
   * 自动计算的探针位置的方向。
   * 用 'M422 S<index> X<pos> Y<pos>' 覆盖 Z 步进电机校准点
   *
   * 2 Steppers:  (0)     (1)
   *               |       |   2   |
   *               | 1   2 |       |
   *               |       |   1   |
   *
   * 3 Steppers:  (0)     (1)     (2)     (3)
   *               |   3   | 1     | 2   1 |     2 |
   *               |       |     3 |       | 3     |
   *               | 1   2 | 2     |   3   |     1 |
   *
   * 4 Steppers:  (0)     (1)     (2)     (3)
   *               | 4   3 | 1   4 | 2   1 | 3   2 |
   *               |       |       |       |       |
   *               | 1   2 | 2   3 | 3   4 | 4   1 |
   */
  #ifndef Z_STEPPER_ALIGN_XY
    //#define Z_STEPPERS_ORIENTATION 0
  #endif

  /**
   * Z 步进电机位置，用于在热床校准中更快收敛。
   * 需要 3 或 4 个 Z 步进电机。
   *
   * 定义 Z1、Z2、Z3... 的步进电机 XY 位置，对应于热床滑架上
   * 的螺丝位置，按步进电机驱动器顺序每个 Z 步进电机
   * 一个位置。
   */
  //#define Z_STEPPER_ALIGN_STEPPER_XY { { 210.7, 102.5 }, { 152.6, 220.0 }, { 94.5, 102.5 } }

  #ifndef Z_STEPPER_ALIGN_STEPPER_XY
    // 放大系数。当步进电机（主轴）位置比测试点更靠外时，
    // 用于放大或缩小校正步长。
    #define Z_STEPPER_ALIGN_AMP 1.0       // 使用 > 1.0 的值。注意：这可能导致不稳定！
  #endif

  // 在 300mm 热床上，5% 的坡度会导致约 1.5cm 的偏差
  #define G34_MAX_GRADE              5    // (%) G34 能处理的最大倾斜度
  #define Z_STEPPER_ALIGN_ITERATIONS 5    // 校准过程中应用的迭代次数
  #define Z_STEPPER_ALIGN_ACC        0.02 // 若精度优于此值则提前停止迭代
  #define RESTORE_LEVELING_AFTER_G34      // G34 完成后恢复调平？
  // G34 之后，重新归位 Z (G28 Z) 还是仅根据最后一次探针高度计算？
  // 重新归位在复现实际 'G28 Z' 归位高度时可能更精确，尤其在不平的热床上。
  #define HOME_AFTER_G34
#endif

//
// 添加 G35 命令读取热床四角以帮助调整螺丝。需要热床探针。
//
//#define ASSISTED_TRAMMING
#if ENABLED(ASSISTED_TRAMMING)

  // 定义 3 到 9 个探测点。
  #define TRAMMING_POINT_XY { {  20, 20 }, { 180,  20 }, { 180, 180 }, { 20, 180 } }

  // 定义探测点的位置名称。
  #define TRAMMING_POINT_NAME_1 "Front-Left"
  #define TRAMMING_POINT_NAME_2 "Front-Right"
  #define TRAMMING_POINT_NAME_3 "Back-Right"
  #define TRAMMING_POINT_NAME_4 "Back-Left"

  #define RESTORE_LEVELING_AFTER_G35    // 启用后在操作结束后恢复调平设置
  //#define REPORT_TRAMMING_MM          // 上报每个点相对于第一个点的 Z 偏差 (mm)

  //#define ASSISTED_TRAMMING_WIZARD    // 在 LCD 菜单中添加校平向导

  //#define ASSISTED_TRAMMING_WAIT_POSITION { X_CENTER, Y_CENTER, 30 } // 将喷嘴移开以便调整

  /**
   * 螺纹规格：
   *   M3: 30 = 顺时针, 31 = 逆时针
   *   M4: 40 = 顺时针, 41 = 逆时针
   *   M5: 50 = 顺时针, 51 = 逆时针
   */
  #define TRAMMING_SCREW_THREAD 30

#endif

// @section motion control

/**
 * 定时长运动控制 -- 实验性功能
 * 使用 G 代码 M493 启用/禁用并设置参数。
 */
//#define FT_MOTION
#if ENABLED(FT_MOTION)
  #define FTM_DEFAULT_MODE         ftMotionMode_ENABLED // 定时长控制的默认模式。(枚举见 ft_types.h)
  #define FTM_DEFAULT_DYNFREQ_MODE dynFreqMode_DISABLED // 动态频率计算的默认模式。(枚举见 ft_types.h)
  #define FTM_SHAPING_DEFAULT_X_FREQ 37.0f              // (Hz) 输入整形器使用的默认峰值频率。
  #define FTM_SHAPING_DEFAULT_Y_FREQ 37.0f              // (Hz) 输入整形器使用的默认峰值频率。
  #define FTM_LINEAR_ADV_DEFAULT_ENA false              // 默认启用线性提前量 (true) 或禁用 (false)。
  #define FTM_LINEAR_ADV_DEFAULT_K    0.0f              // 默认线性提前量增益。
  #define FTM_SHAPING_ZETA            0.1f              // 输入整形器使用的 Zeta。
  #define FTM_SHAPING_V_TOL           0.05f             // EI 输入整形器使用的振动容差。

  /**
   * 高级配置
   */
  #define FTM_BATCH_SIZE 100                            // 轨迹生成的批量大小；
                                                        // 为 Ulendo FBS 时取窗口大小的一半。
  #define FTM_FS           1000                         // (Hz) 轨迹生成的频率。(1 / FTM_TS)
  #define FTM_TS              0.001f                    // (s) 轨迹生成的时间步长。(1 / FTM_FS)
  #define FTM_STEPPER_FS  20000                         // (Hz) 步进电机 I/O 更新的频率。
  #define FTM_MIN_TICKS ((STEPPER_TIMER_RATE) / (FTM_STEPPER_FS)) // 步进之间的最小步进电机节拍数。
  #define FTM_MIN_SHAPE_FREQ 10                         // 最小整形频率。
  #define FTM_ZMAX          100                         // 整形函数的最大延迟（仅限偶数！）。
                                                        // 计算方式：
                                                        //    1/2 * (FTM_FS / FTM_MIN_SHAPE_FREQ) 用于 ZV。
                                                        //    (FTM_FS / FTM_MIN_SHAPE_FREQ) 用于 ZVD、MZV。
                                                        //    3/2 * (FTM_FS / FTM_MIN_SHAPE_FREQ) 用于 2HEI。
                                                        //    2 * (FTM_FS / FTM_MIN_SHAPE_FREQ) 用于 3HEI。
  #define FTM_STEPS_PER_UNIT_TIME 20                    // 单位时间内的插值步进电机指令数。
                                                        // 计算方式 (FTM_STEPPER_FS / FTM_FS)。
  #define FTM_CTS_COMPARE_VAL 10                        // 插值算法中使用的比较值。
                                                        // 计算方式 (FTM_STEPS_PER_UNIT_TIME / 2)。
  // 可通过配置这些值来调整 loop() 的持续时间。
  #define FTM_STEPS_PER_LOOP 60                         // 每次 loop() 生成的步进电机指令数。
  #define FTM_POINTS_PER_LOOP 100                       // 每次 loop() 生成的轨迹点数量。

  // 可通过配置此值来调整消耗命令缓冲区的时间。
  // 若步进运动不平稳，可尝试增大此值。
  #define FTM_STEPPERCMD_BUFF_SIZE 1000                 // 步进电机命令缓冲区的大小。
#endif

/**
 * 输入整形 -- 实验性功能
 *
 * 用于 X 和/或 Y 轴移动的零振动 (ZV) 输入整形。
 *
 * 此选项会占用大量 SRAM 用于步进缓冲区。缓冲区大小
 * 根据 SHAPING_FREQ_[XY]、DEFAULT_AXIS_STEPS_PER_UNIT、
 * DEFAULT_MAX_FEEDRATE 和 ADAPTIVE_STEP_SMOOTHING 自动计算。默认计算方式
 * 可通过设置 SHAPING_MIN_FREQ 和/或 SHAPING_MAX_FEEDRATE 覆盖。
 * 频率越高、进给速度越低，缓冲区越小。
 * 若运行时缓冲区过小，高速移动期间输入整形的
 * 效果会减弱。
 *
 * 使用 M593 D<factor> F<frequency> 调整：
 *
 *  D<factor>    设置 zeta/阻尼系数。若未指定轴 (X、Y 等)，则对所有轴生效。
 *  F<frequency> 设置频率。若未指定轴 (X、Y 等)，则对所有轴生效。
 *  T[map]       输入整形类型，0:ZV、1:EI、2:2H EI（尚未实现）
 *  X<1>         仅对 X 轴设置给定参数。
 *  Y<1>         仅对 Y 轴设置给定参数。
 */
//#define INPUT_SHAPING_X
//#define INPUT_SHAPING_Y
#if EITHER(INPUT_SHAPING_X, INPUT_SHAPING_Y)
  #if ENABLED(INPUT_SHAPING_X)
    #define SHAPING_FREQ_X  40          // (Hz) X 轴的默认主共振频率。
    #define SHAPING_ZETA_X  0.15f       // X 轴的阻尼比（范围：0.0 = 无阻尼 到 1.0 = 临界阻尼）。
  #endif
  #if ENABLED(INPUT_SHAPING_Y)
    #define SHAPING_FREQ_Y  40          // (Hz) Y 轴的默认主共振频率。
    #define SHAPING_ZETA_Y  0.15f       // Y 轴的阻尼比（范围：0.0 = 无阻尼 到 1.0 = 临界阻尼）。
  #endif
  //#define SHAPING_MIN_FREQ  20        // 默认为整形频率的最小值。覆盖此值可影响 SRAM 占用。
  //#define SHAPING_MAX_STEPRATE 10000  // 默认为整形各轴的最大总步进率。覆盖此值可影响 SRAM 占用。
  //#define SHAPING_MENU                // 在 LCD 中添加菜单以设置整形参数。
#endif

// @section motion

#define AXIS_RELATIVE_MODES { false, false, false, false, false }

// 为间距较大的成对喷嘴添加“重复”选项
//#define MULTI_NOZZLE_DUPLICATION

// 步进电机驱动器默认需要高电平有效信号，但某些大功率驱动器需要低电平有效信号才能步进。
#define STEP_STATE_X HIGH
#define STEP_STATE_Y HIGH
#define STEP_STATE_Z HIGH
#define STEP_STATE_I HIGH
#define STEP_STATE_J HIGH
#define STEP_STATE_K HIGH
#define STEP_STATE_U HIGH
#define STEP_STATE_V HIGH
#define STEP_STATE_W HIGH
#define STEP_STATE_E HIGH

/**
 * 空闲时关闭步进电机
 * 启用 DISABLE_IDLE_* 可在空闲一段时间后关闭各轴步进电机。
 * 默认超时时长可用 M18 和 M84 覆盖。设为 0 表示无超时。
 */
#define DEFAULT_STEPPER_TIMEOUT_SEC 3600
#define DISABLE_IDLE_X
#define DISABLE_IDLE_Y
#define DISABLE_IDLE_Z    // 若喷嘴可能落到已打印件上，请禁用！
#define DISABLE_IDLE_I
#define DISABLE_IDLE_J
#define DISABLE_IDLE_K
//#define DISABLE_IDLE_U
//#define DISABLE_IDLE_V
//#define DISABLE_IDLE_W
#define DISABLE_IDLE_E    // 关闭所有空闲的挤出机

// 打印移动和空移的默认最小进给速度
#define DEFAULT_MINIMUMFEEDRATE             0.0     // (mm/s) 最小进给速度。用 M205 S 设置。
#define DEFAULT_MINTRAVELFEEDRATE           0.0     // (mm/s) 最小空移进给速度。用 M205 T 设置。
#if HAS_ROTATIONAL_AXES
  #define DEFAULT_ANGULAR_MINIMUMFEEDRATE   0.0     // (°/s) 仅旋转移动的最小进给速度。用 M205 P 设置。
  #define DEFAULT_ANGULAR_MINTRAVELFEEDRATE 0.0     // (°/s) 仅旋转移动的最小空移进给速度。用 M205 Q 设置。
#endif

// 缓冲区被清空时，一段线段所需的最短时间
#define DEFAULT_MINSEGMENTTIME        20000   // (µs) 用 M205 B 设置。

// 若前瞻缓冲区（默认）半满，则降低机器速度。
// 缓冲区越大，减速除数应越大。
#define SLOWDOWN
#if ENABLED(SLOWDOWN)
  #define SLOWDOWN_DIVISOR 2
#endif

/**
 * XY 频率限制
 * 通过限制小幅之字形填充移动的频率来减小共振。
 * 参见 https://hydraraptor.blogspot.com/2010/12/frequency-limit.html
 * 使用 M201 F<freq> G<min%> 可在运行时更改限制值。
 */
//#define XY_FREQUENCY_LIMIT      10 // (Hz) 小幅之字形填充移动的最高频率。用 M201 F<hertz> 设置。
#ifdef XY_FREQUENCY_LIMIT
  #define XY_FREQUENCY_MIN_PERCENT 5 // (percent) 应用的最小 FR 百分比。用 M201 G<min%> 设置。
#endif

// 规划器最小节点速度。设定规划器在缓冲区末端
// 和所有停止点所规划的默认最低速度。该值不应明显大于零，
// 且仅当用户机器在极慢速运行时出现异常行为才应修改。
#define MINIMUM_PLANNER_SPEED 0.05 // (mm/s)

//
// 反向间隙补偿
// 在改变方向时为各轴增加额外移动量，以补偿反向间隙。
//
//#define BACKLASH_COMPENSATION
#if ENABLED(BACKLASH_COMPENSATION)
  // 定义反向间隙距离和校正值。
  // 若启用了 BACKLASH_GCODE，这些值即为默认值。
  #define BACKLASH_DISTANCE_MM { 0, 0, 0 } // (linear=mm, rotational=°) 每个直线轴一个值
  #define BACKLASH_CORRECTION    0.0       // 0.0 = 不校正；1.0 = 完全校正

  // 在 CORE 运动学下为电机换向添加步进
  //#define CORE_BACKLASH

  // 设置 BACKLASH_SMOOTHING_MM 可将反向间隙校正分散到多个线段上
  // 以减少打印瑕疵。（启用此功能会消耗较多内存和计算资源！）
  //#define BACKLASH_SMOOTHING_MM 3 // (mm)

  // 添加反向间隙值的运行时配置和调整 (M425)
  //#define BACKLASH_GCODE

  #if ENABLED(BACKLASH_GCODE)
    // 在探测时 (G29) 测量 Z 轴反向间隙，并用 "M425 Z" 设置
    #define MEASURE_BACKLASH_WHEN_PROBING

    #if ENABLED(MEASURE_BACKLASH_WHEN_PROBING)
      // 测量时，探针会以 BACKLASH_MEASUREMENT_RESOLUTION
      // 为步长，从接触点最多移开 BACKLASH_MEASUREMENT_LIMIT
      // mm，同时检测接触是否断开。
      #define BACKLASH_MEASUREMENT_LIMIT       0.5   // (mm)
      #define BACKLASH_MEASUREMENT_RESOLUTION  0.005 // (mm)
      #define BACKLASH_MEASUREMENT_FEEDRATE    Z_PROBE_FEEDRATE_SLOW // (mm/min)
    #endif
  #endif
#endif

/**
 * 反向间隙、位置和热端偏移自动校准
 *
 * 启用 G425 可使用安装在热床上的导电立方体、
 * 螺栓或垫圈进行自动校准。
 *
 * G425 用探针触碰热床上校准物的顶面和侧面，
 * 测量并/或校正位置偏移、轴反向间隙
 * 和热端偏移。
 *
 * 注意：HOTEND_OFFSET 和 CALIBRATION_OBJECT_CENTER 必须设置在
 *       真实值 ±5mm 以内，G425 才能成功。
 */
//#define CALIBRATION_GCODE
#if ENABLED(CALIBRATION_GCODE)

  //#define CALIBRATION_SCRIPT_PRE  "M117 Starting Auto-Calibration\nT0\nG28\nG12\nM117 Calibrating..."
  //#define CALIBRATION_SCRIPT_POST "M500\nM117 Calibration data saved"

  #define CALIBRATION_MEASUREMENT_RESOLUTION     0.01 // mm

  #define CALIBRATION_FEEDRATE_SLOW             60    // mm/min
  #define CALIBRATION_FEEDRATE_FAST           1200    // mm/min
  #define CALIBRATION_FEEDRATE_TRAVEL         3000    // mm/min

  // 以下参数对应喷嘴尖端的锥形部分。
  #define CALIBRATION_NOZZLE_TIP_HEIGHT          1.0  // mm
  #define CALIBRATION_NOZZLE_OUTER_DIAMETER      2.0  // mm

  // 取消注释可启用报告（"G425 V" 需要此项，但会占用 PROGMEM）。
  //#define CALIBRATION_REPORTING

  // 立方体/螺栓/垫圈在热床上的真实位置和尺寸。
  #define CALIBRATION_OBJECT_CENTER     { 264.0, -22.0,  -2.0 } // mm
  #define CALIBRATION_OBJECT_DIMENSIONS {  10.0,  10.0,  10.0 } // mm

  // 将探针无法触及的各个面注释掉。为获得最佳
  // 自动校准结果，所有面都必须可触及。
  #define CALIBRATION_MEASURE_RIGHT
  #define CALIBRATION_MEASURE_FRONT
  #define CALIBRATION_MEASURE_LEFT
  #define CALIBRATION_MEASURE_BACK

  //#define CALIBRATION_MEASURE_IMIN
  //#define CALIBRATION_MEASURE_IMAX
  //#define CALIBRATION_MEASURE_JMIN
  //#define CALIBRATION_MEASURE_JMAX
  //#define CALIBRATION_MEASURE_KMIN
  //#define CALIBRATION_MEASURE_KMAX
  //#define CALIBRATION_MEASURE_UMIN
  //#define CALIBRATION_MEASURE_UMAX
  //#define CALIBRATION_MEASURE_VMIN
  //#define CALIBRATION_MEASURE_VMAX
  //#define CALIBRATION_MEASURE_WMIN
  //#define CALIBRATION_MEASURE_WMAX

  // 仅当中心是平面时，在正中心探测才有效。若
  // 探测的是螺钉头或中空垫圈，请在靠近边缘处探测。
  //#define CALIBRATION_MEASURE_AT_TOP_EDGES

  // 定义校准期间读取的引脚
  #ifndef CALIBRATION_PIN
    //#define CALIBRATION_PIN -1            // 在此定义以覆盖默认引脚
    #define CALIBRATION_PIN_INVERTING false // 设为 true 以反转自定义引脚
    //#define CALIBRATION_PIN_PULLDOWN
    #define CALIBRATION_PIN_PULLUP
  #endif
#endif

/**
 * 多步进以突发方式发送步进信号，降低高步进率下的 MCU 占用。
 * 这使进给速度可超出 MCU 原本能支持的范围。
 */
#define MULTISTEPPING_LIMIT   16  //: [1, 2, 4, 8, 16, 32, 64, 128]

/**
 * 自适应步进平滑可提高多轴移动的分辨率，尤其在步进频率
 * 低于 1kHz (AVR) 或 10kHz (ARM) 时，多轴移动中各轴之间的混叠会产生可听
 * 见的振动和表面瑕疵。该算法会自适应地在
 * 最低的步进频率下提供最佳的步进平滑效果。
 */
//#define ADAPTIVE_STEP_SMOOTHING

/**
 * 自定义细分
 * 根据需要为你的配置进行覆盖。最多支持 3 个 MS 引脚。
 */
//#define MICROSTEP1 LOW,LOW,LOW
//#define MICROSTEP2 HIGH,LOW,LOW
//#define MICROSTEP4 LOW,HIGH,LOW
//#define MICROSTEP8 HIGH,HIGH,LOW
//#define MICROSTEP16 LOW,LOW,HIGH
//#define MICROSTEP32 HIGH,LOW,HIGH

// 细分设置（需要具有 X_MS1、X_MS2 等命名引脚的主板）
#define MICROSTEP_MODES { 16, 16, 16, 16, 16, 16 } // [1,2,4,8,16]

/**
 *  @section  stepper motor current
 *
 *  部分主板支持通过固件设置步进电机电流。
 *
 *  上电时的电机电流由以下方式设置：
 *    PWM_MOTOR_CURRENT - 供 MINIRAMBO 与 ULTIMAIN_2 使用
 *                         已知兼容芯片：A4982
 *    DIGIPOT_MOTOR_CURRENT - 供 BQ_ZUM_MEGA_3D、RAMBO 与 SCOOVO_X9H 使用
 *                         已知兼容芯片：AD5206
 *    DAC_MOTOR_CURRENT_DEFAULT - 供 PRINTRBOARD_REVF 与 RIGIDBOARD_V2 使用
 *                         已知兼容芯片：MCP4728
 *    DIGIPOT_I2C_MOTOR_CURRENTS - 供 5DPRINT、AZTEEG_X3_PRO、AZTEEG_X5_MINI_WIFI、MIGHTYBOARD_REVE 使用
 *                         已知兼容芯片：MCP4451、MCP4018
 *
 *  电机电流也可通过 M907 - M910 以及 LCD 设置。
 *    M907 - 适用于所有主板。
 *    M908 - BQ_ZUM_MEGA_3D、RAMBO、PRINTRBOARD_REVF、RIGIDBOARD_V2 与 SCOOVO_X9H
 *    M909、M910 与 LCD - 仅适用于 PRINTRBOARD_REVF 与 RIGIDBOARD_V2
 */
//#define PWM_MOTOR_CURRENT { 1300, 1300, 1250 }          // 数值单位为毫安
//#define DIGIPOT_MOTOR_CURRENT { 135,135,135,135,135 }   // 取值 0-255 (RAMBO 135 = ~0.75A, 185 = ~1A)
//#define DAC_MOTOR_CURRENT_DEFAULT { 70, 80, 90, 80 }    // 默认驱动百分比 - X、Y、Z、E 轴

/**
 * 基于 I2C 的 DIGIPOT（例如 Azteeg X3 Pro）
 */
//#define DIGIPOT_MCP4018             // 需要 https://github.com/felias-fogg/SlowSoftI2CMaster
//#define DIGIPOT_MCP4451
#if EITHER(DIGIPOT_MCP4018, DIGIPOT_MCP4451)
  #define DIGIPOT_I2C_NUM_CHANNELS 8  // 5DPRINT:4   AZTEEG_X3_PRO:8   MKS_SBASE:5   MIGHTYBOARD_REVE:5

  // 实际电机电流，单位为安培。数值个数必须与 DIGIPOT_I2C_NUM_CHANNELS 一致。
  // 这些值对应实际的驱动器，因此若更改顺序请务必注意。
  #define DIGIPOT_I2C_MOTOR_CURRENTS { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 } // AZTEEG_X3_PRO

  //#define DIGIPOT_USE_RAW_VALUES    // 使用 DIGIPOT_MOTOR_CURRENT 的原始滑动电阻值（而非 A4988 电机电流）

  /**
   * 常用从机地址：
   *
   *                        A   (A 已移位)    B   (B 已移位)   IC
   * Smoothie              0x2C (0x58)       0x2D (0x5A)       MCP4451
   * AZTEEG_X3_PRO         0x2C (0x58)       0x2E (0x5C)       MCP4451
   * AZTEEG_X5_MINI        0x2C (0x58)       0x2E (0x5C)       MCP4451
   * AZTEEG_X5_MINI_WIFI         0x58              0x5C        MCP4451
   * MIGHTYBOARD_REVE      0x2F (0x5E)                         MCP4018
   */
  //#define DIGIPOT_I2C_ADDRESS_A 0x2C  // 第一个 DIGIPOT 的未移位从机地址
  //#define DIGIPOT_I2C_ADDRESS_B 0x2D  // 第二个 DIGIPOT 的未移位从机地址
#endif

//===========================================================================
//============================= 附加功能 =============================
//===========================================================================

// @section lcd

#if HAS_MANUAL_MOVE_MENU
  #define MANUAL_FEEDRATE { 50*60, 50*60, 4*60, 2*60 } // (mm/min) 面板上沿 X、Y、Z、E 轴手动移动的进给速度
  #define FINE_MANUAL_MOVE 0.025    // (mm) 多数机器上作用于 Z 轴的最小手动移动量 (< 0.1mm)
  #if IS_ULTIPANEL
    #define MANUAL_E_MOVES_RELATIVE // 显示挤出机移动距离而非"位置"
    #define ULTIPANEL_FEEDMULTIPLY  // 编码器在状态屏上设置进给速度倍率
  #endif
#endif

// 编码器转得越快，数值变化越快
#define ENCODER_RATE_MULTIPLIER
#if ENABLED(ENCODER_RATE_MULTIPLIER)
  #define ENCODER_10X_STEPS_PER_SEC   30  // (steps/s) 10 倍速时的编码器速率
  #define ENCODER_100X_STEPS_PER_SEC  80  // (steps/s) 100 倍速时的编码器速率
#endif

// 在状态屏上更改进给速度时发出提示音
//#define BEEP_ON_FEEDRATE_CHANGE
#if ENABLED(BEEP_ON_FEEDRATE_CHANGE)
  #define FEEDRATE_CHANGE_BEEP_DURATION   10
  #define FEEDRATE_CHANGE_BEEP_FREQUENCY 440
#endif

//
// LCD 背光超时
//
//#define LCD_BACKLIGHT_TIMEOUT_MINS 1  // (minutes) 关闭背光前的超时时间

#if HAS_BED_PROBE && EITHER(HAS_MARLINUI_MENU, HAS_TFT_LVGL_UI)
  //#define PROBE_OFFSET_WIZARD       // 在 LCD 菜单中添加探针 Z 偏移校准选项
  #if ENABLED(PROBE_OFFSET_WIZARD)
    /**
     * 启用后可在启动向导时初始化探针 Z 偏移。
     * 使用略高于预估喷嘴到探针 Z 偏移的高度。
     * 例如，偏移为 -5 时，可考虑使用 -4 作为起始高度。
     */
    //#define PROBE_OFFSET_WIZARD_START_Z -4.0

    // 设置便于校准的位置（探测点以及喷嘴/热床间距）
    //#define PROBE_OFFSET_WIZARD_XY_POS { X_CENTER, Y_CENTER }
  #endif
#endif

#if HAS_MARLINUI_MENU

  #if HAS_BED_PROBE
    // 在探针偏移菜单中添加校准，以补偿 X 轴扭曲。
    //#define X_AXIS_TWIST_COMPENSATION
    #if ENABLED(X_AXIS_TWIST_COMPENSATION)
      /**
       * 启用后可在启动向导时初始化探针 Z 偏移。
       * 使用略高于预估喷嘴到探针 Z 偏移的高度。
       * 例如，偏移为 -5 时，可考虑使用 -4 作为起始高度。
       */
      #define XATC_START_Z 0.0
      #define XATC_MAX_POINTS 3             // 向导中要探测的点数
      #define XATC_Y_POSITION Y_CENTER      // (mm) 要探测的 Y 位置
      #define XATC_Z_OFFSETS { 0, 0, 0 }    // X 轴采样点的 Z 偏移
    #endif

    // 在运动菜单中显示伸出/收起探针选项。
    #define PROBE_DEPLOY_STOW_MENU
  #endif

  // 在 LCD 主菜单中加入一页打印机信息
  //#define LCD_INFO_MENU
  #if ENABLED(LCD_INFO_MENU)
    //#define LCD_PRINTER_INFO_IS_BOOTSCREEN // 显示开机画面而非打印机信息页
  #endif

  // 即使热床较小，也在 MarlinUI 中添加 50/100mm 移动
  //#define LARGE_MOVE_ITEMS

  // BACK 菜单项使高亮保持在顶部
  //#define TURBO_BACK_MENU_ITEM

  // 在顶层插入预热菜单，便于快速访问
  //#define PREHEAT_SHORTCUT_MENU_ITEM

#endif // HAS_MARLINUI_MENU

#if HAS_DISPLAY
  /**
   * *** 厂商请阅读 ***
   *
   * Marlin 允许你为图形 LCD 添加自定义开机画面。
   * 启用此选项后，Marlin 会先显示你的自定义画面，随后
   * 显示带版本号和网址的标准 Marlin 标志。
   *
   * 我们鼓励你使用这一新特性，同时也恳请你
   * 保留未经修改的 Marlin 开机画面。
   */
  #if ANY(HAS_MARLINUI_U8GLIB, TOUCH_UI_FTDI_EVE, IS_DWIN_MARLINUI)
    #define SHOW_BOOTSCREEN                 // 启动时显示 Marlin 开机画面。** 量产请启用 **
    #if ENABLED(SHOW_BOOTSCREEN)
      #define BOOTSCREEN_TIMEOUT 4000       // (ms) 显示开机画面的总时长
      #if EITHER(HAS_MARLINUI_U8GLIB, TFT_COLOR_UI)
        #define BOOT_MARLIN_LOGO_SMALL      // 在开机画面上显示较小的 Marlin 标志（可节省大量 flash）
      #endif
      //#define SHOW_CUSTOM_BOOTSCREEN      // 启动时显示 Marlin/_Bootscreen.h 中的位图。
    #endif
    #if HAS_MARLINUI_U8GLIB
      //#define CUSTOM_STATUS_SCREEN_IMAGE  // 在状态屏上显示 Marlin/_Statusscreen.h 中的位图。
    #endif
  #endif

  //#define SOUND_MENU_ITEM   // 在 LCD 菜单中添加静音选项
  #define SOUND_ON_DEFAULT    // 蜂鸣器/扬声器的默认启用状态

  // 从子菜单返回状态屏的超时时间
  //#define LCD_TIMEOUT_TO_STATUS 15000   // (ms)

  // 将较长的状态消息滚动显示
  //#define STATUS_MESSAGE_SCROLLING

  // 为低优先级状态消息设置超时
  //#define STATUS_MESSAGE_TIMEOUT_SEC 30 // (seconds)

  // 在信息屏上尽可能以一位小数显示 XY
  //#define LCD_DECIMAL_SMALL_XY

  // 打印期间显示 E 轴位置（已用耗材量）
  //#define LCD_SHOW_E_TOTAL

  // 显示负温度而非 "err"
  //#define SHOW_TEMPERATURE_BELOW_ZERO

  /**
   * LED 控制菜单
   * 在 LCD 菜单中添加 LED 控制
   */
  //#define LED_CONTROL_MENU
  #if ENABLED(LED_CONTROL_MENU)
    #define LED_COLOR_PRESETS                 // 启用预设颜色菜单选项
    //#define NEO2_COLOR_PRESETS              // 启用第二个 NeoPixel 预设颜色菜单选项
    #if ENABLED(LED_COLOR_PRESETS)
      #define LED_USER_PRESET_RED        255  // 用户定义的 RED 值
      #define LED_USER_PRESET_GREEN      128  // 用户定义的 GREEN 值
      #define LED_USER_PRESET_BLUE         0  // 用户定义的 BLUE 值
      #define LED_USER_PRESET_WHITE      255  // 用户定义的 WHITE 值
      #define LED_USER_PRESET_BRIGHTNESS 255  // 用户定义的亮度
      //#define LED_USER_PRESET_STARTUP       // 启动时让打印机显示用户预设颜色
    #endif
    #if ENABLED(NEO2_COLOR_PRESETS)
      #define NEO2_USER_PRESET_RED        255 // 用户定义的 RED 值
      #define NEO2_USER_PRESET_GREEN      128 // 用户定义的 GREEN 值
      #define NEO2_USER_PRESET_BLUE         0 // 用户定义的 BLUE 值
      #define NEO2_USER_PRESET_WHITE      255 // 用户定义的 WHITE 值
      #define NEO2_USER_PRESET_BRIGHTNESS 255 // 用户定义的亮度
      //#define NEO2_USER_PRESET_STARTUP      // 启动时让打印机为第二组灯带显示用户预设颜色
    #endif
  #endif

#endif // HAS_DISPLAY

// 添加 'M73' 以设置打印任务进度，将覆盖 Marlin 内置的估算
//#define SET_PROGRESS_MANUALLY
#if ENABLED(SET_PROGRESS_MANUALLY)
  #define SET_PROGRESS_PERCENT            // 添加 'P' 参数以设置完成百分比
  #define SET_REMAINING_TIME              // 添加 'R' 参数以设置剩余时间
  //#define SET_INTERACTION_TIME          // 添加 'C' 参数以设置距下次换料或其他用户交互的时间
  //#define M73_REPORT                    // 向主机报告 M73 的值
  #if BOTH(M73_REPORT, SDSUPPORT)
    #define M73_REPORT_SD_ONLY            // 仅在从 SD 打印时报告
  #endif
#endif

// LCD 打印进度选项。可轮换显示多个时间。
#if HAS_DISPLAY && EITHER(SDSUPPORT, SET_PROGRESS_MANUALLY)
  #define SHOW_PROGRESS_PERCENT           // 显示打印进度百分比（不影响进度条）
  #define SHOW_ELAPSED_TIME               // 显示已用打印时间（前缀 'E'）
  //#define SHOW_REMAINING_TIME           // 显示预计完成时间（前缀 'R'）
  #if ENABLED(SET_INTERACTION_TIME)
    #define SHOW_INTERACTION_TIME         // 显示距下次用户交互的时间（'C' = 换料）
  #endif
  //#define PRINT_PROGRESS_SHOW_DECIMALS  // 以带小数位的方式显示/报告进度，并非所有 UI 都支持

  #if EITHER(HAS_MARLINUI_HD44780, IS_TFTGLCD_PANEL)
    //#define LCD_PROGRESS_BAR            // 在 HD44780 LCD 上为 SD 打印显示进度条
    #if ENABLED(LCD_PROGRESS_BAR)
      #define PROGRESS_BAR_BAR_TIME 2000  // (ms) 显示进度条的时间
      #define PROGRESS_BAR_MSG_TIME 3000  // (ms) 显示状态消息的时间
      #define PROGRESS_MSG_EXPIRE      0  // (ms) 保留状态消息的时间 (0=永久)
      //#define PROGRESS_MSG_ONCE         // 显示消息 MSG_TIME 后清除
      //#define LCD_PROGRESS_BAR_TEST     // 添加一个用于测试进度条的菜单项
    #endif
  #endif
#endif

#if ENABLED(SDSUPPORT)
  /**
   * SD 卡 SPI 速度
   * 可能需要此项来解决 "volume init" 错误。
   *
   * 启用并设置为 SPI_HALF_SPEED、SPI_QUARTER_SPEED 或 SPI_EIGHTH_SPEED，
   *  否则将使用全速。
   *
   * :['SPI_HALF_SPEED', 'SPI_QUARTER_SPEED', 'SPI_EIGHTH_SPEED']
   */
  //#define SD_SPI_SPEED SPI_HALF_SPEED

  // 标准 SD 检测电路在插入介质时读为 LOW，为空时读为 HIGH。
  // 若你的 SD 卡检测不正确，请启用此选项并设为 HIGH。
  //#define SD_DETECT_STATE HIGH

  //#define SD_IGNORE_AT_STARTUP            // 启动时不挂载 SD 卡
  //#define SDCARD_READONLY                 // 只读 SD 卡（可节省 2K 以上 flash）

  //#define GCODE_REPEAT_MARKERS            // 启用 G 代码 M808 以设置重复标记并执行循环

  #define SD_PROCEDURE_DEPTH 1              // 如果需要更多层嵌套的 M32 调用请增大此值

  #define SD_FINISHED_STEPPERRELEASE true   // SD 打印结束时关闭步进电机
  #define SD_FINISHED_RELEASECOMMAND "M84"  // 使用 "M84XYE" 可保持 Z 轴启用，使热床保持原位

  // 反转 SD 排序，按存储卡的 FAT 将"较新"的文件排在前面。
  // 由于 FAT 会随使用变得无序，建议使用 SDCARD_SORT_ALPHA。
  #define SDCARD_RATHERRECENTFIRST

  #define SD_MENU_CONFIRM_START             // 打印前确认所选的 SD 文件

  //#define NO_SD_AUTOSTART                 // 完全移除 auto#.g 文件支持，以节省部分 Flash 和 SRAM
  //#define MENU_ADDAUTOSTART               // 添加一个用于运行 auto#.g 文件的菜单选项

  //#define BROWSE_MEDIA_ON_INSERT          // 插入介质时打开文件浏览器

  //#define MEDIA_MENU_AT_TOP               // 强制将介质菜单列在主菜单顶部

  #define EVENT_GCODE_SD_ABORT "G28XY"      // 中止 SD 打印时执行的 G 代码（例如 "G28XY" 或 "G27"）

  #if ENABLED(PRINTER_EVENT_LEDS)
    #define PE_LEDS_COMPLETED_TIME  (30*60) // (seconds) 恢复正常照明前保持 LED "完成" 色的时间
  #endif

  /**
   * 断电后继续打印 (Creality3D)
   *
   * SD 打印期间在每层开始时将当前状态
   * 保存到 SD 卡。若在启动时找到恢复文件，
   * 则在 LCD 屏幕上提供从文件中最后已知
   * 位置继续打印的选项。
   */
  //#define POWER_LOSS_RECOVERY
  #if ENABLED(POWER_LOSS_RECOVERY)
    #define PLR_ENABLED_DEFAULT   false // 默认启用断电恢复。（用 'M413 Sn' 与 M500 设置）
    //#define BACKUP_POWER_SUPPLY       // 备用电源 / UPS，用于在断电时移动步进电机
    //#define POWER_LOSS_ZRAISE       2 // (mm) 恢复打印时 Z 轴抬升量（断电且有 UPS 时）
    //#define POWER_LOSS_PIN         44 // 检测断电的引脚。设为 -1 可在无该模块的主板上禁用默认引脚。
    //#define POWER_LOSS_STATE     HIGH // 表示断电的引脚状态
    //#define POWER_LOSS_PULLUP         // 根据你的传感器设置上拉 / 下拉
    //#define POWER_LOSS_PULLDOWN
    //#define POWER_LOSS_PURGE_LEN   20 // (mm) 恢复打印时排出的耗材长度
    //#define POWER_LOSS_RETRACT_LEN 10 // (mm) 失败时回抽的耗材长度。需要备用电源。

    // 没有 POWER_LOSS_PIN 时，以下选项有助于减少 SD 卡的磨损，
    // 尤其是在“花瓶模式”打印时。设置过高将导致花瓶无法继续打印。
    #define POWER_LOSS_MIN_Z_CHANGE 0.05 // (mm) 保存断电数据前所需的最小 Z 变化量

    // 若正确恢复需要 Z 归位则启用。99.9% 的情况下都应保持禁用！
    //#define POWER_LOSS_RECOVER_ZHOME
    #if ENABLED(POWER_LOSS_RECOVER_ZHOME)
      //#define POWER_LOSS_ZHOME_POS { 0, 0 } // 归位 Z 时的安全 XY 位置，同时避开热床上的物体
    #endif
  #endif

  /**
   * 按字母顺序排列 SD 卡文件列表。
   *
   * 启用此选项后，SD 卡中的项目将按名称排序，
   * 便于浏览。
   *
   * 默认情况下...
   *
   *  - 使用最慢但最安全的排序方式。
   *  - 文件夹排在最前面。
   *  - 排序键静态分配。
   *  - 不支持附加的 G 代码 (M34)。
   *  - 最多排序 40 个项目。（第 40 个之后的项目不排序。）
   *
   * SD 排序使用静态分配（由 SDSORT_LIMIT 设定），这样编译器
   * 就能计算出最坏情况下的占用量，并在超出 SRAM
   * 限制时抛出错误。
   *
   *  - SDSORT_USES_RAM 通过静态目录缓冲区提供更快的排序。
   *  - SDSORT_USES_STACK 作用相同，但使用基于栈的本地缓冲区。
   *  - SDSORT_CACHE_NAMES 会在 RAM 中保留排序后的文件列表。（开销大！）
   *  - SDSORT_DYNAMIC_RAM 仅在 SD 菜单可见时才使用 RAM。（谨慎使用！）
   */
  //#define SDCARD_SORT_ALPHA

  // SD 卡排序选项
  #if ENABLED(SDCARD_SORT_ALPHA)
    #define SDSORT_LIMIT       40     // 排序项目的最大数量 (10-256)。每项占用 27 字节。
    #define FOLDER_SORTING     -1     // -1=置前  0=不排序  1=置后
    #define SDSORT_GCODE       false  // 允许通过 LCD 和 M34 G 代码开关排序。
    #define SDSORT_USES_RAM    false  // 预分配静态数组以加快预排序速度。
    #define SDSORT_USES_STACK  false  // 预排序时优先使用栈以释放部分 SRAM。（后两个选项会抵消此设置。）
    #define SDSORT_CACHE_NAMES false  // 在 RAM 中更长时间保留排序后的项目，以获得更快的速度。开销最大的选项。
    #define SDSORT_DYNAMIC_RAM false  // 使用动态分配（在 SD 菜单内）。开销最小的选项。使用前必须先设置 SDSORT_LIMIT！
    #define SDSORT_CACHE_VFATS 2      // 用于排序的 13 字节 VFAT 条目最大数量。
                                      // 注意：仅在启用 SDSORT_CACHE_NAMES 时影响 SCROLL_LONG_FILENAMES，SDSORT_DYNAMIC_RAM 则不受影响。
  #endif

  // 允许在长文件名中使用国际符号。要正确显示，
  // LCD 字体必须包含相应字符。请检查所选的 LCD 语言。
  //#define UTF_FILENAME_SUPPORT

  //#define LONG_FILENAME_HOST_SUPPORT    // 用 'M33 <dosname>' 获取文件/文件夹的长文件名，用 'M20 L' 列出长文件名
  //#define LONG_FILENAME_WRITE_SUPPORT   // 通过 M28、M30 和二进制传输协议创建/删除长文件名文件
  //#define M20_TIMESTAMP_SUPPORT         // 为 M20 命令添加 'T' 标志以包含时间戳

  //#define SCROLL_LONG_FILENAMES         // 在 SD 卡菜单中滚动显示长文件名

  //#define SD_ABORT_NO_COOLDOWN          // 停止打印后保持加热器开启（不推荐！）

  /**
   * 当任意限位开关被触发时中止 SD 打印。
   * 此功能通过 'M540 S1' 或从 LCD 菜单启用。
   * 此选项需要限位开关已激活才能生效。
   */
  //#define SD_ABORT_ON_ENDSTOP_HIT
  #if ENABLED(SD_ABORT_ON_ENDSTOP_HIT)
    //#define SD_ABORT_ON_ENDSTOP_HIT_GCODE "G28XY" // 限位开关触发时运行的 G 代码（例如 "G28XY" 或 "G27"）
  #endif

  //#define SD_REPRINT_LAST_SELECTED_FILE // 打印完成后打开 LCD 菜单并选中同一文件

  //#define AUTO_REPORT_SD_STATUS         // 用 'M27 S<seconds>' 自动报告介质状态

  /**
   * 支持使用 Arduino USB Host Shield 或等效的 MAX3421E
   * 扩展板连接 USB U 盘。USB U 盘对 Marlin 而言
   * 就相当于一张 SD 卡。
   *
   * MAX3421E 可以与 SD 卡读卡器分配相同的引脚，
   * 引脚映射如下：
   *
   *    SCLK, MOSI, MISO --> SCLK, MOSI, MISO
   *    INT              --> SD_DETECT_PIN [1]
   *    SS               --> SDSS
   *
   * [1] 在 AVR 上，支持中断的引脚最有利于 UHS3 兼容性。
   */
  //#define USB_FLASH_DRIVE_SUPPORT
  #if ENABLED(USB_FLASH_DRIVE_SUPPORT)
    /**
     * USB Host Shield 库
     *
     * - UHS2 不使用中断，并已在配备 32 位 Archim 主板的
     *   LulzBot TAZ Pro 上通过生产验证。
     *
     * - UHS3 是较新的代码，USB 兼容性更好。但它
     *   测试较少，且已知会干扰舵机。
     *   [1] 这要求 USB_INTR_PIN 支持中断。
     */
    //#define USE_UHS2_USB
    //#define USE_UHS3_USB

    #define DISABLE_DUE_SD_MMC // 禁用通过 USB Host 访问 U 盘，以避免 DUE 平台在块访问时挂起

    /**
     * 部分主板支持的原生 USB Host (USB OTG)
     */
    //#define USE_OTG_USB_HOST

    #if DISABLED(USE_OTG_USB_HOST)
      #define USB_CS_PIN    SDSS
      #define USB_INTR_PIN  SD_DETECT_PIN
    #endif
  #endif

  /**
   * 使用支持 SD-Firmware-Flashing 的引导程序时，
   * 添加一个菜单项以在下次重启时激活 SD-FW-Update。
   *
   * 需要 ATMEGA2560 (Arduino Mega)
   *
   * 已使用以下引导程序测试：
   *   https://github.com/FleetProbe/MicroBridge-Arduino-ATMega2560
   */
  //#define SD_FIRMWARE_UPDATE
  #if ENABLED(SD_FIRMWARE_UPDATE)
    #define SD_FIRMWARE_UPDATE_EEPROM_ADDR    0x1FF
    #define SD_FIRMWARE_UPDATE_ACTIVE_VALUE   0xF0
    #define SD_FIRMWARE_UPDATE_INACTIVE_VALUE 0xFF
  #endif

  /**
   * 如果有超过约 3K 的未使用的 flash 空间，请启用此选项。
   * Marlin 会将所有设置以压缩数据的形式嵌入固件二进制文件中。
   * 使用 'M503 C' 将设置以 'mc.zip' 写入 SD 卡。
   * 有关 'mc-apply.py' 的使用详情，请参阅 docs/ConfigEmbedding.md。
   */
  //#define CONFIGURATION_EMBEDDING

  // 添加一种优化的二进制文件传输模式，通过 'M28 B1' 启动
  //#define BINARY_FILE_TRANSFER

  #if ENABLED(BINARY_FILE_TRANSFER)
    // 包含额外的功能（例如 'M20 F'），以支持通过 BINARY_FILE_TRANSFER 上传固件
    //#define CUSTOM_FIRMWARE_UPLOAD
  #endif

  /**
   * 将此选项设置为以下之一（否则使用主板的默认值）：
   *
   *           LCD - 使用外置 LCD 控制器中的 SD 卡驱动器。
   *       ONBOARD - 使用控制板上的 SD 卡驱动器。
   *  CUSTOM_CABLE - 使用自定义线缆访问 SD 卡（在引脚文件中定义）。
   *
   * :[ 'LCD', 'ONBOARD', 'CUSTOM_CABLE' ]
   */
  //#define SDCARD_CONNECTION LCD

  // 若 SD 卡检测功能失效（例如使用了 SD 延长线），则启用
  //#define NO_SD_DETECT

  /**
   * 多卷支持 - 实验性功能。
   * 新增 'M21 Pm' / 'M21 S' / 'M21 U' 用于挂载 SD 卡 / U 盘。
   */
  //#define MULTI_VOLUME
  #if ENABLED(MULTI_VOLUME)
    #define VOLUME_SD_ONBOARD
    #define VOLUME_USB_FLASH_DRIVE
    #define DEFAULT_VOLUME SV_SD_ONBOARD
    #define DEFAULT_SHARED_VOLUME SV_USB_FLASH_DRIVE
  #endif

#endif // SDSUPPORT

/**
 * 默认情况下，板载 SD 卡读卡器可作为 USB 大容量
 * 存储设备共享。此选项会将对 SD 卡的访问从主机 PC 上隐藏。
 */
//#define NO_SD_HOST_DRIVE   // 禁止通过 USB 访问 SD 卡（出于安全考虑）。

/**
 * 默认情况下，框架负责共享介质 I/O。
 * 如果需要由 Marlin 处理共享介质 I/O，请启用此选项。
 * 在某些主板上共享介质工作不正常时，此选项很有用。
 */
#if ENABLED(SDSUPPORT) && DISABLED(NO_SD_HOST_DRIVE)
  //#define DISKIO_HOST_DRIVE
#endif

/**
 * 图形显示器的附加选项
 *
 * 使用这里的优化选项来提升打印性能，
 * 因为图形显示器的绘制会对其产生不利影响，
 * 尤其是在进行多次短距离移动时，以及在
 * DELTA 和 SCARA 机器上打印时。
 *
 * 由于需要在可靠的打印性能与快速的显示刷新之间权衡，
 * 其中一些选项可能导致显示落后于
 * 控制器事件。
 */
#if HAS_MARLINUI_U8GLIB
  // 在信息屏幕上绘制空心边框或不绘制边框，可节省大量运算周期
  //#define XYZ_NO_FRAME
  #define XYZ_HOLLOW_FRAME

  // 编辑项可使用更大的字体。占用 3120 字节 flash。
  // 仅限西方文字。不支持西里尔文、假名、土耳其文、希腊文或中文。
  //#define USE_BIG_EDIT_FONT

  // 信息屏幕可使用较小的字体。占用 2434 字节 flash。
  // 仅限西方文字。不支持西里尔文、假名、土耳其文、希腊文或中文。
  //#define USE_SMALL_INFOFONT

  /**
   * 图形显示器休眠
   *
   * U8G 库为 SH1106、SSD1306、
   * SSD1309 以及其他一些 DOGM 显示屏提供休眠/唤醒功能。
   * 启用此选项可节省电能并防止 OLED 像素烧屏。
   * 新增菜单项 Configuration > LCD Timeout (m)，可将等待时间
   * 设置为 0（禁用）至 99 分钟。
   */
  //#define DISPLAY_SLEEP_MINUTES 2  // (minutes) 关闭屏幕前的超时时间。用 M255 S 设置。

  /**
   * 基于 ST7920 的 LCD 可以利用 ST7920 字符发生器
   * 模拟 16 x 4 字符显示器，实现非常快速的屏幕刷新。
   * 启用 LIGHTWEIGHT_UI 即可使用这种特殊显示模式。
   *
   * 由于 LIGHTWEIGHT_UI 空间有限，位置和状态
   * 消息将占用同一行。将 STATUS_EXPIRE_SECONDS 设为
   * 状态消息清除前的显示时长。
   *
   * 将 STATUS_EXPIRE_SECONDS 设为零则永不清除状态。
   * 这将导致位置更新无法显示。
   */
  #if IS_U8GLIB_ST7920
    // 启用此选项并减小该值以优化屏幕刷新。
    // 正常延迟为 10µs。请使用仍能保证显示可靠的最小值。
    //#define DOGM_SPI_DELAY_US 5

    //#define LIGHTWEIGHT_UI
    #if ENABLED(LIGHTWEIGHT_UI)
      #define STATUS_EXPIRE_SECONDS 20
    #endif
  #endif

  /**
   * 状态（信息）屏幕自定义
   * 这些选项可能影响代码大小和屏幕渲染时间。
   * 自定义状态屏幕可以强制覆盖这些设置。
   */
  //#define STATUS_COMBINE_HEATERS    // 使用组合的加热器图像而非各自的图像
  //#define STATUS_HOTEND_NUMBERLESS  // 使用不带编号的热端图标而非带编号的图标（热端多于 1 个时）
  #define STATUS_HOTEND_INVERTED      // 加热时显示实心喷嘴位图（带编号的热端需要 STATUS_HOTEND_ANIM）
  #define STATUS_HOTEND_ANIM          // 使用第二张位图表示热端加热
  #define STATUS_BED_ANIM             // 使用第二张位图表示热床加热
  #define STATUS_CHAMBER_ANIM         // 使用第二张位图表示腔体加热
  //#define STATUS_CUTTER_ANIM        // 使用第二张位图表示主轴/激光处于活动状态
  //#define STATUS_COOLER_ANIM        // 使用第二张位图表示激光冷却
  //#define STATUS_FLOWMETER_ANIM     // 使用多张位图表示冷却液流动
  //#define STATUS_ALT_BED_BITMAP     // 使用备用的热床位图
  //#define STATUS_ALT_FAN_BITMAP     // 使用备用的风扇位图
  //#define STATUS_FAN_FRAMES 3       // :[0,1,2,3,4] 风扇动画帧数
  //#define STATUS_HEAT_PERCENT       // 以进度条形式显示加热
  //#define BOOT_MARLIN_LOGO_ANIMATED // 动画 Marlin 标志。占用约 3260（或约 940）字节 flash。

  // 小游戏选项
  //#define MARLIN_BRICKOUT
  //#define MARLIN_INVADERS
  //#define MARLIN_SNAKE
  //#define GAMES_EASTER_EGG          // 在 "Games" 子菜单上方添加额外的空行

#endif // HAS_MARLINUI_U8GLIB

#if HAS_MARLINUI_U8GLIB || IS_DWIN_MARLINUI
  #define MENU_HOLLOW_FRAME           // 启用后可在菜单屏幕上绘制空心边框，节省大量运算周期
  //#define OVERLAY_GFX_REVERSE       // 交换图形叠加中的 CW/CCW 指示符
#endif

//
// DGUS / DWIN 显示器的附加选项
//
#if HAS_DGUS_LCD
  #define LCD_BAUDRATE 115200

  #define DGUS_RX_BUFFER_SIZE 128
  #define DGUS_TX_BUFFER_SIZE 48
  //#define SERIAL_STATS_RX_BUFFER_OVERRUNS  // 修复 Rx 溢出问题（目前仅适用于 AVR）

  #define DGUS_UPDATE_INTERVAL_MS  500    // (ms) 自动屏幕更新之间的间隔

  #if DGUS_UI_IS(FYSETC, MKS, HIPRECY)
    #define DGUS_PRINT_FILENAME           // 打印时显示文件名
    #define DGUS_PREHEAT_UI               // 加热过程中显示预热界面

    #if DGUS_UI_IS(FYSETC, MKS)
      //#define DGUS_UI_MOVE_DIS_OPTION   // FYSETC 和 MKS 默认禁用
    #else
      #define DGUS_UI_MOVE_DIS_OPTION     // UI_HIPRECY 默认启用
    #endif

    #define DGUS_FILAMENT_LOADUNLOAD
    #if ENABLED(DGUS_FILAMENT_LOADUNLOAD)
      #define DGUS_FILAMENT_PURGE_LENGTH 10
      #define DGUS_FILAMENT_LOAD_LENGTH_PER_TIME 0.5 // (mm) 按 DGUS_UPDATE_INTERVAL_MS 的比例调整
    #endif

    #define DGUS_UI_WAITING               // 在某些屏幕之间显示 "waiting" 屏幕
    #if ENABLED(DGUS_UI_WAITING)
      #define DGUS_UI_WAITING_STATUS 10
      #define DGUS_UI_WAITING_STATUS_PERIOD 8 // 增大此值可放慢等待状态的循环
    #endif
  #endif
#endif // HAS_DGUS_LCD

//
// AnyCubic Chiron TFT 显示器的附加选项
//
#if ENABLED(ANYCUBIC_LCD_CHIRON)
  // 默认自动检测面板类型。
  // 如果已知面板类型，请启用以下选项之一。
  //#define CHIRON_TFT_STANDARD
  //#define CHIRON_TFT_NEW

  // 启用较长的 Anycubic 上电启动音
  //#define AC_DEFAULT_STARTUP_TUNE

  /**
   * 显示文件夹
   * 默认文件浏览器以扁平列表显示所有 G 代码文件（包括子文件夹中的文件）。
   * 启用此选项可显示层次化的文件浏览器。
   *
   * 注意：
   * - 不启用此选项时，建议启用 SDCARD_SORT_ALPHA，使文件排在文件夹之前/之后。
   * - 与 "new" 面板搭配使用时，文件夹名也会追加 '.gcode'。
   *   目前这个变通做法是强制面板显示文件夹所必需的。
   */
  #define AC_SD_FOLDER_VIEW
#endif

//
// 指定 UI 的附加语言。默认语言由 LCD_LANGUAGE 指定。
//
#if ANY(DOGLCD, TFT_COLOR_UI, TOUCH_UI_FTDI_EVE, IS_DWIN_MARLINUI, ANYCUBIC_LCD_VYPER)
  //#define LCD_LANGUAGE_2 fr
  //#define LCD_LANGUAGE_3 de
  //#define LCD_LANGUAGE_4 es
  //#define LCD_LANGUAGE_5 it
  #ifdef LCD_LANGUAGE_2
    //#define LCD_LANGUAGE_AUTO_SAVE // 更改时自动将语言保存到 EEPROM
  #endif
#endif

//
// FTDI 嵌入式视频引擎 (EVE) 的触摸 UI
//
#if ENABLED(TOUCH_UI_FTDI_EVE)
  // 使用的显示屏
  //#define LCD_FTDI_VM800B35A        // FTDI 3.5" 搭配 FT800 (320x240)
  //#define LCD_4DSYSTEMS_4DLCD_FT843 // 4D Systems 4.3" (480x272)
  //#define LCD_HAOYU_FT800CB         // Haoyu 4.3" 或 5" (480x272)
  //#define LCD_HAOYU_FT810CB         // Haoyu 5" (800x480)
  //#define LCD_LULZBOT_CLCD_UI       // LulzBot 彩色 LCD UI
  //#define LCD_FYSETC_TFT81050       // FYSETC 5" (800x480)
  //#define LCD_EVE3_50G              // Matrix Orbital 5.0", 800x480, BT815
  //#define LCD_EVE2_50G              // Matrix Orbital 5.0", 800x480, FT813

  // 如果未使用原配 TFT 面板，请修正分辨率。
  //#define TOUCH_UI_320x240
  //#define TOUCH_UI_480x272
  //#define TOUCH_UI_800x480

  // 带有标准 RepRapDiscount 显示器连接器的主板的引脚映射
  //#define AO_EXP1_PINMAP      // LulzBot CLCD UI EXP1 映射
  //#define AO_EXP2_PINMAP      // LulzBot CLCD UI EXP2 映射
  //#define CR10_TFT_PINMAP     // Rudolph Riedel 的 CR10 引脚映射
  //#define S6_TFT_PINMAP       // FYSETC S6 引脚映射
  //#define F6_TFT_PINMAP       // FYSETC F6 引脚映射

  //#define OTHER_PIN_LAYOUT  // 在下方手动定义引脚
  #if ENABLED(OTHER_PIN_LAYOUT)
    // 必须选择 CS 和 MOD_RESET (PD) 的引脚
    #define CLCD_MOD_RESET  9
    #define CLCD_SPI_CS    10

    // 如果使用软件 SPI，请指定 SCLK、MOSI、MISO 的引脚
    //#define CLCD_USE_SOFT_SPI
    #if ENABLED(CLCD_USE_SOFT_SPI)
      #define CLCD_SOFT_SPI_MOSI 11
      #define CLCD_SOFT_SPI_MISO 12
      #define CLCD_SOFT_SPI_SCLK 13
    #endif
  #endif

  // 显示方向。FT800 支持反向（即上下颠倒）显示。
  // FT810 及更新的型号还支持
  // 竖屏和镜像方向。
  //#define TOUCH_UI_INVERTED
  //#define TOUCH_UI_PORTRAIT
  //#define TOUCH_UI_MIRRORED

  // UTF8 处理与渲染。
  // 不支持的字符显示为 '?'。
  //#define TOUCH_UI_USE_UTF8
  #if ENABLED(TOUCH_UI_USE_UTF8)
    // 支持西方重音字符。这些带重音的字符使用
    // 组合位图，所需的存储空间相对较少。
    #define TOUCH_UI_UTF8_WESTERN_CHARSET
    #if ENABLED(TOUCH_UI_UTF8_WESTERN_CHARSET)
      // 其他字符组。这些字符需要
      // 完整位图，占用相当大的存储空间：
      //#define TOUCH_UI_UTF8_SUPERSCRIPTS  // ¹ ² ³
      //#define TOUCH_UI_UTF8_COPYRIGHT     // © ®
      //#define TOUCH_UI_UTF8_GERMANIC      // ß
      //#define TOUCH_UI_UTF8_SCANDINAVIAN  // Æ Ð Ø Þ æ ð ø þ
      //#define TOUCH_UI_UTF8_PUNCTUATION   // « » ¿ ¡
      //#define TOUCH_UI_UTF8_CURRENCY      // ¢ £ ¤ ¥
      //#define TOUCH_UI_UTF8_ORDINALS      // º ª
      //#define TOUCH_UI_UTF8_MATHEMATICS   // ± × ÷
      //#define TOUCH_UI_UTF8_FRACTIONS     // ¼ ½ ¾
      //#define TOUCH_UI_UTF8_SYMBOLS       // µ ¶ ¦ § ¬
    #endif

    // 西里尔字符集，约占用 27KiB flash
    //#define TOUCH_UI_UTF8_CYRILLIC_CHARSET
  #endif

  // 当标签无法容纳于按钮内时使用较小的字体
  #define TOUCH_UI_FIT_TEXT

  // "Screen lock" 键盘使用数字密码。
  // （建议用于较小的显示屏）
  //#define TOUCH_UI_PASSCODE

  // 输出触摸 UI 事件的额外调试信息
  //#define TOUCH_UI_DEBUG

  // 开发者菜单（通过点击 "About Printer" 版权文字进入）
  //#define TOUCH_UI_DEVELOPER_MENU
#endif

//
// 经典 UI 选项
//
#if TFT_SCALED_DOGLCD
  //#define TFT_MARLINUI_COLOR 0xFFFF // 白色
  //#define TFT_MARLINBG_COLOR 0x0000 // 黑色
  //#define TFT_DISABLED_COLOR 0x0003 // 接近黑色
  //#define TFT_BTCANCEL_COLOR 0xF800 // 红色
  //#define TFT_BTARROWS_COLOR 0xDEE6 // 11011 110111 00110 黄色
  //#define TFT_BTOKMENU_COLOR 0x145F // 00010 100010 11111 青色
#endif

//
// ADC 按键消抖
//
#if HAS_ADC_BUTTONS
  #define ADC_BUTTON_DEBOUNCE_DELAY 16  // 如果按键抖动或重复过快，请增大此值
#endif

// @section safety

/**
 * 如果固件负载过重，无法读取温度传感器，
 * 看门狗硬件定时器将执行复位并禁用所有输出。
 *
 * 如果发现看门狗重启导致 AVR 主板永久挂起，
 * 请启用 WATCHDOG_RESET_MANUAL 以使用自定义定时器代替 WDTO。
 * 注意：此方法可靠性较低，因为它只能在
 * 中断启用时捕获挂起。
 */
#define USE_WATCHDOG
#if ENABLED(USE_WATCHDOG)
  //#define WATCHDOG_RESET_MANUAL
#endif

// @section lcd

/**
 * 微调（babystepping）可在不改变当前位置数值的情况下
 * 让各轴做极小的移动。此功能主要用于在打印第一层时
 * 实时调整 Z 轴。
 *
 * 警告：不会遵循限位开关！
 */
//#define BABYSTEPPING
#if ENABLED(BABYSTEPPING)
  //#define INTEGRATED_BABYSTEPPING         // 实验性功能：将微调集成到步进电机 ISR 中
  //#define BABYSTEP_WITHOUT_HOMING
  //#define BABYSTEP_ALWAYS_AVAILABLE       // 允许在任何时候微调（不仅限于移动过程中）。
  //#define BABYSTEP_XY                     // 同时启用 X/Y 微调。DELTA 上不支持！
  #define BABYSTEP_INVERT_Z false           // 如果希望 Z 微调方向相反，请修改此项
  //#define BABYSTEP_MILLIMETER_UNITS       // 以 mm 而不是微步指定 BABYSTEP_MULTIPLICATOR_(XY|Z)
  #define BABYSTEP_MULTIPLICATOR_Z  1       // (steps or mm) 每次 Z 微调的步数或毫米距离
  #define BABYSTEP_MULTIPLICATOR_XY 1       // (steps or mm) 每次 XY 微调的步数或毫米距离

  //#define DOUBLECLICK_FOR_Z_BABYSTEPPING  // 在状态屏幕上双击以进行 Z 微调。
  #if ENABLED(DOUBLECLICK_FOR_Z_BABYSTEPPING)
    #define DOUBLECLICK_MAX_INTERVAL 1250   // 两次点击之间的最大间隔（毫秒）。
                                            // 注意：可能增加额外时间以缓解控制器延迟。
    //#define MOVE_Z_WHEN_IDLE              // 打印机空闲时双击直接跳转到移动 Z 菜单。
    #if ENABLED(MOVE_Z_WHEN_IDLE)
      #define MOVE_Z_IDLE_MULTIPLICATOR 1   // 将 1mm 乘以该系数以确定移动步长。
    #endif
  #endif

  //#define BABYSTEP_DISPLAY_TOTAL          // 显示自上次 G28 以来的微调总步数

  //#define BABYSTEP_ZPROBE_OFFSET          // 结合 M851 Z 与微调
  //#define BABYSTEP_GLOBAL_Z               // 结合 M424 Z 与微调

  #if EITHER(BABYSTEP_ZPROBE_OFFSET, BABYSTEP_GLOBAL_Z)
    #if ENABLED(BABYSTEP_ZPROBE_OFFSET)
      //#define BABYSTEP_HOTEND_Z_OFFSET    // 多热端时，微调相对于 Z 偏移
    #endif
    //#define BABYSTEP_GFX_OVERLAY          // 在 Z 偏移编辑器中启用图形叠加
  #endif
#endif

// @section extruder

/**
 * 线性压力控制 v1.5
 *
 * 假设：advance [steps] = k * (delta velocity [steps/s])
 * K=0 表示禁用 advance。
 *
 * 注意：LIN_ADVANCE 1.5 的 K 值与早期版本不同！
 *
 * 对于 3mm PLA 直驱式、驱动齿轮与热断间距约 6.5cm 的情况，请将 K 设为 0.22 左右。
 * 柔性耗材和更大的间距需要更大的 K 值。
 * 如果此算法产生的速度偏移超出挤出机的处理能力（与 E 轴 jerk 相比），
 * 则在受影响的移动过程中会降低打印加速度以保持在限制内。
 *
 * 完整说明请见 https://marlinfw.org/docs/features/lin_advance.html
 */
//#define LIN_ADVANCE
#if ENABLED(LIN_ADVANCE)
  #if ENABLED(DISTINCT_E_FACTORS)
    #define ADVANCE_K { 0.22 }    // (mm) 每 1mm/s 挤出机速度对应的压缩长度，按挤出机分别计算
  #else
    #define ADVANCE_K 0.22        // (mm) 适用于所有挤出机的压缩长度
  #endif
  //#define ADVANCE_K_EXTRA       // 添加第二个线性 advance 常量，可用 M900 L 配置。
  //#define LA_DEBUG              // 运行期间将调试信息输出到串口。正式使用时请禁用。
  //#define ALLOW_LOW_EJERK       // 允许 DEFAULT_EJERK 的值 < 10。推荐用于直驱式热端。
  //#define EXPERIMENTAL_I2S_LA   // 允许 I2S_STEPPER_STREAM 与 LA 配合使用。当 LA 步进频率达到约 20kHz 时性能会下降。
#endif

// @section leveling

/**
 * 使用安全热床调平坐标，在探测热床前将各轴移动到合适的位置。
 * 例如，旋转轴归位后，Z 探针可能不再与热床垂直。
 * 请选择合适的值，使热床水平、Z 探针垂直。
 */
//#define SAFE_BED_LEVELING_START_X 0.0
//#define SAFE_BED_LEVELING_START_Y 0.0
//#define SAFE_BED_LEVELING_START_Z 0.0
//#define SAFE_BED_LEVELING_START_I 0.0
//#define SAFE_BED_LEVELING_START_J 0.0
//#define SAFE_BED_LEVELING_START_K 0.0
//#define SAFE_BED_LEVELING_START_U 0.0
//#define SAFE_BED_LEVELING_START_V 0.0
//#define SAFE_BED_LEVELING_START_W 0.0

/**
 * 所有三点调平流程的探测点。
 * 如果自动选定的点不理想，可在此覆盖。
 */
#if NEEDS_THREE_PROBE_POINTS
  //#define PROBE_PT_1 {  15, 180 }   // (mm) { x, y }
  //#define PROBE_PT_2 {  15,  20 }
  //#define PROBE_PT_3 { 170,  20 }
#endif

/**
 * 探测边距
 *
 * 为打印平台的每一侧单独覆盖 PROBING_MARGIN
 * 可用于让探测点精确落在目标位置上，
 * 或让调平只在热床的特定边避开平台夹具。
 * 使用 NOZZLE_AS_PROBE 时允许
 * 负值，以便在热床外探测。
 *
 * 如果要替换之前的 *_PROBE_BED_POSITION 选项，
 * 多数情况下 LEFT 和 FRONT 的值可直接对应，
 * 而 RIGHT 和 REAR 则是其反向值，例如
 * (X/Y_BED_SIZE - RIGHT/BACK_PROBE_BED_POSITION)
 *
 * 这样所有位置在编译时都能匹配，但如果
 * 之后用 M851XY 修改了探针位置，
 * 探测点也会随之变化。这可避免任何改动导致
 * 探针无法到达某些点。
 */
#if PROBE_SELECTED && !IS_KINEMATIC
  //#define PROBING_MARGIN_LEFT PROBING_MARGIN
  //#define PROBING_MARGIN_RIGHT PROBING_MARGIN
  //#define PROBING_MARGIN_FRONT PROBING_MARGIN
  //#define PROBING_MARGIN_BACK PROBING_MARGIN
#endif

#if EITHER(MESH_BED_LEVELING, AUTO_BED_LEVELING_UBL)
  // 如果自动（最大）区域过大，则覆盖网格区域
  //#define MESH_MIN_X MESH_INSET
  //#define MESH_MIN_Y MESH_INSET
  //#define MESH_MAX_X X_BED_SIZE - (MESH_INSET)
  //#define MESH_MAX_Y Y_BED_SIZE - (MESH_INSET)
#endif

#if BOTH(AUTO_BED_LEVELING_UBL, EEPROM_SETTINGS)
  //#define OPTIMIZED_MESH_STORAGE  // 以较低的精度存储网格以节省 EEPROM 空间
#endif

/**
 * 反复尝试 G29 调平直到成功。
 * 尝试 G29_MAX_RETRIES 次后停止。
 */
//#define G29_RETRY_AND_RECOVER
#if ENABLED(G29_RETRY_AND_RECOVER)
  #define G29_MAX_RETRIES 3
  #define G29_HALT_ON_FAILURE
  /**
   * 指定调平成功时、两次尝试之间以及达到最大重试次数后
   * 将执行的 GCODE 命令。
   */
  #define G29_SUCCESS_COMMANDS "M117 Bed leveling done."
  #define G29_RECOVER_COMMANDS "M117 Probe failed. Rewiping.\nG28\nG12 P0 S12 T0"
  #define G29_FAILURE_COMMANDS "M117 Bed leveling failed.\nG0 Z10\nM300 P25 S880\nM300 P50 S0\nM300 P25 S880\nM300 P50 S0\nM300 P25 S880\nM300 P50 S0\nG4 S1"

#endif

/**
 * 探针热补偿
 *
 * 调整探针测量值，以补偿与探针、热床和/或
 * 热端温度相关的变形。
 * 使用 G76 可针对探针和热床温度自动校准此功能。
 * （挤出机温度/偏移值必须手动校准。）
 * 使用 M871 可手动设置温度/偏移值。
 * 详见 https://marlinfw.org/docs/features/probe_temp_compensation.html
 */
//#define PTC_PROBE    // 根据探针温度进行补偿
//#define PTC_BED      // 根据热床温度进行补偿
//#define PTC_HOTEND   // 根据热端温度进行补偿

#if ANY(PTC_PROBE, PTC_BED, PTC_HOTEND)
  /**
   * 如果探针超出定义范围，则使用最接近的点
   * 与索引为 PTC_LINEAR_EXTRAPOLATION 的点进行线性外推。例如设为 4 时，
   * 对低于 PTC_PROBE_START 的值将使用 data[0] 与 data[4] 之间的线性外推。
   */
  //#define PTC_LINEAR_EXTRAPOLATION 4

  #if ENABLED(PTC_PROBE)
    // 探针温度校准会生成一张数值表，起点为 PTC_PROBE_START
    // （例如 30），步长为 PTC_PROBE_RES（例如 5），共 PTC_PROBE_COUNT（例如 10）个采样。
    #define PTC_PROBE_START   30    // (°C)
    #define PTC_PROBE_RES      5    // (°C)
    #define PTC_PROBE_COUNT   10
    #define PTC_PROBE_ZOFFS   { 0 } // (µm) 每个采样点的 Z 调整量
  #endif

  #if ENABLED(PTC_BED)
    // 热床温度校准会生成一张类似的表。
    #define PTC_BED_START     60    // (°C)
    #define PTC_BED_RES        5    // (°C)
    #define PTC_BED_COUNT     10
    #define PTC_BED_ZOFFS     { 0 } // (µm) 每个采样点的 Z 调整量
  #endif

  #if ENABLED(PTC_HOTEND)
    // 注意：热端没有自动校准。请使用 M871。
    #define PTC_HOTEND_START 180    // (°C)
    #define PTC_HOTEND_RES     5    // (°C)
    #define PTC_HOTEND_COUNT  20
    #define PTC_HOTEND_ZOFFS  { 0 } // (µm) 每个采样点的 Z 调整量
  #endif

  // G76 选项
  #if BOTH(PTC_PROBE, PTC_BED)
    // 等待探针冷却的停放位置
    #define PTC_PARK_POS   { 0, 0, 100 }

    // 探测位置，并在探测时等待探针达到目标温度
    //#define PTC_PROBE_POS  { 12.0f, 7.3f } // 示例：MK52 磁性热床
    #define PTC_PROBE_POS  { 90, 100 }

    // 热床温度校准期间进行测量时，
    // 探针应达到的温度。
    #define PTC_PROBE_TEMP    30  // (°C)

    // 喷嘴抬起至 Z=0.0 以上的高度。降低此值有助于探针更快升温。
    // 注意：Z=0.0 偏移由探针 Z 偏移决定（例如用 M851 Z 设置）。
    #define PTC_PROBE_HEATING_OFFSET 0.5
  #endif
#endif // PTC_PROBE || PTC_BED || PTC_HOTEND

// @section extras

//
// G60/G61 位置保存与返回
//
//#define SAVED_POSITIONS 1         // 每个保存位置槽占用 12 字节

//
// G2/G3 圆弧支持
//
#define ARC_SUPPORT                   // 需要约 3226 字节
#if ENABLED(ARC_SUPPORT)
  #define MIN_ARC_SEGMENT_MM      0.1 // (mm) 每段圆弧的最小长度
  #define MAX_ARC_SEGMENT_MM      1.0 // (mm) 每段圆弧的最大长度
  #define MIN_CIRCLE_SEGMENTS    72   // 完整圆周的最少分段数
  //#define ARC_SEGMENTS_PER_SEC 50   // 使用进给速度来选择分段长度
  #define N_ARC_CORRECTION       25   // 两次校正之间的插值分段数
  //#define ARC_P_CIRCLES             // 启用 'P' 参数以指定完整圆周
  //#define SF_ARC_FIX                // 仅在使用带 "Arc Point" 圆角流程的 SkeinForge 时启用
#endif

// 支持带 XYZE 终点和 IJPQ 偏移的 G5 贝塞尔曲线
//#define BEZIER_CURVE_SUPPORT        // 需要约 2666 字节

#if EITHER(ARC_SUPPORT, BEZIER_CURVE_SUPPORT)
  //#define CNC_WORKSPACE_PLANES      // 允许 G2/G3/G5 在 XY、ZX 或 YZ 平面内工作
#endif

/**
 * 直接步进
 *
 * 与 Klipper 使用的方法类似，G6 直接步进通过预先计算所有运动，
 * 显著减少了运动计算量，提高了最高打印速度，并
 * 减少了步进混叠。
 * 准备 G 代码：https://github.com/colinrgodsey/step-daemon
 */
//#define DIRECT_STEPPING

/**
 * G38 探针目标
 *
 * 此选项新增 G38.2 和 G38.3（朝目标探测），
 * 并可选增加 G38.4 和 G38.5（背离目标探测）。
 * 为 G38 设置 MULTIPLE_PROBING 可进行多次探测。
 */
//#define G38_PROBE_TARGET
#if ENABLED(G38_PROBE_TARGET)
  //#define G38_PROBE_AWAY        // 包含 G38.4 和 G38.5 以背离目标探测
  #define G38_MINIMUM_MOVE 0.0275 // (mm) 能产生移动的最小距离。
#endif

// 步数少于此值的移动（或分段）将与下一次移动合并
#define MIN_STEPS_PER_SEGMENT 1

/**
 * 设置步进电机 DIR 前后的最小延迟（ns）
 *     0 : 无延迟（由于一次步进电机 ISR 必须经过，预计至少需要 10µS）
 *    20 : TMC2xxx 驱动器的最小值
 *   200 : A4988 驱动器的最小值
 *   400 : A5984 驱动器的最小值
 *   500 : LV8729 驱动器的最小值（推测，数据手册中无此信息）
 *   650 : DRV8825 驱动器的最小值
 *  1500 : TB6600 驱动器的最小值（推测，数据手册中无此信息）
 * 15000 : TB6560 驱动器的最小值（推测，数据手册中无此信息）
 *
 * 可根据 Configuration.h 中设置的驱动器类型覆盖默认值。
 */
//#define MINIMUM_STEPPER_POST_DIR_DELAY 650
//#define MINIMUM_STEPPER_PRE_DIR_DELAY 650

/**
 * 步进电机驱动器的最小脉冲宽度（µs）
 *   0 : 微控制器能产生的最小宽度，兼容 TMC2xxx 驱动器
 *   0 : LV8729 的最小值为 500ns，在 stepper.h 中调整
 *   1 : A4988 和 A5984 步进电机驱动器的最小值
 *   2 : DRV8825 步进电机驱动器的最小值
 *   3 : TB6600 步进电机驱动器的最小值
 *  30 : TB6560 步进电机驱动器的最小值
 *
 * 可根据 Configuration.h 中设置的驱动器类型覆盖默认值。
 */
//#define MINIMUM_STEPPER_PULSE 2

/**
 * 步进电机驱动器允许的最高步进频率（Hz）
 *  若未定义，默认为 1MHz / (2 * MINIMUM_STEPPER_PULSE)
 *  5000000 : TMC2xxx 步进电机驱动器的最大值
 *  1000000 : LV8729 步进电机驱动器的最大值
 *  500000  : A4988 步进电机驱动器的最大值
 *  250000  : DRV8825 步进电机驱动器的最大值
 *  150000  : TB6600 步进电机驱动器的最大值
 *   15000  : TB6560 步进电机驱动器的最大值
 *
 * 可根据 Configuration.h 中设置的驱动器类型覆盖默认值。
 */
//#define MAXIMUM_STEPPER_RATE 250000

// @section temperature

// 并联控制加热器 0 和加热器 1。
//#define HEATERS_PARALLEL

//===========================================================================
//================================= 缓冲区 =================================
//===========================================================================

// @section motion

// 规划器中可同时存在的线性移动数量。
// BLOCK_BUFFER_SIZE 的值必须是 2 的幂（例如 8、16、32）
#if BOTH(SDSUPPORT, DIRECT_STEPPING)
  #define BLOCK_BUFFER_SIZE  8
#elif ENABLED(SDSUPPORT)
  #define BLOCK_BUFFER_SIZE 16
#else
  #define BLOCK_BUFFER_SIZE 16
#endif

// @section serial

// 串口输入的 ASCII 缓冲区
#define MAX_CMD_SIZE 96
#define BUFSIZE 4

// 发送到主机的缓冲区大小
// 设为 0 可节省 386 字节 flash（以及 TX_BUFFER_SIZE+3 字节 RAM）。
// 若要缓冲一条简单的 "ok" 响应需要 4 字节。
// 对于 ADVANCED_OK (M105) 需要 32 字节。
// 若要获得最佳速度的调试回显：128 字节。
// 其他输出不需要这么高的速度。
// :[0, 2, 4, 8, 16, 32, 64, 128, 256]
#define TX_BUFFER_SIZE 0

// 主机接收缓冲区大小
// 不使用 XON/XOFF 流控时（参见下方的 SERIAL_XON_XOFF），32 字节应该足够。
// 若要使用流控，请将此缓冲区大小设为至少 1024 字节。
// :[0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048]
//#define RX_BUFFER_SIZE 1024

#if RX_BUFFER_SIZE >= 1024
  // 启用后控制器会向主机发送 XON/XOFF 控制字符，
  // 以指示 RX 缓冲区即将写满。
  //#define SERIAL_XON_XOFF
#endif

#if ENABLED(SDSUPPORT)
  // 启用此选项可收集并显示文件传输到 SD 后
  // RX 队列的最大使用量。
  //#define SERIAL_STATS_MAX_RX_QUEUED

  // 启用此选项可收集并显示文件传输到 SD 后
  // 丢弃的字节数。
  //#define SERIAL_STATS_DROPPED_RX
#endif

// 监控 RX 缓冲区使用情况
// 如果串口接收缓冲区溢出，则向串口输出错误信息。
// 如果看到这些错误，请增大 RX_BUFFER_SIZE 的值。
// 并非所有平台都支持。
//#define RX_BUFFER_MONITOR

/**
 * 紧急命令解析器
 *
 * 添加一个底层解析器，在某些命令进入串口接收
 * 缓冲区时拦截它们，使其无法被阻塞。
 * 目前可处理 M108、M112、M410、M876
 * 注意：尚未在所有平台上实现。
 */
//#define EMERGENCY_PARSER

/**
 * 实时报告（需要 EMERGENCY_PARSER）
 *
 * - 报告机器的位置和状态（类似 Grbl）。
 * - 在长距离移动期间自动报告位置。
 * - 适用于 CNC/激光。
 *
 * 增加对以下命令的支持：
 *  S000 : 移动过程中报告状态和位置。
 *  P000 : 移动过程中立即暂停/保持。
 *  R000 : 从暂停/保持中恢复。
 *
 * - 保持期间所有紧急解析器命令照常可用。
 * - 启用 NANODLP_Z_SYNC 和 NANODLP_ALL_AXIS 以报告移动命令的结束状态。
 */
//#define REALTIME_REPORTING_COMMANDS
#if ENABLED(REALTIME_REPORTING_COMMANDS)
  //#define FULL_REPORT_TO_HOST_FEATURE   // 像 Grbl CNC 一样自动报告机器状态
#endif

// 串口连接异常时，发送 'ok' 可能会漏掉一条已收到的命令
// 因此有些客户端会在 30 秒超时后中止。
// 有些客户端会在收到 'wait' 的同时开始发送命令。
// "wait" 仅在缓冲区为空时发送。此处 1 秒是个合适的值。
//#define NO_TIMEOUTS 1000 // 毫秒

// 一些客户端很快就会具备此功能，那样 NO_TIMEOUTS 可能就不需要了。
//#define ADVANCED_OK

// Printrun 可能难以一次性接收长字符串。
// 此选项会在串口输出的各行之间插入短暂延时。
#define SERIAL_OVERRUN_PROTECTION

// 串口回显时小数点后的位数
//#define SERIAL_FLOAT_PRECISION 4

/**
 * 设置填充一个典型字符宽度所需的比例字体空格数。
 * 这有助于更好地对齐 `G29 O` 网格输出等命令的输出。
 *
 * 对于使用固定宽度字体的客户端（如 OctoPrint），请保持此值为 1.0。
 * 否则请根据你的客户端和字体进行调整。
 */
#define PROPORTIONAL_FONT_RATIO 1.0

// @section extras

/**
 * 附加风扇速度
 * 为每个打印冷却风扇增加一个备用速度档位。
 *   'M106 P<fan> T3-255' : 为 <fan> 设置备用速度
 *   'M106 P<fan> T2'     : 使用已设置的备用速度
 *   'M106 P<fan> T1'     : 恢复之前的风扇速度
 */
//#define EXTRA_FAN_SPEED

/**
 * 基于固件和 LCD 控制的回抽
 *
 * 增加 G10 / G11 命令用于自动执行基于固件的回抽/恢复。
 * 使用 M207 和 M208 定义回抽/恢复的参数。
 *
 * 使用 M209 启用或禁用自动回抽。
 * 启用自动回抽后，设定范围内的所有 G1 E 移动
 * 都会转换为基于固件的回抽/恢复移动。
 *
 * 换耗材时务必关闭自动回抽。
 *
 * 注意 M207 / M208 / M209 的设置会保存到 EEPROM。
 */
//#define FWRETRACT
#if ENABLED(FWRETRACT)
  #define FWRETRACT_AUTORETRACT             // 覆盖切片机的回抽
  #if ENABLED(FWRETRACT_AUTORETRACT)
    #define MIN_AUTORETRACT             0.1 // (mm) 不转换短于该长度的 E 移动
    #define MAX_AUTORETRACT            10.0 // (mm) 不转换长于该长度的 E 移动
  #endif
  #define RETRACT_LENGTH                3   // (mm) 默认回抽长度（正值）
  #define RETRACT_LENGTH_SWAP          13   // (mm) 默认换料回抽长度（正值）
  #define RETRACT_FEEDRATE             45   // (mm/s) 回抽的默认进给速度
  #define RETRACT_ZRAISE                0   // (mm) 回抽时默认的 Z 轴抬升
  #define RETRACT_RECOVER_LENGTH        0   // (mm) 默认额外恢复长度（恢复时加到回抽长度上）
  #define RETRACT_RECOVER_LENGTH_SWAP   0   // (mm) 默认额外换料恢复长度（从换刀恢复时加到回抽长度上）
  #define RETRACT_RECOVER_FEEDRATE      8   // (mm/s) 回抽后恢复的默认进给速度
  #define RETRACT_RECOVER_FEEDRATE_SWAP 8   // (mm/s) 换料回抽后恢复的默认进给速度
  #if ENABLED(MIXING_EXTRUDER)
    //#define RETRACT_SYNC_MIXING           // 同时回抽并恢复所有混合步进电机
  #endif
#endif

/**
 * 通用换刀设置。
 * 除明确注明外，适用于所有类型的挤出机。
 */
#if HAS_MULTI_EXTRUDER
  // 换刀时的 Z 轴抬升距离，某些挤出机需要
  #define TOOLCHANGE_ZRAISE                 2 // (mm)
  //#define TOOLCHANGE_ZRAISE_BEFORE_RETRACT  // 在换料回抽前先抬升（如果已启用）
  //#define TOOLCHANGE_NO_RETURN              // 换刀后绝不返回原位置
  #if ENABLED(TOOLCHANGE_NO_RETURN)
    //#define EVENT_GCODE_AFTER_TOOLCHANGE "G12X"   // 换刀后运行的附加 G 代码
  #endif

  /**
   * 执行换刀命令时运行的附加 G 代码。可用于驱动额外的
   * 步进电机（例如 Configuration.h 中的 I 轴）来驱动换刀机构。
   */
  //#define EVENT_GCODE_TOOLCHANGE_T0 "G28 A\nG1 A0"  // 执行换刀命令 T0 时运行的附加 G 代码
  //#define EVENT_GCODE_TOOLCHANGE_T1 "G1 A10"        // 执行换刀命令 T1 时运行的附加 G 代码
  //#define EVENT_GCODE_TOOLCHANGE_ALWAYS_RUN         // 总是执行上面的 G 代码序列。谨慎使用！

  /**
   * 将 EVENT_GCODE_TOOLCHANGE_Tx 的坐标视为相对于 T0，
   * 这样所有工具在指定轴上的移动都完全一致。
   */
  //#define TC_GCODE_USE_GLOBAL_X   // 使用相对于 0 号工具的 X 位置
  //#define TC_GCODE_USE_GLOBAL_Y   // 使用相对于 0 号工具的 Y 位置
  //#define TC_GCODE_USE_GLOBAL_Z   // 使用相对于 0 号工具的 Z 位置

  /**
   * 工具传感器可检测工具何时被取走或放下。
   * 需要 TOOL_SENSOR1_PIN、TOOL_SENSOR2_PIN 等引脚。
   */
  //#define TOOL_SENSOR

  /**
   * 换刀时回抽并顶料，以减少
   * 溢料和拉丝，使过渡更干净。
   */
  //#define TOOLCHANGE_FILAMENT_SWAP
  #if ENABLED(TOOLCHANGE_FILAMENT_SWAP)
    // 装料 / 卸料
    #define TOOLCHANGE_FS_LENGTH              12  // (mm) 装料/卸料长度
    #define TOOLCHANGE_FS_EXTRA_RESUME_LENGTH  0  // (mm) 额外长度以便更好地重新开始。可用 LCD 或 M217 B 调整。
    #define TOOLCHANGE_FS_RETRACT_SPEED   (50*60) // (mm/min) (卸料)
    #define TOOLCHANGE_FS_UNRETRACT_SPEED (25*60) // (mm/min) (SINGLENOZZLE 或 Bowden 装料时必须减速)

    // 更长的顶料行程以清理 SINGLENOZZLE
    #define TOOLCHANGE_FS_EXTRA_PRIME          0  // (mm) 额外顶料长度
    #define TOOLCHANGE_FS_PRIME_SPEED    (4.6*60) // (mm/min) 额外顶料的进给速度
    #define TOOLCHANGE_FS_WIPE_RETRACT         0  // (mm) 在停放位置截断回抽，以减少拉丝、改善擦拭效果等。可用 LCD 或 M217 G 调整。

    // 顶料后冷却以减少拉丝
    #define TOOLCHANGE_FS_FAN                 -1  // 风扇索引，-1 表示跳过
    #define TOOLCHANGE_FS_FAN_SPEED          255  // 0-255
    #define TOOLCHANGE_FS_FAN_TIME            10  // (seconds)

    // 每个挤出机首次顶料时使用 TOOLCHANGE_FS_PRIME_SPEED 进给速度
    //#define TOOLCHANGE_FS_SLOW_FIRST_PRIME

    /**
     * 首次向打印机发送 T0 时对 T0 顶料：
     *  [ 上电 -> T0 { 激活并顶料 T0 } -> T1 { 回抽 T0，激活并顶料 T1 } ]
     * 若禁用，则在从其他挤出机切回 T0 之前不会对 T0 顶料：
     *  [ 上电 -> T0 { T0 已激活 } -> T1 { 激活并顶料 T1 } -> T0 { 回抽 T1，激活并顶料 T0 } ]
     * 打印前用 M217 V1 启用，以免主机连接时发生非预期的顶料。
     */
    //#define TOOLCHANGE_FS_PRIME_FIRST_USED

    /**
     * 换刀迁移
     * 此功能提供 G 代码和 LCD 选项，可在打印中途切换工具。
     * 所有适用的工具属性都会迁移，使打印得以继续。
     * 各工具必须高度匹配，可能还有其他限制。
     * 适用于：
     *   - 不中断地更换耗材颜色
     *   - 耗材用尽时自动切换料盘
     *   - 挤出机卡料时切换到其他喷嘴
     */
    #define TOOLCHANGE_MIGRATION_FEATURE

  #endif

  /**
   * 换刀时停放打印头的位置。
   * 不适用于 SWITCHING_TOOLHEAD、DUAL_X_CARRIAGE 或 PARKING_EXTRUDER
   */
  //#define TOOLCHANGE_PARK
  #if ENABLED(TOOLCHANGE_PARK)
    #define TOOLCHANGE_PARK_XY    { X_MIN_POS + 10, Y_MIN_POS + 10 }
    #define TOOLCHANGE_PARK_XY_FEEDRATE 6000  // (mm/min)
    //#define TOOLCHANGE_PARK_X_ONLY          // 仅移动 X 轴
    //#define TOOLCHANGE_PARK_Y_ONLY          // 仅移动 Y 轴
  #endif
#endif // HAS_MULTI_EXTRUDER

// @section advanced pause

/**
 * 换耗材的高级暂停
 *  - 增加 M600 换耗材 G 代码，用于启动换耗材。
 *  - 默认的 FILAMENT_RUNOUT_SCRIPT 需要此功能。
 *
 * 要求：
 *  - 换耗材停放需启用并配置 NOZZLE_PARK_FEATURE。
 *  - 需要用户交互，请启用 LCD 显示屏、HOST_PROMPT_SUPPORT 或 EMERGENCY_PARSER。
 *
 * 启用 PARK_HEAD_ON_PAUSE 可增加 M125 暂停并停放 G 代码。
 */
//#define ADVANCED_PAUSE_FEATURE
#if ENABLED(ADVANCED_PAUSE_FEATURE)
  #define PAUSE_PARK_RETRACT_FEEDRATE         60  // (mm/s) 初始回抽进给速度。
  #define PAUSE_PARK_RETRACT_LENGTH            2  // (mm) 初始回抽。
                                                  // 此短回抽在停放喷嘴之前立即执行。
  #define FILAMENT_CHANGE_UNLOAD_FEEDRATE     10  // (mm/s) 卸料进给速度。可以相当快。
  #define FILAMENT_CHANGE_UNLOAD_ACCEL        25  // (mm/s^2) 较低的加速度可以允许更快的进给速度。
  #define FILAMENT_CHANGE_UNLOAD_LENGTH      100  // (mm) 完整卸料所需的耗材长度。
                                                  //   对于 Bowden，为管路加喷嘴的总长度。
                                                  //   对于直接驱动，为喷嘴的全长。
                                                  //   设为 0 表示手动卸料。
  #define FILAMENT_CHANGE_SLOW_LOAD_FEEDRATE   6  // (mm/s) 开始装料时的慢速移动。
  #define FILAMENT_CHANGE_SLOW_LOAD_LENGTH     0  // (mm) 慢速长度，以留出插入耗材的时间。
                                                  // 0 表示禁用起始装料，直接进入快速装料
  #define FILAMENT_CHANGE_FAST_LOAD_FEEDRATE   6  // (mm/s) 装料进给速度。可以相当快。
  #define FILAMENT_CHANGE_FAST_LOAD_ACCEL     25  // (mm/s^2) 较低的加速度可以允许更快的进给速度。
  #define FILAMENT_CHANGE_FAST_LOAD_LENGTH     0  // (mm) 耗材的装料长度，从挤出机齿轮到喷嘴。
                                                  //   对于 Bowden，为管路加喷嘴的总长度。
                                                  //   对于直接驱动，为喷嘴的全长。
  //#define ADVANCED_PAUSE_CONTINUOUS_PURGE       // 持续吹扫直到达到吹扫长度或被中断。
  #define ADVANCED_PAUSE_PURGE_FEEDRATE        3  // (mm/s) 挤出进给速度（装料后）。应比装料进给速度慢。
  #define ADVANCED_PAUSE_PURGE_LENGTH         50  // (mm) 装料后挤出的长度。
                                                  //   设为 0 表示手动挤出。
                                                  //   可在换耗材菜单中反复挤出耗材，
                                                  //   直到挤出稳定，并清除旧耗材。
  #define ADVANCED_PAUSE_RESUME_PRIME          0  // (mm) 从停放位置返回后顶出喷嘴的额外距离。
  //#define ADVANCED_PAUSE_FANS_PAUSE             // 机器暂停时关闭打印冷却风扇。

                                                  // 卸料前先执行回抽、延时和吹扫：
  #define FILAMENT_UNLOAD_PURGE_RETRACT       13  // (mm) 卸料的初始回抽长度。
  #define FILAMENT_UNLOAD_PURGE_DELAY       5000  // (ms) 回抽后等待耗材冷却的延时。
  #define FILAMENT_UNLOAD_PURGE_LENGTH         8  // (mm) 先执行一次解除回抽，然后吹扫此长度。
  #define FILAMENT_UNLOAD_PURGE_FEEDRATE      25  // (mm/s) 卸料前吹扫的进给速度

  #define PAUSE_PARK_NOZZLE_TIMEOUT           45  // (seconds) 为安全起见，喷嘴关闭前的时限。
  #define FILAMENT_CHANGE_ALERT_BEEPS         10  // 需要响应时提示音的蜂鸣次数。
  #define PAUSE_PARK_NO_STEPPER_TIMEOUT           // 启用后，换耗材期间 XYZ 步进电机保持通电。
  //#define FILAMENT_CHANGE_RESUME_ON_INSERT      // 耗材耗尽传感器再次触发时自动继续/装料。
  //#define PAUSE_REHEAT_FAST_RESUME              // 超时后不再提示，从而减少等待次数。

  //#define PARK_HEAD_ON_PAUSE                    // 暂停和换耗材期间停放喷嘴。
  //#define HOME_BEFORE_FILAMENT_CHANGE           // 如有需要，换耗材停放前先归位

  //#define FILAMENT_LOAD_UNLOAD_GCODES           // 增加 M701/M702 装料/卸料 G 代码，并在 LCD 准备菜单中增加装料/卸料项。
  //#define FILAMENT_UNLOAD_ALL_EXTRUDERS         // 允许 M702 卸下所有目标温度高于最低值（由 M302 设置）的挤出机
#endif

// @section tmc_smart

/**
 * Trinamic 智能驱动
 *
 * 要在 SPI 模式下使用 TMC2130、TMC2160、TMC2660、TMC5130、TMC5160 步进电机驱动：
 *  - 将 SPI 引脚连接到板载硬件 SPI 接口。
 *    有些板子只需简单的跳线连接！请查阅你所用板子的文档。
 *  - 在你的 `pins_MYBOARD.h` 文件中定义所需的步进电机 CS 引脚。
 *    （例如可参考 RAMPS 的引脚定义。）
 *  - 也可以用 GPIO 引脚配合软件 SPI 代替硬件 SPI。
 *
 * 要用串行 UART 使用 TMC220x 步进电机驱动：
 *  - 通过 1K 电阻将 PDN_UART 连接到 #_SERIAL_TX_PIN。
 *    若需读取能力信息，还需将 PDN_UART 无电阻地连接到 #_SERIAL_RX_PIN。
 *    有些板子只需简单的跳线连接！请查阅你所用板子的文档。
 *  - 这些驱动也可配合硬件串口使用。
 *
 * TMC26X 步进电机驱动需要 TMC26XStepper 库。
 *   https://github.com/MarlinFirmware/TMC26XStepper
 *
 * 其他 TMC 步进电机驱动需要 TMCStepper 库。
 *   https://github.com/teemuatlut/TMCStepper
 *
 * @section tmc/config
 */
#if HAS_TRINAMIC_CONFIG || HAS_TMC26X

  #define HOLD_MULTIPLIER    0.5  // 按运行电流的比例调低保持电流

  /**
   * 将微步插值到 256
   * 可用下面的 <driver>_INTERPOLATE 设置为每个驱动单独覆盖
   */
  #define INTERPOLATE      true

  #if AXIS_IS_TMC_CONFIG(X)
    #define X_CURRENT       800        // (mA) RMS 电流。峰值电流需乘以 1.414。
    #define X_CURRENT_HOME  1000  // (mA) 无传感器归位时的 RMS 电流
    #define X_MICROSTEPS     64        // 0..256
    #define X_RSENSE          0.11     // TMC26X 时乘以 x1000
    #define X_CHAIN_POS      -1        // -1..0: 不串联。1: MCU MOSI 已连接。2: 链中的下一个，...
    //#define X_INTERPOLATE  true      // 启用以覆盖 X 轴的 'INTERPOLATE'
    //#define X_HOLD_MULTIPLIER 0.5    // 启用以覆盖 X 轴的 'HOLD_MULTIPLIER'
  #endif

  #if AXIS_IS_TMC_CONFIG(X2)
    #define X2_CURRENT      800
    #define X2_CURRENT_HOME X2_CURRENT
    #define X2_MICROSTEPS    X_MICROSTEPS
    #define X2_RSENSE         0.11
    #define X2_CHAIN_POS     -1
    //#define X2_INTERPOLATE true
    //#define X2_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(Y)
    #define Y_CURRENT       1000
    #define Y_CURRENT_HOME  Y_CURRENT
    #define Y_MICROSTEPS     64
    #define Y_RSENSE          0.11
    #define Y_CHAIN_POS      -1
    //#define Y_INTERPOLATE  true
    //#define Y_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(Y2)
    #define Y2_CURRENT      Y_CURRENT
    #define Y2_CURRENT_HOME Y2_CURRENT
    #define Y2_MICROSTEPS    Y_MICROSTEPS
    #define Y2_RSENSE         0.11
    #define Y2_CHAIN_POS     -1
    //#define Y2_INTERPOLATE true
    //#define Y2_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(Z)
    #define Z_CURRENT       800
    #define Z_CURRENT_HOME  Z_CURRENT
    #define Z_MICROSTEPS      8
    #define Z_RSENSE          0.11
    #define Z_CHAIN_POS      -1
    //#define Z_INTERPOLATE  true
    //#define Z_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(Z2)
    #define Z2_CURRENT      800
    #define Z2_CURRENT_HOME Z2_CURRENT
    #define Z2_MICROSTEPS    Z_MICROSTEPS
    #define Z2_RSENSE         0.11
    #define Z2_CHAIN_POS     -1
    //#define Z2_INTERPOLATE true
    //#define Z2_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(Z3)
    #define Z3_CURRENT      800
    #define Z3_CURRENT_HOME Z3_CURRENT
    #define Z3_MICROSTEPS    Z_MICROSTEPS
    #define Z3_RSENSE         0.11
    #define Z3_CHAIN_POS     -1
    //#define Z3_INTERPOLATE true
    //#define Z3_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(Z4)
    #define Z4_CURRENT      800
    #define Z4_CURRENT_HOME Z4_CURRENT
    #define Z4_MICROSTEPS    Z_MICROSTEPS
    #define Z4_RSENSE         0.11
    #define Z4_CHAIN_POS     -1
    //#define Z4_INTERPOLATE true
    //#define Z4_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(I)
    #define I_CURRENT      200
    #define I_CURRENT_HOME I_CURRENT
    #define I_MICROSTEPS     8
    #define I_RSENSE         0.11
    #define I_CHAIN_POS     -1
    //#define I_INTERPOLATE  true
    //#define I_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(J)
    #define J_CURRENT      200
    #define J_CURRENT_HOME J_CURRENT
    #define J_MICROSTEPS     8
    #define J_RSENSE         0.11
    #define J_CHAIN_POS     -1
    //#define J_INTERPOLATE  true
    //#define J_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(K)
    #define K_CURRENT      800
    #define K_CURRENT_HOME K_CURRENT
    #define K_MICROSTEPS    16
    #define K_RSENSE         0.11
    #define K_CHAIN_POS     -1
    //#define K_INTERPOLATE  true
    //#define K_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(U)
    #define U_CURRENT      800
    #define U_CURRENT_HOME U_CURRENT
    #define U_MICROSTEPS     8
    #define U_RSENSE         0.11
    #define U_CHAIN_POS     -1
    //#define U_INTERPOLATE  true
    //#define U_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(V)
    #define V_CURRENT      800
    #define V_CURRENT_HOME V_CURRENT
    #define V_MICROSTEPS     8
    #define V_RSENSE         0.11
    #define V_CHAIN_POS     -1
    //#define V_INTERPOLATE  true
    //#define V_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(W)
    #define W_CURRENT      800
    #define W_CURRENT_HOME W_CURRENT
    #define W_MICROSTEPS     8
    #define W_RSENSE         0.11
    #define W_CHAIN_POS     -1
    //#define W_INTERPOLATE  true
    //#define W_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(E0)
    #define E0_CURRENT      800
    #define E0_MICROSTEPS    16
    #define E0_RSENSE         0.11
    #define E0_CHAIN_POS     -1
    //#define E0_INTERPOLATE true
    //#define E0_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(E1)
    #define E1_CURRENT      800
    #define E1_MICROSTEPS   E0_MICROSTEPS
    #define E1_RSENSE         0.11
    #define E1_CHAIN_POS     -1
    //#define E1_INTERPOLATE true
    //#define E1_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(E2)
    #define E2_CURRENT      800
    #define E2_MICROSTEPS   E0_MICROSTEPS
    #define E2_RSENSE         0.11
    #define E2_CHAIN_POS     -1
    //#define E2_INTERPOLATE true
    //#define E2_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(E3)
    #define E3_CURRENT      800
    #define E3_MICROSTEPS   E0_MICROSTEPS
    #define E3_RSENSE         0.11
    #define E3_CHAIN_POS     -1
    //#define E3_INTERPOLATE true
    //#define E3_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(E4)
    #define E4_CURRENT      800
    #define E4_MICROSTEPS   E0_MICROSTEPS
    #define E4_RSENSE         0.11
    #define E4_CHAIN_POS     -1
    //#define E4_INTERPOLATE true
    //#define E4_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(E5)
    #define E5_CURRENT      800
    #define E5_MICROSTEPS   E0_MICROSTEPS
    #define E5_RSENSE         0.11
    #define E5_CHAIN_POS     -1
    //#define E5_INTERPOLATE true
    //#define E5_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(E6)
    #define E6_CURRENT      800
    #define E6_MICROSTEPS   E0_MICROSTEPS
    #define E6_RSENSE         0.11
    #define E6_CHAIN_POS     -1
    //#define E6_INTERPOLATE true
    //#define E6_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(E7)
    #define E7_CURRENT      800
    #define E7_MICROSTEPS   E0_MICROSTEPS
    #define E7_RSENSE         0.11
    #define E7_CHAIN_POS     -1
    //#define E7_INTERPOLATE true
    //#define E7_HOLD_MULTIPLIER 0.5
  #endif

  // @section tmc/spi

  /**
   * 在此覆盖 TMC2130、TMC2160、TMC2660、TMC5130 和 TMC5160 驱动的默认 SPI 引脚。
   * 默认引脚可在你所用板子的引脚文件中找到。
   */
  //#define X_CS_PIN      -1
  //#define Y_CS_PIN      -1
  //#define Z_CS_PIN      -1
  //#define X2_CS_PIN     -1
  //#define Y2_CS_PIN     -1
  //#define Z2_CS_PIN     -1
  //#define Z3_CS_PIN     -1
  //#define Z4_CS_PIN     -1
  //#define I_CS_PIN      -1
  //#define J_CS_PIN      -1
  //#define K_CS_PIN      -1
  //#define U_CS_PIN      -1
  //#define V_CS_PIN      -1
  //#define W_CS_PIN      -1
  //#define E0_CS_PIN     -1
  //#define E1_CS_PIN     -1
  //#define E2_CS_PIN     -1
  //#define E3_CS_PIN     -1
  //#define E4_CS_PIN     -1
  //#define E5_CS_PIN     -1
  //#define E6_CS_PIN     -1
  //#define E7_CS_PIN     -1

  /**
   * SPI 驱动（TMC2130、TMC2160、TMC2660、TMC5130 和 TMC5160）的软件选项。
   * 默认的 SW SPI 引脚定义在相应的引脚文件中，
   * 但你可以在此覆盖或重新定义。
   */
  #define TMC_USE_SW_SPI
  //#define TMC_SPI_MOSI  -1
  //#define TMC_SPI_MISO  -1
  //#define TMC_SPI_SCK   -1

  // @section tmc/serial

  /**
   * 四个 TMC2209 驱动可以通过硬件配置的地址共用同一个硬件/软件串口。
   * 使用 MS1 和 MS2 引脚上的跳线设置地址。
   * 地址    | MS1  | MS2
   *       0 | LOW  | LOW
   *       1 | HIGH | LOW
   *       2 | LOW  | HIGH
   *       3 | HIGH | HIGH
   *
   * 为同一串口上的所有驱动设置匹配的 *_SERIAL_TX_PIN 和 *_SERIAL_RX_PIN，
   * 可在此处设置，也可在你所用板子的引脚文件中设置。
   */
  //#define  X_SLAVE_ADDRESS 0
  //#define  Y_SLAVE_ADDRESS 0
  //#define  Z_SLAVE_ADDRESS 0
  //#define X2_SLAVE_ADDRESS 0
  //#define Y2_SLAVE_ADDRESS 0
  //#define Z2_SLAVE_ADDRESS 0
  //#define Z3_SLAVE_ADDRESS 0
  //#define Z4_SLAVE_ADDRESS 0
  //#define  I_SLAVE_ADDRESS 0
  //#define  J_SLAVE_ADDRESS 0
  //#define  K_SLAVE_ADDRESS 0
  //#define  U_SLAVE_ADDRESS 0
  //#define  V_SLAVE_ADDRESS 0
  //#define  W_SLAVE_ADDRESS 0
  //#define E0_SLAVE_ADDRESS 0
  //#define E1_SLAVE_ADDRESS 0
  //#define E2_SLAVE_ADDRESS 0
  //#define E3_SLAVE_ADDRESS 0
  //#define E4_SLAVE_ADDRESS 0
  //#define E5_SLAVE_ADDRESS 0
  //#define E6_SLAVE_ADDRESS 0
  //#define E7_SLAVE_ADDRESS 0

  // @section tmc/smart

  /**
   * 软件使能
   *
   * 适用于没有专用使能引脚、而是通过 SPI 或 UART 等通信
   * 线路来处理相同功能的驱动。
   */
  //#define SOFTWARE_DRIVER_ENABLE

  // @section tmc/stealthchop

  /**
   * 仅适用于 TMC2130、TMC2160、TMC2208、TMC2209、TMC5130 和 TMC5160
   * 使用 Trinamic 的超静音步进模式。
   * 禁用后 Marlin 将使用 spreadCycle 步进模式。
   */
  #if HAS_STEALTHCHOP
    //#define STEALTHCHOP_XY
    #define STEALTHCHOP_Z
    #define STEALTHCHOP_I
    #define STEALTHCHOP_J
    #define STEALTHCHOP_K
    #define STEALTHCHOP_U
    #define STEALTHCHOP_V
    #define STEALTHCHOP_W
    #define STEALTHCHOP_E
  #endif

  /**
   * 通过使用预定义的参数集来优化 spreadCycle 斩波器参数，
   * 或借助库中附带的示例。
   * 提供的参数集有
   * CHOPPER_DEFAULT_12V
   * CHOPPER_DEFAULT_19V
   * CHOPPER_DEFAULT_24V
   * CHOPPER_DEFAULT_36V
   * CHOPPER_09STEP_24V   // 0.9 度步进电机 (24V)
   * CHOPPER_PRUSAMK3_24V // 从官方 Průša MK3 固件导入的参数 (24V)
   * CHOPPER_MARLIN_119   // Marlin v1.1.9 的旧默认值
   *
   * 用以下格式定义自己的参数：
   * { <off_time[1..15]>, <hysteresis_end[-3..12]>, hysteresis_start[1..8] }
   */
  #define CHOPPER_TIMING CHOPPER_DEFAULT_24V        // 所有轴（在下面覆盖）
  //#define CHOPPER_TIMING_X  CHOPPER_TIMING        // 用于 X 轴（在下面覆盖）
  //#define CHOPPER_TIMING_X2 CHOPPER_TIMING_X
  //#define CHOPPER_TIMING_Y  CHOPPER_TIMING        // 用于 Y 轴（在下面覆盖）
  //#define CHOPPER_TIMING_Y2 CHOPPER_TIMING_Y
  //#define CHOPPER_TIMING_Z  CHOPPER_TIMING        // 用于 Z 轴（在下面覆盖）
  //#define CHOPPER_TIMING_Z2 CHOPPER_TIMING_Z
  //#define CHOPPER_TIMING_Z3 CHOPPER_TIMING_Z
  //#define CHOPPER_TIMING_Z4 CHOPPER_TIMING_Z
  //#define CHOPPER_TIMING_I  CHOPPER_TIMING        // 用于 I 轴
  //#define CHOPPER_TIMING_J  CHOPPER_TIMING        // 用于 J 轴
  //#define CHOPPER_TIMING_K  CHOPPER_TIMING        // 用于 K 轴
  //#define CHOPPER_TIMING_U  CHOPPER_TIMING        // 用于 U 轴
  //#define CHOPPER_TIMING_V  CHOPPER_TIMING        // 用于 V 轴
  //#define CHOPPER_TIMING_W  CHOPPER_TIMING        // 用于 W 轴
  //#define CHOPPER_TIMING_E  CHOPPER_TIMING        // 用于挤出机（在下面覆盖）
  //#define CHOPPER_TIMING_E1 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E2 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E3 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E4 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E5 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E6 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E7 CHOPPER_TIMING_E

  // @section tmc/status

  /**
   * 监控 Trinamic 驱动
   * 的错误状况，如过温和对地短路。
   * 为处理过温，Marlin 可以降低驱动电流直至错误状况消除。
   * 其他检测到的状况可用于停止当前打印。
   * 相关 G 代码：
   * M906 - 使用轴代码 X、Y、Z、E 以毫安为单位设置或读取电机电流。未指定轴代码时报告数值。
   * M911 - 报告步进电机驱动的过温预警状态。
   * M912 - 清除步进电机驱动的过温预警标志。
   * M122 - 报告驱动参数（需要 TMC_DEBUG）
   */
  //#define MONITOR_DRIVER_STATUS

  #if ENABLED(MONITOR_DRIVER_STATUS)
    #define CURRENT_STEP_DOWN     50  // [mA]
    #define REPORT_CURRENT_CHANGE
    #define STOP_ON_ERROR
  #endif

  // @section tmc/hybrid

  /**
   * 仅适用于 TMC2130、TMC2160、TMC2208、TMC2209、TMC5130 和 TMC5160
   * 当步进速度超过 HYBRID_THRESHOLD 时，驱动会切换到 spreadCycle。
   * 该模式以更高的噪声为代价换取更快的移动速度。
   * 使用 HYBRID_THRESHOLD 前必须启用 STEALTHCHOP_(XY|Z|E)。
   * M913 X/Y/Z/E 可实时调整该设置
   */
  //#define HYBRID_THRESHOLD

  #define X_HYBRID_THRESHOLD     100  // [mm/s]
  #define X2_HYBRID_THRESHOLD    100
  #define Y_HYBRID_THRESHOLD     100
  #define Y2_HYBRID_THRESHOLD    100
  #define Z_HYBRID_THRESHOLD       3
  #define Z2_HYBRID_THRESHOLD      3
  #define Z3_HYBRID_THRESHOLD      3
  #define Z4_HYBRID_THRESHOLD      3
  #define I_HYBRID_THRESHOLD       3  // [linear=mm/s, rotational=°/s]
  #define J_HYBRID_THRESHOLD       3  // [linear=mm/s, rotational=°/s]
  #define K_HYBRID_THRESHOLD       3  // [linear=mm/s, rotational=°/s]
  #define U_HYBRID_THRESHOLD       3  // [mm/s]
  #define V_HYBRID_THRESHOLD       3
  #define W_HYBRID_THRESHOLD       3
  #define E0_HYBRID_THRESHOLD     30
  #define E1_HYBRID_THRESHOLD     30
  #define E2_HYBRID_THRESHOLD     30
  #define E3_HYBRID_THRESHOLD     30
  #define E4_HYBRID_THRESHOLD     30
  #define E5_HYBRID_THRESHOLD     30
  #define E6_HYBRID_THRESHOLD     30
  #define E7_HYBRID_THRESHOLD     30

  /**
   * 使用 StallGuard 对 X、Y、Z 进行归位/探测。
   *
   * 仅适用于 TMC2130、TMC2160、TMC2209、TMC2660、TMC5130 和 TMC5160
   * 将步进电机驱动的 DIAG1 引脚连接到 X/Y 限位开关引脚。
   * X、Y 和 Z 的归位始终在 spreadCycle 模式下进行。
   *
   * X/Y/Z_STALL_SENSITIVITY 是默认的失速阈值。
   * 使用 M914 X Y Z 在运行时设置失速阈值：
   *
   *  灵敏度        TMC2209   其他
   *    最高          255      -64    (过于灵敏 => 误触发)
   *    最低           0        63    (过于迟钝 => 不触发)
   *
   * 建议将 HOMING_BUMP_MM 设为 { 0, 0, 0 }。
   *
   * SPI_ENDSTOPS  *** 仅限 TMC2130/TMC5160 ***
   * 归位时通过 SPI 轮询驱动以判断负载。
   * 这样无需再从 DIAG1 引线到限位开关引脚。
   *
   * IMPROVE_HOMING_RELIABILITY 会调整归位时的
   * 加速度和加加速度，并为限位开关触发增加保护时间。
   *
   * 注释掉 *_STALL_SENSITIVITY 可禁用该轴的无传感器归位。
   * @section tmc/stallguard
   */
  //#define SENSORLESS_HOMING // 仅限支持 StallGuard 的驱动
  //#define SENSORLESS_STALLGUARD_DELAY 20

  #if EITHER(SENSORLESS_HOMING, SENSORLESS_PROBING)
    // TMC2209: 0...255. TMC2130: -64...63
    #define X_STALL_SENSITIVITY 120
    #define X2_STALL_SENSITIVITY X_STALL_SENSITIVITY
    #define Y_STALL_SENSITIVITY 100
    #define Y2_STALL_SENSITIVITY Y_STALL_SENSITIVITY
    //#define Z_STALL_SENSITIVITY  8
    //#define Z2_STALL_SENSITIVITY Z_STALL_SENSITIVITY
    //#define Z3_STALL_SENSITIVITY Z_STALL_SENSITIVITY
    //#define Z4_STALL_SENSITIVITY Z_STALL_SENSITIVITY
    //#define I_STALL_SENSITIVITY  8
    //#define J_STALL_SENSITIVITY  8
    //#define K_STALL_SENSITIVITY  8
    //#define U_STALL_SENSITIVITY  8
    //#define V_STALL_SENSITIVITY  8
    //#define W_STALL_SENSITIVITY  8
    //#define SPI_ENDSTOPS              // 仅限 TMC2130/TMC5160
    //#define IMPROVE_HOMING_RELIABILITY
  #endif

  // @section tmc/config

  /**
   * TMC 归位步进相位。
   *
   * 通过归位到步进电机线圈最近的绝对
   * 相位位置来提高归位重复性。Trinamic 驱动使用包含 1024 个值的步进相位表，
   * 覆盖 4 个整步，每步 256 个位置（即共 1024 个位置）。
   * 整步位置（128、384、640、896）具有最大的保持扭矩。
   *
   * 取值范围 0..1023，-1 表示禁用该轴的归位相位。
   */
   #define TMC_HOME_PHASE { 896, 896, 896 }

  /**
   * 在上升沿和下降沿信号上都步进（如同方波）。
   */
  //#define EDGE_STEPPING

  /**
   * 为 TMC 步进电机驱动启用 M122 调试命令。
   * M122 S0/1 将启用连续报告。
   */
  #define TMC_DEBUG

  /**
   * 你可以通过填写预定义函数来自定义高级设置。
   * 可用函数列表见该库的 github 页面
   * https://github.com/teemuatlut/TMCStepper
   *
   * 示例：
   * #define TMC_ADV() { \
   *   stepperX.diag0_otpw(1); \
   *   stepperY.intpol(0); \
   * }
   */
  #define TMC_ADV() {  }

#endif // HAS_TRINAMIC_CONFIG || HAS_TMC26X

// @section i2cbus

//
// 用于 LPC176x LCD 和数字电流控制的 I2C 主机 ID
// 不适用于基于 Wire 库的其他外设。
//
//#define I2C_MASTER_ID  1  // 取 0 到 2 之间的值

/**
 * TWI/I2C 总线
 *
 * 此功能为实验性功能，不应在生产
 * 机器上使用。启用后可以向总线上的从设备
 * 发送和接收 I2C 数据。
 *
 * ; 示例 #1
 * ; 此宏将字符串 "Marlin" 发送到地址为 0x63 (99) 的从设备
 * ; 它使用多条带一个 B<base 10> 参数的 M260 命令
 * M260 A99  ; 目标从设备地址
 * M260 B77  ; M
 * M260 B97  ; a
 * M260 B114 ; r
 * M260 B108 ; l
 * M260 B105 ; i
 * M260 B110 ; n
 * M260 S1   ; 发送当前缓冲区
 *
 * ; 示例 #2
 * ; 向地址为 0x63 (99) 的从设备请求 6 个字节
 * M261 A99 B5
 *
 * ; 示例 #3
 * ; M261 请求的串口输出示例
 * echo:i2c-reply: from:99 bytes:5 data:hello
 */

#define EXPERIMENTAL_I2CBUS
#if ENABLED(EXPERIMENTAL_I2CBUS)
  #define I2C_SLAVE_ADDRESS  0  // 取 8 到 127 之间的值以作为从设备
#endif

// @section photo

/**
 * 拍照 G 代码
 * 增加 M240 G 代码用于拍照。
 * 拍照可由数字引脚或物理移动触发。
 */
//#define PHOTO_GCODE
#if ENABLED(PHOTO_GCODE)
  // 拍照前要移动到的位置（并抬升 Z）
  //#define PHOTO_POSITION { X_MAX_POS - 5, Y_MAX_POS, 0 }  // { xpos, ypos, zraise } (M240 X Y Z)
  //#define PHOTO_DELAY_MS   100                            // (ms) 返回移动前的暂停时长 (M240 P)
  //#define PHOTO_RETRACT_MM   6.5                          // (mm) 拍照移动的 E 轴回抽/恢复 (M240 R S)

  // Canon RC-1 或自制的数码相机快门触发器
  // 资料来自：https://www.doc-diy.net/photo/rc-1_hacked/
  //#define PHOTOGRAPH_PIN 23

  // Canon 破解开发套件
  // https://captain-slow.dk/2014/03/09/3d-printing-timelapses/
  //#define CHDK_PIN        4

  // 可选的第二次移动，带延时以触发相机快门
  //#define PHOTO_SWITCH_POSITION { X_MAX_POS, Y_MAX_POS }  // { xpos, ypos } (M240 I J)

  // 保持开关按下或 CHDK_PIN 保持高电平的时长
  //#define PHOTO_SWITCH_MS   50 // (ms) (M240 D)

  /**
   * PHOTO_PULSES_US 可能需要根据主板和相机型号进行调整。
   * 引脚必须运行在 48.4kHz。
   * 请确保使用上升沿和下降沿足够快的 PHOTOGRAPH_PIN。
   * （例如，MKS SBase 的温度传感器引脚太慢，因此改用 J8 上的 P1.23。）
   *
   *  尼康的脉冲数据示例：https://bit.ly/2FKD0Aq
   *                     红外接线：https://git.io/JvJf7
   */
  //#define PHOTO_PULSES_US { 2000, 27850, 400, 1580, 400, 3580, 400 }  // (µs) 48.4kHz 振荡中每个脉冲的持续时间
  #ifdef PHOTO_PULSES_US
    #define PHOTO_PULSE_DELAY_US 13 // (µs) 振荡中每个高电平和低电平脉冲的近似持续时间
  #endif
#endif

// @section cnc

/**
 * 主轴与激光控制
 *
 * 增加 M3、M4 和 M5 命令以开启/关闭主轴/激光，以及
 * 设置主轴转速、主轴方向和激光功率。
 *
 * SuperPid 是 CNC 铣削社区常用的雕刻机/主轴转速控制器。
 * Marlin 可用于开启和关闭主轴，也可用于设置
 * 主轴转速，范围为 5,000 到 30,000 RPM。
 *
 * 你需要为 ON/OFF 功能选择一个引脚，并可选择 0-5V 的
 * 硬件 PWM 引脚用于速度控制，以及一个用于旋转方向的引脚。
 *
 * 更多配置详情请见 https://marlinfw.org/docs/configuration/2.0.9/laser_spindle.html。
 */
//#define SPINDLE_FEATURE
//#define LASER_FEATURE
#if EITHER(SPINDLE_FEATURE, LASER_FEATURE)
  #define SPINDLE_LASER_ACTIVE_STATE    LOW    // 若 SPINDLE_LASER_ENA_PIN 为高电平有效，则设为 "HIGH"

  #define SPINDLE_LASER_USE_PWM                // 如果你的控制器支持设置速度/功率则启用
  #if ENABLED(SPINDLE_LASER_USE_PWM)
    #define SPINDLE_LASER_PWM_INVERT    false  // 如果希望在需要减速时速度/功率反而升高，则设为 "true"
    #define SPINDLE_LASER_FREQUENCY     2500   // (Hz) 主轴/激光频率（仅部分 HAL 支持：AVR、ESP32 和 LPC）
                                               // ESP32: 若 SPINDLE_LASER_PWM_PIN 为板载引脚则 <=78125Hz。对于 I2S 扩展
                                               //  频率决定 PWM 分辨率。2500Hz = 0-100，977Hz = 0-255，...
                                               //  (250000 / SPINDLE_LASER_FREQUENCY) = 最大值。
  #endif

  //#define AIR_EVACUATION                     // 用 G 代码 M10-M11 控制切削吸尘/激光吹风电机
  #if ENABLED(AIR_EVACUATION)
    #define AIR_EVACUATION_ACTIVE       LOW    // 若开关功能为高电平有效，则设为 "HIGH"
    //#define AIR_EVACUATION_PIN        42     // 覆盖默认的切削吸尘或激光吹风引脚
  #endif

  //#define AIR_ASSIST                         // 用 G 代码 M8-M9 控制气动辅助
  #if ENABLED(AIR_ASSIST)
    #define AIR_ASSIST_ACTIVE           LOW    // 气动辅助引脚上的有效状态
    //#define AIR_ASSIST_PIN            44     // 覆盖默认的气动辅助引脚
  #endif

  //#define SPINDLE_SERVO                      // 将角度转换为主轴功率的舵机
  #ifdef SPINDLE_SERVO
    #define SPINDLE_SERVO_NR   0               // 用于主轴控制的舵机索引
    #define SPINDLE_SERVO_MIN 10               // 舵机主轴的最小角度
  #endif

  /**
   * 速度/功率可设置（'M3 S'），并以以下单位显示：
   *  - PWM255  (S0 - S255)
   *  - PERCENT (S0 - S100)
   *  - RPM     (S0 - S50000)  最适合配合主轴使用
   *  - SERVO   (S0 - S180)
   */
  #define CUTTER_POWER_UNIT PWM255

  /**
   * 相对切削功率
   * 通常，'M3 O<power>' 设置的
   * OCR 功率相对于 SPEED_POWER_MIN...SPEED_POWER_MAX 范围。
   * 因此输入的 0...255 功率对应 SPEED_POWER_MIN...SPEED_POWER_MAX
   * 而不是正常范围（0 到 SPEED_POWER_MAX）。
   * 最适合与（如）SuperPID 雕刻机控制器配合使用：S0 = 5,000 RPM，S255 = 30,000 RPM
   */
  //#define CUTTER_POWER_RELATIVE              // 使速度与 [SPEED_POWER_MIN...SPEED_POWER_MAX] 成比例

  #if ENABLED(SPINDLE_FEATURE)
    //#define SPINDLE_CHANGE_DIR               // 如果你的主轴控制器可以改变主轴方向则启用
    #define SPINDLE_CHANGE_DIR_STOP            // 如果希望改变旋转方向前先停止主轴则启用
    #define SPINDLE_INVERT_DIR          false  // 如果旋转方向相反则设为 "true"

    #define SPINDLE_LASER_POWERUP_DELAY   5000 // (ms) 等待主轴/激光达到速度/功率的延时
    #define SPINDLE_LASER_POWERDOWN_DELAY 5000 // (ms) 等待主轴停止的延时

    /**
     * M3/M4 功率公式
     *
     * 每种工具使用不同的速度/功率控制数值范围。
     * 这些参数用于在工具功率单位和 PWM 之间换算。
     *
     * Speed/Power = (PWMDC / 255 * 100 - SPEED_POWER_INTERCEPT) / SPEED_POWER_SLOPE
     * PWMDC = (spdpwr - SPEED_POWER_MIN) / (SPEED_POWER_MAX - SPEED_POWER_MIN) / SPEED_POWER_SLOPE
     */
    #if ENABLED(SPINDLE_LASER_USE_PWM)
      #define SPEED_POWER_INTERCEPT       0    // (%) 0-100 即最小功率百分比
      #define SPEED_POWER_MIN          5000    // (RPM)
      #define SPEED_POWER_MAX         30000    // (RPM) SuperPID 雕刻机控制器 0 - 30,000 RPM
      #define SPEED_POWER_STARTUP     25000    // (RPM) M3/M4 速度/功率默认值（无参数时）
    #endif

  #else

    #if ENABLED(SPINDLE_LASER_USE_PWM)
      #define SPEED_POWER_INTERCEPT       0    // (%) 0-100 即最小功率百分比
      #define SPEED_POWER_MIN             0    // (%) 0-100
      #define SPEED_POWER_MAX           100    // (%) 0-100
      #define SPEED_POWER_STARTUP        80    // (%) M3/M4 速度/功率默认值（无参数时）
    #endif

    // 定义激光试射功能的最小和最大测试脉冲时长
    #define LASER_TEST_PULSE_MIN           1   // (ms) 与激光控制菜单配合使用
    #define LASER_TEST_PULSE_MAX         999   // (ms) 注意：菜单最多只能显示 3 个字符

    #define SPINDLE_LASER_POWERUP_DELAY   50   // (ms) 等待主轴/激光达到速度/功率的延时
    #define SPINDLE_LASER_POWERDOWN_DELAY 50   // (ms) 等待主轴停止的延时

   /**
    * 激光安全超时
    *
    * 当一段时间内没有移动时，应关闭激光。
    * 设置此值时请考虑材料的易燃性、切割速度以及 G 代码顺序。
    * 值过小可能在非常缓慢的移动过程中关闭；过大则
    * 可能导致材料起火。
    */
    #define LASER_SAFETY_TIMEOUT_MS     1000   // (ms)

    /**
     * 任何带 'I' 参数的 M3 或 G1/2/3/5 命令都会启用连续内联功率模式。
     *
     * 例如，'M3 I' 启用由规划器处理的连续内联功率。
     * 功率存储在移动块中，并在步进中断服务程序处理这些块时生效。
     *
     * 'M4 I' 设置动态模式，使用当前进给速度计算激光功率 OCR 值。
     *
     * 动态模式下的任何移动都会使用当前进给速度计算激光功率。
     * 进给速度由移动命令的 F 参数设置，例如 G1 X0 Y10 F6000
     * 激光功率通过右移 8 个最低有效位计算。二进制下即除以 256。
     * 计算得到的 ocr 值为 0 到 255，超过 F65535 的值将按 255 处理。
     * 更精细的功率控制（如加速度/减速度补偿）将在后续版本中实现。
     *
     * M5 I 清除内联模式并将功率设为 0，M5 将功率输出设为 0 但保持内联模式开启。
     */

    /**
     * 为激光模式启用 M3 命令以同步内联功率规划器。
     * 此功能可在 CUTTER_MODE_CONTINUOUS 状态下将任意 M3 S 值注入区块
     * 缓冲区。该选项允许提交 M3 激光功率而无需等待
     * 规划器同步
     */
    //#define LASER_POWER_SYNC

    /**
     * 按移动速率成比例缩放激光功率。
     *
     * - 按进入速度与标称速度之比设置进入功率。
     * - 每 N 步提升一次功率，以逼近速度梯形。
     * - 由于功率分辨率有限，这只是近似值。
     */
    //#define LASER_POWER_TRAP

    //
    // 激光 I2C 电流表（高精度 INA226 高/低端模块）
    //
    //#define I2C_AMMETER
    #if ENABLED(I2C_AMMETER)
      #define I2C_AMMETER_IMAX            0.1    // (Amps) 预期电流范围的校准值
      #define I2C_AMMETER_SHUNT_RESISTOR  0.1    // (Ohms) 校准分流电阻值
    #endif

    //
    // 激光冷却液流量计
    //
    //#define LASER_COOLANT_FLOW_METER
    #if ENABLED(LASER_COOLANT_FLOW_METER)
      #define FLOWMETER_PIN         20  // 需要一个支持外部中断的引脚（例如 RAMPS 2,3,18,19,20,21）
      #define FLOWMETER_PPL       5880  // (pulses/liter) 流量计在输入引脚上的每升脉冲数
      #define FLOWMETER_INTERVAL  1000  // (ms) 流量计算间隔（毫秒）
      #define FLOWMETER_SAFETY          // 防止在未达到下方设定的最小流量时运行激光
      #if ENABLED(FLOWMETER_SAFETY)
        #define FLOWMETER_MIN_LITERS_PER_MINUTE 1.5 // (liters/min) 启用后所需的最小流量
      #endif
    #endif

  #endif
#endif // SPINDLE_FEATURE || LASER_FEATURE

/**
 * 通过 M106/M107 同步控制激光
 *
 * Marlin 通常在处理规划器区块后“不久”才应用 M106/M107 风扇速度。
 * 对于接在风扇排针上的 PWM/TTL 激光（如某些附加激光套件）来说，
 * 这样精度不够。启用此选项可以用精确得多的时序设置风扇/激光
 * 速度，从而提高打印保真度。
 *
 * 注意：此选项会牺牲部分冷却风扇速度选项。
 */
//#define LASER_SYNCHRONOUS_M106_M107

/**
 * 冷却液控制
 *
 * 添加 M7、M8 和 M9 命令，用于开启和关闭雾化或喷淋冷却液。
 *
 * 注意：还必须定义 COOLANT_MIST_PIN 和/或 COOLANT_FLOOD_PIN。
 */
//#define COOLANT_CONTROL
#if ENABLED(COOLANT_CONTROL)
  #define COOLANT_MIST                // 如果有雾化冷却液则启用
  #define COOLANT_FLOOD               // 如果有喷淋冷却液则启用
  #define COOLANT_MIST_INVERT  false  // 如果开关功能是反向的则设为 "true"
  #define COOLANT_FLOOD_INVERT false  // 如果开关功能是反向的则设为 "true"
#endif

// @section filament width

/**
 * 耗材宽度传感器
 *
 * 实时测量耗材宽度并调整
 * 流量，以补偿任何不规则变化。
 *
 * 还可以用测得的耗材直径来设定
 * 挤出率，这样切片软件只需指定
 * 体积。
 *
 * 目前仅支持单个挤出机。
 *
 *  34 RAMPS_14    : AUX2 连接器上的模拟输入 5
 *  81 PRINTRBOARD : Exp1 连接器上的模拟输入 2（版本 B、C、D、E）
 * 301 RAMBO       : 模拟输入 3
 *
 * 注意：其他板子可能还需要另外定义模拟引脚。
 */
//#define FILAMENT_WIDTH_SENSOR

#if ENABLED(FILAMENT_WIDTH_SENSOR)
  #define FILAMENT_SENSOR_EXTRUDER_NUM 0    // 安装耗材传感器的挤出机索引。 :[0,1,2,3,4]
  #define MEASUREMENT_DELAY_CM        14    // (cm) 耗材传感器到熔融腔的距离

  #define FILWIDTH_ERROR_MARGIN        1.0  // (mm) 若测量值与标称宽度差异过大则忽略
  #define MAX_MEASUREMENT_DELAY       20    // (bytes) 用于存储测量值的缓冲区大小（每 cm 1 字节）。必须大于 MEASUREMENT_DELAY_CM。

  #define DEFAULT_MEASURED_FILAMENT_DIA DEFAULT_NOMINAL_FILAMENT_DIA // 初始时将测量值设为标称值

  // 在 LCD 状态行上显示耗材宽度。状态信息将在 5 秒后过期。
  //#define FILAMENT_LCD_DISPLAY
#endif

// @section power

/**
 * 电源监控
 * 监控电压 (V) 和/或电流 (A)，以及（如有可能）功率 (W)
 *
 * 使用 M430 读取和配置
 *
 * 电流传感器向模拟引脚输出与所测电流成比例的直流电压
 * 电压传感器向模拟引脚输出与所测电压成比例的直流电压
 */
//#define POWER_MONITOR_CURRENT   // 监控系统电流
//#define POWER_MONITOR_VOLTAGE   // 监控系统电压

#if ENABLED(POWER_MONITOR_CURRENT)
  #define POWER_MONITOR_VOLTS_PER_AMP    0.05000  // MCU 模拟引脚每安培对应的输入电压  - 不得超过 ADC_VREF！
  #define POWER_MONITOR_CURRENT_OFFSET   0        // 施加到计算所得电流上的偏移量（以安培计）
  #define POWER_MONITOR_FIXED_VOLTAGE   13.6      // 无电压传感器时电流传感器所用的电压（用于功率显示）
#endif

#if ENABLED(POWER_MONITOR_VOLTAGE)
  #define POWER_MONITOR_VOLTS_PER_VOLT  0.077933  // MCU 模拟引脚每伏对应的输入电压 - 不得超过 ADC_VREF！
  #define POWER_MONITOR_VOLTAGE_OFFSET  0         // 施加到计算所得电压上的偏移量（以伏特计）
#endif

// @section safety

/**
 * 步进电机驱动防呆保护
 *
 * 如果你的板子定义了 SAFE_POWER_PIN，Marlin 会在上电之前检查
 * 步进电机驱动是否已正确插入。
 * 如果你的步进电机驱动不支持该功能，请禁用此保护。
 */
//#define DISABLE_DRIVER_SAFE_POWER_PROTECT

// @section cnc

/**
 * CNC 坐标系
 *
 * 启用 G53 和 G54-G59.3 命令以选择坐标系，
 * 并用 G92.1 将工作空间重置为机床原生空间。
 */
//#define CNC_COORDINATE_SYSTEMS

/**
 * CNC 钻孔循环 - 开发中
 *
 * 启用 G81 以执行钻孔循环。
 * 目前仅支持单个循环，不支持 G 代码链接。
 */
//#define CNC_DRILLING_CYCLE

// @section reporting

/**
 * 用 M123 S<seconds> 自动上报风扇转速
 * 需要带转速计引脚的风扇
 */
//#define AUTO_REPORT_FANS

/**
 * 用 M155 S<seconds> 自动上报温度
 */
#define AUTO_REPORT_TEMPERATURES
#if ENABLED(AUTO_REPORT_TEMPERATURES) && TEMP_SENSOR_REDUNDANT
  //#define AUTO_REPORT_REDUNDANT // 在自动上报中包含 "R" 传感器
#endif

/**
 * 用 M154 S<seconds> 自动上报位置
 */
//#define AUTO_REPORT_POSITION

/**
 * 在 M115 输出中包含功能能力信息
 */
#define EXTENDED_CAPABILITIES_REPORT
#if ENABLED(EXTENDED_CAPABILITIES_REPORT)
  //#define M115_GEOMETRY_REPORT
#endif

// @section security

/**
 * 打印机型号校验
 * 添加 M16 G 代码，用于将一个字符串与 MACHINE_NAME 比较。
 * M16 收到不匹配的字符串会使打印机停机。
 */
//#define EXPECTED_PRINTER_CHECK

// @section volumetrics

/**
 * 禁用所有体积挤出选项
 */
//#define NO_VOLUMETRICS

#if DISABLED(NO_VOLUMETRICS)
  /**
   * 体积挤出的默认状态
   * 启用后将体积挤出设为默认方式，
   * 并以 DEFAULT_NOMINAL_FILAMENT_DIA 作为默认直径。
   *
   * M200 D0 禁用，M200 Dn 设置新直径（并启用体积挤出）。
   * M200 S0/S1 禁用/启用体积挤出。
   */
  //#define VOLUMETRIC_DEFAULT_ON

  //#define VOLUMETRIC_EXTRUDER_LIMIT
  #if ENABLED(VOLUMETRIC_EXTRUDER_LIMIT)
    /**
     * 以立方毫米每秒 (mm^3/sec) 表示的体积挤出默认上限。
     * 该出厂设置适用于所有挤出机。
     * 用 'M200 [T<extruder>] L<limit>' 覆盖，用 'M502' 复位。
     * 非零值将启用基于体积的挤出限制。
     */
    #define DEFAULT_VOLUMETRIC_EXTRUDER_LIMIT 0.00      // (mm^3/sec)
  #endif
#endif

// @section reporting

// M114 "当前位置" 报告的附加选项
//#define M114_DETAIL         // 用 'M114` 显示详细信息以检查规划器的计算
//#define M114_REALTIME       // 基于正解运动学的实时当前位置
//#define M114_LEGACY         // M114 曾用于每次调用都同步。需要时启用。

//#define REPORT_FAN_CHANGE   // 当 M106（及其他命令）改变风扇转速时上报新转速

// @section gcode

/**
 * 花费 28 字节 SRAM 以优化 G 代码解析器
 */
#define FASTER_GCODE_PARSER

#if ENABLED(FASTER_GCODE_PARSER)
  #define GCODE_QUOTED_STRINGS    // 支持带引号的字符串参数
#endif

// 支持 MeatPack G 代码压缩 (https://github.com/scottmudge/OctoPrint-MeatPack)
//#define MEATPACK_ON_SERIAL_PORT_1
//#define MEATPACK_ON_SERIAL_PORT_2

//#define GCODE_CASE_INSENSITIVE  // 接受以小写形式发送给固件的 G 代码

//#define REPETIER_GCODE_M360     // 添加最初来自 Repetier 固件的命令

/**
 * 启用此选项可获得更精简的 Marlin 构建，移除所有
 * 工作空间偏移，从而简化坐标变换、调平等。
 *
 *  - M206 和 M428 将被禁用。
 *  - G92 将恢复为 Marlin 1.0 的行为。
 */
//#define NO_WORKSPACE_OFFSETS

/**
 * CNC G 代码选项
 * 支持激光切割机、绘图机凸轮等所用的 CNC 风格 G 代码方言。
 * 注意：在 3D 打印中应谨慎使用 G0 进给速度（如果确实要用的话）。
 * 过高的进给速度可能引起振铃并损害打印质量。
 */
//#define PAREN_COMMENTS      // 支持以括号分隔的注释
//#define GCODE_MOTION_MODES  // 记住运动模式 (G0 G1 G2 G3 G5 G38.X) 并应用于 X Y Z E F 等。

// 启用并为所有 G0 移动设置（默认）进给速度
//#define G0_FEEDRATE 3000 // (mm/min)
#ifdef G0_FEEDRATE
  //#define VARIABLE_G0_FEEDRATE // G0 进给速度由 G0 运动模式中的 F 设定
#endif
//#define G0_ANGULAR_FEEDRATE 2700 // (°/min)

// @section gcode

/**
 * 启动命令
 *
 * 上电后立即执行特定的 G 代码命令。
 */
#define STARTUP_COMMANDS "M300 S2000 P100\nG4 P900\nM300 S2000 P100\nG4 P900\nM300 S2000 P100\nG4 P900\nM300 S2000 P100\nG4 P900\nM300 S2000 P100\nG4 P400\nM300 S2000 P100\nG4 P400\nM300 S2000 P100\nG4 P400\nM300 S2000 P100\nG4 P400\nM300 S2000 P100\nG4 P150\nM300 S2000 P100\nG4 P150\nM300 S2000 P100\nG4 P150\nM300 S2000 P100\nG4 P150\nM300 S2500 P1000"
//#define STARTUP_COMMANDS "M300 S523 P150\nM300 S659 P150\nM300 S784 P300"
/**
 * G 代码宏
 *
 * 添加 G 代码 M810-M819 来定义和运行 G 代码宏。
 * 宏不会保存到 EEPROM。
 */
//#define GCODE_MACROS
#if ENABLED(GCODE_MACROS)
  #define GCODE_MACROS_SLOTS       5  // 最多可使用 10 个
  #define GCODE_MACROS_SLOT_SIZE  50  // 单个宏的最大长度
#endif

/**
 * 用户自定义菜单项，用于运行自定义 G 代码。
 * 最多可定义 25 个，但实际数量取决于 LCD。
 */

// @section custom main menu

// 自定义菜单：主菜单
//#define CUSTOM_MENU_MAIN
#if ENABLED(CUSTOM_MENU_MAIN)
  //#define CUSTOM_MENU_MAIN_TITLE "Custom Commands"
  #define CUSTOM_MENU_MAIN_SCRIPT_DONE "M117 User Script Done"
  #define CUSTOM_MENU_MAIN_SCRIPT_AUDIBLE_FEEDBACK
  //#define CUSTOM_MENU_MAIN_SCRIPT_RETURN   // 脚本运行后返回状态屏幕
  #define CUSTOM_MENU_MAIN_ONLY_IDLE         // 仅在机器空闲时显示自定义菜单

  #define MAIN_MENU_ITEM_1_DESC "Home & UBL Info"
  #define MAIN_MENU_ITEM_1_GCODE "G28\nG29 W"
  //#define MAIN_MENU_ITEM_1_CONFIRM          // 执行此操作前显示确认对话框

  #define MAIN_MENU_ITEM_2_DESC "Preheat for " PREHEAT_1_LABEL
  #define MAIN_MENU_ITEM_2_GCODE "M140 S" STRINGIFY(PREHEAT_1_TEMP_BED) "\nM104 S" STRINGIFY(PREHEAT_1_TEMP_HOTEND)
  //#define MAIN_MENU_ITEM_2_CONFIRM

  //#define MAIN_MENU_ITEM_3_DESC "Preheat for " PREHEAT_2_LABEL
  //#define MAIN_MENU_ITEM_3_GCODE "M140 S" STRINGIFY(PREHEAT_2_TEMP_BED) "\nM104 S" STRINGIFY(PREHEAT_2_TEMP_HOTEND)
  //#define MAIN_MENU_ITEM_3_CONFIRM

  //#define MAIN_MENU_ITEM_4_DESC "Heat Bed/Home/Level"
  //#define MAIN_MENU_ITEM_4_GCODE "M140 S" STRINGIFY(PREHEAT_2_TEMP_BED) "\nG28\nG29"
  //#define MAIN_MENU_ITEM_4_CONFIRM

  //#define MAIN_MENU_ITEM_5_DESC "Home & Info"
  //#define MAIN_MENU_ITEM_5_GCODE "G28\nM503"
  //#define MAIN_MENU_ITEM_5_CONFIRM
#endif

// @section custom config menu

// 自定义菜单：配置菜单
//#define CUSTOM_MENU_CONFIG
#if ENABLED(CUSTOM_MENU_CONFIG)
  //#define CUSTOM_MENU_CONFIG_TITLE "Custom Commands"
  #define CUSTOM_MENU_CONFIG_SCRIPT_DONE "M117 Wireless Script Done"
  #define CUSTOM_MENU_CONFIG_SCRIPT_AUDIBLE_FEEDBACK
  //#define CUSTOM_MENU_CONFIG_SCRIPT_RETURN  // 脚本运行后返回状态屏幕
  #define CUSTOM_MENU_CONFIG_ONLY_IDLE        // 仅在机器空闲时显示自定义菜单

  #define CONFIG_MENU_ITEM_1_DESC "Wifi ON"
  #define CONFIG_MENU_ITEM_1_GCODE "M118 [ESP110] WIFI-STA pwd=12345678"
  //#define CONFIG_MENU_ITEM_1_CONFIRM        // 执行此操作前显示确认对话框

  #define CONFIG_MENU_ITEM_2_DESC "Bluetooth ON"
  #define CONFIG_MENU_ITEM_2_GCODE "M118 [ESP110] BT pwd=12345678"
  //#define CONFIG_MENU_ITEM_2_CONFIRM

  //#define CONFIG_MENU_ITEM_3_DESC "Radio OFF"
  //#define CONFIG_MENU_ITEM_3_GCODE "M118 [ESP110] OFF pwd=12345678"
  //#define CONFIG_MENU_ITEM_3_CONFIRM

  //#define CONFIG_MENU_ITEM_4_DESC "Wifi ????"
  //#define CONFIG_MENU_ITEM_4_GCODE "M118 ????"
  //#define CONFIG_MENU_ITEM_4_CONFIRM

  //#define CONFIG_MENU_ITEM_5_DESC "Wifi ????"
  //#define CONFIG_MENU_ITEM_5_GCODE "M118 ????"
  //#define CONFIG_MENU_ITEM_5_CONFIRM
#endif

// @section custom buttons

/**
 * 用户自定义按钮，用于运行自定义 G 代码。
 * 最多可定义 25 个。
 */
//#define CUSTOM_USER_BUTTONS
#if ENABLED(CUSTOM_USER_BUTTONS)
  //#define BUTTON1_PIN -1
  #if PIN_EXISTS(BUTTON1)
    #define BUTTON1_HIT_STATE     LOW       // 被触发按钮的状态。NC=LOW。NO=HIGH。
    #define BUTTON1_WHEN_PRINTING false     // 是否允许在打印过程中触发按钮？
    #define BUTTON1_GCODE         "G28"
    #define BUTTON1_DESC          "Homing"  // 用于设置 LCD 状态的可选字符串
  #endif

  //#define BUTTON2_PIN -1
  #if PIN_EXISTS(BUTTON2)
    #define BUTTON2_HIT_STATE     LOW
    #define BUTTON2_WHEN_PRINTING false
    #define BUTTON2_GCODE         "M140 S" STRINGIFY(PREHEAT_1_TEMP_BED) "\nM104 S" STRINGIFY(PREHEAT_1_TEMP_HOTEND)
    #define BUTTON2_DESC          "Preheat for " PREHEAT_1_LABEL
  #endif

  //#define BUTTON3_PIN -1
  #if PIN_EXISTS(BUTTON3)
    #define BUTTON3_HIT_STATE     LOW
    #define BUTTON3_WHEN_PRINTING false
    #define BUTTON3_GCODE         "M140 S" STRINGIFY(PREHEAT_2_TEMP_BED) "\nM104 S" STRINGIFY(PREHEAT_2_TEMP_HOTEND)
    #define BUTTON3_DESC          "Preheat for " PREHEAT_2_LABEL
  #endif
#endif

// @section host

/**
 * 主机动作命令
 *
 * 按照标准定义主机流式动作命令。
 *
 * 参见 https://reprap.org/wiki/G-code#Action_commands
 * 常用命令 ........ poweroff, pause, paused, resume, resumed, cancel
 * G29_RETRY_AND_RECOVER .. probe_rewipe, probe_failed
 *
 * 某些功能会添加原因码来扩展这些命令。
 *
 * 主机提示支持可让 Marlin 使用主机来提示用户，从而
 * 使耗材断料等流程能够由主机端管理。
 */
//#define HOST_ACTION_COMMANDS
#if ENABLED(HOST_ACTION_COMMANDS)
  //#define HOST_PAUSE_M76                // 收到 M76 时通知主机暂停
  //#define HOST_PROMPT_SUPPORT           // 发起主机提示以获取用户反馈
  #if ENABLED(HOST_PROMPT_SUPPORT)
    //#define HOST_STATUS_NOTIFICATIONS   // 将一些状态消息作为通知发送给主机
  #endif
  //#define HOST_START_MENU_ITEM          // 添加一个菜单项，通知主机启动
  //#define HOST_SHUTDOWN_MENU_ITEM       // 添加一个菜单项，通知主机关机
#endif

// @section extras

/**
 * 取消对象
 *
 * 实现 M486，让 Marlin 可以跳过对象
 */
//#define CANCEL_OBJECTS
#if ENABLED(CANCEL_OBJECTS)
  #define CANCEL_OBJECTS_REPORTING // 以状态消息形式输出当前对象
#endif

/**
 * 用于闭环控制的 I2C 位置编码器。
 * 由 Aus3D 的 Chris Barr 开发。
 *
 * 维基：https://wiki.aus3d.com.au/Magnetic_Encoder
 * Github：https://github.com/Aus3D/MagneticEncoder
 *
 * 供应商：https://aus3d.com.au/magnetic-encoder-module
 * 备选供应商：https://reliabuild3d.com/
 *
 * Reliabuild 编码器经过改装以提高可靠性。
 * @section i2c encoders
 */

//#define I2C_POSITION_ENCODERS
#if ENABLED(I2C_POSITION_ENCODERS)

  #define I2CPE_ENCODER_CNT         1                       // 已安装的编码器数量；当前最多支持 5
                                                            // 个编码器。

  #define I2CPE_ENC_1_ADDR          I2CPE_PRESET_ADDR_X     // 编码器的 I2C 地址。30-200。
  #define I2CPE_ENC_1_AXIS          X_AXIS                  // 编码器模块安装在哪个轴上。  <X|Y|Z|E>_AXIS。
  #define I2CPE_ENC_1_TYPE          I2CPE_ENC_TYPE_LINEAR   // 编码器类型：  I2CPE_ENC_TYPE_LINEAR -或-
                                                            // I2CPE_ENC_TYPE_ROTARY。
  #define I2CPE_ENC_1_TICKS_UNIT    2048                    // 2mm 极距磁条用 1024；
                                                            // 1mm 极距用 2048。直线编码器为脉冲 / mm，
                                                            // 旋转编码器为脉冲 / 转。
  //#define I2CPE_ENC_1_TICKS_REV     (16 * 200)            // 仅旋转编码器需要；步进电机
                                                            // 每转的步数（电机步数/转 * 细分数）
  //#define I2CPE_ENC_1_INVERT                              // 反转轴的运动方向。
  #define I2CPE_ENC_1_EC_METHOD     I2CPE_ECM_MICROSTEP     // 误差校正的类型。
  #define I2CPE_ENC_1_EC_THRESH     0.10                    // 误差阈值 (mm)，超过该值时
                                                            // 打印机将尝试校正；小于该值的
                                                            // 误差会被忽略，以尽量减小
                                                            // 测量噪声/延迟的影响（滤波）。

  #define I2CPE_ENC_2_ADDR          I2CPE_PRESET_ADDR_Y     // 同上，但用于编码器 2。
  #define I2CPE_ENC_2_AXIS          Y_AXIS
  #define I2CPE_ENC_2_TYPE          I2CPE_ENC_TYPE_LINEAR
  #define I2CPE_ENC_2_TICKS_UNIT    2048
  //#define I2CPE_ENC_2_TICKS_REV   (16 * 200)
  //#define I2CPE_ENC_2_INVERT
  #define I2CPE_ENC_2_EC_METHOD     I2CPE_ECM_MICROSTEP
  #define I2CPE_ENC_2_EC_THRESH     0.10

  #define I2CPE_ENC_3_ADDR          I2CPE_PRESET_ADDR_Z     // 编码器 3。  按上面的方式添加额外的配置选项，
  #define I2CPE_ENC_3_AXIS          Z_AXIS                  // 或使用下面的默认值。

  #define I2CPE_ENC_4_ADDR          I2CPE_PRESET_ADDR_E     // 编码器 4。
  #define I2CPE_ENC_4_AXIS          E_AXIS

  #define I2CPE_ENC_5_ADDR          34                      // 编码器 5。
  #define I2CPE_ENC_5_AXIS          E_AXIS

  // 已启用但上面未配置设置的编码器所用的默认值。
  #define I2CPE_DEF_TYPE            I2CPE_ENC_TYPE_LINEAR
  #define I2CPE_DEF_ENC_TICKS_UNIT  2048
  #define I2CPE_DEF_TICKS_REV       (16 * 200)
  #define I2CPE_DEF_EC_METHOD       I2CPE_ECM_NONE
  #define I2CPE_DEF_EC_THRESH       0.1

  //#define I2CPE_ERR_THRESH_ABORT  100.0                   // 误差阈值 (mm)，任一轴上的误差
                                                            // 超过该值时打印机将中止。注释掉此项可
                                                            // 禁用中止行为。

  #define I2CPE_TIME_TRUSTED        10000                   // 编码器发生故障后，必须经过这段时间 (ms)
                                                            // 且期间不再发生故障，才会重新
                                                            // 信任该编码器。

  /**
   * 每次从缓冲区执行新命令时都会检查位置，但在长距离移动过程中，
   * 此设置决定两次检查之间的最短更新时间。取值 100 与误差滚动平均配合良好，
   * 适合只针对失步进行校正而不针对振动的场合。
   */
  #define I2CPE_MIN_UPD_TIME_MS     4                       // (ms) 两次编码器检查之间的最短时间。

  // 使用滚动平均来识别指示失步的持续性错误，以区别于振动和噪声。
  #define I2CPE_ERR_ROLLING_AVERAGE

#endif // I2C_POSITION_ENCODERS

/**d
 * 模拟摇杆
 * @section joystick
 */
//#define JOYSTICK
#if ENABLED(JOYSTICK)
  #define JOY_X_PIN    5  // RAMPS: 建议使用 AUX2 上的 A5 引脚
  #define JOY_Y_PIN   10  // RAMPS: 建议使用 AUX2 上的 A10 引脚
  #define JOY_Z_PIN   12  // RAMPS: 建议使用 AUX2 上的 A12 引脚
  #define JOY_EN_PIN  44  // RAMPS: 建议使用 AUX2 上的 D44 引脚

  //#define INVERT_JOY_X  // 如果 X 方向反向则启用
  //#define INVERT_JOY_Y  // 如果 Y 方向反向则启用
  //#define INVERT_JOY_Z  // 如果 Z 方向反向则启用

  // 连接后配合 JOYSTICK_DEBUG 使用 M119 找到合适的数值：
  #define JOY_X_LIMITS { 5600, 8190-100, 8190+100, 10800 } // 最小值，死区起点，死区终点，最大值
  #define JOY_Y_LIMITS { 5600, 8250-100, 8250+100, 11000 }
  #define JOY_Z_LIMITS { 4800, 8080-100, 8080+100, 11550 }
  //#define JOYSTICK_DEBUG
#endif

/**
 * 机械式龙门校准
 * Průša TMC_Z_CALIBRATION 的现代替代方案。
 * 增加了配合任何可调电流驱动工作的能力。
 * 由于 M915 已废弃，此功能以 G34 实现。
 * @section calibrate
 */
//#define MECHANICAL_GANTRY_CALIBRATION
#if ENABLED(MECHANICAL_GANTRY_CALIBRATION)
  #define GANTRY_CALIBRATION_CURRENT          600     // 默认校准电流 (ma)
  #define GANTRY_CALIBRATION_EXTRA_HEIGHT      15     // 越过 Z_###_POS 后额外移动的距离，单位 mm
  #define GANTRY_CALIBRATION_FEEDRATE         500     // 校正移动的进给速度
  //#define GANTRY_CALIBRATION_TO_MIN                 // 启用以在 MIN 方向校准 Z

  //#define GANTRY_CALIBRATION_SAFE_POSITION XY_CENTER // 喷嘴的安全位置
  //#define GANTRY_CALIBRATION_XY_PARK_FEEDRATE 3000  // XY 停靠进给速度 - MMM
  //#define GANTRY_CALIBRATION_COMMANDS_PRE   ""
  #define GANTRY_CALIBRATION_COMMANDS_POST  "G28"     // 强烈建议使用 G28 以确保位置准确
#endif

/**
 * 即时冻结 / 解冻功能
 * 可用于需要能够恢复的紧急停止场合。
 * @section interface
 */
//#define FREEZE_FEATURE
#if ENABLED(FREEZE_FEATURE)
  //#define FREEZE_PIN 41   // 在此覆盖默认的 (KILL) 引脚
  #define FREEZE_STATE LOW  // 表示冻结状态的引脚状态
#endif

/**
 * MAX7219 调试矩阵
 *
 * 添加对基于 Max7219 芯片的低成本 8x8 LED 矩阵的支持，用作实时状态显示。
 * 需要 3 根信号线。附带一些实用的调试选项以演示其用法。
 * @section debug matrix
 */
//#define MAX7219_DEBUG
#if ENABLED(MAX7219_DEBUG)
  #define MAX7219_CLK_PIN   64
  #define MAX7219_DIN_PIN   57
  #define MAX7219_LOAD_PIN  44

  //#define MAX7219_GCODE          // 添加 M7219 G 代码以控制 LED 矩阵
  #define MAX7219_INIT_TEST    2   // 启动时的测试图案：0=无，1=扫描，2=螺旋
  #define MAX7219_NUMBER_UNITS 1   // 链中 Max7219 单元的数量。
  #define MAX7219_ROTATE       0   // 顺时针旋转显示（以 +/- 90° 为单位）
                                   // 连接器位置：  right=0   bottom=-90  top=90  left=180
  //#define MAX7219_REVERSE_ORDER  // 可以反转 LED 矩阵单元的顺序
  //#define MAX7219_REVERSE_EACH   // 可以反转每个矩阵单元行内的 LED 顺序
  //#define MAX7219_SIDE_BY_SIDE   // 大尺寸芯片+矩阵板可以并排级联

  /**
   * 调试功能示例
   * 如果添加更多调试显示，请注意避免冲突！
   */
  #define MAX7219_DEBUG_PRINTER_ALIVE     // 闪烁 8x8 矩阵角落的 LED，表示固件正在运行
  #define MAX7219_DEBUG_PLANNER_HEAD  2   // 在此 LED 矩阵行及下一行显示规划器队首位置
  #define MAX7219_DEBUG_PLANNER_TAIL  4   // 在此 LED 矩阵行及下一行显示规划器队尾位置

  #define MAX7219_DEBUG_PLANNER_QUEUE 0   // 在此 LED 矩阵行及下一行显示当前规划器队列深度
                                          // 如果出现卡顿、重启等现象，此选项可以揭示
                                          // 对配置所做的调整如何实时影响打印机。
  #define MAX7219_DEBUG_PROFILE       6   // 在此 LED 矩阵行上显示被分析代码所占的 CPU 时间比例
                                          // 默认分析 idle()，因此这显示处理器的空闲程度。
                                          // 参见 CodeProfiler 类。
  //#define MAX7219_DEBUG_MULTISTEPPING 6 // 在此 LED 矩阵行上显示 1 到 128 的多步进。
#endif

/**
 * NanoDLP 同步支持
 *
 * 配合 NanoDLP 使用时支持同步的 Z 轴移动。G0/G1 轴移动将
 * 输出 "Z_move_comp" 字符串，以实现与 DLP 投影曝光的同步。
 * 此功能允许你使用 [[WaitForDoneMessage]] 代替 M400 命令。
 * @section nanodlp
 */
//#define NANODLP_Z_SYNC
#if ENABLED(NANODLP_Z_SYNC)
  //#define NANODLP_ALL_AXIS  // 对任何轴的移动（不只是 Z）都发送 "Z_move_comp" 报告。
#endif

/**
 * 以太网。使用 M552 启用并设置 IP 地址。
 * @section network
 */
#if HAS_ETHERNET
  #define MAC_ADDRESS { 0xDE, 0xAD, 0xBE, 0xEF, 0xF0, 0x0D }  // 你的网络内唯一的 MAC 地址
#endif

/**
 * WiFi 支持 (Espressif ESP32 WiFi)
 */
//#define WIFISUPPORT         // Marlin 内置 WiFi 管理
//#define ESP3D_WIFISUPPORT   // ESP3D 库 WiFi 管理 (https://github.com/luc-github/ESP3DLib)

#if EITHER(WIFISUPPORT, ESP3D_WIFISUPPORT)
  //#define WEBSUPPORT          // 启动 web 服务器（可能包含自动发现）
  //#define OTASUPPORT          // 支持空中固件更新
  //#define WIFI_CUSTOM_COMMAND // 接受来自主机的功能配置命令（例如 WiFi ESP3D）

  /**
   * 若要设置默认的 WiFi SSID / 密码，请创建一个名为 Configuration_Secure.h 的文件，
   * 其中包含按你的网络定制的以下宏定义。该特定文件已通过
   * .gitignore 排除，以防意外泄露到公开仓库。
   *
   *   #define WIFI_SSID "WiFi SSID"
   *   #define WIFI_PWD  "WiFi Password"
   */
  //#include "Configuration_Secure.h" // 包含 WiFi SSID / 密码的外部文件
#endif

// @section multi-material

/**
 * Průša 多材料单元 (MMU)
 * 在 Configuration.h 中启用
 *
 * 这些设备让板上的单个步进电机驱动可以驱动
 * 任意数量的步进电机所组成的多材料送料器。
 */
#if HAS_PRUSA_MMU1
  /**
   * 此选项仅允许多路复用器在换刀时切换。
   * 配置自定义 E 轴移动的更多选项尚待提供。
   *
   * 如有需要，在此覆盖默认的 DIO 选择引脚。
   * 某些引脚文件可能为这些引脚提供默认值。
   */
  //#define E_MUX0_PIN 40  // 始终需要
  //#define E_MUX1_PIN 42  // 3 到 8 路输入时需要
  //#define E_MUX2_PIN 44  // 5 到 8 路输入时需要
#elif HAS_PRUSA_MMU2
  // 用于与 MMU2 通信的串口。
  #define MMU2_SERIAL_PORT 2

  // 如果为 MMU 定义了引脚，则使用硬件复位
  //#define MMU2_RST_PIN 23

  // 如果 MMU2 使用 12V 步进电机则启用 (MMU2 固件 1.0.2 及以上)
  //#define MMU2_MODE_12V

  // MMU2 F.I.N.D.A. 探针检测到耗材断料时执行的 G 代码
  #define MMU2_FILAMENT_RUNOUT_SCRIPT "M600"

  // 为 MMU2 添加 LCD 菜单
  //#define MMU2_MENUS

  // LCD 菜单中耗材加载/卸载的设置。
  // 这适用于 Průša MK3 风格的挤出机。请按你的硬件进行定制。
  #define MMU2_FILAMENTCHANGE_EJECT_FEED 80.0
  #define MMU2_LOAD_TO_NOZZLE_SEQUENCE \
    {  7.2, 1145 }, \
    { 14.4,  871 }, \
    { 36.0, 1393 }, \
    { 14.4,  871 }, \
    { 50.0,  198 }

  #define MMU2_RAMMING_SEQUENCE \
    {   1.0, 1000 }, \
    {   1.0, 1500 }, \
    {   2.0, 2000 }, \
    {   1.5, 3000 }, \
    {   2.5, 4000 }, \
    { -15.0, 5000 }, \
    { -14.0, 1200 }, \
    {  -6.0,  600 }, \
    {  10.0,  700 }, \
    { -10.0,  400 }, \
    { -50.0, 2000 }

  /**
   * 使用 MMU2S 之类的传感器
   * 此模式需要带有挤出机惰轮传感器的 MK3S 挤出机，类似 MMU2S。
   * 参见 https://help.prusa3d.com/en/guide/3b-mk3s-mk2-5s-extruder-upgrade_41560，步骤 11
   */
  #if HAS_PRUSA_MMU2S
    #define MMU2_C0_RETRY   5             // 重试次数（总时间 = 超时 * 重试次数）

    #define MMU2_CAN_LOAD_FEEDRATE 800    // (mm/min)
    #define MMU2_CAN_LOAD_SEQUENCE \
      {  0.1, MMU2_CAN_LOAD_FEEDRATE }, \
      {  60.0, MMU2_CAN_LOAD_FEEDRATE }, \
      { -52.0, MMU2_CAN_LOAD_FEEDRATE }

    #define MMU2_CAN_LOAD_RETRACT   6.0   // (mm) 应小于加载序列数值之间的距离
    #define MMU2_CAN_LOAD_DEVIATION 0.8   // (mm) 可接受的偏差

    #define MMU2_CAN_LOAD_INCREMENT 0.2   // (mm) 在 MMU2 模块内可复用的量
    #define MMU2_CAN_LOAD_INCREMENT_SEQUENCE \
      { -MMU2_CAN_LOAD_INCREMENT, MMU2_CAN_LOAD_FEEDRATE }

    // 如果在初始卸载移动之后传感器仍检测到耗材，则继续卸载
    //#define MMU_IR_UNLOAD_MOVE
  #else

    /**
     * MMU1 挤出机传感器
     *
     * 支持使用 Průša（或其他）红外传感器来检测挤出机附近的耗材，
     * 从而让加载更可靠。适用于装备有耗材传感器的挤出机，
     * 传感器距齿轮小于 38mm。
     *
     * 加载过程中，传感器触发时挤出机将停止，然后再做最后一次
     * 移动至齿轮处。若未检测到耗材，MMU2 可以再尝试几次。
     * 若所有尝试均失败，则会触发耗材断料。
     */
    //#define MMU_EXTRUDER_SENSOR
    #if ENABLED(MMU_EXTRUDER_SENSOR)
      #define MMU_LOADING_ATTEMPTS_NR 5 // 首次加载失败时加载耗材的最大尝试次数
    #endif

  #endif

  //#define MMU2_DEBUG  // 将调试信息写入串口输出

#endif // HAS_PRUSA_MMU2

/**
 * 高级打印计数器设置
 * @section stats
 */
#if ENABLED(PRINTCOUNTER)
  #define SERVICE_WARNING_BUZZES  3
  // 启用最多 3 个保养周期看门狗
  //#define SERVICE_NAME_1      "Service S"
  //#define SERVICE_INTERVAL_1  100 // 打印小时数
  //#define SERVICE_NAME_2      "Service L"
  //#define SERVICE_INTERVAL_2  200 // 打印小时数
  //#define SERVICE_NAME_3      "Service 3"
  //#define SERVICE_INTERVAL_3    1 // 打印小时数
#endif

// @section develop

//
// M100 空闲内存监视器，用于调试内存使用
//
//#define M100_FREE_MEMORY_WATCHER

//
// M42 - 设置引脚状态
//
#define DIRECT_PIN_CONTROL

//
// M43 - 显示引脚状态、切换引脚、监视引脚、监视限位开关并切换 LED、测试舵机探针
//
#define PINS_DEBUGGING

// 启用启动时运行并生成报告的测试
//#define MARLIN_TEST_BUILD

// 启用 Marlin 开发模式，添加一些特殊命令
//#define MARLIN_DEV_MODE

#if ENABLED(MARLIN_DEV_MODE)
  /**
   * D576 - 缓冲区监控
   * 用于帮助诊断由命令缓冲区为空引起的打印质量问题。
   */
  //#define BUFFER_MONITORING
#endif

/**
 * 事后调试可捕获异常行为，并将 CPU 状态和回溯输出到串口。
 * 在调试器中运行时它会中断以供调试。这有助于理解
 * 远程位置发生的崩溃。需要约 400 字节 SRAM 和 5Kb 闪存。
 */
//#define POSTMORTEM_DEBUGGING

/**
 * 软件复位选项
 */
//#define SOFT_RESET_VIA_SERIAL         // 'KILL' 和 '^X' 命令将软件复位控制器
//#define SOFT_RESET_ON_KILL            // 在 KILL 之后使用数字按钮软件复位控制器

// 从寄存器 r2 而非 MCUSR 读取未清除的复位原因。AVR 上的 Optiboot 支持此功能。
//#define OPTIBOOT_RESET_REASON
