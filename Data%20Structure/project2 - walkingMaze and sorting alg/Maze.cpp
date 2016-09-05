#include "stdio.h"
#include "malloc.h"
#include "stdarg.h"

#define Elemtype Maze
#define elemtype curpose
#define Null 0
#define MAX_BOUND 100
#define MAX_ARRAY_DIM 8

typedef struct
{
	int east;
	int south;
	int west;
	int north;
	int flag;
	char data;
}Maze;

typedef struct
{
	int a;
	int b;
}curpose;

typedef struct
{
	Elemtype *base;
	int dim;
	int *bounds;
	int *constants;
}Array;

typedef struct/*定义栈*/
{
 struct nude1 *top;
 struct nude1 *base;
}stack1;

struct nude1/*定义栈中结点的类型*/
{
	Elemtype data;
	struct nude1 * next;
};

typedef struct/*定义栈*/
{
 struct nude2 *top;
 struct nude2 *base;
}stack2;

struct nude2/*定义栈中结点的类型*/
{
	elemtype data;
	struct nude2 * next;
};

//-----------------------------------------------------------------------------------------------
//array
void InitArray(Array &A,int dim,int l,int w)
{
	va_list ap;
	int i,elemtotal;
	if(dim<1||dim>MAX_ARRAY_DIM) printf("error1");
	A.dim=dim;
	A.bounds=(int *)malloc(dim * sizeof(int));
	if(!A.bounds) printf("error2");
	elemtotal=1;

	va_start(ap,dim);
	for(i=0;i<dim;++i)
	{
		A.bounds[i]=va_arg(ap,int);
		if(A.bounds[i]<0) printf("error3");
		elemtotal = A.bounds[i]*elemtotal;
	}
	va_end(ap);

	A.base=(Elemtype *)malloc(elemtotal*sizeof(Elemtype));
	if(!A.base) printf("error4");
	A.constants=(int *)malloc(dim* sizeof(int));
	if(!A.constants) printf("error5");
	A.constants[dim-1]=1;
	for(i=dim-2;i>=0;--i)
		A.constants[i]=A.bounds[i+1]*A.constants[i+1];
	printf("ok1\n");
}

int Locate(Array A,va_list ap,int &off)
{
	int ind,i;
	off=0;
	for(i=0;i<A.dim;++i)
	{
		ind=va_arg(ap,int);
		if(ind<0||ind>=A.bounds[i]) {printf("error6\n");return 0;}
		off = A.constants[i] * ind + off;
	}
	return 1;
}

void Assign(Array &A,Elemtype e,int l,int w)
{
	int result,off;
	va_list ap;
	va_start(ap,e);
	if((result=Locate(A,ap,off))<=0) printf("error7");
	* (A.base + off) = e;
}

void Value(Array A,Elemtype &e,int l,int w)
{
	int result,off;
	va_list ap;
	va_start(ap,e);
	if((result=Locate(A,ap,off))<=0) printf("error9\n");
	e = * (A.base+off);
}
//-----------------------------------------------------------------------------------------------
//stack1
stack1 InitStack1(stack1 &s)/*初始化栈*/
{
	stack1 *p;
	p=(stack1 *)malloc(sizeof(stack1));
	s=*p;
	s.top=s.base=Null;
	return s;
}

stack1 push1(stack1 &s,Elemtype &e)/*入栈*/
{
	struct nude1 *p;
	p=(struct nude1 *)malloc(sizeof(struct nude1));
	e = p->data;
	p->next=s.top;
	s.top=p;
	return s;
}

void Pop1(stack1 &s,Elemtype &e)/*出栈*/
{
	struct nude1 *q,*p;
	q=s.top;
	p=q->next;
	s.top=p;
	e=q->data;
	free(q);
}

int StackEmpty1(stack1 s)
{
	if(s.base==s.top) return 1;
	else return 0;
}
//-----------------------------------------------------------------------------------------------
//stack2
stack2 InitStack2(stack2 &s)/*初始化栈*/
{
	stack2 *p;
	p=(stack2 *)malloc(sizeof(stack2));
	s=*p;
	s.top=s.base=Null;
	return s;
}

stack2 push2(stack2 &s,elemtype &e)/*入栈*/
{
	struct nude2 * p;
	p=(struct nude2 *)malloc(sizeof(struct nude2));
	e = p->data;
	p->next=s.top;
	s.top=p;
	return s;
}

void Pop2(stack2 &s,elemtype &e)/*出栈*/
{
	struct nude2 *p,*q;
	q=s.top;
	p=q->next;
	e=q->data;
	s.top=p;
	free(q);
}

int StackEmpty2(stack2 s)
{
	if(s.base==s.top) return 1;
	else return 0;
}

//-----------------------------------------------------------------------------------------------
//maze
void InputMaze(Array &A,int l,int w)//输入迷宫的元素
{
	int i,j;
	Elemtype e;
	for(i=0;i<l;i++)
		for(j=0;j<w;j++)
		{
			scanf("%c",&e.data);
			getchar();
			if(e.data=='1')
			{
				e.south=1;
				e.north=1;
				e.west=1;
				e.east=1;
			}
			else
			{
				e.south=0;
				e.north=0;
				e.west=0;
				e.east=0;
			}
			e.flag=0;
			Assign(A,e,i,j);
		}
}

void InitMaze(Array &A,int l,int w)//加边
{
	int i,j;
	Elemtype e;
	for(i=0;i<l;i++)//左边个边
	{
		Value(A,e,i,0);
		e.west=1;
		Assign(A,e,i,0);
	}
	for(j=0;j<w;j++)//下边个边
	{
		Value(A,e,l-1,j);
		e.south=1;
		Assign(A,e,l-1,j);
	}
	for(j=0;j<w;j++)//上边个边
	{
		Value(A,e,l-1,j);
		e.north=1;
		Assign(A,e,0,j);
	}
	for(i=0;i<l;i++)//右边个边
	{
		Value(A,e,l-1,j);
		e.east=1;
		Assign(A,e,i,w-1);
	}
}

int Pass(Array A,int a,int b)
{
	Elemtype e;
	Value(A,e,a,b);
	if(e.flag==1) return 0;
	else return 1;
}

void FootPrint(Array &A,int a,int b)
{
	Elemtype e;
	Value(A,e,a,b);
	e.flag=1;
	Assign(A,e,a,b);
}

int set(Array A,int &a,int &b)
{
	Elemtype e;
	Value(A,e,a,b);
	if(e.east==0) 
	{
		e.east=1;
		Assign(A,e,a,b);
		return 1;
	}
	else
		if(e.south==0)
		{
			e.south=1;
			Assign(A,e,a,b);
			return 2;
		}
		else 
			if(e.west==0)
			{
				e.west=1;
				Assign(A,e,a,b);
				return 3;
			}
			else 
				if(e.north==0)
				{
					e.north=1;
					Assign(A,e,a,b);
					return 4;
				}
				else return 0;
}

void Nextpose(Array &A,int &a,int &b)
{
	int k;
	k=set(A,a,b);
	switch(k)
	{
	case 1: b=b+1;break;
	case 2: a=a+1;break;
	case 3: b=b-1;break;
	case 4: a=a-1;break;
	}
}

int Full(Elemtype e)
{
	if(e.east==1&&e.south==1&&e.north==1&&e.west==1)
		return 1;
	else return 0;
}

void MazePath(Array A,int sl,int sw,int el,int ew,stack1 &s1,stack2 &s2)
{
	curpose cur,e1;
	Elemtype e;
	InitStack1(s1);
	InitStack2(s2);
	cur.a=sl;
	cur.b=sw;
	do
	{
		if(Pass(A,cur.a,cur.b))
		{
			FootPrint(A,cur.a,cur.b);
			Value(A,e,cur.a,cur.b);
			set(A,cur.a,cur.b);
			push1(s1,e);
			push2(s2,cur);
			if(cur.a==el&&cur.b==ew) {printf("ok\n"); break;}
		}
		else
		{
			if(!StackEmpty1(s1))
			{
				Pop1(s1,e);
				Pop2(s2,e1);
				while(Full(e)&&!StackEmpty1(s1))
				{Pop1(s1,e); Pop2(s2,e1);}
				if(!Full(e))
					Nextpose(A,cur.a,cur.b);
			}
		}
	}while(!StackEmpty1(s1));
}

void print(Array &A,stack1 &s1,stack2 &s2,int l,int w)
{
	Elemtype e;
	elemtype e1;
	int i,j;
	do
	{
		Pop1(s1,e);
		Pop2(s2,e1);
		e.data='*';
		Assign(A,e,e1.a,e1.b);
	}while(!StackEmpty1(s1));

	for(i=0;i<l;i++)
		for(j=0;j<w;j++)
		{
			Value(A,e,i,j);
			printf("%c ",e.data);
		}
		printf("\n");
}

void main()
{
	Array A;
	Elemtype e;
	int a,b;
	int sl,sw,el,ew;
	stack1 s1;
	stack2 s2;
	scanf("%d %d",&a,&b);
	getchar();
	InitArray(A,2,a,b);
	InputMaze(A,a,b);
	Value(A,e,0,1);
	InitMaze(A,a,b);
	scanf("%d %d",&sl,&sw);
	scanf("%d %d",&el,&ew);
	MazePath(A,sl,sw,el,ew,s1,s2);
	print(A,s1,s2,a,b);
}