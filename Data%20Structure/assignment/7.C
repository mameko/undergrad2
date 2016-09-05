#include <stdio.h>
#include <malloc.h>
#define increase_size 5
#define stack_init_size 50

/*编写顺序栈的入栈和出栈的操作算法*/

typedef struct/*定义栈的类型*/
{
 int *base;
 int *top;
 int stacksize;
}sqstack;

sqstack init(sqstack s)/*初始化一个栈*/
{
 s.base=(int *)malloc(stack_init_size*sizeof(int));
 if(!s.base) printf("error");
 s.top=s.base;
 s.stacksize=stack_init_size;
 return s;
}

sqstack push(sqstack s,int x)/*入栈*/
{
 if(s.top-s.base>stack_init_size)/*判断空间够不够*/
 {
  s.base=(int *)realloc(s.base,sizeof(int)*(stack_init_size+increase_size));
  if(!s.base)  printf("error");
  s.top=stack_init_size+s.base;
  s.stacksize+=increase_size;
 }
 *s.top++=x;
 return s;
}

void pop(sqstack s)/*出栈*/
{
 int x;
 if(s.top==s.base) printf("error");/*若栈空就输出错误*/
 else 
 {
	 x=*--s.top;
     printf("now pop the top number\nthe number is:%d\n",x);
 }
}

void print(sqstack s)/*把栈打印出来*/
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
