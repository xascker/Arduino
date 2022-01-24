// всего 38 чипов WS2811 (+1 виртуальный для короткой ступени)
#include "Ultrasonic.h"

#define STEP_AMOUNT 13     // количество ступенек
#define STEP_LENGTH 3    // количество чипов WS2811 на ступеньку

#define AUTO_BRIGHT 1     // автояркость 0/1 выкл/вкл (с фоторезистором)
#define CUSTOM_BRIGHT 200  // ручная яркость 0-255

#define FADR_SPEED 200      // скорость эстафеты между ступеньками
#define START_EFFECT C_AQUA    // режим при старте C_WHITE, C_AQUA, C_VIOLET, COLOR, RAINBOW
#define ROTATE_EFFECTS 0      // 0/1 - автосмена эффектов
#define TIMEOUT 40            // секунд, таймаут выключения ступенек, если не сработал конечный датчик

// ПИНЫ !!!
#define BUTTON_START 3 // кнопка начало лестницы
#define BUTTON_END 4   // кнопка конец лестницы
#define BUTTON_SWICH 5   // кнопка переключения еффектов
#define STRIP_PIN 12   // пин ленты
#define PHOTO_PIN A5   // пин фоторезистора
//контакты для первого датчика HC-SR04
#define  ECHO1_PIN  8
#define  TRIG1_PIN  9
//контакты для второго датчика HC-SR04
#define  ECHO2_PIN  10
#define  TRIG2_PIN  11

Ultrasonic ULTRASONIC_START(TRIG1_PIN, ECHO1_PIN);
Ultrasonic ULTRASONIC_END(TRIG2_PIN, ECHO2_PIN);

const float Min_Distance_1 = 68.0; // 68.0см Диапазон, при котором сработает сенсор. Ширина первой ступеньки 75 см.
const float Min_Distance_2 = 53.0; // 39.0см; Ширина последней ступеньки 60 см.

#define ORDER_GBR      // порядок цветов ORDER_GRB / ORDER_RGB / ORDER_BRG / ORDER_GBR /  ORDER_BGR / ORDER_RBG
#define COLOR_DEBTH 3   // цветовая глубина: 1, 2, 3 (в байтах)
#include <microLED.h>
#define NUMLEDS STEP_AMOUNT * STEP_LENGTH // кол-во светодиодов
LEDdata leds[NUMLEDS];  // буфер ленты
microLED strip(leds, STRIP_PIN, STEP_LENGTH, STEP_AMOUNT, ZIGZAG, LEFT_BOTTOM, DIR_RIGHT);  // объект матрица

int8_t effDir;
byte curBright = CUSTOM_BRIGHT;
enum {S_IDLE, S_WORK} systemState = S_IDLE;
enum {C_WHITE, C_AQUA, C_VIOLET, COLOR, RAINBOW} curEffect = START_EFFECT;
#define EFFECTS_AMOUNT 5
byte effectCounter;
int counter = 0;

uint8_t effectMode = 0;

// ==== удобные макросы ====
#define FOR_i(from, to) for(int i = (from); i < (to); i++)
#define FOR_j(from, to) for(int j = (from); j < (to); j++)
#define FOR_k(from, to) for(int k = (from); k < (to); k++)
#define EVERY_MS(x) \
  static uint32_t tmr;\
  bool flag = millis() - tmr >= (x);\
  if (flag) tmr = millis();\
  if (flag)
//===========================

void setup() {
  //Serial.begin(9600);
  strip.setBrightness(curBright);    // яркость (0-255)

  // для кнопок
  pinMode(BUTTON_START, INPUT_PULLUP);
  pinMode(BUTTON_END, INPUT_PULLUP);
  pinMode(BUTTON_SWICH, INPUT_PULLUP);
}

void loop() {
  getBright();
  readSensors();
  swithEffects();
}

void getBright() {
#if (AUTO_BRIGHT == 1)
  if (systemState == S_IDLE) {  // в режиме простоя
    EVERY_MS(3000) {            // каждые 3 сек
      //Serial.println(analogRead(PHOTO_PIN));
      //curBright = map(analogRead(PHOTO_PIN), 30, 800, 10, 200);
      //strip.setBrightness(curBright);
      if (analogRead(PHOTO_PIN) > 300) {
        curBright = 0;
        strip.setBrightness(curBright);
      }
      else {
        curBright = CUSTOM_BRIGHT;
        strip.setBrightness(curBright);
      }
    }
  }
#endif
}

void swithEffects(){
  bool buttonState = digitalRead(BUTTON_SWICH); 
  if (buttonState == LOW) {
    //{C_WHITE, C_AQUA, C_VIOLET, COLOR, RAINBOW}
    switch(effectMode){
      case 0: 
        curEffect = C_VIOLET; 
        stepFader(0, 0); stepFader(0, 1); break;
      case 1: 
        curEffect = C_WHITE; 
        stepFader(0, 0); stepFader(0, 1); break;
      case 2: 
        curEffect = COLOR; 
        stepFader(0, 0); stepFader(0, 1); break;
      case 3: 
        curEffect = RAINBOW; 
        stepFader(0, 0); stepFader(0, 1); break;
      case 4: 
        curEffect = C_AQUA; 
        stepFader(0, 0); stepFader(0, 1); break;
    }
    if ( ++effectMode > 4 ) effectMode = 0;
    delay(300);
  }
}

// читаем сенсоры
void readSensors() {
  static bool flag1 = false, flag2 = false;
  static uint32_t timeoutCounter;

  // ТАЙМАУТ
  if (systemState == S_WORK && millis() - timeoutCounter >= (TIMEOUT * 1000L)) {
    systemState = S_IDLE;
    int changeBright = curBright;
    while (1) {
      EVERY_MS(50) {
        changeBright -= 5;
        if (changeBright < 0) break;
        strip.setBrightness(changeBright);
        strip.show();
      }
    }
    strip.clear();
    strip.setBrightness(curBright);
    strip.show();
  }

  EVERY_MS(50) {
    // СЕНСОР У НАЧАЛА ЛЕСТНИЦЫ
    //if (digitalRead(BUTTON_START)) {
    //if (!(ULTRASONIC_START.Ranging(CM) < Min_Disrance) && (ULTRASONIC_START.Ranging(CM) > 0)) {
    if ( (digitalRead(BUTTON_START)) && (!(ULTRASONIC_START.Ranging(CM) < Min_Distance_1) && (ULTRASONIC_START.Ranging(CM) > 0)) ) {
      if (!flag1) {
        flag1 = true;
        timeoutCounter = millis();
        if (systemState == S_IDLE) {
          effDir = 1;
          if (ROTATE_EFFECTS) {
            if (++effectCounter >= EFFECTS_AMOUNT) effectCounter = 0;
            curEffect = effectCounter;
          }
        }
        switch (systemState) {
          case S_IDLE: stepFader(0, 0); systemState = S_WORK; break;
          case S_WORK:
            if (effDir == -1) {
              stepFader(1, 1); systemState = S_IDLE;
              strip.clear(); strip.show(); return;
            } break;
        }
      }
    } else {
      if (flag1) flag1 = false;
    }

    // СЕНСОР У КОНЦА ЛЕСТНИЦЫ
    //if (digitalRead(BUTTON_END)) {
    if ( (digitalRead(BUTTON_END)) && (!(ULTRASONIC_END.Ranging(CM) < Min_Distance_2) && (ULTRASONIC_END.Ranging(CM) > 0)) ) {
      if (!flag2) {
        flag2 = true;
        timeoutCounter = millis();
        if (systemState == S_IDLE) {
          effDir = -1;
          if (ROTATE_EFFECTS) {
            if (++effectCounter >= EFFECTS_AMOUNT) effectCounter = 0;
            curEffect = effectCounter;
          }
        }
        switch (systemState) {
          case S_IDLE: stepFader(1, 0); systemState = S_WORK; break;
          case S_WORK:
            if (effDir == 1) {
              stepFader(0, 1); systemState = S_IDLE;
              strip.clear(); strip.show(); return;
            } break;
        }
      }
    } else {
      if (flag2) flag2 = false;
    }
  }
}
