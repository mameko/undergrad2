data segment 
	coname db 'SPACE EXPLORERS INC.'
	prline db 20 dup(' ')
data ends

sta segment stack 
	db 256 dup(?)
sta ends

code segment 
	assume ss:sta,cs:code,es:data,ds:data
start:
	mov ax,data
	mov ds,ax
	mov es,ax

	lods coname+3;把3个字节放入Al
	
	mov dl,al
	mov ah,2
	int 21h
	
	lods coname+4;把4个字节放入Al

	mov dl,ah
	mov ah,2
	int 21h
	
	mov ah,4ch
	int 21h
code ends
end start