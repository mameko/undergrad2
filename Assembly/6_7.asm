.model small
.stack 100h

.data
	x db 76,69,84,90,73,88,99,63,100,80
	long dw $-x
	s6 db 0
	s7 db 0
	s8 db 0
	s9 db 0
	s10 db 0

.code
main proc far
start:
	mov ax,@data
	mov ds,ax

	mov cx,long
	mov si,0
next:	
	call judge
	inc si
	loop next

	add s10,30h	
	mov dl,s10
	mov ah,02h
	int 21h

	mov ah,4ch
	int 21h
main endp

judge proc near
	cmp x[si],60
	jb exit
	cmp x[si],69
	jbe k1
	cmp x[si],79
	jbe k2
	cmp x[si],89
	jbe k3
	cmp x[si],99
	jbe k4
	inc s10
	jmp exit
k1:
	inc s6
	jmp exit
k2:
	inc s7
	jmp exit
k3:
	inc s8
	jmp exit
k4:
	inc s9
	jmp exit
exit:
	ret
judge endp
	end start
