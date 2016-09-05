data segment
	b      db 1,3,9,20,10,18,31,24,36,21,22,23,25,29,32,78,29,26,30,41
	long_b dw $-b
	c_arr  dw 15 dup(?)
data ends

data2 segment
	a      db 1,2,4,6,8,10,21,39,26,15,23,44,51,69,60
	long_a dw $-a
data2 ends

sta segment stack
	db 100 dup(?)
sta ends

code segment
	assume ds:data,ss:sta,cs:code,es:data2
main proc far
start:
	push ds
	xor ax,ax
	push ax
	mov ax,data
	mov ds,ax
	mov ax,data2
	mov es,ax

	mov bx,0       ;b array label
	mov si,0       ;c array label
	mov di,0       ;a array label
next:
	cmp bx,long_b
	je print
	mov al,b[bx]
	jmp compare
judge:
	inc bx
	cmp cx,0
	je next
	mov al,a[di-1]
	cbw
	mov c_arr[si],ax
	inc si
	inc si
	jmp next
compare:
	cld
	lea di,a
	mov cx,long_a
	repne scasb
	jmp judge
print:
	mov cx,si
	shr cx,1
	mov si,0
print2:
	mov ax,c_arr[si]
	call output
	add si,2
	call kg
	loop print2
	ret
main endp

output proc near
	push cx
	push ax
	xor cx,cx
	mov bx,10
next2:
	xor dx,dx
	div bx
	push dx
	inc cx
	cmp ax,0
	jne next2
next3:
	pop dx
	add dx,30h
	mov ah,02h
	int 21h
	dec cx
	cmp cx,0
	jne next3
	pop ax
	pop cx
	ret
output endp

kg proc near
	push ax
	push dx
	mov dl,20h
	mov ah,02h
	int 21h
	pop dx
	pop ax
	ret
kg endp
code ends
	end start