#ifndef __TESTSQTREE__HH_
#define __TESTSQTREE__HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;
namespace SQT{
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

typedef struct PTNode
{
	TElemType data;
	int parent;
}PTNode;

typedef struct PTree
{
	PTNode nodes[MAX_TREE_SIZE];
	int n;
}PTree;

#define clearBiTree initBiTree
#define destroyBiTree initBiTree

typedef void(*visitFunc)(TElemType);

//��ӡ����
void visit_tree(TElemType e);

//����ն�����T
void initBiTree(PTree &T);

//���򴴽����������
void createBiTree(PTree &T,int nLine=1);

//�ж϶������Ƿ�Ϊ��
bool biTreeEmpty(PTree T);

//���������
int biTreeDepth(PTree T);

//�������ĸ�
TElemType root(PTree T);

//���ش���λ��e�Ľ���ֵ
TElemType value(PTree p,int i);

//������e��λ�ø���ֵ
void assign(PTree &T,TElemType cur_e,TElemType value);

//��e�����ķǸ����,�򷵻�����˫��,���򷵻ؿ�
TElemType parent(PTree T,TElemType cur_e);

//����e������
TElemType leftChild(PTree T,TElemType e);

//����e�����ֵܻ��߿�
TElemType rightSibling(PTree T,TElemType e);

//��ӡ��
void print(PTree T);

//����cΪT��p�������������
bool insertChild(PTree &T,TElemType p,int i,PTree c);

//����LRΪ1 ��0,ɾ��T��p��ָ�������������
bool deleteChild(PTree &T,TElemType p,int i);

//������
void traverseTree(PTree T,visitFunc func);

};
#endif // !__TESTSQBITREE__HH_
