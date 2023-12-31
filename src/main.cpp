#include <Arduino.h>

const int Table1Sensor = 10;
const int Table2Sensor = 11;
const int Red = 3;
const int Green = 5;
const int Blue = 6;

//Since we want to read values constantly,setting it to ten.
const int SampleTime = 7;
//We are assigning some values to be able to count how many ones in our output in ten seconds(coming from line five).
unsigned long MillisCurrentForTable1; 
unsigned long MillisLastTimeStapForTable1 = 0;
unsigned long millisElapsedForTable1 = 0; 

unsigned long MillisCurrentForTable2; 
unsigned long MillisLastTimeStapForTable2 = 0;
unsigned long millisElapsedForTable2 = 0; 


//We are assigning the times we have one in ten seconds to "BufferValue"
int BufferValueForTable1 = 0; 
int HitForTable1 = 0; 
int BufferValueForTable2 = 0;
int HitForTable2 = 0; 

// -------
// Color Options
void WhiteColor() { 
  analogWrite(Red, 0);
  analogWrite(Green, 0);
  analogWrite(Blue, 0);
}

void RedColor() { 
  analogWrite(Red, 0);
  analogWrite(Green, 255);
  analogWrite(Blue, 255);
}

void GreenColor() { 
  analogWrite(Red, 255);
  analogWrite(Green, 0);
  analogWrite(Blue, 255);
}

void BlueColor() { 
  analogWrite(Red, 255);
  analogWrite(Green, 255);
  analogWrite(Blue, 0);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  //We are starting the counting thanks to this function called "millis()"
  MillisCurrentForTable1 = millis();
  millisElapsedForTable1 = MillisCurrentForTable1-MillisLastTimeStapForTable1;
  MillisCurrentForTable2 = millis();
  millisElapsedForTable2 = MillisCurrentForTable2-MillisLastTimeStapForTable2;

// -----------------
// Sensor1
  if (digitalRead(Table1Sensor) == LOW){
    BufferValueForTable1 ++; 
  }
  if (millisElapsedForTable1 > SampleTime){
    if(BufferValueForTable1> 300){
      BufferValueForTable1 = 0; 
    }
    if(BufferValueForTable1 >5 ){
      HitForTable1 ++; 
      if (HitForTable1 > 1){
        HitForTable1 = 0;
        GreenColor();
        Serial.println("Hit for table 1!");
      }
      BufferValueForTable1 = 0; 
      MillisLastTimeStapForTable1 = MillisCurrentForTable1;
    }
    else {
      Serial.println(BufferValueForTable1);
      BufferValueForTable1 = 0; 
      MillisLastTimeStapForTable1 = MillisCurrentForTable1;
    }
  }

// --------------------------------
// Sensor 2 
  if (digitalRead(Table2Sensor) == LOW){
    BufferValueForTable2 ++; 
  }
  if (millisElapsedForTable2 > SampleTime){
    if(BufferValueForTable2> 300){
      BufferValueForTable2 = 0; 
      MillisLastTimeStapForTable2 = MillisCurrentForTable2;
    }
    if(BufferValueForTable2 >5 ){
      HitForTable2 ++; 
      if (HitForTable2 > 1){
        HitForTable2 = 0;
        BlueColor();
        Serial.println("Hit for table 2!");
      }
      BufferValueForTable2 = 0; 
      MillisLastTimeStapForTable2 = MillisCurrentForTable2;
    }
    else {
      Serial.println(BufferValueForTable2);
      BufferValueForTable2 = 0; 
      MillisLastTimeStapForTable2 = MillisCurrentForTable2;
    }
  }
}
 
