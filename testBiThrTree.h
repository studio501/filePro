#ifndef __TESBITHRTREE__HH_
#define __TESBITHRTREE__HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;
namespace LKTHR{
//��������˳��洢�ṹ
#define  CHAR 0
//#define  CHAR 1

#if CHAR
	typedef char TElemType;
	TElemType Nil='#';
	TElemType EndFlag='\0';
#else
	typedef int TElemType;
	TElemType Nil=0;
	TElemType EndFlag=999;
#endif

#define MAX_TREE_SIZE 100

enum PointerTag
{
	Link,
	Thread
};

typedef struct BiThrNode
{
	TElemType data;
	BiThrNode *lchild,*rchild;
	PointerTag LTag,RTag;
}BiThrNode,BiTNode,*BiThrTree,*BiTree;


#define clearBiTree destroyBiTree


typedef void(*visitFunc)(TElemType);

//��ӡ����
void visit_tree(TElemType e);

//����ն�����T
void initBiTree(BiThrTree &T);

//������
void destroyBiTree(BiThrTree &T);

//��������������
void destroyBiThrTree(BiThrTree &Thrt);

//����һ�������
void makeBiTreeNode(BiThrTree &T,TElemType *buf,int &i);

//���򴴽����������
void createBiTree(BiThrTree &T,int nLine=1);

//ͨ�����������������������
void inThreading(BiThrTree p);

//������������������������� Thrtָ��ͷ���
void inOrderThreading(BiThrTree &Thrt,BiThrTree T);

//������������������ǵݹ��㷨
void inOrderTraverse_Thr(BiThrTree T,visitFunc func);

//����
void preThreading(BiThrTree p);

//�����������������������
void preOrderThreading(BiThrTree &Thrt,BiThrTree T);

//�����������������
void preOrderTraverse_Thr(BiThrTree T,visitFunc func);

//�ж϶������Ƿ�Ϊ��
bool biTreeEmpty(BiTree T);

//���������
int biTreeDepth(BiTree T);

//�������ĸ�
TElemType root(BiTree T);

//���ش���λ��e�Ľ���ֵ
TElemType value(BiTree p);

//������e��λ�ø���ֵ
void assign(BiTree p,TElemType value);

//��e�����ķǸ����,�򷵻�����˫��,���򷵻ؿ�
TElemType parent(BiTree T,TElemType e);

//���ض�������ָ��Ԫ��ֵΪs�Ľ���ָ��
BiTree point(BiTree T,TElemType s);

//����e������
TElemType leftChild(BiTree T,TElemType e);

//����e���Һ���
TElemType rightChild(BiTree T,TElemType e);

//����e�����ֵܻ��߿�
TElemType leftSibling(BiTree T,TElemType e);

//����e�����ֵܻ��߿�
TElemType rightSibling(BiTree T,TElemType e);


};
#endif // !__TESTSQBITREE__HH_
