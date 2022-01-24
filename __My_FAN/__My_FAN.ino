#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> // работа с прерываниями

#define LED     PB4
#define FAN     PB0
#define BUTTON  PB3

boolean lighthouse;
uint8_t mode = 0; //default mode

//ШИМ
int init_pwm (uint8_t pwm)
{
    TCCR0A = 0xB3;  //таймер A
    TCCR0B = 0x02;  //таймер B
    TCNT0  = 0x00;
    OCR0A  = pwm; 
    //TCCR0A = 0x83;  //таймер на 131
    _delay_ms(50);
}

void lighthouse_blink(){
    if (lighthouse){
        uint8_t i = 0;
        while(1){
            PORTB |= (1<<LED);      
            _delay_ms(50);
            PORTB &= ~(1<<LED);
            _delay_ms(50);
            if ( ++i >= 2 ) break; 
        }
        _delay_ms(2800);
    }
}

void mode_setup(){
    switch(mode){
        case 0: // Яркость PWM (Светлячок)
            init_pwm(255);
            break;
        case 1: // Яркость 50%
            init_pwm(200);
            break;
        case 2: // Яркость 100%
            init_pwm(150);
            break;
        case 3: // Яркость 100%
            init_pwm(100);
            break;
        case 4: // Яркость 100%
            init_pwm(50);
            break;
        default: 
            break;
    }
    if(mode >= 5 ) mode = 0;
}

ISR(PCINT0_vect){
    uint8_t i = 0;
    _delay_ms (50); // антидребезг (использовать задержки в прерываниях некошерно, но пока и так сойдёт)
    if ( (PINB & (1<<BUTTON)) == 0 ) mode++ ;
    while ( (PINB & (1<<BUTTON)) == 0 ) { // ждём отпускания кнопки
         i++;
        _delay_ms(50);
    }
    if (i >= 50) {
      lighthouse ^= true;
      mode--;
      i = 0;
    }
}

int main() {
    DDRB |= (1<<LED); // устанавливаем вывод порта как выход
    DDRB |= (1<<FAN); // устанавливаем вывод порта как выход
    PORTB |= (1<<FAN); //Включаем порт
    DDRB &= ~(1<<BUTTON); // устанавливаем вывод порта как вход
    PORTB |= (1<<BUTTON); // подтянуты
    GIMSK |= (1<<PCIE); // Разрешаем внешние прерывания PCINT0.
    PCMSK |= (1<<BUTTON); // Разрешаем по маске прерывания на ногак кнопки (PCINT4)
    sei(); // Разрешить глобальные прерывания
    
    while(1){
        lighthouse_blink();
        mode_setup();
    }
}
