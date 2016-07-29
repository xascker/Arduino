int vall = 100;       //
int fadeAmount = 10;        // шаг изменения

unsigned long currentTime;
unsigned long loopTime;

const int pin_A = 12;       // pin 12
const int pin_B = 11;       // pin 11

unsigned char encoder_A;
unsigned char encoder_B;
unsigned char encoder_A_prev=0;

void setup() {

  pinMode(pin_A, INPUT);
  pinMode(pin_B, INPUT);
  currentTime = millis();
  loopTime = currentTime;
  
  Serial.begin(9600);
}


void loop() {
currentTime = millis();
  if(currentTime >= (loopTime + 5)){ // проверяем каждые 5мс (200 Гц)
    encoder_A = digitalRead(pin_A);     // считываем состояние выхода А энкодера 
    encoder_B = digitalRead(pin_B);     // считываем состояние выхода B энкодера    
    if((!encoder_A) && (encoder_A_prev)){    // если состояние изменилось с положительного к нулю
      if(encoder_B) {
        vall++;  // выход В в полож. сост., значит вращение по часовой стрелке
        Serial.println(vall);       
      }   
      else {
        vall-- ;     
        Serial.println(vall);  
      }   
 
    }   
    encoder_A_prev = encoder_A;     // сохраняем значение А для следующего цикла 
    
    loopTime = currentTime;
  }                       
}
