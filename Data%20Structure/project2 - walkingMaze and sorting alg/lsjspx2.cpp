#include <stdio.h>
#include <malloc.h>

#define m      3
#define radix  10
#define null   0

typedef struct listk
{
	int key[m];
	struct listk *next;
}listk;

typedef struct QNode
{
	listk data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

void InitQueue(LinkQueue &Q)
{
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) printf("error");
	Q.front->next=null;
}

LinkQueue Enqueue(LinkQueue &Q,listk e)
{
	QNode *p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) printf("error enqueue");
	p->data=e; p->next=null;
	Q.rear->next=p;
	Q.rear=p;
	return Q;
}

LinkQueue DeQueue(LinkQueue &Q,listk &e)
{
	QNode *p;
	if(Q.front==Q.rear) printf("error dequeue");
	p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p) Q.rear=Q.front;
	free(p);
	return Q;
}

int Qempty(LinkQueue Q)
{
	if(Q.front==Q.rear) return 1;
	else return 0;
}

void distribute(listk *l,int i,LinkQueue keys[radix])
{
	int j;
	listk *p;
	LinkQueue Q;
	p=l->next;
	do
	{
		j=p->key[i];	
		Q=keys[j];
		keys[j]=Enqueue(Q,*p);
		p=p->next;
	}while(p!=null);
}

void collect(listk *&l,LinkQueue keys[radix])
{
	listk e,*p;
	LinkQueue Qq;
	int i,j,d;
	p=l->next;
	for(i=0;i<radix;i++)
	{
		Qq=keys[i];
		while(!Qempty(Qq))
		{
			keys[i]=DeQueue(Qq,e);
				d=m;
			for(j=d-1;j>=0;j--)
			  p->key[j]=e.key[j];
			p=p->next;
		}
	}
}

listk * radixsort(listk * l)
{
	LinkQueue Q,keys[radix];
	int i,d;
	for(i=0;i<radix;i++)
	{
		InitQueue(Q);
		keys[i]=Q;
	}
	d=m;
	for(i=d-1;i>=0;i--)
	{
		distribute(l,i,keys);
		collect(l,keys);
	}
	return l;
}

struct listk * input()
{
	int a,i,j;
	listk *p,*l,*q;
	printf("input how many number do you want to sort:\n");
	scanf("%d",&a);
	l=(listk *)malloc(sizeof(listk));
	q=l;
	for(i=0;i<a;i++)
	{
			
		p=(listk *)malloc(sizeof(listk));
		printf("please input the %d number \n",i+1);
		for(j=0;j<m;j++)
			scanf("%d",&p->key[j]);
		q->next=p;
		q=q->next;
	}
	p->next=null;
  	return l;
}

void print(listk *l)
{
	listk *p;
	int i;
	p=l;
	while(p->next)
	{
		p=p->next;
		for(i=0;i<m;i++)
			printf("%d",p->key[i]);
		printf(" ");
		
	}
}

void main()
{
	struct listk * l;
	l=input();
	printf("\n");
	l=radixsort(l);
	print1(l);
}