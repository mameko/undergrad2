#include <stdio.h>
#include <malloc.h>
#define null 0
/*����Ԫ���Ĳ��� ɾ�� ���� ���� ��ӡ*/
int n;
	     /*��¼������Ԫ���ĸ��� */

struct data/*�ӵ����������*/
{
 int data;
 struct data * next;
};

struct data * creat()/*����һ������*/
{
 struct data * head;
 head=(struct data *)malloc(sizeof(struct data));/*���ٿռ�*/
 head->data=n;
 head->next=null;
 return head;
}

struct data * input_data(struct data *head)/*����������Ԫ��*/
{
 struct data *p;
 int a,i;
 
 printf("input how many numbers you want in the link :\n");
 scanf("%d",&a);/*��¼ѭ������*/
 for(i=0;i<a;i++)
 {
   p=(struct data*)malloc(sizeof(struct data));
   printf("please input the number:\n");
   scanf("%d",&p->data);
   p->next=head->next;/*�ӱ�ͷ��������Ԫ��*/
   head->next=p;
   n=n+1;
 }
 return head;
}

void arrange(struct data * head)
				 /*6 �������¿ռ�������������*/
{
 int i,j;
 struct data *p,*pmax,*paf,*po;/* *pmaxָ�������Ǹ����
                                  *pafָ�������ĺ�һ�����
								  *poָ��ͷ�ӵ����һ�����*/
 int no=n;
 p=pmax=po=head->next;/*������ָ�붼ָ��ͷָ�����һ�����*/
 for(i=0;i<no;i++)/*�ҵ�һ�����Ľ��*/
 {
  if(p->data>pmax->data)
    pmax=p;
  if(p->next!=null)  
	  p=p->next;
 }
 head->next=pmax->next;/*�������Ǹ����ŵ���β*/
 p->next=po;
 pmax->next=null;
  
 for(j=0;j<no;j++)/*�ź��������*/
 { 
   po=p=pmax=head->next;/*�ְ�ָ��ָ��ͷ������һ�����*/
   for(i=0;i<no-1-j;i++)/*��Ϊ��ǰ�Ѿ��ź���һЩ������ѭ������������N*/
   {
    if(p->data>pmax->data)/*�ұ�����δ�ź����Ľ�㶼��Ľ��*/
      pmax=p;
      if(i<no-2-j) 
		  p=p->next;
   }
   
   if(p==pmax) 
	   continue;/*����Ҫ�ҵ����Ѿ���Ҫ�ŵ�λ�ã����Բ������ˣ�������һ��ѭ��*/
   else/*���ҵ���Ԫ���ź�*/
   {
     paf=pmax->next;
     pmax->next=p->next;
     head->next=paf;
     p->next=po;
   }
   
 }
 
}

struct data * insert(struct data *head)/*����Ԫ��*/
{
 struct data *p,*po;
 int i;
 
 	 p=(struct data*)malloc(sizeof(struct data));
     printf("input the number you want to insert:\n");
     scanf("%d",&p->data);
     po=head;
     for(i=0;i<n;i++)
        if(po->next->data>=p->data)
			break;
		else
			po=po->next;
		
 p->next=po->next;
 po->next=p;
 n=n+1;
 return head;

}

struct data * delete_link(struct data * head,int a)/*ɾ��Ԫ��*/
{
 struct data *po;
 int i;
 po=head;
 for(i=0;i<n;i++)

  if(a==po->next->data)
    po->next=po->next->next;
  else
    if(po->next!=null)
      po=po->next;
 n=n-1;
 return head;
}

int search(struct data * head,int b)/*����Ԫ��*/
{
 struct data *p;
 int i;
 p=head->next;
 for(i=0;i<n;i++)
  if(b==p->data) break;
   else if(p->next!=null) p=p->next;
 return i+1;
}

void print(struct data *head)/*��ӡ����Ԫ��*/
{
 int i;
 struct data *p;
 p=head->next;
 for(i=0;i<n;i++)
   {
    printf("%d",p->data);
    p=p->next;
   }
}

void main()
{
 struct data *head;
 int a,b;
 head=creat();
 head=input_data(head);
 print(head);
	     /*��ʼ������*/
 printf("\n");
 
 arrange(head);/*����������*/
 print(head);
 printf("\n");
 
 head=insert(head);
 print(head);
	     /*����Ԫ��*/
 printf("\n");

 printf("input the number you want to delete:\n");
 scanf("%d",&a);
 head=delete_link(head,a);
 print(head);
	     /*ɾ��Ԫ��*/
 printf("\n");

 printf("input the number you want to search:\n");
 scanf("%d",&a);
 b=search(head,a);
 printf("the number you search is at %d\n",b);
	      /*����Ԫ��*/
 printf("\n");

}