#include "CyberLib.h"

unsigned long nTime, rTime, t;

void setup() 
{
  UART_Init(115200);
  StartSPI(0, 8, 1); //MODE0, DIV8, MSBFIRST
  for(int16_t z=0; z<768; z++) SendSPI(0); //погасить все пикселы ленты
  delay_ms(1); //пауза для инициализации ленты
}

void loop() 
{ Start
 uint8_t data; 
  t = millis(); //получаем текущее время
  UART_SendByte(170); //отправляем байт синхронизации для ПК
   if (UART_ReadByte(data))  //ждем от ПК первый байт с колличеством пикселей ленты
      {
         uint16_t pix_num = data*3;  //получаем общее колличество цветовых каналов ленты 
         uint16_t eTime = micros()-rTime; //получим время с момента окончания загрузки
         if( eTime < 900) delay_us(eTime);  //ждем полной инициализации (минус 100мкс для загрузки след. байта) 
            for(uint16_t i=0; i<pix_num; i++) SendSPI(uart_read());//считываем пиксели 
            rTime = micros(); //стартуем счетчик времени инициализации ленты
             nTime = t; // //обнулить время простоя 
      } else {  
               if((t - nTime) > 4000) ///гасим подсветку если нет потока более 2 сек
                {  
                 for(int16_t z=0; z<768; z++) 
                 SendSPI(0);
                 nTime = t; 
                }  
              }     
End }    
//***************************************************************************
unsigned char uart_read(void)
{
  uint8_t val;
  for (uint8_t i=0; i<255; ++i) //цикл ожидания байта данных из UART порта, время ожидания 2560мкс
    { 
      if(UART_ReadByte(val)) break; //если байт данных получен, то цикл прерывается
      delay_us(10);      //время ожидания байта
    } 
    return val;
}
