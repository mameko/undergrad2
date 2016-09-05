//输入一个字符串，利用先序遍历实现2叉树的生成，并且用中序遍历实现2叉树
#include <stdio.h>
#include <malloc.h>
#define null 0

typedef struct BiTNode
{
	char data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTtree;

void createBiTree(BiTtree &T)
{
	char ch;
	scanf("%c",&ch);
	if(ch==' ') T=null;
	else 
	{
		if(!(T=(BiTNode *)malloc(sizeof(BiTNode)))) printf("error");
        T->data=ch;
		createBiTree(T->lchild);
		createBiTree(T->rchild);
	}
}

void PreOrderTraverse(BiTtree &T)
{
	if(T)
	{
	    PreOrderTraverse(T->lchild);
		if(T->data) printf("%c",T->data);
		PreOrderTraverse(T->rchild);
	}
}

void main()
{
	BiTtree s;
	printf("please input the element:\n");
	createBiTree(s);
    PreOrderTraverse(s);
    printf("\n");
}