#ifndef __DYMEMORY__H__
#define __DYMEMORY__H__

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>
using namespace std;

typedef struct _WORD
{
	union
	{
		_WORD *llink;
		_WORD *uplink;
	};
	int tag;
	int size;
	_WORD *rlink;
}_WORD,head,foot,*Space;

#define FootLoc(p) p+p->size-1


#endif