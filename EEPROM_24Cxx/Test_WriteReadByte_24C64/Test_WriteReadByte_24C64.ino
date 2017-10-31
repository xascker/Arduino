#include <Wire.h>
#include <Eeprom24C32_64.h>
#define EEPROM_ADDRESS  0x50

static Eeprom24C32_64 eeprom(EEPROM_ADDRESS);

void setup()
{
    // Initialize serial communication.
    Serial.begin(9600);
        
    // Initialize EEPROM library.
    eeprom.initialize();
    
    // Write a byte at address 0 in EEPROM memory.
    Serial.println("Write byte to EEPROM memory...");
     for (int i=0; i<=255; i++){
    eeprom.writeByte(i, i);
     delay(2);
     }
    
    delay(10);
    
    // Read a byte at address 0 in EEPROM memory.
    Serial.println("Read byte from EEPROM memory...");
    for (int i=0; i<=255; i++){
    byte data = eeprom.readByte(i);
    
    // Print read byte.
    Serial.print("Read byte = 0x");
    Serial.print(data, HEX);
    Serial.println("");
    }
}


void loop()
{

}
