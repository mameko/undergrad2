.model small
.stack 100h
.data               ;定义变量
	x dw 1
	y dw 2
	z dw ?
	r dw 4
	w dw 0
.code
	
start:
	mov ax,@data
	mov ds,ax

	mov ax,r	
	add ax,9
	mov bx,ax
	mov ax,x
	add ax,6
	mov cx,ax
	mov ax,w
	sub ax,bx
	sub ax,cx
	mov z,ax

	;mov bx,z

	;mov dl,bh
	;mov ah,2
	;int 21h

	;mov dl,bl
	;mov ah,2
	;int 21h
                        ；输出内容
	CMP	AX,0
	JGE	K1
	NEG	AX
	PUSH	AX
	MOV	DL,'-'
	MOV	AH,2
	INT	21H
	POP	AX
K1:	MOV	CX,0
K2:	MOV	DX,0
	MOV	BX,10
	DIV	BX
	PUSH	DX
	INC	CX
	CMP	AX,0
	JZ	K3
	JMP	K2
K3:	POP	DX
	ADD	DL,30H
	MOV	AH,2
	INT	21H
	LOOP	K3
	
	mov ah,4ch
	int 21h
end start
	