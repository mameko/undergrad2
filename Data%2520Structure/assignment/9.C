#include <stdio.h>
#include <malloc.h>
#define increase_size 5
#define stack_init_size 50
#define null 0

/*�ж�����ƥ��ĳ���*/

typedef struct/*����ջ������*/
{
 char *base;
 char *top;
 int stacksize;
}sqstack;

sqstack init(sqstack s)/*��ʼ��ջ*/
{
 s.base=(char *)malloc(stack_init_size*sizeof(char));
 if(!s.base) printf("error");
 s.top=s.base;
 s.stacksize=stack_init_size;
 return s;
}

sqstack push(sqstack s,char x)/*��ջ*/
{
 if(s.top-s.base>stack_init_size)/*�ж�ջ�Ƿ����㹻λ��*/
 {
  s.base=(char *)realloc(s.base,sizeof(char)*(stack_init_size+increase_size));
  if(!s.base)  printf("error");
  s.top=stack_init_size+s.base;
  s.stacksize+=increase_size;
 }
 *s.top++=x;
 return s;
}

sqstack pop(sqstack s)/*��ջ*/
{
 if(s.top==s.base) printf("error");
 else 
 	s.top--;
 return s;
}

char gettop(sqstack s)/*��ȡջ��Ԫ��*/
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
 for(i=0;(i<s.stacksize)&&(a!='#');i++)/*�ж�ƥ�䣬��#����������*/
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
