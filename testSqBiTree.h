#ifndef __TESTSQBITREE__HH_
#define __TESTSQBITREE__HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;

//二叉树的顺序存储结构
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

//打印函数
void visit_tree(TElemType e);

//构造空二叉树T
void initBiTree(SqBiTree T);

//按层次顺序输入二叉树中的结点值
void createBiTree(SqBiTree T,int nLine=1);

//判断二叉树是否为空
bool biTreeEmpty(SqBiTree T);

//求树的深度
int biTreeDepth(SqBiTree T);

//返回树的根
bool root(SqBiTree T,TElemType &e);

//返回处于位置e的结点的值
TElemType value(SqBiTree T,position e);

//给处于e的位置赋新值
bool assign(SqBiTree T,position e,TElemType value);

//若e是树的非根结点,则返回它的双亲,否则返回空
TElemType parent(SqBiTree T,TElemType e);

//返回e的左孩子
TElemType leftChild(SqBiTree T,TElemType e);

//返回e的右孩子
TElemType rightChild(SqBiTree T,TElemType e);

//返回e的左兄弟或者空
TElemType leftSibling(SqBiTree T,TElemType e);

//返回e的右兄弟或者空
TElemType rightSibling(SqBiTree T,TElemType e);

//把从q的j结点开始的子树移为从T的i结点开始的子树
void move(SqBiTree q,int j,SqBiTree T,int i);

//插入c为T中p结点的左或右子树
void insertChild(SqBiTree T,TElemType p,int LR,SqBiTree c);

//根据LR为1 或0,删除T中p所指结点的左或右子树
bool deleteChild(SqBiTree T,position p,int LR);

//先序遍历结点
void preTraverse(SqBiTree T,int e,visitFunc func);

//先序遍历树
void preOrderTraverse(SqBiTree T,visitFunc func);

//中序遍历结点
void inTraverse(SqBiTree T,int e,visitFunc func);

//中序遍历树
void inOrderTraverse(SqBiTree T,visitFunc func);

//后序遍历结点
void postTraverse(SqBiTree T,int e,visitFunc func);

//后序遍历树
void postOrderTraverse(SqBiTree T,visitFunc func);

//层序遍历树
void levelOrderTraverse(SqBiTree T,visitFunc func);

//逐层,按序号输出二叉树
void print(SqBiTree T);
#endif // !__TESTSQBITREE__HH_
