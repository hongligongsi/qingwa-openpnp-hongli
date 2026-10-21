<p align="center">
  <b>🐸 Qingwa PnP Firmware · qingwa-pnp-marlin</b><br/>
  A pick-and-place firmware based on Marlin 2.1.x + the Opulo LumenPnP REV5 board
</p>

<p align="center">
  <a href="LICENSE"><img src="https://img.shields.io/badge/Code-GPL--3.0-blue.svg" alt="Code: GPL-3.0"></a>
  
  <a href="#-credits--license"><img src="https://img.shields.io/badge/HW-CERN--OHL--W%202.0-green.svg" alt="Hardware: CERN-OHL-W 2.0"></a>
  
  <a href="#-credits--license"><img src="https://img.shields.io/badge/Docs-CC%20BY--SA%204.0-blueviolet.svg" alt="Docs: CC BY-SA 4.0"></a>
  <img src="https://img.shields.io/badge/Marlin-2.1.x-important.svg" alt="Marlin 2.1.x">
  <img src="https://img.shields.io/badge/Board-LumenPnP%20REV5-success.svg" alt="LumenPnP REV5">
  <img src="https://img.shields.io/badge/MCU-STM32F407VET6-informational.svg" alt="STM32F407VET6">
  <img src="https://img.shields.io/badge/Build-PlatformIO-orange.svg" alt="PlatformIO">
</p>

<p align="center"><a href="README.md">简体中文</a> | <strong>English</strong></p>

---

## Table of Contents

- [📖 Introduction](#-introduction)
- [🧩 System Architecture: One Source Tree, Two Firmwares](#-system-architecture-one-source-tree-two-firmwares)
- [✨ Features](#-features)
- [🧱 Hardware & Pinout](#-hardware--pinout)
- [🏗 Repository Layout](#-repository-layout)
- [🚀 Quick Start](#-quick-start)
- [⚙️ Building & Flashing](#️-building--flashing)
- [🔧 Configuration & Versioning](#-configuration--versioning)
- [🧰 Common G-code](#-common-g-code)
- [🛠 FAQ](#-faq)
- [🤝 Credits & License](#-credits--license)

---

## 📖 Introduction

This project is the firmware for the **Qingwa (Frog) Pick-and-Place machine**. It is
*not* a 3D-printer firmware — it adapts the open-source **Marlin** firmware into the
**motion controller** of an SMT pick-and-place (PnP) machine.

### What makes up the machine?

A complete Qingwa PnP machine has two major parts, each running its own firmware
built from the **same source tree**:

1. **Motherboard** — the "brain and limbs" of the machine. Based on the
   **Opulo LumenPnP Motherboard REV05** (MCU: **STM32F407VET6**, ARM Cortex-M4,
   512 KB Flash / 192 KB SRAM), it drives gantry X/Y positioning, Z lift,
   dual-motor sync (X/Y2), endstop sensing, and camera/lighting/vacuum peripherals.
   It is the **default build target** of this repo.

2. **Feeder (electric tape feeder)** — indexes component tape pockets into the pick
   position. Each feeder contains an **Opulo feeder controller board (REV3 or
   REV4)**, also running Marlin, using rotational axes to drive the sprocket wheel.
   Feeder firmware is built from the `rev*-feeder-config` snapshots in this repo
   (see the tutorial below).

The firmware talks G-code / status over USB serial, so it can be driven by host
software such as OpenPnP for automated assembly jobs. The host sees **the motherboard
and each feeder as separate serial devices**.

> This repository is customized from upstream **Marlin 2.1.x** and the
> **Opulo LumenPnP** open hardware/software ecosystem, keeping Marlin's powerful
> motion planning and HAL architecture while adding the Opulo board definitions and
> per-revision configuration snapshots.

### What does the motherboard firmware remove?

To behave as a pure motion controller, the build removes 3D-printing logic at the
configuration level:

| Item | This firmware |
|------|---------------|
| `EXTRUDERS` | `0` (no extruder) |
| Temperature sensors | all disabled (no heating / heated bed / fan control) |
| Axis mapping | X / Y / Y2 / Z / I / J (six steppers) |
| Driver type | TMC2209 on all axes (single-wire UART) |
| Serial | USB CDC (`SERIAL_PORT -1`) @ 250000 |

---

## 🧩 System Architecture: One Source Tree, Two Firmwares

This repo maintains **a single Marlin source tree**; both the motherboard firmware
and the feeder firmware are built from it — the only difference is which
**configuration files** (`Configuration.h` / `Configuration_adv.h`) and which
**build environment (env)** are used:

```
                  ┌────────────────────────────────┐
                  │   Host (OpenPnP) / manual G-code │
                  └──────┬──────────────────┬──────┘
              USB serial │                  │ USB serial (one port per feeder)
                         ▼                  ▼
              ┌──────────────────┐  ┌──────────────────┐
              │ Motherboard fw   │  │ Feeder firmware ×N│
              │ REV5 controller  │  │ REV3/REV4 ctrl   │
              │ env: REV5        │  │ env: REV3/REV4   │
              │ cfg: Marlin/ root│  │ cfg: rev*-feeder-config/ │
              ├──────────────────┤  ├──────────────────┤
              │ · X/Y/Y2 gantry  │  │ · rotational axes │
              │ · Z lift         │  │   drive sprockets │
              │ · endstops/DIAG  │  │ · feed/rewind     │
              │ · camera/LED/vac │  │ · EXTRUDERS 0     │
              └──────────────────┘  └──────────────────┘
```

**Which firmware do I pick?**

| Target | env | Config |
|---|---|---|
| Machine motherboard (REV05) | `Opulo_Lumen_REV5` (default, just `pio run`) | `Marlin/` root (nothing to do) |
| Feeder (REV4 controller) | `Opulo_Lumen_REV4` | one of `rev4-v3.0 / v3.1 / v3.1-pwm-aux` |
| Feeder (REV3 controller, legacy) | `Opulo_Lumen_REV3` | `rev3-feeder-config` |

How to choose among the four feeder configs:

- `rev4-v3.0-feeder-config`: v3.0 hardware, conservative feed speed (200 mm/s);
- `rev4-v3.1-feeder-config`: v3.1 hardware, feed speed raised to 1000 mm/s;
- `rev4-v3.1-feeder-pwm-aux-config`: same as v3.1 plus `FAST_PWM_FAN`
  (AUX fan at 31.4 kHz, eliminates whine);
- `rev3-feeder-config`: legacy REV3 feeder controller (substantially different
  pins/features from the REV4 series).

---

## ✨ Features

- **Six independent steppers**: X / Y / Y2 / Z / I / J, each with dedicated
  STEP/DIR/EN pins and single-wire TMC UART readback (soft-serial @ 19200 baud).
  All axes use **TMC2209**.
- **Stall/DIAG detection pins**: DIAG for all six axes are routed out for
  stall/blockage detection by the host.
- **Pure motion / I/O controller**: `EXTRUDERS 0`, all temperature sensors off —
  heating-related code paths are removed so timers/interrupts stay focused on motion.
- **Complete on-board peripheral definitions**:
  - X / Y / Z limit switches
  - 4 fan / driver outputs (`FAN0`–`FAN3`) and a buzzer
  - Dual **NeoPixel** RGB strips (`PC7` / `PC8`)
  - 8-pin **AUX** port: 3×PWM + 1×analog input + I²C (SCL/SDA)
  - **RS485** TX/RX enable pins (external feeders / comm boards)
  - 4 ID pins (`PD0`–`PD3`) for hardware-revision detection
- **Parameter storage**: SRAM EEPROM emulation (8 KB) is prepared at board level,
  but `EEPROM_SETTINGS` is **disabled** by default, so `M500` does not persist —
  see "Common G-code → Parameter storage".
- **Full G-code compatibility**: the complete Marlin G/M command set with its fast
  parser is preserved.
- **Per-revision configuration snapshots**: REV3 / REV4 plus feeder revisions
  (v3.0 / v3.1 / PWM-AUX) are kept for reference, regression and upgrades.
- **Marlin 2.1 ecosystem**: HAL layering (STM32 HAL used here), one-command
  PlatformIO builds, upstream CI workflows and Auto Build scripts.

---

## 🧱 Hardware & Pinout

### Board information

| Item | Value |
|------|-------|
| Board name (M115) | `LumenPnP Motherboard REV05` |
| Machine name | `LumenPnP` |
| MCU | STM32F407VET6 (ARM Cortex-M4 @ 168 MHz) |
| Flash / SRAM | 512 KB / 192 KB |
| Driver interface | 6 × TMC2209 (single-wire UART) |

### Complete pin map (from `Marlin/src/pins/stm32f4/pins_OPULO_LUMEN_REV5.h`)

Every pin is defined in that single header. "Status" means whether this firmware
config actually uses it.

**① Stepper motors (6 × TMC2209, single-wire UART)**

| Axis | STEP | DIR | ENABLE | UART (TX=RX) | DIAG | Status |
|------|------|-----|--------|--------------|------|--------|
| X | `PB15` | `PB14` | `PD9` | `PD8` | `PB10` | active |
| Y | `PE15` | `PE14` | `PB13` | `PB12` | `PB11` | active |
| Y2 | `PD6` | `PD7` | `PA3` | `PA2` | `PC12` | active (dual Y) |
| Z | `PE7` | `PB1` | `PE9` | `PE8` | `PB5` | active |
| A (I axis) | `PC4` | `PA4` | `PB0` | `PC5` | `PC10` | active (rotary) |
| B (J axis) | `PE11` | `PE10` | `PE13` | `PE12` | `PC11` | active (rotary) |

UART is **single-wire half duplex**: TX and RX are the same pin, talking over the
TMC2209 PDN_UART line at a fixed `19200` baud (lower rate for reliability). Note
Y2 is really enabled (`Y2_DRIVER_TYPE TMC2209` in `Configuration.h`), so the
machine has 6 motors, not 5.

**② Endstops and homing**

| Axis | Pin | Notes |
|------|-----|-------|
| X min | `PC6` | physical switch |
| Y min | `PD15` | physical switch |
| Z min | `PD14` | physical switch |

`SENSORLESS_HOMING` is currently off, so although the DIAG pins are wired, homing
uses the physical switches. Enabling it requires turning that macro on and tuning
`X/Y_STALL_SENSITIVITY`.

**③ Fans / buzzer / LEDs**

| Function | Pin | Status |
|----------|-----|--------|
| FAN0 (`M106 P0`) | `PB8` | active (`FAN_COUNT` = 4) |
| FAN1 (`M106 P1`) | `PB9` | active |
| FAN2 (`M106 P2`) | `PE5` | active |
| FAN3 (`M106 P3`) | `PE6` | active |
| Controller fan (auto) | `PE2` | active, spins whenever a motor is enabled |
| Buzzer | `PA7` | active (`SPEAKER`) |
| NeoPixel strip | `PC7` | active, 18 LEDs, `NEO_GRB` |
| Second NeoPixel | `PC8` | defined but unused (`NEOPIXEL2_SEPARATE` off) |

**④ Buses**

| Bus | Pins | Purpose |
|-----|------|---------|
| SPI | MISO `PB4` / MOSI `PB5` / SCK `PB3` | spare TMC SPI mode (UART is used instead) |
| I²C | SDA `PB7` / SCL `PB6` | I²C peripherals, also on the AUX port |
| RS485 | TX enable `PD11` / RX enable `PD12` | feeder / peripheral comms |

> ⚠️ `PB5` is shared between `Z_DIAG_PIN` and `MOSI_PIN`. Harmless here because the
> TMCs use UART rather than SPI; if you attach an SPI device, Z sensorless homing
> would need a different pin.

**⑤ Board ID and system pins**

| Function | Pins | Notes |
|----------|------|-------|
| Board revision ID | `PD0` / `PD1` / `PD2` / `PD3` | set input pullup before reading (`M42`/`M43` examples at the end of the header) |
| General IO (AUX control) | `PD13` | writable and readable |
| USB | `PA11` / `PA12` | fixed by the MCU, virtual serial port |
| SWD debug | `PA13` / `PA14` | ST-Link flashing / debugging |
| EEPROM | none on board | SRAM emulation, 8 KB (`MARLIN_EEPROM_SIZE 0x2000`), but `EEPROM_SETTINGS` is off |

**⑥ Unassigned pins**

`PA0`, `PA1`, `PA8`–`PA10`, `PB2` (BOOT1), `PC1`–`PC3`, `PC9`, `PC13`–`PC15`,
`PD4`, `PD5`, `PD10`, `PE0`, `PE1`, `PE3`, `PE4` are free in the pin header —
handy for custom additions such as extra sensors or pneumatic valves.

### Kinematics & travel parameters (from `Marlin/Configuration.h`)

| Parameter | Value | Notes |
|------|-----|------|
| Steps/mm | `320, 320, 40, 4.44, 4.44` | X / Y / Z / I / J |
| X travel | 0 – 433 mm | homes to min end (`X_HOME_DIR -1`) |
| Y travel | 0 – 487 mm | homes to min end |
| Z travel | 0 – 63 mm | homes to min end, lifts to 21 mm after homing (`Z_AFTER_HOMING`) |
| I / J travel | 0 – 720 (rotation, degrees) | no homing (`I/J_HOME_DIR 0`) |
| Default speeds | `7000, 7000, 1000, 50000, 50000` mm/s | X / Y / Z / I / J |
| X/Y/Y2 coupling | X + Y + Y2 dual-motor sync | gantry; Y2 follows Y |

> I / J are **rotational axes** (`AXIS4_ROTATES` / `AXIS5_ROTATES` in the
> config), referenced in G-code by the letters **`A`** / **`B`**, range
> 0–720° (about two turns); query with `M114`, test with `G1 A90`.
> Y2 is the second Y driver (its own TMC2209 STEP/DIR/EN) for gantry
> dual-motor sync.

### Connecting to the OpenPnP host

- **Interface**: USB CDC virtual serial (`SERIAL_PORT -1`); baud is nominal —
  align on `250000` for consistency;
- **Identify**: send `M115` after connecting — it should report the machine
  name `LumenPnP` and firmware version;
- **Motion commands**: standard `G0/G1` + `G28` homing + `M119` endstop query,
  fully compatible with the Marlin command set;
- **Parameter storage**: ⚠️ `EEPROM_SETTINGS` is **not enabled** in this firmware, so
  `M500` answers `EEPROM disabled`; runtime changes (`M92`, `M906`, ...) are lost on
  reboot. Enable that macro in `Configuration.h` and rebuild if you need persistence;
- Each feeder appears to the host as an **independent serial device** (each
  flashed with the feeder firmware).

### REV05 AUX port (8-pin)

```
             _________
      3.3V  |  1   2  |  GND
    PWM1 PA5|  3   4  | PC0 A1 (analog in)
    PWM2 PA6|  5   6  | SCL
    PWM3 PA15| 7   8  | SDA
             ---------
```

---

## 🏗 Repository Layout

This repo ships **two firmware programs** sharing the same Marlin source tree;
they differ only in configuration files and the PlatformIO environment (env):

| Program | Target hardware | MCU | Build env | Config source |
|---|---|---|---|---|
| **Motherboard firmware** | LumenPnP Motherboard REV5 (PnP main board) | STM32F407VET6 | `Opulo_Lumen_REV5` (default) | Active config in `Marlin/` root (snapshot: `rev5-config/`) |
| **Feeder firmware** | Electric feeder, REV4 controller | STM32F407VET6 | `Opulo_Lumen_REV4` | One of the three `Marlin/rev4-*-feeder-config/` folders |
| **Feeder firmware (legacy)** | Electric feeder, REV3 controller | STM32F407VET6 | `Opulo_Lumen_REV3` | `Marlin/rev3-feeder-config/` |

Board definitions (pins / clock / upload protocol) live in
`buildroot/share/PlatformIO/boards/marlin_opulo_lumen_rev{3,4,5}.json`;
pin maps in `Marlin/src/pins/stm32f4/pins_OPULO_LUMEN_REV{3,4,5}.h`.

```text
qingwa-pnp-marlin/
├── .devcontainer/              # VS Code dev container (build env in one click)
├── .github/                    # GitHub CI / community config (test-builds etc.)
├── .trellis/                   # AI-assisted development workflow scaffold (optional)
├── Marlin/                     # ⭐ Firmware source & configuration (shared by both)
│   ├── Configuration.h         #   Active configuration = Motherboard REV5
│   ├── Configuration_adv.h     #   Advanced configuration
│   ├── config.ini              #   Compile-time config via ini (disabled by default)
│   ├── Makefile                #   Make entry for pio/arduino
│   ├── Version.h               #   Version strings (overridable at build time)
│   │
│   │   ── Motherboard configuration ──
│   ├── rev5-config/            #   REV5 motherboard snapshot (reference/archive)
│   │
│   │   ── Feeder configurations (pick one) ──
│   ├── rev3-feeder-config/     #   Feeder REV3 controller (legacy feeder)
│   ├── rev4-v3.0-feeder-config/#   Feeder REV4 controller + feeder v3.0 (slow params)
│   ├── rev4-v3.1-feeder-config/#   Feeder REV4 controller + feeder v3.1 (fast params)
│   ├── rev4-v3.1-feeder-pwm-aux-config/  # Same as v3.1 + FAST_PWM_FAN (AUX fan 31.4 kHz)
│   │
│   └── src/                    #   Marlin core source (shared, board-agnostic)
│       ├── MarlinCore.cpp|.h   #     Firmware entry point
│       ├── HAL/                #     Hardware Abstraction Layer (STM32 etc.)
│       ├── core/               #     boards.h board IDs / macros
│       ├── pins/               #     Per-board pin definitions
│       │   └── stm32f4/pins_OPULO_LUMEN_REV5.h   # ← REV5 pins (REV3/REV4 also present)
│       ├── module/             #     planner / stepper / endstop …
│       ├── gcode/              #     G/M-code parsing & execution
│       ├── feature/ libs/ lcd/ sd/ inc/ tests/
├── buildroot/                  # PlatformIO board support / scripts / tests
│   ├── share/PlatformIO/
│   │   ├── boards/             #   Board JSONs: marlin_opulo_lumen_rev3/4/5.json
│   │   └── scripts/            #   configuration.py build scripts + config-i18n checkers
│   ├── share/vscode/auto_build.py                #   Auto Build (PIO Build)
│   └── tests/                  #   make tests-all-local etc.
├── config/  docker/  docs/     # Docs / Docker / dev docs (Bresenham, Serial…)
├── ini/                        # PlatformIO env matrix (grouped by MCU)
│   └── stm32f4.ini             #   contains [env:Opulo_Lumen_REV3] / REV4 / REV5
├── .editorconfig  .gitattributes
├── platformio.ini              # ⭐ PlatformIO entry (default_envs = Opulo_Lumen_REV5)
├── Makefile                    # make shortcuts
├── marlin.code-workspace       # VS Code multi-root workspace
├── process-palette.json        # VS Code "Process Palette" → PIO Build
├── LICENSE                     # code GPL-3.0; see "Credits & License" for HW/docs
└── README.md / README.en.md    # Multilingual docs (Chinese by default)
```

### Key differences between the two programs

- **Motherboard firmware (REV5)**: drives the PnP machine's X/Y motion axes,
  endstops, camera/lighting interfaces, etc. — the default build target.
- **Feeder firmware (REV3/REV4)**: `EXTRUDERS 0` (no extruder/hotend) and
  declares `AXIS4/AXIS5/AXIS6` as **rotational axes** (`AXISn_ROTATES`) to
  drive the feed sprocket wheels; feed-speed parameters differ per hardware
  revision.
- Actual differences among the four feeder configs are tiny:
  - `rev4-v3.0` vs `rev4-v3.1`: feed-speed parameters only
    (`DEFAULT_MAX_FEEDRATE` 200→1000 mm/s, `HOMING_FEEDRATE` 100→200 mm/min);
  - `rev4-v3.1-pwm-aux` vs `rev4-v3.1`: only adds `FAST_PWM_FAN`
    (`FAST_PWM_FAN_FREQUENCY 31400`, silent high-frequency AUX fan);
  - `rev3` vs the `rev4` series differ substantially (different controller
    generation — pin map and feature set).

---

## 🚀 Quick Start

Getting a motherboard up and running takes 5 steps (about 15 minutes, excluding
the first full build):

### Step 1: Install the build environment

1. Install [VS Code](https://code.visualstudio.com/) and the
   [PlatformIO IDE extension](https://marketplace.visualstudio.com/items?itemName=PlatformIO.platformio-ide)
   (it auto-installs PlatformIO Core and the STM32 toolchain); or install only the
   command-line [PlatformIO Core](https://docs.platformio.org/en/latest/core/installation.html).
2. Clone this repo:
   ```bash
   git clone https://github.com/hongligongsi/qingwa-openpnp-hongli.git
   cd qingwa-openpnp-hongli
   ```

### Step 2: Build the motherboard firmware

Nothing to change — the default config is the REV5 motherboard:

```bash
pio run
```

The first build downloads library dependencies and compiles everything (a few
minutes); later builds are incremental. Success shows `SUCCESS` plus flash/RAM
stats (Flash ≈ 22%, RAM ≈ 7%); artifacts land in
`.pio/build/Opulo_Lumen_REV5/firmware.bin` (and `.elf`).

### Step 3: Put the board into bootloader mode

The STM32 ships with a built-in **DFU bootloader** (USB ID `0483:df11`):

1. Hold the **BOOT0** button;
2. Press **RESET** once, then release BOOT0;
3. Plug in USB — the device should appear as `STM32 BOOTLOADER` in Device
   Manager (Windows) or `lsusb` (Linux).

> If the board already runs this firmware, `pio run -t upload` usually works
> directly — PlatformIO detects the DFU device automatically.

### Step 4: Flash

```bash
pio run -e Opulo_Lumen_REV5 -t upload
```

`File downloaded successfully` means done; power-cycle USB and the firmware runs.

### Step 5: Verify

```bash
# Open a serial monitor (baud rate 250000)
pio device monitor -b 250000
```

```gcode
M115            ; reports firmware version and machine name (LumenPnP)
M119            ; endstop states
G28             ; home all axes (verify endstop wiring first!)
```

Once verified, connect the machine in OpenPnP.

**What about feeders?** Same build/flash flow, different config and env — see
"Building & Flashing → Program 2" below.

---

## ⚙️ Building & Flashing

### Prerequisites

- Install [PlatformIO Core](https://docs.platformio.org/en/latest/core/installation.html);
  the easiest path is **VS Code + PlatformIO IDE** or Marlin's **Auto Build**
  script (`buildroot/share/vscode/auto_build.py`, or the **PIO Build** command from
  `process-palette.json`).
- The default build environment is already set to the **REV5 motherboard** — no
  extra setup.

### Program 1: Motherboard firmware (REV5, default)

The `Configuration.h` / `Configuration_adv.h` files in the `Marlin/` root are the
active motherboard config — just build:

```bash
# Build (default env is Opulo_Lumen_REV5)
pio run

# Explicit environment
pio run -e Opulo_Lumen_REV5

# Flash
pio run -e Opulo_Lumen_REV5 -t upload

# Serial monitor (250000 baud)
pio device monitor -b 250000
```

> After editing `Configuration.h` etc., just run `pio run` again — PlatformIO
> rebuilds automatically.

### Program 2: Feeder firmware (REV3 / REV4)

The feeder shares the same source tree as the motherboard; apply the desired
feeder config snapshot into the `Marlin/` root, then switch the env. Example
with REV4 + feeder v3.1:

```bash
# 1) Back up the current motherboard config
cp Marlin/Configuration.h    /tmp/mb_Configuration.h
cp Marlin/Configuration_adv.h /tmp/mb_Configuration_adv.h

# 2) Apply a feeder config (pick one, see the table above)
cp Marlin/rev4-v3.1-feeder-config/Configuration*.h Marlin/

# 3) Build the feeder firmware (output in .pio/build/Opulo_Lumen_REV4/)
pio run -e Opulo_Lumen_REV4

# 4) Flash to the feeder controller
pio run -e Opulo_Lumen_REV4 -t upload

# 5) Restore the motherboard config
cp /tmp/mb_Configuration.h    Marlin/Configuration.h
cp /tmp/mb_Configuration_adv.h Marlin/Configuration_adv.h
```

> - The first build after a config swap is a full rebuild (different header
>   dependencies) — that is normal.
> - For `rev3-feeder-config` use `-e Opulo_Lumen_REV3`;
>   `rev4-v3.0-feeder-config` and `rev4-v3.1-feeder-pwm-aux-config` still use
>   `-e Opulo_Lumen_REV4`.
> - Restore the motherboard config before committing — keep the `Marlin/` root
>   on REV5 at all times.

### Flashing methods in detail

Both the motherboard and feeder controllers are STM32F407VET6; the board
definition supports 4 upload protocols (`stlink` / `dfu` / `jlink` /
`blackmagic`), defaulting to **DFU**:

**Method A: DFU (recommended, USB cable only)**

```bash
# 1. Hold BOOT0 → tap RESET → release BOOT0 to enter DFU mode
#    (Device Manager should show "STM32 BOOTLOADER")
# 2. Flash
pio run -e Opulo_Lumen_REV5 -t upload          # motherboard
pio run -e Opulo_Lumen_REV4 -t upload          # feeder (config applied above)
# 3. Unplug/replug USB to reset and run
```

If the DFU device is not detected, use `dfu-util` directly:

```bash
dfu-util -a 0 -d 0483:df11 -D .pio/build/Opulo_Lumen_REV5/firmware.bin -s 0x08000000:leave
```

**Method B: ST-Link (debugger; best for unbricking)**

```bash
pio run -e Opulo_Lumen_REV5 -t upload --upload-protocol stlink
```

Requires 4 wires: SWDIO / SWCLK / GND / 3.3V to the onboard SWD header.
If the firmware is broken and DFU can no longer be entered, ST-Link is the
only reliable recovery path.

### Run upstream tests (optional)

```bash
make tests-all-local                  # all tests locally
make tests-single-local TEST_TARGET=Opulo_Lumen_REV5
```

---

## 🔧 Configuration & Versioning

- **`Marlin/Configuration.h` / `Configuration_adv.h`**: the configuration actually
  used by this repo (the REV5 **motherboard**, the default build target).
- **`Marlin/rev5-config/`**: motherboard config snapshot, kept **byte-identical**
  to the active config (refreshed 2026-10-20). **Convention: after changing the
  motherboard config and committing, refresh the snapshot too**:
  ```bash
  cp Marlin/Configuration.h    Marlin/rev5-config/Configuration.h
  cp Marlin/Configuration_adv.h Marlin/rev5-config/Configuration_adv.h
  ```
- **`Marlin/rev3-*` / `rev4-*` folders**: config snapshots for the **feeder**
  firmware, four sets by controller generation and feeder hardware revision
  (see the table in "Repository Layout"); apply one when building the feeder
  firmware (see "Building & Flashing → Program 2").
- **`Marlin/config.ini`**: Marlin compile-time config via ini
  (`[config:minimal/basic/advanced]`). Disabled by default
  (`ini_use_config = none`); enable it only if you prefer ini-driven config.

### How to modify the configuration safely (tutorial)

Tuning motion parameters (speed / acceleration / current) is the most common
change. Do it like this:

1. **Edit the config.** Most parameters live in `Marlin/Configuration.h`,
   advanced ones in `Configuration_adv.h`. For example, raising X/Y default
   speed from 7000 to 8000 mm/s (axis order: X / Y / Z / I / J):

   ```cpp
   #define DEFAULT_MAX_FEEDRATE {8000, 8000, 1000, 50000, 50000}  // (mm/s)
   ```

2. **Rebuild**: `pio run`. Config changes trigger an incremental rebuild.

3. **Make the values take effect — either**:
   - flash the new firmware — the parameters are then the compiled defaults
     (`EEPROM_SETTINGS` is off, so nothing needs to be saved);
   - or without reflashing, send `M203 X8000 Y8000` over serial for a runtime
     change (lost on reboot).

4. **Sync the snapshot** (when the motherboard config changed): copy the active
   config into `rev5-config/` to keep it current (command in "Configuration
   file layout" above).

**⚠️ Be careful with comments**: some comments in the config files are
**machine-readable** — parsed by `schema.py` to generate config metadata.
Breaking them fails the build or silently drops config items:

| Never touch | Why |
|---|---|
| `// @section xxx` | section grouping key; renaming misclassifies the whole block |
| `// :[0, 1, 2, 3]`, `// :{...}` | option lists; must stay intact on one line |
| parenthesized units `(mm)` `(°C)` `(seconds)` | extracted as schema units fields |
| temperature sensor entry lines (` -5 : MAX31865 ...`) | each entry must stay on its own line |
| string literals, macro names, G-code commands | directly affect firmware behavior |

After editing, run the repo's regression checkers (see
`buildroot/scripts/README-config-i18n.md`):

```bash
python buildroot/scripts/check-config-i18n.py          # comment structure + preprocess + schema
python buildroot/scripts/check-config-code-intact.py --ref HEAD  # confirm zero code changes
```

### Firmware baseline

- Source baseline: **Marlin 2.1.x** (config format `CONFIGURATION_H_VERSION 02010300`),
  preserving the upstream `import-2.1.x` / `bugfix-2.1.x` layout.

---

## 🧰 Common G-code

The firmware keeps Marlin's full G/M command set, but **not every command is
compiled in** — a PnP machine has no extruder, heater, probe, SD card or display,
so those handlers are removed at build time. Three markers are used below:

- ✅ available
- ⚠️ available but limited (see note)
- ❌ not compiled into this firmware (`Unknown command` if sent)

### 1. Connection and status

| Command | Status | Notes |
|---------|--------|-------|
| `M115` | ✅ | Firmware info and capability set — first command any host sends |
| `M114` | ✅ | Report current position (X/Y/Z in mm, A/B in degrees) |
| `M119` | ✅ | State of the three endstops |
| `M122` | ✅ | Full TMC2209 status for all six drivers: current, microsteps, connection errors |
| `M105` | ⚠️ | No temperature sensors — returns empty/zero |
| `M503` | ✅ | Print all adjustable parameters currently in RAM |
| `M111` | ❌ | Debug level, not compiled outside dev mode |
| `M31` | ❌ | No SD card |

### 2. Motion

| Command | Status | Notes |
|---------|--------|-------|
| `G0` / `G1` | ✅ | Linear move — the workhorse for a PnP machine |
| `G2` / `G3` | ✅ | Arc interpolation (`ARC_SUPPORT` is on) |
| `G4` | ✅ | Dwell, `G4 P500` = pause 500 ms |
| `G28` | ✅ | Home; can restrict axes, e.g. `G28 X Y` |
| `G92` | ✅ | Set the logical position without moving |
| `M92` | ✅ | Steps per unit at runtime (lost on reboot) |
| `M201` / `M203` | ✅ | Max acceleration / max feedrate |
| `M204` | ✅ | Acceleration: `P` print, `T` travel, `R` retract |
| `M205` | ✅ | Advanced settings; this firmware uses `J` (junction deviation) |
| `M206` / `M428` | ✅ | Home offset / derive home offset from current position |
| `M211` | ✅ | Software endstops on/off/report |
| `M220` | ✅ | Feedrate factor, `M220 S50` = half speed |
| `M400` | ✅ | Wait for all queued moves to finish |
| `M410` | ✅ | Immediate quickstop, clears the motion queue |
| `M17` / `M18` / `M84` | ✅ | Enable / disable steppers; `M84 S30` sets a 30 s idle timeout |
| `M120` / `M121` | ✅ | Enable / disable endstop-always-on monitoring |
| `M221` | ❌ | Flow factor, no extruder |
| `G29` / `G30` / `G38` | ❌ | No probe, no bed leveling |
| `G10` / `G11` | ❌ | Retract, no extruder |
| `G5` / `G60` / `G61` | ❌ | Bezier / saved positions not enabled |
| `M290` / `M600` | ❌ | Babystepping / filament change not compiled |

### 3. TMC2209 driver tuning

| Command | Status | Notes |
|---------|--------|-------|
| `M906` | ✅ | Set current (mA RMS): `M906 X800 Y1000` |
| `M122` | ✅ | Query driver status; `M122 X` for a single axis |
| `M569` | ✅ | StealthChop on/off: `M569 S1 Z` on, `S0` off |
| `M912` – `M915` | ❌ | Prewarn, hybrid threshold, StallGuard — those features are off |

### 4. Direct pin control (the PnP-specific part)

| Command | Status | Notes |
|---------|--------|-------|
| `M42` | ✅ | Write a pin: `M42 P<n> S<0-255>`; `I` sets input, `T` sets pullup |
| `M43` | ✅ | Read a pin / list pins; **with no arguments it prints the full pin-number map** |
| `M43 E1` | ✅ | Live endstop monitor — the most useful tool when debugging homing |
| `M43 T` | ✅ | Toggle output pins in bulk |

> ⚠️ The `P` value in `M42`/`M43` is Marlin's **internal pin index**, not a GPIO
> name. When unsure, send `M43` first to list the index, then map it to names like
> `PD0` or `PA5`.

### 5. Fans / LED strip / buzzer

| Command | Status | Notes |
|---------|--------|-------|
| `M106 P<0-3> S<0-255>` | ✅ | Four PWM fans (`PB8` / `PB9` / `PE5` / `PE6`) |
| `M107 P<0-3>` | ✅ | Turn the matching fan off |
| `M150` | ✅ | NeoPixel colour: `M150 R255 U0 B0` (`U` is green — the strip is GRB) |
| `M150 P...` | ✅ | Limit the update to the first N LEDs or a range |
| `M300 S<Hz> P<ms>` | ✅ | Beep, `M300 S523 P200` plays C5 |
| `M300 S0` | ✅ | Mute immediately — handy during debugging |

### 6. Parameter storage (a known gotcha)

| Command | Status | Notes |
|---------|--------|-------|
| `M503` | ✅ | Report parameters currently in RAM (always works) |
| `M502` | ✅ | Reset RAM parameters to the compiled defaults |
| `M500` | ⚠️ | **Answers `EEPROM disabled`** because `EEPROM_SETTINGS` is off |
| `M501` | ⚠️ | Nothing to read — behaves like reset-and-report |

To make `M92`, `M906` or `M201` survive a power cycle, enable `EEPROM_SETTINGS`
in `Configuration.h` and rebuild (the board already provides SRAM emulation and
8 KB of space).

### 7. A typical bring-up sequence

```gcode
M115                    ; 1. confirm you are talking to a LumenPnP
M119                    ; 2. push each axis onto its endstop and watch the state flip
G28                     ; 3. home
G92 X0 Y0 Z0 A0 B0      ; 4. declare this the origin (optional after G28)
G0 X50 Y50 F3000        ; 5. slow test move
M114                    ; 6. verify the reported position matches reality
M122                    ; 7. check the drivers for connection errors
M300 S523 P150          ; 8. test the buzzer
M150 R0 U255 B0 P16     ; 9. test the LED strip (green)
M84                     ; 10. release the motors
```

**Feeder firmware (flashed separately)** — a feeder maps its three feed wheels to
the rotary axes `A` / `B` / `C` (degrees), so feeding and retracting is just
rotating them:

```gcode
G1 A45 F2000            ; advance wheel A by 45° (one tape pitch)
G1 A-45 F2000           ; reverse (retract tape)
M114                    ; report axis positions (rotary axes in degrees)
```

Full command reference: [Marlin G-code docs](https://marlinfw.org/docs/gcode/M000-M001.html).

---

## 🛠 FAQ

<details>
<summary><b>No serial port after flashing?</b></summary>

Use a data USB cable to the STM32's USB port; you may need the USB CDC driver on
first use (Windows). A new serial device should appear in Device Manager /
`ls /dev/tty*`. Baud rate is `250000`.
</details>

<details>
<summary><b>How do I check the running firmware version/config?</b></summary>

Send `M115` from your host — the response includes the version string and the
machine name (LumenPnP).
</details>

<details>
<summary><b>Why is there no heating/extrusion?</b></summary>

A PnP machine doesn't need extruder/heating. This firmware sets `EXTRUDERS 0` and
disables all temperature sensors in `Configuration.h` — that's by design, not a fault.
</details>

<details>
<summary><b>Which feeder config should I flash?</b></summary>

Check two things: ① the controller board silkscreen — REV3 or REV4 (picks the
env); ② the feeder mechanism hardware version — v3.0 or v3.1 (picks the speed
config). v3.0 → `rev4-v3.0-feeder-config` (conservative), v3.1 →
`rev4-v3.1-feeder-config`; if the AUX fan whines, switch to
`rev4-v3.1-feeder-pwm-aux-config` (only adds `FAST_PWM_FAN`, 31.4 kHz).
When unsure, flash the v3.1 config first — conservative params won't hurt
validation.
</details>

<details>
<summary><b>Can I debug a feeder directly from my computer?</b></summary>

Yes. The feeder firmware also uses USB CDC serial (`SERIAL_PORT -1`, 250000
baud). Plug the feeder controller into the computer via USB and run
`pio device monitor -b 250000`; `M115` reports the feeder firmware info. Each
feeder appears to the host as an independent serial device. The full flashing
flow is in "Building & Flashing → Program 2".
</details>

<details>
<summary><b>BOOT0 + RESET but no DFU device shows up?</b></summary>

Check in order: ① BOOT0 must be held **at power-on/reset moment** (hold BOOT0
first, then tap RESET); ② try a USB cable that definitely carries data; ③ on
Linux check `dfu-util` permissions (udev rule or sudo); ④ if DFU still cannot
be entered the bootloader may be overwritten — reflash via **ST-Link**
(see "Flashing methods in detail").
</details>

<details>
<summary><b>Build fails or config items go missing after editing comments?</b></summary>

You most likely touched **machine-readable comments** (`@section` markers,
`:[...]` option lists, parenthesized units, sensor entries — see the warning
table in "Configuration & Versioning"). Restore the mis-edited lines via
`git diff Marlin/Configuration.h`, then run
`python buildroot/scripts/check-config-i18n.py` to confirm the schema count is
back to the 2444-item baseline.
</details>

<details>
<summary><b>M500 answers "EEPROM disabled" — settings won't persist?</b></summary>

`EEPROM_SETTINGS` is commented out in `Configuration.h`, so the whole EEPROM code
path is not compiled: `M500` only answers `EEPROM disabled`, and runtime changes
such as `M92` / `M906` / `M201` are lost on reboot. The board-level SRAM emulation
(`SRAM_EEPROM_EMULATION`, 8 KB) is already prepared — enable the macro and rebuild
if you need persistence. To inspect the parameters in effect right now, just send
`M503`.
</details>

<details>
<summary><b>How do I change the startup beeper sound?</b></summary>

The startup tune lives in `STARTUP_COMMANDS` in `Marlin/Configuration_adv.h`
(around line 3855 in the board config). It is simply a chain of `M300` beeper
G-codes executed at boot:

```
#define STARTUP_COMMANDS "M300 S2000 P100\nG4 P900\nM300 S2000 P100\n..." \
                         "...\nM300 S2500 P1000"
```

- `S<hz>` sets the tone frequency, `P<ms>` the duration, and `G4 P<ms>` adds a
  pause between notes.
- To change the rhythm/pitch just edit this string. To use a melody, the
  commented-out three-note example in the config works as-is:
  `"M300 S523 P150\nM300 S659 P150\nM300 S784 P300"` (C5-E5-G5).
- Prerequisites: `SPEAKER` must be enabled in `Configuration.h` (already on for
  the board config), otherwise the `S` frequency parameter of `M300` has no
  effect. The buzzer pin is defined as `BEEPER_PIN PA7` in
  `pins_OPULO_LUMEN_REV5.h`.
- To add an on-screen mute toggle, enable `SOUND_MENU_ITEM` in
  `Configuration_adv.h`; `SOUND_ON_DEFAULT` controls whether sound is on by
  default. For quick testing you can also send `M300 S0 P0` to mute temporarily.

Remember to rebuild and reflash afterwards — the startup tune is baked in at
compile time and cannot be saved at runtime.
</details>

---

## 🤝 Credits & License

This project is not a standalone work — every layer of it builds on someone
else's open-source effort, and those upstream projects use **three different
licenses**. Start with "which content falls under which license", then read what
each one means for you in practice.

### Whose shoulders, which license

| Upstream project | Role here | License | Included in this repo |
|------------------|-----------|---------|------------------------|
| [Marlin](https://github.com/MarlinFirmware/Marlin) (Scott Lahteine and the community) | The firmware core: motion planning, G-code parsing, STM32 HAL, TMC framework | **GPL-3.0** | ✅ the whole `Marlin/` |
| [Opulo LumenPnP](https://github.com/opulo-inc/) hardware | REV5 motherboard schematic / PCB / BOM, board pin definitions | **CERN-OHL-W 2.0** | ⚠️ pins and board constants only |
| Opulo LumenPnP software | Feeder firmware, host-side scripts, configuration templates | **MPL 2.0** | ⚠️ `.openpnp2/` configs |
| Opulo LumenPnP documentation | Assembly, wiring and calibration guides | **CC BY-SA 4.0** | ⚠️ this README adapts it |
| [OpenPnP](https://openpnp.org/) | The host application | GPL-3.0 | ❌ installed separately |
| [TMCStepper](https://github.com/teemuatlut/TMCStepper), [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel), STM32duino | TMC2209 registers, LED driver, STM32 low level | their own terms (see the LICENSE in each `.pio/libdeps` package) | pulled in as dependencies |
| [PlatformIO](https://platformio.org/) | Build system and ARM toolchain | Apache-2.0 | ❌ toolchain |

> **The LICENSE file in each upstream repository is authoritative.** The table
> above follows Opulo's published licensing statement; if upstream has changed a
> version, its latest notice wins.

The scope of the three copyleft licenses differs a lot — one line to remember:

> **GPL covers the whole program → MPL covers individual files → CERN-OHL-W covers the design files you modified → CC BY-SA covers the adapted document.**

### Hardware design: CERN-OHL-W 2.0

The LumenPnP hardware (REV5 motherboard, feeders, structural parts) is released
under the
[CERN Open Hardware Licence v2 – Weakly Reciprocal](https://ohwr.org/cern_ohl_w_v2.txt).
The **W (Weakly)** in the name is the key — it only applies to **the part you
changed**.

| Obligation | What it requires |
|------------|------------------|
| Keep attribution | Keep the original author's name (Opulo) and copyright notices — do not remove them |
| Mark changes | Modified design files must state that they were changed, and when |
| Publish modifications | Design files you modified (schematic, PCB, BOM, mechanical drawings) must still be offered under CERN-OHL-W 2.0 when distributed |
| Provide a Source Location | When shipping a physical product, include a pointer to where the design files can be obtained |
| No extra restrictions | You may not impose further restrictions downstream (no ban on improving it, no pay-to-get-the-files) |
| No warranty | The original author is not liable for your use or modification |

**What "weakly reciprocal" actually means** — this is where people get it wrong:

- ✅ **You can manufacture and sell directly.** Building products with this open
  hardware and selling complete machines is fully allowed; your manufacturing
  process, supply chain and cost structure **stay private**
- ✅ **Your own parts can stay closed.** Independent modules you add on top
  (a custom expansion board, a custom fixture) may be closed-source, as long as
  their **interface to the open part is clear** (connectors, header pinout,
  communication protocol)
- ⚠️ **Modified files must be published.** If you directly edit an open design
  file (reroute a trace, swap a BOM part), **that modified file** must be opened
  up — "I only changed a little" is not an exemption
- ❌ **You cannot hide the open design inside a closed product.** The CERN-OHL-W
  design files may not be distributed as part of your closed design, and you may
  not claim the whole product is your own work

> This repository **does not contain** the LumenPnP design files. It only
> references pin definitions and board constants in
> `Marlin/src/pins/stm32f4/pins_OPULO_LUMEN_REV5.h`. To modify the hardware,
> start from [opulo-inc/lumenpnp](https://github.com/opulo-inc/lumenpnp) and
> follow the terms above.

### Upstream software: MPL 2.0

Opulo's software is released under the
[Mozilla Public License 2.0](https://www.mozilla.org/en-US/MPL/2.0/). MPL is a
**per-file** copyleft — the boundary is the file, not the program.

| Obligation | What it requires |
|------------|------------------|
| Keep attribution | Keep the original author's name, copyright and license notices |
| Publish modifications | MPL files you modified must continue to be offered under MPL 2.0 when distributed |
| Point to the source | When distributing an executable form, explain how to obtain the corresponding source |
| Patent grant | MPL 2.0 grants you rights to its patented technology — but **if you sue the original author over those patents, the grant terminates immediately** |
| No warranty | Provided as-is |

**Combining it with closed-source code is explicitly allowed:**

- ✅ You may link MPL code with closed code and ship them as one product
- ✅ Your own part may stay closed and may be sold commercially
- ⚠️ But **the MPL files you modified** must still be published — you cannot hide
  them behind "the overall product is closed"
- 📌 The boundary is simple: **file you changed → publish it; file you left alone → leave it as-is**

MPL 2.0 is compatible with the GPL (unless marked "Incompatible With Secondary
Licenses"), so MPL files can join a GPL-3.0 larger work — but those files and
their modifications remain under MPL.

> The `.openpnp2/` folder here holds OpenPnP machine configuration, part of which
> may derive from templates Opulo ships. Before building a commercial product,
> sort out which files are original templates and which carry your own settings.

### Documentation: CC BY-SA 4.0

The LumenPnP documentation, assembly and calibration guides are released under
[CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/). Both READMEs in
this repository were written with reference to that material and adapt parts of
it, so **the documentation here is likewise offered under CC BY-SA 4.0**.

| Obligation | What it requires |
|------------|------------------|
| BY — attribution | Credit the original author (Opulo / LumenPnP) |
| BY — source link | Link to the original work |
| BY — license and changes | State that CC BY-SA 4.0 applies, and whether you modified it |
| SA — share alike | Your **adapted material** must use the same license, with no stricter terms added |
| Commercial use | ✅ Allowed, including printing it as a manual sold with machines |

**Four common scenarios and where the line falls:**

| What you do | Must it be released under CC BY-SA? |
|-------------|--------------------------------------|
| Translate, rewrite or restructure it into your own manual | ✅ Yes, and you must credit Opulo |
| Only convert the format (to Word, adjust layout), content essentially unchanged | ✅ Yes — distributing that Word file is "sharing" the work |
| Include it as a **standalone chapter** in your own larger manual, the rest self-written | ⚠️ Only that chapter needs CC BY-SA; the rest of the manual may be licensed separately |
| Internal company use only, never shared | ❌ No — CC obligations only trigger on sharing |

> One common misconception about share-alike: CC BY-SA 4.0 requires the same
> license for the **Adapted Material itself**, not for the larger work it is
> compiled into. So "I used one CC BY-SA paragraph, therefore all my software
> source must be CC BY-SA" does not hold — software code and documentation are
> different types of work, each under its own license.

### Firmware code in this repository: GPL-3.0

The modified parts of `Marlin/` and the verification tools under
`buildroot/scripts/` are released under **GNU GPL v3.0** — see [LICENSE](LICENSE).
It is a strong copyleft license, so distribution (free or paid) requires:

| Obligation | What it requires |
|------------|------------------|
| Provide source | Ship the **complete corresponding source**, including build scripts and configs, with any firmware you distribute (including machines you sell). A binary alone is not enough |
| Keep notices | Do not strip existing copyright, license or warranty notices |
| Mark changes | Modified files must say they were changed and when (GPLv3 §5a) |
| Same license | Derivative works must stay GPL-3.0 — no relicensing to looser or stricter terms |
| No extra restrictions | You may not restrict the rights GPL grants (paid-only licensing, a ban on reverse engineering, ...) |
| No warranty | Provided as-is; authors are not liable for defects or damages |
| Patent grant | Contributors automatically grant users a license to their necessary patents (GPLv3 §11) |

In one sentence: **use it, modify it, sell machines built with it — but the moment
you distribute the firmware, the source has to travel with it.**

### What this project adds

Copyright for the following belongs to the contributors of this repository (code
under GPL-3.0, documentation under CC BY-SA 4.0):

- **Configuration layer**: full Simplified-Chinese comments in `Configuration.h` /
  `Configuration_adv.h`, plus structural repairs to the motherboard and four feeder
  configs (machine-readable comments, schema compatibility)
- **Documentation**: bilingual READMEs (architecture, pinout, build, debugging,
  G-code, FAQ) and the configuration-checking guide
- **Verification tooling**: `buildroot/scripts/check-config-i18n.py`,
  `check-config-code-intact.py` and the schema baseline
- **M300 melody editor**: `m300_editor/` (single-page front end, no external deps)
- **Startup tune and default-parameter adjustments**

### Built With LumenPnP silkscreen

If you use a LumenPnP to produce PCBs, Opulo welcomes a **"Built With LumenPnP"**
mark on the board — silkscreen text, a sticker or a logo, wherever it fits.

That is a **permission, not an obligation**: adding it or not has no effect on
your commercial rights under this design, and no approval is needed. For teams
building or contract-manufacturing machines, the mark is also a nice nod back to
the upstream open-source work.

### Not an official release

This is a **community fork**, not an official Marlin release and not the official
Opulo firmware. "Marlin" is the MarlinFirmware project name and "LumenPnP" is an
Opulo product name; they are referenced here for identification only and imply no
endorsement or affiliation.

### Feedback

This firmware is maintained for the **Qingwa (Frog) PnP** project and shared for
learning and exchange. Bug reports, suggestions and mods are welcome via:

- **Bilibili: @青蛙贴片机** (fastest way to reach us)
- **Issues** on this repository
