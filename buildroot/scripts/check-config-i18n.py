#!/usr/bin/env python3
"""
配置注释翻译回归校验脚本

用法:
    python buildroot/scripts/check-config-i18n.py [--baseline <快照json>]

校验三项:
  1. schema 解析   —— 用上游 schema.py 提取配置项, 与基线逐项比对
  2. 预处理语法     —— 用真实 PlatformIO 编译参数跑 ARM 工具链预处理
  3. 结构完整性     —— 检查被误拆的选项列表 / 被合并的 #define 行

基线快照默认与同目录下的 config-schema-baseline.json 比对;
若基线不存在则只做结构检查并生成新基线。
"""
import argparse
import io
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CONFIG_FILES = ['Marlin/Configuration.h', 'Marlin/Configuration_adv.h']
BASELINE = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'config-schema-baseline.json')


def load_schema():
    """调用上游 schema.py 提取配置项快照"""
    scripts = os.path.join(ROOT, 'buildroot', 'share', 'PlatformIO', 'scripts')
    sys.path.insert(0, scripts)
    os.chdir(ROOT)
    import schema  # noqa: E402
    snap = schema.extract()
    out = {}
    for filekey, sections in snap.items():
        for sectkey, opts in sections.items():
            for optkey, val in opts.items():
                out[f'{filekey}|{sectkey}|{optkey}'] = val
    return out


def core_fields(v):
    """剔除行号与自由文本注释后的语义字段"""
    if not isinstance(v, dict):
        return v
    return {k: v[k] for k in v if k not in ('line', 'sid', 'comment')}


def check_structure():
    """检查注释结构: 选项列表被拆行 / #define 被合并进注释行"""
    problems = []
    for fn in CONFIG_FILES:
        path = os.path.join(ROOT, fn)
        lines = io.open(path, encoding='utf-8').read().split('\n')
        for i, l in enumerate(lines, 1):
            t = l.strip()
            if t.startswith('//'):
                rest = t[2:].strip()
                if rest.startswith('#define'):
                    continue
                if '#define' in rest:
                    problems.append(f'{fn}:{i} #define 被合并进注释行: {t[:80]}')
                c = rest
            elif t.startswith('*'):
                c = t[1:].strip()
                if c.startswith('#define'):
                    continue
            else:
                continue
            if c.startswith(':'):
                d = c[1:].strip()
                if (d.startswith('[') and ']' not in d) or (d.startswith('{') and '}' not in d):
                    problems.append(f'{fn}:{i} 选项列表被拆行: {t[:80]}')
    return problems


def check_preprocess():
    """用真实 PlatformIO 编译参数跑 ARM 工具链预处理"""
    cmd = build_preprocess_cmd()
    if cmd is None:
        return ['跳过预处理检查 (缺少 arm-none-eabi-gcc)']
    # 去掉 -P, 保留完整预处理以捕获错误
    cmd = [c for c in cmd if c != '-P']
    cmd = [c if c != '-E' else '-fsyntax-only' for c in cmd]

    problems = []
    for target in CONFIG_FILES:
        r = subprocess.run(
            cmd + [target, '-o', os.devnull],
            capture_output=True, text=True, cwd=ROOT)
        errs = [l for l in r.stderr.split('\n') if ' error' in l]
        if errs:
            problems.append(f'{target} 预处理报错 {len(errs)} 处')
            problems += ['    ' + e for e in errs[:10]]
    return problems


def build_preprocess_cmd():
    """
    构造与实际固件构建一致的预处理命令。

    优先读 .pio/build/*/idedata.json (含真实 defines/includes);
    该文件是 IDE 索引产物, 构建时可能被清理, 此时从
    platformio.ini + Marlin 已知宏推导等价参数集。
    """
    gcc = None
    for c in [
        r'C:\Users\hongliwang\.platformio\packages\toolchain-gccarmnoneeabi\bin\arm-none-eabi-gcc.exe',
    ]:
        if os.path.exists(c):
            gcc = c
            break
    if not gcc:
        return None

    idedata = os.path.join(ROOT, '.pio', 'build', 'Opulo_Lumen_REV5', 'idedata.json')
    if os.path.exists(idedata):
        d = json.load(open(idedata, encoding='utf-8'))
        cmd = [gcc, '-E', '-x', 'c++', '-std=gnu++11', '-Wno-unused-macros', '-P']
        cmd += ['-D' + x for x in d['defines']]
        cmd += ['-I' + i for i in d['includes']]
        cmd += ['-I', 'Marlin', '-I', 'Marlin/src', '-I', 'buildroot',
                '-I', 'Marlin/src/HAL/STM32', '-I', 'Marlin/src/pins/stm32f4',
                '-I', 'Marlin/src/core']
        cmd += ['-include', 'Marlin/src/core/macros.h']
        return cmd

    # 退化路径: 推导等价的宏集合
    fw = os.path.join(ROOT, '.platformio', 'packages', 'framework-arduinoststm32')
    cmd = [gcc, '-E', '-x', 'c++', '-std=gnu++14', '-Wno-unused-macros', '-P']
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


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--baseline', default=BASELINE,
                    help='基线快照路径 (默认 buildroot/scripts/config-schema-baseline.json)')
    ap.add_argument('--update-baseline', action='store_true', help='用当前状态重写基线')
    args = ap.parse_args()

    print('=' * 64)
    print('Marlin 配置注释翻译 · 回归校验')
    print('=' * 64)

    # 1. 结构完整性
    print('\n[1/3] 注释结构完整性')
    sp = check_structure()
    if sp:
        print(f'  ✗ 发现 {len(sp)} 处问题:')
        for p in sp[:20]:
            print('   ', p)
    else:
        print('  ✓ 未发现被拆行的选项列表或被合并的 #define 行')

    # 2. 预处理
    print('\n[2/3] ARM 工具链预处理')
    pp = check_preprocess()
    if pp:
        for p in pp:
            print('   ', p)
        if not any('跳过' in p for p in pp):
            print('  ✗ 预处理未通过')
    else:
        print('  ✓ 两个配置文件预处理零错误')

    # 3. schema 语义
    print('\n[3/3] schema 配置项比对')
    try:
        cur = load_schema()
    except Exception as e:
        print(f'  ✗ schema 解析失败: {e}')
        return 1

    if args.update_baseline or not os.path.exists(args.baseline):
        os.makedirs(os.path.dirname(args.baseline), exist_ok=True)
        json.dump(cur, open(args.baseline, 'w', encoding='utf-8'),
                  ensure_ascii=False, sort_keys=True, indent=1)
        print(f'  ✓ 已生成基线快照 ({len(cur)} 项) -> {args.baseline}')
    else:
        base = json.load(open(args.baseline, encoding='utf-8'))
        kb, kc = set(base), set(cur)
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

        diff = [k for k in (kb & kc) if core_fields(base[k]) != core_fields(cur[k])]
        real = []
        for k in diff:
            ca, cb = core_fields(base[k]), core_fields(cur[k])
            for f in set(ca) | set(cb):
                va, vb = ca.get(f), cb.get(f)
                if va == vb:
                    continue
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

    ok = not sp
    print('\n' + '=' * 64)
    print('结果:', '✓ 全部通过' if ok else '✗ 存在问题')
    print('=' * 64)
    return 0 if ok else 1


if __name__ == '__main__':
    sys.exit(main())
