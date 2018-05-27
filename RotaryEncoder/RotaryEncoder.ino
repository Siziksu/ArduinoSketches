const String PROGRAM_TITLE = "Arduino Rotary Encoder";
const String MESSAGE = "Rotary value: ";
const int PIN_OF_ROTARY_INPUT_A = 2;
const int PIN_OF_ROTARY_INPUT_B = 3;
const int PIN_OF_LED = 13;

int rotaryValue = 0;
int rotaryState;
int rotaryLastState;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing");
  pinMode(PIN_OF_ROTARY_INPUT_A, INPUT);
  pinMode(PIN_OF_ROTARY_INPUT_B, INPUT);
  pinMode(PIN_OF_LED, OUTPUT);
  digitalWrite(PIN_OF_LED, LOW);
  Serial.println(PROGRAM_TITLE);
  rotaryLastState = digitalRead(PIN_OF_ROTARY_INPUT_A);
}

void loop() {
  rotaryState = digitalRead(PIN_OF_ROTARY_INPUT_A);
  if (rotaryLastState == LOW && rotaryState == HIGH) {
    if (digitalRead(PIN_OF_ROTARY_INPUT_B) == LOW) {
      rotaryValue--;
    } else {
      rotaryValue++;
    }
    Serial.print(MESSAGE);
    Serial.println(rotaryValue);
  }
  rotaryLastState = rotaryState;
}

