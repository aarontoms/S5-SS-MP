print macro msg
lea dx, msg
mov ah, 09h
int 21h
endm

data segment
	array dw 0003h, 0010h, 0002h, 0020h, 0030h
	len1 equ($-array)
	key dw 0011h
	str1 db "key found$"
	str2 db "key not found$"
data ends

code segment
assume cs:code,ds:data
start:
	mov ax,data
	mov ds,ax

	lea si,array

	mov cx,len1
	mov bx,key

	next: mov ax,[si]
	cmp ax,bx
	jz found
	inc si
	dec cx
	jnz next

	print str2
	jmp exit

found: print str1
exit:
mov ah, 4ch
int 21h
code ends
end start
