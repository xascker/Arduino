#include <util/delay.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

extern uint8_t logo[];

double data;

float DIST = 0.059; // 0.059; 59 мм

volatile unsigned char s1 = 0;
volatile unsigned char s2 = 0;

// Timer/Counter 0 initialization
void Timer0_Init( void )
{
    TCNT0 = 0;

    // Bits: COM0A1 COM0A0 COM0B1 COM0B0 - - WGM01 WGM00
    TCCR0A = 0;

    // Bits: FOC0A FOC0B - - WGM02 CS02 CS01 CS00
    TCCR0B = 0;

    // Bits: - - - - - OCIE0B OCIE0A TOIE0
    TIMSK0 = 0;

    // Bits: - - - - - OCF0B OCF0A TOV0
    TIFR0 = 0;
}

// Timer/Counter 1 initialization
void Timer1_Init( void )
{
    TCNT1 = 0;

    // Bits: COM1A1 COM1A0 COM1B1 COM1B0 - - WGM11 WGM10
    TCCR1A = 0;

    // Bits: ICNC1 ICES1 - WGM13 WGM12 CS12 CS11 CS10
    TCCR1B = 0;

    // Bits: FOC1A FOC1B - - - - - -
    TCCR1C = 0;

    // Bits: - - ICIE1 - - OCIE1B OCIE1A TOIE1
    TIMSK1 = 0;

    // Bits: – – ICF1 – - OCF1B OCF1A TOV1
    TIFR1 = 0;
}

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    
    display.clearDisplay();
    display.drawBitmap(0, 0, logo, 128, 64, WHITE);
    display.display();
    delay(2000);
    display.clearDisplay();
    display.display();
    
    // Global disable interrupts
    cli();

    // Timer/Counter 0 initialization
    Timer0_Init();

    // Timer/Counter 1 initialization
    Timer1_Init();

    // Global enable interrupts
    sei();

    //Serial.begin(9600);

    attachInterrupt(0, sensor_1, FALLING);
    attachInterrupt(1, sensor_2, FALLING);
}

void loop()
{
    while ( s1 == 0 && s2 == 0 ) ;
    _delay_ms(800); // wait 800 ms

    if ( s1 != 0 && s2 != 0 )
    {
        data = DIST / (TCNT1 * (1.0 / 16000000.0)); // v = s / t
    }
    else
    {
        data = 0;
    }

    //Serial.println(data);

    display.clearDisplay();
    display.setTextSize(3); 
    display.setTextColor(WHITE); 
    display.setCursor(0,23);  
    
    display.println(data);
    display.display();

    TCCR1B = 0;
    TCNT1 = 0;

    s1 = 0;
    s2 = 0;
}

void sensor_1()
{
    if ( s1 == 0 )
    {
        TCCR1B = (1<<CS10); // Timer/Counter 1 running (no prescaling)
        s1 = 1;
    }
}

void sensor_2()
{
    if ( s2 == 0 )
    {
        TCCR1B = 0; // Timer/Counter 1 stopped (no clock source)
        s2 = 1;
    }
}
