data segment
	m dw 1,2,-10,-8,11,24,-9,-5,-6,3,-7,28,30,0,-1,36,27,-27,18,29
	n dw ?
	p dw ?
	n0 dw ?
data ends

sta segment stack
	dw 100 dup(?)
sta ends
	
code segment 
main proc far
	assume cs:code,ss:sta,ds:data
start:
	push ds
	xor ax,ax
	push ax
	
	mov ax,data
	mov ds,ax
	               ;m��ǰ������������p���������������n�����Ը����ź��棬������ǰ��
	mov si,m+38
	mov di,m
next1:
	cmp word ptr[di],0
	jl next2
	add di,2       ;�ж���һ�������ڻ���С��0����С��0������������е���������
	jmp next1
next2:
	cmp word ptr[si],0     ;Ѱ��Ҫ������������0�ľ���di�ĸ�������
	jg change1     ;�ж���һ�����Ƿ����0
	sub si,2
	jmp next2
change1:
	mov ax,word ptr[si]	;��
	xchg word ptr[di],ax
	mov word ptr[si],ax
	add di,2	;����һ��
	sub si,2
	cmp di,si	;di<siʱ�Ѿ��������   
	jnc next1			

	lea ax,m[si+2]
	mov n,ax	;��n����ĵ�ַ��n   
	lea ax,m
	mov p,ax		;��m����ĵ�ַ��m
	call output       
	ret
main endp           

output proc near        ;�������PȻ���������N
	mov di,10        
	mov si,m
	mov cx,20
k_2:
	mov ax,[si]
	cmp ax,0
	jl change2
k_1:
	cmp ax,0
	je print
	mov dx,0
	imul di
	add dx,30h
	push dx
	inc n0
	jmp k_1
print:
	pop bx
	mov dl,bl
	mov ah,02h
	int 21h
	dec n0
	jnz print
	jmp next
change2:
	neg ax
	mov dl,'-'
	mov ah,02h
	int 21h
	jmp k_1
next:
	add si,2
	cmp si,n
	call hc
	loop k_2
	ret
output endp

hc proc near
	mov dl,0ah
	mov ah,02h
	int 21h
	mov dl,0dh
	mov ah,02h
	int 21h
	ret
hc endp
code ends
end start
