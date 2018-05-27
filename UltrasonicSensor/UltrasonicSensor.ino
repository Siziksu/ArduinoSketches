#include <Commons.h>

float echoTime;
int distance;

Led led(13, false);
Buzzer buzzer(14);
Ultrasonic ultrasonic(11, 10);

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino Ultrasonic Sensor");
}

void loop() {
  ultrasonic.trigger();
  echoTime = ultrasonic.echoTime();
  if (echoTime >= 120 && echoTime <= 5800) {
    distance = ultrasonic.distance(echoTime);
    if (distance <= 25) {
      buzzer.buzz();
      led.on();
    } else if (distance > 25 && distance <= 100) {
      buzzer.buzz();
      led.on();
      delay(distance + 10);  
      buzzer.stopBuzz();
      led.off();
      delay(distance + 10);
    } else if (distance > 100) {
      buzzer.stopBuzz();
      led.off();
    }
    Serial.print("Distance is: ");
    Serial.print(distance);
    Serial.println("cm");
  } else {
    buzzer.stopBuzz();
    led.off();
  }
  delay(100);
}

