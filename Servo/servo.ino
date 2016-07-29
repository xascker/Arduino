/*
Arduino Servo
*/
#include "Servo.h"
Servo servoMain; // Обьект Servo
 
void setup()
{
   servoMain.attach(10); // Servo присоединен к 10 выводу
}
 
void loop()
{
   servoMain.write(45);  // Повернуть серво влево на 45 градусов
   delay(100);          // Пауза 2 сек.
   servoMain.write(0);   // Повернуть серво влево на 0 градусов
   delay(1000);          // Пауза 1 сек.
   servoMain.write(90);  // Повернуть серво на 90 градусов. Центральная позиция
   delay(1500);          // Пауза 1.5 сек.
   servoMain.write(135); // Повернуть серво вправо на 135 градусов
   delay(3000);          // Пауза 3 сек.
   servoMain.write(180); // Повернуть серво вправо на 180 градусов
   delay(1000);          // Пауза 1 сек.
   servoMain.write(90);  // Повернуть серво на 90 градусов. Центральная позиция
   delay(5000);          // Пауза 5 сек.
}
