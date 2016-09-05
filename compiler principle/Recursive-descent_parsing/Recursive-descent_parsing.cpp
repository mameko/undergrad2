#include <stdio.h>
#include <string.h>
#include <io.h>
#define NULL 0

char ch;//记录读取的字符
int syn=0,m=0,n,sum,k;//syn是符号表对应的数字，m是token的指针，sum是常数的返回值，k是用来判断是那种符号
int handle1;//句柄喔,handle1为读的
int flag;
char *rwtab[6]={"if","else","while","do","for","switch"};//关键字表
char token[8];

void F();
void T2();
void T();
void E2();
void E();
void L();
void S();

void readnext()
{
		read(handle1,&ch,sizeof(ch));//读一个字符，然后光标下移一个位置
}

void back()
{
	lseek(handle1,-(sizeof(char)),1);//光标回退一个字符
}

void scanner()
{
	sum=0;
	for(n=0;n<8;n++)
		token[n]=NULL;
	readnext();
	while(ch==' '||ch==10)
		readnext();
	if(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z')
	{
		m=0;
		while(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z'||ch>='0'&&ch<='9')
		{
			token[m]=ch;
			m++;
			readnext();
		}
		token[m++]='\0';
		back();
		syn=10;
		for(n=0;n<6;n++)
		{
			if(strcmp(token,rwtab[n])==0)
			{
				syn=n+1;break;
			}
		}
	}
	else
		if(ch>'0'&&ch<'9')
		{
			while(!eof(handle1)&&ch>'0'&&ch<'9')
			{
				sum=sum*10+ch-'0';
				readnext();
			}
			back();
			syn=11;
		}
		else
			switch(ch)
		{
			case '<': 
				m=0;token[m++]=ch;
				readnext();
				if(ch=='=')
				{
					syn=17;
					token[m++]=ch;
					token[m]='\0';
				}
				else
				{
					syn=18;
					back();
				}
				break;
			case '>':
				m=0;token[m++]=ch;
				readnext();
				if(ch=='=')
				{
					syn=20;
					token[m++]=ch;
					token[m]='\0';
				}
				else
				{
					syn=19;
					back();
				}
				break;
			case '=':
				m=0;token[m++]=ch;
				readnext();
				if(ch=='=')
				{
					syn=33;
					token[m++]=ch;
					token[m]='\0';
				}
				else
				{
					syn=32;
					back();
				}
				break;
			case '+':
				m=0;token[m++]=ch;
				readnext();
				if(ch=='+')
				{
					syn=37;
					token[m++]=ch;
					token[m]='\0';
				}
				else
				{
					syn=13;
					back();
				}
				break;
			case '-':
				m=0;token[m++]=ch;
				readnext();
				if(ch=='-')
				{
					syn=38;
					token[m++]=ch;
					token[m]='\0';
				}
				else
				{
					syn=14;
					back();
				}
				break;
			case ':':
				syn=22;token[0]=ch;token[1]='\0';break;
			case ';':
				syn=23;token[0]=ch;token[1]='\0';break;
			case '{':
				syn=25;token[0]=ch;token[1]='\0';break;
			case '}':
				syn=26;token[0]=ch;token[1]='\0';break;
			case '(':
				syn=27;token[0]=ch;token[1]='\0';break;
			case ')':
				syn=28;token[0]=ch;token[1]='\0';break;
			case '%':
				syn=31;token[0]=ch;token[1]='\0';break;
			case '[':
				syn=35;token[0]=ch;token[1]='\0';break;
			case '@':
				syn=0;token[0]=ch;token[1]='\0';break;
			case '!':
				m=0;token[m++]=ch;
				readnext();
				if(ch=='=')
				{
					syn=21;
					token[m++]=ch;
					token[m]='\0';
				}
				else
				{
					syn=-1;
					back();
				}
				break;
				case '*':
					syn=15;token[0]=ch;token[1]='\0';break;
				case '/'://注释
					m=0;token[m++]=ch;
					readnext();
					if(ch=='*')
					{
						token[m++]=ch;
						token[m++]=' ';
						while(ch!='@')
						{
							readnext();
							if(ch=='*')
							{
								token[m++]=ch;
								readnext();
								if(ch=='/')
								{
									syn=24;
									token[m++]=ch;
									token[m]='\0';
									break;
								}
								else syn=-1;
							}
							else syn=-1;
						}
					}
					else
					{
						syn=16;
						back();
					}
					break;
			default: syn=-1;			
		}
}

void T2()
{
	if(syn==15||syn==16)//15--'*' 16--'/'
	{
		k=syn;
		scanner();
		F();T2();
		if(k==15) printf("*");
		if(k==16) printf("/");
	}
	else
		if(syn!=23&&syn!=28&&syn!=13&&syn!=14)//14--'-' 10--'id' 13--'+' 23--';'
		{ 
			printf("error T2\n");flag=1;
		}
}

void F()
{
	if(syn==27)//27--'('
	{
		scanner();E();
		if(syn==28)//28--')'
		{
			scanner();
		}
		else {printf("error F1\n");flag=1;}
	}
	else
		if(syn==10||syn==11)//10--'id' 11--'nu'
		{
			if(syn==10) printf("%s",token);
			if(syn==11) printf("%d",sum);
			scanner();
		}
		else {printf("error F2\n");flag=1;}
}

void T()
{
	F();T2();
}

void E2()
{
	if(syn==13||syn==14)//13--'+' 14--'-'
	{	
		k=syn;
		scanner();
		T();E2();
		if(k==13) printf("+");
		if(k==14) printf("-");
	}
	else 
		if(syn!=23&&syn!=28) 
		{
			printf("error E2\n");//28--')' 23--';'
			flag=1;
		}
}

void E()
{
	T();E2();
}

void L()
{
	if(syn==10)//10--'id'
	{
		printf("%s",token);
		scanner();
		if(syn==32)//32--'='
		{
			scanner();
			E();
			if(syn==23)//23--';'
			{
				scanner();
				if(syn!=0)//0--'@'
				{
					printf("=\n");
					L();
				}
			}
			else {printf("error L1\n");flag=1;}
		}
		else {printf("error L2\n");flag=1;}
	}
	else {printf("error L3\n");flag=1;}
}

void main()
{
	handle1=open("source.txt",4);//以读方式打开源文件source.txt
	scanner();
	L();
	if(flag==0) printf("\nsuccess\n");
	else printf("\nfail\n");
	close(handle1);
	getchar();
}



