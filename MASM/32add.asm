ASSUME CS:CODE, DS:DATA
DATA SEGMENT
	N1 DD 31345722H
	N2 DD 64154275H
	N3 DW 3 DUP(0)
DATA ENDS

CODE SEGMENT
START:
	MOV AX, DATA
	MOV DS, AX
	MOV AX, WORD PTR N1
	ADD AX, WORD PTR N2
	MOV N3, AX

	MOV AX, WORD PTR N1[2]
	ADC AX, WORD PTR N2[2]
	MOV N3[2], AX
	JNC STOP
	MOV N3[3], 01H
STOP:

MOV AH,4CH
INT 21H

CODE ENDS
END START