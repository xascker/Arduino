/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int vall = 250;  //стартовое значение назаначаемой температуры паяльника     

unsigned long currentTime;
unsigned long loopTime;

const int pin_A = 7;       // pin 7
const int pin_B = 6;       // pin 6

unsigned char encoder_A;
unsigned char encoder_B;
unsigned char encoder_A_prev=0;

void setup() {

  pinMode(pin_A, INPUT);
  pinMode(pin_B, INPUT);
  currentTime = millis();
  loopTime = currentTime;
  
  Serial.begin(9600);
  lcd.begin(16, 2);
}


void loop() {
LCDprint ();  
Encoder_payalnik ();                    
}

void Encoder_payalnik () {  
  currentTime = millis();
  if(currentTime >= (loopTime + 5)){ // проверяем каждые 5мс (200 Гц)
    encoder_A = digitalRead(pin_A);     // считываем состояние выхода А энкодера 
    encoder_B = digitalRead(pin_B);     // считываем состояние выхода B энкодера    
    if((!encoder_A) && (encoder_A_prev)){    // если состояние изменилось с положительного к нулю
      if(encoder_B) {
        vall++;  // выход В, вращение по часовой стрелке
        Serial.println(vall);  
        lcd.setCursor(3, 1);
        lcd.print(vall);     
      }   
      else {
        vall-- ;     // вращение против часовой стрелке
        Serial.println(vall); 
        lcd.setCursor(3, 1);
        lcd.print(vall);  
      }   
 
    }   
    encoder_A_prev = encoder_A;     // сохраняем значение А для следующего цикла   
    loopTime = currentTime;
  }                       
}

void LCDprint () {
  lcd.setCursor(0, 0);
  lcd.print("Pt");  
  lcd.setCursor(3, 0);
  lcd.print("250");
}
  
  
  
  
  
