#include <stdio.h>
#include <string.h>
#include <io.h>
#define NULL 0
//#include <bios.h>

char ch;//记录读取的字符
int syn=0,m=0,n,sum;//syn是符号表对应的数字，m是token的指针，sum是常数的返回值，n
int handle1,handle2;//句柄喔,handle1为读的，handle2为写的
char *rwtab[6]={"if","else","while","do","for","switch"};//关键字表
char token[8];
FILE *fp;

//------------------------------------------------------------------------------------
/*
void output1()//把数字输出到目标文件destination.txt
{
	char c=' ';//用空格把syn与输出的字符分开
	write(handle2,&syn,sizeof(int));
	write(handle2,&c,sizeof(char));
	write(handle2,&sum,sizeof(int));
	c=10;//回车换行
	write(handle2,&c,sizeof(char));
}

void output2()
{
	char c=' ';
	char ch1;
	write(handle2,&syn,sizeof(syn));
	write(handle2,&c,sizeof(char));
	m=0;
	do
	{
		ch1=token[m];
		write(handle2,&ch1,sizeof(char));
		m++;
	}while(ch1!='\0');
	c=10;//回车换行
	write(handle2,&c,sizeof(char));
}
*/
void output1()
{
	fprintf(fp,"(%d , %d)\n",syn,sum);
}

void output2()
{
//	char ch1;
//	m=0;
//	do
//	{
//	    ch1=token[m];
		fprintf(fp,"(%d , %s)\n",syn,token);
//		m++;
//	}while(ch1!='\0');
	char c=10;//回车换行
	write(handle2,&c,sizeof(char));

}
//------------------------------------------------------------------------------------

void readnext()
{
//	if(!eof(handle1)) 
		read(handle1,&ch,sizeof(ch));//读一个字符，然后光标下移一个位置
}

void back()
{
	lseek(handle1,-(sizeof(char)),1);//光标回退一个字符
}

//------------------------------------------------------------------------------------

void scaner()
{
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
		//		syn=13;token[0]=ch;token[1]='\0';break;
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
		/*	case '/':
				m=0;token[m++]=ch;
				readnext();
				if(ch=='*')
				{
					syn=24;
					token[m++]=ch;
					token[m]='\0';
				}
				else
				{
					syn=16;
					back();
				}
				break;
			case '*':
				m=0;token[m++]=ch;
				readnext();
				if(ch=='/')
				{
					syn=34;
					token[m++]=ch;
					token[m]='\0';
				}
				else
				{
					syn=15;
					back();
				}
				break;
				*/

		/*		case '/':
					syn=16;token[0]=ch;token[1]='\0';break;   */
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

//------------------------------------------------------------------------------------
void main()
{
	handle1=open("source.txt",4);//以读方式打开源文件source.txt
//	handle2=open("destination.txt",2);//以写的方式打开目标文件destination.txt
	fp=fopen("destination.txt","w");
	do
	{
		scaner();
		switch(syn)
		{
		case 11: output1();break;
		case -1: fprintf(fp,"error happen\n");break;
		case 24:break;
		default: output2();
		}
//	}while(!eof(handle1));
	}while(syn!=0);
	close(handle1);
//	close(handle2);
	fclose(fp);
}
//------------------------------------------------------------------------------------







