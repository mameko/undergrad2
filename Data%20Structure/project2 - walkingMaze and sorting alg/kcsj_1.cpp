#include <stdio.h>
#include <malloc.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

#define m1      3
#define radix  10
#define null   0

//-------------------------------------------------------------------
typedef struct//前面几种排序的数据类型
{
	int *elem;
	int length;
	int listsize;
}Sqlist;

//--------------------------------------------------------------------
typedef struct listk//基数排序的数据类型
{
	int key[m1];
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

//--------------------------------------------------------------------

void InitList_Sq(Sqlist &l)
{
	l.elem=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
	if(!l.elem) printf("error");
	l.length=0;
	l.listsize=LIST_INIT_SIZE;
}

void LInput_data(Sqlist &l)//输入数据
{
	int a,i,*newbase;
	printf("how many number you want to input:\n");
	scanf("%d",&a);
	for(i=0;i<a;i++)
	{
		if(l.length>=l.listsize)//空间不够
		{
			newbase=(int *)realloc(l.elem,(l.listsize+LISTINCREMENT)*sizeof(int));
			if(!newbase) printf("error");
			l.elem=newbase;
			l.listsize=l.listsize+LISTINCREMENT;
		}
		scanf("%d",&l.elem[i]);
		l.length++;
	}
}

//*****************************************************************

void InsertSort(Sqlist &l)//直接插入排序
{
	int i,j,*p;
	p=l.elem-1;
	for(i=2;i<=l.length;++i)
		if(p[i]<p[i-1])
		{
			p[0]=p[i];
			p[i]=p[i-1];
			for(j=i-2;p[0]<p[j];--j)
				p[j+1]=p[j];
			p[j+1]=p[0];
		}
}

//*****************************************************************

void Shellinsert(Sqlist &l,int dk)//希尔排序
{
	int i,j,*p;
	p=l.elem-1;
	for(i=dk+1;i<=l.length;++i)
		if(p[i]<p[i-dk])
		{
			p[0]=p[i];
			for(j=i-dk;j>0&&(p[0]<p[j]);j-=dk)
				p[j+dk]=p[j];
			p[j+dk]=p[0];
		}
}

void Shellsort(Sqlist &l,int dlta[],int t)
{
	int k;
	for(k=0;k<t;++k)
		Shellinsert(l,dlta[k]);
}

void Shellprepare(Sqlist l)
{
	int dl[10],k,i;//最多有10个DK
	printf("please input the number of increment:\n");
		scanf("%d",&k);
	printf("input the increment:\n");
	for(i=0;i<k;i++)
		scanf("%d",&dl[i]);
	Shellsort(l,dl,k);
}

//*****************************************************************

void BInsetsort(Sqlist &l)//折半插入排序
{
	int i,j,*p,low,high,m;
	p=l.elem-1;
	for(i=2;i<=l.length;++i)
	{
		p[0]=p[i];
		low=1; high=i-1;
		while(low<=high)
		{
			m=(low+high)/2;
			if(p[0]<p[m]) high=m-1;
			else low=m+1;
		}
	for(j=i-1;j>=high+1;--j) p[j+1]=p[j];
	p[high+1]=p[0];
	}
}

//*****************************************************************

void Bubblesort(Sqlist &l)//冒泡排序
{
	int i,j,*p,t;
	p=l.elem;
	for(i=0;i<l.length;i++)
		for(j=0;j<l.length-1;j++)
			if(p[j]>p[j+1])
			{
				t=p[j];
				p[j]=p[j+1];
				p[j+1]=t;
			}
}

//*****************************************************************

int Partition(Sqlist &l,int low,int high)//快速排序
{
	int *p,pivotkey;
	p=l.elem-1;
	p[0]=p[low];
	pivotkey=p[low];
	while(low<high)
	{
		while(low<high&&p[high]>=pivotkey) --high;
		p[low]=p[high];
		while(low<high&&p[low]<=pivotkey) ++low;
		p[high]=p[low];
	}
	p[low]=p[0];
	return low;
}

void Qsort(Sqlist &l,int low,int high)
{
	int pivotloc;
	if(low<high)
	{
		pivotloc=Partition(l,low,high);
		Qsort(l,low,pivotloc-1);
		Qsort(l,pivotloc+1,high);
	}
}

void Quicksort(Sqlist &l)
{
	Qsort(l,1,l.length);
}

//*****************************************************************

void Selectsort(Sqlist &l)//简单选择排序
{
	int i,j,*p,t,min,d;
	p=l.elem;
	for(j=0;j<l.length;j++)
	{
	    for(i=j;i<l.length;i++)
		{
			min=p[j];
			if(p[i]<min) {min=p[i]; d=i;}
		}
		if(d!=j) 
		{
			t=p[d];
			p[d]=p[j];
			p[j]=t;
		}
	}
}

//*****************************************************************

void Heapadjust(Sqlist &l,int s,int m)//堆排序
{
	int rc,j,*p;
	p=l.elem-1;
	rc=p[s];
	for(j=2*s;j<=m;j*=2)
	{
		if(j<m&&p[j]<p[j+1]) ++j;
		if(rc>=p[j]) break;
		p[s]=p[j]; s=j;
	}
	p[s]=rc;
}

void Heapsort(Sqlist &l)
{
	int i,*p,t;
	p=l.elem-1;
	for(i=l.length/2;i>0;--i)
		Heapadjust(l,i,l.length);
	for(i=l.length;i>1;--i)
	{
		t=p[1];
		p[1]=p[i];
		p[i]=t;
		Heapadjust(l,1,i-1);
	}
}

//*****************************************************************

void Merge(Sqlist R,int low,int m,int high)//归并排序
{//将两个有序的子文件R[low..m)和R[m+1..high]归并成一个有序的子文件R[low..high]
	int i=low,j=m+1,p=0;  //置初始值
    int *R1,*q;//自己设置的结构
	q=R.elem-1;
	R1=(int *)malloc((high-low+1)*sizeof(int));//R1是局部向量，若p定义为此类型指针速度更快
	if(! R1) //申请空间失败
		printf("error\n");
	while(i<=m&&j<=high) //归并
		R1[p++]=(q[i]<=q[j]?q[i++]:q[j++]);
	while(i<=m)//把剩下的也归并
		R1[p++]=q[i++];
	while(j<=high)//把剩下的也归并
		R1[p++]=q[j++];
	for(p=0,i=low;i<=high;p++,i++)//归并完成后将结果复制回R[low..high]
		q[i]=R1[p];
} 

void MergeSortDC(Sqlist R,int low,int high)
{//用分治法对R[low..high]进行二路归并排序
	int mid;
	if(low<high)//区间长度大于1
   {
		mid=(low+high)/2; //分解
        MergeSortDC(R,low,mid); //递归地对R[low..mid]排序
        MergeSortDC(R,mid+1,high);//递归地对R[mid+1..high]排序
		Merge(R,low,mid,high);//组合，将两个有序区归并为一个有序区
	}
}

//*****************************************************************

void InitQueue(LinkQueue &Q)//基数排序
{
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) printf("error");
	Q.front->next=null;
}

LinkQueue Enqueue(LinkQueue &Q,listk e)//入队
{
	QNode *p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) printf("error enqueue");
	p->data=e; p->next=null;
	Q.rear->next=p;
	Q.rear=p;
	return Q;
}

LinkQueue DeQueue(LinkQueue &Q,listk &e)//出队
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

int Qempty(LinkQueue Q)//判断队列是否空
{
	if(Q.front==Q.rear) return 1;
	else return 0;
}

void distribute(listk *l,int i,LinkQueue keys[radix])//分配
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

void collect(listk *&l,LinkQueue keys[radix])//收集
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
				d=m1;
			for(j=d-1;j>=0;j--)
			  p->key[j]=e.key[j];
			p=p->next;
		}
	}
}

listk * radixsort(listk * l)//基数排序
{
	LinkQueue Q,keys[radix];
	int i,d;
	for(i=0;i<radix;i++)
	{
		InitQueue(Q);
		keys[i]=Q;
	}
	d=m1;
	for(i=d-1;i>=0;i--)
	{
		distribute(l,i,keys);
		collect(l,keys);
	}
	return l;
}

struct listk * input()//输入数据
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
		for(j=0;j<m1;j++)
			scanf("%d",&p->key[j]);
		q->next=p;
		q=q->next;
	}
	p->next=null;
  	return l;
}

void print1(listk *l)//打印函数2
{
	listk *p;
	int i;
	p=l;
	while(p->next)
	{
		p=p->next;
		for(i=0;i<m1;i++)
			printf("%d",p->key[i]);
		printf(" ");
		
	}
}

//*****************************************************************

void print(Sqlist l)
{
	int *p,i;
	p=l.elem;
	for(i=0;i<l.length;i++)
		printf("%d ",*(p+i));
	printf("\n");
}
                                                          
	
void main()
{
//	Sqlist l;
//	InitList_Sq(l);
//	LInput_data(l);
//	print(l);
//	printf("\n");
//	MergeSortDC(l,1,l.length);
//	print(l);

	struct listk * l;
	l=input();
	printf("\n");
	l=radixsort(l);
	print1(l);
}
