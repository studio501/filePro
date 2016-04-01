
#include "stdafx.h"

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>
#include <functional>
#include "commonFunc.h"

using namespace std;

#define N 10
typedef int keyType;
struct dataType
{
	keyType key;
	int others;
};

#include "biTreeCommon.h"
#define initDSTable initBiTree
#define destroyDSTable destroyBiTree
#define traverseDSTable inorderTraverse

#define BiTree BiTNode<dataType> *

//BiTree searchBST1(BiTree T,keyType key_)
//{
//	if(!T||EQ(key_,T->data.key)) return T;
//	else if LT(key_,T->data.key) return searchBST1(T->lchild,key_);
//	else searchBST1(T->rchild,key_);
//}

bool searchBST(BiTree &T,keyType key_,BiTree f,BiTree &p)
{
	if(!T)
	{
		p=f;
		return false;
	}
	else if EQ(key_,T->data.key)
	{
		p=T;
		return true;
	}
	else if LT(key_,T->data.key)
		return searchBST(T->lchild,key_,T,p);
	else
		return searchBST(T->rchild,key_,T,p);
}

bool insertBST(BiTree &T,dataType e)
{
	BiTree p;
	BiTree s;
	if(!searchBST(T,e.key,NULL,p))
	{
		s=(BiTree)malloc(sizeof(BiTNode<dataType>));
		s->data=e;
		s->lchild=s->rchild=NULL;
		if(!p) T=s;
		else if LT(e.key,p->data.key)
			p->lchild=s;
		else p->rchild=s;
		return true;
	}
	else return false;
}

void deleteBST(BiTree &p)
{
	BiTree q;
	BiTree s;
	if(!p->rchild)
	{
		q=p;
		p=p->lchild;
		free(q);
		q=NULL;
	}
	else if(!p->lchild)
	{
		q=p;
		p=p->rchild;
		free(q);
		q=NULL;
	}
	else
	{
		q=p;
		s=p->lchild;
		while(s->rchild)
		{
			q=s;
			s=s->rchild;
		}
		p->data=s->data;
		if(q!=p) q->rchild=s->lchild;
		else q->lchild=s->lchild;
		free(s);
		s=NULL;
	}
}

bool deleteWholeTree(BiTree &T,keyType key_)
{
	if(!T) return false;
	else
	{
		if EQ(key_,T->data.key)
			deleteBST(T);
		else if LT(key_,T->data.key)
			deleteWholeTree(T->lchild,key_);
		else
			deleteWholeTree(T->rchild,key_);
		return true;
	}
}
static void print(const dataType& c)
{
	printf("(%d  %d)\n",c.key,c.others);
}

void testDySearchTree()
{
	BiTree dt;
	BiTree p;
	int i;
	keyType j;
	dataType r[N]={{45,1},{12,2},{53,3},{3,4},{37,5},{24,6},{100,7},{61,8},{90,9},{78,10}};
	initDSTable(dt);
	for(i=0;i<N;++i)
		insertBST(dt,r[i]);
	traverseDSTable<dataType>(dt,print);
	printf("\n请输入待查找的值: ");
	cin>>j;
	p=searchBST1(dt,j);
	if(p)
	{
		printf("表中存在此值。");
		deleteWholeTree(dt,j);
		printf("删除此值后:\n");
		traverseDSTable<dataType>(dt,print);
		cout<<endl;
	}
	else printf("表中不存在此值\n");
	destroyDSTable(dt);
	int a = 100;
}