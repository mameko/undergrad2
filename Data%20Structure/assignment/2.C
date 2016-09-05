#include <stdio.h>
#include <malloc.h>
#define null 0

/*用C来定义一个空的顺序表*/

struct data/*定义数据类型*/
{
  int d;
  struct data * next;
};

void main()
{
 struct data *p;
 p=(struct data *)malloc(sizeof(struct data));/*开辟第一个接点*/
 p->next=null;//
}
