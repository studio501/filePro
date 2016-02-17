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

//����Թ��Ľ�
void print_m();

//��ʼ����ͼ
void initMap(const char *file="mazeMap.txt");

//�����Ƿ��ͨ��
bool isPass(PosType b);

//ʹm��a���ֵ��Ϊ�㼣
void footPrint(PosType a);

//�鿴�Ƿ�����·
bool checkBack(PosType a);

//���ݵ�ǰλ�ü��ƶ�����,�����һ��λ��
void nextPos(PosType &c,int direc);

//ʹ�Թ�m��b����ű�Ϊ-1(����ͨ����·��)
void markPrint(PosType b);

//������start ������end��ͨ�� ���һ�� ����true
bool mazePath(PosType start_,PosType end_);

//�ж�t1,t2�����ȹ�ϵ
char precede_evalue(char t1,char t2);

//maze���������
void mazeTest();
#endif