#include <EEPROM.h>

int address = 0;
byte value;

void setup() {
    Serial.begin(9600);
    
    Serial.println("Write byte to EEPROM memory...");
     for (int i=0; i<=255; i++){
        EEPROM.write(i, i);
        delay(2);
     }
    
    delay(10);
    
    Serial.println("Read byte from EEPROM memory...");
    for (int i=0; i<=255; i++){
        value = EEPROM.read(i);
    
        Serial.print("Read byte = 0x");
        Serial.print(value, HEX);
        Serial.println("");
    }
}

void loop() {
  // put your main code here, to run repeatedly:
}
