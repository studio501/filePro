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

//-------------------
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

//���ʺ���
void visit(VertexType i);

//����G�ж���u��λ��
int locateVex(OLGraph G,VertexType u);

//����ͼ
void createGraph(OLGraph &G);

//��ӡͼ
void printGraph(ALGraph G);

//���ڱ�ͷ
bool listInsertFirstVex(ArcNode * &p,ArcNode *e,int pos=1);

//ɾ���������1�����
bool listDeleteFirstVex(ArcBox * &p,ArcBox &e,int pos=1);

//��λ�����е�Ԫ��e
int listLocateElem(ArcBox *p,ElemType e);

//ɾ��ĳ�����
ArcNode * listDeleteElem(ArcNode * p,ArcNode e);

//�ڱ��������ҳ���e adjx��ͬ�Ľ��
ArcNode * point(ArcNode *p,ArcNode e,ArcNode * &p1);

//����ͼ
void destroyGraph(OLGraph &G);

//���ض������v��ֵ
VertexType & getVex(OLGraph G,int v);

//��v���¸�ֵ
bool putVex(OLGraph &G,VertexType v,VertexType value);

//����v�ĵ�һ���ڽӶ�������
int firstAdjVex(OLGraph G,VertexType v);

//�������Ƿ����
bool equalvex(ElemType a,ElemType b);

//����v�������w����һ���ڽӶ������,��w�����һ���ڽӶ��㷵��-1
int nextAdjVex(OLGraph G,VertexType v,VertexType w);

//��������v(����������صĻ�)
void insertVex(OLGraph &G,VertexType v);

//��ȡ����ı�������
int lengthOfAdjVex(ALGraph G,VertexType v);

//ɾ������
bool deleteVex(OLGraph &G,VertexType v);

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