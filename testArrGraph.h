#ifndef __TESTARRGRAPH__HH__
#define __TESTARRGRAPH__HH__
#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;

namespace AG{
#define MAX_NAME 20
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

	typedef void (*visitFunc)(VertexType);

	//访问函数
	void visit(VertexType i);

	//返回G中顶点u的位置
	int locateVex(MGraph G,VertexType u);

	//采用数组(邻接矩阵)表示法 构造无向图
	void createFUDG(MGraph &G,const char *filename="GData1.txt");

	//采用数组(邻接矩阵)表示法 构造无向网
	void createFUDN(MGraph &G,const char *filename="GData1_w.txt");

	//采用数组(邻接矩阵)表示法 构造有向图
	void createDG(MGraph &G,const char *filename="GData3.txt");

	//采用数组(邻接矩阵)表示法 构造有向网
	void createDN(MGraph &G,const char *filename="GData4.txt");

	//采用数组(邻接矩阵)表示法 构造无向图
	void createUDG(MGraph &G,const char *filename="GData3.txt");

	//采用数组(邻接矩阵)表示法 构造无向网
	void createUDN(MGraph &G,const char *filename="GData4.txt");

	//构造图
	void createGraph(MGraph &G);

	//销毁图
	void destroyGraph(MGraph &G);

	//返回顶点序号v的值
	VertexType & getVex(MGraph G,int v);

	//对v重新赋值
	bool putVex(MGraph &G,VertexType v,VertexType value);

	//返回v的第一个邻接顶点的序号
	int firstAdjVex(MGraph G,VertexType v);

	//返回v的相对于w的下一个邻接顶面序号,若w是最后一个邻接顶点返回-1
	int nextAdjVex(MGraph G,VertexType v,VertexType w);

	//新增顶点v(但不增加相关的弧)
	void insertVex(MGraph &G,VertexType v);

	//删除顶点
	bool deleteVex(MGraph &G,VertexType v);

	//新增弧
	bool insertArc(MGraph &G,VertexType v,VertexType w);

	//删除弧
	bool deleteArc(MGraph &G,VertexType v,VertexType w);

	//从第v个顶点出发递归地深度优先遍历图G
	void DFS(MGraph G,int v,visitFunc func);

	//从第1个顶点起深度优先遍历图并对每个顶点调用访问函数一次
	void DFSTraverse(MGraph G,visitFunc func);

	//按广度优先非递归遍历图G
	void BFSTraverse(MGraph G,visitFunc func);

	//输出邻接矩阵存储结构的图G
	void display(MGraph G);
};
#endif