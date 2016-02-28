#ifndef __TEST_GLIST__HH__
#define __TEST_GLIST__HH__

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>
#include <stdarg.h>
#include "commonFunc.h"
#include "sstringTest.h"
using namespace std;

#define BASE_BUFF 256

typedef char AtomType;

enum ElemTag
{
	ATOM,
	LIST
};

typedef struct GLNode
{
	ElemTag tag;
	union 
	{
		AtomType atom;
		struct  
		{
			GLNode *hp,*tp;
		}ptr;
	};
}*GList,GLNode;

typedef struct GLNode1
{
	ElemTag tag;
	union 
	{
		AtomType atom;
		GLNode1 *hp;
	};
	GLNode1 *tp;
}*GList1,GLNode1;


typedef void(*viGLFunc)(AtomType);

//�����յĹ����
void initGList(GList &L);

//����ͷβ����洢�ṹ
void createGList(GList &L,SString S);

//��������
void destroyGList(GList &L);

//������
void copyGList(GList &T,GList L);

//��ȡ����
int GListLength(GList L);

//����������
int GListDepth(GList L);

//�жϹ�����Ƿ�Ϊ��
bool GListEmpty(GList L);

//��ȡͷ����β 
GList getEdge(GList L,int side=0);

//����Ԫ��e��Ϊ��ĵ�һ��Ԫ��
void insertFirst(GList &L,GList e);

//ɾ����һ��Ԫ�ز���e������ֵ
void deleteFirst(GList &L,GList &e);

//���������
void traverse_GL(GList &L,viGLFunc func);

#endif // !__TEST_GLIST__HH__
