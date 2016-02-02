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

typedef char ElemType1;
typedef struct
{
	ElemType1 data[20];
	int cur;
}component,sLinkList[100];

//静态链表相关测试
void testStaticList();

//构造一个空的线性表
void initList_SL(LinkList &L);

//销毁线性表
void destroyList_SL(LinkList &L);

//将L置空
void clearList_SL(LinkList &L);

//判断L是否为空
bool isEmpty_SL(LinkList &L);

//取得表长
int listLength_SL(LinkList &L);

//获取第i个元素
bool getElemByIndex_SL(LinkList &L,int i,ElemType &e);

//是数据元素的判定 返回L中第1个与e满足compare()关系的数据元素位序
int locateElem_SL(LinkList &L,ElemType e,compare_func cFunc);

//找到cur_e的前驱
bool priorElem_SL(LinkList &L,ElemType cur_e,ElemType &pre_e);

//找到cur_e的后继
bool nextElem_SL(LinkList &L,ElemType cur_e,ElemType &next_e);

//在i位置插入e
bool listInsert_SL(LinkList &L,int i,ElemType e);

//删除第i个位置元素
bool listDelete_SL(LinkList &L,int i,ElemType &e);

//遍历L
void listTraverse_SL(LinkList &L,vi_func vFunc);

//将Lb合并到La的表尾
void listMerge_SL(LinkList &La,LinkList &Lb);

//==========双向链表
typedef struct DuLNode
{
	ElemType data;
	DuLNode *prior,*next;
}DuLNode,*DuLinkList;

//创建空表
void initList_Du(DuLinkList &L);

//销毁表
void destroyList_Du(DuLinkList &L);

//重置表
void clearList_Du(DuLinkList &L);

//判断是否表空
bool isEmpty_Du(DuLinkList &L);

///获取表长度
int listLength_Du(DuLinkList &L);

//获取位置i的元素
bool getElemByIndex_Du(DuLinkList &L,int i,ElemType &e);

//返回第1 个与e满足compare关系的数据
int locateElem_Du(DuLinkList &L,ElemType e,compare_func cFunc);

//返回cur_e 的前驱
bool priorElem_Du(DuLinkList &L,ElemType cur_e,ElemType &pre_e);

//返回cur_e 的后继
bool nextElem_Du(DuLinkList &L,ElemType cur_e,ElemType &next_e);

//返回第i个元素所在地址
DuLinkList findElemByIndex_Du(DuLinkList &L,int i);

//在位置i插入e
bool listInsert_Du(DuLinkList &L,int i,ElemType e);

//删除位置i 的元素
bool listDelete_Du(DuLinkList &L,int i,ElemType &e);

//遍历表
void listTraverse_Du(DuLinkList &L,vi_func vFunc);

//逆序遍历表
void listTraverseBack_Du(DuLinkList &L,vi_func vFunc);
#endif