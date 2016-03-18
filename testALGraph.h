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

//���ʺ���
void visit(VertexType i);

//����G�ж���u��λ��
int locateVex(ALGraph G,VertexType u);

//����ͼ
void createGraph(ALGraph &G);

//��ӡͼ
void printGraph(ALGraph G);

//���ڱ�ͷ
bool listInsertFirstVex(ArcNode * &p,ArcNode *e,int pos=1);

//ɾ���������1�����
bool listDeleteFirstVex(ArcNode * &p,ArcNode* &e,int pos=1);

//ɾ��ĳ�����
ArcNode * listDeleteElem(ArcNode * p,ArcNode e);

//�ڱ��������ҳ���e adjx��ͬ�Ľ��
ArcNode * point(ArcNode *p,ArcNode e,ArcNode * &p1);

//����ͼ
void destroyGraph(ALGraph &G);

//���ض������v��ֵ
VertexType & getVex(ALGraph G,int v);

//��v���¸�ֵ
bool putVex(ALGraph &G,VertexType v,VertexType value);

//����v�ĵ�һ���ڽӶ�������
int firstAdjVex(ALGraph G,VertexType v);

//�������Ƿ����
bool equalvex(ArcNode a,ArcNode b);

//����v�������w����һ���ڽӶ������,��w�����һ���ڽӶ��㷵��-1
int nextAdjVex(ALGraph G,VertexType v,VertexType w);

//��������v(����������صĻ�)
void insertVex(ALGraph &G,VertexType v);

//��ȡ����ı�������
int lengthOfAdjVex(ALGraph G,VertexType v);

//ɾ������
bool deleteVex(ALGraph &G,VertexType v);

//������
bool insertArc(ALGraph &G,VertexType v,VertexType w);

//ɾ����
bool deleteArc(ALGraph &G,VertexType v,VertexType w);

//�ӵ�v����������ݹ��������ȱ���ͼG
void DFS(ALGraph G,int v,visitFunc func);

//�ӵ�1��������������ȱ���ͼ����ÿ��������÷��ʺ���һ��
void DFSTraverse(ALGraph G,visitFunc func);

//�ӵ�v����������ݹ��������ȱ���ͼG
void DFS1(ALGraph G,int v,visitFunc func);

//�ӵ�1��������������ȱ���ͼ����ÿ��������÷��ʺ���һ��
void DFSTraverse1(ALGraph G,visitFunc func);

//��������ȷǵݹ����ͼG
void BFSTraverse(ALGraph G,visitFunc func);

//��������ȷǵݹ����ͼG
void BFSTraverse1(ALGraph G,visitFunc func);

//����ڽӾ���洢�ṹ��ͼG
void display(MGraph G);
};
#endif