#ifndef __TESTCSTREE__HH_
#define __TESTCSTREE__HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;
namespace CST{
//��������˳��洢�ṹ
//#define  CHAR 0
#define  CHAR 1

#if CHAR
	typedef char TElemType;
	TElemType Nil='#';
	TElemType EndFlag='\0';
	TElemType BranchEnd=' ';
#else
	typedef int TElemType;
	TElemType Nil=0;
	TElemType EndFlag=999;
#endif

#define MAX_TREE_SIZE 100

typedef struct BiTNode
{
	TElemType data;
	BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef struct CSNode
{
	TElemType data;
	CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;

#define clearBiTree destroyBiTree


typedef void(*visitFunc)(TElemType);

//��ӡ����
void visit_tree(TElemType e);

//����ն�����T
void initBiTree(CSTree &T);

//������
void destroyBiTree(CSTree &T);

//����һ�������
void makeBiTreeNode(BiTree &T,TElemType *buf,int &i);

//���򴴽����������
void createBiTree(CSTree &T,int nLine=1);

//�ж϶������Ƿ�Ϊ��
bool biTreeEmpty(CSTree T);

//���������
int biTreeDepth(CSTree T);

//�������ĸ�
TElemType root(CSTree T);

//���ش���λ��e�Ľ���ֵ
TElemType value(CSTree p);

//������e��λ�ø���ֵ
void assign(CSTree &T,TElemType cur_e,TElemType value);

//��e�����ķǸ����,�򷵻�����˫��,���򷵻ؿ�
TElemType parent(CSTree T,TElemType e);

//���ض�������ָ��Ԫ��ֵΪs�Ľ���ָ��
CSTree point(CSTree T,TElemType s);

//����e������
TElemType leftChild(CSTree T,TElemType e);

//����e�����ֵܻ��߿�
TElemType rightSibling(CSTree T,TElemType e);

//����cΪT��p�������������
bool insertChild(CSTree &T,CSTree p,int i,CSTree c);

//����LRΪ1 ��0,ɾ��T��p��ָ�������������
bool deleteChild(CSTree &T,CSTree p, int i);

//���������
void postOrderTraverse(CSTree T,visitFunc func);

//�������
void levelOrderTraverse(CSTree T,visitFunc func);

};
#endif // !__TESTSQBITREE__HH_
