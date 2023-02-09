#include <VarSpeedServo.h> 
 
VarSpeedServo myservo;    // create servo object to control a servo 
int rSpeedMax = 10;
int rSpeedMin = 30;
int rAngel1 = 45;
int rAngel2 = 125;

void setup() {
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() {
  myservo.write(rAngel2, random(rSpeedMax, rSpeedMin), true);        
  delay(random (200, 800));
  myservo.write(rAngel1, random(rSpeedMax, rSpeedMin), true);   
  delay(random (200, 800));
}
