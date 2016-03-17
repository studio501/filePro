
#include "stdafx.h"

#include <malloc.h>
#include <process.h>
#include <math.h>
#include "testList.h"

bool compare_equal(ElemType a,ElemType b)
{
	return a == b;
}



//构造一个空的顺序线性表
void initList(SqList &L)
{
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem) exit(OVERFLOW);

	L.length = 0;
	L.listSize = LIST_INIT_SIZE;
}

//销毁一个线性表
void destroyList(SqList &L)
{
	free(L.elem);
	L.elem = NULL;
	L.length = 0;
	L.listSize = 0;
}

//顺序表已经存在将表重置为空表
void clearList(SqList &L)
{
	L.length = 0;
}

//判断是否为空表
bool isEmpty(SqList &L)
{
	if (L.length > 0) return false;
	else return true;
}

//获取表长度
int getListLen(SqList &L)
{
	return L.length;
}

//检查index是否合法
bool checkIndex(SqList &L,int index)
{
	if (isEmpty(L)) return false;
	if(index <1 || index > getListLen(L)) return false;
	return true;
}

//返回L中第i个数据元素的值
bool getElemByIndex(SqList &L,int i,ElemType &e)
{
	i = mymin( mymax(1,i),L.length );
	e = *(L.elem + i-1);
	return true;
}

//返回L中第i个数据元素的值
ElemType* findElemByIndex(SqList &L,int i)
{
	i = mymin( mymax(1,i),L.length );
	return (L.elem + i-1);
}

//是数据元素的判定 返回L中第1个与e满足compare()关系的数据元素位序
int locateElem(SqList &L,ElemType e,compare_func func)
{
	ElemType *p = L.elem;
	int i=1;

	while(i<=L.length && !func(*p++,e)) ++i;

	if (i<=L.length) return i;
	else return 0;
}

//返回前一个元素 当前元素不能是第一个
bool priorElem(SqList &L,ElemType cur_e,ElemType &pre_e)
{
	int index = locateElem(L,cur_e,compare_equal);
	index = mymax(1,index -1);
	getElemByIndex(L,index,pre_e);
	return true;
}

//返回下一个元素 当前元素不能是最后一个
bool nextElem(SqList &L,ElemType cur_e,ElemType &next_e)
{
	int index = locateElem(L,cur_e,compare_equal);
	index = mymin(index+1,L.length);
	getElemByIndex(L,index,next_e);
	return true;
}

//在L的第i个位置插入新的元素e,L的长度加1
bool listInsert(SqList &L,int i,ElemType e)
{
	ElemType *newbase,*p,*q;
	if(i<1 || i>L.length+1) return false;

	if(L.length>=L.listSize)
	{
		if(!(newbase = (ElemType*)realloc(L.elem,(L.listSize+LIST_INCREMENT)*sizeof(ElemType)))) exit(OVERFLOW);
		L.elem = newbase;
		L.listSize += LIST_INCREMENT;
	}

	q = L.elem + i-1;//q为插入位置
	for(p=L.elem+L.length-1;p>=q;--p)
	{
		*(p+1) = *p;
	}
	*q = e;//插入e
	++L.length;
	return true;
}

//删除L的第i个元素
bool listDelete(SqList &L,int i,ElemType &e)
{
	if(!checkIndex(L,i)) return false;

	ElemType *p,*q;
	p = L.elem+i-1;
	e = *p;
	q = L.elem+L.length -1;
	for(++p;p<=q;++p)
		*(p-1) = *p;
	--L.length;
	return true;
}

//遍历表 对元素使用vi操作
void listTraverse(SqList &L,vi_func vFunc)
{
	ElemType *p=L.elem;
	for(int i=1;i<=L.length;++i)
		vFunc(*p++);
	printf("\n");
}

//对表进行冒泡排序
void listBubbleSort(SqList &L,compare_func cFunc )
{
	if(isEmpty(L)) return;
	ElemType temp,*ei,*ej;
	for(int i=1;i<=L.length;++i)
	{
		ei = findElemByIndex(L,i);
		for(int j=i+1;j<=L.length;++j)
		{
			ej = findElemByIndex(L,j);
			if(!cFunc(*ei,*ej))
			{
				temp = *ei;
				*ei = *ej;
				*ej = temp;
			}
		}
	}
}

//La和Lb合并
void listUnion(SqList &La,SqList &Lb)
{
	int aLen=La.length,bLen=Lb.length;
	ElemType e;
	for(int i=1;i<=bLen;++i)
	{
		getElemByIndex(Lb,i,e);
		if(!locateElem(La,e,compare_equal)) listInsert(La,++aLen,e);
	}
}

//la,lb 有序 归并为lc后仍有序
void listMerge(SqList &La,SqList &Lb,SqList &Lc)
{
	initList(Lc);
	int aLen=La.length,bLen=Lb.length;
	int i=1,j=1,k=0;
	ElemType ai,bj;
	while(i<=aLen && j<=bLen)
	{
		getElemByIndex(La,i,ai);
		getElemByIndex(Lb,j,bj);
		if(ai<=bj)
		{
			listInsert(Lc,++k,ai);
			++i;
		}
		else {listInsert(Lc,++k,bj);++j;}
	}

	while(i<=aLen)
	{
		getElemByIndex(La,i++,ai);
		listInsert(Lc,++k,ai);
	}

	while(j<=bLen)
	{
		getElemByIndex(Lb,j++,bj);
		listInsert(Lc,++k,bj);
	}
}

//la,lb 有序 归并为lc后仍有序
void listMerge1(SqList &La,SqList &Lb,SqList &Lc)
{
	ElemType *pa = La.elem,*pb=Lb.elem,*pc;
	ElemType *pa_last = pa + La.length-1,*pb_last=pb+Lb.length-1;
	Lc.listSize = Lc.length = La.length+Lb.length;
	pc=Lc.elem=(ElemType*)malloc(Lc.listSize*sizeof(ElemType));
	if(!Lc.elem) exit(OVERFLOW);

	while(pa<=pa_last && pb<=pb_last)
	{
		if(*pa<=*pb) *pc++=*pa++;
		else *pc++=*pb++;
	}
	while(pa<=pa_last) *pc++=*pa++;
	while(pb<=pb_last) *pc++=*pb++;
}
