#ifndef __INSERTSORT__HH__
#define __INSERTSORT__HH__
#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>
#include <functional>
#include "commonFunc.h"

using namespace std;

#define MAX_SIZE 20
typedef int keyType;

template<class IT>
struct RedType
{
	keyType key;
	IT otherinfo;
};

#define RDT RedType<IT>

template<class IT>
struct SqList
{
	RDT r[MAX_SIZE+1];
	int length;
};

#define SQLIST SqList<IT>

template<class IT>
void insertSort(SQLIST &L)
{
	int i,j;
	for(i=2;i<=L.length;++i)
		if LT(L.r[i].key,L.r[i-1].key)
		{
			L.r[0]=L.r[i];
			for(j=i-1;LT(L.r[0].key,L.r[j].key);--j)
				L.r[j+1]=L.r[j];
			L.r[j+1]=L.r[0];
		}
}

template<class IT>
void BInsertSort(SQLIST &L)
{
	int i,j,m,low,high;
	for(i=2;i<=L.length;++i)
	{
		L.r[0]=L.r[i];
		low=1;
		high=i-1;
		while(low<=high)
		{
			m=(low+high)/2;
			if LT(L.r[0].key,L.r[m].key)
				high=m-1;
			else
				low=m+1;
		}
		for(j=i-1;j>=high+1;--j)
			L.r[j+1]=L.r[j];
		L.r[high+1]=L.r[0];
	}
}

template<class IT>
void p2_insertSort(SQLIST &L)
{
	int i,j,first,final_;
	RDT *d;
	d=(RDT*)malloc(sizeof(RDT)*L.length);
	d[0]=L.r[1];
	first=final_=0;
	for(i=2;i<=L.length;++i)
		if(L.r[i].key<d[first].key)
		{
			first=(first-1+L.length)%L.length;
			d[first]=L.r[i];
		}
		else if(L.r[i].key>d[final_].key)
		{
			++final_;
			d[final_]=L.r[i];
		}
		else
		{
			j=final_++;
			while(L.r[i].key<d[j].key)
			{
				d[(j+1)%L.length]=d[j];
				j=(j-1+L.length)%L.length;
			}
			d[j+1]=L.r[i];
		}
	for(i=1;i<=L.length;++i)
		L.r[i]=d[(i+first-1)%L.length];
}

#endif // !__INSERTSORT__HH__
