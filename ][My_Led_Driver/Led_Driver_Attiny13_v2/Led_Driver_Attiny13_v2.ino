#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h> // здесь описаны режимы сна
#include <avr/interrupt.h> // работа с прерываниями
#include <avr/eeprom.h>

// Стартует с светлячка, 50% затем 100%. При 3.2V и ниже включается только светлячок. Ниже 3V моргает 3 раза.

/* EEPROM Control Register */ // Добавил для новой версии Arduino IDE
#define    EERIE   3
#define    EEMWE   2
#define    EEWE    1
#define    EERE    0

// --- Configure for LED PIN
#define LED0              PB0
#define LED1              PB1

uint8_t mode              = 0; //default mode

//Ф-я записи в EEPROM
void EEPROM_write(unsigned int uiAddress, unsigned char ucData){
    while(EECR & (1<<EEPE));
    EEAR = uiAddress;
    EEDR = ucData;
    EECR |= (1<<EEMPE);
    EECR |= (1<<EEPE);
}

//Ф-я чтения EEPROM
unsigned char EEPROM_read(unsigned int uiAddress){
    while(EECR & (1<<EEWE));
    EEAR = uiAddress;
    EECR |= (1<<EERE);
    return EEDR;
}

void adc_setup(){
    DDRB=(0<<DDB5)|(0<<DDB4)|(0<<DDB3)|(0<<DDB2)|(1<<DDB1)|(1<<DDB0); // настраиваем пины на вывод
    PORTB=(0<<PORTB5)|(0<<PORTB4)|(0<<PORTB3)|(0<<PORTB1)|(0<<PORTB0); // все пины переводим в LOW 
    
    ADCSRA |= (1 << ADEN) // Разрешение АЦП
    |(1 << ADPS2)|(1 << ADPS1); // Предделитель на 64
    ACSR |= (1 << ACD); // Выключаем аналаговый компаратор
    DIDR0 |= (1 << ADC3D)|(1 << ADC2D); // Отключаем неиспользуемые цифровые входы
}

// Функция чтения АЦП; АЦП на ноге PB2(ADC1)
/*
По документации 1.1V == 255, на тесте 1.05V == 255
Делитель напряжение на 1V = 10K(+АЦП) vs 3K(-АЦП)
 */
int readADC(){ 
    ADMUX=(1<<REFS0)| 1; // Vref=1.1V , ADC1, Выбор канала АЦП 
    ADCSRA |= (1 << ADSC); // Запускаем преобразование
    while((ADCSRA & (1 << ADSC))); // Ждем окончания преобразования 
    return(ADC); // Возвращаем значение АЦП
}

//ШИМ
int init_pwm (uint8_t pwm)
{
    TCCR0A = 0x00;  //таймер A
    TCCR0B = 0x01;  //таймер B
    TCNT0  = 0x00;
    OCR0A  = pwm; 
    TCCR0A = 0x83;  //таймер на 131
}

void alarm_blink(uint8_t blk){
    uint8_t i = 0;
    while(1){
        PORTB |= (1<<LED0);      
        _delay_ms(100);
        PORTB &= ~(1<<LED0);
        _delay_ms(100);
        if(++i >= blk )
            break; 
    }
}

//(Светлячок) ШИМ значение от 0-255
void firefly_mode(uint8_t pwm){ 
    PORTB |= (1<<LED0);
    PORTB &= ~(1<<LED1); 
    init_pwm(pwm); 
}

//Режимы фонаря
void mode_setup(){
    mode=EEPROM_read(7);
    switch(mode){
        case 0: // Яркость PWM (Светлячок)
            firefly_mode(15); //ШИМ значение от 0-255
            break;
        case 1: // Яркость 50%
            PORTB |= (1<<LED0);
            PORTB &= ~(1<<LED1); 
            break;
        case 2: // Яркость 100%
            PORTB |= (1<<LED0);
            PORTB |= (1<<LED1);
            break;
        default: 
            alarm_blink(2); // После прошивки моргнуть 2 раза
            break;
    }
    if(++mode >= 3 ) mode = 0; 
    _delay_ms(50);
    EEPROM_write(7,mode); //Запись в EEPROM  будущий режим
    _delay_ms(1500);  // Время сброса на начало режимов    
    if(mode == 0) mode = 3;
    mode--;
    _delay_ms(10);
   // EEPROM_write(7,mode); //Запись в EEPROM  текущий режим (память последнего режима)
    EEPROM_write(7,0); //Запись в EEPROM  Светлячок (по дефолту) 
    _delay_ms(10);
}

/*
 Таблица напряжений к значению АЦП (Делитель напряжение на 1V)
 V      АЦП
 3.2    192
 3.0    147
 2.95   143
 2.9    130
 2.85   120
 */
void mode_selection(){
    uint8_t v_batt;
    v_batt = readADC();
    if (v_batt < 192){ // Ниже 3.2V
        if (v_batt < 147){ // Ниже 3.0V
            alarm_blink(3); // Моргнуть 3 раза
            PORTB &= ~(0<<LED1);
            _delay_ms(50);
            sleep_enable();
            sleep_cpu();
        }
        firefly_mode(15); // Светлячок, ШИМ значение от 0-255
    }
    else
        mode_setup();
}

int main() {
    TCCR0A = 0x00;  // отключаем таймер
    TCCR0B = 0x00;  // отключаем таймер
    adc_setup();
    mode_selection();  
          
    while(1){
        sleep_enable(); // разрешаем сон
        sleep_cpu(); // спать
    }
}

