data segment
	n db 0
data ends

sta segment stack
	db 100 dup(?)
sta ends

code segment
main proc far
	assume ds:data,ss:sta,cs:code
start:
	push ds
	xor ax,ax
	push ax
	mov ax,data
	mov ds,ax
next:
	mov ah,01h
	int 21h
	cmp al,24h
	je exit	
	cmp al,30h
	ja sz
	add n,1
	jmp next
sz:
	cmp al,39h
	jb next
	add n,1
	jmp next
exit:
	mov dl,0ah
	mov ah,02h
	int 21h
	mov dl,0dh
	mov ah,02h
	int 21h
	add n,30h
	mov dl,n
	mov ah,02h
	int 21h
	ret
main endp
code ends
	end start
	