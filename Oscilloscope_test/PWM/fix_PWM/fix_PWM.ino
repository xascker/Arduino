int value = 0;       // переменная для хранения значения ШИМ
int ledpin = 9;      // светодиод подключён к выводу 9
 
void setup() 
{ 
  // ничего не устанавливаем
} 
 
void loop() 
{ 
    analogWrite(ledpin, 128);           
 
}
