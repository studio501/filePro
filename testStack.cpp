#include "stdafx.h"
#include <malloc.h>
#include <process.h>
#include <math.h>
#include <fstream>
#include <iostream>

#include "testStack.h"


using namespace std;

//打印一个元素
void print_stack(SElemType e)
{
	cout<<e<<" ";
}

//输入到一个元素到文件
void writetofile_stack(SElemType e)
{
	ofstream fout("editLine.txt",ios_base::out | ios_base::app);
	if(fout.is_open())
	{
		fout<<(char)e;
	}
	fout.close();
}

//输入一个换行符到文件
void writeBreakLine(const char *fileName)
{
	ofstream fout("editLine.txt",ios_base::out | ios_base::app);
	if(fout.is_open())
	{
		fout<<"\n";
	}
	fout.close();
}

//创建一个空栈
void initStack(SqStack &S)
{
	if(! (S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType))))
	{
		exit(OVERFLOW);
	}
	S.top=S.base;
	S.stackSize=STACK_INIT_SIZE;
}

//销毁栈
void destroyStack(SqStack &S)
{
	free(S.base);
	S.base=NULL;
	S.top=NULL;
	S.stackSize=0;
}

//清空栈
void clearStack(SqStack &S)
{
	S.top=S.base;
}

//是否是空栈
bool isStackEmpty(SqStack &S)
{
	if(S.top==S.base) return true;
	return false;
}

//当前栈的长度
int stackLength(SqStack &S)
{
	return S.top-S.base;
}
//获取栈顶元素
bool getTop(SqStack &S,SElemType &e)
{
	if(S.top>S.base)
	{
		e=*(S.top-1);
		return true;
	}
	return false;
}

//压栈
void pushStack(SqStack &S,SElemType e)
{
	if(S.top-S.base>=S.stackSize)
	{
		//栈满追加
		S.base=(SElemType*)realloc(S.base,(S.stackSize+STACK_INC_SIZE)*sizeof(SElemType) );
		if(!S.base) exit(OVERFLOW);
		S.top=S.base+S.stackSize;
		S.stackSize+=STACK_INC_SIZE;
	}
	*(S.top)++=e;
}

//出栈
bool popStack(SqStack &S,SElemType &e)
{
	if(S.top==S.base) return false;
	e=*--S.top;
	return true;
}

//遍历栈
void stackTraverse(SqStack S,visitstack_func vFunc)
{
	while(S.top>S.base)
		vFunc(*S.base++);
	printf("\n");
}

//转换进制
void conversion_unit(int n,int N)
{
	n= (n>0?n:0);
	N= (N>0?N:0);
	SqStack S;
	initStack(S);
	SElemType e;
	while(n)
	{
		pushStack(S,n%N);
		n/=N;
	}
	while(!isStackEmpty(S))
	{
		popStack(S,e);
		printf("%d",e);
	}
	printf("\n");

}

//十进制转换为十六进制
void conversion_16(int n)
{
	int N=16;
	n= (n>0?n:0);

	SqStack S;
	initStack(S);
	SElemType e;
	while(n)
	{
		pushStack(S,n%N);
		n/=N;
	}
	while(!isStackEmpty(S))
	{
		popStack(S,e);
		if(e<9) printf("%d",e);
		else printf("%c",e+55);
	}
	printf("\n");
}

//检验括号匹配
void check_bracket(const char *fileName,int mLine)
{
	int curLine=0;
	ifstream fin(fileName);
	char buffer[1024];

	SqStack S;
	SElemType ch[80],*p,e;
	initStack(S);

	if(fin.is_open())
	{
		while(curLine <mLine)
		{
			fin.getline(buffer,sizeof(buffer));
			++curLine;
		}
		int curChar = 0;
		while(buffer[curChar]!='\0')
		{
			switch (buffer[curChar])
			{
			case '(':
			case '[':
			case '{':
				pushStack(S,buffer[curChar]);
				++curChar;
				break;
			case ')':
			case ']':
			case '}':
				if(!isStackEmpty(S))
				{
					popStack(S,e);
					if(!(e=='('&&buffer[curChar]==')' ||
						 e=='['&&buffer[curChar]==']' ||
						 e=='{'&&buffer[curChar]=='}'))
					{
						printf("bracket doesn't match!\n");
						return;
					}
				}
				else
				{
					printf("short of left bracket\n");
					return;
				}
			default:
				++curChar;
				break;
			}
		}
		if(isStackEmpty(S)) printf("bracket match\n");
		else printf("short of right bracket\n");
	}	
}

//行编辑程序
void lineEdit(const char *fileName)
{
	SqStack S;
	char ch;
	SElemType e;
	initStack(S);

	ifstream fin(fileName);
	ch=fin.get();
	while(ch!=EOF)
	{
		while(ch!=EOF && ch!='\n')
		{
			switch (ch)
			{
			case '#':
				if(!isStackEmpty(S)) popStack(S,e);
				break;
			case '@':
				clearStack(S);
				break;
			default:
				pushStack(S,ch);
				break;
			}
			ch=fin.get();
		}
		stackTraverse(S,writetofile_stack);
		writeBreakLine();
		clearStack(S);
		if(ch!=EOF)
			ch=fin.get();
	}
	destroyStack(S);
}
