#include <GyverPWM.h>

void setup() {
  pinMode(10, OUTPUT);

  // запустить ШИМ на D10 с частотой 200'000 Гц, режим FAST_PWM
  PWM_frequency(10, 200000, FAST_PWM);
}

void loop() {
  PWM_set(10, 102);  // заполнение 40% (0-255)
}
