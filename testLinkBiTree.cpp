
#include "stdafx.h"
#include "testLinkBiTree.h"
#include "queueTest.h"
#include <stack>

namespace LKT{
typedef BiTree QElemType;
typedef BiTree SElemType;

//��ӡ����
void visit_tree(TElemType e)
{
	cout<<e<<" ";
}

//����ն�����T
void initBiTree(BiTree &T)
{
	T=NULL;
}

//������
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

//����һ�������
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

//�����˳������������еĽ��ֵ
void createBiTree(BiTree &T,int nLine)
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
bool biTreeEmpty(BiTree T)
{
	if(T) return false;
	else return true;
}

//���������
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

//�������ĸ�
TElemType root(BiTree T)
{
	if(biTreeEmpty(T)) return Nil;
	else return T->data;	
}

//���ش���λ��e�Ľ���ֵ
TElemType value(BiTree p)
{
	return p->data;
}

//������e��λ�ø���ֵ
void assign(BiTree p,TElemType value)
{
	p->data=value;
}

//��e�����ķǸ����,�򷵻�����˫��,���򷵻ؿ�
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

//���ض�������ָ��Ԫ��ֵΪs�Ľ���ָ��
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

//����e������
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

//����e���Һ���
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

//����e�����ӻ��߿�
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

//����e�����ֵܻ��߿�
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

//����cΪT��p�������������
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

//����LRΪ1 ��0,ɾ��T��p��ָ�������������
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


//���������
void preOrderTraverse(BiTree T,visitFunc func)
{
	if(T)
	{
		func(T->data);
		preOrderTraverse(T->lchild,func);
		preOrderTraverse(T->rchild,func);
	}
}

//���������
void inOrderTraverse(BiTree T,visitFunc func)
{
	if(T)
	{
		inOrderTraverse(T->lchild,func);
		func(T->data);
		inOrderTraverse(T->rchild,func);
	}
}

//�������(�ǵݹ�)
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

//�������(�ǵݹ�)
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

//���������
void postOrderTraverse(BiTree T,visitFunc func)
{
	if(T)
	{
		inOrderTraverse(T->lchild,func);
		inOrderTraverse(T->rchild,func);
		func(T->data);
	}
}

//�������
void levelOrderTraverse(BiTree T,visitFunc func)
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

//���,��������������
void print(BiTree T)
{
	
}

};

//���Զ�����������
void testLinkBiTreeMain()
{
	using namespace LKT;
	BiTree T=NULL,p,c;
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
}