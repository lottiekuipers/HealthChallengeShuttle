//Copyright: Suzan Vink & Erik de Kruijff
//Hanze Health Challenge

#include "pitch.h"
#define melodyPin 8

// notes in the melody:
int melody[] = {
  NOTE_E5, NOTE_F5, NOTE_G5, NOTE_C6, NOTE_D5, NOTE_E5, NOTE_F5, 0, 0, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_F6, 0,
  NOTE_A5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_E6, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_C6, 0, NOTE_D6, NOTE_E6, NOTE_F6,
  NOTE_G5,NOTE_G5, NOTE_E6, NOTE_D6, NOTE_G5, NOTE_E6, NOTE_D6, NOTE_G5, NOTE_F6, NOTE_E6, NOTE_D6, NOTE_C6
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
float noteDurations[] = {
  4, 8, 8, 1, 4, 8, 1, 0, 0, 4, 8, 8, 1, 0, 4, 8, 2, 2, 2, 4, 8, 8, 1, 0, 4, 8, 0.7, 4, 8, 2.5, 4, 8, 2.5, 4,
  8, 2.5, 4, 8, 2
};


void setup() {
for (int thisNote = 0; thisNote < 39; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    int noteDuration = 600 / noteDurations[thisNote];
    tone(melodyPin, melody[thisNote]);
    delay(noteDuration);

    // to distinguish the notes, set a minimum time between them.
    //pauseBetweenNotes
    delay(120);
    noTone(8);
  }

}

void loop() { // iterate over the notes of the melody:
 
  
}

