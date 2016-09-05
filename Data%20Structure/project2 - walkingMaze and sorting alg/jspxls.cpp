/*   ����������㷨Դ����*/ 


#include <stdio.h> 

#define   D   3                                               /*   DΪ����������λ��   */ 
#define   R   10                                             /*   RΪ����   */ 

typedef   int   KeyType; 
typedef   int   DataType; 

struct   Node;                                             /*   ������������   */ 
typedef   struct   Node   RadixNode; 

struct   Node   
{ 
	KeyType   key[D];   
    /*   DataType   info;*/
	RadixNode   *next; 
}; 

typedef RadixNode * RadixList; 

typedef struct QueueNode
{ 
	RadixNode   *f;                                     /*   ���е�ͷָ��   */ 
    RadixNode   *e;                                     /*   ���е�βָ��   */ 
}Queue; 

Queue queue[R]; 

void radixSort(RadixList * plist,int d,int r)
{ 
	int i,j,k;   
    RadixNode *p, *head = (*plist)-> next; 
    for(j=d-1;j>=0;j--)   
	{                   /*   ����d�η�����ռ�*/ 
		p=head; 
        for(i=0;i<r;i++)
		{  
			queue[i].f = NULL;
			queue[i].e = NULL;   /*   �����   */ 
		} 
        while(p!=NULL)
		{ 
			k=p->key[j];                             /*   ��������ĵ�j���������з���*/ 
			if(queue[k].f==NULL)
				queue[k].f=p;                   /*   ����k������Ϊ�գ���ǰ��¼Ϊ��ͷ*/   
			else (queue[k].e)->next=p;/*   ����ǰ��¼���ӵ���k�ӵĶ�β*/ 
            queue[k].e=p; 
            p=p->next; 
		}
		for(i=0;queue[i].f==NULL;i++)   /*   �ҳ���һ���ǿն���*/ 
			; 
		p=queue[i].e;     
		head=queue[i].f;   /*   headΪ�ռ������ͷָ��*/ 
		for(i++;i<r;i++) 
			if(queue[i].f!=NULL)
			{   /*   �ռ��ǿն���   */ 
				p->next=queue[i].f;
				p=queue[i].e;
			}               
			p->next=NULL;
	}
	(*plist)->next=head;
} 

struct   Node   element[11]={ 
        0,0,0,NULL,/*��ͷ*/ 
        0,3,6,NULL,/*36*/ 
        0,0,5,NULL,/*5*/ 
        0,1,6,NULL,/*16*/ 
        0,9,8,NULL,/*98*/ 
        0,9,5,NULL,/*95*/ 
        0,4,7,NULL,/*47*/ 
        0,3,2,NULL,/*32*/ 
        0,3,6,NULL,/*36*/ 
        0,4,8,NULL,/*48*/ 
        0,1,0,NULL   /*10*/ 
}; 

int main()
{
	int i;
	RadixList p=element;
	for(i=0;i<10;i++)
		element[i].next=&element[i+1];
	element[10].next=NULL;
	radixSort(&p,3,10);
	p=p->next;
	while(p!=NULL)
	{
		printf("%d ",p->key[1]*10+p->key[2]);
		p=p->next;
	}
	getchar(); 
    return   0; 
} 