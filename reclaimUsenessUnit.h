#ifndef __RECLAIMUSENESSUNIT__HH__
#define __RECLAIMUSENESSUNIT__HH__
#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;

enum ElemTag
{
	ATOM,
	LIST
};

typedef struct GLNode
{
	int mark;
	ElemTag tag;
	union
	{
		AtomType atom;
		struct
		{
			GLNode *hp,*tp;
		}ptr;
	};
}*GList,GLNode;
#endif