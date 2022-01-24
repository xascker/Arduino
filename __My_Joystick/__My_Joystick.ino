#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
2, 0, // Button Count, Hat Switch Count
true, true, true, // X ,Y, Z Axis
true, true, true, // Rx, Ry, Rz Axis
true, true, // Rudder and Throttle
false, false, false); // No accelerator, brake, or steering
int button_1 = 2; // кнопка на pin2
int button_2 = 3; // кнопка на pin3
int button_1_state = 0;
int button_2_state = 0;
unsigned int xAxis_ = 0;
unsigned int yAxis_ = 0;
unsigned int zAxis_ = 0;
unsigned int RxAxis_ = 0;
unsigned int RyAxis_ = 0;
unsigned int RzAxis_ = 0;
int Rudder_ = 0;
int Throttle_ = 0;
const bool initAutoSendState = true; //!иначе придется обновлять состояние контроллера вручную

void setup(){
  Joystick.begin(); // инициализируем библиотеку
  pinMode(button_1, INPUT); // назначаем пин 10, на котором у нас кнопка, как вход.
  pinMode(button_2, INPUT);
//  Joystick.setXAxisRange(-256, 1024);
//  Joystick.setYAxisRange(-256, 1024);
//  Joystick.setZAxisRange(-256, 1024); // 2562
//  Joystick.setRxAxisRange(-256, 1024);
//  Joystick.setRyAxisRange(-256, 1024);
//  Joystick.setRzAxisRange(-256, 1024);
//  Joystick.setThrottleRange(0, 255);
//  Joystick.setRudderRange(0, 255);
}

void loop(){
  
int button_value1 = digitalRead(button_1);
int button_value2 = digitalRead(button_2);
Joystick.setButton(0,button_value1);
Joystick.setButton(1,button_value2);

xAxis_ = analogRead(A0);
Joystick.setXAxis(xAxis_);
yAxis_ = analogRead(A1);
Joystick.setYAxis(yAxis_);
zAxis_ = analogRead(A2);
Joystick.setZAxis(zAxis_);

RxAxis_ = analogRead(A3);
Joystick.setRxAxis(RxAxis_);
RyAxis_ = analogRead(A4);
Joystick.setRyAxis(RyAxis_);
RzAxis_ = analogRead(A5);
Joystick.setRzAxis(RzAxis_);

Rudder_ = analogRead(A6); //PIN4
Joystick.setRudder(Rudder_);
Throttle_ = analogRead(A7); //PIN6
Joystick.setThrottle(Throttle_);


}
