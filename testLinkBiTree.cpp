
#include "stdafx.h"
#include "testLinkBiTree.h"
#include "queueTest.h"
#include "testStack.h"

namespace LKT{
typedef BiTree QElemType;
typedef BiTree SElemType;

//打印函数
void visit_tree(TElemType e)
{
	cout<<e<<" ";
}

//构造空二叉树T
void initBiTree(BiTree &T)
{
	T=NULL;
}

//销毁树
void destroyBiTree(BiTree &T)
{
	if(T)
	{
		if(T->lchild) destroyBiTree(T->lchild);
		if(T->rchild) destroyBiTree(T->rchild);
		free(T);
		T=NULL;
	}
}

//创建一个树结点
void makeBiTreeNode(BiTree &T,char *buf,int &i)
{
	if(buf[i]=='\0') return;
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
void createBiTree(BiTree &T,int nLine)
{
	int i=0;
	initBiTree(T);
#if CHAR
	char s[MAX_TREE_SIZE];
	ifstream fin("charBitTreeLink.txt",ios_base::in);
	if(fin.is_open())
	{
		int curLine=0;
		while(curLine<nLine)
		{
			fin.getline(s,MAX_TREE_SIZE);
			++curLine;
		}
		makeBiTreeNode(T,s,i);
	}
#else
	//cout<<"请按层序输入结点的值(整型)，0表示空结点，输999结束。结点数≤"<<MAX_TREE_SIZE<<":"<<endl;
	char s[MAX_TREE_SIZE];
	ifstream fin("intBitTree.txt",ios_base::in);
	if(fin.is_open())
	{
		int curLine=1;
		while(curLine<nLine)
		{
			fin.getline(s,MAX_TREE_SIZE);
			++curLine;
		}

		while(1)
		{
			fin>>T[i];
			if(T[i]==999)
			{
				T[i]=Nil;
				break;
			}
			++i;
		}
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
	if(p)
	{
		if(LR==0)
			clearBiTree(p->lchild);
		else
			clearBiTree(p->rchild);
		return true;
	}
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
	SqStack S;
	initStack(S);
	while(T||!isStackEmpty(S))
	{
		if(T)
		{
			//pushStack(S,T);
		}
	}
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

//逐层,按序号输出二叉树
void print(BiTree T)
{
	
}

};

//测试二叉树主函数
void testLinkBiTreeMain()
{
	using namespace LKT;
#if CHAR
	BiTree T=NULL;
	LKT::createBiTree(T);
	cout<<"pre order traverse:\n";
	preOrderTraverse(T,visit_tree);
	cout<<"in order traverse:\n";
	inOrderTraverse(T,visit_tree);
	cout<<"depth is : "<<biTreeDepth(T)<<endl;
#else
	SqBiTree T,s;
	createBiTree(T);
	cout<<"tree depth "<<biTreeDepth(T)<<endl;
	position p;
	TElemType e;
	int j;
	root(T,e);
	cout<<"root is "<<e<<endl;
	levelOrderTraverse(T,visit_tree);
	inOrderTraverse(T,visit_tree);
	preOrderTraverse(T,visit_tree);
	postOrderTraverse(T,visit_tree);
	cout<<"请输入待修改结点的层号本层序号: 2 2\n";
	//cin>>p.level>>p.order;
	p.level=2;p.order=2;
	e=value(T,p);
	cout<<"待修改结点的原值为"<<e<<"请输入新值: 8";
	//cin>>e;
	e=8;
	assign(T,p,e);
	preOrderTraverse(T,visit_tree);
	cout<<"结点"<<e<<"的双亲为"<<parent(T,e)<<",左右孩子分别为";
	cout<<leftChild(T,e)<<","<<rightChild(T,e)<<",左右兄弟分别为";
	cout<<leftSibling(T,e)<<","<<rightSibling(T,e)<<endl;
	createBiTree(s,2);
	cout<<"树s插到树T中,请输入树T中树s的双亲结点s为左(0)或右(1)子树: 2 1\n";
	//cin>>e>>j;
	e=2;j=1;
	insertChild(T,e,j,s);
	print(T);
	clearBiTree(T);
	if(root(T,e)) cout<<e<<endl;
	else cout<<"树空,无根\n";
#endif
	
	
}