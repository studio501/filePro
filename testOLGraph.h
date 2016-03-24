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

//���ʺ���
void visit(VertexType i);

//����G�ж���u��λ��
int locateVex(OLGraph G,VertexType u);

//����ͼ
void createGraph(OLGraph &G);

//��ӡͼ
void printGraph(OLGraph G);


//ɾ���������1�����
bool listDeleteFirstVex(ArcBox * &p,ArcBox &e,int pos=1);

//��λ�����е�Ԫ��e
int listLocateElem(ArcBox *p,ElemType e);

//ɾ��ĳ�����
ArcBox * listDeleteElem(ArcBox * p,ArcBox e);

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

//ɾ������
bool deleteVex(OLGraph &G,VertexType v);

//������
bool insertArc(OLGraph &G,VertexType v,VertexType w);

//ɾ����
bool deleteArc(OLGraph &G,VertexType v,VertexType w);

//�ӵ�v����������ݹ��������ȱ���ͼG
void DFS(OLGraph G,int v,visitFunc func);

//�ӵ�1��������������ȱ���ͼ����ÿ��������÷��ʺ���һ��
void DFSTraverse(OLGraph G,visitFunc func);

//��������ȷǵݹ����ͼG
void BFSTraverse(OLGraph G,visitFunc func);

};
#endif