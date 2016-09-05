data segment 
	arr db 1,0,3
	n db 0
data ends

sta segment stack
	db 100 dup(?)
sta ends

code segment
	assume ds:data,ss:sta,cs:code
main proc far
start:
	push ds
	xor ax,ax
	push ax
	mov ax,data
	mov ds,ax

	mov si,1
	mov al,arr[si-1]
	cmp al,arr[si]
	jne next1
	inc n
next1:
	mov al,arr[si]
	cmp al,arr[si+1]
	jne next2
	inc n
	cmp n,2
	je print
next2:	
	mov al,arr[si-1]
	cmp al,arr[si+1]
	jne print
	inc n
print:
	add n,30h
	mov dl,n
	mov ah,02h
	int 21h
	ret
main endp
code ends
	end start
	 