.include "tn13def.inc"

.def rKeyAddr = r21
.equ aKey = 0x60


.equ Tumbler_0 = 3
.equ Tumbler_1 = 4
.equ Tumbler_2 = 2
.equ Dq_pin = 0

.cseg

SBI ACSR, ACD ;Вырубаем аналоговый компаратор.

ldi r16, 0
out DDRB, r16

ldi r16, (1<<4)|(1<<3)|(1<<2) ;Ставим подтяжку на пины 4,3,2 порта B.
out PORTB, r16

;Задержка в 50mS
LDI  R17, 78
LDI  R16, 235
BigDelay0:
DEC  R16
BRNE BigDelay0
DEC  R17
BRNE BigDelay0

; Читаем переключатель:
in r16, PINB 
com r16 ;Инвертируем. 

;Исходя из положения переключателей, соображаем адрес кода нужного ключа.
;Делаем это, тупо переставляя биты. Иначе пришлось бы сначала выставить их в нормальном
;Порядке, а потом умножить на 8, чтобы получить адрес.
ldi rKeyAddr, 0
BST R16, Tumbler_1
BLD rKeyAddr, 4
BST R16, Tumbler_0
BLD rKeyAddr, 3
BST R16, Tumbler_2
BLD rKeyAddr, 5

;Убираем подтяжку с порта B
ldi r16, 0
out PORTB, r16


;Достаём из EEPROM код ключа.
;В оперативке он будет располагаться по адресу aKey и занимать 8 байт.
ldi ZL, aKey
clr ZH
clr R17
FillMemCycle:
	mov R16, rKeyAddr
	add R16, R17
	out EEARL, R16

	SBI EECR, EERE

	in R16, EEDR
	ST Z+, R16

	inc R17
	cpi R17, 8
brne FillMemCycle



MainCycle: ; Начало основного цикла.

;ждём пока домофон даст reset:
SBIC PINB, Dq_pin
rjmp PC-1

; Пропускаем RESET, ждем окончания импульса.
SBIS PINB, Dq_pin
rjmp PC-1

SBI DDRB, Dq_pin ;Прижимаем линию к земле.
 ldi r16, 40 ; Ждем 100uS
 dec r16     ; Это мы подаём PRESENSE импульс
 brne PC-1
CBI DDRB, Dq_pin


ldi r16, 4 ; Ждем 10uS
dec r16    ; За это время линия должна подняться после PRESENS импульса.
brne PC-1  ; Длительность взята с большим запасом.



;Ловим команду, которую даёт нам домофон.
clr R18
ldi R17,8
ReadCommCycle: 
	SBIC PINB, 0  //Ждем \___
	rjmp PC-1

	ldi r16, 8 ; Ждем 25uS
	dec r16    ; Если после этого линия поднялась, значит передали единичку
	brne PC-1  ; Иначе - ноль

	in R16, PINB
	LSR R18
	BST R16, 0
	BLD R18, 7
   
	SBIS PINB, 0 //Ждем ___/
	rjmp PC-1
   
	dec R17
brne ReadCommCycle



;Проверяем, может это команды для записи/чтения памяти?

cpi r18, 0 ;Сравниваем с командой на чтение.
brne read_skip
 rjmp comp_read ;Если совпало, то идем на процедуру чтения
read_skip:

cpi r18, 0xFF ;Сравниваем с командой на запись памяти
brne write_skip
 rjmp comp_read ;Если совпало, то идем на процедуру записи
write_skip:



;Теперь домофон, вероятно, попросит нас предъявить ему код... вуаля!
ldi R18,0
SelectByteCycle:

	clr ZH          //Загружаем в Р20 нужный байт кода
	ldi ZL, aKey
	add ZL, R18
	LD R20,Z

	ldi R19,8
	SendByteCycle:
   
		SBIC PINB, 0 //Ждём, пока домофон не прижмёт линию
		rjmp PC-1

		SBRS R20, 0  ;Если нужно передать нолик, то
		SBI DDRB,0   ;Прижать линию к земле.
		LSR R20


		ldi r16, 8 ; Ждем 30uS
		dec r16   
		brne PC-1      

		CBI DDRB, 0  //Отпускаем линию
		SBIS PINB, 0 //Ждём, пока она поднимется
		rjmp PC-1

		dec R19      //Тут кончается вложенный цикл
	brne SendByteCycle
    
	inc R18          //Тут кончается внешний цикл
	cpi R18,8
brne SelectByteCycle


;Идем в начало основного цикла
rjmp MainCycle




;Читаем EEPROM и выдаем её на линию. Все 64 байта подряд.
comp_read:

ldi R18,0
Comp_SelectByteCycle:
    out EEARL, R18 //Выцепляем из памяти нужный
    SBI EECR, EERE //байт для последующей
    in R20, EEDR   //отправки
    
    ldi R19,8
    Comp_SendByteCycle:
    	SBIC PINB, 0 //Ждём, пока домофон не прижмёт линию
    	rjmp PC-1

    	SBRS R20, 0 //ПРопустить след команду, если бит 0 в Р20 поднят
    	SBI DDRB,0
    	LSR R20

		ldi r16, 8 ; Ждем 30uS
		dec r16   
		brne PC-1      

    	CBI DDRB, 0  //Отпускаем линию
    	SBIS PINB, 0 //Ждём, пока она поднимется
    	rjmp PC-1

    	dec R19             //Тут кончается вложенный цикл
   	brne Comp_SendByteCycle

   	inc R18             //Тут кончается внешний цикл
  	cpi R18,64
brne Comp_SelectByteCycle

rjmp MainCycle




;Принимаем с линии байты и скидываем их в EEPROM
comp_write:

//Глава, посвещённая получению данных от компа и записи их в ЕЕПРОМ.
clr R18
ldi ZL, 0x60
clr ZH
     
ldi R19, 0
Comp_recv_q:
     
	ldi R17,8
	Comp_recv_byte:

	    SBIC PINB, 0  //Ждем \___
	    rjmp PC-1
    
		ldi r16, 8 ; Ждем 30uS
		dec r16   
		brne PC-1  
   
    	in R16, PINB
    	LSL R18
    	BST R16, 0
    	BLD R18, 0
    	SBIS PINB, 0 //Ждем ___/
    	rjmp PC-1

     	dec R17
    brne Comp_recv_byte
     
    ST Z+, R18
     
inc R19             //Тут кончается внешний цикл
cpi R19,64
brne Comp_recv_q

    
    //Теперь у нас в оперативке куча данных (точнее - 64 байта)
    //Их надо записать в ЕЕПРОМ.
    

ldi ZL, 0x60
clr ZH
ldi R19, 0
Comp_recv_write_mem:

	SBIC EECR, EEWE
    rjmp PC-1
       
    out EEARL, R19
    LD R16, Z+
    out EEDR, R16
    SBI EECR, EEMWE
    SBI EECR, EEWE
    
    inc R19
    cpi R19,64
brne Comp_recv_write_mem

rjmp MainCycle
