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

#endif // !__INSERTSORT__HH__
