<p align="center">
  <b>🐸 Qingwa PnP Firmware · qingwa-pnp-marlin</b><br/>
  A pick-and-place firmware based on Marlin 2.1.x + Opulo LumenPnP REV5 hardware reference for the Qingwa PnP
</p>

<p align="center">
  <a href="LICENSE"><img src="https://img.shields.io/badge/Code-GPL--3.0-blue.svg" alt="Code: GPL-3.0"></a>
  
  <a href="#-credits--license"><img src="https://img.shields.io/badge/HW-CERN--OHL--W%202.0-green.svg" alt="Hardware: CERN-OHL-W 2.0"></a>
  
  <a href="#-credits--license"><img src="https://img.shields.io/badge/Docs-CC%20BY--SA%204.0-blueviolet.svg" alt="Docs: CC BY-SA 4.0"></a>
  <img src="https://img.shields.io/badge/Marlin-2.1.x-important.svg" alt="Marlin 2.1.x">
  <img src="https://img.shields.io/badge/Board-Qingwa%20REV5-success.svg" alt="Qingwa REV5">
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
- [🧑‍🏫 Read this first: 5 words + 3 things to prepare](#-read-this-first-5-words--3-things-to-prepare)
- [🚀 Quick Start](#-quick-start)
- [⚙️ Building & Flashing](#-building--flashing)
- [🔧 Configuration & Versioning](#-configuration--versioning)
- [🧰 Common G-code](#-common-g-code)
- [🎛 Tuning quick reference: speed / current / light](#-tuning-quick-reference-speed--current--light)
- [🛠 FAQ](#-faq)
- [📚 Further reading & calibration notes](#-further-reading--calibration-notes)
- [🤝 Credits & License](#-credits--license)

---

## 📖 Introduction

This project is the firmware for the **Qingwa (Frog) Pick-and-Place machine**. It is
*not* a 3D-printer firmware — it adapts the open-source **Marlin** firmware into the
**motion controller** of an SMT pick-and-place (PnP) machine.

### What makes up the machine?

A complete Qingwa PnP machine has two major parts, each running its own firmware
built from the **same source tree**:

1. **Motherboard** — the "brain and limbs" of the machine. The physical board is a
   **custom Qingwa carrier board** (MCU: **STM32F407VET6**, ARM Cortex-M4,
   512 KB Flash / 192 KB SRAM) whose pinout is **fully compatible with the Opulo
   LumenPnP Motherboard REV05** (verified pin by pin — see
   [Hardware & Pinout](#-hardware--pinout)), so the firmware simply uses the REV5
   board definition. It drives gantry X/Y positioning, Z lift, dual-motor sync
   (X/Y2), endstop sensing, and camera/lighting/vacuum peripherals.
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
| Physical board | Frog carrier board (custom design, **pin-compatible** with Opulo LumenPnP REV5) |
| Schematic | `docs/hardware/SCH_插板_主板电路图.pdf` (JLCEDA V1.0, 2026-07-20) |
| Gerber / drill | `docs/hardware/Gerber_主板_2026-10-21.zip` (16 files, fab-ready) |
| Pin verification | ✅ checked pin by pin against the schematic — all match (details in `docs/hardware/主板电路图核对.md`) |
| Compile-time board name | `Qingwa Motherboard REV05` (`BOARD_INFO_NAME`, build label only — not printed by M115) |
| M115 `MACHINE_TYPE` | `3D Printer` (no `CUSTOM_MACHINE_NAME` set; OpenPnP identifies the board by the trailing `UUID`) |
| MCU | STM32F407VET6 (ARM Cortex-M4 @ 168 MHz) |
| Flash / SRAM | 512 KB / 192 KB |
| Driver interface | 6 × TMC2209 (single-wire UART) |

### 📁 Hardware documentation index (`docs/hardware/`)

| Document | File | Notes |
|----------|------|-------|
| 📄 Schematic | `SCH_插板_主板电路图.pdf` | Exported from JLCEDA — the primary reference for wiring |
| 🗂 Gerber files | `Gerber_主板_2026-10-21.zip` | 16 files, fab-ready |
| 🔌 **Wiring guide (Chinese)** | [`接线指南.md`](docs/hardware/接线指南.md) | **Every connector pinout verified**: power / steppers / endstops / pump-valve MOSFETs / LED strips / RS485 / expansion, plus a 6-step power-on checklist |
| ✔ Pin verification log | [`主板电路图核对.md`](docs/hardware/主板电路图核对.md) | Pin-by-pin comparison between schematic and firmware pin header |
| 🧾 Carrier-board BOM | [`插板BOM物料清单.md`](docs/hardware/插板BOM物料清单.md) | 43 line items with LCSC part numbers; warns that TMC2209 must be ordered separately |
| 🖱 Interactive BOM | `InteractiveBOM_插板_2026-10-22.html` | 24 MB — open locally in a browser; clicking a designator highlights the PCB location (not in repo; [download from Release](https://github.com/hongligongsi/qingwa-openpnp-hongli/releases/download/lfpnp-v1.0/InteractiveBOM_2026-10-22.html)) |
| 📦 Full bundle (Windows) | [GitHub Release **HL PNP v1.0**](https://github.com/hongligongsi/qingwa-openpnp-hongli/releases/tag/lfpnp-v1.0) (tag keeps legacy name `lfpnp-v1.0`) | **Deeply customized OpenPnP** (portable build with bundled Java 17 runtime, ~320 MB) |
| 📦 Bundle (Linux x64) | [lfpnp_v1.0-openpnp-linux-x64.tar.gz](https://github.com/hongligongsi/qingwa-openpnp-hongli/releases/download/lfpnp-v1.0/lfpnp_v1.0-openpnp-linux-x64.tar.gz) | Same customized app with bundled Linux JRE 17 (~227 MB); `chmod +x OpenPnP/OpenPnP.sh` then run |

> 💡 The OpenPnP inside the bundle is **not the stock release** — it is a heavily
> customized host software: **fully localized Chinese UI**, translated
> "Issues & Solutions" panel, Chinese feeder type names, real-time panel-array
> refresh, board file browser fix, paste-list import, repeat-placement,
> post-job / fault G-code hooks, a **simultaneous dual-nozzle (parallel
> down-vision)** feature, a **one-click calibration** wizard (fiducials / camera
> calibration / nozzle-tip vision / belt backlash in one pass), and extra feeder
> types (AS2 auto feeder, tadpole feeder). It stores its config in a separate
> `.hlpnp` directory (coexists with stock OpenPnP's `.openpnp2` on the same
> machine; the legacy release (formerly lfpnp v1.0) used `.lfpnp`).
> A class-level diff (16 new classes / 57 modified, UI redesign, simultaneous-vision
> algorithm, one-click calibration call chain) is in
> [`docs/software/OpenPnP定制版与原版差异.md`](docs/software/OpenPnP定制版与原版差异.md).

### Complete pin map (from `Marlin/src/pins/stm32f4/pins_OPULO_LUMEN_REV5.h`)

> ✅ **Verified pin by pin against the physical board schematic**
> (`docs/hardware/SCH_插板_主板电路图.pdf`): all six axes' STEP/DIR/EN/UART/DIAG,
> endstops, buzzer, lights, AUX, RS485 and ID pins **match exactly** — no firmware
> change is needed to drive this board.

Every pin is defined in that single header. "Status" means whether this firmware
config actually uses it. "Silkscreen" is the net/axis label printed on the schematic.

**① Stepper motors (6 × TMC2209, single-wire UART)**

| Axis | Silkscreen | STEP | DIR | ENABLE | UART (TX=RX) | DIAG | Motor connector | Status |
|------|-----------|------|-----|--------|--------------|------|-----------------|--------|
| X | X | `PB15` | `PB14` | `PD9` | `PD8` | `PB10` | CN29 | active |
| Y | Y1 | `PE15` | `PE14` | `PB13` | `PB12` | `PB11` | CN30 | active |
| Y2 | Y2 | `PD6` | `PD7` | `PA3` | `PA2` | `PC12` | CN34 | active (dual Y) |
| Z | Z | `PE7` | `PB1` | `PE9` | `PE8` | `PB5` | CN32 | active |
| A (I axis) | L (left nozzle) | `PC4` | `PA4` | `PB0` | `PC5` | `PC10` | CN33 | active (rotary) |
| B (J axis) | R (right nozzle) | `PE11` | `PE10` | `PE13` | `PE12` | `PC11` | CN31 | active (rotary) |

> Silkscreen **L = left nozzle rotation** (firmware I axis, G-code `A`) and
> **R = right nozzle rotation** (firmware J axis, G-code `B`). Each driver socket's
> `DIAG` pin is **left open by default** — short the jumper first if you want
> sensorless (StallGuard) homing.

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

| Function | Silkscreen | Pin | Status |
|----------|-----------|-----|--------|
| Output 1 (`M106 P0`) | MOS-1 → CN24 | `PB8` | active (`FAN_COUNT` = 4), 24V low-side switch |
| Output 2 (`M106 P1`) | MOS-2 → CN23 | `PB9` | active, 24V low-side switch |
| Output 3 (`M106 P2`) | MOS-3 → CN22 | `PE5` | active, 24V low-side switch |
| Output 4 (`M106 P3`) | MOS-4 → CN21 | `PE6` | active, 24V low-side switch |
| Auxiliary fan (controller fan) | FAN → CN20 | `PE2` | active, spins while any motor is enabled, off 120 s after idle |
| Buzzer | BUZZER | `PA7` | active (`SPEAKER`) |
| Bottom ring light | BTM-LIGHT | `PC7` | active, 18 LEDs, `NEO_GRB` |
| Top ring light | TOP-LIGHT | `PC8` | active, 18 LEDs; address it separately with `M150 S1 ...` |

> MOS-1…4 are **24V low-side switch outputs** (30H10K NMOS + flyback diode) — good
> for vacuum pumps, solenoids and small fans; drive them with `M106 P0..P3 S0..255`.
> Ring lights: MCU → SN74LVC2G34 buffer (3.3V→5V level shift) → XH2.54-3P
> (5V / signal / GND), a standard WS2812 hookup, so the `M150` docs apply as-is.

**④ Buses**

| Bus | Pins | Purpose |
|-----|------|---------|
| SPI | MISO `PB4` / MOSI `PB5` / SCK `PB3` | spare TMC SPI mode (UART is used instead) |
| I²C | SDA `PB7` / SCL `PB6` | on-board PCA9545A mux (see ⑥), also on the AUX port |
| RS485 | DI `PA9` / RO `PA10` / DE `PD11` / RE `PD12` | MAX3078 transceiver to the `FEEDERS` terminal (smart feeder bus) |

> ⚠️ `PB5` is shared between `Z_DIAG_PIN` and `MOSI_PIN`. Harmless here because the
> TMCs use UART rather than SPI; if you attach an SPI device, Z sensorless homing
> would need a different pin.

**⑤ Board ID and system pins**

| Function | Pins | Notes |
|----------|------|-------|
| Board revision ID | `PD0` / `PD1` / `PD2` / `PD3` | ID0–ID3 selected by 0 Ω resistors; set input pullup before reading (`M42`/`M43` examples at the end of the header) |
| General IO (AUX control) | `PD13` | net `AUX`, writable and readable |
| USB | `PA11` / `PA12` | fixed by the MCU, virtual serial port |
| SWD debug | `PA13` / `PA14` | ⚠️ also brought out as `IO72` / `IO76` with 4.7 kΩ pullups — keep external devices off these lines while debugging |
| BOOT1 | `PB2` | 10 kΩ pulldown, boots from main Flash normally |
| EEPROM | none on board | SRAM emulation, 8 KB (`MARLIN_EEPROM_SIZE 0x2000`), but `EEPROM_SETTINGS` is off |

**⑥ Wired on the board, not used by this firmware**

These circuits are populated but have no macro in the current config — write your
own if you want them:

| Circuit | Device | Pins |
|---------|--------|------|
| Smart feeder bus | MAX3078 RS485 transceiver | `PA9`(DI) / `PA10`(RO) / `PD11`(DE) / `PD12`(RE) |
| Vacuum pressure sensing | 2 × XGZP6857D | I²C through a PCA9545A 4-channel mux (`PB6`/`PB7`), one per nozzle |
| Nozzle head detect | net `CHIMERA` | `PC1` (via jumper T9) |
| Debug header H6 (2×5) | SWD + reset | 3V3, `REST`, `PA13`/`PA14` (`IO72`/`IO76`), other pins unpopulated |

**⑦ Unassigned pins**

`PA0`, `PA1`, `PA8`, `PB3`, `PB4`, `PC2`, `PC3`, `PC9`, `PC13`–`PC15`,
`PD4`, `PD5`, `PD10`, `PE0`, `PE1`, `PE3`, `PE4` are **floating / unconnected** both
in the pin header and on the schematic — handy for custom additions such as extra
sensors or pneumatic valves. (`PB3`/`PB4` are reserved as SPI SCK/MISO by the
firmware but are free if you don't use SPI.)

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
- **Identify**: send `M115` after connecting — it should report the firmware
  version, `AXIS_COUNT:5` and a trailing `UUID` (`MACHINE_TYPE` showing the Marlin
  default `3D Printer` is normal — see the [FAQ](#-faq));
- **Motion commands**: standard `G0/G1` + `G28` homing + `M119` endstop query,
  fully compatible with the Marlin command set;
- **Parameter storage**: ⚠️ `EEPROM_SETTINGS` is **not enabled** in this firmware, so
  `M500` answers `EEPROM disabled`; runtime changes (`M92`, `M906`, ...) are lost on
  reboot. Enable that macro in `Configuration.h` and rebuild if you need persistence;
- Each feeder appears to the host as an **independent serial device** (each
  flashed with the feeder firmware).

### REV05 AUX port (8-pin, header U30 on the board)

The physical U30 header (2×4) matches the firmware definition below **pin for pin**:

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
| **Motherboard firmware** | Qingwa Motherboard REV5 (PnP main board) | STM32F407VET6 | `Opulo_Lumen_REV5` (default) | Active config in `Marlin/` root (snapshot: `rev5-config/`) |
| **Feeder firmware** | Electric feeder, REV4 controller | STM32F407VET6 | `Opulo_Lumen_REV4` | One of the three `Marlin/rev4-*-feeder-config/` folders |
| **Feeder firmware (legacy)** | Electric feeder, REV3 controller | STM32F407VET6 | `Opulo_Lumen_REV3` | `Marlin/rev3-feeder-config/` |

Board definitions (pins / clock / upload protocol) live in
`buildroot/share/PlatformIO/boards/marlin_opulo_lumen_rev{3,4,5}.json`;
pin maps in `Marlin/src/pins/stm32f4/pins_OPULO_LUMEN_REV{3,4,5}.h`.

```text
qingwa-openpnp-hongli/
├── .devcontainer/              # VS Code dev container (build env in one click)
├── .github/                    # GitHub CI / community config (test-builds etc.)
├── .trellis/                   # AI-assisted development workflow scaffold (optional)
├── .vscode/                    # VS Code settings (C/C++ IntelliSense, debug, recommended extensions)
├── .workbuddy/                 # AI collaboration logs and project memory (not a build input)
├── .openpnp2/                  # OpenPnP host configuration (tracked)
│   ├── machine.xml             #   Machine setup: axes / cameras / nozzles / drivers / lighting
│   ├── parts.xml  packages.xml #   Part library and package definitions
│   ├── boards.xml  panels.xml  #   Board and panel definitions
│   ├── vision-settings.xml     #   Vision pipeline parameters
│   └── scripts/                #   OpenPnP script examples (JavaScript / Python)
│                               #   log / backups / snapshots are excluded by .gitignore
├── Marlin/                     # ⭐ Firmware source & configuration (shared by both)
│   ├── Configuration.h         #   Active configuration = Motherboard REV5
│   ├── Configuration_adv.h     #   Advanced configuration
│   ├── config.ini              #   Compile-time config via ini (disabled by default)
│   ├── Makefile                #   Make entry for pio/arduino
│   ├── Version.h               #   Version strings (overridable at build time)
│   ├── lib/                    #   Bundled third-party libraries (compiled with the source)
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
│   │   └── scripts/            #   configuration.py build scripts
│   ├── scripts/                #   ⭐ Config checkers (run after editing Configuration*.h)
│   │   ├── check-config-i18n.py          # comment structure + schema (2444-item baseline)
│   │   ├── check-config-code-intact.py   # macro table + ARM preprocessor diff, proves behaviour equality
│   │   ├── config-schema-baseline.json   # schema baseline snapshot
│   │   └── README-config-i18n.md         # usage notes for both scripts
│   ├── share/vscode/auto_build.py                #   Auto Build (PIO Build)
│   └── tests/                  #   make tests-all-local etc.
├── docs/                       # Project docs directory
│   ├── hardware/               #   ⭐ Hardware: schematic PDF / Gerber / wiring guide / BOM / pin log
│   ├── software/               #   ⭐ Host software: customized vs. stock OpenPnP deep dive
│   ├── images/lumenpnp-flashing/  # Flashing tutorial screenshots (14 images)
│   ├── OpenPnP固件更新烧录教程.md    #   ⭐ Step-by-step firmware flashing (CubeProgrammer / DFU)
│   ├── hongli-pnp-源码重建方案.md     # Source rebuild plan
│   └── hongli-pnp-需求规格.md         # Product requirement spec
├── OpenPnP网页版硬件调试工具/    # 🐸 Frog Hardware Bench v3.0 (added 2026-10-29)
│   ├── 硬件调试台.html          #   Page structure (entry page; serve.py redirects / here)
│   ├── app.js                  #   Main app (511 lines, fully commented)
│   ├── core.js                 #   Protocol engine (192 lines, fully commented)
│   ├── core.test.js            #   Node unit tests (23 cases, commented)
│   ├── style.css               #   Stylesheet (367 lines, 12 section comments)
│   ├── serve.py                #   Local HTTP server (commented)
│   └── start.bat               #   One-click Windows launcher (ASCII comments; cmd.exe mis-parses UTF-8 CJK)
├── M300 蜂鸣器旋律编辑器/       # 🎵 Web-based M300 melody editor (renamed 2026-10-29, formerly m300_editor/)
│   ├── m300_editor.html        #   Single-file web app
│   ├── README.md               #   Usage tutorial + screenshots
│   └── images/                 #   4 feature screenshots
├── honglipnp/                  # HL PNP customization dir (OpenPnP/ bundle ~320 MB ⚠️ not tracked; README + install notes tracked)
├── config/  docker/            # Config notes (config/README.md) / containerized build (Dockerfile)
├── ini/                        # PlatformIO env matrix (grouped by MCU)
│   └── stm32f4.ini             #   contains [env:Opulo_Lumen_REV3] / REV4 / REV5
├── .editorconfig  .gitattributes  .gitignore
├── platformio.ini              # ⭐ PlatformIO entry (default_envs = Opulo_Lumen_REV5)
├── Makefile                    # make shortcuts
├── marlin.code-workspace       # VS Code multi-root workspace
├── process-palette.json        # VS Code "Process Palette" → PIO Build
├── LICENSE                     # code GPL-3.0; see "Credits & License" for HW/docs
└── README.md / README.en.md    # Multilingual docs (Chinese by default)
```

> ⚠️ `honglipnp/OpenPnP/` is a third-party binary bundle (~320 MB).
> It is excluded via `.gitignore` and never enters Git history — download it from
> [Release **HL PNP v1.0**](https://github.com/hongligongsi/qingwa-openpnp-hongli/releases/tag/lfpnp-v1.0).

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

## 🧑‍🏫 Read this first: 5 words + 3 things to prepare

If you have never flashed a microcontroller before, spend three minutes here —
the rest of the guide will make far more sense. Already flashed boards before?
Jump straight to "Quick Start".

### Five words you need

| Word | One-line meaning | What it means **here** |
|------|------------------|------------------------|
| **Firmware** | The program burned into the MCU; it runs on power-up | `firmware.bin`, about 120 KB |
| **Motherboard / feeder** | Two different boards, each with its own STM32 | The motherboard runs the head (X/Y/Z); a feeder runs tape advance |
| **Host** | The PC software that drives the machine | OpenPnP |
| **G-code** | A plain-text way to send commands | `G1 X10 Y20 F3000` = move to (10, 20) |
| **Build / compile** | Turn source into a flashable `firmware.bin` | One `pio run` command |

Two more you will definitely meet:

- **env (environment)** — a "recipe" for compiling the same source tree. This
  repo has `Opulo_Lumen_REV5`, `REV4` and `REV3`. Picking the wrong env means
  flashing board B's firmware onto board A, and it simply won't boot
- **DFU** — the bootloader mode built into STM32 chips. The PC can only write
  firmware while the board is in this mode

### You only need three things

| Category | What | Notes |
|----------|------|-------|
| **A board** | Motherboard (REV5), or a feeder controller (REV3 / REV4) | Motherboard only? Ignore feeders entirely |
| **A USB cable** | One that **carries data** | ⚠️ Many cables are charge-only — this is the single most common trap |
| **Software** | VS Code + the PlatformIO IDE extension | Installed once; it fetches the compiler and libraries itself |

**Things you do *not* need to install** (many tutorials tell you to, but skip them):

- ❌ No separate `arm-none-eabi-gcc` — PlatformIO downloads a matching version
- ❌ No Python setup — the extension brings its own
- ❌ No git — you can also click **Code → Download ZIP** on the repository page

> **Windows users** may want [Zadig](https://zadig.akeo.ie/) on hand, but only
> for the "DFU device not recognised" case (see Step 3).

### Which path are you on?

| Your goal | Read | Build environment needed? |
|-----------|------|---------------------------|
| Just get the machine running | Quick Start → Building & Flashing | ✅ Yes |
| Only tune speed / current / light | Tuning quick reference (first three parts, all in OpenPnP) | ❌ No |
| Change firmware parameters (ceilings, microsteps, travel) | Tuning quick reference → part 4, editing the firmware | ✅ Yes |
| Change code, add features | Repository Layout → `Marlin/src/` | ✅ Yes |

> Beginners: take the first path. **Do not start editing configs before the board
> connects and homes successfully** — otherwise you cannot tell a bad parameter
> from a bad wire.

### The only three files you are likely to touch

| File | What you change | Afterwards |
|------|-----------------|------------|
| `Marlin/Configuration.h` | Travel limits, speed ceilings, direction inversion, LED strip, buzzer | Rebuild + flash |
| `Marlin/Configuration_adv.h` | TMC2209 current and microsteps, homing strategy, startup tune, serial buffer | Rebuild + flash |
| `ini/stm32f4.ini` | Build target and upload method (rarely touched) | Rebuild |

Everything else **you can ignore**: `Marlin/src/` is stock Marlin source (motion
planning, G-code parsing, STM32 HAL) and this repo has not changed a line of it;
`Marlin/rev5-config/` and `Marlin/rev*-feeder-config/` are configuration archives
that never take part in a build. Details in "Repository Layout".

---

## 🚀 Quick Start

Getting a motherboard up and running takes 5 steps — about 15 minutes once you
know the flow, but budget half an hour for the very first build, which downloads
the toolchain. Every step below states how to tell it worked and what to do if it
did not.

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

**Confirm the install worked**: run `pio --version` — a version number means you
are set. In VS Code, the PlatformIO (ant) icon appearing in the activity bar is
the equivalent.

> No git? Click **Code → Download ZIP** on the repository page. The extracted
> folder is identical, and every command below works the same — just open a
> terminal inside it.

### Step 2: Build the motherboard firmware

Nothing to change — the default config is the REV5 motherboard:

```bash
pio run
```

The first build downloads library dependencies and compiles everything (a few
minutes); later builds are incremental.

**How to tell it worked**: the last lines show `SUCCESS` plus size statistics:

```text
RAM:   [==        ]  6.8% (used 13720 bytes from 202752 bytes)
Flash: [===       ] 22.7% (used 119700 bytes from 524288 bytes)
SUCCESS
```

Artifacts land in `.pio/build/Opulo_Lumen_REV5/firmware.bin` (and `.elf`).

> ⏳ The first build downloads the whole toolchain — **sitting at `Downloading`
> for five to ten minutes is normal**, so do not hit Ctrl+C. Later rebuilds take
> seconds. If it fails, read the last `Error` line; the FAQ has an entry for
> failed `pio run` builds.

### Step 3: Put the board into bootloader mode

The STM32 ships with a built-in **DFU bootloader** (USB ID `0483:df11`):

1. Hold the **BOOT0** button;
2. Press **RESET** once, then release BOOT0;
3. Plug in USB — the device should appear as `STM32 BOOTLOADER` in Device
   Manager (Windows) or `lsusb` (Linux).

**If Windows does not recognise it** (a `STM32 BOOTLOADER` entry with a yellow
warning triangle, or no new device at all):

1. Open [Zadig](https://zadig.akeo.ie/) → menu **Options → List All Devices**;
2. Pick `STM32 BOOTLOADER` in the dropdown (if it is missing, the board never
   entered DFU — redo the three steps above);
3. Set the target driver to **WinUSB** → click **Replace Driver** and wait.

This is a one-time fix; later flashes need nothing extra.

> If the board already runs this firmware, `pio run -t upload` usually works
> directly — PlatformIO detects the DFU device automatically.

### Step 4: Flash

```bash
pio run -e Opulo_Lumen_REV5 -t upload
```

`File downloaded successfully` means done; power-cycle USB and the firmware runs
(the buzzer plays a short startup tune and the LED strip cycles red/green/blue —
both are normal self-tests).

**If it gets stuck:**

| Message | Cause | Fix |
|---------|-------|-----|
| `No DFU capable USB device available` | Not in DFU mode | Redo Step 3; the order is "hold BOOT0 → tap RESET → release BOOT0" |
| Permission error (Linux), DFU device present | Missing udev rule | Add a udev rule, or run once with `sudo` |
| Flash aborts halfway | Unstable cable or port | Try another cable and a rear-panel port; avoid USB hubs |
| DFU never appears | Bootloader damaged | Use an **ST-Link** over SWD (see "Building & Flashing → upload methods") |

### Step 5: Verify

```bash
# Open a serial monitor (baud rate 250000)
pio device monitor -b 250000
```

```gcode
M115            ; reports firmware version, axis count and chip UUID (MACHINE_TYPE shows 3D Printer — normal)
M119            ; endstop states
G28             ; home all axes (verify endstop wiring first!)
```

`M115` answers with one capability line. Built the way
`Marlin/src/gcode/host/M115.cpp` assembles it, this firmware reports something
like (version and timestamp vary per build):

```text
FIRMWARE_NAME:Marlin bugfix-2.1.x (Oct 21 2026 15:30:00)
SOURCE_CODE_URL:github.com/MarlinFirmware/Marlin PROTOCOL_VERSION:1.0
MACHINE_TYPE:3D Printer EXTRUDER_COUNT:0 AXIS_COUNT:5 UUID:00380031323351...
```

Three fields are worth understanding:

- `MACHINE_TYPE:3D Printer` — **this is expected**. The firmware never sets
  `CUSTOM_MACHINE_NAME`, so Marlin's default stays; OpenPnP identifies the
  machine by the trailing `UUID` (the STM32 chip's unique ID), not by its name
- `EXTRUDER_COUNT:0` — a PnP machine has no extruder (`EXTRUDERS 0`), as designed
- `AXIS_COUNT:5` — X/Y/Z plus the I/J rotary axes (addressed as A/B in G-code)

`M119` lists the three endstops; pressing each one should flip its state.

After `G28` the machine homes and then lifts Z to `Z_AFTER_HOMING` (21 mm, see
`Configuration.h:1929`) — **keep a hand on the power switch the first time you run
`G28`**; if an axis drives into a hard stop, cut power immediately: the matching
`INVERT_X_DIR` (`Configuration.h:1888`, `true` for X, `false` for Y/Z) is wrong.

**Nothing comes back at all?** Check in this order:

1. Wrong serial port — pick the newly appeared one (Windows `COMx`, Linux
   `/dev/ttyACM0`), not a Bluetooth or virtual port;
2. Baud rate is not `250000`;
3. The USB cable is charge-only — swap it;
4. The firmware never actually flashed — redo Step 4 and confirm
   `File downloaded successfully` really appeared.

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
| `M150 R.. U.. B..` | ✅ | NeoPixel colour; `U` is the green channel (`G` is taken by G-code) |
| `M150 P<0-255>` | ✅ | **Brightness**: `P0` off, `P127` half, bare `P` = 255 full |
| `M150 S0` / `S1` | ✅ | Address only strip 1 (`PC7`) / strip 2 (`PC8`); omit `S` to set both |
| `M150 I<n>` | ✅ | Change only LED n (`I` is the index, `P` is brightness) |
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
M115                    ; 1. confirm firmware version and UUID (link check)
M119                    ; 2. push each axis onto its endstop and watch the state flip
G28                     ; 3. home
G92 X0 Y0 Z0 A0 B0      ; 4. declare this the origin (optional after G28)
G0 X50 Y50 F3000        ; 5. slow test move
M114                    ; 6. verify the reported position matches reality
M122                    ; 7. check the drivers for connection errors
M300 S523 P150          ; 8. test the buzzer
M150 R0 U255 B0         ; 9. test the LED strip (green, full brightness)
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

## 🎛 Tuning quick reference: speed / current / light

All three can be changed at **three different layers**, and changing the wrong
layer "looks like it worked but doesn't". The division of labour:

| Layer | What it controls | Rebuild needed? |
|-------|------------------|-----------------|
| OpenPnP (`.openpnp2/machine.xml`) | The `F` value actually sent, the current re-sent on every connect | ❌ |
| Marlin firmware (`Configuration*.h`) | Safety ceilings, power-on defaults | ✅ |
| Runtime G-code (serial / scripts) | Temporary, lost on reboot | ❌ |

> Precondition: **`EEPROM_SETTINGS` is not enabled** in this firmware (see FAQ),
> so any runtime `M9xx` / `M2xx` change is **not saved across power cycles**.

### 1. Machine speed

**The key point: OpenPnP sends `G1 ... F200`, and that `F` comes from the OpenPnP
axis feedrate, not from the firmware.** The firmware's `DEFAULT_MAX_FEEDRATE`
(7000 mm/s) is only a safety ceiling — raising it will not make the machine
faster, and lowering it will clip your commands.

| What you want to change | Where |
|-------------------------|-------|
| Actual move speed | OpenPnP → Machine Setup → Axes → `x` / `y` / `z1` → **Feedrate** |
| Actual acceleration | **Acceleration** on the same page |
| Firmware safety ceiling | `DEFAULT_MAX_FEEDRATE` / `DEFAULT_MAX_ACCELERATION` in `Configuration.h`, or `M203` / `M201` at runtime |
| Temporary global slowdown | `M220 S50` (half speed) over serial, `M220 S100` to restore |

Measured values in this configuration (from `.openpnp2/machine.xml`):

| Axis | Feedrate | Acceleration |
|------|----------|--------------|
| `x` | 200 mm/s | 1500 mm/s² |
| `y` | 200 mm/s | 1500 mm/s² |
| `z1` | 300 mm/s | 1200 mm/s² |
| `a` / `b` (rotary) | 50000 °/s | 500 |

**Tuning advice**: 200 mm/s on X/Y is already fast (12 m/min); the real PnP
bottleneck is usually **acceleration and Z travel**, not cruise speed. Try raising
acceleration first (1500 → 2500 → 3000) — it pays off far more than pushing the
feedrate, which invites lost steps and poor positioning.

Reconnect once in OpenPnP (or restart it) after changing these.

### 2. Motor current

**The easiest route: edit the OpenPnP connect script — no firmware rebuild.**

Because EEPROM is off, current values in the firmware are lost on reboot — but the
`CONNECT_COMMAND` in `machine.xml` re-sends them on every connection:

```gcode
M906 Y1000 X900   ; set Y/X motor current
M906 A200 B200    ; set L/R (rotary A/B) motor current
```

Edit those two lines (units are **mA RMS**). To cover Z, add `M906 Z800`. Note that
`A` / `B` are the firmware's I/J rotary axes (`AXIS4_NAME 'A'`, `AXIS5_NAME 'B'`).

Compile-time defaults live in `Configuration_adv.h`:

| Macro | Value | Axis |
|-------|-------|------|
| `X_CURRENT` | 800 mA | X |
| `Y_CURRENT` | 1000 mA | Y (dual motors) |
| `Z_CURRENT` | 800 mA | Z |
| `I_CURRENT` | 200 mA | rotary A (called `a` in OpenPnP) |
| `J_CURRENT` | 200 mA | rotary B (called `b` in OpenPnP) |

⚠️ **Do not simply crank it up**: a TMC2209 held above **1200 mA** gets noticeably
hot, and with poor cooling it will hit thermal protection and lose steps. The
200 mA on the rotary axes is deliberate (light load); if rotation slips, raise it
**100 mA at a time**.

### 3. Ring light brightness

The ring light is driven by `M150`: **brightness is `P` (0–255), colour is
`R` / `U` / `B`** (`U` = green, because `G` is taken by G-code).

| Goal | Command |
|------|---------|
| Full white, maximum | `M150 P255 R255 U255 B255` |
| About 40%, keeping the colour | `M150 K P102` |
| Warm white (kinder for long sessions) | `M150 P255 R255 U180 B80` |
| Off | `M150 P0` |
| Only the second strip | `M150 S1 P255 R255 U255 B255` |

⚠️ `M150 P102` on its own clears the colour (so nothing lights up) — add `K` to
change brightness while keeping the colour.

**To pin a brightness in OpenPnP**: Machine Setup → actuator `LED` → its on
command is `M150 P255 R255 U255 B255`; lower the `P255` (e.g.
`M150 P120 R255 U255 B255`) so every actuation uses that level automatically.

### 4. Editing the firmware (compile time)

**Editing the firmware is not the first tool for changing speed** — OpenPnP
overwrites several values as soon as it connects:

| What OpenPnP sends, and when | Which firmware value it overrides |
|------------------------------|-----------------------------------|
| `M204 S<accel>` before every move (`MOVE_TO_COMMAND`) | `DEFAULT_ACCELERATION` / `DEFAULT_TRAVEL_ACCELERATION` |
| `M906 X.. Y..` and `M906 A.. B..` on every connect | `X_CURRENT` through `J_CURRENT` |
| `M150 P..` whenever the light is switched on | `NEOPIXEL_BRIGHTNESS`, only used while no `M150` arrives |

So firmware edits genuinely matter in four cases:

1. **Raising a safety ceiling** — the ceiling decides how fast or how hard the
   machine *can* go; anything higher from OpenPnP gets clipped
2. **Firmware-only settings** — microsteps (`_MICROSTEPS`), homing speed, travel
   limits, soft endstops: OpenPnP has no say in these
3. **Standalone operation** — with no host attached, running from serial or a
   script, the compiled values are the only ones there are
4. **Making parameters persist** — only after enabling `EEPROM_SETTINGS` do
   `M906` / `M203` survive a power cycle

#### Speed (`Marlin/Configuration.h`)

| Macro | Line | Current value | Purpose |
|-------|------|---------------|---------|
| `DEFAULT_MAX_FEEDRATE` | 1363 | `{7000,7000,1000,50000,50000}` | Speed **ceiling** for X/Y/Z/I/J (mm/s, °/s) |
| `DEFAULT_MAX_ACCELERATION` | 1377 | `{15000,15000,10000,10000,10000}` | Hard acceleration **ceiling** |
| `DEFAULT_ACCELERATION` | 1396 | `2000` | Default acceleration (overridden by OpenPnP's `M204 S`) |
| `DEFAULT_TRAVEL_ACCELERATION` | 1399 | `2500` | Travel acceleration (also overridden) |
| `JUNCTION_DEVIATION_MM` | 1449 | `0.013` | Corner deviation — smaller follows the path tighter but slower |
| `DEFAULT_AXIS_STEPS_PER_UNIT` | 1355 | `{320,320,40,4.44,4.44}` | Steps per mm; touch it only for microsteps or pulley changes |
| `HOMING_FEEDRATE_MM_M` | 2462 | `{150,150,150,50,50}×60` | Homing speed (mm/min) |

To set acceleration 3000 in OpenPnP, `DEFAULT_MAX_ACCELERATION` must be ≥ 3000
(it is 15000 today, so there is headroom). **If you set 20000 in OpenPnP and feel
no difference, this 15000 ceiling is what clipped it.**

#### Current (`Marlin/Configuration_adv.h`)

| Macro | Line | Current | Axis |
|-------|------|---------|------|
| `X_CURRENT` | 2850 | 800 mA | X |
| `Y_CURRENT` | 2870 | 1000 mA | Y |
| `Z_CURRENT` | 2890 | 800 mA | Z |
| `I_CURRENT` | 2930 | 200 mA | rotary A |
| `J_CURRENT` | 2940 | 200 mA | rotary B |

Just change the numbers; the unit is mA RMS. **There is no separate Y2 macro** —
it reads `Y2_CURRENT Y_CURRENT`, so editing Y covers both gantry motors.

#### Light brightness (`Marlin/Configuration.h`)

| Macro | Line | Current | Purpose |
|-------|------|---------|---------|
| `NEOPIXEL_BRIGHTNESS` | 3758 | `255` | Power-on brightness of strip 1 (`PC7`) |
| `NEOPIXEL2_BRIGHTNESS` | 3765 | `255` | Power-on brightness of strip 2 (`PC8`) |
| `NEOPIXEL_STARTUP_TEST` | 3759 | on | Cycles red/green/blue at boot; comment out if it annoys you |

These only set the brightness **while no `M150` arrives**. OpenPnP sends
`M150 P255 ...` the moment it lights the ring, so it goes back to full — for a
permanently dimmer ring, lower the `P` in the actuator command instead.

#### Four steps after every edit

```bash
# 1. Sync the archive copy (the two must stay byte-identical)
cp Marlin/Configuration.h Marlin/Configuration_adv.h Marlin/rev5-config/

# 2. Validate comment structure and schema (2444-item baseline)
python buildroot/scripts/check-config-i18n.py

# 3. Confirm no code was broken: macro-definition table + preprocessor diff
python buildroot/scripts/check-config-code-intact.py --ref HEAD

# 4. Build and flash (DFU by default)
pio run -e Opulo_Lumen_REV5 -t upload
```

To build without flashing: `pio run -e Opulo_Lumen_REV5`. The artefact lands in
`.pio/build/Opulo_Lumen_REV5/firmware.bin`.

#### Three rules for editing configs

1. **Change numbers, not structure**: `// @section`, `:[...]` option lists and
   parenthesised units like `(mm)` are what `schema.py` parses — breaking them
   silently drops options, or fails the build outright
2. **Microsteps and steps/mm move together**: dropping `X_MICROSTEPS` from 64 to
   32 also requires `DEFAULT_AXIS_STEPS_PER_UNIT` X to go from 320 to 160, or
   1 mm becomes 2 mm
3. **Do not over-current**: a TMC2209 held above 1200 mA runs hot and loses
   steps; raise it 100 mA at a time

### 5. What survives a reboot

| How you changed it | Rebuild? | Persists? |
|--------------------|----------|-----------|
| OpenPnP axis feedrate / acceleration | ❌ | ✅ |
| `M906` in the OpenPnP connect script | ❌ | ✅ (re-sent on every connect) |
| Brightness of the OpenPnP `LED` actuator | ❌ | ✅ |
| `M203` / `M201` / `M204` over serial | ❌ | ❌ |
| `M906` over serial | ❌ | ❌ |
| `M150` over serial | ❌ | ❌ |
| Editing `Configuration*.h` and reflashing | ✅ | ✅ |

> To make runtime `M906` persistent, enable `EEPROM_SETTINGS` in `Configuration.h`
> and rebuild (the board already provides 8 KB of SRAM emulation).

---

## 🛠 FAQ

<details>
<summary><b><code>pio run</code> fails, or hangs at "Downloading"?</b></summary>

Three cases:

**① Stuck at `Downloading` for a long time** — the toolchain and libraries are
being fetched; the first run pulls several hundred MB. A slow network makes this
worse, so use a mirror or proxy if needed. **Do not hit Ctrl+C**: an interrupted
download leaves half a package behind and the next build fails strangely. Delete
the matching folder under `~/.platformio/packages` and retry.

**② An `Error` mentioning a library** — dependencies are incomplete; run
`pio pkg update` once and rebuild.

**③ An error mentioning `Configuration.h` or `schema`** — the configuration was
broken (for example, a `:[...]` option list split across lines, or a `// @section`
line translated). Run:

```bash
python buildroot/scripts/check-config-i18n.py
```

It names the offending entry; use `git diff Marlin/Configuration.h` to compare
and restore.

> The nuclear option for a corrupted environment: delete the project's `.pio/`
> folder and rebuild (dependencies are re-downloaded; your source is untouched).
> On Windows, if `pio run` stalls on bulk deletion, add `-v` to run in verbose mode.
</details>

<details>
<summary><b>No serial port after flashing?</b></summary>

Use a data USB cable to the STM32's USB port; you may need the USB CDC driver on
first use (Windows). A new serial device should appear in Device Manager /
`ls /dev/tty*`. Baud rate is `250000`.
</details>

<details>
<summary><b>How do I check the running firmware version/config?</b></summary>

Send `M115` from your host — the response includes the version string,
`AXIS_COUNT:5` and the chip UUID (`MACHINE_TYPE` is Marlin's default
`3D Printer`, which is expected).
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
<summary><b>How do I dim the ring light or change its colour?</b></summary>

The ring light is a WS2812 strip on `PC7` (`NEOPIXEL_PIN`, 18 LEDs, `NEO_GRB`),
driven by `M150`. **Brightness is `P`, colour is `R` / `U` / `B`** — `U` is the
green channel because `G` is already taken by G-code.

| Goal | Command |
|------|---------|
| Full white, maximum | `M150 P255 R255 U255 B255` |
| 40% brightness, keeping the colour | `M150 K P102` |
| Warm white (easier on the eyes) | `M150 P255 R255 U180 B80` |
| Off | `M150 P0` |
| Only strip 1 / strip 2 | `M150 S0 ...` / `M150 S1 ...` |

⚠️ **Two traps:**

1. **`P` is brightness (0–255), not a pixel count.** To change LED *n* only,
   use `I<n>`.
2. **`M150 P102` on its own clears the colour** (unspecified channels default to
   0, i.e. dark). To change brightness while keeping the colour, add `K`:
   `M150 K P102`. Otherwise write all three colour channels.

Omitting `S` addresses both strips (`PC7` + `PC8`); if your machine only has the
ring light wired, the second strip only reacts when LEDs are attached.

**To pin a brightness in OpenPnP**: Machine Setup → actuator `LED` → its on
command is `M150 P255 R255 U255 B255`, off is `M150 P0`. Lower the `P255`
(e.g. `M150 P120 R255 U255 B255`) so every actuation uses the same comfortable
level instead of retyping it.

> Brightness changes intensity, not colour temperature. If vision fails from
> overexposure, lower `P` first rather than turning the light off — with no
> light the part outline disappears too. Note that `NEOPIXEL_STARTUP_TEST` is
> enabled, so the strip cycles red/green/blue at power-up; that is a self-test,
> not a fault.
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

<details>
<summary><b>How do I use the M300 melody editor?</b></summary>

The repo ships a plain HTML tool, `m300_editor/index.html`, for editing the
startup tune visually on your computer.

**Opening it:**
- double-click `m300_editor/index.html` in a file manager, or
- run `python -m http.server 8765` in the project root and open
  `http://127.0.0.1:8765/m300_editor/index.html`.

**Typical flow:**
1. Paste the G-code from inside `STARTUP_COMMANDS` into the import box at the
   bottom of the page and click "⬆ import from below" — the note table fills in
   with frequencies and durations.
2. Add, remove or edit notes (Hz / ms), or click a preset (simple beep, Morse
   rhythm, Do-Mi-Sol, startup melody, ...).
3. Click "▶ Play" to preview; click a block on the timeline to audition a single
   note.
4. When happy, click "⬇ Export G-code" → "📋 Copy" and paste it back inside the
   quotes of `STARTUP_COMMANDS` in `Configuration_adv.h`, then rebuild and flash.

**About custom waveforms:** the editor offers hand-drawn waveforms and harmonic
sliders, but those only affect the **browser preview**. The piezo buzzer on the
board only produces square waves — `M300` controls frequency and duration and
nothing more.

Full tutorial with screenshots: [m300_editor/README.md](m300_editor/README.md).
</details>

---

## 📚 Further reading & calibration notes

This repo covers the firmware side; for **frame assembly, OpenPnP setup and
machine calibration** follow the upstream and community docs. Links below are
collected from the original author's "Frog" replication guide:

| Resource | Link | Notes |
|----------|------|-------|
| Opulo quick start | <https://ohai.opulo.io/> | official getting started |
| Opulo full docs | <https://docs.opulo.io/> | assembly, calibration, usage (authoritative) |
| LumenPnP repository | <https://github.com/opulo-inc/lumenpnp/> | hardware files + firmware source |
| Ruizao Tech Yuque (zh) | <https://www.yuque.com/lonlypan/td6smc/rgvt49zsg6t72n9u> | Chinese community translation |
| Ruizao Tech Feishu (zh) | <https://tcnyw794ws3e.feishu.cn/wiki/LVXow8r6MiKV5KkbJgZcMZUrnPg> | same content, minor differences |
| Zi Jin's tutorial (zh) | <https://www.zbkcn.top/docs/docs4_lumenpnp/01LumenPnP/> | Chinese community guide |

### Three calibration rules (from the original author — make or break)

1. **Zero everything before calibrating**: clear all compensation data (backlash
   compensation, nozzle concentricity) and disable those options plus reference
   point re-homing. Otherwise new calibration stacks on old compensation and
   drifts further with every pass.
2. **Approach every mark from one direction only**: every axis has backlash
   (some more than others). A position approached left-to-right differs from
   one approached right-to-left — always come at the target from the same side.
3. **Vision pipeline and position calibration are independent**: if ambient
   light changes force you to redo exposure, only the vision pipeline changes.
   Previously calibrated mechanical positions remain valid — no need to redo them.

> ⚠️ Tip: in OpenPnP prefer editing the values directly in Machine Setup over
> the "Issues & Solutions" wizard — they are equivalent, but direct edits make
> it clear what changed and are easier to roll back.

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
