#include <Commons.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4

Adafruit_SSD1306 display(OLED_RESET);

const byte NUM_BUTTONS = 4;
const byte LINE_HEIGHT = 8;
const byte CHAR_WIDTH = 6;

struct Memory {
  boolean modeCc;
  uint8_t channel;
  int8_t octave;
};

Memory memory;

Led led(13, false);
Button *buttons[NUM_BUTTONS];
byte buttonsState[NUM_BUTTONS];
boolean editMode = false;
uint8_t menuOption = 1;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing");

  memory.modeCc = 0;
  memory.channel = 16;
  memory.octave = 0;

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  byte PIN_OFFSET = 2;
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i] = new Button(PIN_OFFSET + i, 5);
  }
  
  Serial.println("Arduino Menu");

  drawMenu();
}

void loop() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttonsState[i] = buttons[i]->state();
  }
  for (int i = 0; i < NUM_BUTTONS; i++) {
    switch (buttonsState[i]) {
      case 1:
        led.on();
          switch(buttons[i]->pin()) {
            case 2:
              editMode = !editMode;
              drawMenu();
              break;
            case 3:
              if (!editMode) {
                menuOption = menuOption > 1 ? menuOption - 1 : menuOption;
              } else {
                switch(menuOption) {
                  case 1:
                    memory.modeCc = !memory.modeCc;
                    break;
                  case 2:
                    memory.channel = memory.channel < 16 ? memory.channel + 1 : memory.channel;
                    break;
                  case 3:
                    memory.octave = memory.octave < 3 ? memory.octave + 1 : memory.octave;
                    break;
                }
              }
              drawMenu();
              break;
            case 4:
              if (!editMode) {
                menuOption = menuOption < 3 ? menuOption + 1 : menuOption;
              } else {
                switch(menuOption) {
                  case 1:
                    memory.modeCc = !memory.modeCc;
                    break;
                  case 2:
                    memory.channel = memory.channel > 1 ? memory.channel - 1 : memory.channel;
                    break;
                  case 3:
                    memory.octave = memory.octave > -3 ? memory.octave - 1 : memory.octave;
                    break;
                }
              }
              drawMenu();
              break;
            case 5:
              
              break;
            default:
              break;
          }
        break;
      case 2:
        led.off();
        break;
      default:
        break;
    }
  }
}

void drawMenu() {
  display.clearDisplay();
  
  display.setTextSize(1);
  
  display.setTextColor(WHITE);
  display.setCursor(CHAR_WIDTH * 4, LINE_HEIGHT * 1);
  display.print("MODE     :");
  if (editMode && menuOption == 1) {
    display.setTextColor(BLACK, WHITE);
  }
  display.print(" ");
  display.print(memory.modeCc ? "NOTE" : "CC");
  display.print(" ");
  
  display.setTextColor(WHITE);
  display.setCursor(CHAR_WIDTH * 4, LINE_HEIGHT * 2);
  display.print("CHANNEL  :");
  if (editMode && menuOption == 2) {
    display.setTextColor(BLACK, WHITE);
  }
  display.print(" ");
  display.print(memory.channel);
  display.print(" ");
  
  display.setTextColor(WHITE);
  display.setCursor(CHAR_WIDTH * 4, LINE_HEIGHT * 3);
  display.print("TRANSPOSE:");
  if (editMode && menuOption == 3) {
    display.setTextColor(BLACK, WHITE);
  }
  display.print(" ");
  if (memory.octave > 0) {
    display.print("+");
  }
  display.print(memory.octave);
  display.print(" ");

  display.setTextColor(WHITE);
  display.setCursor(CHAR_WIDTH * 2, LINE_HEIGHT * menuOption);
  display.write(175);

  display.display();
}

void clearScreen() {
  display.clearDisplay();
  display.display();
}

