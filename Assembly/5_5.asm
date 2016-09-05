data segment
	x db ?
data ends

sta segment stack
	db 100 dup(?)
sta ends

code segment
	assume ds:data,cs:code,ss:sta
	main proc far
start:
	push ds
	xor ax,ax
	push ax

	mov ax,data
	mov ds,ax
	
	mov ah,01h
	int 21h
	
	sub al,30h
	cbw
	mov cx,ax
ring:
	mov dl,07h
	mov ah,02h
	int 21h
	loop ring
	
	ret
	main endp
code ends
end start