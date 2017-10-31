void setup() {
  // задаем частоту ШИМ на 3 выводе 30кГц
  TCCR2B=TCCR2B&0b11111000|0x01;
  analogWrite(3,130);
 
}
void loop(){
}
 
