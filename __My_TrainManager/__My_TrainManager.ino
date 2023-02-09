#include <util/delay.h>
#include <OLED_I2C.h>
#include <EncButton.h>

EncButton<EB_TICK, 2, 3, 4> enc;  // энкодер с кнопкой | CLK -> 2; DT -> 3; SW -> 4

// Display:  SDA pin   -> Arduino Analog 4 or the dedicated SDA pin
//           SCL pin   -> Arduino Analog 5 or the dedicated SCL pin
// Buttons: 7 -> Left; 3 -> Menu; 4 -> Right

OLED myGLCD(SDA, SCL); // подключение дисплея
#define contrast 65    // контрастность дисплея
extern uint8_t SmallFont[], MediumNumbers[], TinyFont[], BigNumbers[];
//extern uint8_t logo[]; // for logo

#define VoltPin  A6 // пин датчика давлени
#define engene1_rotation_pin 8 // пин напрвление вращения; IN2
#define engene1_PWM_pin 9 // пин скорости вращения; IN1

int InputVolt;
float VoltTemp = 0.0;
float r1=100000.0; //сопротивление резистора r1
float r2=10000.0; // сопротивление резистора r2
String ver= "1.0";    // версия прошивки
int e_pwm = 0;

String engine_animation = "";

void setup() {
  pinMode (engene1_rotation_pin, OUTPUT);
  lcd_init(); // for logo

  attachInterrupt(0, isr, CHANGE);  // енкодор. D2
  attachInterrupt(1, isr, CHANGE);  // енкодор. D3
}

void isr() {
  enc.tickISR();  // енкодор. в прерывании вызываем тик ISR
}

void loop() {
  lcd_main();
  Encoder();
  EngeneManager();
}


void lcd_main() { // основной экран
  read_volt();
  myGLCD.clrScr();
  myGLCD.setFont(MediumNumbers);
  myGLCD.printNumI(InputVolt, LEFT, 0);
  myGLCD.printNumI(e_pwm, RIGHT, 0);
  myGLCD.printNumI(enc.counter, CENTER, 25);
  myGLCD.setFont(SmallFont);
  myGLCD.print("Volt/10", 40, 10);
  EngineAnim();
  myGLCD.update();
}


void lcd_init() { // заставка, лого
  myGLCD.begin();
  myGLCD.setBrightness(contrast);
  myGLCD.clrScr();
//  myGLCD.drawBitmap(0, 0, logo, 128, 23);
  myGLCD.setFont(SmallFont);
  myGLCD.print("Arduino", CENTER, 32);
  myGLCD.print("Train Manager", CENTER, 40);
  myGLCD.print("v"+ver, CENTER, 48);
  myGLCD.update();
  delay(1000);
}

void read_volt() {
  int VoltRead = analogRead(VoltPin);
  VoltTemp = ((VoltRead * 5.1) / 1024.0) * 10 ; // формула для конвертирования значения напряжения; 5.1 - напряжение питания ардуино
  InputVolt = VoltTemp / (r2/(r1+r2));
  delay(100);
}

void Encoder() {
    if ( enc.tick() ) {
      if ( enc.counter > 7 ) enc.counter = 7;
      if ( enc.counter < -7 ) enc.counter = -7;
      if ( enc.click() ) enc.counter = 0;

      // в конце лучше вызвать resetState(), чтобы сбросить необработанные флаги!
      enc.resetState();
  }
}

void EngineAnim() { // анимация на включение
  myGLCD.setFont(SmallFont);
  if ( enc.counter == 0 ) myGLCD.print(engine_animation , CENTER, 50);
  if ( enc.counter > 0 ) myGLCD.print(engine_animation , LEFT, 50);
  if ( enc.counter < 0 ) myGLCD.print(engine_animation , RIGHT, 50);
}

void EngeneManager() {
  EngineSpeed();
  analogWrite(engene1_PWM_pin, e_pwm); 

  // вперед
  if ( enc.counter > 0 ) {
    digitalWrite(engene1_rotation_pin, 0);
    delay(300);
  }

  // назад
  if ( enc.counter < 0 ) {
    digitalWrite(engene1_rotation_pin, 1);
    analogWrite(engene1_PWM_pin, e_pwm); 
    delay(300);
  }

  // стоп
  if ( enc.counter == 0 ) {
    digitalWrite(engene1_rotation_pin, 0);
    digitalWrite(engene1_PWM_pin, 0);
    delay(100);
  }  
}

void EngineSpeed() {
  switch (enc.counter) {
    case 0:
      e_pwm = 0;
      engine_animation = "STOP";
      break;
    case 1:
      e_pwm = 150;
      engine_animation = ">>>";
      break;
    case 2:
      e_pwm = 170;
      engine_animation = ">>>>>>>";
      break;
    case 3:
      e_pwm = 185;
      engine_animation = ">>>>>>>>>>";
      break;
    case 4:
      e_pwm = 200;
      engine_animation = ">>>>>>>>>>>>";
      break;
    case 5:
      e_pwm = 217;
      engine_animation = ">>>>>>>>>>>>>>";
      break;
    case 6:
      e_pwm = 235;
      engine_animation = ">>>>>>>>>>>>>>>>>";
      break;    
    case 7:
      e_pwm = 255;
      engine_animation = ">>>>>>>>>>>>>>>>>>>>";
      break;
    case -1:
      e_pwm = 105;
      engine_animation = "<<<";
      break;
    case -2:
      e_pwm = 85;
      engine_animation = "<<<<<<<";
      break;
    case -3:
      e_pwm = 70;
      engine_animation = "<<<<<<<<<<";
      break;
    case -4:
      e_pwm = 55;
      engine_animation = "<<<<<<<<<<<<";
      break;
    case -5:
      e_pwm = 35;
      engine_animation = "<<<<<<<<<<<<<<";
      break;
    case -6:
      e_pwm = 20;
      engine_animation = "<<<<<<<<<<<<<<<<<";
      break;
    case -7:
      e_pwm = 0;
      engine_animation = "<<<<<<<<<<<<<<<<<<<<";
      break;
  }
}

