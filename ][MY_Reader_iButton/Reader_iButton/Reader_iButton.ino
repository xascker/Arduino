#include <OneWire.h>
#include <EEPROM.h>

OneWire ds(6);  // OneWire bus on digital pin 6

int buttonState = 0;         // переменная для хранения состояния кнопки
int button2State = 0;
byte addr [8];               // массив с ключом

void setup() {
  Serial.begin (9600);
  pinMode(2, INPUT);
}

void loop() {
   // ButtunRead();  
    iButtonReader();
    //iButtonWrite();
}

 void ButtunRead(){
    byte value;
    buttonState = digitalRead(2);
    if (buttonState == HIGH) {    
    Serial.println("Read byte from EEPROM memory...");
    Serial.print("Key in HEX ->");
      for (int i=0; i<8; i++){
        value = EEPROM.read(i);
            
        Serial.print(value, HEX);
        Serial.print(" ");
      }
    Serial.println();  
    }
} 

void iButtonWrite(){
  button2State = digitalRead(4);
  if (button2State == HIGH) { 
    if (ds.search(addr)){
        Serial.print("Key in HEX bytes ->");
        for (int i=0; i<8; i++){
            Serial.print(addr[i], HEX);
            Serial.print(" ");
            
            EEPROM.write(i, addr[i]);
            delay(5);
        }
         Serial.println();
         Serial.println("Write byte to EEPROM is OK!");
        ds.reset_search();
    } 
  }
}

void iButtonReader(){
    if (ds.search(addr)){
        Serial.print("Key in HEX bytes ->");
        for (int i=0; i<8; i++){
            Serial.print(addr[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
        ds.reset_search();
  } 
}


















