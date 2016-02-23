#include "stdafx.h"
#include <malloc.h>
#include <process.h>
#include <math.h>
#include <fstream>
#include <iostream>

#include "testStack.h"


using namespace std;

//��ӡһ��Ԫ��
void print_stack(SElemType e)
{
	cout<<e<<" ";
}

//���뵽һ��Ԫ�ص��ļ�
void writetofile_stack(SElemType e)
{
	ofstream fout("editLine.txt",ios_base::out | ios_base::app);
	if(fout.is_open())
	{
		fout<<(char)e;
	}
	fout.close();
}

//����һ�����з����ļ�
void writeBreakLine(const char *fileName)
{
	ofstream fout("editLine.txt",ios_base::out | ios_base::app);
	if(fout.is_open())
	{
		fout<<"\n";
	}
	fout.close();
}

//����һ����ջ
void initStack(SqStack &S)
{
	if(! (S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType))))
	{
		exit(OVERFLOW);
	}
	S.top=S.base;
	S.stackSize=STACK_INIT_SIZE;
}

//����ջ
void destroyStack(SqStack &S)
{
	free(S.base);
	S.base=NULL;
	S.top=NULL;
	S.stackSize=0;
}

//���ջ
void clearStack(SqStack &S)
{
	S.top=S.base;
}

//�Ƿ��ǿ�ջ
bool isStackEmpty(SqStack &S)
{
	if(S.top==S.base) return true;
	return false;
}

//��ǰջ�ĳ���
int stackLength(SqStack &S)
{
	return S.top-S.base;
}
//��ȡջ��Ԫ��
bool getTop(SqStack &S,SElemType &e)
{
	if(S.top>S.base)
	{
		e=*(S.top-1);
		return true;
	}
	return false;
}

//ѹջ
void pushStack(SqStack &S,SElemType e)
{
	if(S.top-S.base>=S.stackSize)
	{
		//ջ��׷��
		S.base=(SElemType*)realloc(S.base,(S.stackSize+STACK_INC_SIZE)*sizeof(SElemType) );
		if(!S.base) exit(OVERFLOW);
		S.top=S.base+S.stackSize;
		S.stackSize+=STACK_INC_SIZE;
	}
	*(S.top)++=e;
}

//��ջ
bool popStack(SqStack &S,SElemType &e)
{
	if(S.top==S.base) return false;
	e=*--S.top;
	return true;
}

//����ջ
void stackTraverse(SqStack S,visitstack_func vFunc)
{
	while(S.top>S.base)
		vFunc(*S.base++);
	printf("\n");
}

//ת������
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

//ʮ����ת��Ϊʮ������
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

//��������ƥ��
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

//�б༭����
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
