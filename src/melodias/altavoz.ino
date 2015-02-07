/*
  Melody
 
 Plays a melody 
 
 circuit:
 * 8-ohm speaker on digital pin 8
 
 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe 

This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/Tone
 
 */
#include "melodies.h"

//isTime vars
unsigned long notesTimeMark = 0;
unsigned long notesPauseTimeMark = 0;

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
int buttonState = 0, buttonHasBeenPressed = 0;
int playTheMelody = 0;

int milis = 0;


//Melody vars
int melodyNote, numNotes, currentNote = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);    

  numNotes = sizeof(melody) / sizeof(int);

  Serial.begin(9600);       // for debugging
}

void loop() {
  milis= milis + 1;
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && buttonHasBeenPressed == 0) { 
    Serial.println("PREEEEEEESSSSS");  
    buttonHasBeenPressed = 1;
    if (playTheMelody == 0){
      playTheMelody = 1;
    }else{
      playTheMelody = 0;
    }    
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
    
  }
  else if (buttonState == LOW) {
    Serial.println("NOOOOOOOO");  
    buttonHasBeenPressed = 0;
    // turn LED off:
    digitalWrite(ledPin, LOW);     
  } 


  if (playTheMelody){
    playMelody();
  }else{
    stopMelody();
  }

}

bool IsTime(unsigned long *timeMark, unsigned long timeInterval) {
    if (millis() - *timeMark >= timeInterval) {
        *timeMark = millis();
        return true;
    }    
    return false;
}

void playMelody() {
  if (currentNote == 0 || IsTime(&notesTimeMark, noteDurations[currentNote])){    
    if (currentNote < numNotes){
      tone(8, melody[currentNote], noteDurations[currentNote]);                
      // Serial.print("TOCO - ");
      // Serial.println(currentNote);
      currentNote = currentNote + 1;
    }else{
      currentNote = 0;
    }        
  }
    
}

void stopMelody(){
  currentNote = 0;
  noTone(8);
}

