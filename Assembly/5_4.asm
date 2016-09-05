data segment
	string1 db 'ABCDE$'
	long1   db $-string1
	string2 db 'ABCDE$'
	long2   db $-string2
	string3 db 'No Match!$'
	string4 db 'Match!$'
data ends

sta segment stack
	db 100 dup(?)
sta ends

code segment
	assume ds:data,ss:sta,cs:code,es:data
	main proc far
start:
	push ds
	xor ax,ax
	push ax

	mov ax,data
	mov ds,ax
	mov es,ax

	mov cl,long1
	mov ch,long2
	cmp cl,ch
	jne exit

	mov al,cl
	cbw
	cld
	mov cx,ax
	lea si,string1
	lea di,string2
	repe cmpsb
	cmp cx,0
	je exit2

exit:	lea dx,string3
	mov ah,09h
	int 21h
	jmp k
	
exit2:   
	lea dx,string4
	mov ah,09h
	int 21h

k:	ret
	main endp
	code ends
end start
	