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


//�����յĹ����
void initGList(GList &L);

//����ͷβ����洢�ṹ
void createGList(GList &L,int nline=1,const char *fileName="glAtom.txt");


#endif // !__TEST_GLIST__HH__
