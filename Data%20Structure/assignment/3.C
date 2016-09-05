#include <stdio.h>
/*顺序表插入一个数*/
void main()
{
 int a[11],i,b,c;

 for(i=0;i<10;i++)
  a[i]=i;
  a[10]=0;
/*表初始化 */
 printf("\nplease input a number:\n");
     /*输入要插入的元数*/
 scanf("%d",&b);

 for(i=0;i<10;i++)
  {
   if(a[i]>=b)
     {c=i; break;}  /* 查找插入位置 */
   else c=10;
  }

 if(c!=10)
  {
   for(i=10;i>c;i--)
   a[i]=a[i-1];       /*后移元数*/

  }

 a[c]=b;

 for(i=0;i<11;i++)
   printf("%d",a[i]);
}