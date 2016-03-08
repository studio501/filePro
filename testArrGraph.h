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
	VRType adj;//顶点关系类型,对无权图1,0表示是否相邻,对带权图,为权值
	InfoType *info;
}ArcCell,AdjMatrix[MAX_VERTEXT_NUM][MAX_VERTEXT_NUM];

struct MGraph
{
	VertexType vexs[MAX_VERTEXT_NUM];
	AdjMatrix arcs;
	int vexnum,arcnum;
	GraphKind kind;
};

//返回G中顶点u的位置
int locateVex(MGraph G,VertexType u);

//采用数组(邻接矩阵)表示法 构造无向图
void createFUDG(MGraph &G,const char *filename="GData1.txt");

//采用数组(邻接矩阵)表示法 构造无向网
void createFUDN(MGraph &G,const char *filename="GData1_w.txt");

//采用数组(邻接矩阵)表示法 构造有向图
void createDG(MGraph &G,const char *filename="GData3.txt");
};
#endif