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

//����յ����Ա�
void initList(LinkList &L);

//�������Ա�
void destroyList(LinkList &L);

//��L����Ϊ�ձ�
void clearList(LinkList &L);

//���Ƿ�Ϊ��
bool isEmpty(LinkList &L);

//���ر�
int listLength(LinkList &L);

//��ȡλ��i��Ԫ��
bool getElemByIndex(LinkList &L,int i,ElemType &e);

//�ҵ�λ��i��Ԫ��
LinkList findElemByIndex(LinkList &L,int i);

//������Ԫ�ص��ж� ����L�е�1����e����compare()��ϵ������Ԫ��λ��
int locateElem(LinkList &L,ElemType e,compare_func cFunc);

//����cur_e��ǰ��
bool priorElem(LinkList &L,ElemType cur_e,ElemType &pre_e);

//����cur_e�ĺ��
bool nextElem(LinkList &L,ElemType cur_e,ElemType &next_e);

//��λ��i����e
bool listInsert(LinkList &L,int i,ElemType e);

//ɾ��λ��iԪ��
bool listDelete(LinkList &L,int i,ElemType &e);

//����list
void listTraverse(LinkList &L,vi_func vFunc);

//��la lb ����
void listUnion(LinkList &La,LinkList &Lb);

//ð������
void listBubleSort(LinkList &L,compare_func cFunc);

//��la,lb����鲢Ϊlc
void listMerge(LinkList &La,LinkList &Lb,LinkList &Lc);

//��la,lb����鲢Ϊlc
void listMerge2(LinkList &La,LinkList &Lb,LinkList &Lc);

//���ļ����ȡ���ݴ�����
void createListWithFile(LinkList &L,const char * fileName);

//���ļ����ȡ���ݴ�����
void createListWithFile2(LinkList &L,const char * fileName);

typedef char ElemType1;
typedef struct
{
	ElemType1 data[20];
	int cur;
}component,sLinkList[100];

//��̬������ز���
void testStaticList();

//����һ���յ����Ա�
void initList_SL(LinkList &L);

//�������Ա�
void destroyList_SL(LinkList &L);

//��L�ÿ�
void clearList_SL(LinkList &L);

//�ж�L�Ƿ�Ϊ��
bool isEmpty_SL(LinkList &L);

//ȡ�ñ�
int listLength_SL(LinkList &L);

//��ȡ��i��Ԫ��
bool getElemByIndex_SL(LinkList &L,int i,ElemType &e);

//������Ԫ�ص��ж� ����L�е�1����e����compare()��ϵ������Ԫ��λ��
int locateElem_SL(LinkList &L,ElemType e,compare_func cFunc);

//�ҵ�cur_e��ǰ��
bool priorElem_SL(LinkList &L,ElemType cur_e,ElemType &pre_e);

//�ҵ�cur_e�ĺ��
bool nextElem_SL(LinkList &L,ElemType cur_e,ElemType &next_e);

//��iλ�ò���e
bool listInsert_SL(LinkList &L,int i,ElemType e);

//ɾ����i��λ��Ԫ��
bool listDelete_SL(LinkList &L,int i,ElemType &e);

//����L
void listTraverse_SL(LinkList &L,vi_func vFunc);

//��Lb�ϲ���La�ı�β
void listMerge_SL(LinkList &La,LinkList &Lb);

//==========˫������
typedef struct DuLNode
{
	ElemType data;
	DuLNode *prior,*next;
}DuLNode,*DuLinkList;

//�����ձ�
void initList_Du(DuLinkList &L);

//���ٱ�
void destroyList_Du(DuLinkList &L);

//���ñ�
void clearList_Du(DuLinkList &L);

//�ж��Ƿ���
bool isEmpty_Du(DuLinkList &L);

///��ȡ����
int listLength_Du(DuLinkList &L);

//��ȡλ��i��Ԫ��
bool getElemByIndex_Du(DuLinkList &L,int i,ElemType &e);

//���ص�1 ����e����compare��ϵ������
int locateElem_Du(DuLinkList &L,ElemType e,compare_func cFunc);

//����cur_e ��ǰ��
bool priorElem_Du(DuLinkList &L,ElemType cur_e,ElemType &pre_e);

//����cur_e �ĺ��
bool nextElem_Du(DuLinkList &L,ElemType cur_e,ElemType &next_e);

//���ص�i��Ԫ�����ڵ�ַ
DuLinkList findElemByIndex_Du(DuLinkList &L,int i);

//��λ��i����e
bool listInsert_Du(DuLinkList &L,int i,ElemType e);

//ɾ��λ��i ��Ԫ��
bool listDelete_Du(DuLinkList &L,int i,ElemType &e);

//������
void listTraverse_Du(DuLinkList &L,vi_func vFunc);

//���������
void listTraverseBack_Du(DuLinkList &L,vi_func vFunc);

//====================================ʵ��Ӧ���е�����====================================

//ʵ��Ӧ���е�����
typedef LNode *Link,*Position;
struct RLinkList
{
	Link head,tail;//�ֱ�ָ��ͷ,β���
	int len;//����Ԫ�ظ���
};

//������pָ���ֵΪe�Ľ��
void makeNode(Link &p,ElemType e);

//�ͷ�p��ָ�Ľ��
void freeNode(Link &p);

//����һ���յ����Ա�
void initList_RL(RLinkList &L);

//����L����Ϊ��
void clearList_RL(RLinkList &L);

//�������Ա�L
void destroyList_RL(RLinkList &L);

//hָ��L��һ�����,��h����ͷ���,��s��ָ�������ڵ�һ�����֮ǰ
void insertFirst(RLinkList &L,Link h,Link s);

//hָ��L��һ�����,��h����ͷ���,ɾ�������еĵ�һ����㲢��q����
bool deleteFirst(RLinkList &L,Link h,Link &q);

//��s��ָ��һ�����������L�����һ�����֮��,���ı�����βָ��ָ���µĽ��
void appenList(RLinkList &L,Link s);

//����pָ���ǰ��λ��
Position priorPos(RLinkList &L,Link p);

//ɾ��β��㲢��q����,�ı�L��βָ��ָ���µ�β���
bool removeList_RL(RLinkList &L,Link &q);

//s��ָ������p��ָ���֮ǰ
void insBefore(RLinkList &L,Link &p,Link s);

//s��ָ������p��ָ���֮��
void insAfter(RLinkList &L,Link &p,Link s);

//��e����p��ָ�Ľ��
void setCurElem(Link p,ElemType e);

//��ȡp��ָ���Ԫ��
ElemType getCurElem(Link p);

//�ж�L�Ƿ�Ϊ�ձ�
bool isEmpty_RL(RLinkList &L);

//��ȡL��ͷ���
Position getHead(RLinkList L);

//��ȡL��β���
Position getTail(RLinkList L);

//��һ��λ��
Position nextPos(Link p);

//���ص�i������ָ��
bool locatePos(RLinkList L,int i,Link &p);

//�������Ա��е�1����e���㺯��compare�ж���ϵԪ�ص�λ��
Position locateElem_RL(RLinkList L,ElemType e,compare_func cFunc);

//����L
void listTraverse_RL(RLinkList L,vi_func vFunc);

//�������e
void orderInsert(RLinkList &L,ElemType e,compare_func cFunc);

//���ص�һ����e�����ж������Ľ��λ��
bool locateElemPos_RL(RLinkList L,ElemType e,Position &q,compare_func cFunc);

//�ڵ�i��Ԫ��λ�ò���e
bool listInsert_RL(RLinkList &L,int i,ElemType e);

//�Ա�ʹ��ð������
void listBubbleSort_RL(RLinkList &L,compare_func cFunc);

//����鲢Ϊ�±�
void listMerge_RL(RLinkList &La,RLinkList &Lb,RLinkList &Lc,compare_func cFunc);

//====================================һԪ����ʽӦ��====================================
typedef struct 
{
	float coef;//ϵ��
	int expn;//ָ��
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
	LPLink head,tail;//�ֱ�ָ��ͷ,β���
	int len;//����Ԫ�ظ���
};
typedef LPRLinkList polynomial;
typedef int (*compare_term_func)(term,term);
int compare_term_status(term a,term b); //<:-1 =:0 >1

//������pָ���ֵΪe�Ľ��
void makeNode_RLP(LPLink &p,PoElemType e);

//�ͷ�p��ָ�Ľ��
void freeNode_RLP(LPLink &p);

//����һ���ձ�
void initList_RLP(LPLink &p);

//����L����Ϊ��
void clearList_RLP(polynomial &L);

//�ж�һ�����Ƿ�Ϊ�ձ�
bool isEmpty_RLP(polynomial p);

//�������Ա�L
void destroyList_RLP(polynomial &L);

//��pb ��չpa
void appenList_RLP(polynomial Pa,LPLink p);

//hָ��L��һ�����,��h����ͷ���,��s��ָ�������ڵ�һ�����֮ǰ
void insertFirst_RLP(LPRLinkList &L,LPLink h,LPLink s);

//hָ��L��һ�����,��h����ͷ���,ɾ�������еĵ�һ����㲢��q����
bool deleteFirst_RLP(LPRLinkList &L,LPLink h,LPLink &q);

//����pָ���ǰ��λ��
LPPosition priorPos_RLP(LPRLinkList &L,LPLink p);

//���ص�һ����e�����ж������Ľ��λ��
bool locateElemPos_RLP(LPRLinkList L,PoElemType e,LPPosition &q,compare_term_func cFunc);

//��e ���õ����к��ʵ�λ��
void orderInsertMerge(LPRLinkList &L,PoElemType e,compare_term_func cFunc); 

//�������ʽ�����ļ����к�,������ʾһԪ�������������p
void createPolyn(polynomial &P,const char *fileName,int mLine =1);

//��ӡ����ʽ
void printPolyn(polynomial P);

//�����������
void addPolyn(polynomial &Pa,polynomial &Pb);

//��һ�����˸�����ʽ��ӵķ���
void addPolyn1(polynomial &Pa,polynomial &Pb);
#endif