#include <Commons.h>
#include "Notes.h"

const String PROGRAM_TITLE = "Arduino Buzzer Tones";
const int NUM_NOTES = 8;

Buzzer buzzer(14);

int melody[NUM_NOTES] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5};
int noteDurations[NUM_NOTES] = {8, 8, 8, 8, 8, 8, 8, 8};

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino Buzzer Tones");
  playNotes();
}

void loop() {

}

void playNotes() {
  for (int note = 0; note < NUM_NOTES; note++) {
    // To calculate the note duration, take one second divided by the note type.
    // E.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[note];
    buzzer.playTone(melody[note], noteDuration);
    // To distinguish the notes, set a minimum time between them.
    // The note's duration + 30%:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    buzzer.stopTone();
  }
}

