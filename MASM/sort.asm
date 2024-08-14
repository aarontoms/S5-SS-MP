assume cs:code,ds:data
data segment
	string1 dw 000AH,001AH,0003H,000CH,0007H
data ends
code segment
start:
	mov ax,data
	mov ds,ax
	mov ch,04h
up2:
	mov cl,ch
	lea si,string1
up1:
	mov ax,[si]
	mov bx,[si+2]
 
	cmp ax,bx
	jc down;ax<bx

	mov dx,[si+2]
	xchg [si],dx
	mov [si+2],dx
down:
	inc si
	inc si
	dec cl
	jnz up1
	dec ch
	jnz up2
	mov ah,4ch
	int 21h
code ends
end start