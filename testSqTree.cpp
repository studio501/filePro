
#include "stdafx.h"
#include "testSqTree.h"
#include "queueTest.h"
#include <stack>

namespace SQT{
typedef struct  
{
	int num;
	TElemType name;
}QElemType;
typedef BiTree SElemType;

//打印函数
void visit_tree(TElemType e)
{
	cout<<e<<" ";
}

//构造空二叉树T
void initBiTree(PTree &T)
{
	T.n=0;
}



//创建一个树结点
void makeBiTreeNode(BiTree &T,TElemType *buf,int &i)
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
		T=(BiTree)malloc(sizeof(BiTNode));
		if(!T) exit(OVERFLOW);
		T->data=ch;
		++i;
		makeBiTreeNode(T->lchild,buf,i);
		makeBiTreeNode(T->rchild,buf,i);
	}
}

//按层次顺序输入二叉树中的结点值
void createBiTree(PTree &T,int nLine)
{
	initBiTree(T);
	LinkQueue<QElemType> q;
	QElemType p,qq;
	initQueue(q);
	int i=0,j=0,l;
	TElemType s[MAX_TREE_SIZE];
	ifstream fin;
#if CHAR
	fin.open("charTree.txt",ios_base::in);
	if(fin.is_open())
	{
		int curLine=0;
		while(curLine<nLine)
		{
			fin.getline(s,MAX_TREE_SIZE);
			++curLine;
		}
		T.nodes[i].data = s[i];
		if(T.nodes[i].data!=Nil)
		{
			T.nodes[i].parent = -1;
			qq.name=T.nodes[i].data;
			qq.num=i;
			enQueue(q,qq);
			while(s[++i]!='\0')
			{
				while(i<MAX_TREE_SIZE&&!isQueueEmpty(q))
				{
					if(s[i]!=BranchEnd)
					{
						++j;
						deQueue(q,qq);
						T.nodes[j].data=s[i];
						T.nodes[j].parent=qq.num;
						p.name=s[i];
						p.num=j;
						enQueue(q,p);
					}
				}
			}
			if(j>MAX_TREE_SIZE) exit(OVERFLOW);
			T.n=j;
		}
		else
			T.n=0;
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
	if(T->lchild)
		i=biTreeDepth(T->lchild);
	else
		i=0;
	if(T->rchild)
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
	return Nil;
}

//返回二叉树中指向元素值为s的结点的指针
BiTree point(BiTree T,TElemType s)
{
	
	return NULL;
}

//返回e的左孩子
TElemType leftChild(BiTree T,TElemType e)
{
	
	BiTree a;
	if(T)
	{
		a=point(T,e);
		if(a&&a->lchild)
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
		if(a&&a->rchild)
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
			if(p->lchild&&p->rchild&&p->rchild->data==e)
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
			if(p->lchild&&p->rchild&&p->lchild->data==e)
				return p->rchild->data;
		}
	}
	return Nil;
}

//插入c为T中p结点的左或右子树
bool insertChild(BiTree p,int LR,BiTree c)
{
	if(p)
	{
		if(LR==0)
		{
			c->rchild=p->lchild;
			p->lchild=c;
		}
		else
		{
			c->rchild=p->rchild;
			p->rchild=c;
		}
		return true;
	}
	return false;
}

//根据LR为1 或0,删除T中p所指结点的左或右子树
bool deleteChild(BiTree p,int LR)
{
	
	return false;
}


//先序遍历树
void preOrderTraverse(BiTree T,visitFunc func)
{
	if(T)
	{
		func(T->data);
		preOrderTraverse(T->lchild,func);
		preOrderTraverse(T->rchild,func);
	}
}

//中序遍历树
void inOrderTraverse(BiTree T,visitFunc func)
{
	if(T)
	{
		inOrderTraverse(T->lchild,func);
		func(T->data);
		inOrderTraverse(T->rchild,func);
	}
}

//中序遍历(非递归)
void inOrderTraverse1(BiTree T,visitFunc func)
{
	stack<SElemType> S;
	while(T||!S.empty())
	{
		if(T)
		{
			S.push(T);
			T=T->lchild;
		}
		else
		{
			T = S.top();
			S.pop();
			func(T->data);
			T=T->rchild;
		}
	}
	cout<<endl;
}

//中序遍历(非递归)
void inOrderTraverse2(BiTree T,visitFunc func)
{
	stack<SElemType> S;
	BiTree p;
	S.push(T);
	while(!S.empty())
	{
		p = S.top();
		while(p)
		{
			S.push(p->lchild);
			p = S.top();
		}
		p=S.top();
		S.pop();
		if(!S.empty())
		{
			p = S.top();
			S.pop();
			func(p->data);
			S.push(p->rchild);
		}
	}
	cout<<endl;
}

//后序遍历树
void postOrderTraverse(BiTree T,visitFunc func)
{
	if(T)
	{
		inOrderTraverse(T->lchild,func);
		inOrderTraverse(T->rchild,func);
		func(T->data);
	}
}

//层序遍历
void levelOrderTraverse(BiTree T,visitFunc func)
{
	
	cout<<endl;
}


};

//测试二叉树主函数
void testSqTreeMain()
{
	using namespace SQT;
	PTree T,p,c;
	TElemType e1,e2;
#if CHAR
	createBiTree(T);
#else
	createBiTree(T);
#endif
	
#if CHAR
	
#else
	
#endif
}