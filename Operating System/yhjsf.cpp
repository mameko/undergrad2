#include <stdio.h>
#include <malloc.h>
#include <time.h> 
#include <stdlib.h>

#define NULL 0

int n,complete,v,a[11];
int available[10];
struct node * head;
struct cnum * chead;


struct node
{
	int max[11];
	int work[10];
	int need[10];
	int request[10];
	int allocation[10];
	struct node * next;
};

struct cnum
{
	int data;
	struct cnum * next;
};

void init(int available[])
{
	int i;
	for(i=0;i<10;i++)
		available[i]=10;
}

void ran1(int k[])
{
	int i;
	srand((unsigned)time(NULL));
	for(i=0;i<10;i++)
		a[i]=rand()%10+1;
}


//int ran1()
//{
//	int i;
//	srand((unsigned)time(NULL));
//	i=rand()%10+1;
//	return i;
//}


node * make_pi(struct node * head)//创建pi进程
{
	struct node * pi;
//	int i,randnum1,randnum2;
	int i,b[11];

	pi=(node *)malloc(sizeof(node));
/*	for(i=0;i<10;i++)
	{
		randnum1=ran1()%a[0];//随机生成最大需求
		pi->max[i]=randnum1;
		randnum2=ran1()%a[1];//随机生成系统分配
		
		if(randnum2>=pi->max[i])
		{
			if(available[i]-pi->max[i]>=0)
			{
				pi->allocation[i]=pi->max[i];
				available[i]=available[i]-pi->allocation[i];
			}
			else
				pi->allocation[i]=0;
		}
		else
		{
			if(available[i]-randnum2>=0)
			{
				pi->allocation[i]=randnum2;
				available[i]=available[i]-pi->allocation[i];
			}
			else
				pi->allocation[i]=0;
		}
	
		pi->need[i]=pi->max[i]-pi->allocation[i];
	}
*/
	ran1(a);//随机生成最大需求
	for(i=0;i<10;i++)
		pi->max[i]=a[i];
	ran1(a);//随机生成系统分配
	for(i=0;i<10;i++)
		b[i]=a[i];
	for(i=0;i<10;i++)
	{
		if(b[i]>pi->max[i])
		{
			if(available[i]-pi->max[i]>=0)
			{
				pi->allocation[i]=pi->max[i];
				available[i]=available[i]-pi->allocation[i];
			}
			else
				pi->allocation[i]=0;
		}
		else
		{
			if(available[i]-b[i]>=0)
			{
				pi->allocation[i]=b[i];
				available[i]=available[i]-pi->allocation[i];
			}
			else
				pi->allocation[i]=0;
		}
	
		pi->need[i]=pi->max[i]-pi->allocation[i];
	}


	pi->next=head->next;
	head->next=pi;
	n=n+1;
	return head;
}

int N_A(struct node * k)//如果need<=available就分比个进程然后收翻D资源
{
	struct node * pi;
	int i;
	pi=k;
	for(i=0;i<10;i++) 
	{	
		if(pi->need[i]>available[i])
			return 0;
	}
	return 1;
}

int save_or_not(struct node * head)//安全性
{
	struct node * pi;
	int i,j;
	
	pi=head->next;
	for(i=0;i<n;i++)
	{
		pi->max[10]=0;//0=flase
		pi=pi->next;
	}

	pi=head->next;//work=available
	for(i=0;i<n;i++)
	{
		for(j=0;j<10;j++)
			pi->work[j]=available[j];
		pi=pi->next;
	}
	
	pi=head->next;//判断false会5会变ture
	for(i=0;i<n;i++)
	{
		if(pi->max[10]==0&&N_A(pi))
		{
			for(j=0;j<10;j++)
				pi->work[j]=pi->work[j]+pi->allocation[j];
			pi->max[10]=1;
		}
		pi=pi->next;
	}

	pi=head->next;
	for(i=0;i<n;i++)
	{
		if(pi->max[10]!=1)
			return 0;
		pi=pi->next;
	}
	return 1;
}

struct node * pirequest(struct node * head,int k)//真系请求
{
//	int i,randnum;
	int i;//,s[11];
	struct node * pi;
	pi=head->next;
	for(i=0;i<n-k;i++)
		pi=pi->next;
//	for(i=0;i<10;i++)
//	{
//		randnum=ran1()%a[3];//随机生成请求
//		if(randnum>=pi->need[i])
//			pi->request[i]=pi->need[i];
//		else
//			pi->request[i]=randnum;
//	}
	ran1(a);
//	for(i=0;i<10;i++)
//		s[i]=a[i];
	for(i=0;i<10;i++)
	{
		if(a[i]>=pi->need[i])
			pi->request[i]=pi->need[i];
		else
			pi->request[i]=a[i];
	}
	return head;
}

int R_A(struct node * k)//request<=available
{
	int i;
	struct node * pi;
	pi=k;
	for(i=0;i<10;i++)
	{
		if(pi->request[i]>available[i]) 
			return 1;
	}
	return 0;
}

int R_N(struct node * k)//request>need
{
	int i;
	struct node * pi;
	pi=k;
	for(i=0;i<10;i++)
	{
		if(pi->request[i]>pi->need[i]) 
			return 1;
	}
	return 0;
}

int pirequire(struct node * &head,int t)//请求资源看如果请求合法就进入安全性算法
{
	struct node * pi;
	int i;
	pi=head->next;
	for(i=0;i<n-t;i++)
		pi=pi->next;//把指针移到t结点
	head=pirequest(head,t);
	if(R_N(pi)) 
		return 0;//请求错误
	else 
		if(R_A(pi))
			return 1;//请求不能被满足，所以等待
		else 
		{
			for(i=0;i<10;i++)
			{
				available[i]=available[i]-pi->request[i];
				pi->allocation[i]=pi->allocation[i]+pi->request[i];
				pi->need[i]=pi->need[i]-pi->request[i];
			}
			return 2;//进入安全性算法
		}
}

void print_process(struct node * head)
{
	int no,i,j;
	struct node *pi;
	no=n;
	if(head->next)
	{
	pi=head->next;
	printf("\nthe process max matrix :\n");
	printf("    A  B  C  D  E  F  G  H  I  J\n\n");
	for(i=0;i<n;i++)
	{
		printf("p%d  ",no-i);
		for(j=0;j<10;j++)
			printf("%d  ",pi->max[j]);
		printf("\n\n");
			if(pi->next!=NULL)
			pi=pi->next;
	}
	}	
}

void re_require(struct node * head,int c)
{
	struct node * pi;
	int i;
	pi=head->next;
	for(i=0;i<n-c;i++)
		pi=pi->next;
	for(i=0;i<10;i++)
	{
		available[i]=available[i]+pi->request[i];
		pi->allocation[i]=pi->allocation[i]-pi->request[i];
		pi->need[i]=pi->need[i]+pi->request[i];
	}
}

void print_allocation(struct node * head)
{
	int no,i,j;
	struct node *pi;
	no=n;
	if(head->next)
	{
		pi=head->next;
		printf("\nthe allocation matrix :\n");
		printf("    A  B  C  D  E  F  G  H  I  J\n\n");
		for(i=0;i<n;i++)
		{
			printf("p%d  ",no-i);
			for(j=0;j<10;j++)
				printf("%d  ",pi->allocation[j]);
			printf("\n\n");
		}
	}
}

int wait(struct cnum * &chead,struct node * head,int o)
{
	int d,c;
	struct cnum * ci;
	v++;
	c=o;
	ci=(cnum *)malloc(sizeof(cnum));
	ci->data=c;
	ci->next=chead->next;
	chead->next=ci;
	if(complete!=0)
	{
		c=ci->data;
		complete--;
W:		d=pirequire(head,ci->data);
		if(d==0) printf("request error\n");
		if(d==1) 
		{
			if(ci->next)
			{
				ci=ci->next;
				goto W;
			}
			else 
				return 0;
		}
		if(d==2) 
		{
			v--;
			c=ci->data;
			return 1;
		}
	}
	else
		return 2;
}

int A_M(struct node * k)//allocation=max就结束
{
	struct node * pi;
	int i;
	pi=k;
	for(i=0;i<10;i++) 
	{	
		if(pi->max[i]!=pi->allocation[i])
			return 0;
	}
	return 1;
}

struct node * pi_end(struct node * head)
{
	struct node * pi,*qi;
	int i,j,no;
	no=n;
	qi=head;
	pi=qi->next;
	for(j=0;j<no;j++)
	{
		if(A_M(pi))
		{
			printf("process %d is over\n",no-j);
			qi->next=pi->next;
			for(i=0;i<10;i++)
				available[i]=available[i]+pi->max[i];
			complete++;
			n=n-1;
			free(pi);
			pi=qi->next;
		}
			else
			{
				pi=pi->next;
				qi=qi->next;
			}
	}
	return head;
}

void main()
{
	int a,b,c,d,e/*,i*/,u;
	chead=(cnum *)malloc(sizeof(cnum));
	chead->next=NULL;
	head=(node *)malloc(sizeof(node));
	head->next=NULL;
//	ran2();
	init(available);

L:  printf("1.add a process\n2.process pi request\n3.exit\n");
	scanf("%d",&a);
	switch(a)
	{
	case 1:
		{
		//	printf("how many process you want to add?\n");
		//	scanf("%d",&b);
		//	for(i=0;i<b;i++)
l:			head=make_pi(head);
			printf("want to make more? Y/N(1/0)\n");
			scanf("%d",&b);
			if(b==1) goto l;
			print_process(head);
		}
		goto L;
	case 2:
		{
			printf("please input which process request for resources\n");
			scanf("%d",&c);
			d = pirequire(head,c);
			if(d==0) printf("request error * \n");
			if(d==1) 
			{
				printf("there are not enough resourse now\n");
				pi_end(head);
				u=wait(chead,head,c);
				if(u==1) goto D2;
				else goto L;
			}
D2:			if(d==2)
			{
				e=save_or_not(head);
				if(e==0)
				{
					printf("The system isn't safe\n");
					re_require(head,c);
				}
				else 
				{
					printf("The system is safe\n");	
				}
				pi_end(head);
				print_allocation(head);
				goto L;
			}
		}
		goto L;
	case 3:
		{
			printf("thank you for using\n");
			break;
		}
	}
}
				
