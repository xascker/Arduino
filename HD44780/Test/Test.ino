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

int a=257;
int b=100;
int c=290;
int d=90;

void setup() {
  lcd.begin(16, 2);
}

void loop() {

  lcd.setCursor(0, 0);
  lcd.print("Pt");
  lcd.setCursor(3, 0);
  lcd.print(a);
  lcd.setCursor(9, 0);
  lcd.print("Ft");
  lcd.setCursor(12, 0);
  lcd.print(c);
  lcd.setCursor(12, 1);
  lcd.print(d);
  for  (b=100; b<=257; b++)
   {
      lcd.setCursor(3, 1);
      lcd.print(b);
      delay (50);  
   }
  b=100;
}

