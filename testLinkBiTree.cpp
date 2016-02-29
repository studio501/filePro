
#include "stdafx.h"
#include "testLinkBiTree.h"
#include "queueTest.h"
#include "testStack.h"

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

//�����˳������������еĽ��ֵ
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
	//cout<<"�밴�����������ֵ(����)��0��ʾ�ս�㣬��999�������������"<<MAX_TREE_SIZE<<":"<<endl;
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

//���,��������������
void print(BiTree T)
{
	
}

};

//���Զ�����������
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
	cout<<"��������޸Ľ��Ĳ�ű������: 2 2\n";
	//cin>>p.level>>p.order;
	p.level=2;p.order=2;
	e=value(T,p);
	cout<<"���޸Ľ���ԭֵΪ"<<e<<"��������ֵ: 8";
	//cin>>e;
	e=8;
	assign(T,p,e);
	preOrderTraverse(T,visit_tree);
	cout<<"���"<<e<<"��˫��Ϊ"<<parent(T,e)<<",���Һ��ӷֱ�Ϊ";
	cout<<leftChild(T,e)<<","<<rightChild(T,e)<<",�����ֱֵܷ�Ϊ";
	cout<<leftSibling(T,e)<<","<<rightSibling(T,e)<<endl;
	createBiTree(s,2);
	cout<<"��s�嵽��T��,��������T����s��˫�׽��sΪ��(0)����(1)����: 2 1\n";
	//cin>>e>>j;
	e=2;j=1;
	insertChild(T,e,j,s);
	print(T);
	clearBiTree(T);
	if(root(T,e)) cout<<e<<endl;
	else cout<<"����,�޸�\n";
#endif
	
	
}