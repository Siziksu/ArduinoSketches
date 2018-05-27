#include <Commons.h>

Led led(13, false);
Button button(2, 5);
byte pressed;

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino Button");
}

void loop() {
  pressed = button.pressed();
  switch (pressed) {
    case 1:
      led.on();
      Serial.println("Button pressed");
      break;
    case 2:
      led.off();
      Serial.println("Button released");
      break;
    default:
      break;
  }
}

