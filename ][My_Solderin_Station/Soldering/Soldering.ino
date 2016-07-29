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
#include <MsTimer2.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int test = 0;
int vall = 280;  //стартовое значение назаначаемой температуры паяльника     

int increment = 0;    //Стартовое значение на сегментах
int tIn = 0;          // Пин Датчика температуры IN Analog через LM358N
int tData =  0;       //Переменная Датчика температура

int nagr = 9;       //Пин вывода нагревательного элемента(через транзистор)
int nshim = 0;       // Начальное значение шим для нагрузки 

unsigned long currentTime;
unsigned long loopTime;

const int pin_A = 7;       // pin 7
const int pin_B = 6;       // pin 6

unsigned char encoder_A;
unsigned char encoder_B;
unsigned char encoder_A_prev=0;

void temp() {
  tData = analogRead(tIn); // Считать состояние датчика температуры и присвоить tdat
  test = analogRead(tIn);
  //tData = map(tData,0,580,25,480); // калибровка для lm358 от ардуинолаб
  //tData = map(tData,0,430,25,310); // калибровка для lm358
  //tData = map(tData,285,440,180,480); // калибровка для R 220 Ом
  tData = map(tData,290,440,120,380); // калибровка для R 220 Ом
  increment = tData;
}

void setup() {

  pinMode(pin_A, INPUT);
  pinMode(pin_B, INPUT);
  
  MsTimer2::set(1000, temp); // Запуск таймера считования температуры паяльника каждую 1сек
  MsTimer2::start(); 
  
  pinMode(nagr, OUTPUT);     // Порт нагрузки (паяльника) настраиваем на выход
  analogWrite(nagr, nshim);     //Вывод шим в нагрузку паяльника (выводим 0 - старт с выключенным паяльником - пока не определим состояние температуры)
  
  currentTime = millis();
  loopTime = currentTime;
  lcd.begin(16, 2);     
}


void loop() {
  Shim();
  LCDprint ();  
  Encoder_payalnik ();   
}

void Shim() {
  if (tData < vall ){   // Если температура паяльника ниже установленной температуры то:
      if ((vall - tData) < 16 & (vall - tData) > 6 ) { // Проверяем разницу между установленной температурой и текущей паяльника,
          // Если разница меньше 10 градусов, то 
          nshim = 190;  // Понижаем мощность нагрева (шим 0-255, мы делаем 99) - таким образом мы убираем инерцию перегрева
       }
          else if ((vall - tData) < 7 & (vall - tData) > 3) {              
              nshim = 150;  // Понижаем мощность нагрева (шим 0-255, мы делаем 99) - таким образом мы убираем инерцию перегрева
          }                           
          else if ((vall - tData) < 4 ) {              
              nshim = 99;  // Понижаем мощность нагрева (шим 0-255, мы делаем 45) - таким образом мы убираем инерцию перегрева
          }                
          else nshim = 255; // Иначе поднимаем мощность нагрева (шим 0-255, мы делаем 240) на максимум для быстрого нагрева до нужной температуры                                         
      analogWrite(nagr, nshim);     //Вывод в шим порт (на транзистор) значение мощности
     }
  else  { //Иначе (если температура паяльника равняется или выше установленной) 
      nshim = 0;  // Выключаем мощность нагрева (шим 0-255  мы делаем 0)  - таким образом мы отключаем паяльник
      analogWrite(nagr, nshim);   //Вывод в шим порт (на транзистор) значение мощности
 } 
}

void Encoder_payalnik () {  
  lcd.setCursor(3, 1);
  lcd.print(vall); 
  currentTime = millis();
  if(currentTime >= (loopTime + 5)){ // проверяем каждые 5мс (200 Гц)
    encoder_A = digitalRead(pin_A);     // считываем состояние выхода А энкодера 
    encoder_B = digitalRead(pin_B);     // считываем состояние выхода B энкодера    
    if((!encoder_A) && (encoder_A_prev)){    // если состояние изменилось с положительного к нулю
      if(encoder_B) {
        vall++;  // выход В, вращение по часовой стрелке
        lcd.setCursor(3, 1);
        lcd.print(vall);     
      }   
      else {
        vall-- ;     // вращение против часовой стрелке
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
  lcd.print(increment);
  
  lcd.setCursor(11, 0);
  lcd.print(test);  
}
  
  
  
  
  
