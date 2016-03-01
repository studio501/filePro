#ifndef __TESTLINKPBITREE__HH_
#define __TESTLINKPBITREE__HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;
namespace LKPT{
//二叉树的顺序存储结构
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

//打印函数
void visit_tree(TElemType e);

//构造空二叉树T
void initBiTree(BiPTree &T);

//销毁树
void destroyBiTree(BiPTree &T);

//创建一个树结点
void makeBiTreeNode(BiPTree &T,TElemType *buf,int &i);

//先序创建链表二叉树
void createBiTree(BiPTree &T,int nLine=1);

//判断二叉树是否为空
bool biTreeEmpty(BiPTree T);

//求树的深度
int biTreeDepth(BiPTree T);

//返回树的根
TElemType root(BiPTree T);

//返回处于位置e的结点的值
TElemType value(BiPTree p);

//给处于e的位置赋新值
void assign(BiPTree p,TElemType value);

//若e是树的非根结点,则返回它的双亲,否则返回空
TElemType parent(BiPTree T,TElemType e);

//返回二叉树中指向元素值为s的结点的指针
BiPTree point(BiPTree T,TElemType s);

//返回e的左孩子
TElemType leftChild(BiPTree T,TElemType e);

//返回e的右孩子
TElemType rightChild(BiPTree T,TElemType e);

//返回e的左兄弟或者空
TElemType leftSibling(BiPTree T,TElemType e);

//返回e的右兄弟或者空
TElemType rightSibling(BiPTree T,TElemType e);

//插入c为T中p结点的左或右子树
bool insertChild(BiPTree p,int LR,BiPTree c);

//根据LR为1 或0,删除T中p所指结点的左或右子树
bool deleteChild(BiPTree p,int LR);

//先序遍历树
void preOrderTraverse(BiPTree T,visitFunc func);

//中序遍历树
void inOrderTraverse(BiPTree T,visitFunc func);

//后序遍历树
void postOrderTraverse(BiPTree T,visitFunc func);

//中序遍历(非递归)
void inOrderTraverse1(BiPTree T,visitFunc func);

//中序遍历(非递归)
void inOrderTraverse2(BiPTree T,visitFunc func);

//层序遍历
void levelOrderTraverse(BiPTree T,visitFunc func);

};
#endif // !__TESTSQBITREE__HH_
