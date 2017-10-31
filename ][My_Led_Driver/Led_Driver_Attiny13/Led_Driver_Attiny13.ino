#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h> // здесь описаны режимы сна
#include <avr/interrupt.h> // работа с прерываниями
#include <avr/eeprom.h>


// --- Configure for LED PIN
#define LED0              PB0
#define LED1              PB1

uint8_t mode              = 0; //default mode
uint8_t switch_voltage [] = {0x8C, 0x98, 0xA3, 0xAE}; // 3.25 3.55 3.75 4.00 (140,152,163,174)

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

// Функция чтения АЦП
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

// Функция вывода заряда батареи
void display_voltage(){
    uint8_t v_batt;
    uint8_t i = 0;
    _delay_ms(250);
    v_batt = readADC();
    while(1){
        PORTB |= (1<<LED0);      
        _delay_ms(250);
        PORTB &= ~(1<<LED0);
        _delay_ms(250);
        if(v_batt < switch_voltage[i])
            break;
        if(++i >= 5 )
            break; 
     } 
    _delay_ms(250); 
}

//Ф-я сохранения батареи
void save_mode(){
    if (readADC() < 130){
        display_voltage();
        TCCR0A = 0x00;	// отключаем таймер
	TCCR0B = 0x00;	// отключаем таймер
    	ADCSRA = 0x00;	// отключаем ADC
	DDRB   = 0x00;	// отрубаем порт
        sleep_enable(); // разрешаем сон
        sleep_cpu(); // спать!
    }
}

//Режимы фонаря
void mode_setup(){
    mode=EEPROM_read(7);
    switch(mode){
        case 0: // Яркость 100%
            PORTB |= (1<<LED0);
            PORTB |= (1<<LED1);
            break;
        case 1: // Яркость 50%
            PORTB |= (1<<LED0);
            PORTB &= ~(1<<LED1); 
            //init_pwm(50); //ШИМ значение от 0-255
            break;
        case 2: // Яркость PWM (Светлячок)
            PORTB |= (1<<LED0);
            PORTB &= ~(1<<LED1); 
            init_pwm(15); //ШИМ значение от 0-255
            break;
        default: // Заряд батареи
            display_voltage();
            break;
    }
    if(++mode >= 3 ) mode = 0; 
    _delay_ms(50);
    EEPROM_write(7,mode); //Запись в EEPROM  будущий режим
    _delay_ms(3000);     
    if(mode == 0) mode = 3;
    mode--;
    _delay_ms(10);
    EEPROM_write(7,mode); //Запись в EEPROM  текущий режим
    _delay_ms(10);
}

int main() {
    TCCR0A = 0x00;	// отключаем таймер
    TCCR0B = 0x00;	// отключаем таймер
    adc_setup();
    //save_mode();
    mode_setup();
      
    while(1){
        sleep_enable(); // разрешаем сон
        sleep_cpu(); // спать
    }
}

