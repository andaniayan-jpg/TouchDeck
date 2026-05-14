# TouchDeck

A custom ESP32-S3 powered touchscreen macropad and temporary scribble pad for creators, students, and developers.

<img width="1748" height="2480" alt="imresizer-oduct" src="https://github.com/user-attachments/assets/716087a9-ae82-4db0-bb94-4712fb55cfb9" />





TouchDeck replaces physical macro keys with a touchscreen interface. It lets users trigger laptop shortcuts through on-screen buttons and also includes a quick doodle/scribble mode where users can write or sketch temporary ideas and clear them instantly.

---

## What is TouchDeck?

TouchDeck is a compact touchscreen control pad built around the ESP32-S3. It has two main features:

1. **Touchscreen Macropad Mode**  
   On-screen buttons act like a physical macropad. Each button can send keyboard shortcuts to a laptop, such as copy, paste, undo, new tab, app shortcuts, or custom productivity actions.

2. **Temporary Scribble Pad Mode**  
   A blank touchscreen canvas lets the user quickly draw, write, doodle, or sketch something. The scribble is temporary and disappears when the user presses the back/clear button.

The goal is to combine the usefulness of a macropad with the freedom of a quick scratchpad, all in one small custom hardware device.

---

## Why I Made This

I wanted to build something that felt more advanced than a basic sensor project, but still possible to complete as a real hardware hackathon project.

I often use tools like coding editors, AI tools, browsers, and design apps, and switching between shortcuts can feel repetitive. Physical macropads are useful, but they are usually limited to fixed buttons. I wanted to make a version where the controls are shown on a screen instead of using mechanical switches.

I also wanted a quick place to write or doodle small ideas without saving them permanently. Sometimes I just need to sketch a rough layout, write a quick thought, or scribble something while thinking. TouchDeck solves that by adding a temporary scribble pad.

This project helped me learn:

- ESP32-S3 hardware design
- USB-C powered PCB design
- USB HID keyboard/macropad behavior
- TFT touchscreen interfaces
- Touch input and coordinate mapping
- PCB layout in KiCad
- Firmware structure for an interactive device
- Designing a product-like device instead of only a circuit

---

## What Makes It Unique

Most small macropads use physical buttons or mechanical switches. TouchDeck uses a touchscreen instead, so the same hardware can show different controls depending on the mode.

It is also not just a display. It is an interactive device with:

- Touch buttons
- Temporary drawing canvas
- USB keyboard shortcut output
- Status feedback through LED/buzzer
- Custom PCB
- 3D printed enclosure
- Compact desktop form factor

It feels like a mini control tablet for creators and students.

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

  <img width="807" height="637" alt="image" src="https://github.com/user-attachments/assets/af7c6ff3-79cf-40f5-9270-ce6b370cb6bb" />
  <img width="580" height="592" alt="image" src="https://github.com/user-attachments/assets/c1d59b20-0be1-4b21-8239-1a179d2a4b46" />

---

## How to Use It

### 1. Power the Device

Connect TouchDeck to your laptop using a USB-C data cable.

The USB-C cable provides:

- Power to the device
- Data connection for sending keyboard shortcuts

No battery is required for the first version because the device is meant to work as a laptop-connected macropad.

---

### 2. Boot into the Home Screen

When powered on, the screen shows two main options:

- **MacroPad Mode**
- **ScribblePad Mode**

Tap the mode you want to use.

---

### 3. MacroPad Mode

In MacroPad Mode, the touchscreen shows several shortcut buttons.

Example buttons:

- Copy
- Paste
- Undo
- Redo
- New Tab
- Close Tab
- Reopen Tab
- ChatGPT shortcut
- VS Code shortcut
- Prompt template
- Music shortcut

When a button is touched, the ESP32-S3 sends a keyboard shortcut to the connected laptop using USB HID.

For example:

- Copy sends `Ctrl + C`
- Paste sends `Ctrl + V`
- Undo sends `Ctrl + Z`
- New Tab sends `Ctrl + T`

Custom shortcuts can also be mapped on the laptop. For example, a button on TouchDeck can send `Ctrl + Alt + C`, and the laptop can be configured to open a specific app or website when that shortcut is received.

---

### 4. ScribblePad Mode

In ScribblePad Mode, the screen becomes a temporary drawing area.

You can:

- Write with your finger
- Use a capacitive stylus
- Doodle quick ideas
- Sketch small layouts
- Scribble notes while thinking

The drawing is not saved. It is meant to be temporary.

Pressing **Clear** removes the drawing from the screen.  
Pressing **Back** returns to the home screen and clears the temporary canvas.

---

<img width="1093" height="710" alt="Screenshot 2026-05-12 185242" src="https://github.com/user-attachments/assets/39bed192-fa30-4eb7-ba5f-bf6ecf6554f1" />


## Hardware Used

The project uses a custom PCB with the following major parts:

- ESP32-S3-WROOM-1 module
- 3.5 inch ILI9488 SPI TFT LCD touch display module
- XPT2046 touch controller
- USB-C receptacle
- AP2112K 3.3V voltage regulator
- USBLC6-2SC6 USB ESD protection
- WS2812B RGB LED
- Passive buzzer
- 2N3904 transistor
- Push buttons
- Resistors and capacitors
- 1x14 display connector/header
- M2.5 hex screws
- 3D printed or acrylic enclosure

The full component list is available in:

```text
BOM.csv
