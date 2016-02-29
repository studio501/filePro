#ifndef __TESTLINKBITREE__HH_
#define __TESTLINKBITREE__HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;
namespace LKT{
//��������˳��洢�ṹ
//#define  CHAR 0
#define  CHAR 1

#if CHAR
	typedef char TElemType;
	TElemType Nil='#';
#else
	typedef int TElemType;
	TElemType Nil=0;
#endif

//start delete
#define MAX_TREE_SIZE 256
typedef TElemType SqBiTree[MAX_TREE_SIZE];
struct position
{
	int level,order;
};

//end delete 
typedef struct BiTNode
{
	TElemType data;
	BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

#define clearBiTree destroyBiTree


typedef void(*visitFunc)(TElemType);

//��ӡ����
void visit_tree(TElemType e);

//����ն�����T
void initBiTree(BiTree &T);

//������
void destroyBiTree(BiTree &T);

//����һ�������
void makeBiTreeNode(BiTree &T,char *buf,int &i);

//���򴴽����������
void createBiTree(BiTree &T,int nLine=1);

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

//����cΪT��p�������������
bool insertChild(BiTree p,int LR,BiTree c);

//����LRΪ1 ��0,ɾ��T��p��ָ�������������
bool deleteChild(BiTree p,int LR);

//���������
void preOrderTraverse(BiTree T,visitFunc func);

//���������
void inOrderTraverse(BiTree T,visitFunc func);

//���������
void postOrderTraverse(BiTree T,visitFunc func);

//�������(�ǵݹ�)
void inOrderTraverse1(BiTree T,visitFunc func);

//���,��������������
void print(BiTree T);
};
#endif // !__TESTSQBITREE__HH_
