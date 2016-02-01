#include "stdafx.h"
#include <malloc.h>
#include <process.h>
#include <math.h>
#include <fstream>
#include "testLinkList.h"



//构造空的线性表
void initList(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	if(!L) exit(OVERFLOW);
	L->next=NULL;
}

//销毁线性表
void destroyList(LinkList &L)
{
	LinkList q;
	while(L)
	{
		q=L->next;
		free(L);
		L=q;
	}
}

//将L重置为空表
void clearList(LinkList &L)
{
	LinkList p=L->next,q;
	while(p)
	{
		q=p->next;
		free(p);
		p=q;
	}
	L->next=NULL;
}

//表是否为空
bool isEmpty(LinkList &L)
{
	if(L->next) return false;
	else return true;
}

//返回表长
int listLength(LinkList &L)
{
	int i=0;
	LinkList p=L->next;
	while(p)
	{
		++i;
		p=p->next;
	}
	return i;
}

//获取位置i的元素
bool getElemByIndex(LinkList &L,int i,ElemType &e)
{
	int j=1;
	LinkList p = L->next;
	while(p&&j<i)
	{
		p=p->next;
		++j;
	}
	if(!p||j>i) return false;
	e = p->data;
	return true;
}

//找到位置i的元素
LinkList findElemByIndex(LinkList &L,int i)
{
	int j=1;
	LinkList p = L->next;
	while(p&&j<i)
	{
		p=p->next;
		++j;
	}
	if(!p||j>i) return  L->next;
	
	return p;
}

//是数据元素的判定 返回L中第1个与e满足compare()关系的数据元素位序
int locateElem(LinkList &L,ElemType e,compare_func cFunc)
{
	int i=0;
	LinkList p=L->next;
	while(p)
	{
		++i;
		if(cFunc(p->data,e)) return i;
		p = p->next;
	}
	return 0;
}

//返回cur_e的前驱
bool priorElem(LinkList &L,ElemType cur_e,ElemType &pre_e)
{
	LinkList q,p=L->next;
	while(p->next)
	{
		q=p->next;
		if(q->data==cur_e)
		{
			pre_e=p->data;
			return true;
		}
		p=q;
	}
	return false;
}

//返回cur_e的后继
bool nextElem(LinkList &L,ElemType cur_e,ElemType &next_e)
{
	LinkList p=L->next;
	while(p->next)
	{
		if(p->data==cur_e)
		{
			next_e = p->next->data;
			return true;
		}
		p=p->next;
	}
	return false;
}

//在位置i插入e
bool listInsert(LinkList &L,int i,ElemType e)
{
	LinkList p;
	if(listLength(L)<=0)
	{
		p = L;
	}
	else
	{
		--i;
		i = mymin(mymax(1,i),listLength(L));
		p = findElemByIndex(L,i);
		if(!p) return false;
	}
	
	LinkList t = (LinkList)malloc(sizeof(LNode));
	t->data = e;
	t->next = p->next;
	p->next = t;
	return true;
}

//删除位置i元素
bool listDelete(LinkList &L,int i,ElemType &e)
{
	i = mymin(mymax(1,i),listLength(L));
	LinkList p = findElemByIndex(L,i-1);
	if(!p) return false;
	LinkList t = p->next;
	p->next = p->next->next;
	e = t->data;
	free(t);
	return true;
}

//遍历list
void listTraverse(LinkList &L,vi_func vFunc)
{
	LinkList p=L->next;
	while(p)
	{
		vFunc(p->data);
		p=p->next;
	}
	printf("\n");
}

//求la lb 并集
void listUnion(LinkList &La,LinkList &Lb)
{
	int aLen=listLength(La),bLen=listLength(Lb);
	ElemType e;
	for(int i=1;i<=bLen;++i)
	{
		getElemByIndex(Lb,i,e);
		if(!locateElem(La,e,compare_equal)) listInsert(La,++aLen,e);
	}
}

//冒泡排序
void listBubleSort(LinkList &L,compare_func cFunc)
{
	if(isEmpty(L)) return;
	LinkList p = L->next;
	
	LinkList q;
	ElemType temp;
	while(p)
	{
		q = p->next;
		while(q)
		{
			if(!cFunc(p->data,q->data))
			{
				temp = p->data;
				p->data = q->data;
				q->data = temp;
			}
			q = q->next;
		}
		p = p->next;
	}
}

//按la,lb有序归并为lc
void listMerge(LinkList &La,LinkList &Lb,LinkList &Lc)
{
	int aLen = listLength(La),bLen=listLength(Lb);
	ElemType ai,bj;
	initList(Lc);
	int i=1,j=1,k=0;
	while(i<=aLen && j<=bLen)
	{
		getElemByIndex(La,i,ai);
		getElemByIndex(Lb,j,bj);
		if(ai<=bj)
		{
			listInsert(Lc,++k,ai);
			++i;
		}
		else
		{
			listInsert(Lc,++k,bj);
			++j;
		}
	}

	while(i<=aLen)
	{
		getElemByIndex(La,i++,ai);
		listInsert(Lc,++k,ai);
	}
	while(j<=bLen)
	{
		getElemByIndex(Lb,j++,bj);
		listInsert(Lc,++k,bj);
	}
}

//按la,lb有序归并为lc
void listMerge2(LinkList &La,LinkList &Lb,LinkList &Lc)
{
	LinkList pa=La->next,pb=Lb->next,pc;
	Lc=pc=La;

	while(pa&&pb)
	{
		if(pa->data<=pb->data )
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}

	pc->next=pa?pa:pb;
}

//从文件里读取数据创建表
void createListWithFile(LinkList &L,const char * fileName)
{
	using namespace std;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	LinkList p;
	ifstream fin(fileName);
	if(fin.is_open())
	{
		ElemType e;
		while(fin>>e)
		{
			p = (LinkList)malloc(sizeof(LNode));
			p->data = e;
			p->next = L->next;
			L->next = p;
		}
	}
}

//从文件里读取数据创建表
void createListWithFile2(LinkList &L,const char * fileName)
{
	using namespace std;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	LinkList p,q=L;
	ifstream fin(fileName);
	if(fin.is_open())
	{
		ElemType e;
		while(fin>>e)
		{
			p = (LinkList)malloc(sizeof(LNode));
			p->data = e;
			p->next=NULL;
			q->next = p;
			q = q->next;
		}
	}
}