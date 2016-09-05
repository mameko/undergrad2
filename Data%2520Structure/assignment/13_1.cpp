//输入一个字符串，利用先序遍历实现2叉树的生成，并且用中序遍历实现2叉树
#include <stdio.h>
#include <malloc.h>
#define null 0

typedef struct BiTNode
{
	char data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTtree;

int n1,n2;//n1计算空格个数，n2计算输入字母总个数

void createBiTree(BiTtree &T)
{
	char ch;
	//	scanf("%c",&ch);
	ch=getchar();
	if(ch!=10)
	{
		n2++;
		if(ch==' ') 
		{
			T=null;
			n1++;
		}
		else 
		{
			
			if(!(T=(BiTNode *)malloc(sizeof(BiTNode)))) printf("error");
			T->data=ch;
			createBiTree(T->lchild);
			createBiTree(T->rchild);
		}
	}
}

void InOrderTraverse(BiTtree &T)
{
	if(T)
	{
	    InOrderTraverse(T->lchild);
		if(T->data) printf("%c",T->data);
		InOrderTraverse(T->rchild);
	}
}

void main()
{
	BiTtree s;
	printf("please input the element:\n");
	createBiTree(s);	
	if(n2==2*n1-1)
	{
		printf("the tree have %d space and %d node.\n",n1,n2);
		InOrderTraverse(s);
		printf("\nok\n");
	}
	else printf("error\n");
}