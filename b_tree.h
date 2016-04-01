
#ifndef __B_TREE__HH__
#define __B_TREE__HH__
#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>
#include <functional>
#include "commonFunc.h"

using namespace std;

template<class others>
struct Record
{
	keyType key;
	others other_;
};

template<class others>
struct BiTNode
{
	int keynum;
	BiTNode<others> *parent;
	struct Node
	{
		keyType key;
		BiTNode<others> *ptr;
		Record<others> *recptr;
	}node[m+1];
};

template<class others>
struct Result
{
	BiTNode<others> *pt;
	int i;
	int tag;
};

#define BTNODE BiTNode<others>
#define BTree BiTNode<others>*
#define RECORD Record<others>
#define RESULT Result<others>

template<class others>
void initDSTable(BTree &DT)
{
	DT=NULL;
}

template<class others>
void destroyDSTable(BTree &DT)
{
	int i;
	if(DT)
	{
		for(i=0;i<=DT->keynum;++i)
			destroyDSTable(DT->node[i].ptr);
		free(DT);
		DT=NULL;
	}
}

template<class others>
int search(BTree p,keyType k)
{
	int i=0,j;
	for(j=1;j<=p->keynum;++j)
		if(p->node[j].key<=k)
			i=j;
	return i;
}

template<class others>
RESULT searchBTree(BTree Tr,keyType k)
{
	BTree p=Tr;
	BTree q=NULL;
	bool found = false;
	int i=0;
	RESULT r;
	while(p&&!found)
	{
		i=search(p,k);
		if(i>0&&p->node[i].key==k)
			found=true;
		else
		{
			q=p;
			p=p->node[i].ptr;
		}
	}
	r.i=i;
	if(found)
	{
		r.pt=p;
		r.tag=1;
	}
	else
	{
		r.pt=q;
		r.tag=0;
	}
	return r;
}

template<class others>
void insert(BTree &q,int i,RECORD *r,BTree ap)
{
	int j;
	for(j=q->keynum;j>i;--j) q->node[j+1]=q->node[j];
	q->node[i+1].key=r->key;
	q->node[i+1].ptr=ap;
	q->node[i+1].recptr=r;
	++q->keynum;
}

template<class others>
void split(BTree &q,BTree &ap)
{
	int i,s=(m+1)/2;
	ap=(BTree)malloc(sizeof(BTNODE));
	ap->node[0].ptr=q->node[s].ptr;
	for(i=s+1;i<=m;++i)
	{
		ap->node[i-s]=q->node[i];
		if(ap->node[i-s].ptr)
			ap->node[i-s].ptr->parent=ap;
	}
	ap->keynum=m-s;
	ap->parent=q->parent;
	q->keynum=s-1;
}

template<class others>
void newRoot(BTree &Tr,RECORD *r,BTree ap)
{
	BTree p;
	p=(BTree)malloc(sizeof(BTNODE));
	p->node[0].ptr=Tr;
	Tr=p;
	if(Tr->node[0].ptr) Tr->node[0].ptr->parent=Tr;
	Tr->parent=NULL;
	Tr->keynum=1;
	Tr->node[1].key=r->key;
	Tr->node[1].recptr=r;
	Tr->node[1].ptr=ap;
	if(Tr->node[1].ptr)
		Tr->node[1].ptr->parent=Tr;
}

template<class others>
void insertBTree(BTree &Tr,RECORD *r,BTree q,int i)
{
	BTree ap=NULL;
	bool finished=false;
	int s;
	RECORD *rx;
	rx=r;
	while(q&&!finished)
	{
		insert(q,i,rx,ap);
		if(q->keynum<m)
			finished=true;
		else
		{
			s=(m+1)/2;
			rx=q->node[s].recptr;
			split(q,ap);
			q=q->parent;
			if(q)
				i=search(q,rx->key);
		}
	}
	if(!finished)
		newRoot(Tr,rx,ap);
}

template<class others>
void traverseDSTable(BTree DT,const std::function<void(const BTNODE &,int)> &visit)
{
	int i;
	if(DT)
	{
		if(DT->node[0].ptr) traverseDSTable(DT->node[0].ptr,visit);
		for(i=1;i<=DT->keynum;++i)
		{
			visit(*DT,i);
			if(DT->node[i].ptr)
				traverseDSTable(DT->node[i].ptr,visit);
		}
	}
}
#endif // !__B_TREE__HH__
