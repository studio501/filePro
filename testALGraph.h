#ifndef __TESTARRGRAPH__HH__
#define __TESTARRGRAPH__HH__
#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;



namespace ALG{
#define MAX_NAME 5
#define MAX_INFO 20
#define INFINITY INT_MAX
#define MAX_VERTEXT_NUM 20
typedef int VRType;
typedef int InfoType;
typedef char VertexType[MAX_NAME];

enum GraphKind
{
	DG,
	DN,
	UDG,
	UDN
};

//-------------------
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
//-------------------


struct ArcNode
{
	int adjvex;
	InfoType *info;
	ArcNode * next;
};
typedef struct
{
	VertexType data;
	ArcNode *firstarc;
}VNode,adjList[MAX_VERTEXT_NUM];

struct ALGraph
{
	adjList vertices;
	int vexnum,arcnum;
	int kind;
};

//#define LNode ArcNode
//#define next nextarc
//typedef ArcNode * LinkList;

typedef void (*visitFunc)(VertexType);

//访问函数
void visit(VertexType i);

//返回G中顶点u的位置
int locateVex(ALGraph G,VertexType u);

//构造图
void createGraph(ALGraph &G);

//打印图
void printGraph(ALGraph G);

//插在表头
bool listInsertFirstVex(ArcNode * &p,ArcNode *e,int pos=1);

//删除边链表第1个结点
bool listDeleteFirstVex(ArcNode * &p,ArcNode* &e,int pos=1);

//删除某个结点
ArcNode * listDeleteElem(ArcNode * p,ArcNode e);

//在边链表中找出与e adjx相同的结点
ArcNode * point(ArcNode *p,ArcNode e,ArcNode * &p1);

//销毁图
void destroyGraph(ALGraph &G);

//返回顶点序号v的值
VertexType & getVex(ALGraph G,int v);

//对v重新赋值
bool putVex(ALGraph &G,VertexType v,VertexType value);

//返回v的第一个邻接顶点的序号
int firstAdjVex(ALGraph G,VertexType v);

//两条弧是否相等
bool equalvex(ArcNode a,ArcNode b);

//返回v的相对于w的下一个邻接顶面序号,若w是最后一个邻接顶点返回-1
int nextAdjVex(ALGraph G,VertexType v,VertexType w);

//新增顶点v(但不增加相关的弧)
void insertVex(ALGraph &G,VertexType v);

//获取顶点的边链表长度
int lengthOfAdjVex(ALGraph G,VertexType v);

//删除顶点
bool deleteVex(ALGraph &G,VertexType v);

//新增弧
bool insertArc(ALGraph &G,VertexType v,VertexType w);

//删除弧
bool deleteArc(ALGraph &G,VertexType v,VertexType w);

//从第v个顶点出发递归地深度优先遍历图G
void DFS(ALGraph G,int v,visitFunc func);

//从第1个顶点起深度优先遍历图并对每个顶点调用访问函数一次
void DFSTraverse(ALGraph G,visitFunc func);

//从第v个顶点出发递归地深度优先遍历图G
void DFS1(ALGraph G,int v,visitFunc func);

//从第1个顶点起深度优先遍历图并对每个顶点调用访问函数一次
void DFSTraverse1(ALGraph G,visitFunc func);

//按广度优先非递归遍历图G
void BFSTraverse(ALGraph G,visitFunc func);

//按广度优先非递归遍历图G
void BFSTraverse1(ALGraph G,visitFunc func);

//输出邻接矩阵存储结构的图G
void display(MGraph G);
};
#endif