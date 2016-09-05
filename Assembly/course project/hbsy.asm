data segment
	mes1 db 'please input a small charater.q:quit c:change',0ah,0dh,'Time now is:',20h,'$'
	mes3 db 'input the time:$'
	x db 3,?,4 dup(?)
	n db ?
	n1 db ?
	n2 db ?
	n3 db ?
	n4 db ?
	n5 db ?
data ends

sta segment stack
	dw 100 dup(?)
sta ends

code segment
main proc far
	assume cs:code,ds:data,ss:sta
start:
	push ds
	xor ax,ax
	push ax

	mov ax,data
	mov ds,ax

	lea dx,mes1      ;print the first message
	call print9

	mov ah,0fh	 ;read the location 
	int 21h
	mov ah,3         
	int 10h
	mov n5,bh        ;record the place
	mov n1,ch
	mov n2,cl
	mov n3,dh
	mov n4,dl
repeat1:
	mov ah,2ch       ;use interuption to get the system time
	int 21h
repeat:
	push ax
	push bx
	push dx
	push cx

	mov bh,n5        ;move to there
	mov ah,2h
	mov ch,n1
	mov ch,n2
	mov dh,n3
	mov dl,n4
	int 10h

	pop cx
	pop dx
	pop bx
	pop ax
			 ;print the time
	mov al,ch        ;print hour
	call output

	push dx
	mov dl,':'
	call print2
	pop dx

	mov al,cl        ;print minute
	call output

	push dx
	mov dl,' '
	call print2
	pop dx

	mov al,dh        ;print second
	call output

	push dx
	mov dl,':'
	call print2
	pop dx

	mov al,dl        ;print minisecond
	call output

	push dx
	mov dl,' '
	call print2
	pop dx

	call print1	 ;input a word to choise the funtion.     
			 ;input q for quit
	cmp al,'q'	 ;input c for change
	je exit1	 ;others to refresh the time
	cmp al,'c'
	jne exit0

	mov dl,0ah	 
	call print2
	mov dl,0dh
	call print2

	lea dx,mes3
	call print9

	mov dl,0ah	  
	call print2
	mov dl,0dh
	call print2

	call change	
	jmp repeat
exit0:
	mov ah,2ch
	int 21h
	jmp repeat
exit1:
	ret
main endp

output proc near
	push ax
	push bx
	push cx
	push dx

	cbw		 ;the number pass to here is in ax
	mov bx,10
	xor cx,cx
next1:
	xor dx,dx
	div bx
	add dx,30h
	push dx
	inc cx
	cmp ax,0
	jne next1
next2:
	pop dx
	call print2
	loop next2
	
	pop dx
	pop cx
	pop bx
	pop ax
	
	ret
output endp

change proc near	 ;change the time	
	call deal
	mov ch,al

	call deal
	mov cl,al

	call deal
	mov bh,al

	call deal
	mov dl,al
	mov dh,bh			

	mov ah,2dh
	int 21h

	ret
change endp

print9 proc near
	push ax
	mov ah,09h
	int 21h
	pop ax
	ret
print9 endp

print2 proc near
	push ax
	mov ah,02h
	int 21h
	pop ax
	ret
print2 endp

print1 proc near
	mov ah,07h
	int 21h
	ret
print1 endp
 
deal proc near		 
	lea dx,x	 ;use no.10 interupt to recieve the number
	mov ah,0ah
	int 21h

	mov si,1
	mov bl,x[si]
	inc si
next3:
	sub x[si],30h
	inc si
	dec bl
	jnz next3

	mov si,2
	mov bl,10
	mov al,x[si]
	mul bl
	xor ah,ah
	add al,x[si+1]
	ret
deal endp
code ends
	end start

