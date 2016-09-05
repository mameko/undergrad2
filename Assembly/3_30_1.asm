data segment
	string db 'The data is FEB&03$'
data ends

sta segment stack
	db 256 dup(?)
sta ends

code segment
	assume cs:code,ds:data,es:data,ss:sta
start:
	mov ax,data
	mov ds,ax
	mov es,ax
	lea di,string
	cld
	mov cx,20
	mov al,'&'
	repne scasb
	mov byte ptr [di-1],20h       
	lea dx,string
	mov ah,9
	int 21h
	mov ah,4ch
	int 21h
code ends
	end start
	