#!/usr/bin/env python3
"""
功能等价性校验：改完配置/注释后，代码行为是否和基线版本**完全一样**。
================================================================================

【初学者导读：这个脚本凭什么能证明"什么都没变"？】

假设你把 `Configuration.h` 里 200 行英文注释翻成了中文，还顺手把 `=` 前后的空格
对齐了一下。你担心的问题是：**除了注释和空格，我有没有不小心动了真正的代码？**

肉眼比对 800 多行不现实。这里用了一个很巧的思路 —— **让编译器替你比对**。

C 语言在真正编译之前有个"预处理"阶段，做三件事：
    ① 把 `#include "xxx.h"` 原地替换成那个文件的内容（递归展开）
    ② 把 `#define X 42` 后面的 X 全部替换成 42
    ③ 处理 `#if / #ifdef` 条件编译，只留下生效的分支

**关键点：预处理会把所有注释和空白都扔掉。** 所以预处理之后的输出，
就是"这台机器真正会编译的代码"，跟注释写成什么样完全无关。

但这里有个**必须知道的盲区**（很多人会想当然）：
    `Configuration.h` 这类文件几乎全是 `#define`，而 `#define` 本身在预处理后
    就消失了——没人展开它，输出里就看不见它的值。实测把 `Y_CURRENT 1000`
    改成 `1234`，预处理输出**一字不差**。
    所以只比预处理输出，是抓不到"宏值被改"的。

真正可靠的做法是**两步一起用**：
    ① 预处理输出比对 → 抓"语法坏了、条件编译分支变了、代码行被删/改"
    ② 宏定义表比对   → 抓"某个 #define 的值被改了 / 整个宏丢了"
    两步都通过，才敢说功能等价。

【初学者小实验（想验证的话自己做一遍）】
    把某个 `#define XXX 100` 改成 `200`，跑本脚本 → 第 ② 步会报"改值"；
    把某行注释里的 `:[...]` 拆成两行 → 第 ① 步可能仍通过，但
    `check-config-i18n.py` 的结构检查会报错。三个脚本合起来才完整。

【三层判据，由强到弱】
    1. 宏定义表 + 预处理等价（本脚本）—— 值没变、代码结构没变。
    2. schema 等价（check-config-i18n.py）—— 配置项集合与语义值一致。
    3. 结构完整性（同上）—— 注释里的机器可读标记没被破坏。

【允许改什么、不许改什么】
    允许：注释文字、纯排版（列对齐、续行 `\\`、空格压缩）
    禁止：任何宏的**值**、任何条件表达式的**语义**

【怎么用？】
    python buildroot/scripts/check-config-code-intact.py --ref HEAD
        --ref 指定对比基线（git 提交号 / 分支名 / HEAD 都行）
        --files 可指定只校验某些文件
    退出码 0 = 完全等价；1 = 有差异；2 = 环境缺工具链，没法判定。
"""
import argparse
import difflib
import io
import json
import os
import re
import subprocess
import sys

# ROOT：仓库根目录（本脚本在 buildroot/scripts/ 下，往上三层即根）
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
FILES = ['Marlin/Configuration.h', 'Marlin/Configuration_adv.h']

# ARM 交叉编译器（本机绝对路径；换机器要改这里）
GCC = r'C:\Users\hongliwang\.platformio\packages\toolchain-gccarmnoneeabi\bin\arm-none-eabi-gcc.exe'


def preprocess_cmd():
    """
    拼出"和真实固件构建一致"的预处理命令。

    为什么必须和真实构建一致？
        预处理结果取决于宏（-D）和包含路径（-I）。差一个宏，`#if` 就会走不同分支，
        两边输出自然对不上，校验就变成"假阳性"。所以这里尽量照搬 PlatformIO 的参数：
          ① 有 .pio/build/Opulo_Lumen_REV5/idedata.json → 直接用它记录的 defines/includes
          ② 没有（.pio 被清理）→ 按 platformio.ini + Marlin 已知宏手工推导等价集合

    返回 None 表示找不到编译器，调用方会以退出码 2 结束。
    """
    # 基线文件要先落盘才能交给 gcc，落盘位置放在仓库根（cwd 也在根，路径好处理）
    idedata = os.path.join(ROOT, '.pio', 'build', 'Opulo_Lumen_REV5', 'idedata.json')
    if not os.path.exists(GCC):
        return None

    # --- 路线①：PlatformIO 的真实构建参数 ---
    if os.path.exists(idedata):
        d = json.load(open(idedata, encoding='utf-8'))
        # -E: 只预处理；-x c++: 按 C++ 解析；-P: 输出里不要行号标记（否则行号差异会干扰比对）
        cmd = [GCC, '-E', '-x', 'c++', '-std=gnu++11', '-Wno-unused-macros', '-P']
        cmd += ['-D' + x for x in d['defines']]
        cmd += ['-I' + i for i in d['includes']]
        cmd += ['-I', 'Marlin', '-I', 'Marlin/src', '-I', 'buildroot',
                '-I', 'Marlin/src/HAL/STM32', '-I', 'Marlin/src/pins/stm32f4',
                '-I', 'Marlin/src/core']
        # 强制先包含 macros.h：Marlin 的配置大量依赖里面的工具宏
        cmd += ['-include', 'Marlin/src/core/macros.h']
        return cmd

    # --- 路线②：退化路径，手工推导等价的宏与包含路径 ---
    fw = os.path.join(ROOT, '.platformio', 'packages', 'framework-arduinoststm32')
    cmd = [GCC, '-E', '-x', 'c++', '-std=gnu++14', '-Wno-unused-macros', '-P']

    # 这些是 PlatformIO 构建 Opulo_Lumen_REV5 时固定会传的宏（板型、主频、串口缓冲…）
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

    # 包含路径统一用"存在才加"（os.path.isdir 判断）：
    # 不同机器上库版本/目录结构略有差异，缺路径时跳过而不是直接报错。
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
    cmd += ['-I', 'Marlin/src', '-I', 'buildroot', '-I', 'Marlin/src/HAL/STM32',
            '-I', 'Marlin/src/pins/stm32f4', '-I', 'Marlin/src/core']
    cmd += ['-include', 'Marlin/src/core/macros.h']
    return cmd


def norm_pp(text):
    """
    归一化预处理输出：每行 strip 掉首尾空白，丢弃空行。

    为什么要去空白？
        翻译时经常顺手调整缩进/对齐，预处理输出里也会残留这些空白。
        它们对编译器毫无意义，但对文本比较是噪声——先统一抹掉，只比"实质内容"。
    """
    return [l.strip() for l in text.split('\n') if l.strip()]


def _strip_comments(line, in_block):
    """
    去掉一行里的注释，返回 (去注释后的代码, 是否仍在块注释中)。

    为什么要自己写而不用正则？
        因为字符串里的 `//`（比如 "http://..."）不是注释，直接 `line.split('//')`
        会切错。这里用一个小状态机逐字符扫描：
            - 在 /* */ 块注释里 → 吃掉字符直到 */
            - 在字符串里（"..." 或 '...'）→ 原样保留，遇反斜杠转义的字符一起保留
            - 遇到 // → 本行剩余部分全是注释，直接结束
            - 遇到 /* → 进入块注释状态（可能跨行，所以状态要由调用方传进传出）
    """
    res = []
    i, n = 0, len(line)
    in_str = None          # 当前所在的字符串引号类型，None 表示不在字符串里
    while i < n:
        ch = line[i]

        if in_block:                       # —— 块注释内 ——
            if line.startswith('*/', i):
                in_block = False
                i += 2
            else:
                i += 1
            continue

        if in_str:                         # —— 字符串内 ——
            res.append(ch)
            if ch == '\\' and i + 1 < n:   # 转义字符：连同下一个字符一起保留
                res.append(line[i + 1])
                i += 2
                continue
            if ch == in_str:               # 遇到配对的引号，字符串结束
                in_str = None
            i += 1
            continue

        # —— 普通代码区 ——
        if ch in ('"', "'"):
            in_str = ch
            res.append(ch)
            i += 1
            continue
        if line.startswith('//', i):
            break                          # 行注释：后面全不要
        if line.startswith('/*', i):
            in_block = True
            i += 2
            continue
        res.append(ch)
        i += 1

    return ''.join(res), in_block


def macro_map(text):
    """
    把文件里的 `#define 名字 值` 抽成字典 {'名字': '归一化的值'}，用来抓"值被改"。

    处理了四件容易踩的事：
      1. **续行**：`#define X { 1, \\` 下一行继续 —— 先把 `\\` 结尾的行合并成一行，
         否则值会被截断，两边比不出真实差异。
      2. **注释**：`#define X 1  // 说明` 和 `//#define X 1`（被注释掉的宏）都要正确排除。
      3. **空白归一**：值里的连续空格/制表符压成一个空格，避免"只是对齐不同"被误报。
      4. **#undef**：出现 `#undef X` 就把 X 从表里删掉，语义与预处理一致。

    注意：这里只做"文本层面"的提取，不判断宏在 `#if 0` 里是否生效——
    对"翻译不该改值"这个目的来说，文本一致就足够了。
    """
    # —— 第 1 步：合并续行 ——
    joined, buf = [], ''
    for raw in text.split('\n'):
        raw = raw.rstrip('\r')
        if raw.rstrip().endswith('\\'):                  # 行尾反斜杠 = 续行
            buf += raw.rstrip()[:-1] + ' '
            continue
        buf += raw
        joined.append(buf)
        buf = ''
    if buf:
        joined.append(buf)

    # —— 第 2 步：逐行去注释 + 抓 #define / #undef ——
    out, in_block = {}, False
    for raw in joined:
        code, in_block = _strip_comments(raw, in_block)
        s = code.strip()

        m = re.match(r'#\s*define\s+([A-Za-z_]\w*)(.*)$', s)
        if m:
            name, val = m.group(1), re.sub(r'\s+', ' ', m.group(2)).strip()
            out[name] = val
            continue

        m = re.match(r'#\s*undef\s+([A-Za-z_]\w*)', s)
        if m:
            out.pop(m.group(1), None)
    return out


def load_ref(ref, fname):
    """
    用 `git show <ref>:<file>` 把基线版本的**文件内容**取出来（不切换工作区）。

    好处：对比时不用 checkout，不会因为忘记还原而把工作区搞脏。
    取不到（比如该提交里没有这个文件）返回 None。
    """
    r = subprocess.run(['git', 'show', f'{ref}:{fname}'],
                       capture_output=True, cwd=ROOT)
    if r.returncode != 0:
        return None
    return r.stdout.decode('utf-8')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--ref', default='HEAD', help='参考版本 (git ref)')
    ap.add_argument('--files', nargs='+', default=None,
                    help='待校验的配置文件 (默认: 主板激活配置两个文件)')
    args = ap.parse_args()
    files = args.files or FILES

    print('=' * 64)
    print(f'功能等价性校验: 当前工作区 vs {args.ref}')
    print('=' * 64)

    cmd = preprocess_cmd()
    if cmd is None:
        print('✗ 缺少 arm-none-eabi-gcc, 无法做预处理等价校验')
        return 2                                  # 2 = 环境不满足，不是"代码有问题"

    total_diff = 0
    for fname in files:
        print(f'\n[{fname}]')
        ref_text = load_ref(args.ref, fname)
        if ref_text is None:
            print('  ✗ 无法读取基线')
            total_diff += 1
            continue

        # ---- 1) 预处理等价（最终判据）----
        cur_path = os.path.join(ROOT, fname)

        # gcc 只认磁盘上的文件，所以把基线内容先写成临时文件，用完立刻删
        tmp = os.path.join(ROOT, '.git_ref_tmp.h')
        io.open(tmp, 'w', encoding='utf-8', newline='').write(ref_text)
        try:
            r_ref = subprocess.run(cmd + [tmp], capture_output=True, text=True, cwd=ROOT)
            r_cur = subprocess.run(cmd + [fname], capture_output=True, text=True, cwd=ROOT)
        finally:
            # finally 保证即使预处理中途抛异常，临时文件也会被清理
            if os.path.exists(tmp):
                os.remove(tmp)

        if r_ref.returncode != 0 or r_cur.returncode != 0:
            print(f'  ✗ 预处理失败 (ref={r_ref.returncode}, cur={r_cur.returncode})')
            for l in (r_cur.stderr or '').split('\n')[:8]:
                if ' error' in l:
                    print('     ', l)
            total_diff += 1
            continue

        # 归一化后逐行比对。SequenceMatcher 会把"连续相同的行"当成 equal 块，
        # 只把真正变化的部分报成 replace/delete/insert，输出比逐行 diff 干净。
        h, c = norm_pp(r_ref.stdout), norm_pp(r_cur.stdout)
        sm = difflib.SequenceMatcher(None, h, c, autojunk=False)
        ops = [o for o in sm.get_opcodes() if o[0] != 'equal']
        if not ops:
            print(f'  ✓ 预处理输出完全一致 ({len(c)} 行) —— 代码功能等价')
        else:
            total_diff += len(ops)
            print(f'  ✗ 预处理输出有 {len(ops)} 处差异:')
            for tag, i1, i2, j1, j2 in ops[:10]:
                print(f'     [{tag}]')
                for x in h[i1:i2][:4]:            # 旧版本这边的内容（最多 4 行）
                    print('       -', x[:110])
                for x in c[j1:j2][:4]:            # 新版本这边的内容
                    print('       +', x[:110])

        # ---- 2) 宏定义表比对（抓"值被改"）----
        # 为什么单独做这一步：预处理输出里看不到"定义了但没人展开"的宏，
        # 而配置文件的绝大部分内容正是这种宏。所以必须文本层面再比一次。
        cur_text = io.open(cur_path, encoding='utf-8').read()
        ma, mb = macro_map(ref_text), macro_map(cur_text)
        removed = sorted(set(ma) - set(mb))          # 基线有、现在没了（宏被删）
        added = sorted(set(mb) - set(ma))            # 现在多了（新增宏）
        changed = sorted(k for k in set(ma) & set(mb) if ma[k] != mb[k])  # 同名但值变了

        if removed or added or changed:
            total_diff += len(removed) + len(added) + len(changed)
            print(f'  ✗ 宏定义表有差异 (基线 {len(ma)} 个 → 当前 {len(mb)} 个):')
            for k in removed[:10]:
                print(f'     - 删除 {k} = {ma[k][:60]}')
            for k in added[:10]:
                print(f'     + 新增 {k} = {mb[k][:60]}')
            for k in changed[:10]:
                print(f'     ~ 改值 {k}: {ma[k][:50]}  →  {mb[k][:50]}')
        else:
            print(f'  ✓ 宏定义表完全一致 ({len(ma)} 个宏, 无增删改)')

        # ---- 3) 中文注释行数统计（纯参考信息，不参与判定）----
        # 作用：顺手看翻译进度——从多少行译到了多少行。
        def n_cjk(t):
            return sum(1 for l in t.split('\n')
                       if (l.strip().startswith('//') or l.strip().startswith('*'))
                       and re.search(r'[\u4e00-\u9fff]', l))
        print(f'  中文注释行: 基线 {n_cjk(ref_text)} -> 当前 {n_cjk(cur_text)}')

    print('\n' + '=' * 64)
    if total_diff:
        print(f'结果: ✗ 存在 {total_diff} 处功能差异')
    else:
        print('结果: ✓ 代码功能与基线完全等价, 改动仅限注释与排版')
    print('=' * 64)
    return 1 if total_diff else 0


if __name__ == '__main__':
    # 退出码即结论：0 等价 / 1 有差异 / 2 环境不满足
    sys.exit(main())
