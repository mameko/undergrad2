data segment
	a0 dw 1
	b0 dw 2
	c0 dw 3
	d0 dw ?
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

	cmp a0,0
	je clear
	cmp b0,0
	je clear
	cmp c0,0
	je clear

	mov ax,0
	add ax,a0
	add ax,b0
	add ax,c0
	mov d0,ax
	jmp exit
clear:
	mov a0,0
	mov b0,0
	mov c0,0
exit:	
	ret
main endp
code ends
	end start