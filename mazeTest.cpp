
#include "stdafx.h"

#include "mazeTest.h"

#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

int curStep=1;
PosType directArr[4]={{0,1},{1,0},{0,-1},{-1,0}};

//输出迷宫的解
void print_m()
{
	for(int i=0;i<=g_x;++i)
	{
		for(int j=0;j<=g_y;++j)
			printf("%3d",m[i][j]);
		printf("\n");
	}
}

//初始化地图
void initMap(const char *file)
{
	char ch;
	ifstream fin(file);
	if(fin.is_open())
	{
		ch = fin.get();
		bool isSet=false;
		int startX=0,startY=0;
		while(ch!=EOF)
		{
			if(ch=='\n')
			{
				if(!isSet)
				{
					g_y=startY-1;
					isSet=true;
				}
				++startX;
				startY=0;
			}
			else if(ch==' ')
			{

			}
			else
			{
				m[startX][startY]=atoi(&ch);
				/*if(m[startX][startY]==2)
				{
					g_begin.x = startX;
					g_begin.y = startY;
				}
				else if(m[startX][startY]==3)
				{
					g_end.x = startX;
					g_end.y = startY;
				}*/
				++startY;
			}
			ch=fin.get();
		}
		g_x=startX;

		g_begin.x = 1;
		g_begin.y = 1;

		g_end.x = 8;
		g_end.y = 8;
	}
}

//返回是否可通过
bool isPass(PosType b)
{
	if(m[b.x][b.y]==1)
		return true;
	else
		return false;
}

//使m的a点的值变为足迹
void footPrint(PosType a)
{
	m[a.x][a.y]=curStep;
}

//查看是否是来路
bool checkBack(PosType a)
{
	if(m[a.x][a.y]<100) return false;
	else return true;
}

//根据当前位置及移动方向,求得下一个位置
void nextPos(PosType &c,int direc)
{
	c.x+=directArr[direc].x;
	c.y+=directArr[direc].y;
}

//使迷宫m的b点序号变为-1(不能通过的路径)
void markPrint(PosType b)
{
	m[b.x][b.y]=-1;
}

//若存在start 到出口end的通道 求得一条 返回true
bool mazePath(PosType start_,PosType end_)
{
	stack<MElemType> S;
	PosType curPos = g_begin;
	MElemType e;

	do 
	{
		if(isPass(curPos))
		{
			footPrint(curPos);
			e.ord=curStep;
			e.seat=curPos;
			e.direct=0;
			S.push(e);
			++curStep;
			if(curPos.x==g_end.x&&curPos.y==g_end.y) return true;
			nextPos(curPos,e.direct);
		}
		else
		{
			if(!S.empty())
			{
				e = S.top();
				S.pop();
				--curStep;
				while(e.direct==3&&!S.empty())
				{
					markPrint(e.seat);
					e=S.top();
					S.pop();
					--curStep;
				}
				if(e.direct<3)
				{
					++e.direct;
					S.push(e);
					++curStep;
					curPos=e.seat;
					nextPos(curPos,e.direct);
				}
			}
		}
	} while (!S.empty());
	return false;
}

//判断t1,t2的优先关系
char precede_evalue(char t1,char t2)
{
	char f;
	switch (t2)
	{
	case '+':
	case '-':
		if(t1=='('||t1=='\n')
			f='<';
		else
			f='>';
		break;
	case '*':
	case '/':
		if(t1=='*'||t1=='/'||t1==')')
			f='>';
		else
			f='<';
		break;
	case '(':
		if(t1==')')
		{
			printf("bracket is not match!\n");
			system("pause");
		}
		else
			f='<';
		break;
	case ')':
		switch(t1)
		{
		case '(':
			f='=';
			break;
		case '\n':
			printf("short of right bracket\n");
			system("pause");
			break;
		default:
			f='>';
			break;
		}
	default:
		break;
	}
}

void mazeTest()
{
	cout<<"mazeTest\n";
	initMap();
	
	if(mazePath(g_begin,g_end))
	{
		cout<<"there is a way in maze:\n";
		print_m();
	}
	else cout<<"no way out\n";
}

