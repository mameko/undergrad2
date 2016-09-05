.model small
.stack 100h
.data
	x dw 0
	y dw 2
	z dw ?
	r dw 4
	w dw 10
.code
	
start:
	mov ax,@data
	mov ds,ax

	mov ax,w
	mov bx,x
	sub ax,bx ;w-x
	mov cl,5   
	idiv cl   ;(w-x)/5
	mov bh,ah 
	mov cx,y 
 
    	imul cx   ;(w-x)/5的商*y
	mov cx,ax
	mov al,bh
	mov dx,y
	imul dx   ;(w-x)/5的余数*y
	add ax,cx ;(w-x)/*y
	mov bx,2  ;((w-x)/5*y)*2
	imul bx

	CMP	AX,0;输出内容
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