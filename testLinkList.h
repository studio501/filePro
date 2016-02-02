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
#endif