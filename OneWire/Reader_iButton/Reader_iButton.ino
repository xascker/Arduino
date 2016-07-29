#include <OneWire.h>
OneWire ds(6);                    // OneWire bus on digital pin 6

void setup() {
  Serial.begin (9600);
}

void loop() {
    byte addr [8];
    if (ds.search(addr)){
        Serial.print("Key by HEX bytes ->");
        for (int i=0; i<8; i++){
            Serial.print(addr[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
        ds.reset_search();
  }
}

















