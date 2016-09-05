data segment
	dat dw 1,-2,3,6,8,9,12,18,13
	long dw $-dat
	sum dw 0
	n dw 0
data ends

sta segment stack
	db 100 dup(?)
sta ends

code segment
	assume ds:data,ss:sta,cs:code
main proc far
start:
	push ds
	xor ax,ax
	push ax
	mov ax,data
	mov ds,ax

	mov si,0
	mov cx,long
	shr cx,1
	xor ax,ax
	xor dx,dx
next1:
	add ax,dat[si]
	add si,2
	cmp si,long
	jne next1
	idiv cx
	mov si,-2
next2:
	add si,2
	cmp si,long
	je exit
	cmp dat[si],ax
	jg next2
	inc n
	jmp next2
exit:
	mov bx,n
	ret
main endp
code ends
	end start