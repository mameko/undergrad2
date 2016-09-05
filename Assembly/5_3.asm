data segment 
	x dw 1234h
data ends

sta segment stack
	db 100 dup(?)
sta ends

code segment
	assume ds:data,cs:code,ss:sta
start:
	mov ax,data
	mov ds,ax
	
	mov ax,x
	push ax
	and ax,000fh
	mov dl,al

	pop ax
	push ax
	and ax,0f00h
	mov cl,8
	shr ax,cl
	mov bl,al

	pop ax
	push ax
	and ax,0f000h
	mov cl,12
	shr ax,cl
	mov bh,al
	
	pop ax
	push ax
	and ax,00f0h
	mov cl,4
	shr ax,cl
	mov cl,al
	mov al,bh

	mov ah,4ch
	int 21h
code ends 
	end start