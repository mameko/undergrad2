#include <stdio.h>
#include <malloc.h>
#define Maxsize 100

//ѭ�����е���Ӻͳ���

typedef struct 
{
	int * base;
	int front;
	int rear;
}sqQueue;

void init(sqQueue &Q)//��ʼ������
{
	Q.base=(int *)malloc(100*sizeof(int));
    if(!Q.base)
		printf("error");
	else
		Q.front=Q.rear=0;
}

int Queuelenth(sqQueue Q)//���г���
{
	return (Q.rear-Q.front+Maxsize)%Maxsize;
}

void enQueue(sqQueue &Q,int e)//���
{
	if((Q.rear+1)%Maxsize==Q.front)
		printf("error");

	else
	{
		Q.base[Q.rear]=e;
		Q.rear=(Q.rear+1)%Maxsize;
	}
}

void deQueue(sqQueue &Q,int e)//����
{
	if(Q.front==Q.rear)
		printf("error");
	else
	{
		e=Q.base[Q.front];
		Q.front=(Q.front+1)%Maxsize;
	}
}

void main()
{
	sqQueue Q;
	int a,b,c,l=0,i;
	init(Q);
	printf("please input howmany number you want in the Queue:\n");
	scanf("%d",&a);
	for(i=0;i<a;i++)
	{
		printf("input the number you want to insert:\n");
		scanf("%d",&b);
		enQueue(Q,b);
	}
	printf("input the number your want to delete in the Queue:\n");
	scanf("%d",&c);
	deQueue(Q,c);
    l=Queuelenth(Q);
	printf("the Queue has %d numbers:\n",l);
}
