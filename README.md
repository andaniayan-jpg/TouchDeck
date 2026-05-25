# TouchDeck

A macropad with touch sensor
<img width="1748" height="2480" alt="TouchDeck product" src="https://github.com/user-attachments/assets/716087a9-ae82-4db0-bb94-4712fb55cfb9" />

Touchdeck is a macropad with touch sensitive display, it has no keys. 

## Table of Contents

WHAT IS TOUCHDECK
WHAT MAKES IT UNIQUE
FEATURES
HOW TO USE IT
BILL OF MATERIALS
SCHEMATIC OVERVIEW
PCB details
3D design 
Assembly Guide
Firmware

---

## What is TouchDeck?

TouchDeck is a device made with ESP32 as the MCU, it acts a touch pad making it both a macropad and a scribble pad. It has 2 modes.

**1.  Macropad Mode**
The screen acts like a touchpad, which digital keys visible on the screen, it enables the device to act as a Touch Screen MacroPad.

**2. Scribble Pad Mode**
When switched to Scribble pad mode, it shows a plain white canvas that can be used to take notes, doodle and etc. NOTHING IS SAVED PERMANENTLY, ONCE EXITING THIS MODE, REMOVES ALL THE WORK. 
---

## What Makes It Unique

It is unique because it doesnt use any buttons or keys like ordinary macropad, it has touch screen. It is unique because it acts as both macropad and scribble pad.
It has a customised PCB, LED, buzzer and  etc.
---

## Main Features

- ESP32-S3 based custom PCB
- 3.5 inch SPI TFT touchscreen display
- XPT2046 touch controller
- USB-C power and data
- On-screen macro buttons
- Temporary scribble/doodle mode
- Back and clear controls
- USB HID keyboard shortcut output
- WS2812B RGB status LED
- Buzzer feedback


<img width="807" height="637" alt="PCB top view" src="https://github.com/user-attachments/assets/af7c6ff3-79cf-40f5-9270-ce6b370cb6bb" />
<img width="580" height="592" alt="PCB bottom view" src="https://github.com/user-attachments/assets/c1d59b20-0be1-4b21-8239-1a179d2a4b46" />

---

## How to Use It

### 1. Power the Device

Connect the device with the laptop or PC. Turn on with power switch, RGB LED turns on and shows the status.

### 2. Select the mode, Macropad or scribble. 

When powered on, the screen shows two main options:

- **MacroPad Mode**
- **ScribblePad Mode**

Tap the mode you want to use.

### 3. MacroPad Mode

The touchscreen shows several shortcut buttons. When a button is touched, the ESP32-S3 sends a keyboard shortcut to the connected laptop via USB HID.

You can add, remove, increase and reduce the sizes of buttons according to your choice by changing the firmware, as it is a custom PCB!!!


### 4. ScribblePad Mode

The screen becomes a temporary drawing area. You can write with your finger or a capacitive stylus, doodle quick ideas, sketch small layouts, or scribble notes while thinking.

The drawing is **not saved** — it is purely temporary.

- **Clear** — removes the drawing from the screen
- **Back** — returns to the home screen and clears the canvas

<img width="1093" height="710" alt="UI overview" src="https://github.com/user-attachments/assets/39bed192-fa30-4eb7-ba5f-bf6ecf6554f1" />

---

## Bill of Materials (BOM)

visit "" for BOM. 

> 
## Component connections
   for component connections, refer to the schematic image or go through the schematic source file to view exact connections. 

## Assembly Guide
   All the components used are present in the folder `cad_assembly` in STEP/STP format, for 3D model, Enclousre, and 3D parts  overview, go through that folder.



### Tools needed
-Soldering iron and flux
-Tweezers
-USB-C data cable


---
### Step 1 — Solder the Small Components

Let's start by soldering the tiny parts. First, apply some flux to the pads where the resistors and capacitors will go. Carefully position each component in place and solder them down. Since resistors and capacitors are the smallest parts, it's easier to tackle these first.

### Step 2 — Solder the USB-C Connector 

Next up is the USB-C connector. Begin by putting a little solder on the ground pads in the center of the PCB. Align the USB-C connector so all the pins match up with the pads. Tack down one corner to hold it in place, then double-check everything’s aligned before soldering the rest. Finally, solder the 5V and ground shield tabs — these will need a bit more heat to get a good connection.

### Step 3 — Solder the Voltage Regulator and ESD IC

Time to solder the voltage regulator and ESD IC. Start with the AP2112K (U2) in its SOT-23-5 package. Just make sure to pay attention to the orientation according to the silkscreen. After that, move on to the USBLC6-2SC6 (U3) in its SOT-23-6 package, keeping an eye on the pin 1 indicator.

### Step 4 — Solder the Transistor and Buzzer

For the next step, solder the transistor (Q1), which is the 2N3904 in the SOT-23 footprint. Then, insert the passive buzzer (LS1) into the through-hole, making sure the positive marking aligns with the pad label. Solder it from the bottom.

### Step 5 — Solder the WS2812B LED (U4)

Next, let’s work on the WS2812B LED, which has an integrated controller. First, apply a bit of flux to all four pads. Solder one of the corner pads first, then work on the others. Just a tip: try not to apply heat for too long on each pad.

### Step 6 — Solder the Push Buttons

Moving on, place the push buttons (SW1 for Boot and SW2 for Reset) into their through-holes. Insert them from the top and then solder their four legs from the bottom.

### Step 7 — Solder the ESP32-S3-WROOM-1 Module

This is one of the most important parts of the project. Start by applying flux on all the pads on three sides of the module footprint. Carefully position the module, ensuring the edges align with the PCB pads. Tack down two corner pads to secure it, then solder each pad using a drag-soldering method or solder wick. Make sure to check under a magnifying glass to spot any solder bridges.

Remember: **Do not solder the antenna area.** The module has a PCB antenna, so keep that section clear.

### Step 8 — Solder the Display Connector (J2)

Now, insert the 1×14 female header into J2. If you’re not using a header, you can solder wires directly instead. Solder all 14 pins from the bottom.

### Step 9 — Power-On Test (Before Display)

Before connecting the display, let's check if the power is working. Connect a USB-C cable from the board to your computer. Use a multimeter to measure the voltage between the 3.3V test point and ground. You should see a reading between **3.28–3.35V**. If it’s 0V or over 3.4V, disconnect immediately and check the solder joints on U2 and C1/C2.

### Step 10 — Attach the Display Module

Now it’s time to add the 3.5" ILI9488 display module into J2. Be careful to check the pin 1 orientation — there’s a marking on the silkscreen to help you out. If you’re doing a permanent build, you might want to use a little hot glue or double-sided foam tape to hold the display flat against the PCB.

### Step 11 — Mount Everything in the Enclosure

Finally, position the PCB in the bottom of the enclosure, making sure the mounting holes line up with the standoff posts. Insert the M2.5 × 6mm standoffs from below through the PCB holes. Then, place the enclosure top frame over the display and secure it with M2.5 × 4mm screws on both the top and bottom. 

And that’s it! At this point, you should have everything nicely assembled and ready to go.

---



---


Hardware design files are released under CERN Open Hardware Licence v2 (CERN-OHL-S).
Firmware source code is released under MIT License.
See `LICENSE` for full terms.
