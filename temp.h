

#pragma once

template<class T>
void testfunc(const T&);

//template<class T>
//void testfunc(const T& a)
//{
//	cout<<a<<endl;
//}

template<class T>
class theclass
{
	T a;
public:
	theclass();

	void show();
	void set(T var);
};

//////////////////////////////////////////////////////////////////////////

template<int ObjectSize,int NumberofObjects=20>
class MemPool
{
	const int MemBlockSize;
	const int ItemSize;
	struct _FreeNode
	{
		_FreeNode *pNext;
		char data[ObjectSize];
	};
	struct _MemBlock
	{
		_MemBlock *pNext;
		_FreeNode data[NumberofObjects];
	};

	_MemBlock * pMemBlockHeader;
	_FreeNode *pFreeNodeHeader;
public:
	MemPool()
		:ItemSize(ObjectSize+sizeof(_FreeNode*))
		,MemBlockSize(sizeof(_MemBlock*)+ NumberofObjects*(ObjectSize+sizeof(_FreeNode*)))
	{
		pMemBlockHeader=NULL;
		pFreeNodeHeader=NULL;
	}

	~MemPool()
	{
		_MemBlock *ptr;
		while(pMemBlockHeader)
		{
			ptr=pMemBlockHeader->pNext;
			delete pMemBlockHeader;
			pMemBlockHeader = ptr;
		}
	}

	void *malloc()
	{
		if(pFreeNodeHeader==NULL)
		{
			_MemBlock * pNewBlock = new _MemBlock;
			pNewBlock->data[0].pNext=NULL;
			for(int i=1;i<NumberofObjects;++i)
				pNewBlock->data[i].pNext = &pNewBlock->data[i-1];
			pFreeNodeHeader=&pNewBlock->data[NumberofObjects-1];
			pNewBlock->pNext = pMemBlockHeader;
			pMemBlockHeader = pNewBlock;
		}
		void * pFreeNode = pFreeNodeHeader;
		pFreeNodeHeader = pFreeNodeHeader->pNext;
		return pFreeNode;
	}

	void free(void *p)
	{
		_FreeNode * pNode = (_FreeNode*)p;
		pNode->pNext = pFreeNodeHeader;
		pFreeNodeHeader = pNode;
	}
};


