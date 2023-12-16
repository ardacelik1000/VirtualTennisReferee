#include <Arduino.h>

const int DigitalPin = 10;
//Since we want to read values constantly,setting it to ten.
const int SampleTime = 10;
//We are assigning some values to be able to count how many ones in our output in ten seconds(coming from line five).
unsigned long MillisCurrent; 
unsigned long MillisLastTimeStap = 0;
unsigned long millisElapsed = 0; 

//We are assigning the times we have one in ten seconds to "BufferValue"
int BufferValue = 0; 

void setup() {
  Serial.begin(9600);
}

void loop() {
  //We are starting the counting thanks to this function called "millis()"
  MillisCurrent = millis();
  millisElapsed = MillisCurrent-MillisLastTimeStap;

  if (digitalRead(DigitalPin) == LOW){
    BufferValue ++; 
  }
  if (millisElapsed > SampleTime){
    if(BufferValue> 300){
      BufferValue = 0; 
      MillisLastTimeStap = MillisCurrent;
    }
    else if(BufferValue >10 ){
      Serial.println("Hit!");
      BufferValue = 0; 
      MillisLastTimeStap = MillisCurrent;
    }
    else {
      Serial.println(BufferValue);
      BufferValue = 0; 
      MillisLastTimeStap = MillisCurrent;
    }
  }
}
 