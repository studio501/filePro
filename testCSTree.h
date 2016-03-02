#ifndef __TESTCSTREE__HH_
#define __TESTCSTREE__HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;
namespace CST{
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

typedef struct CSNode
{
	TElemType data;
	CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;

#define clearBiTree destroyBiTree


typedef void(*visitFunc)(TElemType);

//打印函数
void visit_tree(TElemType e);

//构造空二叉树T
void initBiTree(CSTree &T);

//销毁树
void destroyBiTree(CSTree &T);

//创建一个树结点
void makeBiTreeNode(BiTree &T,TElemType *buf,int &i);

//先序创建链表二叉树
void createBiTree(CSTree &T,int nLine=1);

//判断二叉树是否为空
bool biTreeEmpty(CSTree T);

//求树的深度
int biTreeDepth(CSTree T);

//返回树的根
TElemType root(CSTree T);

//返回处于位置e的结点的值
TElemType value(CSTree p);

//给处于e的位置赋新值
void assign(CSTree &T,TElemType cur_e,TElemType value);

//若e是树的非根结点,则返回它的双亲,否则返回空
TElemType parent(CSTree T,TElemType e);

//返回二叉树中指向元素值为s的结点的指针
CSTree point(CSTree T,TElemType s);

//返回e的左孩子
TElemType leftChild(CSTree T,TElemType e);

//返回e的右兄弟或者空
TElemType rightSibling(CSTree T,TElemType e);

//插入c为T中p结点的左或右子树
bool insertChild(CSTree &T,CSTree p,int i,CSTree c);

//根据LR为1 或0,删除T中p所指结点的左或右子树
bool deleteChild(CSTree &T,CSTree p, int i);

//后序遍历树
void postOrderTraverse(CSTree T,visitFunc func);

//层序遍历
void levelOrderTraverse(CSTree T,visitFunc func);

};
#endif // !__TESTSQBITREE__HH_
