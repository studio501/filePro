
#include "stdafx.h"

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>
#include <functional>
#include "commonFunc.h"

using namespace std;

#define N 5
typedef int keyType;
struct dataType1
{
	keyType key;
	int others;
};

#define HAS_BF 1
#include "biTreeCommon.h"
#define initDSTable initBiTree
#define destroyDSTable destroyBiTree
#define traverseDSTable inorderTraverse

#define BsTree BiTNode<dataType1> *

void r_Rotate(BsTree &p)
{
	BsTree lc;
	lc=p->lchild;
	p->lchild=lc->rchild;
	lc->rchild=p;
	p=lc;
}

void l_Rotate(BsTree &p)
{
	BsTree rc;
	rc=p->rchild;
	p->rchild=rc->lchild;
	rc->lchild=p;
	p=rc;
}

#define LH +1
#define EH 0
#define RH -1

void lefteBalance(BsTree &T)
{
	BsTree lc;
	BsTree rd;
	lc=T->rchild;
	switch(lc->bf)
	{
	case LH:
		T->bf=lc->bf=EH;
		r_Rotate(T);
		break;
	case RH:
		rd=lc->rchild;
		switch(rd->bf)
		{
		case LH:
			T->bf=RH;
			lc->bf=EH;
			break;
		case RH:
			T->bf=EH;
			lc->bf=LH;
			break;
		case EH:
			T->bf=lc->bf=EH;
			break;
		}
		rd->bf=EH;
		l_Rotate(T->lchild);
		r_Rotate(T);
	}
}

void rightBalance(BsTree &T)
{
	BsTree rc;
	BsTree rd;
	rc=T->rchild;
	switch(rc->bf)
	{
	case RH:
		T->bf=rc->bf=EH;
		l_Rotate(T);
		break;
	case LH:
		rd=rc->lchild;
		switch(rd->bf)
		{
		case RH:
			T->bf=LH;
			rc->bf=EH;
			break;
		case EH:
			T->bf=rc->bf=EH;
			break;
		case LH:
			T->bf=EH;
			rc->bf=RH;
		}
		rd->bf=EH;
		r_Rotate(T->rchild);
		l_Rotate(T);
	}
}

bool insertAVL(BsTree &T,dataType1 e,bool &taller)
{
	if(!T)
	{
		T=(BsTree)malloc(sizeof(BiTNode<dataType1>));
		T->data=e;
		T->lchild=T->rchild=NULL;
		T->bf=EH;
		taller=true;
	}
	else
	{
		if EQ(e.key,T->data.key)
		{
			taller=false;
			return false;
		}
		if LT(e.key,T->data.key)
		{
			if(!insertAVL(T->lchild,e,taller))
				return false;
			if(taller)
				switch(T->bf)
			{
				case LH:
					lefteBalance(T);
					taller=false;
					break;
				case EH:
					T->bf=LH;
					taller=true;
					break;
				case RH:
					T->bf=EH;
					taller=false;				
			}
		}
		else
		{
			if(!insertAVL(T->rchild,e,taller))
				return false;
			if(taller)
				switch(T->bf)
			{
				case LH:
					T->bf=EH;
					taller=false;
					break;
				case EH:
					T->bf=RH;
					taller=true;
					break;
				case RH:
					rightBalance(T);
					taller=false;
						
			}
		}

	}
	return true;
}

static void print(const dataType1& c)
{
	printf("(%d  %d)\n",c.key,c.others);
}

void testbfSearchTree()
{
	BsTree dt;
	BsTree p;
	bool k;
	int i;
	keyType j;
	dataType1 r[N]={{13,1},{24,2},{37,3},{90,4},{53,5}};
	initDSTable(dt);
	for(i=0;i<N;++i)
		insertAVL(dt,r[i],k);
	traverseDSTable<dataType1>(dt,print);
	printf("\n请输入待查找的关键字: ");
	cin>>j;
	p=searchBST1(dt,j);
	if(p)
		print(p->data);
	else
		printf("表中不存在此值");
	printf("\n");
	destroyDSTable(dt);
}