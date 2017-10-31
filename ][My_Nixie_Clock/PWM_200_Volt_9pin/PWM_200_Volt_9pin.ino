void setup() {
  // задаем частоту ШИМ на 3 выводе 30кГц
  TCCR1B=TCCR1B&0b11111000|0x01;
  analogWrite(9,130);
 
}
void loop(){
}
 
