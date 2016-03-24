#ifndef __TESTAMLGRAPH__HH__
#define __TESTAMLGRAPH__HH__
#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;

namespace AMLG{
//p327
#define MAX_NAME 5
#define MAX_INFO 20
#define INFINITY INT_MAX
#define MAX_VERTEXT_NUM 20
typedef int VRType;
typedef int InfoType;
typedef char VertexType[MAX_NAME];

enum VisitIF
{
	unvisited,
	visited
};

//---------------------------------
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
//---------------------------------
struct EBox
{
	VisitIF mark;//���ʱ��
	int ivex,jvex;//�ñ���������������λ��
	EBox *ilink,*jlink;
	InfoType *info;
};

struct VexBox
{
	VertexType data;
	EBox *firstedg;//ָ���һ�������ö���ı�
};

struct AMLGraph
{
	VexBox adjmulist[MAX_VERTEXT_NUM];
	int vexnum,edgenum;//����ͼ�Ķ���ͱ���
};

//#define LNode ArcNode
//#define next nextarc
//typedef ArcNode * LinkList;


typedef void (*visitFunc)(VertexType);

//���ʺ���
void visit(VertexType i);

//����G�ж���u��λ��
int locateVex(AMLGraph G,VertexType u);

//����ͼ
void createGraph(AMLGraph &G);

//�ñߵķ��ʱ��Ϊδ����
void markUnvizited(AMLGraph G);

//��ӡͼ
void printGraph(AMLGraph G);

//ɾ���������1�����
bool listDeleteFirstVex(ArcBox * &p,ArcBox &e,int pos=1);

//��λ�����е�Ԫ��e
int listLocateElem(ArcBox *p,ElemType e);

//ɾ��ĳ�����
ArcBox * listDeleteElem(ArcBox * p,ArcBox e);

//����ͼ
void destroyGraph(AMLGraph &G);

//���ض������v��ֵ
VertexType & getVex(AMLGraph G,int v);

//��v���¸�ֵ
bool putVex(AMLGraph &G,VertexType v,VertexType value);

//����v�ĵ�һ���ڽӶ�������
int firstAdjVex(AMLGraph G,VertexType v);

//�������Ƿ����
bool equalvex(ElemType a,ElemType b);

//����v�������w����һ���ڽӶ������,��w�����һ���ڽӶ��㷵��-1
int nextAdjVex(AMLGraph G,VertexType v,VertexType w);

//��������v(����������صĻ�)
void insertVex(AMLGraph &G,VertexType v);

//ɾ����
bool deleteArc(AMLGraph &G,VertexType v,VertexType w);

//ɾ������
bool deleteVex(AMLGraph &G,VertexType v);

//������
bool insertArc(AMLGraph &G,VertexType v,VertexType w);

//�ӵ�v����������ݹ��������ȱ���ͼG
void DFS(AMLGraph G,int v,visitFunc func);

//�ӵ�1��������������ȱ���ͼ����ÿ��������÷��ʺ���һ��
void DFSTraverse(AMLGraph G,visitFunc func);

//��������ȷǵݹ����ͼG
void BFSTraverse(AMLGraph G,visitFunc func);

};
#endif