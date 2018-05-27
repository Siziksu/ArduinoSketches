#include <Commons.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

Led led(13, false);
Button button(2, 5);
byte pressed;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  drawLogo();
  delay(2500);
  clearScreen();
  Serial.println("Arduino Display OLED 128x32 I2C");
}

void loop() {
  pressed = button.pressed();
  switch (pressed) {
    case 1:
      led.on();
      Serial.println("Button pressed");
      drawButtonPressed();
      break;
    case 2:
      led.off();
      Serial.println("Button released");
      clearScreen();
      break;
    default:
      break;
  }
}

void drawLogo() {
  display.clearDisplay();
  display.drawRect(0, 0, 128,32, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 5);
  display.println("       DISPLAY");
  display.println("        TEXTS");
  display.println("         1.0");
  display.display();
}

void drawButtonPressed() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Button pressed");
  display.display();
}

void clearScreen() {
  display.clearDisplay();
  display.display();
}

