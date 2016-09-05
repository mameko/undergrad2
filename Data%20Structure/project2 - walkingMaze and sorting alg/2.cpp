#include "stdafx.h"
#include "stdio.h"
#define N 11
#define d 3
#define rd 10
struct element
{
int key[d];
int next;
};
typedef element sqlist[N];

sqlist R={{{0,0,0},0},{{2,7,8},0},{{1,0,9},0},{{0,6,3},0},{{9,3,0},0},{{5,8,9},0},{{1,8,4},0},
{{5,0,5},0},{{2,6,9},0},{{0,0,8},0},{{0,8,3},0}};
    //定义数据       

void radixsort(sqlist r,int n)
{   
    int f[10],int e[10];
    int i,j,k,p,t;
    int m;
    for(j=1;j<N;j++)
       {
     for(i=0;i<d;i++)
       printf("%3d",r[j].key[i]);///display the data;
           printf("\n");
    }
    printf("\n");

    for(k=1;k<=n-2;k++)////建立静态链表
    r[k].next=k+1;
    r[n-1].next=0;    ///最后收尾
    p=1;              //第一个数据开始  
    for(i=d-1;i>=0;i--)
    {
     for(j=0;j<rd;j++) 
     {
      f[j]=0;        ///队列头初始为0
           }
     while(p!=0)
     {
      k=r[p].key[i];    //第p个数据的第i位   123 则先取3低未，数组是高位
      if(f[k]==0) f[k]=p;//队列头为零，p给队列头
           else
      {
       r[e[k]].next=p;//有数据了，已经放入队列了，连接上下数据，p：下数据
      }
      e[k]=p;    //队尾=下数据（当前）
      p=r[p].next;//静态指针后移，取下一个数据
     }
       j=0;
       while(f[j]==0)
       j++;                 //寻找非空队列
       m=p=f[j] ; t=e[j];  
        while(j<rd-1)
     {
        j++;
        if(f[j]!=0)
     {
       r[t].next=f[j];   //头尾相连
                   t=e[j];////尾给了下一个头
     }
     }
          r[t].next=0;   //最后一个数据为0
}
   

   
       while(m>0)
    {
     for(i=0;i<d;i++)
     {
      printf("%3d", r[m].key[i]);
     
     }
           printf("\n");
           m=r[m].next;       ///输出排序后的静态链表
    }

}