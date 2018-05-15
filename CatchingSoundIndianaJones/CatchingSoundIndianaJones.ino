//Copyright: Suzan Vink & Erik de Kruijff
//Hanze Health Challenge

#include "pitch.h"
#define melodyPin 8

// notes in the melody:
int melody[] = {
  NOTE_F5, NOTE_A5, NOTE_G5, NOTE_C6, NOTE_A5, NOTE_D6
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
float noteDurations[] = {
  2, 2, 2, 1, 1, 0.5
};


void setup() {
for (int thisNote = 0; thisNote < 6; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    int noteDuration = 70 / noteDurations[thisNote];
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

