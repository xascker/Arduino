#include <MaxMatrix.h>

int Trig = 8;
int Echo = 9; 
int ledPin = 13;  // 13 – если будете использовать встроенный в Arduino светодиод

int din = 4; 
int cs = 5;
int clk = 6; 
int maxInUse = 1;

byte CH_1[] = {8, 8, B00000000, B00000000, B10000000, B10000000, B10000000, B10000000, B00000000, B00000000 }; 
byte CH_2[] = {8, 8, B00000000, B00000000, B01000000, B01000000, B01000000, B01000000, B00000000, B00000000 }; 
byte CH_3[] = {8, 8, B00000000, B00000000, B00100000, B00100000, B00100000, B00100000, B00000000, B00000000 }; 
byte CH_4[] = {8, 8, B00000000, B00000000, B00010000, B00010000, B00010000, B00010000, B00000000, B00000000 }; 
byte CH_5[] = {8, 8, B00000000, B00000000, B00001000, B00001000, B00001000, B00001000, B00000000, B00000000 }; 
byte CH_6[] = {8, 8, B00000000, B00000000, B00000100, B00000100, B00000100, B00000100, B00000000, B00000000 }; 
byte CH_7[] = {8, 8, B00000000, B00000000, B00000010, B00000010, B00000010, B00000010, B00000000, B00000000 }; 
byte CH_8[] = {8, 8, B00000000, B00000000, B00000001, B00000001, B00000001, B00000001, B00000000, B00000000 }; 

MaxMatrix m(din, cs, clk, maxInUse);

void setup() { 

pinMode(Trig, OUTPUT); 
pinMode(Echo, INPUT); 
pinMode(ledPin, OUTPUT);   
m.init();
m.setIntensity(0);
Serial.begin(9600); 
} 

unsigned int time_us=0; //unsigned - специальный тип фиксированного размера

unsigned int distance_sm=0; 

void loop() { 

 digitalWrite(Trig, HIGH); // Подаем сигнал на выход микроконтроллера 
 delayMicroseconds(10); // Удерживаем 10 микросекунд 
 digitalWrite(Trig, LOW); // Затем убираем 
 time_us=pulseIn(Echo, HIGH); // pulseIn(*,HIGH) - Замеряем длину импульса 
 distance_sm=time_us/58; // Пересчитываем в сантиметры (S = Tus/58, [см] где Tus - длительность эхо импульса в микросекундах, а 58 - константа. )
 Serial.println(distance_sm); // Выводим на порт

   if (distance_sm<10) {   
        m.writeSprite(0, 0, CH_1); 
   }  
   else if (distance_sm>10&&distance_sm<20) {
         m.writeSprite(0, 0, CH_2);  
   }
   else if (distance_sm>20&&distance_sm<30) {
         m.writeSprite(0, 0, CH_3); 
   }
   else if (distance_sm>30&&distance_sm<40) {
         m.writeSprite(0, 0, CH_4); 
   }       
   else if (distance_sm>40&&distance_sm<50) {
         m.writeSprite(0, 0, CH_5); 
   }      
   else if (distance_sm>50&&distance_sm<=60) {
         m.writeSprite(0, 0, CH_6); 
   }
   else if(distance_sm>60&&distance_sm<70) {
         m.writeSprite(0, 0, CH_7); 
   }
   else if ((distance_sm>70)&&(distance_sm<80)) {
         m.writeSprite(0, 0, CH_8); 
   }       
   else {    
        m.clear(); 
   }
 delay(100); 
}
