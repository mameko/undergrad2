.model small
.stack 100h
.data
     string db 'The data is FEB&03$'
.code
start:
	mov ax,@data
	mov ds,ax
	
	mov dx,offset string
	mov ah,9
	int 21h

	mov string+15,20h
	mov dx,offset string
	mov ah,9
	int 21h

	mov ah,4ch
	int 21h
	end start