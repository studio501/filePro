#ifndef __TEST_LINKLIST__HH__
#define __TEST_LINKLIST__HH__

#include "listConfig.h"

struct LNode
{
	ElemType data;
	LNode *next;
};
typedef LNode * LinkList;

bool compare_equal(ElemType a,ElemType b);

//构造空的线性表
void initList(LinkList &L);

//销毁线性表
void destroyList(LinkList &L);

//将L重置为空表
void clearList(LinkList &L);

//表是否为空
bool isEmpty(LinkList &L);

//返回表长
int listLength(LinkList &L);

//获取位置i的元素
bool getElemByIndex(LinkList &L,int i,ElemType &e);

//找到位置i的元素
LinkList findElemByIndex(LinkList &L,int i);

//是数据元素的判定 返回L中第1个与e满足compare()关系的数据元素位序
int locateElem(LinkList &L,ElemType e,compare_func cFunc);

//返回cur_e的前驱
bool priorElem(LinkList &L,ElemType cur_e,ElemType &pre_e);

//返回cur_e的后继
bool nextElem(LinkList &L,ElemType cur_e,ElemType &next_e);

//在位置i插入e
bool listInsert(LinkList &L,int i,ElemType e);

//删除位置i元素
bool listDelete(LinkList &L,int i,ElemType &e);

//遍历list
void listTraverse(LinkList &L,vi_func vFunc);

//求la lb 并集
void listUnion(LinkList &La,LinkList &Lb);

//冒泡排序
void listBubleSort(LinkList &L,compare_func cFunc);

//按la,lb有序归并为lc
void listMerge(LinkList &La,LinkList &Lb,LinkList &Lc);

//按la,lb有序归并为lc
void listMerge2(LinkList &La,LinkList &Lb,LinkList &Lc);

//从文件里读取数据创建表
void createListWithFile(LinkList &L,const char * fileName);

//从文件里读取数据创建表
void createListWithFile2(LinkList &L,const char * fileName);
#endif