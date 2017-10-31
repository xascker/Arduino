#include <OneWireSlave.h>
//#include <EEPROM.h>

OneWireSlave ds(9);   //9 нога
byte key [8] = {0x1, 0x61, 0x4B, 0x5, 0x0, 0x0, 0x0, 0xD1};

void setup() {  
      ds.setRom(key);
      pinMode(13, OUTPUT);
      
   for (int i=0; i<3; i++){ // мигать 3 раза
        digitalWrite(13, HIGH); 
        delay(300);              
        digitalWrite(13, LOW);    
        delay(300);   
   }
}

void loop() {
     ds.waitForRequest(false);
}

