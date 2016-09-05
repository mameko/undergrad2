data segment
	n1 dw 0  ;number
	n2 dw 0  ;charater
	n3 dw 0  ;else
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

next1:
	mov ah,01h
	int 21h

	cmp al,0dh
	je exit

	cmp al,30h
	jb else0
	cmp al,3ah
	jb num
	cmp al,41h
	jb else0
	cmp al,5bh
	jb cha
	cmp al,61h
	jb else0
	cmp al,7bh
	jb cha
else0:
	inc n3
	jmp next1
cha:
	inc n2
	jmp next1
num:
	inc n1
	jmp next1
exit:
	mov dl,0ah
	mov ah,02h
	int 21h
	mov dl,0dh
	mov ah,02h
	int 21h

	mov ax,n1
	call output
	mov dl,20h
	mov ah,02h
	int 21h
	mov ax,n2
	call output
	mov dl,20h
	mov ah,02h
	int 21h
	mov ax,n3
	call output
	mov dl,20h
	mov ah,02h
	int 21h
	ret
main endp

output proc near
	xor cx,cx
	mov bx,10
next2:
	xor dx,dx
	div bx
	push dx
	inc cx
	cmp ax,0
	jne next2
next3:
	pop dx
	add dx,30h
	mov ah,02h
	int 21h
	dec cx
	cmp cx,0
	jne next3
	ret
output endp
code ends
	end start
