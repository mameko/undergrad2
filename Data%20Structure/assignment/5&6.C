#include <stdio.h>
#include <malloc.h>
#define null 0
/*链表元数的插入 删除 排序 查找 打印*/
int n;
	     /*记录链表中元数的个数 */

struct data/*接点的数据类型*/
{
 int data;
 struct data * next;
};

struct data * creat()/*创造一个链表*/
{
 struct data * head;
 head=(struct data *)malloc(sizeof(struct data));/*开辟空间*/
 head->data=n;
 head->next=null;
 return head;
}

struct data * input_data(struct data *head)/*输入链表的元数*/
{
 struct data *p;
 int a,i;
 
 printf("input how many numbers you want in the link :\n");
 scanf("%d",&a);/*记录循环次数*/
 for(i=0;i<a;i++)
 {
   p=(struct data*)malloc(sizeof(struct data));
   printf("please input the number:\n");
   scanf("%d",&p->data);
   p->next=head->next;/*从表头插入新增元数*/
   head->next=p;
   n=n+1;
 }
 return head;
}

void arrange(struct data * head)
				 /*6 不开辟新空间来把链表排序*/
{
 int i,j;
 struct data *p,*pmax,*paf,*po;/* *pmax指向最大的那个结点
                                  *paf指向最大结点的后一个结点
								  *po指向头接点的下一个结点*/
 int no=n;
 p=pmax=po=head->next;/*把所有指针都指向头指针的下一个结点*/
 for(i=0;i<no;i++)/*找第一个最大的结点*/
 {
  if(p->data>pmax->data)
    pmax=p;
  if(p->next!=null)  
	  p=p->next;
 }
 head->next=pmax->next;/*把最大的那个结点放到表尾*/
 p->next=po;
 pmax->next=null;
  
 for(j=0;j<no;j++)/*排好其他结点*/
 { 
   po=p=pmax=head->next;/*又把指针指回头结点的下一个结点*/
   for(i=0;i<no-1-j;i++)/*因为以前已经排好了一些，所以循环次数不再是N*/
   {
    if(p->data>pmax->data)/*找比所有未排好续的结点都大的结点*/
      pmax=p;
      if(i<no-2-j) 
		  p=p->next;
   }
   
   if(p==pmax) 
	   continue;/*表明要找的数已经在要排的位置，所以不用排了，跳出这一次循环*/
   else/*把找到的元数排好*/
   {
     paf=pmax->next;
     pmax->next=p->next;
     head->next=paf;
     p->next=po;
   }
   
 }
 
}

struct data * insert(struct data *head)/*插入元数*/
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

struct data * delete_link(struct data * head,int a)/*删除元数*/
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

int search(struct data * head,int b)/*查找元数*/
{
 struct data *p;
 int i;
 p=head->next;
 for(i=0;i<n;i++)
  if(b==p->data) break;
   else if(p->next!=null) p=p->next;
 return i+1;
}

void print(struct data *head)/*打印所有元数*/
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
	     /*初始化链表*/
 printf("\n");
 
 arrange(head);/*把链表排序*/
 print(head);
 printf("\n");
 
 head=insert(head);
 print(head);
	     /*插入元数*/
 printf("\n");

 printf("input the number you want to delete:\n");
 scanf("%d",&a);
 head=delete_link(head,a);
 print(head);
	     /*删除元数*/
 printf("\n");

 printf("input the number you want to search:\n");
 scanf("%d",&a);
 b=search(head,a);
 printf("the number you search is at %d\n",b);
	      /*搜索元数*/
 printf("\n");

}