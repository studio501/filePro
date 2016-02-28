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

//创建空的广义表
void initGList(GList &L);

//采用头尾链表存储结构
void createGList(GList &L,SString S);

//销毁链表
void destroyGList(GList &L);

//拷贝表
void copyGList(GList &T,GList L);

//获取表长度
int GListLength(GList L);

//求广义表的深度
int GListDepth(GList L);

//判断广义表是否为空
bool GListEmpty(GList L);

//获取头或者尾 
GList getEdge(GList L,int side=0);

//插入元素e作为表的第一个元素
void insertFirst(GList &L,GList e);

//删除第一个元素并用e返回其值
void deleteFirst(GList &L,GList &e);

//遍历广义表
void traverse_GL(GList &L,viGLFunc func);

#endif // !__TEST_GLIST__HH__
