/*
  ScribbleDeck S3 / TouchDeck Firmware
  ---------------------------------------------------------
  Project: Touchscreen Macropad + Temporary Scribble Pad
  Board:   ESP32-S3-WROOM-1 based custom PCB
  Display: 3.5" SPI TFT LCD, ILI9488 driver + XPT2046 touch
  UI:      Macro buttons + temporary finger scribble pad
  Output:  USB HID keyboard shortcuts to laptop

  Human note:
  This firmware is intentionally written as a hackathon-ready MVP.
  It focuses on the two core features:
    1) on-screen macropad buttons
    2) temporary scribble/doodle pad that clears when Back is pressed

  Required Arduino libraries:
    - TFT_eSPI by Bodmer
    - ESP32 Arduino core with USB HID support

  IMPORTANT TFT_eSPI setup:
  In TFT_eSPI/User_Setup.h, configure your ILI9488 + XPT2046 pins
  according to your PCB wiring. Example pins used by this firmware:

    TFT_CS   GPIO10
    TFT_RST  GPIO14
    TFT_DC   GPIO9
    TFT_MOSI GPIO11
    TFT_SCLK GPIO12
    TFT_MISO GPIO13
    TOUCH_CS GPIO8
    TFT_BL   GPIO21

  USB HID notes:
  In Arduino IDE, select an ESP32-S3 board and enable native USB mode.
*/

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "USB.h"
#include "USBHIDKeyboard.h"

// -------------------- Hardware pins --------------------
#define TFT_BACKLIGHT_PIN 21
#define BUZZER_PIN         5

// -------------------- USB HID keyboard --------------------
USBHIDKeyboard Keyboard;

// -------------------- Display --------------------
TFT_eSPI tft = TFT_eSPI();

static const int SCREEN_W = 480;
static const int SCREEN_H = 320;

// Touch calibration. Tune these after running a touch calibration sketch.
uint16_t calData[5] = { 300, 3600, 300, 3600, 1 };

// -------------------- UI colors --------------------
#define COL_BG        0x18E3
#define COL_PANEL     0x2945
#define COL_CARD      0x39E7
#define COL_CARD_HIT  0x5AEB
#define COL_TEXT      0xFFFF
#define COL_MUTED     0xBDF7
#define COL_ACCENT    0x04FF
#define COL_LINE      0xFFFF

// -------------------- UI state --------------------
enum ScreenMode {
  SCREEN_HOME,
  SCREEN_MACRO,
  SCREEN_SCRIBBLE
};

ScreenMode currentScreen = SCREEN_HOME;

struct Button {
  int x, y, w, h;
  const char* label;
  uint8_t action;
};

enum MacroAction {
  ACT_NONE = 0,
  ACT_COPY,
  ACT_PASTE,
  ACT_UNDO,
  ACT_REDO,
  ACT_NEW_TAB,
  ACT_CLOSE_TAB,
  ACT_REOPEN_TAB,
  ACT_ALT_TAB,
  ACT_CHATGPT_SHORTCUT,
  ACT_VSCODE_SHORTCUT,
  ACT_PROMPT_TEMPLATE,
  ACT_MUSIC_PLAY_PAUSE
};

Button homeButtons[] = {
  { 70, 105, 340, 60, "MacroPad Mode", 1 },
  { 70, 185, 340, 60, "ScribblePad Mode", 2 }
};

Button macroButtons[] = {
  { 20,  70, 135, 52, "Copy",     ACT_COPY },
  { 165, 70, 135, 52, "Paste",    ACT_PASTE },
  { 310, 70, 135, 52, "Undo",     ACT_UNDO },

  { 20,  135, 135, 52, "Redo",    ACT_REDO },
  { 165, 135, 135, 52, "New Tab", ACT_NEW_TAB },
  { 310, 135, 135, 52, "Close",   ACT_CLOSE_TAB },

  { 20,  200, 135, 52, "Reopen",  ACT_REOPEN_TAB },
  { 165, 200, 135, 52, "Alt Tab", ACT_ALT_TAB },
  { 310, 200, 135, 52, "Prompt",  ACT_PROMPT_TEMPLATE },

  { 20,  265, 135, 42, "ChatGPT", ACT_CHATGPT_SHORTCUT },
  { 165, 265, 135, 42, "VS Code", ACT_VSCODE_SHORTCUT },
  { 310, 265, 135, 42, "Music",   ACT_MUSIC_PLAY_PAUSE }
};

Button backButton = { 380, 10, 90, 38, "Back", ACT_NONE };
Button clearButton = { 270, 10, 95, 38, "Clear", ACT_NONE };

bool wasDrawing = false;
int lastX = -1;
int lastY = -1;

// -------------------- Utility functions --------------------
bool pointInButton(int x, int y, const Button& b) {
  return (x >= b.x && x <= b.x + b.w && y >= b.y && y <= b.y + b.h);
}

void beep(uint16_t duration = 25) {
  tone(BUZZER_PIN, 2400, duration);
}

void drawHeader(const char* title) {
  tft.fillRect(0, 0, SCREEN_W, 56, COL_PANEL);
  tft.setTextColor(COL_TEXT, COL_PANEL);
  tft.setTextDatum(ML_DATUM);
  tft.drawString(title, 18, 28, 4);
}

void drawButton(const Button& b, uint16_t color = COL_CARD) {
  tft.fillRoundRect(b.x, b.y, b.w, b.h, 10, color);
  tft.drawRoundRect(b.x, b.y, b.w, b.h, 10, COL_MUTED);
  tft.setTextColor(COL_TEXT, color);
  tft.setTextDatum(MC_DATUM);
  tft.drawString(b.label, b.x + b.w / 2, b.y + b.h / 2, 2);
}

void flashButton(const Button& b) {
  drawButton(b, COL_CARD_HIT);
  delay(90);
  drawButton(b, COL_CARD);
}

// -------------------- USB HID helpers --------------------
void keyCombo(uint8_t modifier, char key) {
  Keyboard.press(modifier);
  delay(10);
  Keyboard.press(key);
  delay(30);
  Keyboard.releaseAll();
}

void keyCombo2(uint8_t modifier1, uint8_t modifier2, char key) {
  Keyboard.press(modifier1);
  Keyboard.press(modifier2);
  delay(10);
  Keyboard.press(key);
  delay(30);
  Keyboard.releaseAll();
}

void sendMacro(uint8_t action) {
  beep();

  switch (action) {
    case ACT_COPY:
      keyCombo(KEY_LEFT_CTRL, 'c');
      break;

    case ACT_PASTE:
      keyCombo(KEY_LEFT_CTRL, 'v');
      break;

    case ACT_UNDO:
      keyCombo(KEY_LEFT_CTRL, 'z');
      break;

    case ACT_REDO:
      keyCombo(KEY_LEFT_CTRL, 'y');
      break;

    case ACT_NEW_TAB:
      keyCombo(KEY_LEFT_CTRL, 't');
      break;

    case ACT_CLOSE_TAB:
      keyCombo(KEY_LEFT_CTRL, 'w');
      break;

    case ACT_REOPEN_TAB:
      keyCombo2(KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 't');
      break;

    case ACT_ALT_TAB:
      Keyboard.press(KEY_LEFT_ALT);
      delay(10);
      Keyboard.press(KEY_TAB);
      delay(60);
      Keyboard.releaseAll();
      break;

    case ACT_CHATGPT_SHORTCUT:
      // Map Ctrl+Alt+C on your laptop to open ChatGPT/browser.
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('c');
      delay(40);
      Keyboard.releaseAll();
      break;

    case ACT_VSCODE_SHORTCUT:
      // Map Ctrl+Alt+V on your laptop to open VS Code.
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('v');
      delay(40);
      Keyboard.releaseAll();
      break;

    case ACT_PROMPT_TEMPLATE:
      Keyboard.print("Improve this without changing the core layout. Make it cleaner, more premium, and explain only the exact changes needed.");
      break;

    case ACT_MUSIC_PLAY_PAUSE:
      // Reliable MVP method: map Ctrl+Alt+M to play/pause on laptop if needed.
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('m');
      delay(40);
      Keyboard.releaseAll();
      break;

    default:
      break;
  }
}

// -------------------- Screen drawing --------------------
void drawHome() {
  currentScreen = SCREEN_HOME;
  tft.fillScreen(COL_BG);
  drawHeader("ScribbleDeck S3");

  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(COL_MUTED, COL_BG);
  tft.drawString("Touch macros. Quick doodles. No physical switches.", SCREEN_W / 2, 78, 2);

  for (Button& b : homeButtons) {
    drawButton(b);
  }

  tft.setTextColor(COL_MUTED, COL_BG);
  tft.drawString("Hackathon MVP v1", SCREEN_W / 2, 292, 2);
}

void drawMacroPad() {
  currentScreen = SCREEN_MACRO;
  tft.fillScreen(COL_BG);
  drawHeader("MacroPad");
  drawButton(backButton, COL_PANEL);

  for (Button& b : macroButtons) {
    drawButton(b);
  }
}

void drawScribblePad() {
  currentScreen = SCREEN_SCRIBBLE;
  tft.fillScreen(COL_BG);
  drawHeader("ScribblePad");
  drawButton(backButton, COL_PANEL);
  drawButton(clearButton, COL_PANEL);

  tft.drawRoundRect(12, 60, SCREEN_W - 24, SCREEN_H - 72, 8, COL_MUTED);
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(COL_MUTED, COL_BG);
  tft.drawString("Draw here. Back clears everything.", SCREEN_W / 2, SCREEN_H / 2, 2);

  wasDrawing = false;
  lastX = -1;
  lastY = -1;
}

void clearScribbleArea() {
  tft.fillRect(14, 62, SCREEN_W - 28, SCREEN_H - 76, COL_BG);
  tft.drawRoundRect(12, 60, SCREEN_W - 24, SCREEN_H - 72, 8, COL_MUTED);
}

// -------------------- Touch handling --------------------
bool getTouchPoint(uint16_t& x, uint16_t& y) {
  return tft.getTouch(&x, &y, 600);
}

void handleHomeTouch(uint16_t x, uint16_t y) {
  if (pointInButton(x, y, homeButtons[0])) {
    flashButton(homeButtons[0]);
    drawMacroPad();
  } else if (pointInButton(x, y, homeButtons[1])) {
    flashButton(homeButtons[1]);
    drawScribblePad();
  }
}

void handleMacroTouch(uint16_t x, uint16_t y) {
  if (pointInButton(x, y, backButton)) {
    beep();
    drawHome();
    return;
  }

  for (Button& b : macroButtons) {
    if (pointInButton(x, y, b)) {
      flashButton(b);
      sendMacro(b.action);
      return;
    }
  }
}

void handleScribbleTouch(uint16_t x, uint16_t y) {
  if (pointInButton(x, y, backButton)) {
    beep();
    drawHome();
    return;
  }

  if (pointInButton(x, y, clearButton)) {
    beep();
    clearScribbleArea();
    wasDrawing = false;
    lastX = -1;
    lastY = -1;
    return;
  }

  if (y > 62 && y < SCREEN_H - 12 && x > 14 && x < SCREEN_W - 14) {
    if (!wasDrawing) {
      wasDrawing = true;
      lastX = x;
      lastY = y;
      tft.fillCircle(x, y, 2, COL_LINE);
    } else {
      tft.drawLine(lastX, lastY, x, y, COL_LINE);
      tft.fillCircle(x, y, 2, COL_LINE);
      lastX = x;
      lastY = y;
    }
  }
}

// -------------------- Setup and loop --------------------
void setup() {
  pinMode(TFT_BACKLIGHT_PIN, OUTPUT);
  digitalWrite(TFT_BACKLIGHT_PIN, HIGH);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.begin(115200);
  delay(300);

  tft.init();
  tft.setRotation(1);
  tft.setTouch(calData);
  tft.fillScreen(COL_BG);

  Keyboard.begin();
  USB.begin();

  drawHome();

  Serial.println("ScribbleDeck S3 ready.");
  Serial.println("Use touchscreen for MacroPad or ScribblePad mode.");
}

void loop() {
  uint16_t x, y;

  if (getTouchPoint(x, y)) {
    switch (currentScreen) {
      case SCREEN_HOME:
        handleHomeTouch(x, y);
        break;

      case SCREEN_MACRO:
        handleMacroTouch(x, y);
        break;

      case SCREEN_SCRIBBLE:
        handleScribbleTouch(x, y);
        break;
    }

    if (currentScreen != SCREEN_SCRIBBLE) {
      delay(160);
    } else {
      delay(8);
    }
  } else {
    wasDrawing = false;
    lastX = -1;
    lastY = -1;
    delay(8);
  }
}
