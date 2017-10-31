/*     
LCD5110
    CLK  - Pin 8 
    DIN  - Pin 9 
    DC   - Pin 10  
    RST  - Pin 11  
    CE   - Pin 12

*/

#include <LCD5110_Basic.h>
#include <Wire.h> 
#include <BMP085.h>
#include <DHT.h>
#include <stdio.h>
#include <DS1302.h>

#define DHTPIN 2    //датчик влажности ко 2 пину
#define DHTTYPE DHT11

BMP085 dps = BMP085();    //vcc +3.3v; SDA->A4; SCL->A5 барометр

LCD5110 myGLCD(8,9,10,11,12);

DHT dht(DHTPIN, DHTTYPE);  //модуль часов

extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

long Temperature = 0, Pressure = 0;

//================= Часы ===================================
namespace {

const int kCePin   = 5;  // Chip Enable rst
const int kIoPin   = 6;  // Input/Output  dat
const int kSclkPin = 7;  // Serial Clock clk

DS1302 rtc(kCePin, kIoPin, kSclkPin);

String dayAsString(const Time::Day day) {
    switch (day) {
        case Time::kSunday: return "Sunday";
        case Time::kMonday: return "Monday";
        case Time::kTuesday: return "Tuesday";
        case Time::kWednesday: return "Wednesday";
        case Time::kThursday: return "Thursday";
        case Time::kFriday: return "Friday";
        case Time::kSaturday: return "Saturday";
    }
    return "(unknown day)";
}

void printTime() {
    Time t = rtc.time();
    const String day = dayAsString(t.day);
    char buf[50];
    
    //snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
    snprintf(buf, sizeof(buf), "%02d:%02d",
    //  day.c_str(),
    //  t.yr, t.mon, t.date,
    //  t.hr, t.min, t.sec);
        t.hr, t.min);

    myGLCD.print(buf, CENTER, 24);
    Serial.println(buf);
}
}  // namespace
//=========================================================

void setup() {
  myGLCD.InitLCD(60);  // контрасность LCD  
  dps.init();   
  dht.begin();

  rtc.writeProtect(false);    //часы
  rtc.halt(false);
  Time t(2014, 11, 27, 0, 00, 29, Time::kSunday);
  rtc.time(t);
 
  Serial.begin(9600); 
}

void loop() {
    dps.getPressure(&Pressure); 
    dps.getTemperature(&Temperature);
    float h = dht.readHumidity();
    myGLCD.clrScr();
    
    myGLCD.setFont(MediumNumbers);
    //myGLCD.setFont(BigNumbers);
    myGLCD.printNumI(Pressure/133.3, 7, 0);
    myGLCD.printNumI(Temperature*0.1, LEFT, 37);
    myGLCD.printNumI(h, 44, 37);
    
    myGLCD.setFont(SmallFont);
    myGLCD.print("C", 25, 47);
    myGLCD.print("mm.rt", 44, 10);
    myGLCD.print("%", 70, 47);
   
    printTime();
    
  Serial.print("Pressure(mm Hg): "); 
  Serial.print(Pressure/133.3);      //Выводим давление в мм.рт ст
  Serial.print("  Pressure(hPa): "); 
  Serial.println(Pressure*0.01);
  Serial.print("Temp: "); 
  Serial.println(Temperature*0.1);   // Температуру в градусах Цельсия
  Serial.print("Humidity: ");       
  Serial.println(h);                 //Влажность 
  
  delay(5000); 
}
