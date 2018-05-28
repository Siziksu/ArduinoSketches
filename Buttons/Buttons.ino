#include <Commons.h>

const byte NUM_BUTTONS = 3;

Button *buttons[NUM_BUTTONS];
byte buttonsState[NUM_BUTTONS];

Led led(13, false);

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing");
  byte PIN_OFFSET = 2;
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i] = new Button(PIN_OFFSET + i, 5);
  }
  Serial.println("Arduino Buttons");
}

void loop() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttonsState[i] = buttons[i]->state();
  }
  for (int i = 0; i < NUM_BUTTONS; i++) {
    switch (buttonsState[i]) {
      case 1:
        led.on();
        Serial.print("Button pressed: ");
        Serial.println(buttons[i]->pin());
        break;
      case 2:
        led.off();
        Serial.print("Button released: ");
        Serial.println(buttons[i]->pin());
        break;
      default:
        break;
    }
  }
}

