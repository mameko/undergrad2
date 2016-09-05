data segment
	coname db 'SPACE EXPLORES INC.'
	prline db 20 dup(' '),'$'
data ends
                           ;5
sta segment stack 
	db 256 dup(?)
sta ends

code segment                ;10
	assume ds:data,ss:sta,cs:code,es:data
start:
	mov ax,data
	mov ds,ax
	mov es,ax           ;15
	
	mov ax,30
	cld
	lea di,prline+5
	mov cx,8         ;20
	mov ah,41h
	mov al,42h
	stosw 
	lea dx,prline      
	mov ah,9         ;25
	int 21h
	mov ah,4ch          
	int 21h
code ends
end start                ;30