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
#endif