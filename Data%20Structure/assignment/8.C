#include <stdio.h>
#include <malloc.h>
#define null 0

/*链栈的入栈和出栈算法*/

typedef struct/*定义栈*/
{
 struct nude *top;
 struct nude *base;
}sqstack;

struct nude/*定义栈中结点的类型*/
{
 int data;
 struct nude * next;
};

int n=0;/*记录有多少个结点*/

sqstack init(sqstack s)/*初始化栈*/
{
 s.base=(struct nude *)malloc(sizeof(struct nude));
 s.top=s.base;
 return s;
}

sqstack push(sqstack s)/*入栈*/
{
 struct nude * p;
 p=(struct nude *)malloc(sizeof(struct nude));
 printf("input a number:\n");
 if(n==0)
    scanf("%d",s.top);
 else
    {
     scanf("%d",&p->data);/*在表尾插入刚进栈的元数*/
     s.top->next=p;
	 s.top=p;
     p->next=null;
    }
  n+=1;
  return s;
}

void pop(sqstack s)/*出栈*/
{
 struct nude *p,*q;
 q=s.top;
 p=s.base+n-2;
 s.top=p;
 p->next=null;
 printf("the number to pop is:\n%d",*q);
 free(q);
 n-=1;
}

void main()
{
 sqstack s,k;
 int b,i;
 k.top=k.base=null;
 s=init(k);
 printf("how many numbers you want the in stack:\n");
 scanf("%d",&b);
 for(i=0;i<b;i++)
   s=push(s);
 pop(s);
 printf("\nthe stack now have %d numbers\n",n);
}