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
    //��������       

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

    for(k=1;k<=n-2;k++)////������̬����
    r[k].next=k+1;
    r[n-1].next=0;    ///�����β
    p=1;              //��һ�����ݿ�ʼ  
    for(i=d-1;i>=0;i--)
    {
     for(j=0;j<rd;j++) 
     {
      f[j]=0;        ///����ͷ��ʼΪ0
           }
     while(p!=0)
     {
      k=r[p].key[i];    //��p�����ݵĵ�iλ   123 ����ȡ3��δ�������Ǹ�λ
      if(f[k]==0) f[k]=p;//����ͷΪ�㣬p������ͷ
           else
      {
       r[e[k]].next=p;//�������ˣ��Ѿ���������ˣ������������ݣ�p��������
      }
      e[k]=p;    //��β=�����ݣ���ǰ��
      p=r[p].next;//��ָ̬����ƣ�ȡ��һ������
     }
       j=0;
       while(f[j]==0)
       j++;                 //Ѱ�ҷǿն���
       m=p=f[j] ; t=e[j];  
        while(j<rd-1)
     {
        j++;
        if(f[j]!=0)
     {
       r[t].next=f[j];   //ͷβ����
                   t=e[j];////β������һ��ͷ
     }
     }
          r[t].next=0;   //���һ������Ϊ0
}
   

   
       while(m>0)
    {
     for(i=0;i<d;i++)
     {
      printf("%3d", r[m].key[i]);
     
     }
           printf("\n");
           m=r[m].next;       ///��������ľ�̬����
    }

}