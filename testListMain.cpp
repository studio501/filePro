#include "stdafx.h"

#include <iostream>

#include "testList.h"

using namespace std;


void vi_print(ElemType &a)
{
	cout<<a<<" ";
}

void vi_double(ElemType &a)
{
	a*=2;
}

bool compare_equal1(ElemType a,ElemType b)
{
	return a == b;
}

bool compare_less(ElemType a,ElemType b)
{
	return a <= b;
}

bool compare_absoluteless(ElemType a,ElemType b)
{
	return a < b;
}

void testListMain()
{
	SqList L;
	initList(L);
	for(int i=1;i<=5;++i) listInsert(L,1,i);
	listTraverse(L,vi_print);

	clearList(L);
	listTraverse(L,vi_print);

	for(int i=1;i<=12;++i) listInsert(L,i,i);
	listTraverse(L,vi_print);

	listTraverse(L,vi_double);
	listTraverse(L,vi_print);

	cout<<locateElem(L,44,compare_equal1)<<endl;

	int e;
	priorElem(L,20,e);
	cout<<e<<endl;

	nextElem(L,20,e);
	cout<<e<<endl;

	listDelete(L,10,e);
	listTraverse(L,vi_print);
	
	SqList Lb;
	initList(Lb);
	for(int i=1;i<=15;++i)
		listInsert(Lb,i,i);

	listUnion(L,Lb);
	listTraverse(L,vi_print);

	listBubbleSort(L,compare_less);
	listTraverse(L,vi_print);

	SqList Lc;
	//listMerge(L,Lb,Lc);
	listMerge1(L,Lb,Lc);
	listTraverse(Lc,vi_print);
}

