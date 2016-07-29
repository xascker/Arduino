// LCD5110_ViewFont (C)2013 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a demo of the included full font.
//
// This program requires a Nokia 5110 LCD module.
//
// It is assumed that the LCD module is connected to
// the following pins using a levelshifter to get the
// correct voltage to the module.
//      CLK  - Pin 8 
//      DIN  - Pin 9 
//      DC   - Pin 10  
//      RST  - Pin 11  
//      CE   - Pin 12
//

#include <LCD5110_Basic.h>

LCD5110 myGLCD(8,9,10,11,12);

extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

void setup()
{
  myGLCD.InitLCD(60);
  myGLCD.setFont(SmallFont);
}

void loop()
{
  myGLCD.setFont(BigNumbers); 
  myGLCD.clrScr();
  myGLCD.print("3", CENTER, 15);
  delay (1000);
  
  myGLCD.clrScr();
  myGLCD.print("2", CENTER, 15);
  delay (1000);
  
    myGLCD.clrScr();
  myGLCD.print("1", CENTER, 15);
  delay (1000);
  
      myGLCD.clrScr();
  myGLCD.print("0", CENTER, 15);
  delay (1000);

  myGLCD.setFont(SmallFont); 
  myGLCD.clrScr();
  myGLCD.print("Masha I Love", CENTER, 14);
  myGLCD.print("You", CENTER, 22);
  myGLCD.print("Very masch !!!", CENTER, 30);
  delay (5000);
  
  myGLCD.clrScr();
  myGLCD.print("And You?", CENTER, 16);
  myGLCD.print("Love Me?", CENTER, 24);
  delay (5000);
  
   myGLCD.clrScr();
  myGLCD.print("Kiss Me", CENTER, 16);
  delay (5000);
  
}
