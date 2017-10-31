
#include "Keypad.h"
#include "Servo.h"

#define KeysSize 4

int PASS = 1234;

Servo servoMain;     // Обьект Servo
	 
const byte ROWS = 4; //кол-во строк
const byte COLS = 4; //кол-во столбов

char Keys[ROWS][COLS] = {
    {'A','#','0','*'},
    {'B','3','2','1'},
    {'C','6','5','4'},
    {'D','9','8','7'}
};
byte rowPins[ROWS] = {9,8,7,6}; //строки ввода
byte colPins[COLS] = {5,4,3,2}; //столбцы вывода
	 
Keypad customKeypad = Keypad( makeKeymap(Keys), rowPins, colPins, ROWS, COLS); 

unsigned char row_counter=0;	   //количество нажатых клавиш
unsigned char BufKey[KeysSize]={}; //массив, который содержит нажатые клавиши
unsigned long int BufPass=0;       //переменная для ковертации в нее char масива(Buf[KeysSize])

void setup(){
    pinMode(13, OUTPUT);
    servoMain.attach(10);           // 10 пин - серва
    servoMain.write(0);             // положение сервы при включении
    Serial.begin(9600);
    customKeypad.addEventListener(ChengPass);
}
	   
void loop(){
    char customKey = customKeypad.getKey();
	   
    if (customKey)
        Serial.println(customKey);  //вывод нажых кнопок           
    
    if ((is_digit(customKey)==1)&&(row_counter<KeysSize)) { //Нажата цифра и не достигнут лимит в KeysSize
        BufKey[row_counter]=customKey;                      //Добавить в row и увеличить row_counter
        row_counter++;
    }
    
    if (customKey == 'B')                   //Если нажата 'B' очищаем BufKey
        row_counter=0;             
        
    if ((customKey == 'D')&&(row_counter>0)) 
        row_counter--;                      //Если нажата 'D' удалить последнюю цифру
        
    if (customKey == '*')                   //Если нажата '*' запираем замок
        Lock();      
        
    if (customKey == 'A') {	            //Если нажата 'A' тогда сверяем BufPass и код доступа замка
        get_BufPass();
            if (BufPass==PASS) {
                UnLock ();                  //отпираем замок
                row_counter=0;              //очищаем BufKey
            }
                else {
                    Serial.print("Error Pass: ");
                    Serial.println(BufPass);
                    for (int i=0; i<4; i++){
                        digitalWrite(13, HIGH); 
                        delay(500);              
                        digitalWrite(13, LOW);    
                        delay(500);   
                    }
                    row_counter=0;          //очищаем BufKey
                }            
     }        
} 

//Конвертирует "BufKey" в int значение BufPass
void get_BufPass(void) { 
    unsigned char i;
    BufPass=0;
    for (i=0; i<row_counter; i++) { 
        BufPass=BufPass*10;
	BufPass=BufPass+BufKey[i]-0x30;
   }
}

//Проверка, является ли х цифрой, если да результат =1, иначе результат =0
unsigned char is_digit (unsigned char x) {
    if ((x>='0')&&(x<='9')) return 1; 
    else return 0;
}

void UnLock(void) {
    Serial.print("Pass OK: ");
    Serial.println(BufPass);
    digitalWrite(13, HIGH); 
    delay(1000);
    digitalWrite(13, LOW);
    servoMain.write(110);               // Повернуть серво на 0 градусов
}

void Lock(void) {
    for (int i=0; i<2; i++){            // мигать 2 раза
        digitalWrite(13, HIGH); 
        delay(500);              
        digitalWrite(13, LOW);    
        delay(500);   
     }
     servoMain.write(0);                 // Повернуть серво на 0 градусов
}

// Замена стандартного пароля
void ChengPass(KeypadEvent Key){
    int time = 0;                       // Счетчик времени нажатия кнопки    
    servoMain.read();
    int val = servoMain.read();         // положение сервы    
    switch (customKeypad.getState()){  
       
    case HOLD:
        if ((Key == 'C')&&(val == 110)){     //если нажата копка 'C' и замок открыт
            for(int i=0; i<40; i++ ) {       //запустить цикл времени нажатия кнопки - 4 сек
                time++;
                delay(100);
            }
         }
        if ((Key == 'C')&&(time>=40)&&(val == 110)) {  //если копка 'C' нажата более 4 сек и замок открыт 
            for (int i=0; i<6; i++){                   // мигать 6 раз
                digitalWrite(13, HIGH); 
                delay(500);              
                digitalWrite(13, LOW);    
                delay(500);   
            }
            time = 0;
            row_counter=0;
            Serial.println("Enter new PASS: ");
            break;
        } 
            if ((row_counter == KeysSize)&&(Key == '#')) { //если нажата копка '#' и длина пароля равна 4
                get_BufPass();                             
                PASS = BufPass;                            //меняем пароль
                row_counter=0;                             // сбрасываем счетчики
                time = 0;                                  //
                Serial.println("New PASS: ");
                Serial.println(BufPass);
                    for (int i=0; i<3; i++){               // мигать 3 раза
                        digitalWrite(13, HIGH); 
                        delay(500);              
                        digitalWrite(13, LOW);    
                        delay(500);   
                    }
            }  
    }
}

