#ifndef __KEY_TREE__HH__
#define __KEY_TREE__HH__

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>
#include <functional>
#include "commonFunc.h"

using namespace std;

#define MAX_KEY_LEN 16
#define Nil ' '
struct keysType
{
	char ch[MAX_KEY_LEN];
	int num;
};

template<class Others>
struct Record
{
	keysType key;
	Others others;
};

enum NodeKind
{
	LEAF,
	BRANCH
};

template<class Others>
struct DLTNode
{
	char symbol;
	DLTNode<Others> *next;
	NodeKind kind;
	union
	{
		Record<Others> *infoptr;
		DLTNode<Others> *first;
	};
};

#define DLTNODE DLTNode<Others>
#define DLTree DLTNode<Others>*
#define RECORD Record<Others>

template<class Others>
void initDSTable(DLTree &DT)
{
	DT=NULL;
}

template<class Others>
void destroyDSTable(DLTree &DT)
{
	if(DT)
	{
		if(DT->kind==BRANCH&&DT->first) destroyDSTable(DT->first);
		if(DT->next) destroyDSTable(DT->next);
		free(DT);
		DT=NULL;
	}
}

template<class Others>
RECORD *searchDLTree(DLTree T,keysType k)
{
	DLTree p;
	int i;
	if(T)
	{
		p=T;
		i=0;
		while(p&&i<k.num)
		{
			while(p&&p->symbol!=k.ch[i])
				p=p->next;
			if(p&&i<k.num)
				p=p->first;
			++i;
		}
		if(!p) return NULL;
		else return p->infoptr;
	}
	else return NULL;
}

template<class Others>
void insertDSTable(DLTree &DT,RECORD *r)
{
	DLTree p=NULL;
	DLTree q=NULL;
	DLTree ap=NULL;
	int i=0;
	keysType k = r->key;
	if(!DT&&k.num)
	{
		DT=ap=(DLTree)malloc(sizeof(DLTNODE));
		for(;i<k.num;++i)
		{
			if(p) p->first=ap;
			ap->next=NULL;
			ap->symbol=k.ch[i];
			ap->kind=BRANCH;
			p=ap;
			ap=(DLTree)malloc(sizeof(DLTNODE));
		}
		p->first=ap;
		ap->next=NULL;
		ap->symbol=Nil;
		ap->kind=LEAF;
		ap->infoptr=r;
	}
	else
	{
		p=DT;
		while(p&&i<k.num)
		{
			while(p&&p->symbol<k.ch[i])
			{
				q=p;
				p=p->next;
			}
			if(p&&p->symbol==k.ch[i])
			{
				q=p;
				p=p->first;
				++i;
			}
			else
			{
				ap=(DLTree)malloc(sizeof(DLTNODE));
				if(q->first==p) q->first=ap;
				else q->next=ap;
				ap->next=p;
				ap->symbol=k.ch[i];
				ap->kind=BRANCH;
				p=ap;
				ap=(DLTree)malloc(sizeof(DLTNODE));
				++i;
				for(;i<k.num;++i)
				{
					p->first=ap;
					ap->next=NULL;
					ap->symbol=k.ch[i];
					ap->kind=BRANCH;
					p=ap;
					ap=(DLTree)malloc(sizeof(DLTNODE));
				}
				p->first=ap;
				ap->next=NULL;
				ap->symbol=Nil;
				ap->kind=LEAF;
				ap->infoptr=r;
			}
		}
	}
}

template<class Others>
struct ud
{
	char ch;
	DLTree p;
};

#include "stackCommon.h"
#define SElem ud<Others>
#define SQSTACK SqStack<SElem>

template<class Others>
void traverseDSTable(DLTree DT,const std::function<void(const RECORD&)> &func)
{
	SQSTACK s;
	SElem e;
	DLTree p;
	int i=0,n=8;
	if(DT)
	{
		initStack(s);
		e.p=DT;
		e.ch=DT->symbol;
		pushStack(s,e);
		p=DT->first;
		while(p->kind==BRANCH)
		{
			e.p=p;
			e.ch=p->symbol;
			pushStack(s,e);
			p=p->first;
		}
		e.p=p;
		e.ch=p->symbol;
		pushStack(s,e);
		func(*(p->infoptr));
		++i;
		while(!isStackEmpty(s))
		{
			popStack(s,e);
			p=e.p;
			if(p->next)
			{
				p=p->next;
				while(p->kind==BRANCH)
				{
					e.p=p;
					e.ch=p->symbol;
					pushStack(s,e);
					p=p->first;
				}
				e.p=p;
				e.ch=p->symbol;
				pushStack(s,e);
				func(*(p->infoptr));
				++i;
				if(i%n==0) printf("\n");
			}
		}
	}
}
#endif // !__KEY_TREE__HH__
