#ifndef __STACK_COMMON__HH__
#define __STACK_COMMON__HH__
#include <functional>

#define STACK_INIT_SIZE  80
#define STACK_INC_SIZE  20

template<class SElemType>
struct SqStack
{
	SElemType *top,*base;
	int stackSize;
};


#define SQSTACK SqStack<SElemType>

template<class SElemType>
void initStack(SQSTACK &S)
{
	if(! (S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType))))
	{
		exit(OVERFLOW);
	}
	S.top=S.base;
	S.stackSize=STACK_INIT_SIZE;
}

template<class SElemType>
void destroyStack(SQSTACK &S)
{
	free(S.base);
	S.base=NULL;
	S.top=NULL;
	S.stackSize=0;
}

template<class SElemType>
void clearStack(SQSTACK &S)
{
	S.top=S.base;
}

template<class SElemType>
bool isStackEmpty(SQSTACK &S)
{
	if(S.top==S.base) return true;
	return false;
}

template<class SElemType>
int stackLength(SQSTACK &S)
{
	return S.top-S.base;
}

template<class SElemType>
bool getTop(SQSTACK &S,SElemType &e)
{
	if(S.top>S.base)
	{
		e=*(S.top-1);
		return true;
	}
	return false;
}

template<class SElemType>
void pushStack(SQSTACK &S,SElemType e)
{
	if(S.top-S.base>=S.stackSize)
	{
		//Õ»Âú×·¼Ó
		S.base=(SElemType*)realloc(S.base,(S.stackSize+STACK_INC_SIZE)*sizeof(SElemType) );
		if(!S.base) exit(OVERFLOW);
		S.top=S.base+S.stackSize;
		S.stackSize+=STACK_INC_SIZE;
	}
	*(S.top)++=e;
}

template<class SElemType>
bool popStack(SQSTACK &S,SElemType &e)
{
	if(S.top==S.base) return false;
	e=*--S.top;
	return true;
}

template<class SElemType>
void stackTraverse(SQSTACK S,std::function<void(const SElemType&)> &vFunc)
{
	while(S.top>S.base)
		vFunc(*S.base++);
	printf("\n");
}

#endif // !__STACK_COMMON__HH__
