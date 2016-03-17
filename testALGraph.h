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
//-------------------

struct ElemType
{
	int adjvex;
	InfoType *info;
};

struct ArcNode
{
	ElemType data;
	ArcNode * nextarc;
};
//36
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

//���ʺ���
void visit(VertexType i);

//����G�ж���u��λ��
int locateVex(ALGraph G,VertexType u);

//����ͼ
void createGraph(MGraph &G);

//����ͼ
void destroyGraph(ALGraph &G);

//���ض������v��ֵ
VertexType & getVex(MGraph G,int v);

//��v���¸�ֵ
bool putVex(MGraph &G,VertexType v,VertexType value);

//����v�ĵ�һ���ڽӶ�������
int firstAdjVex(MGraph G,VertexType v);

//����v�������w����һ���ڽӶ������,��w�����һ���ڽӶ��㷵��-1
int nextAdjVex(MGraph G,VertexType v,VertexType w);

//��������v(����������صĻ�)
void insertVex(MGraph &G,VertexType v);

//ɾ������
bool deleteVex(MGraph &G,VertexType v);

//������
bool insertArc(MGraph &G,VertexType v,VertexType w);

//ɾ����
bool deleteArc(MGraph &G,VertexType v,VertexType w);

//�ӵ�v����������ݹ��������ȱ���ͼG
void DFS(MGraph G,int v,visitFunc func);

//�ӵ�1��������������ȱ���ͼ����ÿ��������÷��ʺ���һ��
void DFSTraverse(MGraph G,visitFunc func);

//��������ȷǵݹ����ͼG
void BFSTraverse(MGraph G,visitFunc func);

//����ڽӾ���洢�ṹ��ͼG
void display(MGraph G);
};
#endif