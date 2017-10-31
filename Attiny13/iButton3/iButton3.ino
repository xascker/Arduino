#include <OneWireSlave.h>
//#include <EEPROM.h>

OneWireSlave ds(3);  
byte key [8] = {0x1, 0x37, 0x9E, 0x7B, 0x1, 0x0, 0x0, 0xD7};

void setup() {
  ds.setRom(key);
}

void loop() {
 ds.waitForRequest(false);
}

