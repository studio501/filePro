#ifndef __TESTSQBITREE__HH_
#define __TESTSQBITREE__HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;

//��������˳��洢�ṹ
//#define  CHAR 0
#define  CHAR 1

#if CHAR
	typedef char TElemType;
	TElemType Nil=' ';
#else
	typedef int TElemType;
	TElemType Nil=0;
#endif

#define MAX_TREE_SIZE 256
typedef TElemType SqBiTree[MAX_TREE_SIZE];
struct position
{
	int level,order;
};

#define clearBiTree initBiTree
#define destroyBiTree initBiTree

typedef void(*visitFunc)(TElemType);

//��ӡ����
void visit_tree(TElemType e);

//����ն�����T
void initBiTree(SqBiTree T);

//�����˳������������еĽ��ֵ
void createBiTree(SqBiTree T,int nLine=1);

//�ж϶������Ƿ�Ϊ��
bool biTreeEmpty(SqBiTree T);

//���������
int biTreeDepth(SqBiTree T);

//�������ĸ�
bool root(SqBiTree T,TElemType &e);

//���ش���λ��e�Ľ���ֵ
TElemType value(SqBiTree T,position e);

//������e��λ�ø���ֵ
bool assign(SqBiTree T,position e,TElemType value);

//��e�����ķǸ����,�򷵻�����˫��,���򷵻ؿ�
TElemType parent(SqBiTree T,TElemType e);

//����e������
TElemType leftChild(SqBiTree T,TElemType e);

//����e���Һ���
TElemType rightChild(SqBiTree T,TElemType e);

//����e�����ֵܻ��߿�
TElemType leftSibling(SqBiTree T,TElemType e);

//����e�����ֵܻ��߿�
TElemType rightSibling(SqBiTree T,TElemType e);

//�Ѵ�q��j��㿪ʼ��������Ϊ��T��i��㿪ʼ������
void move(SqBiTree q,int j,SqBiTree T,int i);

//����cΪT��p�������������
void insertChild(SqBiTree T,TElemType p,int LR,SqBiTree c);

//����LRΪ1 ��0,ɾ��T��p��ָ�������������
bool deleteChild(SqBiTree T,position p,int LR);

//����������
void preTraverse(SqBiTree T,int e,visitFunc func);

//���������
void preOrderTraverse(SqBiTree T,visitFunc func);

//����������
void inTraverse(SqBiTree T,int e,visitFunc func);

//���������
void inOrderTraverse(SqBiTree T,visitFunc func);

//����������
void postTraverse(SqBiTree T,int e,visitFunc func);

//���������
void postOrderTraverse(SqBiTree T,visitFunc func);

//���������
void levelOrderTraverse(SqBiTree T,visitFunc func);

//���,��������������
void print(SqBiTree T);
#endif // !__TESTSQBITREE__HH_
