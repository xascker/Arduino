#include <SPI.h>

typedef struct {uint8_t b; uint8_t g; uint8_t r;} RGB;
RGB pixel[32];

void setup() 
{
  Serial.begin(115200);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0); 
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  delay(1); 
}

void loop() 
{
run_pix(32); //количество тестируемых светодиодов в ленте
}

void run_pix(uint8_t num)
{
      pixel[0].r=0;   
      pixel[0].g=0;
      pixel[0].b=50;
         
   for(uint8_t i=0; i<num; i++) 
   {
     pixel[i+1].r=pixel[i].r; 
      pixel[i+1].g=pixel[i].g;
      pixel[i+1].b=pixel[i].b;
      pixel[i].r=0; 
      pixel[i].g=0;
      pixel[i].b=0; 
      set_pix(num); 
       delay(25); //пауза между вспышками светодиодов
   } 
}

void set_pix(uint8_t num)
{
   for(uint8_t i=0; i<num; i++) 
   {   
      SPI.transfer(pixel[i].b);
      SPI.transfer(pixel[i].g);
      SPI.transfer(pixel[i].r);
    }
  delay(1);
}
