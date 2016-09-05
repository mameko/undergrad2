data segment 
	a dw 2
	b dw 4
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

	mov bx,a
	shr bx,1
	shl bx,1
	cmp bx,a
	je next1
	inc n
next1:
	mov cx,b
	shr cx,1
	shl cx,1
	cmp cx,b
	je even0
	inc n

	cmp n,1
	jne next2
	mov ax,a
	xchg b,ax
	mov a,ax
next2:
	cmp n,2
	jne even0
	inc a
	inc b
even0:
	ret
main endp
code ends
	end start 