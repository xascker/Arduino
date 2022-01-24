#include <GyverPWM.h>

void setup() {
  pinMode(10, OUTPUT);

  // запустить ШИМ на D9 с частотой 250000 Гц, режим FAST_PWM
  // разрядность 6, см. таблицу №1 в GyverPWM.h
  PWM_resolution(10, 6, FAST_PWM);
}

void loop() {
  PWM_set(10, 25); // заполнение 40% 102
}
