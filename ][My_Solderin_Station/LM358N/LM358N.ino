
int increment = 0;   //Стартовое значение на сегментах
int tIn = 0;         // Пин Датчика температуры IN Analog через LM358N
int tData =  0;       //Переменная Датчика температура

void setup() {
    Serial.begin(9600);
}


void loop() {
    tData = analogRead(tIn); // Считать состояние датчика температуры и присвоить tdat
    tData = map(tData,0,430,25,310); // калибровка
    increment = tData;
    Serial.println(analogRead(tIn)); 
    Serial.println(increment); 
     delay(1000); 
}
