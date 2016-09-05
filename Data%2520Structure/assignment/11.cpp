//kmp
#include <stdio.h>
#include <malloc.h>
#define String_maxsize 50

typedef unsigned char SString[String_maxsize+1];

void get_nextval(SString T,int nextval[])
{
	int i,j;
	i=1;
	nextval[1]=0;
	j=0;
	while(i<T[0])
	{
		if(j==0||T[i]==T[j])
		{
			++i;++j;
			if(T[i]!=T[j]) nextval[i]=j;
			else nextval[i]=nextval[j];
		}
		else j=nextval[j];
	}
}

int Index_kmp(SString S,SString T,int pos,int k[])
{
	int i,j;
	i=pos;
	j=1;
	while(i<=S[0]&&j<=T[0])
	{
		if(j==0||S[i]==T[j])
		{
			++i;++j;
		}
		else j=k[j];
	}
	if(j>T[0]) return i-T[0];
	else return 0;
}

void creat_a_string(SString &D)
{
	int i;
	char c;
	i=1;
	while(i<String_maxsize+1)
	{
		c=getchar();
		if(c!='#')
	  	{
			if(c!=10) 
			{
				D[i]=c;
				i++;
			}
			else continue;
		}
		else break;
	}
	D[0]=i-1;
}

void main()
{
	SString S,T;
	int a[10],b,c;
	printf("please input the main string:\n");
	creat_a_string(S);
	printf("the main string has %d char:\n",S[0]);
	printf("please input the substring:\n");
	creat_a_string(T);
	printf("the sub string has %d char:\n",T[0]);
	get_nextval(T,a);
	printf("please input where to start:\n");
	scanf("%d",&b);
	c=Index_kmp(S,T,b,a);
	printf("the place is at %d",c);
}
