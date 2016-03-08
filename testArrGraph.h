#ifndef __TESTARRGRAPH__HH__
#define __TESTARRGRAPH__HH__
#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;

namespace AG{
#define MAX_NAME 5
#define MAX_INFO 20
#define INFINITY INT_MAX
#define MAX_VERTEXT_NUM 26
typedef int VRType;
typedef char InfoType;
typedef char VertexType[MAX_NAME];

enum GraphKind
{
	DG,
	DN,
	UDG,
	UDN
};

typedef struct 
{
	VRType adj;//�����ϵ����,����Ȩͼ1,0��ʾ�Ƿ�����,�Դ�Ȩͼ,ΪȨֵ
	InfoType *info;
}ArcCell,AdjMatrix[MAX_VERTEXT_NUM][MAX_VERTEXT_NUM];

struct MGraph
{
	VertexType vexs[MAX_VERTEXT_NUM];
	AdjMatrix arcs;
	int vexnum,arcnum;
	GraphKind kind;
};

//����G�ж���u��λ��
int locateVex(MGraph G,VertexType u);

//��������(�ڽӾ���)��ʾ�� ��������ͼ
void createFUDG(MGraph &G,const char *filename="GData1.txt");

//��������(�ڽӾ���)��ʾ�� ����������
void createFUDN(MGraph &G,const char *filename="GData1_w.txt");

//��������(�ڽӾ���)��ʾ�� ��������ͼ
void createDG(MGraph &G,const char *filename="GData3.txt");
};
#endif