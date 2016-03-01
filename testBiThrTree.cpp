
#include "stdafx.h"
#include "testBiThrTree.h"
#include "queueTest.h"
#include <stack>

namespace LKTHR{
typedef BiTree QElemType;
typedef BiTree SElemType;

BiThrTree pre;//全局变量

//打印函数
void visit_tree(TElemType e)
{
	cout<<e<<" ";
}

//构造空二叉树T
void initBiTree(BiThrTree &T)
{
	T=NULL;
}

//销毁树
void destroyBiTree(BiThrTree &T)
{
	if(T)
	{
		if(T->LTag==Link) destroyBiTree(T->lchild);
		if(T->RTag==Link) destroyBiTree(T->rchild);
		free(T);
		T=NULL;
	}
}

//销毁线索二叉树
void destroyBiThrTree(BiThrTree &Thrt)
{
	if(Thrt)
	{
		if(Thrt->lchild)
			destroyBiTree(Thrt->lchild);
		free(Thrt);
		Thrt=NULL;
	}
}

//创建一个树结点
void makeBiTreeNode(BiThrTree &T,TElemType *buf,int &i)
{
	if(buf[i]==EndFlag) return;
	TElemType ch=(TElemType)buf[i];
	if(ch==Nil) 
	{
		T=NULL;
		++i;
	}
	else
	{
		T=(BiThrTree)malloc(sizeof(BiThrNode));
		if(!T) exit(OVERFLOW);
		T->data=ch;
		++i;
		makeBiTreeNode(T->lchild,buf,i);
		if(T->lchild) T->LTag=Link;
		makeBiTreeNode(T->rchild,buf,i);
		if(T->rchild) T->RTag=Link;
	}
}

//按层次顺序输入二叉树中的结点值
void createBiTree(BiThrTree &T,int nLine)
{
	int i=0;
	initBiTree(T);
	TElemType s[MAX_TREE_SIZE];
	ifstream fin;
#if CHAR
	fin.open("charBitTreeLink.txt",ios_base::in);
	if(fin.is_open())
	{
		int curLine=0;
		while(curLine<nLine)
		{
			fin.getline(s,MAX_TREE_SIZE);
			++curLine;
		}
		fin.close();
	}
#else
	char temp[MAX_TREE_SIZE];
	int j=0;
	fin.open("intBitTreeLink.txt",ios_base::in);
	if(fin.is_open())
	{
		int curLine=1;
		while(curLine<nLine)
		{
			fin.getline(temp,MAX_TREE_SIZE);
			++curLine;
		}
		while(fin>>s[j++]);
		s[--j]=EndFlag;

		fin.close();
	}
#endif
	makeBiTreeNode(T,s,i);
}

//通过中序遍历进行中序线索化
void inThreading(BiThrTree p)
{
	if(p)
	{
		inThreading(p->lchild);
		if(!p->lchild)
		{
			p->LTag=Thread;
			p->lchild=pre;
		}
		if(!pre->rchild)
		{
			pre->RTag=Thread;
			pre->rchild=p;
		}
		pre=p;
		inThreading(p->rchild);
	}
}

//中序遍历树并阍其中序线索化 Thrt指向头结点
void inOrderThreading(BiThrTree &Thrt,BiThrTree T)
{
	if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
	Thrt->LTag=Link;
	Thrt->RTag=Thread;
	Thrt->rchild=Thrt;
	if(!T) Thrt->lchild=Thrt;
	else
	{
		Thrt->lchild=T;
		pre=Thrt;
		inThreading(T);
		pre->rchild=Thrt;
		pre->RTag=Thread;
		Thrt->rchild=pre;
	}
}

//中序遍历线索二叉树非递归算法
void inOrderTraverse_Thr(BiThrTree T,visitFunc func)
{
	BiThrTree p;
	p=T->lchild;
	while(p!=T)
	{
		while(p->LTag==Link)
			p=p->lchild;
		func(p->data);
		while(p->RTag==Thread&&p->rchild!=T)
		{
			p=p->rchild;
			func(p->data);
		}
		p=p->rchild;
	}
	cout<<endl;
}

//先序化
void preThreading(BiThrTree p)
{
	if(!pre->rchild)
	{
		pre->rchild=p;
		pre->RTag=Thread;
	}
	if(!p->lchild)
	{
		p->LTag=Thread;
		p->lchild=pre;
	}
	pre=p;
	if(p->LTag==Link)
		preThreading(p->lchild);
	if(p->RTag==Link)
		preThreading(p->rchild);
}

//先序遍历树并先序线索化树
void preOrderThreading(BiThrTree &Thrt,BiThrTree T)
{
	if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrTree)))) exit(OVERFLOW);
	Thrt->LTag=Link;
	Thrt->RTag=Thread;
	Thrt->rchild=Thrt;
	if(!T) Thrt->lchild=Thrt;
	else
	{
		Thrt->lchild=T;
		pre=Thrt;
		preThreading(T);
		pre->rchild=Thrt;
		pre->RTag=Thread;
		Thrt->rchild=pre;
	}
}

//先序遍历线索二叉树
void preOrderTraverse_Thr(BiThrTree T,visitFunc func)
{
	BiThrTree p=T->lchild;
	while(p!=T)
	{
		func(p->data);
		if(p->LTag==Link) p=p->lchild;
		else p=p->rchild;
	}
	cout<<endl;
}

//判断二叉树是否为空
bool biTreeEmpty(BiTree T)
{
	if(T) return false;
	else return true;
}

//求树的深度
int biTreeDepth(BiTree T)
{
	int i,j;
	if(!T) return 0;
	if(T->LTag==Link)
		i=biTreeDepth(T->lchild);
	else
		i=0;
	if(T->RTag==Link)
		j=biTreeDepth(T->rchild);
	else
		j=0;
	return i>j?i+1:j+1;
}

//返回树的根
TElemType root(BiTree T)
{
	if(biTreeEmpty(T)) return Nil;
	else return T->data;	
}

//返回处于位置e的结点的值
TElemType value(BiTree p)
{
	return p->data;
}

//给处于e的位置赋新值
void assign(BiTree p,TElemType value)
{
	p->data=value;
}

//若e是树的非根结点,则返回它的双亲,否则返回空
TElemType parent(BiTree T,TElemType e)
{
	LinkQueue<QElemType> q;
	QElemType a;
	if(T)
	{
		initQueue(q);
		enQueue(q,T);
		while(!isQueueEmpty(q))
		{
			deQueue(q,a);
			if(a->lchild&&a->lchild->data==e||a->rchild&&a->rchild->data==e)
				return a->data;
			else
			{
				if(a->lchild)
					enQueue(q,a->lchild);
				if(a->rchild)
					enQueue(q,a->rchild);
			}
		}
	}
	return Nil;
}

//返回二叉树中指向元素值为s的结点的指针
BiTree point(BiTree T,TElemType s)
{
	LinkQueue<QElemType> q;
	QElemType a;
	if(T)
	{
		initQueue(q);
		enQueue(q,T);
		while(!isQueueEmpty(q))
		{
			deQueue(q,a);
			if(a->data==s)
				return a;
			if(a->lchild)
				enQueue(q,a->lchild);
			if(a->rchild)
				enQueue(q,a->rchild);
		}
	}
	return NULL;
}

//返回e的左孩子
TElemType leftChild(BiTree T,TElemType e)
{
	
	BiTree a;
	if(T)
	{
		a=point(T,e);
		if(a&&a->LTag==Link)
			return a->lchild->data;
	}
	return Nil;
}

//返回e的右孩子
TElemType rightChild(BiTree T,TElemType e)
{
	
	BiTree a;
	if(T)
	{
		a=point(T,e);
		if(a&&a->RTag==Link)
			return a->rchild->data;
	}
	return Nil;
}

//返回e的左孩子或者空
TElemType leftSibling(BiTree T,TElemType e)
{
	
	TElemType a;
	BiTree p;
	if(T)
	{
		a=parent(T,e);
		if(a!=Nil)
		{
			p=point(T,a);
			if(p->LTag==Link&&p->RTag==Link&&p->rchild->data==e)
				return p->lchild->data;
		}
	}
	return Nil;
}

//返回e的右兄弟或者空
TElemType rightSibling(BiTree T,TElemType e)
{
	TElemType a;
	BiTree p;
	if(T)
	{
		a=parent(T,e);
		if(a!=Nil)
		{
			p=point(T,a);
			if(p->LTag==Link&&p->RTag==Link&&p->lchild->data==e)
				return p->rchild->data;
		}
	}
	return Nil;
}


};

//测试二叉树主函数
void testBiThrTreeMain()
{
	using namespace LKTHR;
	BiThrTree T=NULL,H=NULL;
	BiThrTree T1=NULL,H1=NULL;
	BiThrTree p,q,r;
	TElemType e1,e2;
	createBiTree(T);
	createBiTree(T1,2);
#if CHAR
	
#else

#endif
	inOrderThreading(H,T);
	cout<<"in order traverse tree:\n";
	inOrderTraverse_Thr(H,visit_tree);

	preOrderThreading(H1,T1);
	cout<<"pre order traverse tree:\n";
	preOrderTraverse_Thr(H1,visit_tree);
	cout<<"depth or T1 is "<<biTreeDepth(T1)<<endl;
#if CHAR
	
#else
	e1=3;
	e2=parent(T1,e1);
	cout<<"e1's parent is "<<e2<<endl;
	p=point(T1,e2);
	cout<<leftChild(T1,e2)<<endl;
	cout<<"left sibling is "<<leftSibling(T1,e1)<<endl;
	cout<<"right sibling is "<<rightSibling(T1,e2)<<endl;
#endif
}