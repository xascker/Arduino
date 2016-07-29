
#include <Keypad.h>
	 
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'A','#','0','*'},
  {'B','3','2','1'},
  {'C','6','5','4'},
  {'D','9','8','7'}
};
byte rowPins[ROWS] = {9,8,7,6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5,4,3,2}; //connect to the column pinouts of the keypad
	 
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
 
void setup(){
    Serial.begin(9600);
}
	   
void loop(){
    char customKey = customKeypad.getKey();
	   
    if (customKey){
        Serial.println(customKey);
    }
}
