#ifndef __DYMEMORY1__H__
#define __DYMEMORY1__H__

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>
using namespace std;

#define m 10
typedef struct WORD_b
{
	WORD_b *llink;
	int tag;
	int kval;
	WORD_b *rlink;
}WORD_b,head,*Space_b;

typedef struct HeadNode
{
	int nodesize;
	WORD_b *first;
}FreeList[m+1];


#endif