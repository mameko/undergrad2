#include <stdio.h>
#include <malloc.h>
#define increase_size 5
#define stack_init_size 50

/*��д˳��ջ����ջ�ͳ�ջ�Ĳ����㷨*/

typedef struct/*����ջ������*/
{
 int *base;
 int *top;
 int stacksize;
}sqstack;

sqstack init(sqstack s)/*��ʼ��һ��ջ*/
{
 s.base=(int *)malloc(stack_init_size*sizeof(int));
 if(!s.base) printf("error");
 s.top=s.base;
 s.stacksize=stack_init_size;
 return s;
}

sqstack push(sqstack s,int x)/*��ջ*/
{
 if(s.top-s.base>stack_init_size)/*�жϿռ乻����*/
 {
  s.base=(int *)realloc(s.base,sizeof(int)*(stack_init_size+increase_size));
  if(!s.base)  printf("error");
  s.top=stack_init_size+s.base;
  s.stacksize+=increase_size;
 }
 *s.top++=x;
 return s;
}

void pop(sqstack s)/*��ջ*/
{
 int x;
 if(s.top==s.base) printf("error");/*��ջ�վ��������*/
 else 
 {
	 x=*--s.top;
     printf("now pop the top number\nthe number is:%d\n",x);
 }
}

void print(sqstack s)/*��ջ��ӡ����*/
{
 int * sp;
 printf("the stack is:\n");
 for(sp=--s.top;sp>=s.base;sp--)
    printf("%d\n",*sp);
} 

void main()
{
 sqstack s,k;
 int a,c,i=0;
 k.top=k.base=0;
 k.stacksize=0;
 s=init(k);
 printf("plsese input how many numbers you want:\n");
 scanf("%d",&c);
 for(i=0;i<c;i++)
 {
  printf("input number %d\n",i+1);
  scanf("%d",&a);
  s=push(s,a); 
 }
 print(s);
 pop(s);
}