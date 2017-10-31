//#include <EEPROM.h>

#include <inttypes.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define WirePin 3

byte key [8] = {0x1, 0x37, 0x9E, 0x7B, 0x1, 0x0, 0x0, 0xD7};



void OneWire_sendByte( const uint8_t Byte){
    
    // - Write each bit
    for( uint8_t BitMask = 0x01; BitMask; BitMask <<= 1 ) OneWire_sendBit( (BitMask & Byte) ? 1 : 0 );
    
       digitalWrite(WirePin,LOW);
       pinMode(WirePin, OUTPUT);     
}

void OneWire_sendBit( uint8_t Bit ){
    if( Bit & 1 ){
    //if( Bit ){
        // прижимаем линию к земле
        digitalWrite(WirePin,LOW);
        pinMode(WirePin, OUTPUT);
        
         // Посылаем единичку
        _delay_us ( 5 );
       // digitalWrite(WirePin,HIGH);
       pinMode(WirePin, INPUT); 
        _delay_us ( 90 );
    }else{
        // прижимаем линию к земле
        digitalWrite(WirePin,LOW);
        pinMode(WirePin, OUTPUT);
        
        // Посылаем нолик
        _delay_us( 90 );
       // digitalWrite(WirePin,HIGH);
        pinMode(WirePin, INPUT); 
        _delay_us( 5 );
    }
}


void setup() {

}

void loop() {
    waitReset();
    PRESENCE();
    for(int i=0; i<8; i++) {
             OneWire_sendByte(key[i]); 
    }
             delay(200);
}


void waitReset(){  
    pinMode(WirePin, INPUT);
    while(digitalRead(WirePin)) {
        delayMicroseconds(30); 
    }
  /*
    pinMode(WirePin, INPUT);
    while(digitalRead(WirePin)) {
        delayMicroseconds(15);
    }
    while(!digitalRead(WirePin)){
        delayMicroseconds(1);
    }
    delayMicroseconds(40);
    */
}

void PRESENCE() {
    digitalWrite(WirePin,LOW);         // прижимаем линию к земле
    pinMode(WirePin, OUTPUT);
    delayMicroseconds(120);      // 60-240 микросекунд
    pinMode(WirePin, INPUT);           // отключаемся
    delayMicroseconds(450);
}



 

