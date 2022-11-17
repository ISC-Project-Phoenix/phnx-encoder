/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include <Arduino.h>
#define LED_BUILTIN 13

// Encoder provides two channels for determining Rotation

#define TICK_CH_A_PIN 23 // Changes state when encoder moves 1 Tick
#define DIR_CH_B_PIN 22 // State relative to Channel A determines direction of Encoder, CW or CCW
// If B != A, CW
//If B == A, CCW 

int counter = 0; 
int currentStateTick; 
int lastStateTick;
String dir = ""; 
void increment(){
  counter++;
}
void setup(){

  pinMode(TICK_CH_A_PIN, INPUT);
  pinMode(DIR_CH_B_PIN, INPUT);
  Serial.begin(9600);

  //Set initial state of Tick Pin
  lastStateTick = digitalRead(TICK_CH_A_PIN);

}
void loop(){
  // Read current state of Tick Pin 

  currentStateTick = digitalRead(TICK_CH_A_PIN);

  // Determine Tick movement and Direction movement 

  if(currentStateTick != lastStateTick && currentStateTick == 1){ //if the Tick state changed from LOW to HIGH

    // if the Direction State is different from the Tick State 
    if(digitalRead(DIR_CH_B_PIN) != currentStateTick){
      counter--; //Encoder is moved one Tick in CCW direction
      dir = "CCW";
    }
    else{//Otherwise, Encoder moved one Tick in CW direction 
      counter++; 
      dir = "CW";
    }
    // Print Direction and Counter when Encoder moves 1 Tick
    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(counter);
  }
  // Log last state of Tick PIN 
  lastStateTick = currentStateTick;

  //debugging purposes
  delay(1); 

}

