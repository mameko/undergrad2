data segment
	coname db 'SPACE EXPLORES INC.'
	prline db 20 dup(' ')
data ends
                           
sta segment stack 
	db 256 dup(?)
sta ends

code segment                ;10
	assume ds:data,ss:sta,cs:code,es:data
start:
	mov ax,data
	mov ds,ax
	mov es,ax           
	
	lea di,coname
	mov al,20h
	mov cx,20
	cld                 ;20    
	repne scasb         ;урЁЖ©у╦Я

	mov bx,30h
	cmp cx,0
	jnz exit          
	mov bx,20h           
exit:
	mov dl,bh
	mov ah,2
	int 21h            ;30
	mov dl,bl
	mov ah,2
	int 21h  
	mov ah,4ch           
	int 21h
code ends
end start