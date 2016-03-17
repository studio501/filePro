#ifndef __TEST_LIST__HH_
#define __TEST_LIST__HH_

#include "listConfig.h"

const int LIST_INIT_SIZE = 10;
const int LIST_INCREMENT = 8;

struct SqList
{
	ElemType *elem;
	int length;
	int listSize;
};

//构造一个空的顺序线性表
void initList(SqList &L);

//销毁一个线性表
void destroyList(SqList &L);

//顺序表已经存在将表重置为空表
void clearList(SqList &L);

//判断是否为空表
bool isEmpty(SqList &L);

//获取表长度
int getListLen(SqList &L);

//检查index是否合法
bool checkIndex(SqList &L,int index);

//返回L中第i个数据元素的值
bool getElemByIndex(SqList &L,int i,ElemType &e);

//返回L中第i个数据元素的值
ElemType *findElemByIndex(SqList &L,int i);

//是数据元素的判定 返回L中第1个与e满足compare()关系的数据元素位序
int locateElem(SqList &L,ElemType e,compare_func func);

//返回前一个元素 当前元素不能是第一个
bool priorElem(SqList &L,ElemType cur_e,ElemType &pre_e);

//返回下一个元素 当前元素不能是最后一个
bool nextElem(SqList &L,ElemType cur_e,ElemType &next_e);

//在L的第i个位置插入新的元素e,L的长度加1
bool listInsert(SqList &L,int i,ElemType e);

//删除L的第i个元素
bool listDelete(SqList &L,int i,ElemType &e);

//遍历表 对元素使用vi操作
void listTraverse(SqList &L,vi_func vFunc);

//对表进行冒泡排序
void listBubbleSort(SqList &L,compare_func cFunc );

//La和Lb合并
void listUnion(SqList &La,SqList &Lb);

//la,lb 有序 归并为lc后仍有序
void listMerge(SqList &La,SqList &Lb,SqList &Lc);

//la,lb 有序 归并为lc后仍有序
void listMerge1(SqList &La,SqList &Lb,SqList &Lc);


#endif