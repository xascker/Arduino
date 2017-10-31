
#include <FastLED.h>

// Define the number of LEDs
#define NUM_LEDS 32

// Define SPI Pin
#define CLOCK_PIN 13    //CK
#define DATA_PIN 11     //SD

// Baudrate, higher rate allows faster refresh rate and more LEDs (defined in /etc/boblight.conf)
#define serialRate 115200

// Adalight sends a "Magic Word" (defined in /etc/boblight.conf) before sending the pixel data
uint8_t prefix[] = {'A', 'd', 'a'}, hi, lo, chk, i;

// initialise LED-array
CRGB leds[NUM_LEDS];

void setup()
{
  
   FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RBG>(leds, NUM_LEDS);   //сдесь менял тип ленты
  
  // initial RGB flash
  LEDS.showColor(CRGB(255, 0, 0));
  delay(500);
  LEDS.showColor(CRGB(0, 255, 0));
  delay(500);
  LEDS.showColor(CRGB(0, 0, 255));
  delay(500);
  LEDS.showColor(CRGB(0, 0, 0));
  
  Serial.begin(serialRate);
  Serial.print("Ada\n"); // Send "Magic Word" string to host
  
}

void loop() { 
  // wait for first byte of Magic Word
  for(i = 0; i < sizeof prefix; ++i) {
    waitLoop: while (!Serial.available()) ;;
    // Check next byte in Magic Word
    if(prefix[i] == Serial.read()) continue;
    // otherwise, start over
    i = 0;
    goto waitLoop;
  }
  
  // Hi, Lo, Checksum
  
  while (!Serial.available()) ;;
  hi=Serial.read();
  while (!Serial.available()) ;;
  lo=Serial.read();
  while (!Serial.available()) ;;
  chk=Serial.read();
  
  // if checksum does not match go back to wait
  if (chk != (hi ^ lo ^ 0x55))
  {
    i=0;
    goto waitLoop;
  }
  
  memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));
  // read the transmission data and set LED values
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    byte r, g, b;    
    while(!Serial.available());
    r = Serial.read();
    while(!Serial.available());
    g = Serial.read();
    while(!Serial.available());
    b = Serial.read();
    leds[i].r = r;
    leds[i].g = g;
    leds[i].b = b;
  }
  // shows new values
 FastLED.show();
}
