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

//����һ���յ�˳�����Ա�
void initList(SqList &L);

//����һ�����Ա�
void destroyList(SqList &L);

//˳����Ѿ����ڽ�������Ϊ�ձ�
void clearList(SqList &L);

//�ж��Ƿ�Ϊ�ձ�
bool isEmpty(SqList &L);

//��ȡ����
int getListLen(SqList &L);

//���index�Ƿ�Ϸ�
bool checkIndex(SqList &L,int index);

//����L�е�i������Ԫ�ص�ֵ
bool getElemByIndex(SqList &L,int i,ElemType &e);

//����L�е�i������Ԫ�ص�ֵ
ElemType *findElemByIndex(SqList &L,int i);

//������Ԫ�ص��ж� ����L�е�1����e����compare()��ϵ������Ԫ��λ��
int locateElem(SqList &L,ElemType e,compare_func func);

//����ǰһ��Ԫ�� ��ǰԪ�ز����ǵ�һ��
bool priorElem(SqList &L,ElemType cur_e,ElemType &pre_e);

//������һ��Ԫ�� ��ǰԪ�ز��������һ��
bool nextElem(SqList &L,ElemType cur_e,ElemType &next_e);

//��L�ĵ�i��λ�ò����µ�Ԫ��e,L�ĳ��ȼ�1
bool listInsert(SqList &L,int i,ElemType e);

//ɾ��L�ĵ�i��Ԫ��
bool listDelete(SqList &L,int i,ElemType &e);

//������ ��Ԫ��ʹ��vi����
void listTraverse(SqList &L,vi_func vFunc);

//�Ա����ð������
void listBubbleSort(SqList &L,compare_func cFunc );

//La��Lb�ϲ�
void listUnion(SqList &La,SqList &Lb);

//la,lb ���� �鲢Ϊlc��������
void listMerge(SqList &La,SqList &Lb,SqList &Lc);

//la,lb ���� �鲢Ϊlc��������
void listMerge1(SqList &La,SqList &Lb,SqList &Lc);


#endif