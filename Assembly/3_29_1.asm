data segment 
	coname db 'SPACE EXPLORERS INC.$'
	prline db  21 dup(' ')
DATA ENDS

sta segment stack 
	db 256 dup(?)
sta ends

CODE SEGMENT
	assume ss:sta,ds:data,cs:code,es:data
start:
	mov ax,data
	mov ds,ax
	mov es,ax
	
	lea si,coname
	lea di,prline
	cld
	mov cx,21
	rep movsb

	lea dx,prline
	mov ah,9
	int 21h
	
	mov ah,4ch
	int 21h
code ends
end start