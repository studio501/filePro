#ifndef __TESTOLGRAPH__HH__
#define __TESTOLGRAPH__HH__
#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;

namespace OLG{
#define MAX_NAME 5
#define MAX_INFO 20
#define INFINITY INT_MAX
#define MAX_VERTEXT_NUM 20
typedef int VRType;
typedef int InfoType;
typedef char VertexType[MAX_NAME];


struct ArcBox1
{
	int tialvex,headvex;
	InfoType *info;
	ArcBox1 *hlink,*tlink;
};

struct ElemType
{
	int tailvex,headvex;
	InfoType *info;
	ArcBox1 *hlink;
};

struct ArcBox
{
	ElemType data;
	ArcBox * tlink;
};

struct VexNode
{
	VertexType data;
	ArcBox1 *firstin;
	ArcBox *firstout;
};

struct OLGraph
{
	VexNode xlist[MAX_VERTEXT_NUM];
	int vexnum,arcnum;
};


//#define LNode ArcNode
//#define next nextarc
//typedef ArcNode * LinkList;

typedef void (*visitFunc)(VertexType);

//访问函数
void visit(VertexType i);

//返回G中顶点u的位置
int locateVex(OLGraph G,VertexType u);

//构造图
void createGraph(OLGraph &G);

//打印图
void printGraph(OLGraph G);


//删除边链表第1个结点
bool listDeleteFirstVex(ArcBox * &p,ArcBox &e,int pos=1);

//定位链表中的元素e
int listLocateElem(ArcBox *p,ElemType e);

//删除某个结点
ArcBox * listDeleteElem(ArcBox * p,ArcBox e);

//销毁图
void destroyGraph(OLGraph &G);

//返回顶点序号v的值
VertexType & getVex(OLGraph G,int v);

//对v重新赋值
bool putVex(OLGraph &G,VertexType v,VertexType value);

//返回v的第一个邻接顶点的序号
int firstAdjVex(OLGraph G,VertexType v);

//两条弧是否相等
bool equalvex(ElemType a,ElemType b);

//返回v的相对于w的下一个邻接顶面序号,若w是最后一个邻接顶点返回-1
int nextAdjVex(OLGraph G,VertexType v,VertexType w);

//新增顶点v(但不增加相关的弧)
void insertVex(OLGraph &G,VertexType v);

//删除顶点
bool deleteVex(OLGraph &G,VertexType v);

//新增弧
bool insertArc(OLGraph &G,VertexType v,VertexType w);

//删除弧
bool deleteArc(OLGraph &G,VertexType v,VertexType w);

//从第v个顶点出发递归地深度优先遍历图G
void DFS(OLGraph G,int v,visitFunc func);

//从第1个顶点起深度优先遍历图并对每个顶点调用访问函数一次
void DFSTraverse(OLGraph G,visitFunc func);

//按广度优先非递归遍历图G
void BFSTraverse(OLGraph G,visitFunc func);

};
#endif