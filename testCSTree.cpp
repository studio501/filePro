
#include "stdafx.h"
#include "testCSTree.h"
#include "queueTest.h"
#include <stack>

namespace CST{
typedef CSTree QElemType;
typedef BiTree SElemType;

//��ӡ����
void visit_tree(TElemType e)
{
	cout<<e<<" ";
}

//����ն�����T
void initBiTree(CSTree &T)
{
	T=NULL;
}

//������
void destroyBiTree(CSTree &T)
{
	if(T)
	{
		if(T->firstchild) destroyBiTree(T->firstchild);
		if(T->nextsibling) destroyBiTree(T->nextsibling);
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
void createBiTree(CSTree &T,int nLine)
{
	initBiTree(T);
	LinkQueue<QElemType> q;
	QElemType p,pl;
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
		
		if(s[0]!=Nil)
		{
			T=(CSTree)malloc(sizeof(CSNode));
			T->data=s[0];
			T->nextsibling=NULL;
			enQueue(q,T);

			bool isFirst = false;

			while(s[++i]!=EndFlag&&i<MAX_TREE_SIZE)
			{
				if(s[i]!=BranchEnd)
				{
					if(s[i]!=Nil)
					{
						if(isFirst)
						{
							pl=p->firstchild=(CSTree)malloc(sizeof(CSNode));
							pl->data=s[i];
							pl->nextsibling=NULL;
							isFirst = false;
						}
						else
						{
							pl->nextsibling=(CSTree)malloc(sizeof(CSNode));
							
							pl=pl->nextsibling;
							pl->data=s[i];
							pl->nextsibling=NULL;
							
						}
						enQueue(q,pl);
					}
					else
					{
						p->firstchild=NULL;
					}
						
				}
				else
				{
					isFirst = true;
					deQueue(q,p);
				}
			}
		}
		else
			T=NULL;
		fin.close();
	}
#else
	
#endif
}

//�ж϶������Ƿ�Ϊ��
bool biTreeEmpty(CSTree T)
{
	if(T) return false;
	else return true;
}

//���������
int biTreeDepth(CSTree T)
{
	CSTree p;
	int depth,max=0;
	if(!T) return 0;
	if(!T->firstchild) return 1;
	for(p=T->firstchild;p;p=p->nextsibling)
	{
		depth = biTreeDepth(p);
		max = (depth>max?depth:max);
	}
	return max+1;
}

//�������ĸ�
TElemType root(CSTree T)
{
	if(T) return value(T);
	else return Nil;
}

//���ش���λ��e�Ľ���ֵ
TElemType value(CSTree p)
{
	return p->data;
}

//������e��λ�ø���ֵ
void assign(CSTree &T,TElemType cur_e,TElemType value)
{
	CSTree p;
	if(T)
	{
		p=point(T,cur_e);
		if(p)
		{
			p->data=value;
		}
	}
}

//��e�����ķǸ����,�򷵻�����˫��,���򷵻ؿ�
TElemType parent(CSTree T,TElemType e)
{
	CSTree p,t;
	LinkQueue<QElemType> q;
	initQueue(q);
	if(T)
	{
		if(value(T)==e) return Nil;
		enQueue(q,T);
		while(!isQueueEmpty(q))
		{
			deQueue(q,p);
			if(p->firstchild)
			{
				if(p->firstchild->data==e)
					return value(p);
				t=p;
				p=p->firstchild;
				enQueue(q,p);
				while(p->nextsibling)
				{
					p=p->nextsibling;
					if(value(p)==e) return value(t);
					enQueue(q,p);
				}
			}
		}
	}
	return Nil;
}

//���ض�������ָ��Ԫ��ֵΪs�Ľ���ָ��
CSTree point(CSTree T,TElemType s)
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
			if(a->data==s) return a;
			if(a->firstchild)
				enQueue(q,a->firstchild);
			if(a->nextsibling)
				enQueue(q,a->nextsibling);
		}
	}
	return NULL;
}

//����e������
TElemType leftChild(CSTree T,TElemType e)
{
	CSTree f;
	f=point(T,e);
	if(f&&f->firstchild)
		return f->firstchild->data;
	else
		return Nil;
}

//����e�����ֵܻ��߿�
TElemType rightSibling(CSTree T,TElemType e)
{
	CSTree f;
	f=point(T,e);
	if(f&&f->nextsibling)
		return f->nextsibling->data;
	else
		return Nil;
}

//����cΪT��p�������������
bool insertChild(CSTree &T,CSTree p,int i,CSTree c)
{
	int j;
	if(T)
	{
		if(i==1)
		{
			c->nextsibling=p->firstchild;
			p->firstchild=c;
		}
		else
		{
			p=p->nextsibling;
			j=2;
			while(p&&j<i)
			{
				p=p->nextsibling;
				++j;
			}
			if(j==i)
			{
				c->nextsibling=p->nextsibling;
				p->nextsibling=c;
			}
			else
				return false;
		}
		return true;
	}
	else return false;
}

//����LRΪ1 ��0,ɾ��T��p��ָ�������������
bool deleteChild(CSTree &T,CSTree p, int i)
{
	CSTree b;
	int j;
	if(T)
	{
		if(i==1)
		{
			b=p->firstchild;
			p->firstchild=b->nextsibling;
			b->nextsibling=NULL;
			destroyBiTree(b);
		}
		else
		{
			p=p->firstchild;
			j=2;
			while(p&&j<i)
			{
				p=p->nextsibling;
				++j;
			}
			if(j==i)
			{
				b=p->nextsibling;
				p->nextsibling=b->nextsibling;
				b->nextsibling=NULL;
				destroyBiTree(b);
			}
			else return false;
		}
		return true;
	}
	else return false;
}

//���������
void postOrderTraverse(CSTree T,visitFunc func)
{
	CSTree p;
	if(T)
	{
		if(T->firstchild)
		{
			postOrderTraverse(T->firstchild,func);
			p=T->firstchild->nextsibling;
			while(p)
			{
				postOrderTraverse(p,func);
				p=p->nextsibling;
			}
		}
		func(value(T));
	}
}

//�������
void levelOrderTraverse(CSTree T,visitFunc func)
{
	CSTree p;
	LinkQueue<QElemType> q;
	initQueue(q);
	if(T)
	{
		func(value(T));
		enQueue(q,T);
		while(!isQueueEmpty(q))
		{
			deQueue(q,p);
			if(p->firstchild)
			{
				p=p->firstchild;
				func(value(p));
				enQueue(q,p);
				while(p->nextsibling)
				{
					p=p->nextsibling;
					func(value(p));
					enQueue(q,p);
				}
			}
		}
	}
}


};

//���Զ�����������
void testCSTreeMain()
{
	using namespace CST;
	CSTree T=NULL,T1=NULL,p,c;
	TElemType e1,e2;
#if CHAR
	createBiTree(T);
	cout<<"depth is "<<biTreeDepth(T)<<endl;
	p=point(T,'A');
	cout<<p->data<<endl;
	assign(T,p->data,'V');
	cout<<parent(T,'V')<<endl;
	cout<<"left child is "<<leftChild(T,'V')<<endl;
	cout<<"right sibling is "<<rightSibling(T,'D')<<endl;
	createBiTree(T1,2);
	insertChild(T,point(T,'V'),2,T1);
	bool b = deleteChild(T,point(T,'V'),2);
	postOrderTraverse(T,visit_tree);
	cout<<endl;
	levelOrderTraverse(T,visit_tree);
	int a = 100;
#else
	createBiTree(T);
#endif
	
#if CHAR
	
#else
	
#endif
}