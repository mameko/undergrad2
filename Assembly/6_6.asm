.model small
.stack 100h
.code

main proc far
start:
	mov ax,@data
	mov ds,ax
	
	mov ah,01h
	int 21h
	cbw
	sub ax,30h
	mov cx,ax
next:
	call skiplines
	loop next

	mov ah,4ch
	int 21h
main endp

skiplines proc near
	mov dl,0ah
	mov ah,02h
	int 21h
	mov dl,0dh
	mov ah,02h
	int 21h
	ret
skiplines endp
	end start
