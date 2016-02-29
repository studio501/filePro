#ifndef __TESTLINKBITREE__HH_
#define __TESTLINKBITREE__HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;
namespace LKT{
//二叉树的顺序存储结构
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

//打印函数
void visit_tree(TElemType e);

//构造空二叉树T
void initBiTree(BiTree &T);

//销毁树
void destroyBiTree(BiTree &T);

//创建一个树结点
void makeBiTreeNode(BiTree &T,char *buf,int &i);

//先序创建链表二叉树
void createBiTree(BiTree &T,int nLine=1);

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

//逐层,按序号输出二叉树
void print(BiTree T);
};
#endif // !__TESTSQBITREE__HH_
