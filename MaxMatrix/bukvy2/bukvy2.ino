
#include <MaxMatrix.h>
#include <avr/pgmspace.h> 

PROGMEM prog_uchar CH[] = { 
3, 8, B0000000, B0000000, B0000000, B0000000, B0000000, // space 
1, 8, B1011111, B0000000, B0000000, B0000000, B0000000, // ! 
3, 8, B0000011, B0000000, B0000011, B0000000, B0000000, // " 
5, 8, B0010100, B0111110, B0010100, B0111110, B0010100, // # 
4, 8, B0100100, B1101010, B0101011, B0010010, B0000000, // $ 
5, 8, B1100011, B0010011, B0001000, B1100100, B1100011, // % 
5, 8, B0110110, B1001001, B1010110, B0100000, B1010000, // & 
1, 8, B0000011, B0000000, B0000000, B0000000, B0000000, // ' 
3, 8, B0011100, B0100010, B1000001, B0000000, B0000000, // ( 
3, 8, B1000001, B0100010, B0011100, B0000000, B0000000, // ) 
5, 8, B0101000, B0011000, B0001110, B0011000, B0101000, // * 
5, 8, B0001000, B0001000, B0111110, B0001000, B0001000, // + 
2, 8, B10110000, B1110000, B0000000, B0000000, B0000000, // , 
4, 8, B0001000, B0001000, B0001000, B0001000, B0000000, // - 
2, 8, B1100000, B1100000, B0000000, B0000000, B0000000, // . 
4, 8, B1100000, B0011000, B0000110, B0000001, B0000000, // / 
4, 8, B0111110, B1000001, B1000001, B0111110, B0000000, // 0 
3, 8, B1000010, B1111111, B1000000, B0000000, B0000000, // 1 
4, 8, B1100010, B1010001, B1001001, B1000110, B0000000, // 2 
4, 8, B0100010, B1000001, B1001001, B0110110, B0000000, // 3 
4, 8, B0011000, B0010100, B0010010, B1111111, B0000000, // 4 
4, 8, B0100111, B1000101, B1000101, B0111001, B0000000, // 5 
4, 8, B0111110, B1001001, B1001001, B0110000, B0000000, // 6 
4, 8, B1100001, B0010001, B0001001, B0000111, B0000000, // 7 
4, 8, B0110110, B1001001, B1001001, B0110110, B0000000, // 8 
4, 8, B0000110, B1001001, B1001001, B0111110, B0000000, // 9 
2, 8, B01010000, B0000000, B0000000, B0000000, B0000000, // : 
2, 8, B10000000, B01010000, B0000000, B0000000, B0000000, // ; 
3, 8, B0010000, B0101000, B1000100, B0000000, B0000000, // < 
3, 8, B0010100, B0010100, B0010100, B0000000, B0000000, // = 
3, 8, B1000100, B0101000, B0010000, B0000000, B0000000, // > 
4, 8, B0000010, B1011001, B0001001, B0000110, B0000000, // ? 
5, 8, B0111110, B1001001, B1010101, B1011101, B0001110, // @ 
4, 8, B1111110, B0010001, B0010001, B1111110, B0000000, // A 
4, 8, B1111111, B1001001, B1001001, B0110110, B0000000, // B 
4, 8, B0111110, B1000001, B1000001, B0100010, B0000000, // C 
4, 8, B1111111, B1000001, B1000001, B0111110, B0000000, // D 
4, 8, B1111111, B1001001, B1001001, B1000001, B0000000, // E 
4, 8, B1111111, B0001001, B0001001, B0000001, B0000000, // F 
4, 8, B0111110, B1000001, B1001001, B1111010, B0000000, // G 
4, 8, B1111111, B0001000, B0001000, B1111111, B0000000, // H 
3, 8, B1000001, B1111111, B1000001, B0000000, B0000000, // I 
4, 8, B0110000, B1000000, B1000001, B0111111, B0000000, // J 
4, 8, B1111111, B0001000, B0010100, B1100011, B0000000, // K 
4, 8, B1111111, B1000000, B1000000, B1000000, B0000000, // L 
5, 8, B1111111, B0000010, B0001100, B0000010, B1111111, // M 
5, 8, B1111111, B0000100, B0001000, B0010000, B1111111, // N 
4, 8, B0111110, B1000001, B1000001, B0111110, B0000000, // O 
4, 8, B1111111, B0001001, B0001001, B0000110, B0000000, // P 
4, 8, B0111110, B1000001, B1000001, B10111110, B0000000, // Q 
4, 8, B1111111, B0001001, B0001001, B1110110, B0000000, // R 
4, 8, B1000110, B1001001, B1001001, B0110010, B0000000, // S 
5, 8, B0000001, B0000001, B1111111, B0000001, B0000001, // T 
4, 8, B0111111, B1000000, B1000000, B0111111, B0000000, // U 
5, 8, B0001111, B0110000, B1000000, B0110000, B0001111, // V 
5, 8, B0111111, B1000000, B0111000, B1000000, B0111111, // W 
5, 8, B1100011, B0010100, B0001000, B0010100, B1100011, // X 
5, 8, B0000111, B0001000, B1110000, B0001000, B0000111, // Y 
4, 8, B1100001, B1010001, B1001001, B1000111, B0000000, // Z 
2, 8, B1111111, B1000001, B0000000, B0000000, B0000000, // [ 
4, 8, B0000001, B0000110, B0011000, B1100000, B0000000, // backslash 
2, 8, B1000001, B1111111, B0000000, B0000000, B0000000, // ] 
3, 8, B0000010, B0000001, B0000010, B0000000, B0000000, // hat 
4, 8, B1000000, B1000000, B1000000, B1000000, B0000000, // _ 
2, 8, B0000001, B0000010, B0000000, B0000000, B0000000, // ` 
4, 8, B0100000, B1010100, B1010100, B1111000, B0000000, // a 
4, 8, B1111111, B1000100, B1000100, B0111000, B0000000, // b 
4, 8, B0111000, B1000100, B1000100, B0101000, B0000000, // c 
4, 8, B0111000, B1000100, B1000100, B1111111, B0000000, // d 
4, 8, B0111000, B1010100, B1010100, B0011000, B0000000, // e 
3, 8, B0000100, B1111110, B0000101, B0000000, B0000000, // f 
4, 8, B10011000, B10100100, B10100100, B01111000, B0000000, // g 
4, 8, B1111111, B0000100, B0000100, B1111000, B0000000, // h 
3, 8, B1000100, B1111101, B1000000, B0000000, B0000000, // i 
4, 8, B1000000, B10000000, B10000100, B1111101, B0000000, // j 
4, 8, B1111111, B0010000, B0101000, B1000100, B0000000, // k 
3, 8, B1000001, B1111111, B1000000, B0000000, B0000000, // l 
5, 8, B1111100, B0000100, B1111100, B0000100, B1111000, // m 
4, 8, B1111100, B0000100, B0000100, B1111000, B0000000, // n 
4, 8, B0111000, B1000100, B1000100, B0111000, B0000000, // o 
4, 8, B11111100, B0100100, B0100100, B0011000, B0000000, // p 
4, 8, B0011000, B0100100, B0100100, B11111100, B0000000, // q 
4, 8, B1111100, B0001000, B0000100, B0000100, B0000000, // r 
4, 8, B1001000, B1010100, B1010100, B0100100, B0000000, // s 
3, 8, B0000100, B0111111, B1000100, B0000000, B0000000, // t 
4, 8, B0111100, B1000000, B1000000, B1111100, B0000000, // u 
5, 8, B0011100, B0100000, B1000000, B0100000, B0011100, // v 
5, 8, B0111100, B1000000, B0111100, B1000000, B0111100, // w 
5, 8, B1000100, B0101000, B0010000, B0101000, B1000100, // x 
4, 8, B10011100, B10100000, B10100000, B1111100, B0000000, // y 
3, 8, B1100100, B1010100, B1001100, B0000000, B0000000, // z 
3, 8, B0001000, B0110110, B1000001, B0000000, B0000000, // { 
1, 8, B1111111, B0000000, B0000000, B0000000, B0000000, // | 
3, 8, B1000001, B0110110, B0001000, B0000000, B0000000, // } 
4, 8, B0001000, B0000100, B0001000, B0000100, B0000000, // ~ 
};  



byte A[] = {4, 8, B11111110, B00010001, B00010001, B11111110 };			//А
byte B[] = {4, 8, B11111111, B10001001, B10001001, B11110001 };			//Б
byte V[] = {4, 8, B11111111, B10001001, B10001111, B11111000 };			//В
byte G[] = {4, 8, B11111111, B00000001, B00000001, B00000001 };			//Г
byte D[] = {5, 8, B11000000, B01111110, B01000001, B01111110, B11000000}; 	//Д
byte E[] = {4, 8, B11111111, B10001001, B10001001, B10001001 }; 		//Е
byte J[] = {5, 8, B11000011, B00111100, B11111111, B00111100, B11000011}; 	//Ж
byte Z[] = {4, 8, B01000010, B10001001, B10001001, B11110111 }; 		//З
byte I[] = {4, 8, B11111111, B00110000, B00001100, B11111111};          	//И
byte K[] = {4, 8, B11111111, B00011000, B01100110, B10000001 };	                //K
byte L[] = {4, 8, B10000000, B01111110, B00000001, B11111111 };			//Л
byte M[] = {5, 8, B11111111, B00000011, B00000100, B00000011, B11111111}; 	//M
byte N[] = {4, 8, B11111111, B00010000, B00010000, B11111111};          	//Н
byte O[] = {4, 8, B01111110, B10000001, B10000001, B01111110 };			//O
byte P[] = {4, 8, B11111111, B00000001, B00000001, B11111111 };			//П
byte R[] = {4, 8, B11111111, B00001001, B00001001, B00001111 }; 		//Р
byte C[] = {4, 8, B01111110, B10000001, B10000001, B01000010 };			//С
byte T[] = {5, 8, B00000001, B00000001, B11111111, B00000001, B00000001};	//T

// описание подключения
// DIN к 8
// CS к 9
// CLK к 10
// 1 модуль (Когда 2 матрицы последняя цифра меняется с 1 на кол-во матриц)
MaxMatrix m(8, 9, 10, 1);

byte buffer[10]; 
char msg[] = "12345678901234567890=+++"; 

void setup(){
m.init();  
m.setIntensity(0);  
printString(msg);
}

void loop()
{   
printString(msg);
// delay(100);  
//m.shiftLeft(false, true); 

}   



void printString(char* s) 
 {    
   while (*s != 0)   
  {     
    if (*s < 32) return;   
    char c = *s - 32;    
    memcpy_P(buffer, CH + 7*c, 7);  
    m.writeSprite(32, 0, buffer);  
    m.setColumn(32 + buffer[0], 0);    
    for (int i=0; i<buffer[0]+1; i++){
      delay(100);     
    m.shiftLeft(false, false);   
    }
        s++;
  }   
}

/*
 void printString(char* s) 
 {   
   int col = 0;  
   while (*s != 0)   
  {     
    if (*s < 32) continue;    
    char c = *s - 32;    
    memcpy_P(buffer, CH + 7*c, 7);  
    m.writeSprite(col, 0, buffer);  
    m.setColumn(col + buffer[0], 0);    
    col += buffer[0] + 1;   
    s++;  
  } 
  
}
*/
