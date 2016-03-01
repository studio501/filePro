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

//创建一个树结点
void makeBiTreeNode(BiTree &T,TElemType *buf,int &i);

//先序创建链表二叉树
void createBiTree(PTree &T,int nLine=1);

//判断二叉树是否为空
bool biTreeEmpty(BiTree T);

//求树的深度
int biTreeDepth(BiTree T);

//返回树的根
TElemType root(BiTree T);

//返回处于位置e的结点的值
TElemType value(BiTree p);

//给处于e的位置赋新值
void assign(BiTree p,TElemType value);

//若e是树的非根结点,则返回它的双亲,否则返回空
TElemType parent(BiTree T,TElemType e);

//返回二叉树中指向元素值为s的结点的指针
BiTree point(BiTree T,TElemType s);

//返回e的左孩子
TElemType leftChild(BiTree T,TElemType e);

//返回e的右孩子
TElemType rightChild(BiTree T,TElemType e);

//返回e的左兄弟或者空
TElemType leftSibling(BiTree T,TElemType e);

//返回e的右兄弟或者空
TElemType rightSibling(BiTree T,TElemType e);

//插入c为T中p结点的左或右子树
bool insertChild(BiTree p,int LR,BiTree c);

//根据LR为1 或0,删除T中p所指结点的左或右子树
bool deleteChild(BiTree p,int LR);

//先序遍历树
void preOrderTraverse(BiTree T,visitFunc func);

//中序遍历树
void inOrderTraverse(BiTree T,visitFunc func);

//后序遍历树
void postOrderTraverse(BiTree T,visitFunc func);

//中序遍历(非递归)
void inOrderTraverse1(BiTree T,visitFunc func);

//中序遍历(非递归)
void inOrderTraverse2(BiTree T,visitFunc func);

//层序遍历
void levelOrderTraverse(BiTree T,visitFunc func);

};
#endif // !__TESTSQBITREE__HH_
