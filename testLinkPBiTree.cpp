
#include "stdafx.h"
#include "testLinkPBiTree.h"
#include "queueTest.h"
#include <stack>

namespace LKPT{
typedef BiPTree QElemType;
typedef BiPTree SElemType;

//��ӡ����
void visit_tree(TElemType e)
{
	cout<<e<<" ";
}

//����ն�����T
void initBiTree(BiPTree &T)
{
	T=NULL;
}

//������
void destroyBiTree(BiPTree &T)
{
	if(T)
	{
		if(T->lchild) destroyBiTree(T->lchild);
		if(T->rchild) destroyBiTree(T->rchild);
		free(T);
		T=NULL;
	}
}

//����һ�������
void makeBiTreeNode(BiPTree &T,TElemType *buf,int &i)
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
		T=(BiPTree)malloc(sizeof(BiTPNode));
		if(!T) exit(OVERFLOW);
		T->data=ch;
		T->parent=NULL;
		++i;
		makeBiTreeNode(T->lchild,buf,i);
		if(T->lchild) T->lchild->parent=T;
		makeBiTreeNode(T->rchild,buf,i);
		if(T->rchild) T->rchild->parent=T;
	}
}

//�����˳������������еĽ��ֵ
void createBiTree(BiPTree &T,int nLine)
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

//�ж϶������Ƿ�Ϊ��
bool biTreeEmpty(BiPTree T)
{
	if(T) return false;
	else return true;
}

//���������
int biTreeDepth(BiPTree T)
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

//�������ĸ�
TElemType root(BiPTree T)
{
	if(biTreeEmpty(T)) return Nil;
	else return T->data;	
}

//���ش���λ��e�Ľ���ֵ
TElemType value(BiPTree p)
{
	return p->data;
}

//������e��λ�ø���ֵ
void assign(BiPTree p,TElemType value)
{
	p->data=value;
}

//��e�����ķǸ����,�򷵻�����˫��,���򷵻ؿ�
TElemType parent(BiPTree T,TElemType e)
{
	BiPTree a;
	if(T)
	{
		a=point(T,e);
		if(a&&a!=T)
			return a->parent->data;
	}
	return Nil;
}

//���ض�������ָ��Ԫ��ֵΪs�Ľ���ָ��
BiPTree point(BiPTree T,TElemType s)
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

//����e������
TElemType leftChild(BiPTree T,TElemType e)
{
	
	BiPTree a;
	if(T)
	{
		a=point(T,e);
		if(a&&a->lchild)
			return a->lchild->data;
	}
	return Nil;
}

//����e���Һ���
TElemType rightChild(BiPTree T,TElemType e)
{
	
	BiPTree a;
	if(T)
	{
		a=point(T,e);
		if(a&&a->rchild)
			return a->rchild->data;
	}
	return Nil;
}

//����e�����ӻ��߿�
TElemType leftSibling(BiPTree T,TElemType e)
{
	
	BiPTree a;
	if(T)
	{
		a=point(T,e);
		if(a&&a!=T&&a->parent->lchild&&a->parent->lchild!=a)
			return a->parent->lchild->data;
	}
	return Nil;
}

//����e�����ֵܻ��߿�
TElemType rightSibling(BiPTree T,TElemType e)
{
	BiPTree a;
	if(T)
	{
		a=point(T,e);
		if(a&&a!=T&&a->parent->rchild&&a->parent->rchild!=a)
			return a->parent->rchild->data;
	}
	return Nil;
}

//����cΪT��p�������������
bool insertChild(BiPTree p,int LR,BiPTree c)
{
	if(p)
	{
		if(LR==0)
		{
			c->rchild=p->lchild;
			if(c->rchild) c->rchild->parent=c;
			p->lchild=c;
			c->parent=p;
		}
		else
		{
			c->rchild=p->rchild;
			if(c->rchild) c->rchild->parent=c;
			p->rchild=c;
			c->parent=p;
		}
		return true;
	}
	return false;
}

//����LRΪ1 ��0,ɾ��T��p��ָ�������������
bool deleteChild(BiPTree p,int LR)
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


//���������
void preOrderTraverse(BiPTree T,visitFunc func)
{
	if(T)
	{
		func(T->data);
		preOrderTraverse(T->lchild,func);
		preOrderTraverse(T->rchild,func);
	}
}

//���������
void inOrderTraverse(BiPTree T,visitFunc func)
{
	if(T)
	{
		inOrderTraverse(T->lchild,func);
		func(T->data);
		inOrderTraverse(T->rchild,func);
	}
}

//�������(�ǵݹ�)
void inOrderTraverse1(BiPTree T,visitFunc func)
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

//�������(�ǵݹ�)
void inOrderTraverse2(BiPTree T,visitFunc func)
{
	stack<SElemType> S;
	BiPTree p;
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

//���������
void postOrderTraverse(BiPTree T,visitFunc func)
{
	if(T)
	{
		inOrderTraverse(T->lchild,func);
		inOrderTraverse(T->rchild,func);
		func(T->data);
	}
}

//�������
void levelOrderTraverse(BiPTree T,visitFunc func)
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
			func(a->data);
			if(a->lchild!=NULL) enQueue(q,a->lchild);
			if(a->rchild!=NULL) enQueue(q,a->rchild);
		}
	}
	cout<<endl;
}

};

//���Զ�����������
void testLinkBiPTreeMain()
{
	using namespace LKPT;
	BiPTree T=NULL,p,c;
	TElemType e1,e2;
#if CHAR
	createBiTree(T);
#else
	createBiTree(T);
#endif
	cout<<"pre order traverse:\n";
	preOrderTraverse(T,visit_tree);
	cout<<"\nin order traverse:\n";
	inOrderTraverse(T,visit_tree);
	cout<<"\ndepth is : "<<biTreeDepth(T)<<endl;
	cout<<"in order traverse1:\n";
	inOrderTraverse1(T,visit_tree);
	cout<<"in order traverse2:\n";
	inOrderTraverse2(T,visit_tree);
	cout<<"level order traverse:\n";
	levelOrderTraverse(T,visit_tree);
	e1=root(T);
	cout<<"root is : ";
	visit_tree(e1);
	cout<<endl;
	p=point(T,e1);
	cout<<"node value is "<<value(p)<<endl;
	cout<<"input new value: k";
	e2='k';
	assign(p,e2);
	cout<<"level order traverse:\n";
	levelOrderTraverse(T,visit_tree);
	c=p->lchild;
	levelOrderTraverse(c,visit_tree);
#if CHAR
	createBiTree(c,2);
	cout<<"pre order traverse c :\n";
	preOrderTraverse(c,visit_tree);
	e1='b';
	int i=1;
	p=point(T,e1);
	insertChild(p,i,c);
	cout<<"\nlevel order traverse:\n";
	levelOrderTraverse(T,visit_tree);
#else
	
#endif
}