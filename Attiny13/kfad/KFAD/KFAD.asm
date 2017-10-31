.include "tn13def.inc"

.def rKeyAddr = r21
.equ aKey = 0x60


.equ Tumbler_0 = 3
.equ Tumbler_1 = 4
.equ Tumbler_2 = 2
.equ Dq_pin = 0

.cseg

SBI ACSR, ACD ;�������� ���������� ����������.

ldi r16, 0
out DDRB, r16

ldi r16, (1<<4)|(1<<3)|(1<<2) ;������ �������� �� ���� 4,3,2 ����� B.
out PORTB, r16

;�������� � 50mS
LDI  R17, 78
LDI  R16, 235
BigDelay0:
DEC  R16
BRNE BigDelay0
DEC  R17
BRNE BigDelay0

; ������ �������������:
in r16, PINB 
com r16 ;�����������. 

;������ �� ��������� ��������������, ���������� ����� ���� ������� �����.
;������ ���, ���� ����������� ����. ����� �������� �� ������� ��������� �� � ����������
;�������, � ����� �������� �� 8, ����� �������� �����.
ldi rKeyAddr, 0
BST R16, Tumbler_1
BLD rKeyAddr, 4
BST R16, Tumbler_0
BLD rKeyAddr, 3
BST R16, Tumbler_2
BLD rKeyAddr, 5

;������� �������� � ����� B
ldi r16, 0
out PORTB, r16


;������ �� EEPROM ��� �����.
;� ���������� �� ����� ������������� �� ������ aKey � �������� 8 ����.
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



MainCycle: ; ������ ��������� �����.

;��� ���� ������� ���� reset:
SBIC PINB, Dq_pin
rjmp PC-1

; ���������� RESET, ���� ��������� ��������.
SBIS PINB, Dq_pin
rjmp PC-1

SBI DDRB, Dq_pin ;��������� ����� � �����.
 ldi r16, 40 ; ���� 100uS
 dec r16     ; ��� �� ����� PRESENSE �������
 brne PC-1
CBI DDRB, Dq_pin


ldi r16, 4 ; ���� 10uS
dec r16    ; �� ��� ����� ����� ������ ��������� ����� PRESENS ��������.
brne PC-1  ; ������������ ����� � ������� �������.



;����� �������, ������� ��� ��� �������.
clr R18
ldi R17,8
ReadCommCycle: 
	SBIC PINB, 0  //���� \___
	rjmp PC-1

	ldi r16, 8 ; ���� 25uS
	dec r16    ; ���� ����� ����� ����� ���������, ������ �������� ��������
	brne PC-1  ; ����� - ����

	in R16, PINB
	LSR R18
	BST R16, 0
	BLD R18, 7
   
	SBIS PINB, 0 //���� ___/
	rjmp PC-1
   
	dec R17
brne ReadCommCycle



;���������, ����� ��� ������� ��� ������/������ ������?

cpi r18, 0 ;���������� � �������� �� ������.
brne read_skip
 rjmp comp_read ;���� �������, �� ���� �� ��������� ������
read_skip:

cpi r18, 0xFF ;���������� � �������� �� ������ ������
brne write_skip
 rjmp comp_read ;���� �������, �� ���� �� ��������� ������
write_skip:



;������ �������, ��������, �������� ��� ���������� ��� ���... �����!
ldi R18,0
SelectByteCycle:

	clr ZH          //��������� � �20 ������ ���� ����
	ldi ZL, aKey
	add ZL, R18
	LD R20,Z

	ldi R19,8
	SendByteCycle:
   
		SBIC PINB, 0 //���, ���� ������� �� ������ �����
		rjmp PC-1

		SBRS R20, 0  ;���� ����� �������� �����, ��
		SBI DDRB,0   ;������� ����� � �����.
		LSR R20


		ldi r16, 8 ; ���� 30uS
		dec r16   
		brne PC-1      

		CBI DDRB, 0  //��������� �����
		SBIS PINB, 0 //���, ���� ��� ����������
		rjmp PC-1

		dec R19      //��� ��������� ��������� ����
	brne SendByteCycle
    
	inc R18          //��� ��������� ������� ����
	cpi R18,8
brne SelectByteCycle


;���� � ������ ��������� �����
rjmp MainCycle




;������ EEPROM � ������ � �� �����. ��� 64 ����� ������.
comp_read:

ldi R18,0
Comp_SelectByteCycle:
    out EEARL, R18 //��������� �� ������ ������
    SBI EECR, EERE //���� ��� �����������
    in R20, EEDR   //��������
    
    ldi R19,8
    Comp_SendByteCycle:
    	SBIC PINB, 0 //���, ���� ������� �� ������ �����
    	rjmp PC-1

    	SBRS R20, 0 //���������� ���� �������, ���� ��� 0 � �20 ������
    	SBI DDRB,0
    	LSR R20

		ldi r16, 8 ; ���� 30uS
		dec r16   
		brne PC-1      

    	CBI DDRB, 0  //��������� �����
    	SBIS PINB, 0 //���, ���� ��� ����������
    	rjmp PC-1

    	dec R19             //��� ��������� ��������� ����
   	brne Comp_SendByteCycle

   	inc R18             //��� ��������� ������� ����
  	cpi R18,64
brne Comp_SelectByteCycle

rjmp MainCycle




;��������� � ����� ����� � ��������� �� � EEPROM
comp_write:

//�����, ����������� ��������� ������ �� ����� � ������ �� � ������.
clr R18
ldi ZL, 0x60
clr ZH
     
ldi R19, 0
Comp_recv_q:
     
	ldi R17,8
	Comp_recv_byte:

	    SBIC PINB, 0  //���� \___
	    rjmp PC-1
    
		ldi r16, 8 ; ���� 30uS
		dec r16   
		brne PC-1  
   
    	in R16, PINB
    	LSL R18
    	BST R16, 0
    	BLD R18, 0
    	SBIS PINB, 0 //���� ___/
    	rjmp PC-1

     	dec R17
    brne Comp_recv_byte
     
    ST Z+, R18
     
inc R19             //��� ��������� ������� ����
cpi R19,64
brne Comp_recv_q

    
    //������ � ��� � ���������� ���� ������ (������ - 64 �����)
    //�� ���� �������� � ������.
    

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
