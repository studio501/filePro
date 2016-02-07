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
bool compare_less(ElemType a,ElemType b);
bool compare_absoluteless(ElemType a,ElemType b);

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

//====================================实际应用中的链表====================================

//实际应用中的链表
typedef LNode *Link,*Position;
struct RLinkList
{
	Link head,tail;//分别指向头,尾结点
	int len;//表中元素个数
};

//分配由p指向的值为e的结点
void makeNode(Link &p,ElemType e);

//释放p所指的结点
void freeNode(Link &p);

//构造一个空的线性表
void initList_RL(RLinkList &L);

//将表L重置为空
void clearList_RL(RLinkList &L);

//销毁线性表L
void destroyList_RL(RLinkList &L);

//h指向L的一个结点,把h当做头结点,将s所指结点插入在第一个结点之前
void insertFirst(RLinkList &L,Link h,Link s);

//h指向L的一个结点,把h当做头结点,删除链表中的第一个结点并以q返回
bool deleteFirst(RLinkList &L,Link h,Link &q);

//将s所指的一串结点链接在L的最后一个结点之后,并改变链表尾指针指向新的结点
void appenList(RLinkList &L,Link s);

//返回p指向的前驱位置
Position priorPos(RLinkList &L,Link p);

//删除尾结点并以q返回,改变L的尾指针指向新的尾结点
bool removeList_RL(RLinkList &L,Link &q);

//s所指结点插入p所指结点之前
void insBefore(RLinkList &L,Link &p,Link s);

//s所指结点插入p所指结点之后
void insAfter(RLinkList &L,Link &p,Link s);

//用e更新p所指的结点
void setCurElem(Link p,ElemType e);

//获取p所指向的元素
ElemType getCurElem(Link p);

//判断L是否为空表
bool isEmpty_RL(RLinkList &L);

//获取L的头结点
Position getHead(RLinkList L);

//获取L的尾结点
Position getTail(RLinkList L);

//下一个位置
Position nextPos(Link p);

//返回第i个结点的指针
bool locatePos(RLinkList L,int i,Link &p);

//返回线性表中第1个与e满足函数compare判定关系元素的位置
Position locateElem_RL(RLinkList L,ElemType e,compare_func cFunc);

//遍历L
void listTraverse_RL(RLinkList L,vi_func vFunc);

//按序插入e
void orderInsert(RLinkList &L,ElemType e,compare_func cFunc);

//返回第一个与e满足判定函数的结点位置
bool locateElemPos_RL(RLinkList L,ElemType e,Position &q,compare_func cFunc);

//在第i个元素位置插入e
bool listInsert_RL(RLinkList &L,int i,ElemType e);

//对表使用冒泡排序
void listBubbleSort_RL(RLinkList &L,compare_func cFunc);

//有序归并为新表
void listMerge_RL(RLinkList &La,RLinkList &Lb,RLinkList &Lc,compare_func cFunc);

//====================================一元多项式应用====================================
typedef struct 
{
	float coef;//系数
	int expn;//指数
}term,PoElemType;

struct LPNode
{
	PoElemType data;
	LPNode *next;
};
typedef LPNode * LPLinkList;
typedef LPNode *LPLink,*LPPosition;

struct LPRLinkList
{
	LPLink head,tail;//分别指向头,尾结点
	int len;//表中元素个数
};
typedef LPRLinkList polynomial;
typedef int (*compare_term_func)(term,term);
int compare_term_status(term a,term b); //<:-1 =:0 >1

//分配由p指向的值为e的结点
void makeNode_RLP(LPLink &p,PoElemType e);

//释放p所指的结点
void freeNode_RLP(LPLink &p);

//创建一个空表
void initList_RLP(LPLink &p);

//将表L重置为空
void clearList_RLP(polynomial &L);

//判断一个表是否为空表
bool isEmpty_RLP(polynomial p);

//销毁线性表L
void destroyList_RLP(polynomial &L);

//用pb 扩展pa
void appenList_RLP(polynomial Pa,LPLink p);

//h指向L的一个结点,把h当做头结点,将s所指结点插入在第一个结点之前
void insertFirst_RLP(LPRLinkList &L,LPLink h,LPLink s);

//h指向L的一个结点,把h当做头结点,删除链表中的第一个结点并以q返回
bool deleteFirst_RLP(LPRLinkList &L,LPLink h,LPLink &q);

//返回p指向的前驱位置
LPPosition priorPos_RLP(LPRLinkList &L,LPLink p);

//返回第一个与e满足判定函数的结点位置
bool locateElemPos_RLP(LPRLinkList L,PoElemType e,LPPosition &q,compare_term_func cFunc);

//将e 放置到表中合适的位置
void orderInsertMerge(LPRLinkList &L,PoElemType e,compare_term_func cFunc); 

//输入多项式所在文件和行号,建立表示一元多项的有序链表p
void createPolyn(polynomial &P,const char *fileName,int mLine =1);

//打印多项式
void printPolyn(polynomial P);

//两个多项相加
void addPolyn(polynomial &Pa,polynomial &Pb);

//另一种两人个多项式相加的方法
void addPolyn1(polynomial &Pa,polynomial &Pb);
#endif