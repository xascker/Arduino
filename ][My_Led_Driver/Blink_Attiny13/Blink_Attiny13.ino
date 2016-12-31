#include <inttypes.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// --- Configure for PIN
#define PIN0             PB0

int main() {
  DDRB=(0<<DDB5)|(0<<DDB4)|(0<<DDB3)|(0<<DDB2)|(0<<DDB1)|(1<<DDB0);
  PORTB=(0<<PORTB5)|(0<<PORTB4)|(0<<PORTB3)|(0<<PORTB1)|(0<<PORTB0);
  while(1){
    _delay_ms(500);    //Задержка
    PORTB |= (1<<PIN0);    //Включить свет
    _delay_ms(500);    //Задержка
    PORTB &= ~(1<<PIN0);    //Выключить свет
  }
}
