#include "stdafx.h"

#include <iostream>

#include <fstream>
#include <stdio.h>
#include <string>

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

	testStaticList();

	cout<<"\n========================================================\n";
	LinkList LL;
	initList_SL(LL);

	for(int i=1;i<=20;++i)
		listInsert_SL(LL,i,i);
	listTraverse_SL(LL,vi_print);

	priorElem_SL(LL,18,e);
	cout<<e<<endl;

	nextElem_SL(LL,18,e);
	cout<<e<<endl;

	listDelete_SL(LL,2,e);
	cout<<e<<endl;
	listTraverse_SL(LL,vi_print);
	cout<<isEmpty_SL(LL)<<endl;
	clearList_SL(LL);
	cout<<isEmpty_SL(LL)<<endl;


	for(int i=1;i<=20;++i)
		listInsert_SL(LL,i,i);

	LinkList LLb;
	initList_SL(LLb);
	for(int i=1;i<=10;++i)
		listInsert_SL(LLb,i,i*i);
	listTraverse_SL(LLb,vi_print);
	listMerge_SL(LL,LLb);
	listTraverse_SL(LL,vi_print);

	cout<<"\n========================================================\n";
	DuLinkList DL;
	initList_Du(DL);
	for(int i=1;i<=15;++i)
		listInsert_Du(DL,i,i);
	listTraverse_Du(DL,vi_print);
	listTraverseBack_Du(DL,vi_print);

	listDelete_Du(DL,13,e);
	listTraverse_Du(DL,vi_print);
	listTraverseBack_Du(DL,vi_print);

	getElemByIndex_Du(DL,12,e);
	cout<<e<<endl;

	priorElem_Du(DL,12,e);
	cout<<e<<endl;

	nextElem_Du(DL,12,e);
	cout<<e<<endl;

	cout<<"\n===============REAL LIST LIKE THIS!!!===============================\n";
	RLinkList RL;
	initList_RL(RL);

	Link rp;
	for(int i=1;i<=9;++i)
	{
		makeNode(rp,i);
		insertFirst(RL,RL.tail,rp);
	}
	listTraverse_RL(RL,vi_print);

	orderInsert(RL,20,compare_absoluteless);
	orderInsert(RL,19,compare_absoluteless);
	orderInsert(RL,19,compare_absoluteless);
	orderInsert(RL,18,compare_absoluteless);
	orderInsert(RL,16,compare_absoluteless);
	orderInsert(RL,15,compare_absoluteless);
	listTraverse_RL(RL,vi_print);

	locateElemPos_RL(RL,200,rp,compare_equal1);
	cout<<rp->data<<endl;
	for(int j=1;j<=4;++j)
	{
		deleteFirst(RL,RL.head,rp);
		cout<<"delete: "<<rp->data<<endl;
		listTraverse_RL(RL,vi_print);
	}

	Link rh;
	makeNode(rp,100);
	rp->next=NULL;
	for(int j=4;j>=1;--j)
	{
		makeNode(rh,j*2);
		rh->next=rp;
		rp=rh;
	}
	appenList(RL,rh);
	listTraverse_RL(RL,vi_print);

	listInsert_RL(RL,5,999);
	listTraverse_RL(RL,vi_print);

	listBubbleSort_RL(RL,compare_less);
	listTraverse_RL(RL,vi_print);

	RLinkList RLb;
	initList_RL(RLb);

	for(int i=1;i<=9;++i)
	{
		makeNode(rp,i*i*i);
		insertFirst(RLb,RLb.tail,rp);
	}
	listTraverse_RL(RLb,vi_print);

	RLinkList RLc;
	listMerge_RL(RL,RLb,RLc,compare_less);
	listTraverse_RL(RLc,vi_print);

	listTraverse_RL(RL,vi_print);
	listTraverse_RL(RLb,vi_print);

	cout<<"\n===============POLYN TEST!!!===============================\n";
	polynomial P;
	createPolyn(P,"polyn.txt");
	printPolyn(P);

	polynomial P1;
	createPolyn(P1,"polyn.txt",2);
	printPolyn(P1);
	addPolyn(P,P1);

	printPolyn(P);

	polynomial P2;
	createPolyn(P2,"polyn.txt",3);
	addPolyn1(P,P2);
	printPolyn(P);


}





