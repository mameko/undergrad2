#include "stdio.h"
#include "malloc.h"

#define Null 0

extern Maze A;

#define Elemtype Maze

typedef struct/*定义栈*/
{
 struct nude *top;
 struct nude *base;
}stack;

struct nude/*定义栈中结点的类型*/
{
	Elemtype data;
	struct nude * next;
};

stack InitStack()/*初始化栈*/
{
	stack *p;
	stack s;
	p=(stack *)malloc(sizeof(stack));
	s=*p;
	s.top=s.base=Null;
	return s;
}

stack push(stack s,Elemtype &e)/*入栈*/
{
	struct nude * p;
	p=(struct nude *)malloc(sizeof(struct nude));
	e = p->data;
	p->next=s.top;
	s.top=p;
	return s;
}

Elemtype Pop(stack s)/*出栈*/
{
	struct nude *p,*q;
	Elemtype e;
	q=*(s.top);
	p=q->next;
	e=*q;
	s.top=p;
	free(q);
	return e;
}

int StackEmpty(linkstack s)
{
	if(s.base==s.top) return 1;
	else return 0;
}

