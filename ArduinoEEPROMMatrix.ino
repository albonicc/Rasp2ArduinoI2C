/*
  Arduino Slave for Raspberry Pi Master
  Connects to Raspberry Pi via I2C

  
*/
 
// Include the Wire library for I2C
#include <Wire.h>
#include <EEPROM.h>
 
byte dataArray[12];
 
void setup() {
  
  Serial.begin(9600);
  // Join I2C bus as slave with address 8
  Wire.begin(0x8);
  
  // Call receiveEvent when data received                
  Wire.onReceive(receiveEvent);

  //Call requestEvent when data requested
  Wire.onRequest(requestEvent);
}
 
// Function that executes whenever data is received from master
void receiveEvent(int howMany) {
  byte intermediate;
  while (Wire.available()) { // loop through all but the last
    Serial.print("Datos mandados RPi");
    Serial.print('\n');
    for(int i = 0; i < howMany; i++){
       intermediate = Wire.read();
       if(intermediate == 0){
          intermediate = 0;
          continue;
        }
        else{
          dataArray[i] = intermediate;
          EEPROM.update(i, dataArray[i]);
        }
      Serial.print(dataArray[i]);
      Serial.print(" ");
    }
    Serial.print('\n');
//    Serial.print("Datos a guardar en la EEPROM");
//    Serial.print('\n');
//    for(int j = 0; j < 11; j++){
//      Serial.print(dataArray[j]);
//      Serial.print(" ");
//      EEPROM.update(j, dataArray[j]);
//      Serial.print(j);
//      Serial.print(" ");
//    } 
  }
}
void requestEvent(){
    char message[12];
    char message_original[13];
    char character;
    Serial.print('\n');
    Serial.print("Datos guardados en la EEPROM");
    Serial.print('\n');
    for(int i = 1; i < 13;i++){
        character = EEPROM.read(i);
        Serial.print(character);
        message[i] = character;
    }
    
    
    Serial.print('\n');
    Serial.print(message);
    Wire.write(message);

}
void loop() {
  delay(100);
}
