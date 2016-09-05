.model small
.stack 100h
.data  
       cstring db 'based addressing'
.code 
start:
	mov ax,@data
	mov ds,ax
	
	mov dh,cstring
	mov dl,dh
	mov ah,2
	int 21h
	
	mov dl,cstring+6
	mov ah,2
	int 21h	
	
	mov ah,4ch
	int 21h
	end start
 