#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>
#define Elmetype int

#define MAX_BOUND 100
#define MAX_ARRAY_DIM 8
typedef struct
{ 
	Elmetype *base;
	int dim;
	int *bounds;
	int *constants;
}Array;

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

	A.base=(Elmetype *)malloc(elemtotal*sizeof(Elmetype));
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

void Assign(Array &A,Elmetype e,int l,int w)
{
	int off;
	va_list ap;
	va_start(ap,e);
	if(Locate(A,ap,off)<=0) printf("error7");
	* (A.base + off)=e;
}

void Value(Array A,Elmetype &e,int l,int w)
{
	int off;
	va_list ap;
	va_start(ap,e);
	if(Locate(A,ap,off)<=0) printf("error9\n");
	e = * (A.base+off);
}

void print(Array A,int l,int w)
{
	int j,i,e=0;
	for(i=0;i<l;i++)
	{
		for(j=0;j<w;j++)
		{
			Value(A,e,i,j);
			printf("%d ",e);
		}
			printf("\n");
	}
}

void input(Array &A,int l,int w)
{
	int e,i,j;
	for(i=0;i<l;i++)
		for(j=0;j<w;j++)
		{
			printf("please input one element:\n");
			scanf("%d",&e);
			Assign(A,e,i,j);
		}
}

void main()
{
	Array a;
	int w,l,d;
	printf("please input length & width\n");
	scanf("%d %d",&l,&w);
	printf("please input the dim\n");
	scanf("%d",&d);
	InitArray(a,d,l,w);
	input(a,l,w);
	print(a,l,w);
}
