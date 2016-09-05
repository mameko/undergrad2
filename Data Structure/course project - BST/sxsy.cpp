//˫��ʵ��
#include <stdio.h>
#include <malloc.h>
#define null 0

#define increase_size 5     //ջ��
#define stack_init_size 100

typedef struct BiTNode//���Ľ��
{
	int data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTtree;

typedef struct/*����ջ������*/
{
   BiTtree * base;
   BiTtree * top;
   int stacksize;
}sqstack;

int n1,n2,n;//n1����ո������n2����������ĸ�ܸ���
int n4;//������סn3��ֵ
int n5;

void init(sqstack &s)/*��ʼ��һ��ջ*/
{
 s.base=(BiTtree *)malloc(stack_init_size*sizeof(BiTtree));
 if(!s.base) printf("error");
 s.top=s.base;
 s.stacksize=stack_init_size;
}

void push(sqstack &s,BiTtree &p0)/*��ջ*/
{
	if(s.top-s.base>stack_init_size)/*�жϿռ乻����*/
	{
		s.base=(BiTtree *)realloc(s.base,sizeof(BiTtree)*(stack_init_size+increase_size));
		if(!s.base)  printf("error");
		s.top=stack_init_size+s.base;
		s.stacksize+=increase_size;
	}
		if(p0!=null)
		s.top=s.top+1;
		*s.top=p0;
}

void pop(sqstack &s,BiTtree &p0)/*��ջ*/
{
	if(s.top==s.base) printf("error");/*��ջ�վ��������*/
	p0=*s.top;
	s.top=s.top-1;
}

void createBiTree1(BiTtree &T)
{
	int c;
	scanf("%d",&c);
	if(c!='@')
	{
		n2++;
	    if(c==0)
		{
			T=null;
			n1++;
		}
		else 
		{
			if(!(T=(BiTNode *)malloc(sizeof(BiTNode)))) printf("error");
			T->data=c;
			createBiTree1(T->lchild);
			createBiTree1(T->rchild);
		}
	}
}

void createBiTree2(BiTtree &T)
{
	T=null;
}

int searchBST1(BiTtree T,int e,BiTtree f,BiTtree &p)//���ݹؼ��ּ�������Ƿ��������
{
    if(!T)
	{
		p=f;
		printf("not exist.\n");
		return 0;
	}
	else 
		if(e==T->data)
		{
			p=T;
			printf("exist.\n");
			return 1;
		}
		else 
			if(e<T->data)
				return	searchBST1(T->lchild,e,T,p);
			else 
				return searchBST1(T->rchild,e,T,p);
}

int searchBST2(BiTtree T,int e,BiTtree f,BiTtree &p)//���ݹؼ��ּ�������Ƿ��������
{
    if(!T)
	{
		p=f;
		printf("not exist.\n");
		return 0;
	}
	else 
		if(e==T->data)
		{
			p=T;
			printf("exist.\n");
			return 1;
		}
		else 
			if(e>T->data)
				return	searchBST2(T->lchild,e,T,p);
			else 
				return searchBST2(T->rchild,e,T,p);
}

void InsertBST1(BiTtree &T,int e)//����һ�����
{
	BiTtree p,s;
	if(!searchBST1(T,e,null,p))
	{
		s=(BiTtree)malloc(sizeof(BiTNode));
		s->data=e;
		s->lchild=s->rchild=null;
		if(!p) T=s;
		else 
			if(e<p->data)
				p->lchild=s;
			else p->rchild=s;
	}
}

void InsertBST2(BiTtree &T,int e)//����һ�����
{
	BiTtree p,s;
	if(!searchBST2(T,e,null,p))
	{
		s=(BiTtree)malloc(sizeof(BiTNode));
		s->data=e;
		s->lchild=s->rchild=null;
		if(!p) T=s;
		else 
			if(e>p->data)
				p->lchild=s;
			else p->rchild=s;
	}
}


			
void InOrderTraverse(BiTtree &T)//�������
{
	if(T)
	{
	    InOrderTraverse(T->lchild);
		if(T->data) printf("%d ",T->data);
		InOrderTraverse(T->rchild);
	}
}

void PreOrderTraverse(BiTtree &T)//�������
{
	if(T)
	{
	    if(T->data) printf("%d ",T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

void PostOrderTraverse(BiTtree &T)//�������
{
	if(T)
	{
	    PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		if(T->data) printf("%d ",T->data);
	}
}

void NDIOT(BiTtree T)
{
	sqstack s;
	BiTtree p0;
	s.base=s.top=null;
	s.stacksize=0;
	init(s);
	p0=T;
	while(p0||!(s.base==s.top))
	{
		if(p0)
		{
			push(s,p0);
			p0=p0->lchild;
		}
		else
		{
			pop(s,p0);
			if(p0->data)  printf("%d ",p0->data);
			p0=p0->rchild;
		}	
	}
}

void deapth(BiTtree T)
{
	int flag,n3;//n3��������ÿ�ε������м���
	flag=1;//������ס��������δ
	if(T)//���ĸ����5��
	{
		n3=n4;//�ѽ���ݹ�ǰ�Ĳ�������n3
		if(T->lchild)
		{
			n3++;//�������
			n4=n3;//��¼����ݹ�ǰ�Ľ�����
			deapth(T->lchild);
			flag=0;//���������
		}

		if(T->rchild)
		{
		if(!T->lchild)	n3++;//�������н������Ͳ��üӼ�
		    n4=n3;
			deapth(T->rchild);
			flag=0;
		}
	}

	if(flag)	
		if(n3>n) n=n3;//������������󣬽�����������ϵ��n��
	
}

void getleafnumber(BiTtree T)//��ӡҶ�ӽ��
{
	if(T)
	{
		if((T->lchild==null)&&(T->rchild==null)) n5++;
		getleafnumber(T->lchild);
		getleafnumber(T->rchild);
	}
}


void getleaf(BiTtree T,int i,int e)//��ӡҶ�ӽ��
{
	if(i==e&&T)
		printf("%d ",T->data);//��Ҷ�ӽ��Ŵ�ӡ
	if(T&&i!=e)//���Ƶݹ����,�ҵ�Ҷ�Ӻ�����ݹ�
	{
		e++;
		getleaf(T->lchild,i,e);
		getleaf(T->rchild,i,e);
	}
}

void leavetraverse(BiTtree T)//��forѭ������ӡÿһ��
{
	int i,e=1;//i�ǲ�����e��ÿһ�ν���ѭ����ʱ��Ѳ�����1
	deapth(T);
	for(i=1;i<=n+1;i++)
		getleaf(T,i,e);
}

void LRChange(BiTtree T)//������������
{
	BiTtree p;
	if(T)
	{
		p=T->rchild;         
		T->rchild=T->lchild;
		T->lchild=p;
		if(T->lchild)
			LRChange(T->lchild);
		if(T->rchild)
			LRChange(T->rchild);
	}
}


void main()
{
	BiTtree s,p;
	int b,a,f,c,d,j=1;
	char u;
//-----------------------------------------------------------------------
	printf("please choose a way to creat a tree:\n");
	printf("1.input the whole bittree\n");
	printf("2.input the node only\n");
	scanf("%d",&c);
	switch(c)
	{
	case 1:
		printf("please input the element:\n");//���루ǰ��
		createBiTree1(s);
		if(n2==2*n1-1)
		{
			printf("the tree have %d null pointors and %d nodes.\n",n1,n2);
			printf("the inordertraverse virsion:\n");//���������
			InOrderTraverse(s);
			printf("\nok\n");
		}
		else printf("error\n");
		break;
	case 2:
		createBiTree2(s);
        k1:	printf("please input node %d:\n",j);
			scanf("%d",&d);
			getchar();
			if(d!=0)
			{
				InsertBST1(s,d);
				j++;
				goto k1;
			}
			else break;
		
	}	
	printf("-----------------------------------------------------------------------\n");
	printf("please choose the funtion you want to use:\n");//������
	printf("-----------------------------------------------------------------------\n");
	printf("1.deapth of the tree\n");
	printf("2.change the tree's left & right child\n");
	printf("3.inordertraverse\n");
	printf("4.preordertraverse\n");
	printf("5.postordertraverse\n");
	printf("6.leavetraverse\n");
	printf("7.inordertraverse(virson 2)\n");
	printf("8.search a node\n");
	printf("9.insert a node\n");
	printf("10.show how many leaf nodes\n");
	printf("-----------------------------------------------------------------------\n");
k:	scanf("%d",&f);
	switch(f)
	{		
//-----------------------------------------------------------------------
	case 1:
		deapth(s);//���
		printf("the tree have %d leavals.\n",n+1);
		break;
//-----------------------------------------------------------------------
	case 2:
		LRChange(s);//������������
		printf("after left right change the inordertraverse:\n");
		InOrderTraverse(s);//�������
		printf("\n");
		break;
//-----------------------------------------------------------------------
	case 3:
		printf("the inordertraverse:\n");
		InOrderTraverse(s);
		printf("\n");
		break;
//-----------------------------------------------------------------------
	case 4:
		printf("the preordertraverse:\n");
		PreOrderTraverse(s);
		printf("\n");
		break;
//-----------------------------------------------------------------------
	case 5:
		printf("the postordertraverse:\n");
		PostOrderTraverse(s);
		printf("\n");
		break;
//-----------------------------------------------------------------------
	case 6:
		printf("the leavetraverse virsion:\n");//��α���
	    leavetraverse(s);
     	printf("\n");
		break;
//-----------------------------------------------------------------------
	case 7:
		printf("another inordertraverse virsion:\n");//�ǵݹ���������
	    NDIOT(s);
    	printf("\n");
		break;
//-----------------------------------------------------------------------
	case 8:
		printf("please input the number you want to search:\n");//��������Ľ��
    	getchar();
    	scanf("%d",&a);
		if((s->data)>(s->lchild->data))	searchBST1(s,a,null,p);
		else searchBST2(s,a,null,p);
		break;
//-----------------------------------------------------------------------
	case 9:
    	printf("please input the number you want to insert:\n");//����һ�����
	    scanf("%d",&b);
		if((s->data)>(s->lchild->data))
			InsertBST1(s,b);
		else InsertBST2(s,b);
    	printf("the inordertraverse virsion:\n");
    	InOrderTraverse(s);//�������
    	printf("\n");
		break;
	
//-----------------------------------------------------------------------
	case 10:
		n5=0;
		getleafnumber(s);
		printf("\nthere are %d leaves nodes in the tree\n",n5);
		break;
//-----------------------------------------------------------------------
	}
	printf("want to quit?(input y or n):\n");
	getchar();
	scanf("%c",&u);
	if(u=='n') 
	{
		printf("\n");
		printf("please choose another function:\n");
		goto k;
	}
	else printf("thank you for using.\n");

}
