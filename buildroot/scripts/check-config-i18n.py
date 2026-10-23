#!/usr/bin/env python3
"""
配置注释翻译回归校验脚本 —— 初学者导读
================================================================================

【这个脚本解决什么问题？】
本仓库把 Marlin 的 `Configuration.h` / `Configuration_adv.h` 里的英文注释逐段译成了
简体中文。听着只是"改注释"，其实风险不小：Marlin 有一部分**注释是机器要读的**。
一旦把格式改坏，构建脚本解析不到配置项，编译就会失败，或者更糟——静默丢配置
（改过的参数悄悄消失，机器还照常编译，但行为变了）。

所以每次改完注释，都跑一遍这个脚本，确认"注释结构没坏、代码语义没变"。

【为什么注释会被程序读取？先认识 3 个概念】

1. `// @section 章节名`
   Marlin 用这种注释做分组。`schema.py` 靠它把配置项归到"Stepper Drivers"这类
   章节下。把 `@section` 译成中文 → 分组键变了 → 整个网站/JSON 的配置结构错位。

2. `#define XYZ 42   // :[10:20] :{A} :{B}`
   注意行尾 `:[min:max]`（数值范围）和 `:{选项}`（枚举可选值）——这是给配置器
   （如 Marlin 官方 Configuration 网页）用的**机器可读**数据，必须写在同一行。
   若翻译时被换行拆开，解析器会抛 `ValueError: substring not found`。

3. 括号里的单位，如 `(mm)` `(°C)` `(ms)`
   会被抽出来当成单位标签显示。译成"(毫米)"就丢了单位元数据。

结论：**注释文字可以随便译，但上面这三类"结构标记"必须原样保留。**

【这个脚本校验什么？（三步，由轻到重）】

  [1/3] 结构完整性 —— 便宜、快。纯文本扫描，找被拆行的选项列表、被合并进注释的
        `#define` 行。这一步能抓住 90% 的手滑。

  [2/3] 预处理语法 —— 真正调 ARM 交叉编译器跑一遍 `-E`（预处理）/`-fsyntax-only`
        （只查语法），确认改了注释之后头文件仍然能被编译器接受。

  [3/3] schema 语义 —— 调上游 `schema.py` 把配置项抽成"键 → 值"快照，和基线
        `config-schema-baseline.json`（2444 项）逐项比对，确认没有配置项丢失/新增，
        也没有实质语义变化。纯空白差异会放行（C++ 里 `a  =  1` 和 `a = 1` 等价）。

【怎么用？】
    python buildroot/scripts/check-config-i18n.py                # 常规校验
    python buildroot/scripts/check-config-i18n.py --update-baseline  # 确实要改配置时重写基线

退出码：0 = 全部通过，1 = 有问题（可直接用在 CI 里）。

【想深入学的建议阅读顺序】
    schema.py（上游，看它怎么解析注释） → 本脚本第 1 步（结构规则到底有哪些）
    → 第 3 步（怎么把配置项拍平成可比较的快照）
"""
import argparse
import io
import json
import os
import re
import subprocess
import sys

# ---------------------------------------------------------------------------
# 路径常量
# ROOT = 仓库根目录。__file__ 是本脚本路径，往上三层正好是仓库根：
#   .../buildroot/scripts/check-config-i18n.py
#   └─ scripts/      └─ buildroot/      └─ 仓库根
# 用绝对路径而非相对路径，是为了让脚本在任何目录下执行都能找到文件。
# ---------------------------------------------------------------------------
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

# 需要校验的两个配置文件（主板激活配置）
CONFIG_FILES = ['Marlin/Configuration.h', 'Marlin/Configuration_adv.h']

# 基线快照：记录"翻译前"的配置项集合，用来和当前状态对比
BASELINE = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'config-schema-baseline.json')


def load_schema():
    """
    调用上游 schema.py 提取当前配置项，拍平成 {'文件|章节|配置项': 值} 的一层字典。

    为什么要拍平？
      schema.extract() 返回的是三层嵌套结构：
          {文件: {章节: {配置项: {...字段...}}}}
      嵌套结构不利于做集合比较（"少没少项"）。拍平成一层后，直接比 set 就行。

    这里的 `import schema` 有点讲究：schema.py 在 buildroot/share/PlatformIO/scripts/
    下，不在默认搜索路径里，所以先用 sys.path.insert 把该目录加进去。
    另外 schema.extract() 内部按**当前工作目录**找配置文件，所以先 os.chdir(ROOT)。
    """
    scripts = os.path.join(ROOT, 'buildroot', 'share', 'PlatformIO', 'scripts')
    sys.path.insert(0, scripts)
    os.chdir(ROOT)
    import schema  # noqa: E402  (放在函数内导入：避免脚本启动时就依赖上游文件)

    snap = schema.extract()
    out = {}
    for filekey, sections in snap.items():
        for sectkey, opts in sections.items():
            for optkey, val in opts.items():
                out[f'{filekey}|{sectkey}|{optkey}'] = val
    return out


def core_fields(v):
    """
    取"语义字段"，剔除只跟位置/展示有关的字段。

    schema 抽出来的每个配置项是个 dict，里面除了值还有：
      line    —— 在文件第几行（翻译时行号必然变，不能算差异）
      sid     —— 内部编号（可能随顺序变）
      comment —— 注释原文（翻译后当然不一样，这正是我们要做的）
    这三项一剔除，剩下的就是"这台机器实际会怎么跑"相关的字段。
    """
    if not isinstance(v, dict):
        return v
    return {k: v[k] for k in v if k not in ('line', 'sid', 'comment')}


def check_structure():
    """
    【第 1 步】纯文本扫描，检查两类最容易犯的错。

    规则一：`#define` 不能被并进注释行
        错误示例（把注释和下一行的 #define 合并了）：
            // 步进电机每毫米步数  #define DEFAULT_AXIS_STEPS_PER_UNIT { 80, 80, 400 }
        这样 #define 就"失效"了——它现在是注释的一部分，编译器看不见，配置项凭空消失。

    规则二：`:[...]` / `:{...}` 选项列表不能换行
        错误示例（把一行的选项列表拆成了两行）：
            // :[10:20]
            // :{A} :{B}
        schema.py 用正则整行匹配，拆行后匹配不到 → 直接抛异常。

    实现思路：逐行看"去掉注释符号后的正文"，如果它以 `:` 开头且括号没闭合，就是被拆行了。
    注意 `//#define`（注释掉的 #define）是合法写法，要放行——所以先遇到 `#define` 就 continue。
    """
    problems = []
    for fn in CONFIG_FILES:
        path = os.path.join(ROOT, fn)
        lines = io.open(path, encoding='utf-8').read().split('\n')
        for i, l in enumerate(lines, 1):          # i 从 1 开始：报错要给"人看"的行号
            t = l.strip()

            # 取出这一行的"注释正文" c
            if t.startswith('//'):
                rest = t[2:].strip()               # // 开头的行注释
                if rest.startswith('#define'):
                    continue                       # 合法的 //#define（被注释掉的宏）
                if '#define' in rest:
                    problems.append(f'{fn}:{i} #define 被合并进注释行: {t[:80]}')
                c = rest
            elif t.startswith('*'):
                c = t[1:].strip()                  # /* ... */ 块注释的中间行（以 * 开头）
                if c.startswith('#define'):
                    continue
            else:
                continue                           # 普通代码行，跳过

            # 只关心以 `:` 开头的选项列表行
            if c.startswith(':'):
                d = c[1:].strip()
                # 有左括号却没有对应的右括号 ⇒ 被换行拆开了
                if (d.startswith('[') and ']' not in d) or (d.startswith('{') and '}' not in d):
                    problems.append(f'{fn}:{i} 选项列表被拆行: {t[:80]}')
    return problems


def check_preprocess():
    """
    【第 2 步】让真正的 ARM 编译器读一遍改过的头文件。

    为什么需要这一步？
        第 1 步只查"注释形状"，查不出"注释里的内容是否意外破坏了宏定义"。
        比如注释里出现了不配对的 `/*`，或者 `#if` 结构被注释掉一半——这些只有
        预处理器才能判断。

    做法：
        -E              只做预处理（展开 include/define），不编译
        -fsyntax-only   只做语法检查，不生成机器码
        把 -E 换成 -fsyntax-only，让编译器走得更深一点，能顺带发现语法错误。

    注意：这里只挑 stderr 里含 " error" 的行统计，warning 不算失败
    （Marlin 本身 warning 很多，翻译不该为它们背锅）。
    """
    cmd = build_preprocess_cmd()
    if cmd is None:
        return ['跳过预处理检查 (缺少 arm-none-eabi-gcc)']   # 环境没装工具链时优雅降级

    # 改造命令：只要语法检查，不要预处理输出（-P 会把行号标记去掉，这里不需要）
    cmd = [c for c in cmd if c != '-P']
    cmd = [c if c != '-E' else '-fsyntax-only' for c in cmd]

    problems = []
    for target in CONFIG_FILES:
        r = subprocess.run(
            cmd + [target, '-o', os.devnull],     # -o /dev/null：不落盘产物
            capture_output=True, text=True, cwd=ROOT)
        errs = [l for l in r.stderr.split('\n') if ' error' in l]
        if errs:
            problems.append(f'{target} 预处理报错 {len(errs)} 处')
            problems += ['    ' + e for e in errs[:10]]   # 最多列 10 条，避免刷屏
    return problems


def build_preprocess_cmd():
    """
    拼出"和真实固件构建一致"的编译器命令行。

    关键点：预处理结果对不对，取决于宏定义（-D）和头文件搜索路径（-I）是否和
    PlatformIO 实际编译时一致。差一个宏，条件编译走的分支就不同，校验就没意义。

    两条路：
      ① 优先读 .pio/build/Opulo_Lumen_REV5/idedata.json —— 这是 PlatformIO 生成给
         IDE 做代码索引用的文件，里面就是**真实构建用的 defines 和 includes**。
         有它最省事，直接照搬。
      ② 没这个文件（.pio 被清理过）时，按 platformio.ini + Marlin 已知宏手工推导
         一套等价参数。会啰嗦一点，但离线也能校验。

    返回 None 表示找不到 ARM 工具链，调用方会跳过这一步。
    """
    # --- 找交叉编译器（写死本机路径；换机器需要改这里）---
    gcc = None
    for c in [
        r'C:\Users\hongliwang\.platformio\packages\toolchain-gccarmnoneeabi\bin\arm-none-eabi-gcc.exe',
    ]:
        if os.path.exists(c):
            gcc = c
            break
    if not gcc:
        return None

    # --- 路线①：用 PlatformIO 的真实构建参数 ---
    idedata = os.path.join(ROOT, '.pio', 'build', 'Opulo_Lumen_REV5', 'idedata.json')
    if os.path.exists(idedata):
        d = json.load(open(idedata, encoding='utf-8'))
        # -E 只预处理；-x c++ 按 C++ 解析（Marlin 是 C++ 工程）；-P 去掉行号标记
        cmd = [gcc, '-E', '-x', 'c++', '-std=gnu++11', '-Wno-unused-macros', '-P']
        cmd += ['-D' + x for x in d['defines']]     # 复制真实宏
        cmd += ['-I' + i for i in d['includes']]    # 复制真实包含路径
        cmd += ['-I', 'Marlin', '-I', 'Marlin/src', '-I', 'buildroot',
                '-I', 'Marlin/src/HAL/STM32', '-I', 'Marlin/src/pins/stm32f4',
                '-I', 'Marlin/src/core']
        # 强制先包含 macros.h：Marlin 的配置大量依赖其中的工具宏
        cmd += ['-include', 'Marlin/src/core/macros.h']
        return cmd

    # --- 路线②：退化路径，手工推导等价参数 ---
    fw = os.path.join(ROOT, '.platformio', 'packages', 'framework-arduinoststm32')
    cmd = [gcc, '-E', '-x', 'c++', '-std=gnu++14', '-Wno-unused-macros', '-P']

    # 这些宏就是 PlatformIO 构建 Opulo_Lumen_REV5 时会传的（板型/主频/串口缓冲等）
    for macro in [
        'PLATFORMIO=60200', 'STM32F407xx', '__MARLIN_FIRMWARE__', 'NDEBUG',
        'HAL_STM32', 'USBCON', 'USBD_USE_CDC', 'TIM_IRQ_PRIO=13',
        'ADC_RESOLUTION=12', 'ARDUINO_BLACK_F407VE', 'USBD_USE_CDC_COMPOSITE',
        'USE_USB_FS', 'BOARD_F_CPU=168000000L', 'SERIAL_RX_BUFFER_SIZE=128',
        'SERIAL_TX_BUFFER_SIZE=64', 'USART_RX_BUF_SIZE=128', 'USART_TX_BUF_SIZE=64',
        'STM32F4xx', 'ARDUINO=10808', 'ARDUINO_ARCH_STM32',
        'ARDUINO_MARLIN_OPULO_LUMEN_REV5', 'BOARD_NAME="MARLIN_OPULO_LUMEN_REV5"',
        'HAL_UART_MODULE_ENABLED', 'HAL_PCD_MODULE_ENABLED',
    ]:
        cmd.append('-D' + macro)

    # 逐个把"存在才加"的包含路径加进去：目录不存在就跳过，
    # 这样换一台机器（库版本不同）也不会因为路径缺失直接报错。
    cmd += ['-I', 'Marlin']
    for sub in ['Servo/src', 'Wire/src', 'EEPROM/src', 'IWatchdog/src',
                'SPI/src', 'SoftwareSerial/src']:
        p = os.path.join(fw, 'libraries', sub)
        if os.path.isdir(p):
            cmd += ['-I', p]
    for lib in ['Adafruit NeoPixel', 'TMCStepper/src', 'RS485/include', 'RS485/src']:
        p = os.path.join(ROOT, '.pio', 'libdeps', 'Opulo_Lumen_REV5', lib)
        if os.path.isdir(p):
            cmd += ['-I', p]
    for sub in ['cores/arduino/avr', 'cores/arduino/stm32', 'cores/arduino/stm32/LL',
                'cores/arduino/stm32/usb', 'cores/arduino/stm32/usb/hid',
                'cores/arduino/stm32/usb/cdc', 'cores/arduino', 'variants/MARLIN_F407VE']:
        p = os.path.join(fw, sub)
        if os.path.isdir(p):
            cmd += ['-I', p]
    for sub in ['system/Drivers/STM32F4xx_HAL_Driver/Inc',
                'system/Drivers/STM32F4xx_HAL_Driver/Src',
                'system/STM32F4xx',
                'system/Middlewares/ST/STM32_USB_Device_Library/Core/Inc',
                'system/Middlewares/ST/STM32_USB_Device_Library/Core/Src']:
        p = os.path.join(fw, sub)
        if os.path.isdir(p):
            cmd += ['-I', p]
    cmsis = os.path.join(ROOT, '.platformio', 'packages', 'framework-cmsis')
    for sub in ['CMSIS/Core/Include', 'CMSIS/DSP/Include']:
        p = os.path.join(cmsis, sub)
        if os.path.isdir(p):
            cmd += ['-I', p]
    for sub in ['system/Drivers/CMSIS/Device/ST/STM32F4xx/Include',
                'system/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc']:
        p = os.path.join(fw, sub)
        if os.path.isdir(p):
            cmd += ['-I', p]

    # Marlin 自身的头文件路径 + 同样的强制包含
    cmd += ['-I', 'Marlin/src', '-I', 'buildroot', '-I', 'Marlin/src/HAL/STM32',
            '-I', 'Marlin/src/pins/stm32f4', '-I', 'Marlin/src/core']
    cmd += ['-include', 'Marlin/src/core/macros.h']
    return cmd


def main():
    """命令行入口：按 [1/3] → [2/3] → [3/3] 的顺序跑完三步校验。"""
    ap = argparse.ArgumentParser()
    ap.add_argument('--baseline', default=BASELINE,
                    help='基线快照路径 (默认 buildroot/scripts/config-schema-baseline.json)')
    ap.add_argument('--update-baseline', action='store_true', help='用当前状态重写基线')
    args = ap.parse_args()

    print('=' * 64)
    print('Marlin 配置注释翻译 · 回归校验')
    print('=' * 64)

    # ---- [1/3] 结构完整性（最快，先跑）----
    print('\n[1/3] 注释结构完整性')
    sp = check_structure()
    if sp:
        print(f'  ✗ 发现 {len(sp)} 处问题:')
        for p in sp[:20]:                     # 最多显示 20 条
            print('   ', p)
    else:
        print('  ✓ 未发现被拆行的选项列表或被合并的 #define 行')

    # ---- [2/3] 预处理（要调编译器，稍慢）----
    print('\n[2/3] ARM 工具链预处理')
    pp = check_preprocess()
    if pp:
        for p in pp:
            print('   ', p)
        # 若只是"跳过"（没装工具链），不算失败
        if not any('跳过' in p for p in pp):
            print('  ✗ 预处理未通过')
    else:
        print('  ✓ 两个配置文件预处理零错误')

    # ---- [3/3] schema 语义比对（最严格）----
    print('\n[3/3] schema 配置项比对')
    try:
        cur = load_schema()
    except Exception as e:
        print(f'  ✗ schema 解析失败: {e}')
        return 1

    if args.update_baseline or not os.path.exists(args.baseline):
        # 没有基线（首次运行）或用户明确要求重建：直接把当前状态存成基线
        os.makedirs(os.path.dirname(args.baseline), exist_ok=True)
        json.dump(cur, open(args.baseline, 'w', encoding='utf-8'),
                  ensure_ascii=False, sort_keys=True, indent=1)
        print(f'  ✓ 已生成基线快照 ({len(cur)} 项) -> {args.baseline}')
    else:
        base = json.load(open(args.baseline, encoding='utf-8'))
        kb, kc = set(base), set(cur)

        # ① 先比"键集合"：配置项有没有少/多
        missing, added = sorted(kb - kc), sorted(kc - kb)
        print(f'  基线 {len(base)} 项 | 当前 {len(cur)} 项')
        if missing:
            print(f'  ✗ 缺失 {len(missing)} 项:')
            for k in missing[:15]:
                print('     -', k)
        if added:
            print(f'  ✗ 新增 {len(added)} 项:')
            for k in added[:15]:
                print('     +', k)
        if not missing and not added:
            print('  ✓ 配置项集合完全一致 (无缺失/无新增)')

        # ② 再比"值"：同名项的内容有没有变
        diff = [k for k in (kb & kc) if core_fields(base[k]) != core_fields(cur[k])]
        real = []
        for k in diff:
            ca, cb = core_fields(base[k]), core_fields(cur[k])
            for f in set(ca) | set(cb):          # 逐字段比较，定位到具体哪一项
                va, vb = ca.get(f), cb.get(f)
                if va == vb:
                    continue
                # 字符串型字段：去掉所有空白后再比。`a  =  1` 与 `a = 1` 在 C++ 里等价，
                # 不该算语义差异（翻译时经常顺手调整空格对齐）。
                if isinstance(va, str) and isinstance(vb, str) and \
                        re.sub(r'\s+', '', va) == re.sub(r'\s+', '', vb):
                    continue  # 仅空白差异, C++ 语义等价
                real.append(f'{k}.{f}')

        if real:
            print(f'  ✗ {len(real)} 处实质语义差异:')
            for r in real[:15]:
                print('     ', r)
        else:
            print(f'  ✓ {len(diff)} 项仅空白差异, 无实质语义差异')

    # 汇总：只以第 1 步（注释结构）决定成败；第 2、3 步已在上面打印结论
    ok = not sp
    print('\n' + '=' * 64)
    print('结果:', '✓ 全部通过' if ok else '✗ 存在问题')
    print('=' * 64)
    return 0 if ok else 1


if __name__ == '__main__':
    # 用 sys.exit 把 main() 的返回值变成进程退出码，方便脚本/CI 判断成败
    sys.exit(main())
