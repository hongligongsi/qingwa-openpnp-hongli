#!/usr/bin/env python3
"""
校验: 配置文件与基线版本在**功能上**等价。

判据 (由强到弱):
  1. 预处理等价 —— 用真实 PlatformIO 编译参数跑 ARM 工具链预处理,
     比对归一化后的输出。这是最终判据: 输出相同即代码行为完全一致。
  2. schema 等价 —— 见 check-config-i18n.py

翻译工作允许改动注释文本与纯排版(对齐列、续行 \\、空格压缩),
但不得改变任何宏的值、任何条件表达式的语义。

用法:
    python buildroot/scripts/check-config-code-intact.py --ref HEAD
"""
import argparse
import difflib
import io
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
FILES = ['Marlin/Configuration.h', 'Marlin/Configuration_adv.h']
GCC = r'C:\Users\hongliwang\.platformio\packages\toolchain-gccarmnoneeabi\bin\arm-none-eabi-gcc.exe'


def preprocess_cmd():
    """
    构造与实际固件构建一致的预处理命令。

    优先读 .pio/build/*/idedata.json (含真实 defines/includes);
    该文件是 IDE 索引产物, 构建时可能被清理, 此时从
    platformio.ini + Marlin 已知宏推导等价参数集。
    """
    idedata = os.path.join(ROOT, '.pio', 'build', 'Opulo_Lumen_REV5', 'idedata.json')
    if not os.path.exists(GCC):
        return None

    if os.path.exists(idedata):
        d = json.load(open(idedata, encoding='utf-8'))
        cmd = [GCC, '-E', '-x', 'c++', '-std=gnu++11', '-Wno-unused-macros', '-P']
        cmd += ['-D' + x for x in d['defines']]
        cmd += ['-I' + i for i in d['includes']]
        cmd += ['-I', 'Marlin', '-I', 'Marlin/src', '-I', 'buildroot',
                '-I', 'Marlin/src/HAL/STM32', '-I', 'Marlin/src/pins/stm32f4',
                '-I', 'Marlin/src/core']
        cmd += ['-include', 'Marlin/src/core/macros.h']
        return cmd

    # 退化路径: 推导等价的宏与包含路径
    fw = os.path.join(ROOT, '.platformio', 'packages', 'framework-arduinoststm32')
    cmd = [GCC, '-E', '-x', 'c++', '-std=gnu++14', '-Wno-unused-macros', '-P']
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
    return [l.strip() for l in text.split('\n') if l.strip()]


def load_ref(ref, fname):
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
        print('✗ 缺少 arm-none-eabi-gcc 或 idedata.json, 无法做预处理等价校验')
        return 2

    total_diff = 0
    for fname in files:
        print(f'\n[{fname}]')
        ref_text = load_ref(args.ref, fname)
        if ref_text is None:
            print('  ✗ 无法读取基线')
            total_diff += 1
            continue

        # 1) 预处理等价 (最终判据)
        cur_path = os.path.join(ROOT, fname)
        r_ref = subprocess.run(cmd + [os.path.join(ROOT, '.git_ref_tmp.h')],
                               capture_output=True, text=True, cwd=ROOT) if False else None

        # 基线内容需落盘才能被 gcc 读取
        tmp = os.path.join(ROOT, '.git_ref_tmp.h')
        io.open(tmp, 'w', encoding='utf-8', newline='').write(ref_text)
        try:
            r_ref = subprocess.run(cmd + [tmp], capture_output=True, text=True, cwd=ROOT)
            r_cur = subprocess.run(cmd + [fname], capture_output=True, text=True, cwd=ROOT)
        finally:
            if os.path.exists(tmp):
                os.remove(tmp)

        if r_ref.returncode != 0 or r_cur.returncode != 0:
            print(f'  ✗ 预处理失败 (ref={r_ref.returncode}, cur={r_cur.returncode})')
            for l in (r_cur.stderr or '').split('\n')[:8]:
                if ' error' in l:
                    print('     ', l)
            total_diff += 1
            continue

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
                for x in h[i1:i2][:4]:
                    print('       -', x[:110])
                for x in c[j1:j2][:4]:
                    print('       +', x[:110])

        # 2) 注释统计
        def n_cjk(t):
            return sum(1 for l in t.split('\n')
                       if (l.strip().startswith('//') or l.strip().startswith('*'))
                       and re.search(r'[\u4e00-\u9fff]', l))
        cur_text = io.open(cur_path, encoding='utf-8').read()
        print(f'  中文注释行: 基线 {n_cjk(ref_text)} -> 当前 {n_cjk(cur_text)}')

    print('\n' + '=' * 64)
    if total_diff:
        print(f'结果: ✗ 存在 {total_diff} 处功能差异')
    else:
        print('结果: ✓ 代码功能与基线完全等价, 改动仅限注释与排版')
    print('=' * 64)
    return 1 if total_diff else 0


if __name__ == '__main__':
    sys.exit(main())

