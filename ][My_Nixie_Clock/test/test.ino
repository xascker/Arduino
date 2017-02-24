
int out1 = 4;
int out2 = 5;
int out3 = 6;
int out4 = 7;

int key1= 8;
int key2= 9;
int key3= 10;
int key4= 11;

void setup() {
  // задаем частоту ШИМ на 3 выводе 30кГц
  TCCR2B=TCCR2B&0b11111000|0x01;
  analogWrite(3,130);
  
  pinMode(out1,OUTPUT);
  pinMode(out2,OUTPUT);
  pinMode(out3,OUTPUT);
  pinMode(out4,OUTPUT);

  pinMode(key1,OUTPUT);
  pinMode(key2,OUTPUT);
  pinMode(key3,OUTPUT);
  pinMode(key4,OUTPUT);
}
void loop(){
  digitalWrite(key1,HIGH);
  digitalWrite(key2,LOW);
  digitalWrite(key3,LOW);
  digitalWrite(key4,LOW);
  

//   for (int a=0; a<=9; a++){
//       // a=0;
//      show(a);
//   delay(500);
//     }

int a=3;
show(a);
}
 
// void show(int a[])
void show(int a)
{
 setNumber(a);
}

void setNumber(int num)
{
 switch (num)
 {
   case 0:
   digitalWrite (out1,LOW);
   digitalWrite (out2,LOW);
   digitalWrite (out3,LOW);
   digitalWrite (out4,LOW);
   break;
   case 1:
   digitalWrite (out1,HIGH);
   digitalWrite (out2,LOW);
   digitalWrite (out3,LOW);
   digitalWrite (out4,LOW);
   break;
   case 2:
   digitalWrite (out1,LOW);
   digitalWrite (out2,HIGH);
   digitalWrite (out3,LOW);
   digitalWrite (out4,LOW);
   break;
   case 3:
   digitalWrite (out1,HIGH);
   digitalWrite (out2,HIGH);
   digitalWrite (out3,LOW);
   digitalWrite (out4,LOW);
   break;
   case 4:
   digitalWrite (out1,LOW);
   digitalWrite (out2,LOW);
   digitalWrite (out3,HIGH);
   digitalWrite (out4,LOW);
   break;
   case 5:
   digitalWrite (out1,HIGH);
   digitalWrite (out2,LOW);
   digitalWrite (out3,HIGH);
   digitalWrite (out4,LOW);
   break;
   case 6:
   digitalWrite (out1,LOW);
   digitalWrite (out2,HIGH);
   digitalWrite (out3,HIGH);
   digitalWrite (out4,LOW);
   break;
   case 7:
   digitalWrite (out1,HIGH);
   digitalWrite (out2,HIGH);
   digitalWrite (out3,HIGH);
   digitalWrite (out4,LOW);
   break;
   case 8:
   digitalWrite (out1,LOW);
   digitalWrite (out2,LOW);
   digitalWrite (out3,LOW);
   digitalWrite (out4,HIGH);
   break;
   case 9:
   digitalWrite (out1,HIGH);
   digitalWrite (out2,LOW);
   digitalWrite (out3,LOW);
   digitalWrite (out4,HIGH);
   break;
 }
}

