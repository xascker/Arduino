#include <SPI.h>
#define numpix 160

typedef struct {uint8_t b; uint8_t g; uint8_t r;} RGB;
RGB pixel[numpix];

void setup() {  
Serial.begin(115200);  
SPI.begin();  
SPI.setBitOrder(MSBFIRST);  
SPI.setDataMode(SPI_MODE0);   
SPI.setClockDivider(SPI_CLOCK_DIV16); 
 delay(1);
 }

void loop() { 
run_pix(numpix, 255, 0, 0 ); 
run_pix(numpix, 255, 255, 0 ); 
run_pix(numpix, 0, 255, 0 ); 
run_pix(numpix, 0, 255, 255 ); 
run_pix(numpix, 0, 0, 255 ); 
run_pix(numpix, 255, 0, 255 );
}

void run_pix(uint8_t num, uint8_t rp, uint8_t gp, uint8_t bp)
{         
 for(uint8_t i=0; i<num; i++)   
 {      
pixel[i].r=rp;       
pixel[i].g=gp;      
pixel[i].b=bp;      
set_pix(num);      
delay(5);   
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

