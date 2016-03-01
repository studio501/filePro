#ifndef __TESTLINKPBITREE__HH_
#define __TESTLINKPBITREE__HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;
namespace LKPT{
//��������˳��洢�ṹ
//#define  CHAR 0
#define  CHAR 1

#if CHAR
	typedef char TElemType;
	TElemType Nil='#';
	TElemType EndFlag='\0';
#else
	typedef int TElemType;
	TElemType Nil=0;
	TElemType EndFlag=999;
#endif


#define MAX_TREE_SIZE 256

//start delete
typedef struct BiTNode
{
	TElemType data;
	BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
//end delete 

typedef struct BiTPNode
{
	TElemType data;
	BiTPNode *parent,*lchild,*rchild;
}BiTPNode,*BiPTree;

#define clearBiTree destroyBiTree


typedef void(*visitFunc)(TElemType);

//��ӡ����
void visit_tree(TElemType e);

//����ն�����T
void initBiTree(BiPTree &T);

//������
void destroyBiTree(BiPTree &T);

//����һ�������
void makeBiTreeNode(BiPTree &T,TElemType *buf,int &i);

//���򴴽����������
void createBiTree(BiPTree &T,int nLine=1);

//�ж϶������Ƿ�Ϊ��
bool biTreeEmpty(BiPTree T);

//���������
int biTreeDepth(BiPTree T);

//�������ĸ�
TElemType root(BiPTree T);

//���ش���λ��e�Ľ���ֵ
TElemType value(BiPTree p);

//������e��λ�ø���ֵ
void assign(BiPTree p,TElemType value);

//��e�����ķǸ����,�򷵻�����˫��,���򷵻ؿ�
TElemType parent(BiPTree T,TElemType e);

//���ض�������ָ��Ԫ��ֵΪs�Ľ���ָ��
BiPTree point(BiPTree T,TElemType s);

//����e������
TElemType leftChild(BiPTree T,TElemType e);

//����e���Һ���
TElemType rightChild(BiPTree T,TElemType e);

//����e�����ֵܻ��߿�
TElemType leftSibling(BiPTree T,TElemType e);

//����e�����ֵܻ��߿�
TElemType rightSibling(BiPTree T,TElemType e);

//����cΪT��p�������������
bool insertChild(BiPTree p,int LR,BiPTree c);

//����LRΪ1 ��0,ɾ��T��p��ָ�������������
bool deleteChild(BiPTree p,int LR);

//���������
void preOrderTraverse(BiPTree T,visitFunc func);

//���������
void inOrderTraverse(BiPTree T,visitFunc func);

//���������
void postOrderTraverse(BiPTree T,visitFunc func);

//�������(�ǵݹ�)
void inOrderTraverse1(BiPTree T,visitFunc func);

//�������(�ǵݹ�)
void inOrderTraverse2(BiPTree T,visitFunc func);

//�������
void levelOrderTraverse(BiPTree T,visitFunc func);

};
#endif // !__TESTSQBITREE__HH_
