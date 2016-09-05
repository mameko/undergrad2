data segment
	x dw 3,0,0,9,0,6,8,7,2,1
	long dw $-x
	k dw ?
	n dw 0
data ends

sta segment stack
	db 100 dup(?)
sta ends

code segment
	assume ds:data,cs:code,ss:sta
main proc far
start:
	push ds
	xor ax,ax
	push ax
	mov ax,data
	mov ds,ax

	mov si,-2
	mov cx,long
	mov k,cx
next1:
	add si,2
	cmp si,k
	je k1
	cmp x[si],0
	je next1
	inc n
	jmp next1
k1:
	mov dx,n
	shl dx,1
	mov si,0
	mov ax,0
	mov long,ax	
next2:
	cmp x[si],0
	je press
	add si,2
	cmp si,k 
	jne next2	       
	sub cx,2
	jmp exit 
press:
	mov ax,x[si+2]
	mov x[si],ax
	add si,2
	cmp si,cx
	jne press
	mov si,0
next3:
	cmp x[si],0
	je press
	add si,2
	cmp si,dx
	jne next3	
exit: 
	mov si,k
	mov x[si+2],24h
	mov si,0
next4:
	add x[si],30h
	add si,2
	cmp si,cx
	jne next4

	lea dx,x
	mov ah,09h
	int 21h
	ret
main endp
code ends
	end start