//用三元组表存储稀疏矩阵的快速转置算法
#include <stdio.h>
#define MAXSIZE 150

typedef struct
{
	int i,j,e;
}triple;

typedef struct
{
	triple data[MAXSIZE+1];
	int mu,nu,tu;
}TSMatrix;

void FTSMatrix(TSMatrix m,TSMatrix &t)
{
	int k,col,p,q;
	int cpot[30];
	int num[30];
    t.mu=m.mu;  
	t.nu=m.mu;  
	t.tu=m.tu;
	if(t.tu)
	{
		for(col=1;col<=m.nu;++col) num[col]=0;
		for(k=1;k<=m.tu;++k)  ++num[m.data[k].j];
		cpot[1]=1;
		for(col=2;col<=m.nu;++col) cpot[col]=cpot[col-1]+num[col-1];
		for(p=1;p<=m.tu;++p)
		{
			col=m.data[p].j;
			q=cpot[col];
			t.data[q].i=m.data[p].j;
			t.data[q].j=m.data[p].i;
			t.data[q].e=m.data[p].e;
			++cpot[col];
		}
	}
}

void init_matrix(TSMatrix &d)
{
	int a,b,i,c,g,f;
	printf("please input howmany rows,columns in the array:\n");
	scanf("%d,%d",&a,&b);
    d.mu=a;d.nu=b;
	printf("please input the nonzero numbers row,columne,value:\n");
//	scanf("%d,%d,%d",&d.data[1].i,&d.data[1].j,&d.data[1].e);
	for(i=1;i<=MAXSIZE;i++)
	{
	    //scanf("%d",&d.data[i].e);
		scanf("%d %d %d",&c,&g,&f);
		if(c!=0)  
		{
			d.data[i].i=c;
        	d.data[i].j=g;
			d.data[i].e=f;
		}
		else break;
	}
	d.tu=i-1;
}

void print(TSMatrix k)
{
	int r;
	printf("\n*********************************\n");
    for(r=1;r<=k.tu;r++)
		printf("%8d%8d%8d\n",k.data[r].i,k.data[r].j,k.data[r].e);
	printf("\n*********************************\n");
	printf("The matrix has %d rows and %d columns and %d nonzero elements\n",k.mu,k.nu,k.tu);
}

void main()
{
	TSMatrix M,T;
	init_matrix(M);
	print(M);
	FTSMatrix(M,T);
	print(T);
}

