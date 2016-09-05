data segment
	x db 5,?,6 dup(?)
data ends

sta segment stack
	db 100 dup(?)
sta ends

code segment
	assume ss:sta,cs:code,ds:data
main proc far
start:
	push ds
	xor ax,ax
	push ax
	mov ax,data
	mov ds,ax
	lea dx,x
	mov ah,0ah
	int 21h
	mov si,1
judge:
	inc si
	mov al,x[si]
	cbw
	mov ch,5
	mov cl,4
	mov bx,ax
	cmp bx,30h
	jl error
	cmp bx,39h
	jb sz
	cmp bx,40h
	jb error
	cmp bx,46h
	jna zm1
	cmp bx,60h
	jb error
	cmp bx,66h
	jna zm2
	ja error

sz:
	sub bx,30h
	jmp deal_with
zm1:
	sub bx,37h
	jmp deal_with
zm2:
	sub bx,57h

deal_with:
	dec ch
	jz print
	shr bx,1
	jc push_1
	mov ax,30h
	push ax
	jmp deal_with
push_1:
	mov ax,31h
	push ax
	jmp deal_with

print:
	pop dx
	mov ah,02h
	int 21h
	dec cl
	jnz print
	mov dl,20h
	mov ah,02h
	int 21h
	dec x+2
	jnz judge
error:
	ret
main endp
code ends
	end start	