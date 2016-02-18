#ifndef __MAZE_TEST__HH_
#define __MAZE_TEST__HH_
#include "testStack.h"

struct PosType
{
	int x;
	int y;
};

#define MAXLENGTH 25
typedef int MazeType[MAXLENGTH][MAXLENGTH];

MazeType m;
int g_x,g_y;
PosType g_begin,g_end;

struct MElemType
{
	int ord;
	PosType seat;
	int direct;
};

//输出迷宫的解
void print_m();

//初始化地图
void initMap(const char *file="mazeMap.txt");

//返回是否可通过
bool isPass(PosType b);

//使m的a点的值变为足迹
void footPrint(PosType a);

//查看是否是来路
bool checkBack(PosType a);

//根据当前位置及移动方向,求得下一个位置
void nextPos(PosType &c,int direc);

//使迷宫m的b点序号变为-1(不能通过的路径)
void markPrint(PosType b);

//若存在start 到出口end的通道 求得一条 返回true
bool mazePath(PosType start_,PosType end_);

//判断t1,t2的优先关系
char precede_evalue(char t1,char t2);

//判断c是否是7种运算之一
bool is7operate(char c);

//做四则运算
float doOperate(float a,char theta,float b);

//算术表达式求值
float evaluateExpression(int mLine=1,const char *file="evaluateExpression.txt");

//move x-->z
void moveHanoi(char x,int n,char z,int &gc);

//将塔座x上按直径由小到大且自上而下编号为1到n的n个圆盘按规则搬到塔座z上 y 用作辅助塔
void hanoi(char x,char y,char z,int &gc,int n=3);
//maze测试主入口
void mazeTest();
#endif