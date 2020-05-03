/*
  Arduino Slave for Raspberry Pi Master
  Connects to Raspberry Pi via I2C

  
*/
 
// Include the Wire library for I2C
#include <Wire.h>
#include <EEPROM.h>
 
int i = 0
char c;

 
void setup() {
  // Join I2C bus as slave with address 8
  Wire.begin(0x8);
  
  // Call receiveEvent when data received                
  Wire.onReceive(receiveEvent);

  //Call requestEvent when data requested
  Wire.onRequest(requestEvent);
}
 
// Function that executes whenever data is received from master
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    c = Wire.read(); // receive byte as a character
    while(i < i + 19){
        EEPROM.write(i, c);
    } 
  }
}
void requestEvent(){
    String message;
    char character;
    while(i < 1+19){
        character = EEPROM.read(i);
        message = String(message + character)
    }
    Wire.write(message);

}
void loop() {
  delay(100);
}
}