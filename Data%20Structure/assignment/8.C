#include <stdio.h>
#include <malloc.h>
#define null 0

/*��ջ����ջ�ͳ�ջ�㷨*/

typedef struct/*����ջ*/
{
 struct nude *top;
 struct nude *base;
}sqstack;

struct nude/*����ջ�н�������*/
{
 int data;
 struct nude * next;
};

int n=0;/*��¼�ж��ٸ����*/

sqstack init(sqstack s)/*��ʼ��ջ*/
{
 s.base=(struct nude *)malloc(sizeof(struct nude));
 s.top=s.base;
 return s;
}

sqstack push(sqstack s)/*��ջ*/
{
 struct nude * p;
 p=(struct nude *)malloc(sizeof(struct nude));
 printf("input a number:\n");
 if(n==0)
    scanf("%d",s.top);
 else
    {
     scanf("%d",&p->data);/*�ڱ�β����ս�ջ��Ԫ��*/
     s.top->next=p;
	 s.top=p;
     p->next=null;
    }
  n+=1;
  return s;
}

void pop(sqstack s)/*��ջ*/
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