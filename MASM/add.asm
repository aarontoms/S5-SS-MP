ASSUME CS:CODE, DS:DATA
DATA SEGMENT
	N1 DW 1144H
	N2 DW 2233H
	N3 DW 2 DUP(0)
DATA ENDS

CODE SEGMENT
START:
	MOV AX,DATA
	MOV DS,AX
	MOV AX,N1
	ADD AX,N2
	MOV N3,AX
	JNC STOP
	MOV N3[2],01H

STOP:

MOV AH,4CH
INT 21H

CODE ENDS
END START