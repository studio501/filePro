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

//maze测试主入口
void mazeTest();
#endif