#ifndef __TESTSQTREE__HH_
#define __TESTSQTREE__HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;
namespace SQT{
//二叉树的顺序存储结构
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

//打印函数
void visit_tree(TElemType e);

//构造空二叉树T
void initBiTree(PTree &T);

//先序创建链表二叉树
void createBiTree(PTree &T,int nLine=1);

//判断二叉树是否为空
bool biTreeEmpty(PTree T);

//求树的深度
int biTreeDepth(PTree T);

//返回树的根
TElemType root(PTree T);

//返回处于位置e的结点的值
TElemType value(PTree p,int i);

//给处于e的位置赋新值
void assign(PTree &T,TElemType cur_e,TElemType value);

//若e是树的非根结点,则返回它的双亲,否则返回空
TElemType parent(PTree T,TElemType cur_e);

//返回e的左孩子
TElemType leftChild(PTree T,TElemType e);

//返回e的右兄弟或者空
TElemType rightSibling(PTree T,TElemType e);

//打印树
void print(PTree T);

//插入c为T中p结点的左或右子树
bool insertChild(PTree &T,TElemType p,int i,PTree c);

//根据LR为1 或0,删除T中p所指结点的左或右子树
bool deleteChild(PTree &T,TElemType p,int i);

//遍历树
void traverseTree(PTree T,visitFunc func);

};
#endif // !__TESTSQBITREE__HH_
