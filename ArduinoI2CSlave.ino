/*
  Arduino Slave for Raspberry Pi Master
  Connects to Raspberry Pi via I2C

  LED state is stored into the Arduino's
  EEPROM, so when power is lost and then 
  recovered, the LED will continue to be
  on or off depending on how it was 
  before.
*/
 
// Include the Wire library for I2C
#include <Wire.h>
#include <EEPROM.h>
 
// LED on pin 13
const int ledPin = 13;
char ledState;

long lastDebounceTime = 0;
long debounceDelay = 50; 
 
void setup() {
  // Join I2C bus as slave with address 8
  Wire.begin(0x8);
  
  // Call receiveEvent when data received                
  Wire.onReceive(receiveEvent);
  
  // Setup pin 13 as output and turn LED off
  pinMode(ledPin, OUTPUT);
  checkLedState();
}
 
// Function that executes whenever data is received from master
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    ledState = Wire.read(); // receive byte as a character
    digitalWrite(ledPin, ledState);
    EEPROM.update(0, ledState);
  }
}
void loop() {
  delay(100);
}

// Prints and upates the LED state
// when the Arduino board restarts or powers up
void checkLedState() {
   Serial.println("LED status after restart: ");
   ledState = EEPROM.read(0);
   if(ledState == 1) {
    Serial.println ("ON");
    digitalWrite(ledPin, HIGH);
   } 
   if(ledState == 0) {
    Serial.println ("OFF");
    digitalWrite(ledPin, LOW);
   }
}