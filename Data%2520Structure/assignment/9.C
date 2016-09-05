#include <stdio.h>
#include <malloc.h>
#define increase_size 5
#define stack_init_size 50
#define null 0

/*判断括号匹配的程序*/

typedef struct/*定义栈的类型*/
{
 char *base;
 char *top;
 int stacksize;
}sqstack;

sqstack init(sqstack s)/*初始化栈*/
{
 s.base=(char *)malloc(stack_init_size*sizeof(char));
 if(!s.base) printf("error");
 s.top=s.base;
 s.stacksize=stack_init_size;
 return s;
}

sqstack push(sqstack s,char x)/*入栈*/
{
 if(s.top-s.base>stack_init_size)/*判断栈是否够有足够位置*/
 {
  s.base=(char *)realloc(s.base,sizeof(char)*(stack_init_size+increase_size));
  if(!s.base)  printf("error");
  s.top=stack_init_size+s.base;
  s.stacksize+=increase_size;
 }
 *s.top++=x;
 return s;
}

sqstack pop(sqstack s)/*出栈*/
{
 if(s.top==s.base) printf("error");
 else 
 	s.top--;
 return s;
}

char gettop(sqstack s)/*获取栈顶元数*/
{
   if(s.top==s.base) return null;
    else return *(s.top-1);
}

void main()
{
 sqstack s,k;
 int i;
 char a,b;
 k.top=k.base=null;
 k.stacksize=0;
 s=init(k);
 for(i=0;(i<s.stacksize)&&(a!='#');i++)/*判断匹配，用#来结束输入*/
 {
	 printf("please input parenthesis %d:\n",i+1);
	 a=getchar();
     if(a=='('||a=='[')
	 {
		 s=push(s,a);
		 printf("push in\n");
	 }
     else 
	 {
	       b=gettop(s);
           if(a==')')
		   {
			   if(b=='(') {s=pop(s);printf("pop out\n");}
			   else {printf("error\n");break;}
		   }
           else
	            if(a==']')
				{
		             if(b=='[') {s=pop(s);printf("pop out\n");}
	                 else {printf("error\n");break;}
				}
	 }
	 
 }

if(s.base==s.top)
    printf("right\n");
}
