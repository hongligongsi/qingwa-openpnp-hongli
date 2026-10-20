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
 * 仅在完全清楚自己在做什么时才修改这些选项。
 * 部分设置若配置不当可能损坏打印机！
 *
 * 基础设置见 Configuration.h
 */
#define CONFIGURATION_ADV_H_VERSION 02010300

// @section develop

/**
 * 配置导出
 *
 * 在编译过程中导出配置。（参见 signature.py）
 * 输出文件随编译产物一起保存（例如 .pio/build/mega2560）。
 *
 * 将配置归档为 config.ini 的示例见 `build_all_examples --ini`。
 *
 *  1 = marlin_config.json - 包含配置的字典。
 *      该文件也会为 CONFIGURATION_EMBEDDING 生成。
 *  2 = config.ini - PlatformIO 预处理使用的文件格式。
 *  3 = schema.json - 完整的配置架构。（13 = 分组模式）
 *  4 = schema.yml - 完整的配置架构。
 */
//#define CONFIG_EXPORT 2 // :[1:'JSON', 2:'config.ini', 3:'schema.json', 4:'schema.yml']

//===========================================================================
//============================= Thermal Settings ============================
//===========================================================================
// @section temperature

/**
 * 热电偶传感器对噪声相当敏感。任何感应到
 * 传感器导线上的噪声，例如与它们平行走线的
 * 步进电机导线引入的噪声，都可能导致热电偶传感器报告虚假错误。
 * 该值是在报告错误之前允许连续出现的错误次数。
 * 这样可以忽略间歇性的错误状况，同时仍能检测到真正的故障——
 * 真正的故障应表现为传感器持续不断地报告
 * 错误流。
 *
 * 将此值设为 0 可在出现第一个错误时立即判定失败。
 */
#define THERMOCOUPLE_MAX_ERRORS 15

//
// 自定义热敏电阻 1000 参数
//
#if TEMP_SENSOR_0 == 1000
  #define HOTEND0_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define HOTEND0_RESISTANCE_25C_OHMS   100000 // 25°C 时的电阻
  #define HOTEND0_BETA                    3950 // Beta 值
  #define HOTEND0_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_1 == 1000
  #define HOTEND1_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define HOTEND1_RESISTANCE_25C_OHMS   100000 // 25°C 时的电阻
  #define HOTEND1_BETA                    3950 // Beta 值
  #define HOTEND1_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_2 == 1000
  #define HOTEND2_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define HOTEND2_RESISTANCE_25C_OHMS   100000 // 25°C 时的电阻
  #define HOTEND2_BETA                    3950 // Beta 值
  #define HOTEND2_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_3 == 1000
  #define HOTEND3_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define HOTEND3_RESISTANCE_25C_OHMS   100000 // 25°C 时的电阻
  #define HOTEND3_BETA                    3950 // Beta 值
  #define HOTEND3_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_4 == 1000
  #define HOTEND4_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define HOTEND4_RESISTANCE_25C_OHMS   100000 // 25°C 时的电阻
  #define HOTEND4_BETA                    3950 // Beta 值
  #define HOTEND4_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_5 == 1000
  #define HOTEND5_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define HOTEND5_RESISTANCE_25C_OHMS   100000 // 25°C 时的电阻
  #define HOTEND5_BETA                    3950 // Beta 值
  #define HOTEND5_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_6 == 1000
  #define HOTEND6_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define HOTEND6_RESISTANCE_25C_OHMS   100000 // 25°C 时的电阻
  #define HOTEND6_BETA                    3950 // Beta 值
  #define HOTEND6_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_7 == 1000
  #define HOTEND7_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define HOTEND7_RESISTANCE_25C_OHMS   100000 // 25°C 时的电阻
  #define HOTEND7_BETA                    3950 // Beta 值
  #define HOTEND7_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_BED == 1000
  #define BED_PULLUP_RESISTOR_OHMS        4700 // 上拉电阻
  #define BED_RESISTANCE_25C_OHMS       100000 // 25°C 时的电阻
  #define BED_BETA                        3950 // Beta 值
  #define BED_SH_C_COEFF                     0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_CHAMBER == 1000
  #define CHAMBER_PULLUP_RESISTOR_OHMS    4700 // 上拉电阻
  #define CHAMBER_RESISTANCE_25C_OHMS   100000 // 25°C 时的电阻
  #define CHAMBER_BETA                    3950 // Beta 值
  #define CHAMBER_SH_C_COEFF                 0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_COOLER == 1000
  #define COOLER_PULLUP_RESISTOR_OHMS     4700 // 上拉电阻
  #define COOLER_RESISTANCE_25C_OHMS    100000 // 25°C 时的电阻
  #define COOLER_BETA                     3950 // Beta 值
  #define COOLER_SH_C_COEFF                  0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_PROBE == 1000
  #define PROBE_PULLUP_RESISTOR_OHMS      4700 // 上拉电阻
  #define PROBE_RESISTANCE_25C_OHMS     100000 // 25°C 时的电阻
  #define PROBE_BETA                      3950 // Beta 值
  #define PROBE_SH_C_COEFF                   0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_BOARD == 1000
  #define BOARD_PULLUP_RESISTOR_OHMS      4700 // 上拉电阻
  #define BOARD_RESISTANCE_25C_OHMS     100000 // 25°C 时的电阻
  #define BOARD_BETA                      3950 // Beta 值
  #define BOARD_SH_C_COEFF                   0 // Steinhart-Hart C 系数
#endif

#if TEMP_SENSOR_REDUNDANT == 1000
  #define REDUNDANT_PULLUP_RESISTOR_OHMS  4700 // 上拉电阻
  #define REDUNDANT_RESISTANCE_25C_OHMS 100000 // 25°C 时的电阻
  #define REDUNDANT_BETA                  3950 // Beta 值
  #define REDUNDANT_SH_C_COEFF               0 // Steinhart-Hart C 系数
#endif

/**
 * 热电偶选项 — 适用于 MAX6675 (-2)、MAX31855 (-3) 和 MAX31865 (-5)。
 */
//#define TEMP_SENSOR_FORCE_HW_SPI                // 忽略 SCK/MOSI/MISO 引脚；使用 CS 和默认 SPI 总线。
//#define MAX31865_SENSOR_WIRES_0 2               // (2-4) 连接到 MAX31865 板的探头线数。
//#define MAX31865_SENSOR_WIRES_1 2
//#define MAX31865_SENSOR_WIRES_2 2

//#define MAX31865_50HZ_FILTER                    // 使用 50Hz 滤波器代替默认的 60Hz。
//#define MAX31865_USE_READ_ERROR_DETECTION       // 将数值尖峰（1 秒内变化 20°C）视为读取错误。

//#define MAX31865_USE_AUTO_MODE                  // 比 1-shot 模式读取更快更频繁；偏置电压常开；对 RTD 温度有轻微影响。
//#define MAX31865_MIN_SAMPLING_TIME_MSEC     100 // (ms) 1-shot 模式：最小读取间隔。让传感器在更长的间隔内断电，以减小偏置电压的影响。
//#define MAX31865_IGNORE_INITIAL_FAULTY_READS 10 // 忽略部分读取故障（保留温度读数），以规避一个潜在问题（#23439）。

//#define MAX31865_WIRE_OHMS_0              0.95f // 两线制时设置导线电阻以获得更精确的读数。
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
// 热床 Bang-Bang 控制选项
//
#if DISABLED(PIDTEMPBED)
  #define BED_CHECK_INTERVAL 5000   // (ms) bang-bang 控制下两次检查之间的间隔
  #if ENABLED(BED_LIMIT_SWITCHING)
    #define BED_HYSTERESIS 2        // (°C) 仅当 ABS(T-target) > BED_HYSTERESIS 时才设置相应的加热器状态
  #endif
#endif

//
// 加热腔选项
//
#if DISABLED(PIDTEMPCHAMBER)
  #define CHAMBER_CHECK_INTERVAL 5000   // (ms) bang-bang 控制下两次检查之间的间隔
  #if ENABLED(CHAMBER_LIMIT_SWITCHING)
    #define CHAMBER_HYSTERESIS 2        // (°C) 仅当 ABS(T-target) > CHAMBER_HYSTERESIS 时才设置相应的加热器状态
  #endif
#endif

#if TEMP_SENSOR_CHAMBER
  //#define HEATER_CHAMBER_PIN      P2_04   // 加热器开关引脚（必需）（示例：SKR 1.4 Turbo 的 HE1 插座）
  //#define HEATER_CHAMBER_INVERTING false
  //#define FAN1_PIN                   -1   // 移除 P2_04 引脚上的风扇信号（示例：SKR 1.4 Turbo 的 HE1 插座）

  //#define CHAMBER_FAN               // 启用腔体风扇
  #if ENABLED(CHAMBER_FAN)
    //#define CHAMBER_FAN_INDEX   2   // 用作腔体风扇的风扇编号。（默认：第一个未使用的风扇）
    #define CHAMBER_FAN_MODE      2   // 风扇控制模式：0=恒速；1=温度高于目标时线性增加；2=V 形曲线；3=与 1 类似但风扇常开。
    #if CHAMBER_FAN_MODE == 0
      #define CHAMBER_FAN_BASE  255   // 腔体风扇 PWM (0-255)
    #elif CHAMBER_FAN_MODE == 1
      #define CHAMBER_FAN_BASE  128   // 腔体风扇基础 PWM (0-255)；腔体温度高于目标时开启
      #define CHAMBER_FAN_FACTOR 25   // 高于目标每 1°C 增加的 PWM
    #elif CHAMBER_FAN_MODE == 2
      #define CHAMBER_FAN_BASE  128   // 腔体风扇最小 PWM (0-255)
      #define CHAMBER_FAN_FACTOR 25   // 与目标每相差 1°C 增加的 PWM
    #elif CHAMBER_FAN_MODE == 3
      #define CHAMBER_FAN_BASE  128   // 腔体风扇基础 PWM (0-255)
      #define CHAMBER_FAN_FACTOR 25   // 高于目标每 1°C 增加的 PWM
    #endif
  #endif

  //#define CHAMBER_VENT              // 启用腔体上的舵机控制通风口
  #if ENABLED(CHAMBER_VENT)
    #define CHAMBER_VENT_SERVO_NR  1  // 通风口舵机编号
    #define HIGH_EXCESS_HEAT_LIMIT 5  // 温度高于目标多少度时认为腔内存在多余热量
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
  #define TEMP_COOLER_HYSTERESIS   1  // (°C) 视为与目标"足够接近"的温度容差
  #define COOLER_PIN               8  // 激光冷却器开关引脚，用于控制冷却元件供电（例如 TEC、经继电器的外置冷水机）
  #define COOLER_INVERTING     false
  #define TEMP_COOLER_PIN         15  // 激光/冷却器温度传感器引脚。必须为 ADC 引脚。
  #define COOLER_FAN                  // 启用冷却器风扇，风扇编号 0,1,2,3 等。
  #define COOLER_FAN_INDEX         0  // 风扇编号 0, 1, 2 等。例如：
  #if ENABLED(COOLER_FAN)
    #define COOLER_FAN_BASE      100  // 冷却器风扇基础 PWM (0-255)；冷却器温度高于目标时开启
    #define COOLER_FAN_FACTOR     25  // 高于目标每 1°C 增加的 PWM
  #endif
#endif

//
// 主板传感器选项
//
#if TEMP_SENSOR_BOARD
  #define THERMAL_PROTECTION_BOARD   // 若主板传感器超出下方温度范围则停机。
  #define BOARD_MINTEMP           8  // (°C)
  #define BOARD_MAXTEMP          70  // (°C)
  #ifndef TEMP_BOARD_PIN
    //#define TEMP_BOARD_PIN -1      // 主板温度传感器引脚（若未在引脚文件中设置）。
  #endif
#endif

/**
 * 热保护为打印机提供额外的防护，避免损坏
 * 和火灾。Marlin 始终包含安全的最小和最大温度范围，
 * 以防热敏电阻导线断裂或脱落。
 *
 * 问题所在：如果热敏电阻脱落，它将报告远低于实际
 * 的室温，固件会继续
 * 保持加热器开启。
 *
 * 解决方案：一旦温度达到目标，就开始监视。
 * 如果温度在过长时间（周期）内持续低于目标过远（滞后），
 * 固件将出于安全考虑停止机器。
 *
 * 如果"热失控"出现误报，请增大
 * THERMAL_PROTECTION_HYSTERESIS 和/或 THERMAL_PROTECTION_PERIOD
 */
#if ENABLED(THERMAL_PROTECTION_HOTENDS)
  #define THERMAL_PROTECTION_PERIOD 40        // 秒
  #define THERMAL_PROTECTION_HYSTERESIS 4     // 摄氏度

  //#define ADAPTIVE_FAN_SLOWING              // 若温度下降则降低散热风扇转速
  #if ENABLED(ADAPTIVE_FAN_SLOWING)
    //#define REPORT_ADAPTIVE_FAN_SLOWING     // 将风扇减速情况报告到控制台
    #if EITHER(MPCTEMP, PIDTEMP)
      //#define TEMP_TUNING_MAINTAIN_FAN      // 在 M303 或 M306 T 期间不降低风扇转速
    #endif
  #endif

  /**
   * 每当 M104、M109 或 M303 提高目标温度时，
   * 固件会等待 WATCH_TEMP_PERIOD 到期。如果温度
   * 没有升高 WATCH_TEMP_INCREASE 度，机器将停机并
   * 需要硬复位才能恢复。该测试会随任何 M104/M109/M303 重新开始，但仅
   * 当当前温度比目标低得足够多、
   * 测试可靠时才执行。
   *
   * 如果"加热失败"出现误报，请增大 WATCH_TEMP_PERIOD
   * 和/或减小 WATCH_TEMP_INCREASE。WATCH_TEMP_INCREASE 不应
   * 设为低于 2。
   */
  #define WATCH_TEMP_PERIOD  40               // 秒
  #define WATCH_TEMP_INCREASE 2               // 摄氏度
#endif

/**
 * 热床的热保护参数与上文热端的设置相同。
 */
#if ENABLED(THERMAL_PROTECTION_BED)
  #define THERMAL_PROTECTION_BED_PERIOD        20 // 秒
  #define THERMAL_PROTECTION_BED_HYSTERESIS     2 // 摄氏度

  /**
   * 如上文所述，但针对热床（M140/M190/M303）。
   */
  #define WATCH_BED_TEMP_PERIOD                60 // 秒
  #define WATCH_BED_TEMP_INCREASE               2 // 摄氏度
#endif

/**
 * 加热腔的热保护参数。
 */
#if ENABLED(THERMAL_PROTECTION_CHAMBER)
  #define THERMAL_PROTECTION_CHAMBER_PERIOD    20 // 秒
  #define THERMAL_PROTECTION_CHAMBER_HYSTERESIS 2 // 摄氏度

  /**
   * 加热腔监视设置（M141/M191）。
   */
  #define WATCH_CHAMBER_TEMP_PERIOD            60 // 秒
  #define WATCH_CHAMBER_TEMP_INCREASE           2 // 摄氏度
#endif

/**
 * 激光冷却器的热保护参数。
 */
#if ENABLED(THERMAL_PROTECTION_COOLER)
  #define THERMAL_PROTECTION_COOLER_PERIOD     10 // 秒
  #define THERMAL_PROTECTION_COOLER_HYSTERESIS  3 // 摄氏度

  /**
   * 激光冷却监视设置（M143/M193）。
   */
  #define WATCH_COOLER_TEMP_PERIOD             60 // 秒
  #define WATCH_COOLER_TEMP_INCREASE            3 // 摄氏度
#endif

#if ANY(THERMAL_PROTECTION_HOTENDS, THERMAL_PROTECTION_BED, THERMAL_PROTECTION_CHAMBER, THERMAL_PROTECTION_COOLER)
  /**
   * 热保护波动监视器 - 实验性
   * 在温度传感器卡死时停止机器。
   *
   * 此功能可能导致某些热稳定系统停机。请务必在
   * 多种条件下充分测试。若出现误报请禁用。
   *
   * 此功能确保温度传感器定期更新。如果传感器失效或"卡住"，
   * 或 Marlin 停止读取它们，温度将保持恒定，而加热器可能仍在通电！
   * 此功能只监测温度变化，因此无论是硬件还是软件问题都能发现。
   *
   * 默认使用 THERMAL_PROTECTION_*_PERIOD 常量（见上文）作为时间窗口，在窗口内
   * 必须至少发生一次温度变化，以表明传感器轮询正常。若任何受监测
   * 加热器的温度在此期间完全恒定（连微小变化都没有），
   * 则发生热故障错误并停机。
   *
   * 非常稳定的加热器可能产生误报并导致停机。此时可尝试稍微增大
   * 相应的 THERMAL_PROTECTION_*_PERIOD 常量。请注意，不受控的
   * 加热不应持续超过一两分钟。
   *
   * 禁用此功能前，请仔细区分误报与真实的传感器问题。如果重启后
   * 加热器温度看起来比预期略高，则可能是真实的
   * 热故障。可在主机上查看温度曲线是否有异常凸起。
   */
  //#define THERMAL_PROTECTION_VARIANCE_MONITOR
  #if ENABLED(THERMAL_PROTECTION_VARIANCE_MONITOR)
    // 用于覆盖上文 THERMAL_PROTECTION...PERIOD 设置的波动检测窗口。
    // 请注意，有些加热器升温比其他的快。
    //#define THERMAL_PROTECTION_VARIANCE_MONITOR_PERIOD 30  // (s) 覆盖所有监视周期
  #endif
#endif

#if ENABLED(PIDTEMP)
  // 向加热器功率增加一个与挤出速度成正比的附加项。
  // 选择合适的 Kc 值应恰好提供熔化增量材料所需的功率。
  //#define PID_EXTRUSION_SCALING
  #if ENABLED(PID_EXTRUSION_SCALING)
    #define DEFAULT_Kc (100) // 加热功率 = Kc * e_speed
    #define LPQ_MAX_LEN 50
  #endif

  /**
   * 向加热器功率增加一个与风扇转速成正比的附加项。
   * 选择合适的 Kf 值应恰好补偿冷却风扇造成的功率损失。
   * 既可以通过 DEFAULT_Kf 值直接添加一个恒定补偿，
   * 也可以按照下述方法获得随转速变化的补偿。
   *
   * 恒定补偿（仅适用于 0% 和 100% 的风扇转速）
   * ---------------------------------------------------------------------
   * Kf 值的良好起点可由以下公式计算：
   *   kf = (power_fan * eff_fan) / power_heater * 255
   * 其中 eff_fan 在 0.0 到 1.0 之间，取决于风扇效率以及流向喷嘴/加热器的气流。
   *
   * 示例：
   *   加热器：40W，风扇：0.1A * 24V = 2.4W，eff_fan = 0.8
   *   Kf = (2.4W * 0.8) / 40W * 255 = 12.24
   *
   * 随风扇转速变化的补偿
   * --------------------------------
   * 1. 要找到合适的 Kf 值，先设置热端温度，等待稳定，然后开启风扇（100%）。
   *    确认 PID_FAN_SCALING_LIN_FACTOR 为 0 且未启用 PID_FAN_SCALING_ALTERNATIVE_DEFINITION。
   *    如果看到温度下降，重复测试并缓慢增大 Kf 值，直到温度
   *    不再下降。如果开启风扇后温度过冲，说明 Kf 值过大。
   * 2. 记录风扇转速 100% 时的 Kf 值
   * 3. 为 PID_FAN_SCALING_MIN_SPEED 确定一个合适的值，大约在风扇开始转动的转速附近。
   * 4. 针对该风扇转速重复步骤 1 和 2。
   * 5. 启用 PID_FAN_SCALING_ALTERNATIVE_DEFINITION，并将两个 Kf 值分别填入
   *    PID_FAN_SCALING_AT_FULL_SPEED 和 PID_FAN_SCALING_AT_MIN_SPEED。将最小转速填入 PID_FAN_SCALING_MIN_SPEED
   */
  //#define PID_FAN_SCALING
  #if ENABLED(PID_FAN_SCALING)
    //#define PID_FAN_SCALING_ALTERNATIVE_DEFINITION
    #if ENABLED(PID_FAN_SCALING_ALTERNATIVE_DEFINITION)
      // 替代定义用于简化配置。
      // 只需测出全速（255）时的 Kf 和 PID_FAN_SCALING_MIN_SPEED。
      // DEFAULT_Kf 和 PID_FAN_SCALING_LIN_FACTOR 会据此计算得出。

      #define PID_FAN_SCALING_AT_FULL_SPEED 13.0        //=PID_FAN_SCALING_LIN_FACTOR*255+DEFAULT_Kf
      #define PID_FAN_SCALING_AT_MIN_SPEED   6.0        //=PID_FAN_SCALING_LIN_FACTOR*PID_FAN_SCALING_MIN_SPEED+DEFAULT_Kf
      #define PID_FAN_SCALING_MIN_SPEED     10.0        // 启用 PID_FAN_SCALING 的最小风扇转速

      #define DEFAULT_Kf (255.0*PID_FAN_SCALING_AT_MIN_SPEED-PID_FAN_SCALING_AT_FULL_SPEED*PID_FAN_SCALING_MIN_SPEED)/(255.0-PID_FAN_SCALING_MIN_SPEED)
      #define PID_FAN_SCALING_LIN_FACTOR (PID_FAN_SCALING_AT_FULL_SPEED-DEFAULT_Kf)/255.0

    #else
      #define PID_FAN_SCALING_LIN_FACTOR (0)             // 冷却造成的功率损失 = Kf * (fan_speed)
      #define DEFAULT_Kf 10                              // 添加到 PID 调参器的常量
      #define PID_FAN_SCALING_MIN_SPEED 10               // 启用 PID_FAN_SCALING 的最小风扇转速
    #endif
  #endif
#endif

/**
 * 自动温度模式
 *
 * 根据已规划的 E 轴移动动态调整热端目标温度。
 *
 * （与 PID_EXTRUSION_SCALING 对比：后者跟踪 E 轴运动并用附加的
 *  Kc 值调整 PID 行为。）
 *
 * Autotemp 按 (mintemp + factor * mm_per_sec) 计算，上限为 maxtemp。
 *
 * 使用 M104/M109 F<factor> S<mintemp> B<maxtemp> 启用自动温度模式。
 * 发送不带 F 参数的 M104/M109（或在 AUTOTEMP_PROPORTIONAL 下发送 F0）即可禁用。
 */
#define AUTOTEMP
#if ENABLED(AUTOTEMP)
  #define AUTOTEMP_OLDWEIGHT    0.98  // 用于加权历史读数的因子 (0.0 < 值 < 1.0)
  #define AUTOTEMP_MIN          210
  #define AUTOTEMP_MAX          250
  #define AUTOTEMP_FACTOR       0.1f
  // 按此处设置的比例，在 M104/M109 时默认开启 AUTOTEMP
  //#define AUTOTEMP_PROPORTIONAL
  #if ENABLED(AUTOTEMP_PROPORTIONAL)
    #define AUTOTEMP_MIN_P      0 // (°C) 加到目标温度上
    #define AUTOTEMP_MAX_P      5 // (°C) 加到目标温度上
    #define AUTOTEMP_FACTOR_P   1 // 默认应用此 F 参数（可被 M104/M109 F 覆盖）
  #endif
#endif

// 显示温度 ADC 值
// 启用后 M105 会包含从温度传感器读取的 ADC 值。
//#define SHOW_TEMP_ADC_VALUES

/**
 * 高温热敏电阻支持
 *
 * 支持高温的热敏电阻往往难以在室温和更低温度下获得
 * 良好读数。这意味着 TEMP_SENSOR_X_RAW_LO_TEMP
 * 可能会在预热过程中加热元件首次开启时被触发，
 * 从而出于安全考虑触发 MINTEMP 错误
 * 并强制停止一切。
 * 为规避这一限制，我们允许一段预热时间（期间
 * 不触发 MINTEMP 错误），并增加一个 min_temp 缓冲
 * 来处理异常读数。
 *
 * 如果要为热端热敏电阻启用此功能，
 * 请取消注释并将下方常量设为大于 0 的值
 */

// 允许连续出现的低温错误次数，
// 超过此数才触发 MINTEMP 错误。（不应大于 10。）
//#define MAX_CONSECUTIVE_LOW_TEMPERATURE_ERROR_ALLOWED 0

/**
 * 热端开始检查温度前的预热毫秒数。
 * 此值不应设为热端达到目标温度所需的时间，
 * 而是达到热敏电阻可读取的最低温度所需的时间。
 * 越短越好/越安全。
 * 通常不应超过 30 秒（30000）
 */
//#define PREHEAT_TIME_HOTEND_MS 0
//#define PREHEAT_TIME_BED_MS 0

// @section extruder

/**
 * 挤出机空闲防堵。
 * 若机器空闲且温度高于 MINTEMP，
 * 则每隔几秒挤出一点耗材。
 */
//#define EXTRUDER_RUNOUT_PREVENT
#if ENABLED(EXTRUDER_RUNOUT_PREVENT)
  #define EXTRUDER_RUNOUT_MINTEMP 190
  #define EXTRUDER_RUNOUT_SECONDS 30
  #define EXTRUDER_RUNOUT_SPEED 1500  // (mm/min)
  #define EXTRUDER_RUNOUT_EXTRUDE 5   // (mm)
#endif

/**
 * 热端空闲超时
 * 防止喷嘴中的耗材碳化并造成严重堵塞。
 */
//#define HOTEND_IDLE_TIMEOUT
#if ENABLED(HOTEND_IDLE_TIMEOUT)
  #define HOTEND_IDLE_TIMEOUT_SEC (5*60)    // (seconds) 触发保护前允许挤出机无移动的时间
  #define HOTEND_IDLE_MIN_TRIGGER   180     // (°C) 启用热端保护的最低温度
  #define HOTEND_IDLE_NOZZLE_TARGET   0     // (°C) 超时后喷嘴的安全温度
  #define HOTEND_IDLE_BED_TARGET      0     // (°C) 超时后热床的安全温度
#endif

// @section temperature

// AD595 / AD8495 传感器的校准，用于调整温度测量。
// 最终温度按 (measuredTemp * GAIN) + OFFSET 计算。
#define TEMP_SENSOR_AD595_OFFSET  0.0
#define TEMP_SENSOR_AD595_GAIN    1.0
#define TEMP_SENSOR_AD8495_OFFSET 0.0
#define TEMP_SENSOR_AD8495_GAIN   1.0

/**
 * 控制器风扇
 * 用于冷却步进电机驱动和 MOSFET。
 *
 * 只要任何驱动器被启用，风扇就会自动开启，并在驱动器
 * 关闭后不久关闭（或降到怠速转速）。
 */
//#define USE_CONTROLLER_FAN
#if ENABLED(USE_CONTROLLER_FAN)
  //#define CONTROLLER_FAN_PIN -1           // 为控制器风扇设置自定义引脚
  //#define CONTROLLER_FAN2_PIN -1          // 为第二个控制器风扇设置自定义引脚
  //#define CONTROLLER_FAN_USE_Z_ONLY       // 启用此项后仅考虑 Z 轴
  //#define CONTROLLER_FAN_IGNORE_Z         // 忽略 Z 步进电机。在禁用步进电机超时功能时有用。
  #define CONTROLLERFAN_SPEED_MIN         0 // (0-255) 最小转速。（低于此值时风扇关闭。）
  #define CONTROLLERFAN_SPEED_ACTIVE    255 // (0-255) 活动转速，任一电机启用时使用
  #define CONTROLLERFAN_SPEED_IDLE        0 // (0-255) 怠速转速，电机禁用时使用
  #define CONTROLLERFAN_IDLE_TIME        60 // (seconds) 电机禁用后风扇多运行的时间

  // 使用 TEMP_SENSOR_BOARD 作为启用控制器风扇的触发条件
  //#define CONTROLLER_FAN_MIN_BOARD_TEMP 40  // (°C) 主板达到此温度时开启风扇

  //#define CONTROLLER_FAN_EDITABLE         // 启用 M710 可配置设置
  #if ENABLED(CONTROLLER_FAN_EDITABLE)
    #define CONTROLLER_FAN_MENU             // 启用控制器风扇子菜单
  #endif
#endif

/**
 * 风扇启动助力
 * 当散热风扇或控制器风扇首次启动时，先以一个能可靠
 * 使风扇转起来的转速运行一小段时间，再设定为请求的转速。
 * （在 Sanguinololu 上使用 FAN_SOFT_PWM 时无效。）
 */
//#define FAN_KICKSTART_TIME  100  // (ms)
//#define FAN_KICKSTART_POWER 180  // 64-255

// 某些冷却器可能需要非零的"关闭"状态。
//#define FAN_OFF_PWM  1

/**
 * PWM 风扇转速范围
 *
 * 定义 PWM 风扇的最小/最大转速（用 M106 设置）。
 *
 * 启用这些选项后，M106 的 0-255 数值范围会被缩放到一个子区间，
 * 以确保风扇有足够的功率转动，或以更大电流驱动低电流风扇。
 * （例如 5V/12V 风扇接 12V/24V。）
 * 数值 0 始终关闭风扇。
 *
 * 定义其中一个或两个可覆盖默认的 0-255 范围。
 */
//#define FAN_MIN_PWM 50
//#define FAN_MAX_PWM 128

/**
 * 风扇快速 PWM
 *
 * 内部通过 PWM 模式、预分频值和 TOP 分辨率的组合，
 * 产生尽可能接近期望频率的频率。
 *
 * FAST_PWM_FAN_FREQUENCY
 *   将其设置为期望的频率。
 *   对于 AVR，若未定义则默认为 F = F_CPU/(2*255*1)，
 *            即 16MHz 微控制器上 F = 31.4kHz，20MHz 微控制器上 F = 39.2kHz。
 *   对于非 AVR，若未定义则默认为 F = 1Khz。
 *   这个 F 值只是为了在缺少配置时保护硬件，
 *   并不能在用户未意识到必须专门设置频率以支持目标板时自动完成配置。
 *
 *   注意：设置过低的频率（< 10 Hz）可能导致定时器行为异常。
 *         设置过高的频率可能损坏硬件。
 *
 * USE_OCR2A_AS_TOP [默认未定义]
 *   使用 TIMER2 做 PWM 的板子存在限制，TIMER2 上只有几种可选频率：
 *   16MHz MCU: [62.5kHz, 31.4kHz (默认), 7.8kHz, 3.92kHz, 1.95kHz, 977Hz, 488Hz, 244Hz, 60Hz, 122Hz, 30Hz]
 *   20MHz MCU: [78.1kHz, 39.2kHz (默认), 9.77kHz, 4.9kHz, 2.44kHz, 1.22kHz, 610Hz, 305Hz, 153Hz, 76Hz, 38Hz]
 *   启用 USE_OCR2A_AS_TOP 可获得更大的频率范围。但请注意，此选项会
 *   禁止在 OC2A 引脚上使用 PWM。仅在不需要 OC2A 上的 PWM 时使用此选项。（请查阅原理图。）
 *   USE_OCR2A_AS_TOP 以牺牲占空比控制分辨率为代价换取更宽的频率范围。
 */
//#define FAST_PWM_FAN    // 提高风扇 PWM 频率。消除 PWM 噪声，但会增加 FET/Arduino 的发热
#if ENABLED(FAST_PWM_FAN)
  //#define FAST_PWM_FAN_FREQUENCY 31400  // 在此定义以覆盖下方默认值
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
 * 将一个 PWM 风扇用作冗余散热风扇
 */
//#define REDUNDANT_PART_COOLING_FAN 2  // 与风扇 0 同步的风扇编号。

// @section extruder

/**
 * 挤出机冷却风扇
 *
 * 挤出机自动风扇会在其对应挤出机的温度超过
 * EXTRUDER_AUTO_FAN_TEMPERATURE 时自动开启。
 *
 * 板卡引脚文件中已指定推荐引脚。可在此处覆盖，
 * 或设为 -1 完全禁用。
 *
 * 多个挤出机可以共用同一引脚，此时只要任一
 * 选中的挤出机超过阈值，风扇就会开启。
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
 * 热端冷却风扇转速计
 *
 * 定义一个或多个转速计引脚以启用风扇转速
 * 监测，并通过 M123 报告风扇转速。
 *
 * 注意：仅适用于 7000 RPM 以下的风扇。
 */
//#define FOURWIRES_FANS      // 安装 4 线 PWM 风扇时需与 AUTO_FAN 一起使用
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
 * 散热风扇多路复用器
 *
 * 此功能允许对风扇输出进行数字多路复用。
 * 多路复用器会在换头时自动切换。
 * 在下方设置 FANMUX[012]_PIN 可支持最多 2、4 或 8 个多路复用风扇。
 */
#define FANMUX0_PIN -1
#define FANMUX1_PIN -1
#define FANMUX2_PIN -1

/**
 * M355 机箱灯开关/亮度
 */
//#define CASE_LIGHT_ENABLE
#if ENABLED(CASE_LIGHT_ENABLE)
  //#define CASE_LIGHT_PIN 4                  // 如有需要可覆盖默认引脚
  #define INVERT_CASE_LIGHT false             // 若引脚为低电平时机箱灯点亮则设为 true
  #define CASE_LIGHT_DEFAULT_ON true          // 设为默认上电开启
  #define CASE_LIGHT_DEFAULT_BRIGHTNESS 105   // 设为默认上电亮度 (0-255，需要 PWM 引脚)
  //#define CASE_LIGHT_NO_BRIGHTNESS          // 禁用亮度控制。非 PWM 灯具时启用。
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

// 如果希望限位开关（默认情况下）即使在不归位时也保持开启，
// 请启用此选项。可随时用 M120、M121 覆盖。
//#define ENDSTOPS_ALWAYS_ON_DEFAULT

// @section extras

//#define Z_LATE_ENABLE // 最后时刻才启用 Z。Z 驱动器过热时需要。

// 使用外部闭环控制器。如有需要可在此覆盖引脚。
//#define EXTERNAL_CLOSED_LOOP_CONTROLLER
#if ENABLED(EXTERNAL_CLOSED_LOOP_CONTROLLER)
  //#define CLOSED_LOOP_ENABLE_PIN        -1
  //#define CLOSED_LOOP_MOVE_COMPLETE_PIN -1
#endif

/**
 * 双 X 滑车
 *
 * 此配置有两个可独立移动的 X 滑车，各自配有热端。
 * 两个滑车可用于双色或双材料打印，或在
 * "复制模式"下同时打印两个相同或 X 镜像的物体。
 * 不活动的滑车会自动停靠以防止漏料。
 * X1 为左滑车，X2 为右滑车。它们在 X 轴两端分别停靠和归位。
 * 默认情况下 X2 步进电机分配给板上第一个未使用的 E 插座。
 *
 * 以下双 X 滑车模式可通过 M605 S<mode> 选择：
 *
 *   0 : (FULL_CONTROL) 切片软件完全控制两个 X 滑车，只要它支持双 X 滑车，
 *       就能获得最佳空移效果。(M605 S0)
 *
 *   1 : (AUTO_PARK) 固件在换头时自动停靠和释放 X 滑车，
 *       无需切片软件额外支持。(M605 S1)
 *
 *   2 : (DUPLICATION) 固件使第二个 X 滑车和挤出机与
 *       第一个 X 滑车和挤出机同步移动，同时打印同一物体的两份副本。
 *       用 M605 S2 X[offs] R[deg] 设置恒定 X 偏移和温差，
 *       然后发送 M605 S2 启动复制移动。
 *
 *   3 : (MIRRORED) 源自 Formbot/Vivedino 的镜像模式，第二个挤出机
 *       复制第一个挤出机的运动，但 X 轴方向相反。
 *       用 M605 S2 X[offs] R[deg] 设置初始 X 偏移和温差，
 *       然后发送 M605 S3 启动镜像移动。
 */
//#define DUAL_X_CARRIAGE
#if ENABLED(DUAL_X_CARRIAGE)
  #define X1_MIN_POS X_MIN_POS    // 设为 X_MIN_POS
  #define X1_MAX_POS X_BED_SIZE   // 最大坐标，防止 X1 滑车撞上停靠的 X2 滑车
  #define X2_MIN_POS    80        // 最小坐标，防止 X2 滑车撞上停靠的 X1 滑车
  #define X2_MAX_POS   353        // X2 滑车的最大位置，通常也是归位位置
  #define X2_HOME_DIR    1        // 设为 1。X2 滑车总是归位到最大限位位置
  #define X2_HOME_POS X2_MAX_POS  // X2 默认归位位置。设为 X2_MAX_POS。
                                  // 注意：双 X 滑车模式下可用 M218 T1 Xn 覆盖 X2_HOME_POS。
                                  // 这样无需重新编译即可重新校准限位开关距离。
                                  // 记得在切片软件中将第二个挤出机的 X 偏移设为 0。

  // 这是默认上电模式，之后可用 M605 S<mode> 更改。
  #define DEFAULT_DUAL_X_CARRIAGE_MODE DXC_AUTO_PARK_MODE

  // 复制模式下的默认 X 偏移（通常设为打印热床宽度的一半）
  #define DEFAULT_DUPLICATION_X_OFFSET 100

  // M605 模式切换命令后默认执行的动作。通常用 G28X 应用新模式。
  //#define EVENT_GCODE_IDEX_AFTER_MODECHANGE "G28X"
#endif

/**
 * 多步进电机 / 多限位开关
 *
 * 定义 X2_DRIVER_TYPE 后，表示 X 和 X2 电机协同工作。
 * 以下关于 X 的说明同样适用于 Y 和 Z 的多步进电机配置。
 * 限位开关偏移可通过 'M666 X<offset> Y<offset> Z<offset>' 修改并保存到 EEPROM。
 *
 * - 若 X2 电机需要与 X 相反的 DIR 信号，启用 INVERT_X2_VS_X_DIR。
 *
 * - 若第二个电机有自己的限位开关（偏移可调），启用 X_DUAL_ENDSTOPS。
 *
 *   - 额外的限位开关会包含在 'M119' 的输出中。
 *
 *   - 将 X_DUAL_ENDSTOP_ADJUSTMENT 设为 X2 限位开关的已知误差。
 *     该值会在 'G28' / 'G28 X' 时作用于 X2 电机。
 *     通过 X 轴归位并测量误差来获取偏移。
 *     也可用 'M666 X<offset>' 设置，并用 'M500' 保存到 EEPROM。
 *
 *   - 使用 X2_USE_ENDSTOP 按名称设置限位开关插座。(_XMIN_, _XMAX_, _YMIN_, _YMAX_, _ZMIN_, _ZMAX_)
 */
#if HAS_X2_STEPPER && DISABLED(DUAL_X_CARRIAGE)
  //#define INVERT_X2_VS_X_DIR        // X2 方向信号与 X 相反
  //#define X_DUAL_ENDSTOPS           // X2 有自己的限位开关
  #if ENABLED(X_DUAL_ENDSTOPS)
    #define X2_USE_ENDSTOP    _XMAX_  // X2 限位开关的板载插座。别忘了启用 USE_*_PLUG。
    #define X2_ENDSTOP_ADJUSTMENT  0  // X2 相对 X 限位开关的偏移
  #endif
#endif

#if HAS_DUAL_Y_STEPPERS
  //#define INVERT_Y2_VS_Y_DIR        // Y2 方向信号与 Y 相反
  //#define Y_DUAL_ENDSTOPS           // Y2 有自己的限位开关
  #if ENABLED(Y_DUAL_ENDSTOPS)
    #define Y2_USE_ENDSTOP    _YMAX_  // Y2 限位开关的板载插座。别忘了启用 USE_*_PLUG。
    #define Y2_ENDSTOP_ADJUSTMENT  0  // Y2 相对 Y 限位开关的偏移
  #endif
#endif

//
// 多 Z 步进电机
//
#ifdef Z2_DRIVER_TYPE
  //#define INVERT_Z2_VS_Z_DIR        // Z2 方向信号与 Z 相反

  //#define Z_MULTI_ENDSTOPS          // 其他 Z 轴有自己的限位开关
  #if ENABLED(Z_MULTI_ENDSTOPS)
    #define Z2_USE_ENDSTOP   _XMAX_   // Z2 限位开关的板载插座。别忘了启用 USE_*_PLUG。
    #define Z2_ENDSTOP_ADJUSTMENT 0   // Z2 相对 Z 限位开关的偏移
  #endif
  #ifdef Z3_DRIVER_TYPE
    //#define INVERT_Z3_VS_Z_DIR      // Z3 方向信号与 Z 相反
    #if ENABLED(Z_MULTI_ENDSTOPS)
      #define Z3_USE_ENDSTOP   _YMAX_ // Z3 限位开关的板载插座。别忘了启用 USE_*_PLUG。
      #define Z3_ENDSTOP_ADJUSTMENT 0 // Z3 相对 Z 限位开关的偏移
    #endif
  #endif
  #ifdef Z4_DRIVER_TYPE
    //#define INVERT_Z4_VS_Z_DIR      // Z4 方向信号与 Z 相反
    #if ENABLED(Z_MULTI_ENDSTOPS)
      #define Z4_USE_ENDSTOP   _ZMAX_ // Z4 限位开关的板载插座。别忘了启用 USE_*_PLUG。
      #define Z4_ENDSTOP_ADJUSTMENT 0 // Z4 相对 Z 限位开关的偏移
    #endif
  #endif
#endif

// 用两个同步步进电机驱动 E 轴
//#define E_DUAL_STEPPER_DRIVERS
#if ENABLED(E_DUAL_STEPPER_DRIVERS)
  //#define INVERT_E1_VS_E0_DIR       // E 方向信号相反
#endif

// 使用 M380 激活当前挤出机上的电磁铁。用 M381 全部禁用。
// 为每个带电磁铁的挤出机定义 SOL0_PIN、SOL1_PIN 等。
//#define EXT_SOLENOID

// @section homing

/**
 * 归位流程
 * 归位（G28）会向限位开关做一次不限时移动，以确定
 * 刀头相对工作空间的位置。
 */

#define SENSORLESS_BACKOFF_MM  { 5, 5, 0, 0, 0, 0 }  // (linear=mm, rotational=°) 无传感器归位前从限位开关回退的距离

#define HOMING_BUMP_MM      { 0, 0, 2, 2, 2, 5 } // (linear=mm, rotational=°) 首次触碰后从限位开关回退的距离
#define HOMING_BUMP_DIVISOR { 2, 2, 4, 4, 4, 2 } // 二次触碰速度除数（除以归位进给速度）

//#define HOMING_BACKOFF_POST_MM { 5, 5, 0, 0, 0, 0 }  // (linear=mm, rotational=°) 归位完成后从限位开关回退的距离

//#define QUICK_HOME                            // 若 G28 包含 XY 则先做对角移动
//#define HOME_Y_BEFORE_X                     // 若 G28 包含 XY 则先归位 Y 再归位 X
//#define HOME_Z_FIRST                        // 先归位 Z。需要 Z-MIN 限位开关（不能是探针）。
//#define CODEPENDENT_XY_HOMING               // 若 X/Y 必须先归位 Y/X 才能归位

// @section bltouch

#if ENABLED(BLTOUCH)
  /**
   * 可选用默认值（推荐），或针对特殊用途使用以下 DEFINES。
   * 不要激活探针可能无法识别的设置。仿制品可能会误解
   * 高级命令。
   *
   * 注意：如果探针没有伸出，请执行"Reset"和"Self-Test"，然后检查
   *       棕色、红色和橙色线的接线。
   *
   * 注意：如果探针的触发信号未被识别，很多时候
   *       是因为黑色和白色线需要互换。它们不像真正的开关那样可以"互换"。
   *       所以请先检查接线。
   *
   * 所有 BLTouch 及其仿制品的设置：
   */

  // 安全：探针需要时间来识别命令。
  //         最小命令延迟 (ms)。如有需要可启用并增大。
  //#define BLTOUCH_DELAY 500

  /**
   * 适用于 BLTOUCH Classic 1.2、1.3 或 BLTouch Smart 1.0、2.0、2.2、3.0、3.1 及大多数仿制品的设置：
   */

  // 功能：伸出后切换到 SW 模式。它会使输出脉冲变长。在某些特殊情况下有用，
  //          例如输入配置有噪声或经过滤波时。
  //#define BLTOUCH_FORCE_SW_MODE

  /**
   * BLTouch Smart 3.0 和 3.1 的设置
   * 摘要：
   *   - 电压模式：5V 和 OD（漏极开路 - "无逻辑电压"）输出模式
   *   - 高速模式
   *   - 禁用 LCD 电压选项
   */

  /**
   * 危险：除非控制器可耐受 5V，否则不要启用 5V 模式！
   * V3.0 或 3.1：在 Marlin 启动时将默认模式设为 5V 模式。
   * 若禁用，3.0 上硬编码的默认模式为 OD 模式。
   * 启动时 Marlin 会将其 EEPROM 与此值比较。若所选模式
   * 不同，将在初始化时完成一次模式设置的 EEPROM 写入。
   * 可用下方选项强制对 V3.1 探针执行 EEPROM 写入。
   */
  //#define BLTOUCH_SET_5V_MODE

  // 安全：在 LCD 菜单中启用电压模式设置。
  //#define BLTOUCH_LCD_VOLTAGE_MENU

  /**
   * 安全：在连接电压模式未知的探针时启用。
   * V3.0：在 Marlin 启动时将探针设为上文选择的模式。3.0 上使用 5V 模式时必须启用
   * V3.1：在 Marlin 启动时强制将模式未知的探针设为所选模式（ = 探针 EEPROM 写入 ）
   * 为延长探针寿命，使用一次后请关闭并重新刷写固件。
   */
  //#define BLTOUCH_FORCE_MODE_SET

  /**
   * 为探针启用"高速"选项。
   * 危险：如果探针偶尔失灵请禁用。仅适用于稳定且调试良好的系统。
   * 此功能专为 Z 轴移动非常快的 Delta 机型设计；不过速度较快的
   * 笛卡尔机型也许可以使用。如果机器无法足够快地抬起 Z 轴，BLTouch 可能进入报警状态。
   *
   * 在此设置默认状态，可用 'M401 S' 或 UI 更改，M500 保存，M502 重置。
   */
  //#define BLTOUCH_HS_MODE true

  #ifdef BLTOUCH_HS_MODE
    // 探针 Z 偏移（M851 Z）是探针触发时的高度。
    // 它必须足够大，使探针针尖远离热床，并避免
    // 被热床夹子挂住。
    #define BLTOUCH_HS_EXTRA_CLEARANCE    7 // 额外 Z 方向间隙
  #endif

#endif // BLTOUCH

// @section calibration

/**
 * Z 步进电机自动对齐
 * 添加 G34 命令，使用热床探针对齐多个 Z 步进电机。
 */
//#define Z_STEPPER_AUTO_ALIGN
#if ENABLED(Z_STEPPER_AUTO_ALIGN)
  /**
   * 定义 Z1、Z2 [, Z3 [, Z4]] 的探针 X 和 Y 位置。
   * 这些位置是相对于机器的，不随 M206 归位偏移而移动！
   * 若未定义，将使用探针极限位置。
   * 可用 'M422 S<index> X<pos> Y<pos>' 覆盖。
   */
  //#define Z_STEPPER_ALIGN_XY { {  10, 190 }, { 100,  10 }, { 190, 190 } }

  /**
   * 自动计算的探针位置的方向。
   * 可用 'M422 S<index> X<pos> Y<pos>' 覆盖 Z 步进电机对齐点。
   *
   * 2 步进电机:  (0)     (1)
   *               |       |   2   |
   *               | 1   2 |       |
   *               |       |   1   |
   *
   * 3 步进电机:  (0)     (1)     (2)     (3)
   *               |   3   | 1     | 2   1 |     2 |
   *               |       |     3 |       | 3     |
   *               | 1   2 | 2     |   3   |     1 |
   *
   * 4 步进电机:  (0)     (1)     (2)     (3)
   *               | 4   3 | 1   4 | 2   1 | 3   2 |
   *               |       |       |       |       |
   *               | 1   2 | 2   3 | 3   4 | 4   1 |
   */
  #ifndef Z_STEPPER_ALIGN_XY
    //#define Z_STEPPERS_ORIENTATION 0
  #endif

  /**
   * 为热床校准时更快收敛而设的 Z 步进电机位置。
   * 需要 3 或 4 个 Z 步进电机。
   *
   * 为 Z1、Z2、Z3... 定义步进电机 XY 位置，对应热床托架上
   * 螺丝的位置，每个 Z 步进电机一个位置，按步进电机
   * 驱动器顺序排列。
   */
  //#define Z_STEPPER_ALIGN_STEPPER_XY { { 210.7, 102.5 }, { 152.6, 220.0 }, { 94.5, 102.5 } }

  #ifndef Z_STEPPER_ALIGN_STEPPER_XY
    // 放大系数。用于在步进电机（丝杆）位置比测试点
    // 更远时放大或缩小校正步长。
    #define Z_STEPPER_ALIGN_AMP 1.0       // 使用大于 1.0 的值。注意：这可能导致不稳定！
  #endif

  // 在 300mm 热床上 5% 的坡度会产生约 1.5cm 的偏差
  #define G34_MAX_GRADE              5    // (%) G34 能处理的最大倾角
  #define Z_STEPPER_ALIGN_ITERATIONS 5    // 对齐过程中执行的迭代次数
  #define Z_STEPPER_ALIGN_ACC        0.02 // 精度优于此值时提前停止迭代
  #define RESTORE_LEVELING_AFTER_G34      // G34 完成后恢复调平设置？
  // G34 之后，是重新归位 Z（G28 Z）还是仅根据最后几次探针高度计算？
  // 重新归位可能更精确地复现实际的 'G28 Z' 归位高度，尤其在热床不平时。
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

  #define RESTORE_LEVELING_AFTER_G35    // 启用后在操作完成后恢复调平设置
  //#define REPORT_TRAMMING_MM          // 报告每个点相对第一点的 Z 偏差 (mm)

  //#define ASSISTED_TRAMMING_WIZARD    // 在 LCD 菜单中添加调平向导

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
 * 基于固定时间的运动控制 -- 实验性
 * 使用 G 代码 M493 启用/禁用并设置参数。
 */
//#define FT_MOTION
#if ENABLED(FT_MOTION)
  #define FTM_DEFAULT_MODE         ftMotionMode_ENABLED // 固定时间控制的默认模式。（枚举定义见 ft_types.h）
  #define FTM_DEFAULT_DYNFREQ_MODE dynFreqMode_DISABLED // 动态频率计算的默认模式。（枚举定义见 ft_types.h）
  #define FTM_SHAPING_DEFAULT_X_FREQ 37.0f              // (Hz) 输入整形器使用的默认峰值频率。
  #define FTM_SHAPING_DEFAULT_Y_FREQ 37.0f              // (Hz) 输入整形器使用的默认峰值频率。
  #define FTM_LINEAR_ADV_DEFAULT_ENA false              // 线性推进（Linear Advance）默认启用 (true) 或禁用 (false)。
  #define FTM_LINEAR_ADV_DEFAULT_K    0.0f              // 线性推进增益的默认值。
  #define FTM_SHAPING_ZETA            0.1f              // 输入整形器使用的 Zeta 值。
  #define FTM_SHAPING_V_TOL           0.05f             // EI 输入整形器使用的振动容差。

  /**
   * 高级配置
   */
  #define FTM_BATCH_SIZE 100                            // 轨迹生成的批处理大小；
                                                        // Ulendo FBS 为窗口大小的一半。
  #define FTM_FS           1000                         // (Hz) 轨迹生成频率。(1 / FTM_TS)
  #define FTM_TS              0.001f                    // (s) 轨迹生成的时间步长。(1 / FTM_FS)
  #define FTM_STEPPER_FS  20000                         // (Hz) 步进电机 I/O 更新频率。
  #define FTM_MIN_TICKS ((STEPPER_TIMER_RATE) / (FTM_STEPPER_FS)) // 步与步之间最小的步进计时器 tick 数。
  #define FTM_MIN_SHAPE_FREQ 10                         // 最小整形频率。
  #define FTM_ZMAX          100                         // 整形函数的最大延迟（只能为偶数！）。
                                                        // 计算方法：
                                                        //    ZV：1/2 * (FTM_FS / FTM_MIN_SHAPE_FREQ)。
                                                        //    ZVD、MZV：(FTM_FS / FTM_MIN_SHAPE_FREQ)。
                                                        //    2HEI：3/2 * (FTM_FS / FTM_MIN_SHAPE_FREQ)。
                                                        //    3HEI：2 * (FTM_FS / FTM_MIN_SHAPE_FREQ)。
  #define FTM_STEPS_PER_UNIT_TIME 20                    // 单位时间内插补的步进命令数。
                                                        // 计算方法：(FTM_STEPPER_FS / FTM_FS)。
  #define FTM_CTS_COMPARE_VAL 10                        // 插补算法中使用的比较值。
                                                        // 计算方法：(FTM_STEPS_PER_UNIT_TIME / 2)。
  // 可以配置这些值来调整 loop() 的执行时长。
  #define FTM_STEPS_PER_LOOP 60                         // 每次 loop() 生成的步进命令数量。
  #define FTM_POINTS_PER_LOOP 100                       // 每次 loop() 生成的轨迹点数量。

  // 可以配置此值来调整消耗命令缓冲区所需的时长。
  // 如果步进电机运动不平滑，可尝试增大此值。
  #define FTM_STEPPERCMD_BUFF_SIZE 1000                 // 步进命令缓冲区的大小。
#endif

/**
 * 输入整形 —— 实验性
 *
 * 针对 X 和/或 Y 轴运动的零振动 (ZV) 输入整形。
 *
 * 此选项会为步进缓冲区占用大量 SRAM。缓冲区大小会根据
 * SHAPING_FREQ_[XY]、DEFAULT_AXIS_STEPS_PER_UNIT、
 * DEFAULT_MAX_FEEDRATE 和 ADAPTIVE_STEP_SMOOTHING 自动计算。
 * 默认计算结果可以通过设置 SHAPING_MIN_FREQ 和/或 SHAPING_MAX_FEEDRATE 覆盖。
 * 频率越高、进给速度越低，缓冲区越小。
 * 如果运行时缓冲区太小，输入整形在高速运动时的
 * 效果会打折扣。
 *
 * 使用 M593 D<factor> F<frequency> 调整：
 *
 *  D<factor>    设置 zeta/阻尼系数。若未指定轴（X、Y 等），则对所有轴生效。
 *  F<frequency> 设置频率。若未指定轴（X、Y 等），则对所有轴生效。
 *  T[map]       输入整形类型，0:ZV, 1:EI, 2:2H EI（尚未实现）
 *  X<1>         仅为 X 轴设置给定参数。
 *  Y<1>         仅为 Y 轴设置给定参数。
 */
//#define INPUT_SHAPING_X
//#define INPUT_SHAPING_Y
#if EITHER(INPUT_SHAPING_X, INPUT_SHAPING_Y)
  #if ENABLED(INPUT_SHAPING_X)
    #define SHAPING_FREQ_X  40          // (Hz) X 轴默认的主共振频率。
    #define SHAPING_ZETA_X  0.15f       // X 轴的阻尼比（范围：0.0 = 无阻尼，1.0 = 临界阻尼）。
  #endif
  #if ENABLED(INPUT_SHAPING_Y)
    #define SHAPING_FREQ_Y  40          // (Hz) Y 轴默认的主共振频率。
    #define SHAPING_ZETA_Y  0.15f       // Y 轴的阻尼比（范围：0.0 = 无阻尼，1.0 = 临界阻尼）。
  #endif
  //#define SHAPING_MIN_FREQ  20        // 默认取各整形频率中的最小值。可覆盖此设置以影响 SRAM 占用。
  //#define SHAPING_MAX_STEPRATE 10000  // 默认取被整形轴的总最大步进速率。可覆盖此设置以影响 SRAM 占用。
  //#define SHAPING_MENU                // 在 LCD 上添加设置整形参数的菜单。
#endif

// @section motion

#define AXIS_RELATIVE_MODES { false, false, false, false, false, false }

// 为间距较远的连体喷嘴添加 Duplicate（复制）选项
//#define MULTI_NOZZLE_DUPLICATION

// 默认情况下步进电机驱动需要高电平有效信号，但某些大功率驱动需要低电平有效信号才能步进。
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
 * 步进电机空闲关闭
 * 启用 DISABLE_IDLE_* 可在轴空闲一段时间后关闭其步进电机。
 * 默认超时时长可通过 M18 和 M84 覆盖。设为 0 表示不超时。
 */
#define DEFAULT_STEPPER_TIMEOUT_SEC 3600
#define DISABLE_IDLE_X
#define DISABLE_IDLE_Y
#define DISABLE_IDLE_Z    // 如果喷嘴可能砸到已打印的工件，请禁用此项！
#define DISABLE_IDLE_I
#define DISABLE_IDLE_J
#define DISABLE_IDLE_K
//#define DISABLE_IDLE_U
//#define DISABLE_IDLE_V
//#define DISABLE_IDLE_W
#define DISABLE_IDLE_E    // 关闭所有空闲的挤出机

// 打印移动和空走移动的默认最小进给速度
#define DEFAULT_MINIMUMFEEDRATE             0.0     // (mm/s) 最小进给速度。通过 M205 S 设置。
#define DEFAULT_MINTRAVELFEEDRATE           0.0     // (mm/s) 最小空走进给速度。通过 M205 T 设置。
#if HAS_ROTATIONAL_AXES
  #define DEFAULT_ANGULAR_MINIMUMFEEDRATE   0.0     // (°/s) 仅旋转移动的最小进给速度。通过 M205 P 设置。
  #define DEFAULT_ANGULAR_MINTRAVELFEEDRATE 0.0     // (°/s) 仅旋转移动的最小空走进给速度。通过 M205 Q 设置。
#endif

// 缓冲区排空时段落所需的最短时间
#define DEFAULT_MINSEGMENTTIME        20000   // (µs) 通过 M205 B 设置。

// 当前瞻缓冲区（默认）半满时降低机器速度。
// 缓冲区越大，减速除数应相应增大。
#define SLOWDOWN
#if ENABLED(SLOWDOWN)
  #define SLOWDOWN_DIVISOR 2
#endif

/**
 * XY 频率限制
 * 通过限制小幅之字形填充移动的频率来减少共振。
 * 参见 https://hydraraptor.blogspot.com/2010/12/frequency-limit.html
 * 使用 M201 F<freq> G<min%> 可在运行时更改限制。
 */
//#define XY_FREQUENCY_LIMIT      10 // (Hz) 小幅之字形填充移动的最大频率。通过 M201 F<hertz> 设置。
#ifdef XY_FREQUENCY_LIMIT
  #define XY_FREQUENCY_MIN_PERCENT 5 // (percent) 应用 FR 的最小百分比。通过 M201 G<min%> 设置。
#endif

// 规划器最小交接速度。设定规划器在缓冲区末端
// 以及所有停顿处规划的默认最小速度。该值不应远大于 0，
// 只有当观察到用户机器在极低速运行时出现异常行为才应修改。
#define MINIMUM_PLANNER_SPEED 0.05 // (mm/s)

//
// 间隙（背隙）补偿
// 在轴换向时增加额外移动量以补偿间隙。
//
//#define BACKLASH_COMPENSATION
#if ENABLED(BACKLASH_COMPENSATION)
  // 定义间隙距离和修正量。
  // 如果启用了 BACKLASH_GCODE，这些值将作为默认值。
  #define BACKLASH_DISTANCE_MM { 0, 0, 0 } // (linear=mm, rotational=°) 每个直线轴一个数值
  #define BACKLASH_CORRECTION    0.0       // 0.0 = 不修正；1.0 = 完全修正

  // 在 CORE 运动学中为电机换向添加步数
  //#define CORE_BACKLASH

  // 设置 BACKLASH_SMOOTHING_MM 可将间隙修正分散到多个段落中，
  // 以减少打印瑕疵。（启用后内存和计算开销都很大！）
  //#define BACKLASH_SMOOTHING_MM 3 // (mm)

  // 添加间隙值的运行时配置与调整 (M425)
  //#define BACKLASH_GCODE

  #if ENABLED(BACKLASH_GCODE)
    // 探测时 (G29) 测量 Z 轴间隙，并用 "M425 Z" 设置
    #define MEASURE_BACKLASH_WHEN_PROBING

    #if ENABLED(MEASURE_BACKLASH_WHEN_PROBING)
      // 测量时，探针会从接触点向外最多移动 BACKLASH_MEASUREMENT_LIMIT
      // mm，以 BACKLASH_MEASUREMENT_RESOLUTION 为增量，
      // 同时检测接触是否断开。
      #define BACKLASH_MEASUREMENT_LIMIT       0.5   // (mm)
      #define BACKLASH_MEASUREMENT_RESOLUTION  0.005 // (mm)
      #define BACKLASH_MEASUREMENT_FEEDRATE    Z_PROBE_FEEDRATE_SLOW // (mm/min)
    #endif
  #endif
#endif

/**
 * 间隙、位置与热端偏移的自动校准
 *
 * 启用 G425，利用安装在热床上的导电
 * 立方体、螺栓或垫圈执行自动校准。
 *
 * G425 使用探针触碰热床上校准物体的顶面和侧面，
 * 测量和/或修正位置偏移、轴间隙
 * 以及热端偏移。
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

  // 以下参数针对喷嘴尖端的锥形部分。
  #define CALIBRATION_NOZZLE_TIP_HEIGHT          1.0  // mm
  #define CALIBRATION_NOZZLE_OUTER_DIAMETER      2.0  // mm

  // 取消注释以启用报告输出（"G425 V" 需要此功能，但会占用 PROGMEM）。
  //#define CALIBRATION_REPORTING

  // 热床上立方体/螺栓/垫圈的真实位置和尺寸。
  #define CALIBRATION_OBJECT_CENTER     { 264.0, -22.0,  -2.0 } // mm
  #define CALIBRATION_OBJECT_DIMENSIONS {  10.0,  10.0,  10.0 } // mm

  // 注释掉探针无法触及的面。要获得最佳
  // 自动校准结果，所有面都必须可以触及。
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

  // 仅当顶面中心为平面时才能在正中心探测。如果
  // 探测对象是螺钉头或空心垫圈，请靠近边缘探测。
  //#define CALIBRATION_MEASURE_AT_TOP_EDGES

  // 定义校准期间要读取的引脚
  #ifndef CALIBRATION_PIN
    //#define CALIBRATION_PIN -1            // 在此处定义以覆盖默认引脚
    #define CALIBRATION_PIN_INVERTING false // 设为 true 以反转自定义引脚
    //#define CALIBRATION_PIN_PULLDOWN
    #define CALIBRATION_PIN_PULLUP
  #endif
#endif

/**
 * 多重步进以突发方式发送脉冲，降低高步进速率下的 MCU 占用。
 * 由此可获得 MCU 原本无法支持的更高进给速度。
 */
#define MULTISTEPPING_LIMIT   16  //: [1, 2, 4, 8, 16, 32, 64, 128]

/**
 * 自适应步进平滑可提高多轴移动的分辨率，尤其是当步进频率
 * 低于 1kHz（AVR）或 10kHz（ARM）时，多轴移动中轴间的混叠会产生可闻的
 * 振动和表面瑕疵。该算法会自适应地在最低步进频率下
 * 提供尽可能好的步进平滑效果。
 */
//#define ADAPTIVE_STEP_SMOOTHING

/**
 * 自定义细分
 * 可根据实际配置按需覆盖。最多支持 3 个 MS 引脚。
 */
//#define MICROSTEP1 LOW,LOW,LOW
//#define MICROSTEP2 HIGH,LOW,LOW
//#define MICROSTEP4 LOW,HIGH,LOW
//#define MICROSTEP8 HIGH,HIGH,LOW
//#define MICROSTEP16 LOW,LOW,HIGH
//#define MICROSTEP32 HIGH,LOW,HIGH

// 细分设置（要求板卡具有名为 X_MS1、X_MS2 等的引脚）
#define MICROSTEP_MODES { 16, 16, 16, 16, 16, 16 } // [1,2,4,8,16]

/**
 *  @section  stepper motor current
 *
 *  部分板卡支持通过固件设置步进电机电流。
 *
 *  上电时的电机电流由以下项设置：
 *    PWM_MOTOR_CURRENT - 用于 MINIRAMBO 和 ULTIMAIN_2
 *                         已知兼容芯片：A4982
 *    DIGIPOT_MOTOR_CURRENT - 用于 BQ_ZUM_MEGA_3D、RAMBO 和 SCOOVO_X9H
 *                         已知兼容芯片：AD5206
 *    DAC_MOTOR_CURRENT_DEFAULT - 用于 PRINTRBOARD_REVF 和 RIGIDBOARD_V2
 *                         已知兼容芯片：MCP4728
 *    DIGIPOT_I2C_MOTOR_CURRENTS - 用于 5DPRINT、AZTEEG_X3_PRO、AZTEEG_X5_MINI_WIFI、MIGHTYBOARD_REVE
 *                         已知兼容芯片：MCP4451、MCP4018
 *
 *  电机电流也可以通过 M907 - M910 和 LCD 设置。
 *    M907 - 对所有驱动生效。
 *    M908 - BQ_ZUM_MEGA_3D、RAMBO、PRINTRBOARD_REVF、RIGIDBOARD_V2 和 SCOOVO_X9H
 *    M909、M910 和 LCD - 仅限 PRINTRBOARD_REVF 和 RIGIDBOARD_V2
 */
//#define PWM_MOTOR_CURRENT { 1300, 1300, 1250 }          // 数值单位为毫安
//#define DIGIPOT_MOTOR_CURRENT { 135,135,135,135,135 }   // 数值范围 0-255 (RAMBO 135 = ~0.75A, 185 = ~1A)
//#define DAC_MOTOR_CURRENT_DEFAULT { 70, 80, 90, 80 }    // 默认驱动百分比 - X、Y、Z、E 轴

/**
 * 基于 I2C 的 DIGIPOT（例如 Azteeg X3 Pro）
 */
//#define DIGIPOT_MCP4018             // 需要 https://github.com/felias-fogg/SlowSoftI2CMaster
//#define DIGIPOT_MCP4451
#if EITHER(DIGIPOT_MCP4018, DIGIPOT_MCP4451)
  #define DIGIPOT_I2C_NUM_CHANNELS 8  // 5DPRINT:4   AZTEEG_X3_PRO:8   MKS_SBASE:5   MIGHTYBOARD_REVE:5

  // 实际电机电流，单位安培。条目数量必须与 DIGIPOT_I2C_NUM_CHANNELS 一致。
  // 这些值与物理驱动器一一对应，更改顺序时请务必留意。
  #define DIGIPOT_I2C_MOTOR_CURRENTS { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 } // AZTEEG_X3_PRO

  //#define DIGIPOT_USE_RAW_VALUES    // 使用 DIGIPOT_MOTOR_CURRENT 的原始滑块值（而非 A4988 电机电流）

  /**
   * 常用从机地址：
   *
   *                        A   (A shifted)   B   (B shifted)  IC
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
//=============================其他功能===========================
//===========================================================================

// @section lcd

#if HAS_MANUAL_MOVE_MENU
  #define MANUAL_FEEDRATE { 50*60, 50*60, 4*60, 2*60 } // (mm/min) 从面板沿 X、Y、Z、E 手动移动的进给速度
  #define FINE_MANUAL_MOVE 0.025    // (mm) 最小手动移动量（< 0.1mm），在大多数机器上适用于 Z 轴
  #if IS_ULTIPANEL
    #define MANUAL_E_MOVES_RELATIVE // 显示挤出机移动距离而非“位置”
    #define ULTIPANEL_FEEDMULTIPLY  // 编码器在状态屏上设置进给速度倍率
  #endif
#endif

// 编码器旋转越快时数值变化越快
#define ENCODER_RATE_MULTIPLIER
#if ENABLED(ENCODER_RATE_MULTIPLIER)
  #define ENCODER_10X_STEPS_PER_SEC   30  // (steps/s) 10 倍速时的编码器速率
  #define ENCODER_100X_STEPS_PER_SEC  80  // (steps/s) 100 倍速时的编码器速率
#endif

// 在状态屏上更改进给速度时发出蜂鸣
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
     * 启用后，向导启动时会初始化探针 Z 偏移。
     * 使用略高于估算的喷嘴-探针 Z 偏移的高度。
     * 例如，偏移为 -5 时，起始高度可取 -4。
     */
    //#define PROBE_OFFSET_WIZARD_START_Z -4.0

    // 设置一个便于校准的位置（探测点与喷嘴/热床距离）
    //#define PROBE_OFFSET_WIZARD_XY_POS { X_CENTER, Y_CENTER }
  #endif
#endif

#if HAS_MARLINUI_MENU

  #if HAS_BED_PROBE
    // 在探针偏移菜单中添加校准功能，以补偿 X 轴扭转。
    //#define X_AXIS_TWIST_COMPENSATION
    #if ENABLED(X_AXIS_TWIST_COMPENSATION)
      /**
       * 启用后，向导启动时会初始化探针 Z 偏移。
       * 使用略高于估算的喷嘴-探针 Z 偏移的高度。
       * 例如，偏移为 -5 时，起始高度可取 -4。
       */
      #define XATC_START_Z 0.0
      #define XATC_MAX_POINTS 3             // 向导中要探测的点数
      #define XATC_Y_POSITION Y_CENTER      // (mm) 要探测的 Y 位置
      #define XATC_Z_OFFSETS { 0, 0, 0 }    // X 轴各采样点的 Z 偏移
    #endif

    // 在运动菜单中显示展开/收起探针选项。
    #define PROBE_DEPLOY_STOW_MENU
  #endif

  // 在 LCD 主菜单中包含打印机信息页
  //#define LCD_INFO_MENU
  #if ENABLED(LCD_INFO_MENU)
    //#define LCD_PRINTER_INFO_IS_BOOTSCREEN // 显示开机画面而非打印机信息页
  #endif

  // 即使热床较小，也在 MarlinUI 中添加 50/100mm 移动
  //#define LARGE_MOVE_ITEMS

  // “返回”菜单项将高亮保持在顶部
  //#define TURBO_BACK_MENU_ITEM

  // 在顶层插入预热菜单，便于快速访问
  //#define PREHEAT_SHORTCUT_MENU_ITEM

#endif // HAS_MARLINUI_MENU

#if HAS_DISPLAY
  /**
   * *** 敬请厂商阅读 ***
   *
   * Marlin 允许您为图形 LCD 添加自定义开机图像。
   * 启用此选项后，Marlin 会先显示您的自定义画面，
   * 然后显示带有版本号和网址的标准 Marlin 标志。
   *
   * 我们鼓励您善用这一新功能，同时也诚挚
   * 希望您保留未经修改的 Marlin 开机画面。
   */
  #if ANY(HAS_MARLINUI_U8GLIB, TOUCH_UI_FTDI_EVE, IS_DWIN_MARLINUI)
    #define SHOW_BOOTSCREEN                 // 启动时显示 Marlin 开机画面。** 生产固件务必启用 **
    #if ENABLED(SHOW_BOOTSCREEN)
      #define BOOTSCREEN_TIMEOUT 4000       // (ms) 开机画面的总显示时长
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

  // 滚动显示较长的状态消息
  //#define STATUS_MESSAGE_SCROLLING

  // 为低优先级状态消息设置超时
  //#define STATUS_MESSAGE_TIMEOUT_SEC 30 // (seconds)

  // 在信息屏上尽可能以一位小数显示 XY
  //#define LCD_DECIMAL_SMALL_XY

  // 打印期间显示 E 位置（耗材用量）
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
    //#define NEO2_COLOR_PRESETS              // 启用第二组 NeoPixel 预设颜色菜单选项
    #if ENABLED(LED_COLOR_PRESETS)
      #define LED_USER_PRESET_RED        255  // 用户定义的红色值
      #define LED_USER_PRESET_GREEN      128  // 用户定义的绿色值
      #define LED_USER_PRESET_BLUE         0  // 用户定义的蓝色值
      #define LED_USER_PRESET_WHITE      255  // 用户定义的白色值
      #define LED_USER_PRESET_BRIGHTNESS 255  // 用户定义的亮度
      //#define LED_USER_PRESET_STARTUP       // 启动时让打印机显示用户预设颜色
    #endif
    #if ENABLED(NEO2_COLOR_PRESETS)
      #define NEO2_USER_PRESET_RED        255 // 用户定义的红色值
      #define NEO2_USER_PRESET_GREEN      128 // 用户定义的绿色值
      #define NEO2_USER_PRESET_BLUE         0 // 用户定义的蓝色值
      #define NEO2_USER_PRESET_WHITE      255 // 用户定义的白色值
      #define NEO2_USER_PRESET_BRIGHTNESS 255 // 用户定义的亮度
      //#define NEO2_USER_PRESET_STARTUP      // 启动时让打印机为第二条灯带显示用户预设颜色
    #endif
  #endif

#endif // HAS_DISPLAY

// 添加 'M73' 以设置打印任务进度，覆盖 Marlin 内置的估算值
//#define SET_PROGRESS_MANUALLY
#if ENABLED(SET_PROGRESS_MANUALLY)
  #define SET_PROGRESS_PERCENT            // 添加 'P' 参数以设置已完成百分比
  #define SET_REMAINING_TIME              // 添加 'R' 参数以设置剩余时间
  //#define SET_INTERACTION_TIME          // 添加 'C' 参数以设置到下次换耗材或其他用户交互的时间
  //#define M73_REPORT                    // 向主机报告 M73 值
  #if BOTH(M73_REPORT, SDSUPPORT)
    #define M73_REPORT_SD_ONLY            // 仅在从 SD 卡打印时报告
  #endif
#endif

// LCD 打印进度选项。多种时间可轮流显示。
#if HAS_DISPLAY && EITHER(SDSUPPORT, SET_PROGRESS_MANUALLY)
  #define SHOW_PROGRESS_PERCENT           // 显示打印进度百分比（不影响进度条）
  #define SHOW_ELAPSED_TIME               // 显示已打印时间（前缀 'E'）
  //#define SHOW_REMAINING_TIME           // 显示预计完成时间（前缀 'R'）
  #if ENABLED(SET_INTERACTION_TIME)
    #define SHOW_INTERACTION_TIME         // 显示到下次用户交互的时间（'C' = 换耗材）
  #endif
  //#define PRINT_PROGRESS_SHOW_DECIMALS  // 以小数位显示/报告进度，并非所有 UI 都支持

  #if EITHER(HAS_MARLINUI_HD44780, IS_TFTGLCD_PANEL)
    //#define LCD_PROGRESS_BAR            // 在 HD44780 LCD 上为 SD 打印显示进度条
    #if ENABLED(LCD_PROGRESS_BAR)
      #define PROGRESS_BAR_BAR_TIME 2000  // (ms) 进度条的显示时长
      #define PROGRESS_BAR_MSG_TIME 3000  // (ms) 状态消息的显示时长
      #define PROGRESS_MSG_EXPIRE      0  // (ms) 状态消息的保留时长（0=永久）
      //#define PROGRESS_MSG_ONCE         // 显示消息 MSG_TIME 时间后将其清除
      //#define LCD_PROGRESS_BAR_TEST     // 添加测试进度条的菜单项
    #endif
  #endif
#endif

#if ENABLED(SDSUPPORT)
  /**
   * SD 卡 SPI 速度
   * 可能有助于解决“volume init”错误。
   *
   * 启用并设置为 SPI_HALF_SPEED、SPI_QUARTER_SPEED 或 SPI_EIGHTH_SPEED，
   *  否则将使用全速。
   *
   * :['SPI_HALF_SPEED', 'SPI_QUARTER_SPEED', 'SPI_EIGHTH_SPEED']
   */
  //#define SD_SPI_SPEED SPI_HALF_SPEED

  // 标准 SD 检测电路在插入介质时读 LOW，空载时读 HIGH。
  // 如果您的 SD 卡检测不正确，请启用此选项并设为 HIGH。
  //#define SD_DETECT_STATE HIGH

  //#define SD_IGNORE_AT_STARTUP            // 启动时不挂载 SD 卡
  //#define SDCARD_READONLY                 // 只读 SD 卡（可节省 2K 以上 flash）

  //#define GCODE_REPEAT_MARKERS            // 启用 G 代码 M808 设置重复标记并执行循环

  #define SD_PROCEDURE_DEPTH 1              // 如需更多层嵌套的 M32 调用可增大此值

  #define SD_FINISHED_STEPPERRELEASE true   // SD 打印结束后禁用步进电机
  #define SD_FINISHED_RELEASECOMMAND "M84"  // 使用 "M84XYE" 保持 Z 轴启用，使热床保持原位

  // 反转 SD 排序，根据卡内 FAT 先显示“较新”的文件。
  // 由于 FAT 会随使用变得乱序，建议使用 SDCARD_SORT_ALPHA。
  #define SDCARD_RATHERRECENTFIRST

  #define SD_MENU_CONFIRM_START             // 打印前确认所选的 SD 文件

  //#define NO_SD_AUTOSTART                 // 彻底移除 auto#.g 文件支持以节省 Flash 和 SRAM
  //#define MENU_ADDAUTOSTART               // 添加运行 auto#.g 文件的菜单选项

  //#define BROWSE_MEDIA_ON_INSERT          // 插入介质时打开文件浏览器

  //#define MEDIA_MENU_AT_TOP               // 强制介质菜单显示在主菜单顶部

  #define EVENT_GCODE_SD_ABORT "G28XY"      // 中止 SD 打印时运行的 G 代码（例如 "G28XY" 或 "G27"）

  #if ENABLED(PRINTER_EVENT_LEDS)
    #define PE_LEDS_COMPLETED_TIME  (30*60) // (seconds) 恢复正常照明前 LED 保持“完成”颜色的时间
  #endif

  /**
   * 断电续打（创想三维）
   *
   * SD 打印期间，在每层开始时将当前状态存储到 SD 卡。
   * 如果开机时找到恢复文件，会在 LCD 屏幕上
   * 显示选项，允许从文件中最后已知的
   * 位置继续打印。
   */
  //#define POWER_LOSS_RECOVERY
  #if ENABLED(POWER_LOSS_RECOVERY)
    #define PLR_ENABLED_DEFAULT   false // 断电续打默认启用。（通过 'M413 Sn' 与 M500 设置）
    //#define BACKUP_POWER_SUPPLY       // 断电时用于移动步进电机的备用电源/UPS
    //#define POWER_LOSS_ZRAISE       2 // (mm) 恢复时 Z 轴抬升量（配合 UPS 断电时）
    //#define POWER_LOSS_PIN         44 // 检测断电的引脚。设为 -1 可在无模块的板卡上禁用默认引脚。
    //#define POWER_LOSS_STATE     HIGH // 表示断电的引脚状态
    //#define POWER_LOSS_PULLUP         // 根据传感器设置上拉/下拉
    //#define POWER_LOSS_PULLDOWN
    //#define POWER_LOSS_PURGE_LEN   20 // (mm) 恢复时挤出的耗材长度
    //#define POWER_LOSS_RETRACT_LEN 10 // (mm) 失败时回抽的耗材长度。需要备用电源。

    // 没有 POWER_LOSS_PIN 时，以下选项有助于减少 SD 卡的磨损，
    // 尤其是在“花瓶模式”打印时。设置过大会导致花瓶无法续打。
    #define POWER_LOSS_MIN_Z_CHANGE 0.05 // (mm) 保存断电数据所需的最小 Z 变化量

    // 如果正确恢复需要 Z 归位则启用。99.9% 的情况下都应禁用此项！
    //#define POWER_LOSS_RECOVER_ZHOME
    #if ENABLED(POWER_LOSS_RECOVER_ZHOME)
      //#define POWER_LOSS_ZHOME_POS { 0, 0 } // 避开热床上物体进行 Z 归位的安全 XY 位置
    #endif
  #endif

  /**
   * 按字母顺序排列 SD 文件列表。
   *
   * 启用此选项后，SD 卡上的条目将按名称排序，
   * 便于浏览。
   *
   * 默认情况下……
   *
   *  - 使用最慢但最安全的排序方法。
   *  - 文件夹排在最前。
   *  - 排序键为静态分配。
   *  - 不额外添加 G 代码 (M34) 支持。
   *  - 排序上限 40 项。（前 40 项之后的条目不排序。）
   *
   * SD 排序使用静态分配（由 SDSORT_LIMIT 设置），
   * 编译器可据此计算最坏情况下的内存占用，
   * 超出 SRAM 限制时将报错。
   *
   *  - SDSORT_USES_RAM 通过静态目录缓冲区实现更快的排序。
   *  - SDSORT_USES_STACK 功能相同，但使用局部栈缓冲区。
   *  - SDSORT_CACHE_NAMES 将排序后的文件列表保留在 RAM 中。（开销很大！）
   *  - SDSORT_DYNAMIC_RAM 仅在 SD 菜单可见时使用 RAM。（谨慎使用！）
   */
  //#define SDCARD_SORT_ALPHA

  // SD 卡排序选项
  #if ENABLED(SDCARD_SORT_ALPHA)
    #define SDSORT_LIMIT       40     // 可排序的最大条目数 (10-256)。每条占用 27 字节。
    #define FOLDER_SORTING     -1     // -1=在上方  0=不排序  1=在下方
    #define SDSORT_GCODE       false  // 允许通过 LCD 和 M34 G 代码开关排序。
    #define SDSORT_USES_RAM    false  // 预分配静态数组以加快预排序。
    #define SDSORT_USES_STACK  false  // 预排序优先使用栈以释放部分 SRAM。（会被后两个选项抵消。）
    #define SDSORT_CACHE_NAMES false  // 将排序结果更久地保留在 RAM 中以提升性能。开销最大的选项。
    #define SDSORT_DYNAMIC_RAM false  // 使用动态分配（仅在 SD 菜单内）。开销最小的选项。使用前必须先设置 SDSORT_LIMIT！
    #define SDSORT_CACHE_VFATS 2      // 用于排序的 13 字节 VFAT 条目最大数量。
                                      // 注意：仅影响启用 SDSORT_CACHE_NAMES（而非 SDSORT_DYNAMIC_RAM）时的 SCROLL_LONG_FILENAMES。
  #endif

  // 允许长文件名中出现国际字符。要正确显示，
  // LCD 的字体必须包含这些字符。请检查所选的 LCD 语言。
  //#define UTF_FILENAME_SUPPORT

  //#define LONG_FILENAME_HOST_SUPPORT    // 通过 'M33 <dosname>' 获取文件/文件夹的长文件名，并用 'M20 L' 列出长文件名
  //#define LONG_FILENAME_WRITE_SUPPORT   // 通过 M28、M30 和二进制传输协议创建/删除长文件名的文件
  //#define M20_TIMESTAMP_SUPPORT         // 在 M20 命令中加入 'T' 标志以包含时间戳

  //#define SCROLL_LONG_FILENAMES         // 在 SD 卡菜单中滚动显示长文件名

  //#define SD_ABORT_NO_COOLDOWN          // 停止打印后保持加热器开启（不推荐！）

  /**
   * 任意限位开关触发时中止 SD 打印。
   * 此功能可通过 'M540 S1' 或 LCD 菜单启用。
   * 必须激活限位开关才能生效。
   */
  //#define SD_ABORT_ON_ENDSTOP_HIT
  #if ENABLED(SD_ABORT_ON_ENDSTOP_HIT)
    //#define SD_ABORT_ON_ENDSTOP_HIT_GCODE "G28XY" // 触发限位开关时运行的 G 代码（例如 "G28XY" 或 "G27"）
  #endif

  //#define SD_REPRINT_LAST_SELECTED_FILE // 打印完成后打开 LCD 菜单并选中同一文件

  //#define AUTO_REPORT_SD_STATUS         // 通过 'M27 S<seconds>' 自动报告介质状态

  /**
   * 支持使用 Arduino USB Host Shield 或等效的
   * MAX3421E 扩展板的 U 盘。U 盘在 Marlin 中
   * 将以 SD 卡的形式呈现。
   *
   * MAX3421E 可以与 SD 读卡器使用相同的引脚，
   * 引脚映射如下：
   *
   *    SCLK, MOSI, MISO --> SCLK, MOSI, MISO
   *    INT              --> SD_DETECT_PIN [1]
   *    SS               --> SDSS
   *
   * [1] 在 AVR 上，具备中断能力的引脚最有利于 UHS3 兼容性。
   */
  //#define USB_FLASH_DRIVE_SUPPORT
  #if ENABLED(USB_FLASH_DRIVE_SUPPORT)
    /**
     * USB 主机库
     *
     * - UHS2 不使用中断，已在搭载 32 位 Archim 板的
     *   LulzBot TAZ Pro 上经过量产验证。
     *
     * - UHS3 代码较新，USB 兼容性更好。但其
     *   测试较少，且已知会干扰舵机。
     *   [1] 这要求 USB_INTR_PIN 具备中断能力。
     */
    //#define USE_UHS2_USB
    //#define USE_UHS3_USB

    #define DISABLE_DUE_SD_MMC // 禁止 USB 主机访问 U 盘，以避免 DUE 平台在块访问时卡死

    /**
     * 部分板卡支持的原生 USB 主机 (USB OTG)
     */
    //#define USE_OTG_USB_HOST

    #if DISABLED(USE_OTG_USB_HOST)
      #define USB_CS_PIN    SDSS
      #define USB_INTR_PIN  SD_DETECT_PIN
    #endif
  #endif

  /**
   * 使用支持 SD 固件刷写的 bootloader 时，
   * 添加一个菜单项，在下次重启时激活 SD 固件更新。
   *
   * 需要 ATMEGA2560 (Arduino Mega)
   *
   * 已在此 bootloader 上测试：
   *   https://github.com/FleetProbe/MicroBridge-Arduino-ATMega2560
   */
  //#define SD_FIRMWARE_UPDATE
  #if ENABLED(SD_FIRMWARE_UPDATE)
    #define SD_FIRMWARE_UPDATE_EEPROM_ADDR    0x1FF
    #define SD_FIRMWARE_UPDATE_ACTIVE_VALUE   0xF0
    #define SD_FIRMWARE_UPDATE_INACTIVE_VALUE 0xFF
  #endif

  /**
   * 如果您有 3K 以上的空闲 flash 空间，请启用此选项。
   * Marlin 会将全部设置以压缩数据的形式嵌入固件二进制文件。
   * 使用 'M503 C' 将设置导出到 SD 卡，生成 'mc.zip'。
   * 有关 'mc-apply.py' 的用法详见 docs/ConfigEmbedding.md。
   */
  //#define CONFIGURATION_EMBEDDING

  // 添加优化的二进制文件传输模式，通过 'M28 B1' 启动
  //#define BINARY_FILE_TRANSFER

  #if ENABLED(BINARY_FILE_TRANSFER)
    // 包含额外功能（如 'M20 F'），支持通过 BINARY_FILE_TRANSFER 上传固件
    //#define CUSTOM_FIRMWARE_UPLOAD
  #endif

  /**
   * 将此选项设置为以下值之一（否则使用板卡默认值）：
   *
   *           LCD - 使用外部 LCD 控制器上的 SD 卡槽。
   *       ONBOARD - 使用控制板上的 SD 卡槽。
   *  CUSTOM_CABLE - 使用自定义线缆访问 SD（在引脚文件中定义）。
   *
   * :[ 'LCD', 'ONBOARD', 'CUSTOM_CABLE' ]
   */
  //#define SDCARD_CONNECTION LCD

  // 如果 SD 检测失效（例如使用 SD 延长线）则启用
  //#define NO_SD_DETECT

  /**
   * 多卷支持 - 实验性。
   * 添加 'M21 Pm' / 'M21 S' / 'M21 U' 以挂载 SD 卡 / U 盘。
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
 * 默认情况下，板载 SD 读卡器可以作为 USB 大容量
 * 存储设备共享。此选项会对主机 PC 隐藏 SD 卡。
 */
//#define NO_SD_HOST_DRIVE   // 禁用通过 USB 访问 SD 卡（出于安全考虑）。

/**
 * 默认情况下共享介质的 I/O 由框架负责。
 * 如果需要 Marlin 自行处理共享介质 I/O，请启用此项。
 * 当某些板卡上共享介质工作不正常时很有用。
 */
#if ENABLED(SDSUPPORT) && DISABLED(NO_SD_HOST_DRIVE)
  //#define DISKIO_HOST_DRIVE
#endif

/**
 * 图形显示器的附加选项
 *
 * 使用这里的优化措施来提升打印性能，
 * 因为图形显示器的绘制可能对性能产生不利影响，
 * 尤其是在执行多个短移动时，以及在 DELTA 和 SCARA
 * 机器上打印时。
 *
 * 其中部分选项可能导致显示滞后于控制器事件，
 * 因为在可靠的打印性能与快速的显示刷新之间
 * 需要权衡取舍。
 */
#if HAS_MARLINUI_U8GLIB
  // 在信息屏上绘制空心边框或不绘制边框，可节省大量时钟周期
  //#define XYZ_NO_FRAME
  #define XYZ_HOLLOW_FRAME

  // 编辑项可使用更大的字体。占用 3120 字节 flash。
  // 仅限西文。不支持西里尔文、假名、土耳其文、希腊文或中文。
  //#define USE_BIG_EDIT_FONT

  // 信息屏可使用更小的字体。占用 2434 字节 flash。
  // 仅限西文。不支持西里尔文、假名、土耳其文、希腊文或中文。
  //#define USE_SMALL_INFOFONT

  /**
   * 图形显示器休眠
   *
   * U8G 库为 SH1106、SSD1306、SSD1309 以及其他一些
   * DOGM 显示器提供了休眠/唤醒函数。
   * 启用此选项可节省电能并防止 OLED 像素烧屏。
   * 会添加菜单项“配置 > LCD 超时 (m)”，可设置 0（禁用）
   * 到 99 分钟的等待时间。
   */
  //#define DISPLAY_SLEEP_MINUTES 2  // (minutes) 关闭屏幕前的超时时间。通过 M255 S 设置。

  /**
   * 基于 ST7920 的 LCD 可以利用 ST7920 字符发生器
   * 模拟 16 x 4 字符显示屏，实现极快的屏幕刷新。
   * 启用 LIGHTWEIGHT_UI 即可使用这种特殊显示模式。
   *
   * 由于 LIGHTWEIGHT_UI 的空间有限，位置和状态
   * 消息会占用同一行。将 STATUS_EXPIRE_SECONDS 设为
   * 状态消息清除前的显示时长。
   *
   * 将 STATUS_EXPIRE_SECONDS 设为 0 表示永不清除状态。
   * 这将导致位置更新不再显示。
   */
  #if IS_U8GLIB_ST7920
    // 启用此选项并减小数值可优化屏幕刷新。
    // 正常延时为 10µs。请使用仍能可靠显示的最低值。
    //#define DOGM_SPI_DELAY_US 5

    //#define LIGHTWEIGHT_UI
    #if ENABLED(LIGHTWEIGHT_UI)
      #define STATUS_EXPIRE_SECONDS 20
    #endif
  #endif

  /**
   * 状态（信息）屏自定义
   * 这些选项可能影响代码大小和屏幕渲染时间。
   * 自定义状态屏可强制覆盖这些设置。
   */
  //#define STATUS_COMBINE_HEATERS    // 使用合并的加热器图标而非分开的图标
  //#define STATUS_HOTEND_NUMBERLESS  // 使用无编号的热端图标（热端数量在 2 个及以上时）
  #define STATUS_HOTEND_INVERTED      // 加热时显示实心喷嘴位图（编号热端需配合 STATUS_HOTEND_ANIM）
  #define STATUS_HOTEND_ANIM          // 使用第二张位图指示热端加热
  #define STATUS_BED_ANIM             // 使用第二张位图指示热床加热
  #define STATUS_CHAMBER_ANIM         // 使用第二张位图指示腔室加热
  //#define STATUS_CUTTER_ANIM        // 使用第二张位图指示主轴/激光激活
  //#define STATUS_COOLER_ANIM        // 使用第二张位图指示激光冷却
  //#define STATUS_FLOWMETER_ANIM     // 使用多张位图指示冷却液流量
  //#define STATUS_ALT_BED_BITMAP     // 使用备选热床位图
  //#define STATUS_ALT_FAN_BITMAP     // 使用备选风扇位图
  //#define STATUS_FAN_FRAMES 3       // :[0,1,2,3,4] 风扇动画帧数
  //#define STATUS_HEAT_PERCENT       // 在进度条中显示加热进度
  //#define BOOT_MARLIN_LOGO_ANIMATED // Marlin 标志动画。占用约 3260（或约 940）字节 flash。

  // 趣味游戏选项
  //#define MARLIN_BRICKOUT
  //#define MARLIN_INVADERS
  //#define MARLIN_SNAKE
  //#define GAMES_EASTER_EGG          // 在“游戏”子菜单上方添加额外空行

#endif // HAS_MARLINUI_U8GLIB

#if HAS_MARLINUI_U8GLIB || IS_DWIN_MARLINUI
  #define MENU_HOLLOW_FRAME           // 启用后在菜单屏上绘制空心边框，可节省大量时钟周期
  //#define OVERLAY_GFX_REVERSE       // 交换图形叠加层中的顺时针/逆时针指示
#endif

//
// DGUS / DWIN 显示屏的附加选项
//
#if HAS_DGUS_LCD
  #define LCD_BAUDRATE 115200

  #define DGUS_RX_BUFFER_SIZE 128
  #define DGUS_TX_BUFFER_SIZE 48
  //#define SERIAL_STATS_RX_BUFFER_OVERRUNS  // 修复 Rx 溢出情况（目前仅适用于 AVR）

  #define DGUS_UPDATE_INTERVAL_MS  500    // (ms) 自动刷新屏幕的间隔

  #if DGUS_UI_IS(FYSETC, MKS, HIPRECY)
    #define DGUS_PRINT_FILENAME           // 打印时显示文件名
    #define DGUS_PREHEAT_UI               // 加热期间显示预热画面

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

    #define DGUS_UI_WAITING               // 在部分画面之间显示“等待”画面
    #if ENABLED(DGUS_UI_WAITING)
      #define DGUS_UI_WAITING_STATUS 10
      #define DGUS_UI_WAITING_STATUS_PERIOD 8 // 增大数值可减慢等待状态的循环速度
    #endif
  #endif
#endif // HAS_DGUS_LCD

//
// AnyCubic Chiron TFT 显示屏的附加选项
//
#if ENABLED(ANYCUBIC_LCD_CHIRON)
  // 默认会自动检测面板类型。
  // 如果您知道面板类型，请启用以下选项之一。
  //#define CHIRON_TFT_STANDARD
  //#define CHIRON_TFT_NEW

  // 启用较长的 Anycubic 开机启动音乐
  //#define AC_DEFAULT_STARTUP_TUNE

  /**
   * 显示文件夹
   * 默认情况下，文件浏览器以平铺列表列出所有 G 代码文件（包括子文件夹中的文件）。
   * 启用此选项可显示分层文件浏览器。
   *
   * 注意：
   * - 不启用此项时，建议同时启用 SDCARD_SORT_ALPHA，使文件排在文件夹之前/之后。
   * - 配合“新”面板使用时，文件夹名称也会追加 '.gcode' 后缀。
   *   目前需要这种变通方式才能让面板显示文件夹。
   */
  #define AC_SD_FOLDER_VIEW
#endif

//
// 指定 UI 的其他语言。默认语言由 LCD_LANGUAGE 指定。
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
  // 所使用的显示板
  //#define LCD_FTDI_VM800B35A        // FTDI 3.5"，配 FT800 (320x240)
  //#define LCD_4DSYSTEMS_4DLCD_FT843 // 4D Systems 4.3" (480x272)
  //#define LCD_HAOYU_FT800CB         // Haoyu，4.3" 或 5" (480x272)
  //#define LCD_HAOYU_FT810CB         // Haoyu，5" (800x480)
  //#define LCD_LULZBOT_CLCD_UI       // LulzBot 彩色 LCD UI
  //#define LCD_FYSETC_TFT81050       // FYSETC，5" (800x480)
  //#define LCD_EVE3_50G              // Matrix Orbital 5.0", 800x480, BT815
  //#define LCD_EVE2_50G              // Matrix Orbital 5.0", 800x480, FT813

  // 如果未使用原装 TFT 面板，请修正分辨率。
  //#define TOUCH_UI_320x240
  //#define TOUCH_UI_480x272
  //#define TOUCH_UI_800x480

  // 带标准 RepRapDiscount 显示接口的板卡的引脚映射
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

    // 如果使用软件 SPI，请指定 SCLK、MOSI、MISO 引脚
    //#define CLCD_USE_SOFT_SPI
    #if ENABLED(CLCD_USE_SOFT_SPI)
      #define CLCD_SOFT_SPI_MOSI 11
      #define CLCD_SOFT_SPI_MISO 12
      #define CLCD_SOFT_SPI_SCLK 13
    #endif
  #endif

  // 显示方向。FT800 支持反转（即上下颠倒）显示。
  // FT810 及更高版本还支持
  // 纵向和镜像方向。
  //#define TOUCH_UI_INVERTED
  //#define TOUCH_UI_PORTRAIT
  //#define TOUCH_UI_MIRRORED

  // UTF8 处理与渲染。
  // 不支持的字符将显示为 '?'。
  //#define TOUCH_UI_USE_UTF8
  #if ENABLED(TOUCH_UI_USE_UTF8)
    // 西文重音符号支持。这些带重音的字符使用
    // 组合位图，所需存储空间相对较小。
    #define TOUCH_UI_UTF8_WESTERN_CHARSET
    #if ENABLED(TOUCH_UI_UTF8_WESTERN_CHARSET)
      // 额外字符组。这些字符需要
      // 完整位图，占用相当多的存储空间：
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

    // 西里尔字符集，占用约 27KiB flash
    //#define TOUCH_UI_UTF8_CYRILLIC_CHARSET
  #endif

  // 当标签放不进按钮时使用较小字体
  #define TOUCH_UI_FIT_TEXT

  // “屏幕锁定”键盘使用数字密码。
  // （建议在小屏幕上使用）
  //#define TOUCH_UI_PASSCODE

  // 为触摸 UI 事件输出额外调试信息
  //#define TOUCH_UI_DEBUG

  // 开发者菜单（触摸“关于打印机”的版权文字进入）
  //#define TOUCH_UI_DEVELOPER_MENU
#endif

//
// 经典 UI 选项
//
#if TFT_SCALED_DOGLCD
  //#define TFT_MARLINUI_COLOR 0xFFFF // 白色
  //#define TFT_MARLINBG_COLOR 0x0000 // 黑色
  //#define TFT_DISABLED_COLOR 0x0003 // 近黑色
  //#define TFT_BTCANCEL_COLOR 0xF800 // 红色
  //#define TFT_BTARROWS_COLOR 0xDEE6 // 11011 110111 00110 黄色
  //#define TFT_BTOKMENU_COLOR 0x145F // 00010 100010 11111 青色
#endif

//
// ADC 按键消抖
//
#if HAS_ADC_BUTTONS
  #define ADC_BUTTON_DEBOUNCE_DELAY 16  // 如果按键抖动或重复过快可增大此值
#endif

// @section safety

/**
 * 如果固件过载到无法读取温度传感器的程度，
 * 看门狗硬件定时器将执行复位并禁用所有输出。
 *
 * 如果发现看门狗重启导致您的 AVR 板卡永久卡死，
 * 请启用 WATCHDOG_RESET_MANUAL，改用自定义定时器而非 WDTO。
 * 注意：这种方式可靠性较低，因为它只能在
 * 中断启用期间捕获卡死。
 */
#define USE_WATCHDOG
#if ENABLED(USE_WATCHDOG)
  //#define WATCHDOG_RESET_MANUAL
#endif

// @section lcd

/**
 * 微步调整（Babystepping）允许在不改变当前位置数值的情况下
 * 以极小步进移动各轴。此功能主要用于在打印第一层时
 * 实时调整 Z 轴。
 *
 * 警告：不遵守限位开关！
 */
//#define BABYSTEPPING
#if ENABLED(BABYSTEPPING)
  //#define INTEGRATED_BABYSTEPPING         // 将微步调整集成进步进电机 ISR 的实验性功能
  //#define BABYSTEP_WITHOUT_HOMING
  //#define BABYSTEP_ALWAYS_AVAILABLE       // 允许随时进行微步调整（不仅限于运动期间）。
  //#define BABYSTEP_XY                     // 同时启用 X/Y 轴微步调整。DELTA 不支持！
  #define BABYSTEP_INVERT_Z false           // 如果 Z 轴微步调整方向应相反则更改此项
  //#define BABYSTEP_MILLIMETER_UNITS       // 以 mm 而非微步为单位指定 BABYSTEP_MULTIPLICATOR_(XY|Z)
  #define BABYSTEP_MULTIPLICATOR_Z  1       // (steps or mm) 每次 Z 轴微步调整的步数或毫米距离
  #define BABYSTEP_MULTIPLICATOR_XY 1       // (steps or mm) 每次 XY 轴微步调整的步数或毫米距离

  //#define DOUBLECLICK_FOR_Z_BABYSTEPPING  // 在状态屏上双击进行 Z 轴微步调整。
  #if ENABLED(DOUBLECLICK_FOR_Z_BABYSTEPPING)
    #define DOUBLECLICK_MAX_INTERVAL 1250   // 两次点击之间的最大间隔（毫秒）。
                                            // 注意：可能会额外增加时间以缓解控制器延迟。
    //#define MOVE_Z_WHEN_IDLE              // 打印机空闲时双击跳转到移动 Z 菜单。
    #if ENABLED(MOVE_Z_WHEN_IDLE)
      #define MOVE_Z_IDLE_MULTIPLICATOR 1   // 将 1mm 乘以此系数作为移动步长。
    #endif
  #endif

  //#define BABYSTEP_DISPLAY_TOTAL          // 显示自上次 G28 以来的微步总数

  //#define BABYSTEP_ZPROBE_OFFSET          // 将 M851 Z 与微步调整合并
  //#define BABYSTEP_GLOBAL_Z               // 将 M424 Z 与微步调整合并

  #if EITHER(BABYSTEP_ZPROBE_OFFSET, BABYSTEP_GLOBAL_Z)
    #if ENABLED(BABYSTEP_ZPROBE_OFFSET)
      //#define BABYSTEP_HOTEND_Z_OFFSET    // 针对多个热端，微调相对 Z 偏移
    #endif
    //#define BABYSTEP_GFX_OVERLAY          // 在 Z 偏移编辑器上启用图形叠加显示
  #endif
#endif

// @section extruder

/**
 * 线性压力控制 v1.5
 *
 * 假设：advance [步数] = k * (速度增量 [步/秒])
 * K=0 表示禁用 advance。
 *
 * 注意：LIN_ADVANCE 1.5 的 K 值与早期版本不同！
 *
 * 对于 3mm PLA 直驱挤出（驱动齿轮与热break之间距离约 6.5cm），K 可设为 0.22 左右。
 * 柔性耗材或更长距离时需要更大的 K 值。
 * 如果该算法产生的速度偏移超出挤出机的承受能力（与 E jerk 相比），
 * 受影响的移动过程中会降低打印加速度，以保持在限值之内。
 *
 * 完整说明请见 https://marlinfw.org/docs/features/lin_advance.html
 */
//#define LIN_ADVANCE
#if ENABLED(LIN_ADVANCE)
  #if ENABLED(DISTINCT_E_FACTORS)
    #define ADVANCE_K { 0.22 }    // (mm) 每个挤出机在 1mm/s 挤出速度下的压缩长度
  #else
    #define ADVANCE_K 0.22        // (mm) 适用于所有挤出机的压缩长度
  #endif
  //#define ADVANCE_K_EXTRA       // 增加第二个线性前进常数，可通过 M900 L 配置。
  //#define LA_DEBUG              // 运行期间通过串口打印调试信息。正式使用时应禁用。
  //#define ALLOW_LOW_EJERK       // 允许 DEFAULT_EJERK 值小于 10。推荐直驱热端使用。
  //#define EXPERIMENTAL_I2S_LA   // 允许 I2S_STEPPER_STREAM 与 LA 一起使用。当 LA 步进速率达到约 20kHz 时性能会下降。
#endif

// @section leveling

/**
 * 使用安全调平坐标，在热床探测前将各轴移动到合适的位置。
 * 例如，旋转轴归位后 Z 探针可能不再垂直于热床。
 * 请选择能使热床处于水平、Z 探针处于垂直的坐标值。
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
 * 如果自动选择的点不合适，可在此覆盖。
 */
#if NEEDS_THREE_PROBE_POINTS
  //#define PROBE_PT_1 {  15, 180 }   // (mm) { x, y }
  //#define PROBE_PT_2 {  15,  20 }
  //#define PROBE_PT_3 { 170,  20 }
#endif

/**
 * 探测边距
 *
 * 为打印平台的每一边单独覆盖 PROBING_MARGIN。
 * 可用于将探测点精确对准目标位置，或让调平
 * 仅在热床的特定边上避开平台夹具。
 * 启用 NOZZLE_AS_PROBE 时允许负值，
 * 以便在热床范围之外探测。
 *
 * 如果你打算替换先前的 *_PROBE_BED_POSITION 选项，
 * 大多数情况下 LEFT 和 FRONT 的值可直接沿用，
 * 而 RIGHT 和 REAR 应取其反值，例如
 * (X/Y_BED_SIZE - RIGHT/BACK_PROBE_BED_POSITION)
 *
 * 这样在编译时所有位置都能匹配，但如果探测位置
 * 之后通过 M851XY 被修改，
 * 探测点也会随之移动。这可防止任何改动
 * 导致探针无法到达某些点。
 */
#if PROBE_SELECTED && !IS_KINEMATIC
  //#define PROBING_MARGIN_LEFT PROBING_MARGIN
  //#define PROBING_MARGIN_RIGHT PROBING_MARGIN
  //#define PROBING_MARGIN_FRONT PROBING_MARGIN
  //#define PROBING_MARGIN_BACK PROBING_MARGIN
#endif

#if EITHER(MESH_BED_LEVELING, AUTO_BED_LEVELING_UBL)
  // 如果自动（最大）网格区域过大，可在此覆盖网格区域
  //#define MESH_MIN_X MESH_INSET
  //#define MESH_MIN_Y MESH_INSET
  //#define MESH_MAX_X X_BED_SIZE - (MESH_INSET)
  //#define MESH_MAX_Y Y_BED_SIZE - (MESH_INSET)
#endif

#if BOTH(AUTO_BED_LEVELING_UBL, EEPROM_SETTINGS)
  //#define OPTIMIZED_MESH_STORAGE  // 以较低精度存储网格以节省 EEPROM 空间
#endif

/**
 * 反复尝试 G29 调平直到成功。
 * 在 G29_MAX_RETRIES 次尝试后停止。
 */
//#define G29_RETRY_AND_RECOVER
#if ENABLED(G29_RETRY_AND_RECOVER)
  #define G29_MAX_RETRIES 3
  #define G29_HALT_ON_FAILURE
  /**
   * 指定调平成功时、每次尝试之间、以及达到最大重试次数后
   * 将要执行的 GCODE 命令。
   */
  #define G29_SUCCESS_COMMANDS "M117 Bed leveling done."
  #define G29_RECOVER_COMMANDS "M117 Probe failed. Rewiping.\nG28\nG12 P0 S12 T0"
  #define G29_FAILURE_COMMANDS "M117 Bed leveling failed.\nG0 Z10\nM300 P25 S880\nM300 P50 S0\nM300 P25 S880\nM300 P50 S0\nM300 P25 S880\nM300 P50 S0\nG4 S1"

#endif

/**
 * 探针温度补偿
 *
 * 调整探针测量值，以补偿探针、热床和/或热端温度
 * 引起的形变。
 * 使用 G76 针对探针和热床温度自动校准此功能。
 * （挤出机温度/偏移值必须手动校准。）
 * 使用 M871 手动设置温度/偏移值。
 * 更多细节请见 https://marlinfw.org/docs/features/probe_temp_compensation.html
 */
//#define PTC_PROBE    // 基于探针温度进行补偿
//#define PTC_BED      // 基于热床温度进行补偿
//#define PTC_HOTEND   // 基于热端温度进行补偿

#if ANY(PTC_PROBE, PTC_BED, PTC_HOTEND)
  /**
   * 如果探针温度超出定义范围，则使用最近的数据点与索引为
   * PTC_LINEAR_EXTRAPOLATION 的点做线性外推。例如设为 4 时，
   * 低于 PTC_PROBE_START 的值将在 data[0] 和 data[4] 之间做线性外推。
   */
  //#define PTC_LINEAR_EXTRAPOLATION 4

  #if ENABLED(PTC_PROBE)
    // 探针温度校准会生成一个数据表，从 PTC_PROBE_START
    // （例如 30）开始，以 PTC_PROBE_RES（例如 5）为步长，
    // 共 PTC_PROBE_COUNT（例如 10）个采样点。
    #define PTC_PROBE_START   30    // (°C)
    #define PTC_PROBE_RES      5    // (°C)
    #define PTC_PROBE_COUNT   10
    #define PTC_PROBE_ZOFFS   { 0 } // (µm) 每个采样点的 Z 调整量
  #endif

  #if ENABLED(PTC_BED)
    // 热床温度校准会构建类似的数据表。
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
    // 等待探针冷却的停靠位置
    #define PTC_PARK_POS   { 0, 0, 100 }

    // 探测位置：在此探测并等待探针达到目标温度
    //#define PTC_PROBE_POS  { 12.0f, 7.3f } // 示例：MK52 磁性热床
    #define PTC_PROBE_POS  { 90, 100 }

    // 热床温度校准期间测量时探针应处的温度。
    #define PTC_PROBE_TEMP    30  // (°C)

    // 喷嘴抬升到 Z=0.0 以上的高度。调低此值有助于探针更快升温。
    // 注意：Z=0.0 偏移由探针 Z 偏移决定（例如通过 M851 Z 设置）。
    #define PTC_PROBE_HEATING_OFFSET 0.5
  #endif
#endif // PTC_PROBE || PTC_BED || PTC_HOTEND

// @section extras

//
// G60/G61 位置保存与返回
//
//#define SAVED_POSITIONS 1         // 每个保存位置槽位占用 12 字节

//
// G2/G3 圆弧支持
//
#define ARC_SUPPORT                   // 需要约 3226 字节
#if ENABLED(ARC_SUPPORT)
  #define MIN_ARC_SEGMENT_MM      0.1 // (mm) 每段圆弧的最小长度
  #define MAX_ARC_SEGMENT_MM      1.0 // (mm) 每段圆弧的最大长度
  #define MIN_CIRCLE_SEGMENTS    72   // 完整圆的最小段数
  //#define ARC_SEGMENTS_PER_SEC 50   // 根据进给速度选择分段长度
  #define N_ARC_CORRECTION       25   // 两次修正之间插值段的数量
  //#define ARC_P_CIRCLES             // 启用 'P' 参数以指定完整圆
  //#define SF_ARC_FIX                // 仅在使用 SkeinForge 的 "Arc Point" 圆角处理时启用
#endif

// G5 贝塞尔曲线支持，使用 XYZE 终点和 IJPQ 偏移
//#define BEZIER_CURVE_SUPPORT        // 需要约 2666 字节

#if EITHER(ARC_SUPPORT, BEZIER_CURVE_SUPPORT)
  //#define CNC_WORKSPACE_PLANES      // 允许 G2/G3/G5 在 XY、ZX 或 YZ 平面内工作
#endif

/**
 * 直接步进
 *
 * 与 Klipper 使用的方案类似，G6 直接步进通过预先计算所有运动，
 * 显著减少运动计算量、提高最高打印速度，
 * 并减少步进混叠现象。
 * 准备你的 G 代码：https://github.com/colinrgodsey/step-daemon
 */
//#define DIRECT_STEPPING

/**
 * G38 探测目标
 *
 * 此选项添加 G38.2 和 G38.3（朝目标探测），
 * 以及可选的 G38.4 和 G38.5（远离目标探测）。
 * 设置 MULTIPLE_PROBING 可让 G38 多次探测。
 */
//#define G38_PROBE_TARGET
#if ENABLED(G38_PROBE_TARGET)
  //#define G38_PROBE_AWAY        // 包含 G38.4 和 G38.5，用于远离目标探测
  #define G38_MINIMUM_MOVE 0.0275 // (mm) 会产生移动的最小距离。
#endif

// 步数少于该值的移动（或分段）将与下一个移动合并
#define MIN_STEPS_PER_SEGMENT 1

/**
 * 设置步进电机 DIR 信号前后的最小延时（单位 ns）
 *     0 : 无延时（至少应间隔 10µS，即至少经历一次步进电机 ISR）
 *    20 : TMC2xxx 驱动的最小值
 *   200 : A4988 驱动的最小值
 *   400 : A5984 驱动的最小值
 *   500 : LV8729 驱动的最小值（推测，数据手册中无相关信息）
 *   650 : DRV8825 驱动的最小值
 *  1500 : TB6600 驱动的最小值（推测，数据手册中无相关信息）
 * 15000 : TB6560 驱动的最小值（推测，数据手册中无相关信息）
 *
 * 根据 Configuration.h 中设置的驱动类型覆盖默认值。
 */
//#define MINIMUM_STEPPER_POST_DIR_DELAY 650
//#define MINIMUM_STEPPER_PRE_DIR_DELAY 650

/**
 * 步进电机驱动最小脉冲宽度（单位 µs）
 *   0 : MCU 能产生的最小宽度，与 TMC2xxx 驱动兼容
 *   0 : LV8729 最小 500ns，在 stepper.h 中调整
 *   1 : A4988 和 A5984 步进电机驱动的最小值
 *   2 : DRV8825 步进电机驱动的最小值
 *   3 : TB6600 步进电机驱动的最小值
 *  30 : TB6560 步进电机驱动的最小值
 *
 * 根据 Configuration.h 中设置的驱动类型覆盖默认值。
 */
//#define MINIMUM_STEPPER_PULSE 2

/**
 * 步进电机驱动允许的最大步进速率（单位 Hz）
 *  若未定义，默认为 1MHz / (2 * MINIMUM_STEPPER_PULSE)
 *  5000000 : TMC2xxx 步进电机驱动的最大值
 *  1000000 : LV8729 步进电机驱动的最大值
 *  500000  : A4988 步进电机驱动的最大值
 *  250000  : DRV8825 步进电机驱动的最大值
 *  150000  : TB6600 步进电机驱动的最大值
 *   15000  : TB6560 步进电机驱动的最大值
 *
 * 根据 Configuration.h 中设置的驱动类型覆盖默认值。
 */
//#define MAXIMUM_STEPPER_RATE 250000

// @section temperature

// 并行控制 0 号和 1 号加热器。
//#define HEATERS_PARALLEL

//===========================================================================
//================================= 缓冲区 ==================================
//===========================================================================

// @section motion

// 规划器中可同时容纳的直线移动数量。
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
// 若要节省 386 字节 flash（以及 TX_BUFFER_SIZE+3 字节 RAM），可设为 0。
// 缓冲一个简单的 "ok" 需要 4 字节。
// 对于 ADVANCED_OK (M105) 需要 32 字节。
// 对于调试回显：128 字节可获得最佳速度。
// 其他输出不需要这么快。
// :[0, 2, 4, 8, 16, 32, 64, 128, 256]
#define TX_BUFFER_SIZE 0

// 主机接收缓冲区大小
// 在没有 XON/XOFF 流控的情况下（见下方 SERIAL_XON_XOFF），32 字节应该足够。
// 若要使用流控，请将此缓冲区大小设为至少 1024 字节。
// :[0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048]
//#define RX_BUFFER_SIZE 1024

#if RX_BUFFER_SIZE >= 1024
  // 启用后，控制器会向主机发送 XON/XOFF 控制字符，
  // 以提示 RX 缓冲区即将占满。
  //#define SERIAL_XON_XOFF
#endif

#if ENABLED(SDSUPPORT)
  // 启用此选项可在向 SD 卡传输文件后收集并显示
  // RX 队列的最大使用量。
  //#define SERIAL_STATS_MAX_RX_QUEUED

  // 启用此选项可在向 SD 卡传输文件后收集并显示
  // 丢失的字节数。
  //#define SERIAL_STATS_DROPPED_RX
#endif

// 监视 RX 缓冲区使用情况
// 当串口接收缓冲区溢出时，向串口输出错误信息。
// 如果看到此类错误，请增大 RX_BUFFER_SIZE 的值。
// 并非所有平台都支持。
//#define RX_BUFFER_MONITOR

/**
 * 紧急命令解析器
 *
 * 添加一个底层解析器，在特定命令进入串口接收缓冲区时
 * 立即拦截，使其不会被阻塞。
 * 目前处理 M108、M112、M410、M876
 * 注意：尚未在所有平台上实现。
 */
//#define EMERGENCY_PARSER

/**
 * 实时报告（需要 EMERGENCY_PARSER）
 *
 * - 报告机器的位置和状态（类似 Grbl）。
 * - 在长距离移动期间自动报告位置。
 * - 对 CNC/激光有用。
 *
 * 增加以下命令支持：
 *  S000 : 移动时报告状态和位置。
 *  P000 : 移动时立即暂停 / 保持。
 *  R000 : 从暂停 / 保持中恢复。
 *
 * - 保持期间所有紧急解析器命令照常可用。
 * - 启用 NANODLP_Z_SYNC 和 NANODLP_ALL_AXIS 以在移动命令结束时报告状态。
 */
//#define REALTIME_REPORTING_COMMANDS
#if ENABLED(REALTIME_REPORTING_COMMANDS)
  //#define FULL_REPORT_TO_HOST_FEATURE   // 像 Grbl CNC 一样自动向主机报告机器状态
#endif

// 串口连接不良时可能丢失已接收的命令并发送 'ok'
// 因此有些上位机软件会在 30 秒后超时中止。
// 另一些上位机软件在收到 'wait' 时开始发送命令。
// 这个 "wait" 只在缓冲区为空时发送。此处 1 秒是不错的取值。
//#define NO_TIMEOUTS 1000 // 毫秒

// 一些上位机软件很快会支持相应功能，届时 NO_TIMEOUTS 可能不再必要。
//#define ADVANCED_OK

// Printrun 在一次性接收长字符串时可能出问题。
// 此选项在串口输出的各行之间插入短暂延时。
#define SERIAL_OVERRUN_PROTECTION

// 串口回显时小数点后的位数
//#define SERIAL_FLOAT_PRECISION 4

/**
 * 设置填满一个典型字符空间所需的比例字体空格数。
 * 这有助于更好地对齐 `G29 O` 网格输出等命令的结果。
 *
 * 对于使用等宽字体的上位机软件（如 OctoPrint），保持 1.0 即可。
 * 否则，请根据你的上位机软件和字体进行调整。
 */
#define PROPORTIONAL_FONT_RATIO 1.0

// @section extras

/**
 * 附加风扇转速
 * 为每个打印冷却风扇增加一个第二转速。
 *   'M106 P<fan> T3-255' : 为 <fan> 设置第二转速
 *   'M106 P<fan> T2'     : 使用已设置的第二转速
 *   'M106 P<fan> T1'     : 恢复之前的风扇转速
 */
//#define EXTRA_FAN_SPEED

/**
 * 基于固件的、LCD 控制的回抽
 *
 * 添加 G10 / G11 命令，实现基于固件的自动回抽 / 回补。
 * 使用 M207 和 M208 定义回抽 / 回补参数。
 *
 * 使用 M209 启用或禁用自动回抽。
 * 启用自动回抽后，设定范围内所有 G1 E 移动
 * 都会被转换为基于固件的回抽/回补移动。
 *
 * 更换耗材期间务必关闭自动回抽。
 *
 * 注意 M207 / M208 / M209 的设置会保存到 EEPROM。
 */
//#define FWRETRACT
#if ENABLED(FWRETRACT)
  #define FWRETRACT_AUTORETRACT             // 覆盖切片软件的回抽设置
  #if ENABLED(FWRETRACT_AUTORETRACT)
    #define MIN_AUTORETRACT             0.1 // (mm) 不转换短于此长度的 E 移动
    #define MAX_AUTORETRACT            10.0 // (mm) 不转换长于此长度的 E 移动
  #endif
  #define RETRACT_LENGTH                3   // (mm) 默认回抽长度（正值）
  #define RETRACT_LENGTH_SWAP          13   // (mm) 默认换料回抽长度（正值）
  #define RETRACT_FEEDRATE             45   // (mm/s) 默认回抽进给速度
  #define RETRACT_ZRAISE                0   // (mm) 默认回抽时 Z 轴抬升量
  #define RETRACT_RECOVER_LENGTH        0   // (mm) 默认附加回补长度（回补时加到回抽长度上）
  #define RETRACT_RECOVER_LENGTH_SWAP   0   // (mm) 默认附加换料回补长度（换料后回补时加到回抽长度上）
  #define RETRACT_RECOVER_FEEDRATE      8   // (mm/s) 默认回补进给速度
  #define RETRACT_RECOVER_FEEDRATE_SWAP 8   // (mm/s) 默认换料回补进给速度
  #if ENABLED(MIXING_EXTRUDER)
    //#define RETRACT_SYNC_MIXING           // 同时回抽并恢复所有混色步进电机
  #endif
#endif

/**
 * 通用换头设置。
 * 适用于所有类型的挤出机，除非有明确说明。
 */
#if HAS_MULTI_EXTRUDER
  // 换头时的 Z 轴抬升距离，某些挤出机需要
  #define TOOLCHANGE_ZRAISE                 2 // (mm)
  //#define TOOLCHANGE_ZRAISE_BEFORE_RETRACT  // 在换料回抽（如启用）之前先抬升
  //#define TOOLCHANGE_NO_RETURN              // 换头后绝不返回之前的位置
  #if ENABLED(TOOLCHANGE_NO_RETURN)
    //#define EVENT_GCODE_AFTER_TOOLCHANGE "G12X"   // 换头后执行的附加 G 代码
  #endif

  /**
   * 执行换头命令时运行的附加 G 代码。可用于驱动额外的
   * 步进电机（例如 Configuration.h 中的 I 轴）来驱动换头装置。
   */
  //#define EVENT_GCODE_TOOLCHANGE_T0 "G28 A\nG1 A0"  // 执行换头命令 T0 时运行的附加 G 代码
  //#define EVENT_GCODE_TOOLCHANGE_T1 "G1 A10"        // 执行换头命令 T1 时运行的附加 G 代码
  //#define EVENT_GCODE_TOOLCHANGE_ALWAYS_RUN         // 总是执行上述 G 代码序列。请谨慎使用！

  /**
   * 将 EVENT_GCODE_TOOLCHANGE_Tx 的坐标视为相对于 T0，
   * 使指定轴上的移动对所有工具保持一致。
   */
  //#define TC_GCODE_USE_GLOBAL_X   // 使用相对于工具 0 的 X 位置
  //#define TC_GCODE_USE_GLOBAL_Y   // 使用相对于工具 0 的 Y 位置
  //#define TC_GCODE_USE_GLOBAL_Z   // 使用相对于工具 0 的 Z 位置

  /**
   * 工具传感器用于检测工具是否已被拾取或放下。
   * 需要定义 TOOL_SENSOR1_PIN、TOOL_SENSOR2_PIN 等引脚。
   */
  //#define TOOL_SENSOR

  /**
   * 换头时回抽并预挤出耗材，以减少
   * 渗漏和拉丝，使切换更干净。
   */
  //#define TOOLCHANGE_FILAMENT_SWAP
  #if ENABLED(TOOLCHANGE_FILAMENT_SWAP)
    // 装载 / 卸载
    #define TOOLCHANGE_FS_LENGTH              12  // (mm) 装载 / 卸载长度
    #define TOOLCHANGE_FS_EXTRA_RESUME_LENGTH  0  // (mm) 便于更好恢复打印的附加长度。可通过 LCD 或 M217 B 调整。
    #define TOOLCHANGE_FS_RETRACT_SPEED   (50*60) // (mm/min) （卸载）
    #define TOOLCHANGE_FS_UNRETRACT_SPEED (25*60) // (mm/min) （SINGLENOZZLE 或 Bowden 挤出机装载时需放慢）

    // 加长预挤以清理 SINGLENOZZLE
    #define TOOLCHANGE_FS_EXTRA_PRIME          0  // (mm) 附加预挤长度
    #define TOOLCHANGE_FS_PRIME_SPEED    (4.6*60) // (mm/min) 附加预挤进给速度
    #define TOOLCHANGE_FS_WIPE_RETRACT         0  // (mm) 从停靠位置额外回抽，可减少拉丝、改善擦拭等。可通过 LCD 或 M217 G 调整。

    // 预挤后冷却以减少拉丝
    #define TOOLCHANGE_FS_FAN                 -1  // 风扇编号，或 -1 表示跳过
    #define TOOLCHANGE_FS_FAN_SPEED          255  // 0-255
    #define TOOLCHANGE_FS_FAN_TIME            10  // (seconds)

    // 每个挤出机首次预挤时使用 TOOLCHANGE_FS_PRIME_SPEED 进给速度
    //#define TOOLCHANGE_FS_SLOW_FIRST_PRIME

    /**
     * 首次发送 T0 到打印机时预挤 T0：
     *  [ 上电 -> T0 { 激活并预挤 T0 } -> T1 { 回抽 T0，激活并预挤 T1 } ]
     * 若禁用，则从其他挤出机切回 T0 之前不会预挤：
     *  [ 上电 -> T0 { 激活 T0 } -> T1 { 激活并预挤 T1 } -> T0 { 回抽 T1，激活并预挤 T0 } ]
     * 打印前用 M217 V1 启用，以避免主机连接时产生不必要的预挤。
     */
    //#define TOOLCHANGE_FS_PRIME_FIRST_USED

    /**
     * 换头迁移
     * 此功能提供 G 代码和 LCD 选项，可在打印中途切换工具。
     * 所有适用的工具属性都会被迁移，以便打印继续进行。
     * 工具必须高度匹配，且可能存在其他限制。
     * 适用于：
     *   - 不中断地更换耗材颜色
     *   - 耗材耗尽时自动切换料卷
     *   - 挤出机堵塞时更换不同喷嘴
     */
    #define TOOLCHANGE_MIGRATION_FEATURE

  #endif

  /**
   * 换头期间机头的停靠位置。
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
 * 高级暂停（用于换料）
 *  - 添加 G 代码 M600 换料，用于发起换料。
 *  - 默认的 FILAMENT_RUNOUT_SCRIPT 需要此功能。
 *
 * 前提条件：
 *  - 要在换料时停靠，请启用并配置 NOZZLE_PARK_FEATURE。
 *  - 要与用户交互，请启用 LCD 显示屏、HOST_PROMPT_SUPPORT 或 EMERGENCY_PARSER。
 *
 * 启用 PARK_HEAD_ON_PAUSE 可添加 G 代码 M125 暂停并停靠。
 */
//#define ADVANCED_PAUSE_FEATURE
#if ENABLED(ADVANCED_PAUSE_FEATURE)
  #define PAUSE_PARK_RETRACT_FEEDRATE         60  // (mm/s) 初始回抽进给速度。
  #define PAUSE_PARK_RETRACT_LENGTH            2  // (mm) 初始回抽。
                                                  // 这段短回抽会在停靠喷嘴之前立即执行。
  #define FILAMENT_CHANGE_UNLOAD_FEEDRATE     10  // (mm/s) 卸载耗材进给速度。可以相当快。
  #define FILAMENT_CHANGE_UNLOAD_ACCEL        25  // (mm/s^2) 降低加速度可允许更快的进给速度。
  #define FILAMENT_CHANGE_UNLOAD_LENGTH      100  // (mm) 完整卸载所需的耗材长度。
                                                  //   Bowden 挤出机：料管与喷嘴的全长。
                                                  //   直驱挤出机：喷嘴的全长。
                                                  //   设为 0 表示手动卸载。
  #define FILAMENT_CHANGE_SLOW_LOAD_FEEDRATE   6  // (mm/s) 开始装载时的慢速移动。
  #define FILAMENT_CHANGE_SLOW_LOAD_LENGTH     0  // (mm) 慢速装载长度，留出插入耗材的时间。
                                                  // 设为 0 表示禁用起始装载，直接跳到快速装载
  #define FILAMENT_CHANGE_FAST_LOAD_FEEDRATE   6  // (mm/s) 装载耗材进给速度。可以相当快。
  #define FILAMENT_CHANGE_FAST_LOAD_ACCEL     25  // (mm/s^2) 降低加速度可允许更快的进给速度。
  #define FILAMENT_CHANGE_FAST_LOAD_LENGTH     0  // (mm) 耗材装载长度，从挤出机齿轮到喷嘴。
                                                  //   Bowden 挤出机：料管与喷嘴的全长。
                                                  //   直驱挤出机：喷嘴的全长。
  //#define ADVANCED_PAUSE_CONTINUOUS_PURGE       // 持续挤出到冲挤长度为止，直到被中断。
  #define ADVANCED_PAUSE_PURGE_FEEDRATE        3  // (mm/s) 挤出进给速度（装载后）。应慢于装载进给速度。
  #define ADVANCED_PAUSE_PURGE_LENGTH         50  // (mm) 装载后的挤出长度。
                                                  //   设为 0 表示手动挤出。
                                                  //   可从换料菜单反复挤出耗材，
                                                  //   直到挤出稳定，并冲净旧耗材。
  #define ADVANCED_PAUSE_RESUME_PRIME          0  // (mm) 从停靠位置返回后预挤喷嘴的附加距离。
  //#define ADVANCED_PAUSE_FANS_PAUSE             // 机器暂停期间关闭打印冷却风扇。

                                                  // 卸载耗材会先执行回抽、延时和冲挤：
  #define FILAMENT_UNLOAD_PURGE_RETRACT       13  // (mm) 卸载初始回抽长度。
  #define FILAMENT_UNLOAD_PURGE_DELAY       5000  // (ms) 回抽后等待耗材冷却的延时。
  #define FILAMENT_UNLOAD_PURGE_LENGTH         8  // (mm) 先做一次回补，然后冲挤出此长度。
  #define FILAMENT_UNLOAD_PURGE_FEEDRATE      25  // (mm/s) 卸载前的冲挤进给速度

  #define PAUSE_PARK_NOZZLE_TIMEOUT           45  // (seconds) 出于安全在喷嘴关闭前的时限。
  #define FILAMENT_CHANGE_ALERT_BEEPS         10  // 需要用户响应时播放的警示蜂鸣次数。
  #define PAUSE_PARK_NO_STEPPER_TIMEOUT           // 启用后换料期间 XYZ 步进电机保持通电。
  //#define FILAMENT_CHANGE_RESUME_ON_INSERT      // 当耗材检测传感器再次触发时自动继续 / 装载耗材。
  //#define PAUSE_REHEAT_FAST_RESUME              // 超时后不再重新提示，减少等待次数。

  //#define PARK_HEAD_ON_PAUSE                    // 暂停和换料期间停靠喷嘴。
  //#define HOME_BEFORE_FILAMENT_CHANGE           // 如有需要，换料停靠前先归位

  //#define FILAMENT_LOAD_UNLOAD_GCODES           // 添加 M701/M702 装载/卸载 G 代码，并在 LCD 准备菜单中添加装载/卸载项。
  //#define FILAMENT_UNLOAD_ALL_EXTRUDERS         // 允许 M702 在高于最低目标温度（由 M302 设置）时卸载所有挤出机
#endif

// @section tmc_smart

/**
 * Trinamic 智能驱动
 *
 * 要在 SPI 模式下使用 TMC2130、TMC2160、TMC2660、TMC5130、TMC5160 步进电机驱动：
 *  - 将 SPI 引脚连接到板载硬件 SPI 接口。
 *    有些开发板只需简单的跳线连接！请查阅你的开发板文档。
 *  - 在你的 `pins_MYBOARD.h` 文件中定义所需的步进电机 CS 引脚。
 *    （例如可参考 RAMPS 的引脚定义。）
 *  - 也可以用 GPIO 引脚使用软件 SPI 代替硬件 SPI。
 *
 * 要在串口 UART 模式下使用 TMC220x 步进电机驱动：
 *  - 将 PDN_UART 通过 1K 电阻连接到 #_SERIAL_TX_PIN。
 *    若要具备读取能力，还需将 PDN_UART 不经电阻连接到 #_SERIAL_RX_PIN。
 *    有些开发板只需简单的跳线连接！请查阅你的开发板文档。
 *  - 这些驱动也可以使用硬件串口。
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

  #define HOLD_MULTIPLIER    0.5  // 将保持电流相对运行电流按比例缩小

  /**
   * 将微步插值到 256
   * 可通过下方的 <driver>_INTERPOLATE 设置为每个驱动单独覆盖
   */
  #define INTERPOLATE      true

  #if AXIS_IS_TMC_CONFIG(X)
    #define X_CURRENT       800        // (mA) RMS 电流。乘以 1.414 得到峰值电流。
    #define X_CURRENT_HOME  1000  // (mA) 无传感器归位时的 RMS 电流
    #define X_MICROSTEPS     64        // 0..256
    #define X_RSENSE          0.11     // TMC26X 需乘以 1000
    #define X_CHAIN_POS      -1        // -1..0: 不串联。1: MCU MOSI 已连接。2: 链中的下一个，……
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
    #define Y_CURRENT_HOME  1500
    #define Y_MICROSTEPS     64
    #define Y_RSENSE          0.11
    #define Y_CHAIN_POS      -1
    //#define Y_INTERPOLATE  true
    //#define Y_HOLD_MULTIPLIER 0.5
  #endif

  #if AXIS_IS_TMC_CONFIG(Y2)
    #define Y2_CURRENT      800
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
   * 默认引脚可在你的开发板引脚文件中找到。
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
   * SPI 驱动的驱动器（TMC2130、TMC2160、TMC2660、TMC5130 和 TMC5160）的软件方案。
   * 默认的软件 SPI 引脚在各自的引脚文件中定义，
   * 但你可以在此覆盖或定义它们。
   */
  #define TMC_USE_SW_SPI
  //#define TMC_SPI_MOSI  -1
  //#define TMC_SPI_MISO  -1
  //#define TMC_SPI_SCK   -1

  // @section tmc/serial

  /**
   * 四个 TMC2209 驱动可以通过硬件配置的地址共用同一个硬件/软件串口。
   * 使用 MS1 和 MS2 引脚上的跳线设置地址。
   * 地址 | MS1  | MS2
   *       0 | LOW  | LOW
   *       1 | HIGH | LOW
   *       2 | LOW  | HIGH
   *       3 | HIGH | HIGH
   *
   * 为同一串口上的所有驱动设置匹配的
   * *_SERIAL_TX_PIN 和 *_SERIAL_RX_PIN，可在此处或开发板引脚文件中设置。
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
   * 适用于不使用专用使能引脚、而是通过 SPI 或 UART 等
   * 通信线路实现相同功能的驱动。
   */
  //#define SOFTWARE_DRIVER_ENABLE

  // @section tmc/stealthchop

  /**
   * 仅适用于 TMC2130、TMC2160、TMC2208、TMC2209、TMC5130 和 TMC5160
   * 使用 Trinamic 的超静音步进模式。
   * 禁用时，Marlin 将使用 spreadCycle 步进模式。
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
   * 使用预定义参数集或库中示例提供的参数，
   * 优化 spreadCycle 斩波参数。
   * 提供的参数集有
   * CHOPPER_DEFAULT_12V
   * CHOPPER_DEFAULT_19V
   * CHOPPER_DEFAULT_24V
   * CHOPPER_DEFAULT_36V
   * CHOPPER_09STEP_24V   // 0.9 度步进电机（24V）
   * CHOPPER_PRUSAMK3_24V // 从官方 Průša 固件 MK3（24V）导入的参数
   * CHOPPER_MARLIN_119   // Marlin v1.1.9 的旧默认值
   *
   * 自定义参数的格式为：
   * { <off_time[1..15]>, <hysteresis_end[-3..12]>, hysteresis_start[1..8] }
   */
  #define CHOPPER_TIMING CHOPPER_DEFAULT_12V        // 所有轴（可被下方覆盖）
  //#define CHOPPER_TIMING_X  CHOPPER_TIMING        // 用于 X 轴（可被下方覆盖）
  //#define CHOPPER_TIMING_X2 CHOPPER_TIMING_X
  //#define CHOPPER_TIMING_Y  CHOPPER_TIMING        // 用于 Y 轴（可被下方覆盖）
  //#define CHOPPER_TIMING_Y2 CHOPPER_TIMING_Y
  //#define CHOPPER_TIMING_Z  CHOPPER_TIMING        // 用于 Z 轴（可被下方覆盖）
  //#define CHOPPER_TIMING_Z2 CHOPPER_TIMING_Z
  //#define CHOPPER_TIMING_Z3 CHOPPER_TIMING_Z
  //#define CHOPPER_TIMING_Z4 CHOPPER_TIMING_Z
  //#define CHOPPER_TIMING_I  CHOPPER_TIMING        // 用于 I 轴
  //#define CHOPPER_TIMING_J  CHOPPER_TIMING        // 用于 J 轴
  //#define CHOPPER_TIMING_K  CHOPPER_TIMING        // 用于 K 轴
  //#define CHOPPER_TIMING_U  CHOPPER_TIMING        // 用于 U 轴
  //#define CHOPPER_TIMING_V  CHOPPER_TIMING        // 用于 V 轴
  //#define CHOPPER_TIMING_W  CHOPPER_TIMING        // 用于 W 轴
  //#define CHOPPER_TIMING_E  CHOPPER_TIMING        // 用于挤出机（可被下方覆盖）
  //#define CHOPPER_TIMING_E1 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E2 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E3 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E4 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E5 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E6 CHOPPER_TIMING_E
  //#define CHOPPER_TIMING_E7 CHOPPER_TIMING_E

  // @section tmc/status

  /**
   * 监视 Trinamic 驱动
   * 是否出现过热、对地短路等错误状况。
   * 对于过热，Marlin 可降低驱动电流，直到错误状况消除。
   * 检测到的其他状况可用于停止当前打印。
   * 相关 G 代码：
   * M906 - 使用轴代码 X、Y、Z、E 设置或获取电机电流（毫安）。未给出轴代码时报告当前值。
   * M911 - 报告步进电机驱动过热预警状况。
   * M912 - 清除步进电机驱动过热预警状况标志。
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
   * 当步进电机速度超过 HYBRID_THRESHOLD 时，驱动会切换到 spreadCycle。
   * 此模式以更高的噪声为代价实现更快的运动。
   * 必须启用 STEALTHCHOP_(XY|Z|E) 才能使用 HYBRID_THRESHOLD。
   * 可用 M913 X/Y/Z/E 实时调整该设置
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
  #define I_HYBRID_THRESHOLD       3  // [直线轴=mm/s, 旋转轴=°/s]
  #define J_HYBRID_THRESHOLD       3  // [直线轴=mm/s, 旋转轴=°/s]
  #define K_HYBRID_THRESHOLD       3  // [直线轴=mm/s, 旋转轴=°/s]
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
   * 使用 StallGuard 对 X、Y、Z 进行归位 / 探测。
   *
   * 仅适用于 TMC2130、TMC2160、TMC2209、TMC2660、TMC5130 和 TMC5160
   * 将步进电机驱动的 DIAG1 引脚连接到 X/Y 限位开关引脚。
   * X、Y、Z 的归位将始终在 spreadCycle 模式下进行。
   *
   * X/Y/Z_STALL_SENSITIVITY 是默认失步阈值。
   * 使用 M914 X Y Z 在运行时设置失步阈值：
   *
   *  灵敏度        TMC2209    其他
   *    最高          255      -64    （过于灵敏 => 误触发）
   *    最低            0       63    （过于不灵敏 => 不触发）
   *
   * 建议将 HOMING_BUMP_MM 设为 { 0, 0, 0 }。
   *
   * SPI_ENDSTOPS  *** 仅 TMC2130/TMC5160 ***
   * 归位时通过 SPI 轮询驱动以判断负载。
   * 省去从 DIAG1 连接到限位开关引脚的接线。
   *
   * IMPROVE_HOMING_RELIABILITY 在归位时调整加速度与急动度，
   * 并增加一个限位开关触发的保护期。
   *
   * 注释掉 *_STALL_SENSITIVITY 可禁用该轴的无传感器归位。
   * @section tmc/stallguard
   */
  #define SENSORLESS_HOMING // 仅限支持 StallGuard 的驱动
  #define SENSORLESS_STALLGUARD_DELAY 20

  #if EITHER(SENSORLESS_HOMING, SENSORLESS_PROBING)
    // TMC2209: 0...255。TMC2130: -64...63
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
   * TMC 归位步进电机相位。
   *
   * 通过归位到步进电机线圈最近的绝对相位位置来提高归位的重复性。
   * Trinamic 驱动使用一张包含 1024 个值的步进电机相位表，
   * 覆盖 4 个整步，每步 256 个位置（即共 1024 个位置）。
   * 整步位置（128, 384, 640, 896）具有最高的保持扭矩。
   *
   * 取值 0..1023，-1 表示禁用该轴的归位相位。
   */
   #define TMC_HOME_PHASE { 896, 896, 896 }

  /**
   * 在上升沿和下降沿信号都步进（如方波）。
   */
  //#define EDGE_STEPPING

  /**
   * 启用 TMC 步进电机驱动的 M122 调试命令。
   * M122 S0/1 将启用持续上报。
   */
  #define TMC_DEBUG

  /**
   * 你可以通过填充预定义函数来设置自己的高级选项。
   * 可用函数列表见库的 GitHub 页面
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
// 用于 LPC176x LCD 与数字电流控制的 I2C 主机 ID
// 不适用于基于 Wire 库的其他外设。
//
//#define I2C_MASTER_ID  1  // 设置 0 到 2 之间的值

/**
 * TWI/I2C 总线
 *
 * 此功能为实验性功能，因此不应在生产
 * 机器上使用。启用后即可向总线上的从机
 * 设备发送和接收 I2C 数据。
 *
 * ; 示例 #1
 * ; 此宏将字符串 "Marlin" 发送到地址为 0x63 (99) 的从机设备
 * ; 它使用多个 M260 命令，每个带一个 B<十进制> 参数
 * M260 A99  ; 目标从机地址
 * M260 B77  ; M
 * M260 B97  ; a
 * M260 B114 ; r
 * M260 B108 ; l
 * M260 B105 ; i
 * M260 B110 ; n
 * M260 S1   ; 发送当前缓冲区
 *
 * ; 示例 #2
 * ; 从地址为 0x63 (99) 的从机设备请求 6 个字节
 * M261 A99 B5
 *
 * ; 示例 #3
 * ; M261 请求的串口输出示例
 * echo:i2c-reply: from:99 bytes:5 data:hello
 */

#define EXPERIMENTAL_I2CBUS
#if ENABLED(EXPERIMENTAL_I2CBUS)
  #define I2C_SLAVE_ADDRESS  0  // 设置 8 到 127 之间的值以作为从机
#endif

// @section photo

/**
 * 拍照 G 代码
 * 添加 M240 G 代码用于拍照。
 * 拍照可由数字引脚或物理移动触发。
 */
//#define PHOTO_GCODE
#if ENABLED(PHOTO_GCODE)
  // 拍照前移动到的位置（并抬高 Z）
  //#define PHOTO_POSITION { X_MAX_POS - 5, Y_MAX_POS, 0 }  // { xpos, ypos, zraise } (M240 X Y Z)
  //#define PHOTO_DELAY_MS   100                            // (ms) 返回前暂停的时长 (M240 P)
  //#define PHOTO_RETRACT_MM   6.5                          // (mm) 拍照移动的 E 轴回抽/恢复 (M240 R S)

  // Canon RC-1 或自制数码相机触发器
  // 数据来源：https://www.doc-diy.net/photo/rc-1_hacked/
  //#define PHOTOGRAPH_PIN 23

  // Canon Hack Development Kit
  // https://captain-slow.dk/2014/03/09/3d-printing-timelapses/
  //#define CHDK_PIN        4

  // 可选的第二次移动（带延时）以触发相机快门
  //#define PHOTO_SWITCH_POSITION { X_MAX_POS, Y_MAX_POS }  // { xpos, ypos } (M240 I J)

  // 保持开关按下或维持 CHDK_PIN 高电平的时长
  //#define PHOTO_SWITCH_MS   50 // (ms) (M240 D)

  /**
   * PHOTO_PULSES_US 可能需要根据主板和相机型号进行调整。
   * 引脚必须运行在 48.4kHz。
   * 请务必使用升/降沿足够快的 PHOTOGRAPH_PIN。
   * （例如，MKS SBase 的温度传感器引脚太慢，因此改用 J8 上的 P1.23。）
   *
   *  Nikon 的脉冲数据示例：https://bit.ly/2FKD0Aq
   *                红外接线：https://git.io/JvJf7
   */
  //#define PHOTO_PULSES_US { 2000, 27850, 400, 1580, 400, 3580, 400 }  // (µs) 每次 48.4kHz 振荡的持续时间
  #ifdef PHOTO_PULSES_US
    #define PHOTO_PULSE_DELAY_US 13 // (µs) 振荡中每个高/低电平脉冲的近似持续时间
  #endif
#endif

// @section cnc

/**
 * 主轴与激光控制
 *
 * 添加 M3、M4 和 M5 命令以打开/关闭主轴/激光，
 * 并设置主轴转速、主轴方向和激光功率。
 *
 * SuperPid 是 CNC 铣削社区使用的一种雕铣机/主轴转速控制器。
 * Marlin 可用于打开和关闭主轴，也可用于设置
 * 5,000 到 30,000 RPM 的主轴转速。
 *
 * 你需要为开/关功能选择一个引脚，并可选地选择一个 0-5V
 * 硬件 PWM 引脚用于速度控制，以及一个用于旋转方向的引脚。
 *
 * 更多配置细节参见 https://marlinfw.org/docs/configuration/2.0.9/laser_spindle.html。
 */
//#define SPINDLE_FEATURE
//#define LASER_FEATURE
#if EITHER(SPINDLE_FEATURE, LASER_FEATURE)
  #define SPINDLE_LASER_ACTIVE_STATE    LOW    // 若 SPINDLE_LASER_ENA_PIN 为高电平有效则设为 "HIGH"

  #define SPINDLE_LASER_USE_PWM                // 若主控支持设置速度/功率则启用
  #if ENABLED(SPINDLE_LASER_USE_PWM)
    #define SPINDLE_LASER_PWM_INVERT    false  // 若速度/功率在你想要变慢时反而升高则设为 "true"
    #define SPINDLE_LASER_FREQUENCY     2500   // (Hz) 主轴/激光频率（仅限受支持的 HAL：AVR、ESP32 和 LPC）
                                               // ESP32：若 SPINDLE_LASER_PWM_PIN 在板载则 <=78125Hz。对于 I2S 扩展器
                                               //  频率决定 PWM 分辨率。2500Hz = 0-100，977Hz = 0-255，...
                                               //  (250000 / SPINDLE_LASER_FREQUENCY) = 最大值。
  #endif

  //#define AIR_EVACUATION                     // 通过 G 代码 M10-M11 控制切割吸尘/激光吹扫电机
  #if ENABLED(AIR_EVACUATION)
    #define AIR_EVACUATION_ACTIVE       LOW    // 若开/关功能为高电平有效则设为 "HIGH"
    //#define AIR_EVACUATION_PIN        42     // 覆盖默认的切割吸尘或激光吹扫引脚
  #endif

  //#define AIR_ASSIST                         // 通过 G 代码 M8-M9 控制吹气辅助
  #if ENABLED(AIR_ASSIST)
    #define AIR_ASSIST_ACTIVE           LOW    // 吹气辅助引脚的有效电平
    //#define AIR_ASSIST_PIN            44     // 覆盖默认的吹气辅助引脚
  #endif

  //#define SPINDLE_SERVO                      // 将角度转换为主轴功率的舵机
  #ifdef SPINDLE_SERVO
    #define SPINDLE_SERVO_NR   0               // 用于主轴控制的舵机编号
    #define SPINDLE_SERVO_MIN 10               // 舵机主轴的最小角度
  #endif

  /**
   * 速度/功率可通过（'M3 S'）设置并按以下方式显示：
   *  - PWM255  (S0 - S255)
   *  - PERCENT (S0 - S100)
   *  - RPM     (S0 - S50000)  最适合搭配主轴使用
   *  - SERVO   (S0 - S180)
   */
  #define CUTTER_POWER_UNIT PWM255

  /**
   * 相对切割功率
   * 通常，'M3 O<power>' 设置的
   * OCR 功率相对于 SPEED_POWER_MIN...SPEED_POWER_MAX 范围。
   * 因此输入功率 0...255 对应 SPEED_POWER_MIN...SPEED_POWER_MAX，
   * 而不是常规范围（0 到 SPEED_POWER_MAX）。
   * 最适合与（例如）SuperPID 雕铣机控制器搭配使用：S0 = 5,000 RPM，S255 = 30,000 RPM
   */
  //#define CUTTER_POWER_RELATIVE              // 使速度与 [SPEED_POWER_MIN...SPEED_POWER_MAX] 成比例

  #if ENABLED(SPINDLE_FEATURE)
    //#define SPINDLE_CHANGE_DIR               // 若主轴控制器可改变主轴方向则启用
    #define SPINDLE_CHANGE_DIR_STOP            // 若改变旋转方向前应先停止主轴则启用
    #define SPINDLE_INVERT_DIR          false  // 若旋转方向相反则设为 "true"

    #define SPINDLE_LASER_POWERUP_DELAY   5000 // (ms) 等待主轴/激光达到速度/功率的延时
    #define SPINDLE_LASER_POWERDOWN_DELAY 5000 // (ms) 等待主轴停止的延时

    /**
     * M3/M4 功率公式
     *
     * 每种工具使用不同的数值范围进行速度/功率控制。
     * 这些参数用于在工具功率单位与 PWM 之间转换。
     *
     * Speed/Power = (PWMDC / 255 * 100 - SPEED_POWER_INTERCEPT) / SPEED_POWER_SLOPE
     * PWMDC = (spdpwr - SPEED_POWER_MIN) / (SPEED_POWER_MAX - SPEED_POWER_MIN) / SPEED_POWER_SLOPE
     */
    #if ENABLED(SPINDLE_LASER_USE_PWM)
      #define SPEED_POWER_INTERCEPT       0    // (%) 0-100，即最小功率百分比
      #define SPEED_POWER_MIN          5000    // (RPM)
      #define SPEED_POWER_MAX         30000    // (RPM) SuperPID 雕铣机控制器 0 - 30,000 RPM
      #define SPEED_POWER_STARTUP     25000    // (RPM) M3/M4 的默认速度/功率（无参数时）
    #endif

  #else

    #if ENABLED(SPINDLE_LASER_USE_PWM)
      #define SPEED_POWER_INTERCEPT       0    // (%) 0-100，即最小功率百分比
      #define SPEED_POWER_MIN             0    // (%) 0-100
      #define SPEED_POWER_MAX           100    // (%) 0-100
      #define SPEED_POWER_STARTUP        80    // (%) M3/M4 的默认速度/功率（无参数时）
    #endif

    // 定义激光测试点火功能的最小和最大测试脉冲时间值
    #define LASER_TEST_PULSE_MIN           1   // (ms) 用于激光控制菜单
    #define LASER_TEST_PULSE_MAX         999   // (ms) 注意：菜单可能无法显示超过 3 个字符

    #define SPINDLE_LASER_POWERUP_DELAY   50   // (ms) 等待主轴/激光达到速度/功率的延时
    #define SPINDLE_LASER_POWERDOWN_DELAY 50   // (ms) 等待主轴停止的延时

   /**
    * 激光安全超时
    *
    * 当一段时间内没有移动时应关闭激光。
    * 设置此值时请考虑材料的易燃性、切割速度和
    * G 代码顺序。太低可能在非常缓慢的移动中被关闭；
    * 太高则可能点燃材料。
    */
    #define LASER_SAFETY_TIMEOUT_MS     1000   // (ms)

    /**
     * 任何带 'I' 参数的 M3 或 G1/2/3/5 命令都会启用连续内联功率模式。
     *
     * 例如，'M3 I' 启用连续内联功率，由规划器处理。
     * 功率存储在移动块中，并在步进中断（ISR）处理这些块时应用。
     *
     * 'M4 I' 设置动态模式，使用当前进给速度计算激光功率 OCR 值。
     *
     * 动态模式下的任何移动都会使用当前进给速度计算激光功率。
     * 进给速度由移动命令的 F 参数设置，例如 G1 X0 Y10 F6000
     * 激光功率通过按位移除低 8 位来计算。二进制下即除以 256。
     * 计算得到 0 到 255 的 ocr 值，超过 F65535 的值将被设为 255。
     * 更精细的功率控制（如加速/减速补偿）将在未来版本中实现。
     *
     * M5 I 清除内联模式并将功率设为 0，M5 将功率输出设为 0 但保留内联模式。
     */

    /**
     * 启用 M3 命令用于激光模式的内联功率规划器同步。
      * 此功能使任何 M3 S 值都能在 CUTTER_MODE_CONTINUOUS 模式下
      * 注入块缓冲区。该选项允许 M3 激光功率无需等待
      * 规划器同步即可提交。
     */
    //#define LASER_POWER_SYNC

    /**
     * 按移动速率等比例缩放激光功率。
     *
     * - 根据入口速度与标称速度之比设置入口功率。
     * - 每 N 步提升一次功率，以近似速度梯形。
     * - 由于功率分辨率有限，这只是近似值。
     */
    //#define LASER_POWER_TRAP

    //
    // 激光 I2C 电流表（高精度 INA226 高/低边模块）
    //
    //#define I2C_AMMETER
    #if ENABLED(I2C_AMMETER)
      #define I2C_AMMETER_IMAX            0.1    // (Amps) 预期电流量程的校准值
      #define I2C_AMMETER_SHUNT_RESISTOR  0.1    // (Ohms) 校准分流电阻值
    #endif

    //
    // 激光冷却液流量计
    //
    //#define LASER_COOLANT_FLOW_METER
    #if ENABLED(LASER_COOLANT_FLOW_METER)
      #define FLOWMETER_PIN         20  // 需要支持外部中断的引脚（如 RAMPS 的 2,3,18,19,20,21）
      #define FLOWMETER_PPL       5880  // (pulses/liter) 流量计在输入引脚上每升的脉冲数
      #define FLOWMETER_INTERVAL  1000  // (ms) 流量计算间隔（毫秒）
      #define FLOWMETER_SAFETY          // 防止在低于下方设置的最小流量时运行激光
      #if ENABLED(FLOWMETER_SAFETY)
        #define FLOWMETER_MIN_LITERS_PER_MINUTE 1.5 // (liters/min) 启用后所需的最小流量
      #endif
    #endif

  #endif
#endif // SPINDLE_FEATURE || LASER_FEATURE

/**
 * 使用 M106/M107 的同步激光控制
 *
 * Marlin 通常在处理规划器块"稍后不久"应用 M106/M107 风扇速度。
 * 对于连接到风扇接口的 PWM/TTL 激光（如某些激光附加套件）来说，这不够精确。
 * 启用此选项可以以精确得多的时序设置风扇/激光速度，
 * 从而提升打印保真度。
 *
 * 注意：此选项会牺牲部分冷却风扇速度选项。
 */
//#define LASER_SYNCHRONOUS_M106_M107

/**
 * 冷却液控制
 *
 * 添加 M7、M8 和 M9 命令以打开/关闭喷雾或浇注冷却。
 *
 * 注意：还必须定义 COOLANT_MIST_PIN 和/或 COOLANT_FLOOD_PIN。
 */
//#define COOLANT_CONTROL
#if ENABLED(COOLANT_CONTROL)
  #define COOLANT_MIST                // 若存在喷雾冷却则启用
  #define COOLANT_FLOOD               // 若存在浇注冷却则启用
  #define COOLANT_MIST_INVERT  false  // 若开/关功能相反则设为 "true"
  #define COOLANT_FLOOD_INVERT false  // 若开/关功能相反则设为 "true"
#endif

// @section filament width

/**
 * 耗材宽度传感器
 *
 * 实时测量耗材宽度并调整流量，
 * 以补偿任何不规则之处。
 *
 * 还允许用测得的耗材直径来设定
 * 挤出速率，这样切片软件只需指定
 * 体积。
 *
 * 目前仅支持单个挤出机。
 *
 *  34 RAMPS_14    : AUX2 连接器上的模拟输入 5
 *  81 PRINTRBOARD : Exp1 连接器上的模拟输入 2（版本 B,C,D,E）
 * 301 RAMBO       : 模拟输入 3
 *
 * 注意：其他主板可能需要定义模拟引脚。
 */
//#define FILAMENT_WIDTH_SENSOR

#if ENABLED(FILAMENT_WIDTH_SENSOR)
  #define FILAMENT_SENSOR_EXTRUDER_NUM 0    // 安装耗材传感器的挤出机编号。:[0,1,2,3,4]
  #define MEASUREMENT_DELAY_CM        14    // (cm) 从耗材传感器到熔化腔的距离

  #define FILWIDTH_ERROR_MARGIN        1.0  // (mm) 若测量值与标称宽度相差过大则忽略
  #define MAX_MEASUREMENT_DELAY       20    // (bytes) 存储测量的缓冲区大小（每厘米 1 字节）。必须大于 MEASUREMENT_DELAY_CM。

  #define DEFAULT_MEASURED_FILAMENT_DIA DEFAULT_NOMINAL_FILAMENT_DIA // 初始时将测量值设为标称值

  // 在 LCD 状态行显示耗材宽度。状态消息将在 5 秒后消失。
  //#define FILAMENT_LCD_DISPLAY
#endif

// @section power

/**
 * 功率监测器
 * 监测电压 (V) 和/或电流 (A)，以及（如可能）功率 (W)
 *
 * 通过 M430 读取和配置
 *
 * 电流传感器将与测量电流相关的直流电压馈入模拟引脚
 * 电压传感器将与测量电压相关的直流电压馈入模拟引脚
 */
//#define POWER_MONITOR_CURRENT   // 监测系统电流
//#define POWER_MONITOR_VOLTAGE   // 监测系统电压

#if ENABLED(POWER_MONITOR_CURRENT)
  #define POWER_MONITOR_VOLTS_PER_AMP    0.05000  // 每安培输入到 MCU 模拟引脚的电压 - 切勿超过 ADC_VREF！
  #define POWER_MONITOR_CURRENT_OFFSET   0        // 应用于计算电流的偏移量（单位：安培）
  #define POWER_MONITOR_FIXED_VOLTAGE   13.6      // 无电压传感器时电流传感器所用的电压（用于功率显示）
#endif

#if ENABLED(POWER_MONITOR_VOLTAGE)
  #define POWER_MONITOR_VOLTS_PER_VOLT  0.077933  // 每伏特输入到 MCU 模拟引脚的电压 - 切勿超过 ADC_VREF！
  #define POWER_MONITOR_VOLTAGE_OFFSET  0         // 应用于计算电压的偏移量（单位：伏特）
#endif

// @section safety

/**
 * 步进电机驱动防错插保护
 *
 * 如果你的主板定义了 SAFE_POWER_PIN，Marlin 会在通电前
 * 检查步进电机驱动是否已正确插好。
 * 如果你的步进电机驱动不支持该功能，请禁用保护。
 */
//#define DISABLE_DRIVER_SAFE_POWER_PROTECT

// @section cnc

/**
 * CNC 坐标系
 *
 * 启用 G53 和 G54-G59.3 命令以选择坐标系，
 * 并启用 G92.1 将工作区重置回本机坐标空间。
 */
//#define CNC_COORDINATE_SYSTEMS

/**
 * CNC 钻孔循环 - 开发中
 *
 * 启用 G81 执行钻孔循环。
 * 目前仅支持单次循环，不支持 G 代码链式调用。
 */
//#define CNC_DRILLING_CYCLE

// @section reporting

/**
 * 通过 M123 S<seconds> 自动上报风扇速度
 * 需要带有转速计引脚的风扇
 */
//#define AUTO_REPORT_FANS

/**
 * 通过 M155 S<seconds> 自动上报温度
 */
#define AUTO_REPORT_TEMPERATURES
#if ENABLED(AUTO_REPORT_TEMPERATURES) && TEMP_SENSOR_REDUNDANT
  //#define AUTO_REPORT_REDUNDANT // 在自动上报中包含 "R" 传感器
#endif

/**
 * 通过 M154 S<seconds> 自动上报位置
 */
//#define AUTO_REPORT_POSITION

/**
 * 在 M115 输出中包含功能列表
 */
#define EXTENDED_CAPABILITIES_REPORT
#if ENABLED(EXTENDED_CAPABILITIES_REPORT)
  //#define M115_GEOMETRY_REPORT
#endif

// @section security

/**
 * 预期打印机检查
 * 添加 M16 G 代码用于将字符串与 MACHINE_NAME 比对。
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
   * 体积挤出默认状态
   * 激活后将使体积挤出成为默认方式，
   * 并以 DEFAULT_NOMINAL_FILAMENT_DIA 作为默认直径。
   *
   * M200 D0 禁用，M200 Dn 设置新直径（并启用体积挤出）。
   * M200 S0/S1 禁用/启用体积挤出。
   */
  //#define VOLUMETRIC_DEFAULT_ON

  //#define VOLUMETRIC_EXTRUDER_LIMIT
  #if ENABLED(VOLUMETRIC_EXTRUDER_LIMIT)
    /**
     * 默认体积挤出限制，单位为立方毫米每秒 (mm^3/sec)。
     * 此出厂设置适用于所有挤出机。
     * 使用 'M200 [T<extruder>] L<limit>' 覆盖，'M502' 重置。
     * 非零值将启用基于体积的挤出限制。
     */
    #define DEFAULT_VOLUMETRIC_EXTRUDER_LIMIT 0.00      // (mm^3/sec)
  #endif
#endif

// @section reporting

// M114 "当前位置"报告的额外选项
//#define M114_DETAIL         // 使用 'M114` 查看详情以检查规划器计算
//#define M114_REALTIME       // 基于正向运动学的实际当前位置
//#define M114_LEGACY         // M114 过去会在每次调用时同步。如有需要请启用。

//#define REPORT_FAN_CHANGE   // 当风扇速度被 M106（及其他命令）更改时上报新值

// @section gcode

/**
 * 花费 28 字节 SRAM 来优化 G 代码解析器
 */
#define FASTER_GCODE_PARSER

#if ENABLED(FASTER_GCODE_PARSER)
  #define GCODE_QUOTED_STRINGS    // 支持带引号的字符串参数
#endif

// 支持 MeatPack G 代码压缩 (https://github.com/scottmudge/OctoPrint-MeatPack)
//#define MEATPACK_ON_SERIAL_PORT_1
//#define MEATPACK_ON_SERIAL_PORT_2

//#define GCODE_CASE_INSENSITIVE  // 接受以小写发送到固件的 G 代码

//#define REPETIER_GCODE_M360     // 添加源自 Repetier 固件的命令

/**
 * 启用此选项可获得更精简的 Marlin 构建，移除所有
 * 工作区偏移，简化坐标变换、调平等。
 *
 *  - M206 和 M428 被禁用。
 *  - G92 将恢复为 Marlin 1.0 的行为。
 */
//#define NO_WORKSPACE_OFFSETS

/**
 * CNC G 代码选项
 * 支持激光切割机、绘图机 CAM 等使用的 CNC 风格 G 代码方言。
 * 注意 G0 进给速度在 3D 打印中应谨慎使用（如果使用的话）。
 * 高进给速度可能导致振纹并损害打印质量。
 */
//#define PAREN_COMMENTS      // 支持括号界定的注释
//#define GCODE_MOTION_MODES  // 记住运动模式 (G0 G1 G2 G3 G5 G38.X) 并应用于 X Y Z E F 等。

// 启用并为所有 G0 移动设置（默认）进给速度
//#define G0_FEEDRATE 3000 // (mm/min)
#ifdef G0_FEEDRATE
  //#define VARIABLE_G0_FEEDRATE // G0 进给速度在 G0 运动模式下由 F 设定
#endif
//#define G0_ANGULAR_FEEDRATE 2700 // (°/min)

// @section gcode

/**
 * 启动命令
 *
 * 上电后立即执行某些 G 代码命令。
 */
//#define STARTUP_COMMANDS "M17 Z"

/**
 * G 代码宏
 *
 * 添加 G 代码 M810-M819 用于定义和运行 G 代码宏。
 * 宏不会保存到 EEPROM。
 */
//#define GCODE_MACROS
#if ENABLED(GCODE_MACROS)
  #define GCODE_MACROS_SLOTS       5  // 最多可使用 10 个
  #define GCODE_MACROS_SLOT_SIZE  50  // 单个宏的最大长度
#endif

/**
 * 用户自定义菜单项以运行自定义 G 代码。
 * 最多可定义 25 个，但实际数量取决于 LCD。
 */

// @section custom main menu

// 自定义菜单：主菜单
//#define CUSTOM_MENU_MAIN
#if ENABLED(CUSTOM_MENU_MAIN)
  //#define CUSTOM_MENU_MAIN_TITLE "Custom Commands"
  #define CUSTOM_MENU_MAIN_SCRIPT_DONE "M117 User Script Done"
  #define CUSTOM_MENU_MAIN_SCRIPT_AUDIBLE_FEEDBACK
  //#define CUSTOM_MENU_MAIN_SCRIPT_RETURN   // 脚本执行后返回状态屏幕
  #define CUSTOM_MENU_MAIN_ONLY_IDLE         // 仅在机器空闲时显示自定义菜单

  #define MAIN_MENU_ITEM_1_DESC "Home & UBL Info"
  #define MAIN_MENU_ITEM_1_GCODE "G28\nG29 W"
  //#define MAIN_MENU_ITEM_1_CONFIRM          // 在此操作前显示确认对话框

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
  //#define CUSTOM_MENU_CONFIG_SCRIPT_RETURN  // 脚本执行后返回状态屏幕
  #define CUSTOM_MENU_CONFIG_ONLY_IDLE        // 仅在机器空闲时显示自定义菜单

  #define CONFIG_MENU_ITEM_1_DESC "Wifi ON"
  #define CONFIG_MENU_ITEM_1_GCODE "M118 [ESP110] WIFI-STA pwd=12345678"
  //#define CONFIG_MENU_ITEM_1_CONFIRM        // 在此操作前显示确认对话框

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
 * 用户自定义按钮以运行自定义 G 代码。
 * 最多可定义 25 个。
 */
//#define CUSTOM_USER_BUTTONS
#if ENABLED(CUSTOM_USER_BUTTONS)
  //#define BUTTON1_PIN -1
  #if PIN_EXISTS(BUTTON1)
    #define BUTTON1_HIT_STATE     LOW       // 按钮触发时的电平状态。NC=LOW。NO=HIGH。
    #define BUTTON1_WHEN_PRINTING false     // 打印期间是否允许按钮触发？
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
 * 按标准定义主机流媒体的动作命令。
 *
 * 参见 https://reprap.org/wiki/G-code#Action_commands
 * 常用命令 ........ poweroff、pause、paused、resume、resumed、cancel
 * G29_RETRY_AND_RECOVER .. probe_rewipe、probe_failed
 *
 * 某些功能会添加原因代码以扩展这些命令。
 *
 * 主机提示支持使 Marlin 能够利用主机进行用户提示，
 * 这样耗材耗尽等过程可以从主机侧管理。
 */
//#define HOST_ACTION_COMMANDS
#if ENABLED(HOST_ACTION_COMMANDS)
  //#define HOST_PAUSE_M76                // 收到 M76 时告知主机暂停
  //#define HOST_PROMPT_SUPPORT           // 发起主机提示以获取用户反馈
  #if ENABLED(HOST_PROMPT_SUPPORT)
    //#define HOST_STATUS_NOTIFICATIONS   // 以通知形式向主机发送一些状态消息
  #endif
  //#define HOST_START_MENU_ITEM          // 添加一个告知主机开始的菜单项
  //#define HOST_SHUTDOWN_MENU_ITEM       // 添加一个告知主机关机的菜单项
#endif

// @section extras

/**
 * 取消对象
 *
 * 实现 M486，让 Marlin 可以跳过对象
 */
//#define CANCEL_OBJECTS
#if ENABLED(CANCEL_OBJECTS)
  #define CANCEL_OBJECTS_REPORTING // 将当前对象作为状态消息发出
#endif

/**
 * 用于闭环控制的 I2C 位置编码器。
 * 由 Aus3D 的 Chris Barr 开发。
 *
 * Wiki：https://wiki.aus3d.com.au/Magnetic_Encoder
 * Github：https://github.com/Aus3D/MagneticEncoder
 *
 * 供应商：https://aus3d.com.au/magnetic-encoder-module
 * 备选供应商：https://reliabuild3d.com/
 *
 * Reliabuild 编码器经过修改以提高可靠性。
 * @section i2c encoders
 */

//#define I2C_POSITION_ENCODERS
#if ENABLED(I2C_POSITION_ENCODERS)

  #define I2CPE_ENCODER_CNT         1                       // 已安装编码器的数量；当前最多支持
                                                            // 5 个编码器。

  #define I2CPE_ENC_1_ADDR          I2CPE_PRESET_ADDR_X     // 编码器的 I2C 地址。30-200。
  #define I2CPE_ENC_1_AXIS          X_AXIS                  // 编码器模块安装所在的轴。<X|Y|Z|E>_AXIS。
  #define I2CPE_ENC_1_TYPE          I2CPE_ENC_TYPE_LINEAR   // 编码器类型：I2CPE_ENC_TYPE_LINEAR 或
                                                            // I2CPE_ENC_TYPE_ROTARY。
  #define I2CPE_ENC_1_TICKS_UNIT    2048                    // 磁条极距为 2mm 时用 1024；极距为
                                                            // 1mm 时用 2048。对线性编码器这是 ticks / mm，
                                                            // 对旋转编码器这是 ticks / 圈。
  //#define I2CPE_ENC_1_TICKS_REV     (16 * 200)            // 仅旋转编码器需要；每整圈的步进电机
                                                            // 步数（电机步数/圈 * 细分步进）
  //#define I2CPE_ENC_1_INVERT                              // 反转轴的移动方向。
  #define I2CPE_ENC_1_EC_METHOD     I2CPE_ECM_MICROSTEP     // 误差校正类型。
  #define I2CPE_ENC_1_EC_THRESH     0.10                    // 误差（单位 mm）超过此阈值时
                                                            // 打印机将尝试校正；小于此阈值的误差
                                                            // 会被忽略，以尽量减少
                                                            // 测量噪声/延迟（滤波）的影响。

  #define I2CPE_ENC_2_ADDR          I2CPE_PRESET_ADDR_Y     // 同上，但用于编码器 2。
  #define I2CPE_ENC_2_AXIS          Y_AXIS
  #define I2CPE_ENC_2_TYPE          I2CPE_ENC_TYPE_LINEAR
  #define I2CPE_ENC_2_TICKS_UNIT    2048
  //#define I2CPE_ENC_2_TICKS_REV   (16 * 200)
  //#define I2CPE_ENC_2_INVERT
  #define I2CPE_ENC_2_EC_METHOD     I2CPE_ECM_MICROSTEP
  #define I2CPE_ENC_2_EC_THRESH     0.10

  #define I2CPE_ENC_3_ADDR          I2CPE_PRESET_ADDR_Z     // 编码器 3。可像上面那样添加额外的配置选项，
  #define I2CPE_ENC_3_AXIS          Z_AXIS                  // 或使用下方的默认值。

  #define I2CPE_ENC_4_ADDR          I2CPE_PRESET_ADDR_E     // 编码器 4。
  #define I2CPE_ENC_4_AXIS          E_AXIS

  #define I2CPE_ENC_5_ADDR          34                      // 编码器 5。
  #define I2CPE_ENC_5_AXIS          E_AXIS

  // 已启用但未在上方配置设置的编码器的默认设置。
  #define I2CPE_DEF_TYPE            I2CPE_ENC_TYPE_LINEAR
  #define I2CPE_DEF_ENC_TICKS_UNIT  2048
  #define I2CPE_DEF_TICKS_REV       (16 * 200)
  #define I2CPE_DEF_EC_METHOD       I2CPE_ECM_NONE
  #define I2CPE_DEF_EC_THRESH       0.1

  //#define I2CPE_ERR_THRESH_ABORT  100.0                   // 误差（单位 mm）在任一轴上超过此阈值时
                                                            // 打印机将中止。注释掉即可
                                                            // 禁用中止行为。

  #define I2CPE_TIME_TRUSTED        10000                   // 编码器出错后，必须在此时间量（单位 ms）内
                                                            // 不再出错，编码器才会
                                                            // 重新被信任。

  /**
   * 每次从缓冲区执行新命令时都会检查位置，但在长距离移动期间，
   * 此设置决定两次检查之间的最小更新时间。在只校正失步而不校正振动时，
   * 取值 100 与误差滚动平均值配合效果良好。
   */
  #define I2CPE_MIN_UPD_TIME_MS     4                       // (ms) 编码器检查之间的最小时间间隔。

  // 使用滚动平均值来识别表明失步的持续错误，以区别于振动和噪声。
  #define I2CPE_ERR_ROLLING_AVERAGE

#endif // I2C_POSITION_ENCODERS

/**
 * 模拟摇杆
 * @section joystick
 */
//#define JOYSTICK
#if ENABLED(JOYSTICK)
  #define JOY_X_PIN    5  // RAMPS：建议使用 AUX2 上的引脚 A5
  #define JOY_Y_PIN   10  // RAMPS：建议使用 AUX2 上的引脚 A10
  #define JOY_Z_PIN   12  // RAMPS：建议使用 AUX2 上的引脚 A12
  #define JOY_EN_PIN  44  // RAMPS：建议使用 AUX2 上的引脚 D44

  //#define INVERT_JOY_X  // 若 X 方向相反则启用
  //#define INVERT_JOY_Y  // 若 Y 方向相反则启用
  //#define INVERT_JOY_Z  // 若 Z 方向相反则启用

  // 连接后可配合 JOYSTICK_DEBUG 使用 M119 来寻找合理的数值：
  #define JOY_X_LIMITS { 5600, 8190-100, 8190+100, 10800 } // 最小值、死区起点、死区终点、最大值
  #define JOY_Y_LIMITS { 5600, 8250-100, 8250+100, 11000 }
  #define JOY_Z_LIMITS { 4800, 8080-100, 8080+100, 11550 }
  //#define JOYSTICK_DEBUG
#endif

/**
 * 机械龙门架校准
 * Průša TMC_Z_CALIBRATION 的现代替代方案。
 * 增加了与任何可调电流驱动器配合使用的能力。
 * 因 M915 已弃用，故实现为 G34。
 * @section calibrate
 */
//#define MECHANICAL_GANTRY_CALIBRATION
#if ENABLED(MECHANICAL_GANTRY_CALIBRATION)
  #define GANTRY_CALIBRATION_CURRENT          600     // 默认校准电流（毫安）
  #define GANTRY_CALIBRATION_EXTRA_HEIGHT      15     // 越过 Z_###_POS 后额外移动的距离（mm）
  #define GANTRY_CALIBRATION_FEEDRATE         500     // 校正移动的进给速度
  //#define GANTRY_CALIBRATION_TO_MIN                 // 启用后沿 MIN 方向校准 Z

  //#define GANTRY_CALIBRATION_SAFE_POSITION XY_CENTER // 喷嘴的安全位置
  //#define GANTRY_CALIBRATION_XY_PARK_FEEDRATE 3000  // XY 停靠进给速度 - mm/min
  //#define GANTRY_CALIBRATION_COMMANDS_PRE   ""
  #define GANTRY_CALIBRATION_COMMANDS_POST  "G28"     // 强烈建议使用 G28 以确保位置准确
#endif

/**
 * 立即冻结/解冻功能
 * 对允许恢复的紧急停止可能有用。
 * @section interface
 */
//#define FREEZE_FEATURE
#if ENABLED(FREEZE_FEATURE)
  //#define FREEZE_PIN 41   // 在此处覆盖默认的 (KILL) 引脚
  #define FREEZE_STATE LOW  // 指示冻结状态的引脚电平
#endif

/**
 * MAX7219 调试矩阵
 *
 * 添加对基于 Max7219 芯片的低成本 8x8 LED 矩阵的支持，作为实时状态显示。
 * 需要 3 根信号线。包含一些实用的调试选项以演示其用法。
 * @section debug matrix
 */
//#define MAX7219_DEBUG
#if ENABLED(MAX7219_DEBUG)
  #define MAX7219_CLK_PIN   64
  #define MAX7219_DIN_PIN   57
  #define MAX7219_LOAD_PIN  44

  //#define MAX7219_GCODE          // 添加 M7219 G 代码以控制 LED 矩阵
  #define MAX7219_INIT_TEST    2   // 启动时的测试图案：0=无, 1=扫掠, 2=螺旋
  #define MAX7219_NUMBER_UNITS 1   // 链中 Max7219 单元的数量。
  #define MAX7219_ROTATE       0   // 顺时针旋转显示（以 +/- 90° 的倍数）
                                   // 连接器位置：右=0   下=-90  上=90  左=180
  //#define MAX7219_REVERSE_ORDER  // LED 矩阵单元的顺序可以反转
  //#define MAX7219_REVERSE_EACH   // 每个矩阵单元行中的 LED 可以反转
  //#define MAX7219_SIDE_BY_SIDE   // 大芯片+矩阵板可以并排链接

  /**
   * 示例调试功能
   * 如果添加更多调试显示，请小心避免冲突！
   */
  #define MAX7219_DEBUG_PRINTER_ALIVE     // 闪烁 8x8 矩阵的角落 LED 以表明固件正在运行
  #define MAX7219_DEBUG_PLANNER_HEAD  2   // 在此行及下一行 LED 矩阵上显示规划器队列头部位置
  #define MAX7219_DEBUG_PLANNER_TAIL  4   // 在此行及下一行 LED 矩阵上显示规划器队列尾部位置

  #define MAX7219_DEBUG_PLANNER_QUEUE 0   // 在此行及下一行 LED 矩阵上显示当前规划器队列深度
                                          // 如果遇到卡顿、重启等问题，此选项可以实时显示
                                          // 对配置的调整如何影响打印机。
  #define MAX7219_DEBUG_PROFILE       6   // 在此行 LED 矩阵上显示 CPU 花在被分析代码上的时间比例。
                                          // 默认对 idle() 进行分析，因此这能显示处理器有多"空闲"。
                                          // 参见 CodeProfiler 类。
  //#define MAX7219_DEBUG_MULTISTEPPING 6 // 在此行 LED 矩阵上显示 1 到 128 的细分步进。
#endif

/**
 * NanoDLP 同步支持
 *
 * 与 NanoDLP 配合使用时支持 Z 轴同步移动。G0/G1 轴移动会
 * 输出一个 "Z_move_comp" 字符串，以实现与 DLP 投影仪曝光的同步。
 * 此功能允许你用 [[WaitForDoneMessage]] 代替 M400 命令。
 * @section nanodlp
 */
//#define NANODLP_Z_SYNC
#if ENABLED(NANODLP_Z_SYNC)
  //#define NANODLP_ALL_AXIS  // 对任意轴移动（不仅是 Z）发送 "Z_move_comp" 报告。
#endif

/**
 * 以太网。使用 M552 启用并设置 IP 地址。
 * @section network
 */
#if HAS_ETHERNET
  #define MAC_ADDRESS { 0xDE, 0xAD, 0xBE, 0xEF, 0xF0, 0x0D }  // 你的网络中唯一的 MAC 地址
#endif

/**
 * WiFi 支持（Espressif ESP32 WiFi）
 */
//#define WIFISUPPORT         // Marlin 内置 WiFi 管理
//#define ESP3D_WIFISUPPORT   // ESP3D 库 WiFi 管理 (https://github.com/luc-github/ESP3DLib)

#if EITHER(WIFISUPPORT, ESP3D_WIFISUPPORT)
  //#define WEBSUPPORT          // 启动网页服务器（可能包括自动发现）
  //#define OTASUPPORT          // 支持无线（OTA）固件更新
  //#define WIFI_CUSTOM_COMMAND // 接受来自主机的功能配置命令（如 WiFi ESP3D）

  /**
   * 要设置默认的 WiFi SSID / 密码，请创建一个名为 Configuration_Secure.h 的文件，
   * 内容为以下定义，并根据你的网络进行定制。此文件已通过
   * .gitignore 排除，以防意外泄露到公开场合。
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
 * 这些设备允许主板上单个步进电机驱动来驱动
 * 带任意数量步进电机的多材料送料器。
 */
#if HAS_PRUSA_MMU1
  /**
   * 此选项仅允许多路复用器在换工具时切换。
   * 用于配置自定义 E 轴移动的额外选项尚待开发。
   *
   * 如有需要，可在此处覆盖默认的 DIO 选择器引脚。
   * 某些引脚文件可能已提供这些引脚的默认值。
   */
  //#define E_MUX0_PIN 40  // 始终必需
  //#define E_MUX1_PIN 42  // 3 到 8 路输入时需要
  //#define E_MUX2_PIN 44  // 5 到 8 路输入时需要
#elif HAS_PRUSA_MMU2
  // 用于与 MMU2 通信的串口。
  #define MMU2_SERIAL_PORT 2

  // 若为其定义了引脚，则对 MMU 使用硬件复位
  //#define MMU2_RST_PIN 23

  // 若 MMU2 使用 12V 步进电机则启用（MMU2 固件 1.0.2 及以上）
  //#define MMU2_MODE_12V

  // 当 MMU2 F.I.N.D.A. 探针检测到耗材耗尽时执行的 G 代码
  #define MMU2_FILAMENT_RUNOUT_SCRIPT "M600"

  // 为 MMU2 添加 LCD 菜单
  //#define MMU2_MENUS

  // 从 LCD 菜单装载/卸载耗材的设置。
  // 适用于 Průša MK3 风格的挤出机。请根据你的硬件定制。
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
   * 使用类似 MMU2S 的传感器
   * 此模式需要 MK3S 挤出机，其挤出机压轮处带有传感器，如 MMU2S。
   * 参见 https://help.prusa3d.com/en/guide/3b-mk3s-mk2-5s-extruder-upgrade_41560，第 11 步
   */
  #if HAS_PRUSA_MMU2S
    #define MMU2_C0_RETRY   5             // 重试次数（总时间 = 超时*重试次数）

    #define MMU2_CAN_LOAD_FEEDRATE 800    // (mm/min)
    #define MMU2_CAN_LOAD_SEQUENCE \
      {  0.1, MMU2_CAN_LOAD_FEEDRATE }, \
      {  60.0, MMU2_CAN_LOAD_FEEDRATE }, \
      { -52.0, MMU2_CAN_LOAD_FEEDRATE }

    #define MMU2_CAN_LOAD_RETRACT   6.0   // (mm) 保持小于装载序列各值之间的距离
    #define MMU2_CAN_LOAD_DEVIATION 0.8   // (mm) 可接受的偏差

    #define MMU2_CAN_LOAD_INCREMENT 0.2   // (mm) 在 MMU2 模块内复用
    #define MMU2_CAN_LOAD_INCREMENT_SEQUENCE \
      { -MMU2_CAN_LOAD_INCREMENT, MMU2_CAN_LOAD_FEEDRATE }

    // 若传感器在初始卸料移动后检测到耗材则继续卸料
    //#define MMU_IR_UNLOAD_MOVE
  #else

    /**
     * MMU1 挤出机传感器
     *
     * 支持 Průša（或其他）红外传感器检测挤出机附近的耗材，
     * 使装载更可靠。适用于齿轮 38mm 范围内装有耗材
     * 传感器的挤出机。
     *
     * 装载期间，传感器被触发时挤出机会停止，然后
     * 向齿轮做最后一次移动。如果未检测到耗材，MMU2 可以再尝试几次。
     * 如果所有尝试都失败，将触发耗材耗尽。
     */
    //#define MMU_EXTRUDER_SENSOR
    #if ENABLED(MMU_EXTRUDER_SENSOR)
      #define MMU_LOADING_ATTEMPTS_NR 5 // 首次装载失败时装载耗材的最大尝试次数
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
  // 激活最多 3 个保养间隔看门狗
  //#define SERVICE_NAME_1      "Service S"
  //#define SERVICE_INTERVAL_1  100 // 打印小时
  //#define SERVICE_NAME_2      "Service L"
  //#define SERVICE_INTERVAL_2  200 // 打印小时
  //#define SERVICE_NAME_3      "Service 3"
  //#define SERVICE_INTERVAL_3    1 // 打印小时
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

// 启用将在启动时运行并生成报告的测试
//#define MARLIN_TEST_BUILD

// 启用 Marlin 开发模式，会添加一些特殊命令
//#define MARLIN_DEV_MODE

#if ENABLED(MARLIN_DEV_MODE)
  /**
   * D576 - 缓冲区监测
   * 用于帮助诊断由命令缓冲区空置引起的打印质量问题。
   */
  //#define BUFFER_MONITORING
#endif

/**
 * 事后调试（Postmortem Debugging）捕获异常行为并将 CPU 状态和回溯输出到串口。
 * 在调试器中运行时会中断以便调试。这有助于远程分析
 * 崩溃原因。需要约 400 字节 SRAM 和 5Kb 闪存。
 */
//#define POSTMORTEM_DEBUGGING

/**
 * 软件复位选项
 */
//#define SOFT_RESET_VIA_SERIAL         // 'KILL' 和 '^X' 命令将软复位控制器
//#define SOFT_RESET_ON_KILL            // 在 KILL 后使用数字按钮软复位控制器

// 从寄存器 r2 而非 MCUSR 报告未经清理的复位原因。AVR 上的 Optiboot 支持。
//#define OPTIBOOT_RESET_REASON
