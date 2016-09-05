data segment
	string db a,b,c,d,1,3,e,f,g,h,i
	long dw $-string
data ends

sta segment stack
	db 100 dup(?)
sta ends

code segment
	assume ds:data,cs:code,ss:sta
main proc fat
start:
	mov si,0
	xor cl,cl
next:
	cmp string[si],30h
	jnb sz                       ;可能是数字
	inc si
	cmp si,long
	jne next
	jmp exit
sz:
	cmp string[si],39h
	jnb next
	and cl,00010000b
exit:
	mov dl,cl
	mov ah,02h
	int 21h
main endp
code ends
	end start