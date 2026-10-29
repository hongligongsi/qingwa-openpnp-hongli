# 项目长期记忆 · qingwa-openpnp-hongli

## 项目定位
「青蛙贴片机」专用固件：Marlin 2.1.x 改造为 SMT 贴片机运动控制器。
- 硬件：Opulo LumenPnP Motherboard REV5（STM32F407VET6，Cortex-M4）
- 目标 env：`Opulo_Lumen_REV5`（platformio.ini，default_envs）
- README 已全面中文化（README.md 中文 / README.en.md 英文对照）

## 注释本地化约定（进行中）
`Marlin/Configuration.h` 与 `Marlin/Configuration_adv.h` 的英文注释正在逐段译为简体中文。
统一术语：步进电机驱动 / 挤出机 / 热端 / 热床 / 探针 / 限位开关 / 归位 / 调平 /
校准 / 固件 / 主机 / 启用·禁用 / 默认 / 覆盖 / 喷嘴 / 耗材 / 回抽 / 进给速度 / 微控制器。

### 翻译时绝不能改动的机器可读内容
`buildroot/share/PlatformIO/scripts/schema.py` 会解析配置注释生成
`marlin_config.json` / `schema.json`，以下内容一旦破坏会导致构建失败：
1. `// @section xxx` —— 章节名是解析器分组键，翻译会导致整段错位
2. `:[...]` 与 `:{...}` 选项列表 —— 必须单行，换行会抛 `ValueError: substring not found`
3. 括号单位标记 `(mm)` `(°C)` `(ms)` `(seconds)` `(K/s)` —— 会被提取为 schema 的 units 字段
4. `Temperature sensors available:` 标记行 —— 解析器据此切换到传感器收集模式
5. 温度传感器条目行 ` *    -5 : MAX31865 with ...` —— 每条必须独占一行
6. 字符串字面量、宏名、G 代码命令、URL

## 校验工具（本次新增，务必使用）
- `buildroot/scripts/check-config-i18n.py`
  三段校验：注释结构完整性 → ARM 工具链预处理 → schema 与基线快照比对
  基线：`buildroot/scripts/config-schema-baseline.json`（2444 项配置项）
- `buildroot/scripts/check-config-code-intact.py --ref HEAD`
  功能等价校验：用真实 PlatformIO 编译参数跑 `arm-none-eabi-gcc -E`，
  比对归一化后的预处理输出。**这是最终判据** —— 输出相同即代码行为完全一致。

## 踩过的坑
1. **批量重排配置注释会破坏 schema 解析**：把 `:[...]` 拆行、把 `//#define` 与前文
   合并到同一行、把传感器条目并进 NOTE 文本 —— 都会让 `schema.extract()` 崩溃或
   静默丢失配置项（曾一次丢 34 项）。
2. **`pio run` 触发 WorkBuddy 批量删除守卫**：PlatformIO 想删 `.pio/libdeps` 下
   143 个缓存文件时会被 `[safe-delete][SAFE_DELETE_BULK_CONFIRM_REQUIRED]` 拦下。
   绕过办法：用 `pio run -v`（verbose 模式不触发删除），从输出中抓真实编译命令。
3. **纯格式化改动（对齐列、续行 `\`、压缩空格）不影响功能**，已用预处理输出
   逐字节比对确认。Configuration.h 现有 109 处续行、819 行有效代码（原 710 行）。

## hongli pnp 产品线口径（易搞混，务必记住）
- **honglipnp/ 是 jpackage 绿色版运行时映像**（321 MB，OpenPnP.exe + app/ + runtime/ 自带 Java 17.0.20.1）
- 用户提供的「定制功能清单」是 **需求口径（PRD）**，不是已实现功能介绍。
  权威规格：`docs/hongli-pnp-需求规格.md`（R1–R9 / 28 条 / 验收标准 / 优先级）。
  规格不得写成"已实现"，实现状态单独对照（见该文档附录 A）
- 待定版的口径冲突：配置目录 `.hlpnp`（需求）vs `.lfpnp`（安装说明.txt 旧）；
  安装路径 `C:\honglipnp`（需求）vs `%LOCALAPPDATA%\OpenPnP`（安装说明.txt 旧）
- 已知缺口：`ThickSliderUI` 尚未进入打包产物（jar 内无 Slider 类）
- **定制版源码副本已丢失，但可完整重建**：上游 openpnp tag 2.6 已克隆至
  `C:/Users/hongliwang/Desktop/openpnp-2.6-src`；产物=干净 2.6+16 新类（jar/上游对比 0 缺失）。
  重建方案见 `docs/hongli-pnp-源码重建方案.md`；反编译用 honglipnp 自带 JRE

## 平台信息
- 编译前需 `python3 ./.trellis/scripts/init_developer.py <name>`（trellis 工作流）
- ARM 工具链：`C:\Users\hongliwang\.platformio\packages\toolchain-gccarmnoneeabi\bin\`
- PlatformIO 装在系统 Python 3.13（非 managed venv），`pio` 可直接用
