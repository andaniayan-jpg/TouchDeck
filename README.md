# TouchDeck

A custom ESP32-S3 powered touchscreen macropad and temporary scribble pad for creators, students, and developers.

<img width="1748" height="2480" alt="TouchDeck product" src="https://github.com/user-attachments/assets/716087a9-ae82-4db0-bb94-4712fb55cfb9" />

TouchDeck replaces physical macro keys with a touchscreen interface. It lets users trigger laptop shortcuts through on-screen buttons and also includes a quick doodle/scribble mode where users can write or sketch temporary ideas and clear them instantly.

---

## Table of Contents

- [What is TouchDeck?](#what-is-touchdeck)
- [What Makes It Unique](#what-makes-it-unique)
- [Main Features](#main-features)
- [How to Use It](#how-to-use-it)
- [Bill of Materials (BOM)](#bill-of-materials-bom)
- [Schematic Overview](#schematic-overview)
- [PCB Details](#pcb-details)
- [Enclosure](#enclosure)
- [Assembly Guide](#assembly-guide)
- [Firmware Flashing Instructions](#firmware-flashing-instructions)
- [Troubleshooting](#troubleshooting)

---

## What is TouchDeck?

TouchDeck is a compact touchscreen control pad built around the ESP32-S3. It has two main features:

**1. Touchscreen Macropad Mode**
On-screen buttons act like a physical macropad. Each button can send keyboard shortcuts to a laptop — copy, paste, undo, new tab, app shortcuts, or custom productivity actions.

**2. Temporary Scribble Pad Mode**
A blank touchscreen canvas lets the user quickly draw, write, doodle, or sketch something. The scribble is temporary and disappears when the user presses the back/clear button.

---

## What Makes It Unique

Most small macropads use physical buttons or mechanical switches. TouchDeck uses a touchscreen instead, so the same hardware can show different controls depending on the mode.

It is also not just a display. It is an interactive device with:

- Touch buttons
- Temporary drawing canvas
- USB keyboard shortcut output
- Status feedback through LED and buzzer
- Custom PCB
- 3D printed enclosure
- Compact desktop form factor

---

## Main Features

- ESP32-S3 based custom PCB
- 3.5 inch SPI TFT touchscreen display
- ILI9488 display driver
- XPT2046 touch controller
- USB-C power and data
- On-screen macro buttons
- Temporary scribble/doodle mode
- Back and clear controls
- USB HID keyboard shortcut output
- WS2812B RGB status LED
- Buzzer feedback
- Custom enclosure support

<img width="807" height="637" alt="PCB top view" src="https://github.com/user-attachments/assets/af7c6ff3-79cf-40f5-9270-ce6b370cb6bb" />
<img width="580" height="592" alt="PCB bottom view" src="https://github.com/user-attachments/assets/c1d59b20-0be1-4b21-8239-1a179d2a4b46" />

---

## How to Use It

### 1. Power the Device

Connect TouchDeck to your laptop using a USB-C data cable. The cable provides both power and the data connection for sending keyboard shortcuts. No battery is needed — the device is designed to work as a laptop-connected macropad.

### 2. Boot into the Home Screen

When powered on, the screen shows two main options:

- **MacroPad Mode**
- **ScribblePad Mode**

Tap the mode you want to use.

### 3. MacroPad Mode

The touchscreen shows several shortcut buttons. When a button is touched, the ESP32-S3 sends a keyboard shortcut to the connected laptop via USB HID.

| Button | Shortcut Sent |
|---|---|
| Copy | `Ctrl + C` |
| Paste | `Ctrl + V` |
| Undo | `Ctrl + Z` |
| Redo | `Ctrl + Y` |
| New Tab | `Ctrl + T` |
| Close Tab | `Ctrl + W` |
| Reopen Tab | `Ctrl + Shift + T` |
| ChatGPT | `Ctrl + Alt + G` (custom) |
| VS Code | `Ctrl + Alt + V` (custom) |
| Music | `Ctrl + Alt + M` (custom) |

Custom shortcuts can be mapped on the laptop — a button on TouchDeck sends a key combo (e.g., `Ctrl + Alt + C`) and the OS is configured to open a specific app or website on that combo.

### 4. ScribblePad Mode

The screen becomes a temporary drawing area. You can write with your finger or a capacitive stylus, doodle quick ideas, sketch small layouts, or scribble notes while thinking.

The drawing is **not saved** — it is purely temporary.

- **Clear** — removes the drawing from the screen
- **Back** — returns to the home screen and clears the canvas

<img width="1093" height="710" alt="UI overview" src="https://github.com/user-attachments/assets/39bed192-fa30-4eb7-ba5f-bf6ecf6554f1" />

---

## Bill of Materials (BOM)

The full machine-readable BOM is in `BOM.csv`. The table below covers all major components.

| # | Reference | Description | Value / Part Number | Qty | Notes |
|---|---|---|---|---|---|
| 1 | U1 | Main microcontroller module | ESP32-S3-WROOM-1-N8 | 1 | 8 MB flash, built-in USB |
| 2 | U2 | LDO voltage regulator | AP2112K-3.3V | 1 | SOT-23-5 package |
| 3 | U3 | USB ESD protection | USBLC6-2SC6 | 1 | SOT-23-6 package |
| 4 | U4 | RGB status LED | WS2812B | 1 | 5050 package |
| 5 | Q1 | NPN transistor (buzzer driver) | 2N3904 | 1 | SOT-23 |
| 6 | LS1 | Passive buzzer | 5V passive buzzer | 1 | Through-hole |
| 7 | J1 | USB-C receptacle | USB Type-C 16-pin | 1 | SMD, mid-mount |
| 8 | J2 | Display connector | 1×14 female header, 2.54mm | 1 | Or solder directly |
| 9 | SW1 | Boot button | 6mm tactile push button | 1 | |
| 10 | SW2 | Reset button | 6mm tactile push button | 1 | |
| 11 | R1, R2 | USB CC pull-down resistors | 5.1kΩ, 0402 | 2 | Required for USB-C DFP |
| 12 | R3 | Buzzer base resistor | 1kΩ, 0402 | 1 | |
| 13 | R4 | LED data resistor | 33Ω, 0402 | 1 | |
| 14 | R5, R6 | USB D+/D− resistors | 27Ω, 0402 | 2 | |
| 15 | C1, C2 | Bulk decoupling capacitors | 10µF, 0805 | 2 | |
| 16 | C3–C6 | Bypass capacitors | 100nF, 0402 | 4 | Place near power pins |
| 17 | DISP1 | 3.5" TFT touchscreen module | ILI9488 + XPT2046 | 1 | SPI interface, 320×480 |
| — | — | M2.5 × 6mm hex standoffs | Brass or nylon | 4 | PCB to enclosure |
| — | — | M2.5 × 4mm screws | Steel | 8 | Top and bottom |
| — | — | USB-C data cable | USB 2.0, full data | 1 | Not charge-only |

> **Display Note:** Use a 3.5" ILI9488 SPI module that includes the XPT2046 touch controller on the same board. Confirm the pinout before soldering — some modules reorder the 14-pin connector.

---

## Schematic Overview

The full KiCad schematic is in the `hardware/` folder (`touchdeck.kicad_sch`). A PDF export is at `hardware/schematic.pdf`.

### Key Signal Connections

**ESP32-S3 → Display (SPI)**

| ESP32-S3 GPIO | Display Pin | Signal |
|---|---|---|
| GPIO 10 | CS | Display chip select |
| GPIO 11 | MOSI | SPI data out |
| GPIO 12 | SCK | SPI clock |
| GPIO 13 | MISO | SPI data in |
| GPIO 14 | DC | Data / Command select |
| GPIO 15 | RST | Display reset |
| GPIO 16 | BL | Backlight (PWM) |

**ESP32-S3 → Touch Controller (XPT2046, shared SPI bus)**

| ESP32-S3 GPIO | Touch Pin | Signal |
|---|---|---|
| GPIO 11 | T_DIN | Shared MOSI |
| GPIO 12 | T_CLK | Shared SCK |
| GPIO 13 | T_DO | Shared MISO |
| GPIO 17 | T_CS | Touch chip select |
| GPIO 18 | T_IRQ | Touch interrupt |

**ESP32-S3 → Peripherals**

| ESP32-S3 GPIO | Component | Signal |
|---|---|---|
| GPIO 48 | WS2812B (U4) | RGB LED data |
| GPIO 38 | Q1 base via R3 | Buzzer PWM |
| GPIO 0 | SW1 | Boot button |
| EN | SW2 | Reset button |

**Power Rail**

```
USB-C VBUS (5V)
    └── USBLC6-2SC6 (ESD protection)
    └── AP2112K-3.3V (LDO regulator)
            └── 3.3V rail → ESP32-S3, Display, XPT2046, WS2812B
```

USB data lines (D+/D−) go through 27Ω resistors directly to the ESP32-S3's built-in USB transceiver on GPIO 19 (D−) and GPIO 20 (D+).

---

## PCB Details

PCB design files are in `hardware/` (KiCad 7.x format).

### Specifications

| Parameter | Value |
|---|---|
| Board dimensions | 90 mm × 70 mm |
| Layers | 2 (top copper + bottom copper) |
| PCB thickness | 1.6 mm |
| Minimum trace width | 0.2 mm |
| Minimum clearance | 0.2 mm |
| Surface finish | HASL or ENIG |
| Solder mask | Green (or your preferred color) |
| Copper weight | 1 oz |

### Ordering the PCB

Gerber files are exported to `hardware/gerbers/`. To order:

1. Zip the contents of `hardware/gerbers/`
2. Upload to your preferred fab (JLCPCB, PCBWay, OSHPark, etc.)
3. Use default 2-layer settings; 1.6mm thickness
4. Minimum quantity is typically 5 boards

### Layer Description

| Layer | Purpose |
|---|---|
| F.Cu (top) | Signal traces, ESP32-S3 module, SMD passives |
| B.Cu (bottom) | Ground plane, USB-C connector, buzzer |
| F.Silkscreen | Component labels and reference designators |
| B.Silkscreen | Project name, version |
| F.Mask / B.Mask | Solder mask |
| Edge.Cuts | Board outline |

---

## Enclosure

### 3D Printed Version

STL files are in `enclosure/stl/`. Print two parts:

- `enclosure_bottom.stl` — main body with PCB mounting posts
- `enclosure_top.stl` — display frame/bezel

**Recommended print settings:**

| Parameter | Value |
|---|---|
| Material | PLA or PETG |
| Layer height | 0.2 mm |
| Infill | 20% |
| Supports | None required |
| Perimeters | 3 |

The display window in the top frame is sized for the 3.5" module. The bottom has four M2.5 boss posts that align with the PCB mounting holes.

### Acrylic Version

Laser-cutting files are in `enclosure/dxf/`. Cut from 3mm acrylic. Stack layers:

1. Bottom plate
2. Spacer ring (sides)
3. Top frame with display cutout

Use M2.5 × 20mm screws and brass standoffs to stack the layers.

---

## Assembly Guide

Follow these steps in order. Do not power the board until all soldering is complete.

### Tools Required

- Soldering iron (fine tip, 320–350°C)
- Solder (0.6mm, 63/37 or lead-free)
- Flux pen
- Tweezers
- Multimeter
- USB-C data cable
- Computer with Python 3 and esptool installed

---

### Step 1 — Solder SMD Passives

Start with the smallest components to avoid working around larger parts.

1. Apply flux to pads for C3–C6 (100nF bypass caps) and R1–R6 (resistors).
2. Place and solder each component. Use the silkscreen and schematic PDF for orientation.
3. Solder C1 and C2 (10µF bulk caps) — observe polarity marking if using polarized caps.

> **Tip:** Solder one pad of each component first to tack it in place, then reflow and solder the second pad.

---

### Step 2 — Solder USB-C Receptacle (J1)

1. Apply a small amount of solder to the center GND pads on the PCB.
2. Align the USB-C connector, ensuring all pins line up with the pads.
3. Tack one corner pad, then check alignment before soldering all remaining pads.
4. Solder the 5V and GND shield tabs last — they require more heat.

---

### Step 3 — Solder Voltage Regulator and ESD IC

1. Solder U2 (AP2112K) — SOT-23-5 package. Note pin 1 orientation from silkscreen.
2. Solder U3 (USBLC6-2SC6) — SOT-23-6 package. Note pin 1 dot.

---

### Step 4 — Solder Transistor and Buzzer

1. Solder Q1 (2N3904) in SOT-23 footprint. Check the datasheet for base/collector/emitter pin order.
2. Insert LS1 (passive buzzer) through-hole. Match the `+` marking on the buzzer to the pad label. Solder from the bottom.

---

### Step 5 — Solder WS2812B LED (U4)

The WS2812B is an SMD LED with an integrated controller — it is sensitive to heat.

1. Apply flux to all four pads.
2. Solder one corner pad quickly, check alignment.
3. Solder remaining pads. Do not apply heat for more than 3–4 seconds per pad.
4. The notched corner of the package marks pin 1 (GND). Match it to the PCB silkscreen.

---

### Step 6 — Solder Push Buttons

1. Place SW1 (Boot) and SW2 (Reset) — 6mm tactile buttons, through-hole.
2. Insert from the top, solder four legs from the bottom.

---

### Step 7 — Solder ESP32-S3-WROOM-1 Module

This is the most critical step.

1. Apply flux along all castellated pads on three sides of the module footprint.
2. Place the module carefully, aligning the castellated edges with the PCB pads.
3. Tack two corner pads on opposite sides to lock position.
4. Solder each pad on all three sides using a drag-soldering technique or iron with solder wick.
5. Inspect under magnification for solder bridges.

> **Do not solder the antenna area.** The module has a PCB antenna on one end — keep that end clear of anything conductive.

---

### Step 8 — Solder Display Connector (J2)

1. Insert the 1×14 female header into J2, or solder wires directly if skipping the header.
2. Solder all 14 pins from the bottom.

---

### Step 9 — Power-On Test (Without Display)

Before attaching the display, verify the power rails.

1. Connect a USB-C cable between the board and a computer.
2. Using a multimeter, measure between the 3.3V test point and GND.
3. Expected reading: **3.28–3.35V**.
4. If 0V or above 3.4V, disconnect immediately and inspect U2 and C1/C2 solder joints.

---

### Step 10 — Attach Display Module

1. Insert the 3.5" ILI9488 display module into J2.
2. Confirm pin 1 orientation — the silkscreen shows pin numbering. Misaligning the display can damage it.
3. For a permanent build, use a small dab of hot glue or double-sided foam tape to hold the display flat against the PCB.

---

### Step 11 — Mount to Enclosure

1. Place the PCB into the enclosure bottom, aligning mounting holes with the boss posts.
2. Insert M2.5 × 6mm standoffs from below through the PCB holes.
3. Place the enclosure top frame over the display.
4. Secure with M2.5 × 4mm screws on top and bottom.

---


Hardware design files are released under CERN Open Hardware Licence v2 (CERN-OHL-S).
Firmware source code is released under MIT License.
See `LICENSE` for full terms.
