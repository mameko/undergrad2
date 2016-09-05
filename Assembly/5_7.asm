data segment
	x     dw 1,9,4,6,2,7,8,5,11,12
	long  dw $-x
	min   dw ?
data ends

sta segment stack
	dw 100 dup(?)
sta ends

code segment
	assume ss:sta,cs:code,ds:data
main proc far
start:
	push ds
	xor ax,ax
	push ax
	mov ax,data
	mov ds,ax                          
	mov cx,long                         
	shr cx,1
	inc cx
	mov si,-2
	mov min,0
next:
	dec cx
	jz exit
	add si,2
	mov bx,x[si]
	shr bx,1                          
	shl bx,1                            
	cmp bx,x[si]
	je even_1
	cmp cx,0
	jmp next
even_1: 
	cmp min,0
	jne even_2
	mov dx,x[si]    
	mov min,dx      
even_2:
	mov dx,x[si]
	cmp min,dx                
	jna next
	mov min,dx
	jmp next
exit:
	mov ax,min
	ret
main endp
code ends
	end start