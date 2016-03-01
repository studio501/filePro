#ifndef __TESBITHRTREE__HH_
#define __TESBITHRTREE__HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

using namespace std;
namespace LKTHR{
//二叉树的顺序存储结构
#define  CHAR 0
//#define  CHAR 1

#if CHAR
	typedef char TElemType;
	TElemType Nil='#';
	TElemType EndFlag='\0';
#else
	typedef int TElemType;
	TElemType Nil=0;
	TElemType EndFlag=999;
#endif

#define MAX_TREE_SIZE 100

enum PointerTag
{
	Link,
	Thread
};

typedef struct BiThrNode
{
	TElemType data;
	BiThrNode *lchild,*rchild;
	PointerTag LTag,RTag;
}BiThrNode,BiTNode,*BiThrTree,*BiTree;


#define clearBiTree destroyBiTree


typedef void(*visitFunc)(TElemType);

//打印函数
void visit_tree(TElemType e);

//构造空二叉树T
void initBiTree(BiThrTree &T);

//销毁树
void destroyBiTree(BiThrTree &T);

//销毁线索二叉树
void destroyBiThrTree(BiThrTree &Thrt);

//创建一个树结点
void makeBiTreeNode(BiThrTree &T,TElemType *buf,int &i);

//先序创建链表二叉树
void createBiTree(BiThrTree &T,int nLine=1);

//通过中序遍历进行中序线索化
void inThreading(BiThrTree p);

//中序遍历树并阍其中序线索化 Thrt指向头结点
void inOrderThreading(BiThrTree &Thrt,BiThrTree T);

//中序遍历线索二叉树非递归算法
void inOrderTraverse_Thr(BiThrTree T,visitFunc func);

//先序化
void preThreading(BiThrTree p);

//先序遍历树并先序线索化树
void preOrderThreading(BiThrTree &Thrt,BiThrTree T);

//先序遍历线索二叉树
void preOrderTraverse_Thr(BiThrTree T,visitFunc func);

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


};
#endif // !__TESTSQBITREE__HH_
