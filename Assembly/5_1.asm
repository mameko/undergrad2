data segment	
	x db ?
data ends

sta segment STACK
	db 256 dup (?)
sta ends

code segment
	assume cs:code,ss:sta,ds:data
start:
	mov ax,data
	mov ds,ax

	mov ah,01h
	int 21h
	
	add al,20h
	mov cl,al

	mov dl,cl
	mov ah,02h
	int 21h

	mov ah,4ch
	int 21h
code ends
    end start
