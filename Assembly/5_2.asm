data segment
	x1 db ?;��ǰ���Ǹ���ĸ
	x2 db ?;�ź����Ǹ���ĸ
data ends

sta segment stack
	db 100 dup(?)
sta ends

code segment
	assume ds:data,ss:sta,cs:code
start:
	mov ax,data
	mov ds,ax
	
	mov ah,01h
	int 21h

	mov bl,al
	dec bl
	mov x1,bl
      
	mov cl,al
	inc cl
	mov x2,cl

	mov ch,al	
	
	mov dl,x1
	mov ah,02h
	int 21h

	mov dl,ch
	mov ah,02h
	int 21h

	mov dl,x2
	mov ah,02h
	int 21h

	mov ah,4ch
	int 21h
code ends
	end start