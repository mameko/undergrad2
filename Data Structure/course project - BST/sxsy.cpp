//双性实验
#include <stdio.h>
#include <malloc.h>
#define null 0

#define increase_size 5     //栈的
#define stack_init_size 100

typedef struct BiTNode//树的结点
{
	int data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTtree;

typedef struct/*定义栈的类型*/
{
   BiTtree * base;
   BiTtree * top;
   int stacksize;
}sqstack;

int n1,n2,n;//n1计算空格个数，n2计算输入字母总个数
int n4;//用来记住n3的值
int n5;

void init(sqstack &s)/*初始化一个栈*/
{
 s.base=(BiTtree *)malloc(stack_init_size*sizeof(BiTtree));
 if(!s.base) printf("error");
 s.top=s.base;
 s.stacksize=stack_init_size;
}

void push(sqstack &s,BiTtree &p0)/*入栈*/
{
	if(s.top-s.base>stack_init_size)/*判断空间够不够*/
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

void pop(sqstack &s,BiTtree &p0)/*出栈*/
{
	if(s.top==s.base) printf("error");/*若栈空就输出错误*/
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

int searchBST1(BiTtree T,int e,BiTtree f,BiTtree &p)//根据关键字检查树中是否有这个字
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

int searchBST2(BiTtree T,int e,BiTtree f,BiTtree &p)//根据关键字检查树中是否有这个字
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

void InsertBST1(BiTtree &T,int e)//插入一个结点
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

void InsertBST2(BiTtree &T,int e)//插入一个结点
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


			
void InOrderTraverse(BiTtree &T)//中序遍历
{
	if(T)
	{
	    InOrderTraverse(T->lchild);
		if(T->data) printf("%d ",T->data);
		InOrderTraverse(T->rchild);
	}
}

void PreOrderTraverse(BiTtree &T)//先序遍历
{
	if(T)
	{
	    if(T->data) printf("%d ",T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

void PostOrderTraverse(BiTtree &T)//后序遍历
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
	int flag,n3;//n3用来计算每次单边树有几层
	flag=1;//用来记住个边树完未
	if(T)//树的根结点5空
	{
		n3=n4;//把进入递归前的层数附给n3
		if(T->lchild)
		{
			n3++;//计算层数
			n4=n3;//记录进入递归前的结点层数
			deapth(T->lchild);
			flag=0;//这边树完啦
		}

		if(T->rchild)
		{
		if(!T->lchild)	n3++;//如果左边有结点层数就不用加加
		    n4=n3;
			deapth(T->rchild);
			flag=0;
		}
	}

	if(flag)	
		if(n3>n) n=n3;//如果个边树完左，将个最大层数摆系个n度
	
}

void getleafnumber(BiTtree T)//打印叶子结点
{
	if(T)
	{
		if((T->lchild==null)&&(T->rchild==null)) n5++;
		getleafnumber(T->lchild);
		getleafnumber(T->rchild);
	}
}


void getleaf(BiTtree T,int i,int e)//打印叶子结点
{
	if(i==e&&T)
		printf("%d ",T->data);//是叶子结点才打印
	if(T&&i!=e)//控制递归次数,找到叶子后结束递归
	{
		e++;
		getleaf(T->lchild,i,e);
		getleaf(T->rchild,i,e);
	}
}

void leavetraverse(BiTtree T)//用for循环来打印每一层
{
	int i,e=1;//i是层数，e是每一次进入循环的时候把层数清1
	deapth(T);
	for(i=1;i<=n+1;i++)
		getleaf(T,i,e);
}

void LRChange(BiTtree T)//左右子树互换
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
		printf("please input the element:\n");//输入（前序）
		createBiTree1(s);
		if(n2==2*n1-1)
		{
			printf("the tree have %d null pointors and %d nodes.\n",n1,n2);
			printf("the inordertraverse virsion:\n");//输出（中序）
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
	printf("please choose the funtion you want to use:\n");//主界面
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
		deapth(s);//深度
		printf("the tree have %d leavals.\n",n+1);
		break;
//-----------------------------------------------------------------------
	case 2:
		LRChange(s);//左右子树互换
		printf("after left right change the inordertraverse:\n");
		InOrderTraverse(s);//中序输出
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
		printf("the leavetraverse virsion:\n");//层次遍历
	    leavetraverse(s);
     	printf("\n");
		break;
//-----------------------------------------------------------------------
	case 7:
		printf("another inordertraverse virsion:\n");//非递归的中序遍历
	    NDIOT(s);
    	printf("\n");
		break;
//-----------------------------------------------------------------------
	case 8:
		printf("please input the number you want to search:\n");//查找输入的结点
    	getchar();
    	scanf("%d",&a);
		if((s->data)>(s->lchild->data))	searchBST1(s,a,null,p);
		else searchBST2(s,a,null,p);
		break;
//-----------------------------------------------------------------------
	case 9:
    	printf("please input the number you want to insert:\n");//插入一个结点
	    scanf("%d",&b);
		if((s->data)>(s->lchild->data))
			InsertBST1(s,b);
		else InsertBST2(s,b);
    	printf("the inordertraverse virsion:\n");
    	InOrderTraverse(s);//中序输出
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
