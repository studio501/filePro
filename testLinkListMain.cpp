#include "stdafx.h"

#include <iostream>

#include <fstream>
#include <stdio.h>

#include "testLinkList.h"

using namespace std;

const char * listfile = "list.txt";

void vi_print(ElemType &a);

bool compare_equal1(ElemType a,ElemType b);

bool compare_less(ElemType a,ElemType b);

void vi_saveToFile(ElemType &a)
{
	ofstream fout(listfile,ios_base::out | ios_base::app);
	if(!fout.is_open())
	{
		cerr<<"can't open "<<listfile<<" to write.\n";
		exit(0);
	}
	fout<<a<<" ";
	fout.close();
}

void testLinkListMain()
{
	LinkList L;
	initList(L);
	for(int i=1;i<=15;++i)
		listInsert(L,i,i);
	listTraverse(L,vi_print);

	ElemType e;
	getElemByIndex(L,10,e);
	cout<<e<<endl;

	ElemType e1;
	priorElem(L,e,e1);
	cout<<e1<<endl;

	nextElem(L,e,e1);
	cout<<e1<<endl;

	listDelete(L,12,e1);
	listTraverse(L,vi_print);

	LinkList Lb;
	initList(Lb);
	for(int i=1;i<=20;++i)
		listInsert(Lb,i,i*2);
	listUnion(L,Lb);
	listTraverse(L,vi_print);

	listBubleSort(L,compare_less);
	listTraverse(L,vi_print);

	LinkList Lc;
	//listMerge(L,Lb,Lc);
	listMerge2(L,Lb,Lc);
	listTraverse(Lc,vi_print);

	remove(listfile);
	listTraverse(Lc,vi_saveToFile);

	LinkList Ld;
	createListWithFile(Ld,listfile);
	listTraverse(Ld,vi_print);

	LinkList Le;
	createListWithFile2(Le,listfile);
	listTraverse(Le,vi_print);
}


