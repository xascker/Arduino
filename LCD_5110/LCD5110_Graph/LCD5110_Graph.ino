// It is assumed that the LCD module is connected to
// the following pins:
//      SCK  - Pin 8
//      MOSI - Pin 9
//      DC   - Pin 10
//      RST  - Pin 11
//      CS   - Pin 12
//
#include <LCD5110_Graph.h>

LCD5110 myGLCD(8,9,10,11,12);

extern unsigned char SmallFont[];

float y;

void setup()
{
  myGLCD.InitLCD(60);
  myGLCD.setFont(SmallFont);
}

void loop()
{
//  myGLCD.clrScr();

  myGLCD.drawLine(0, 23, 84, 23);
  myGLCD.drawLine(41, 0, 41, 47);
    for (int i=0; i<84; i++)
    {
      y=i*0.017453292519943295769236907684886;
      myGLCD.invPixel(i, (sin(y*6)*20)+23);
      myGLCD.update();
      delay(2);
    }
  //delay(2000);
}
