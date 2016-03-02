
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

bool deletedArr[MAX_TREE_SIZE+1];
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
			
			while(s[++i]!='\0'&&i<MAX_TREE_SIZE)
			{
				if(s[i]!=BranchEnd)
				{
					if(s[i]!=Nil)
					{
						++j;
						T.nodes[j].data=s[i];
						T.nodes[j].parent=qq.num;
						p.name=s[i];
						p.num=j;
						enQueue(q,p);
					}
				}
				else
				{
					deQueue(q,qq);
				}
			}
			++j;
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
bool biTreeEmpty(PTree T)
{
	if(T.n) return false;
	else return true;
}

//求树的深度
int biTreeDepth(PTree T)
{
	int k,m,def,max=0;
	for(k=0;k<T.n;++k)
	{
		def=1;
		m=T.nodes[k].parent;
		while(m!=-1)
		{
			m=T.nodes[m].parent;
			++def;
		}
		if(max<def) max=def;
	}
	return max;
}

//返回树的根
TElemType root(PTree T)
{
	int i;
	for(i=0;i<T.n;++i)
		if(T.nodes[i].parent<0)
			return T.nodes[i].data;
	return Nil;
	
}

//返回处于位置e的结点的值
TElemType value(PTree T,int i)
{
	if(i<T.n)
		return T.nodes[i].data;
	else return Nil;
}

//给处于e的位置赋新值
void assign(PTree &T,TElemType cur_e,TElemType value)
{
	for(int j=0;j<T.n;++j)
	{
		if(T.nodes[j].data==cur_e)
		{
			T.nodes[j].data=value;
		}
	}
}

//若e是树的非根结点,则返回它的双亲,否则返回空
TElemType parent(PTree T,TElemType cur_e)
{
	for(int j=1;j<T.n;++j)
		if(T.nodes[j].data==cur_e)
			return T.nodes[T.nodes[j].parent].data;
	return Nil;
}


//返回e的左孩子
TElemType leftChild(PTree T,TElemType e)
{
	
	int i,j;
	for(i=0;i<T.n;++i)
		if(T.nodes[i].data==e)
			break;
	for(j=i+1;j<T.n;++j)
		if(T.nodes[j].parent==i)
			return T.nodes[j].data;
	return Nil;
}

//返回e的右兄弟或者空
TElemType rightSibling(PTree T,TElemType e)
{
	int i;
	for(i=0;i<T.n;++i)
		if(T.nodes[i].data==e)
			break;
	if(T.nodes[i+1].parent==T.nodes[i].parent)
		return T.nodes[i+1].data;
	return Nil;
}

//打印树
void print(PTree T)
{
	int i;
	cout<<"树的结点个数="<<T.n<<endl;
	cout<<"结点      双亲\n";
	for(i=0;i<T.n;++i)
	{
		cout<<"  "<<value(T,i);
		if(T.nodes[i].parent>=0)
			cout<<"        "<<value(T,T.nodes[i].parent);
		cout<<endl;
	}
}

//插入c为T中p结点的左或右子树
bool insertChild(PTree &T,TElemType p,int i,PTree c)
{
	int j,k,l,f=1,n=0;
	PTNode t;
	if(!biTreeEmpty(T))
	{
		for(j=0;j<T.n;++j)
			if(T.nodes[j].data==p)
				break;
		l=j+1;
		if(i>1)
		{
			for(k=j+1;k<T.n;++k)
				if(T.nodes[k].parent==j)
				{
					++n;
					if(n==i-1)
						break;
				}
			l=k+1;
		}
		if(l<T.n)
			for(k=T.n-1;k>=l;--k)
			{
				T.nodes[k+c.n]=T.nodes[k];
				if(T.nodes[k].parent>=1)
					T.nodes[k+c.n].parent+=c.n;
			}
		for(k=0;k<c.n;++k)
		{
			T.nodes[l+k].data=c.nodes[k].data;
			T.nodes[l+k].parent=c.nodes[k].parent+l;
		}
		T.nodes[l].parent=j;
		T.n+=c.n;
		while(f)
		{
			f=0;
			for(j=l;j<T.n-1;++j)
				if(T.nodes[j].parent>T.nodes[j+1].parent)
				{
					t=T.nodes[j];
					T.nodes[j]=T.nodes[j+1];
					T.nodes[j+1]=t;
					f=1;
					for(k=j;k<T.n;++k)
						if(T.nodes[k].parent==j)
							++T.nodes[k].parent;
						else if(T.nodes[k].parent==j+1)
							--T.nodes[k].parent;
				}
		}
		return true;
	}
	else return false;
}

//根据LR为1 或0,删除T中p所指结点的左或右子树
bool deleteChild(PTree &T,TElemType p,int i)
{
	
	int j,k,n=0;
	LinkQueue<QElemType> q;
	QElemType pq,qq;
	for(j=0;j<=T.n;++j)
		deletedArr[j]=false;
	pq.name=Nil;
	initQueue(q);
	for(j=0;j<T.n;++j)
		if(T.nodes[j].data==p)
			break;
	for(k=j+1;k<T.n;++k)
	{
		if(T.nodes[k].parent==j)
			++n;
		if(n==i)
			break;
	}
	if(k<T.n)
	{
		n=0;
		pq.num=k;
		deletedArr[k]=true;
		++n;
		enQueue(q,pq);
		while(!isQueueEmpty(q))
		{
			deQueue(q,qq);
			for(j=qq.num+1;j<T.n;++j)
				if(T.nodes[j].parent==qq.num)
				{
					pq.num=j;
					deletedArr[j]=true;
					++n;
					enQueue(q,pq);
				}
		}
		for(j=0;j<T.n;++j)
			if(deletedArr[j]==true)
			{
				for(k=j+1;k<=T.n;++k)
				{
					deletedArr[k-1]=deletedArr[k];
					T.nodes[k-1]=T.nodes[k];
					if(T.nodes[k].parent>j)
						--T.nodes[k-1].parent;
				}
				--j;
			}
		T.n-=n;
	}
	return true;
}

//遍历树
void traverseTree(PTree T,visitFunc func)
{
	int i;
	for(i=0;i<T.n;++i)
		func(T.nodes[i].data);
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
	cout<<"tree depth is :"<<biTreeDepth(T)<<endl;
	print(T);
	traverseTree(T,visit_tree);
	e1='R';
	assign(T,e1,'V');
	print(T);
	traverseTree(T,visit_tree);
	e1='D';
	cout<<e1<<"的双亲是"<<parent(T,e1)<<"第一个孩子是"<<leftChild(T,e1)<<"下一个兄弟是"<<rightSibling(T,e1)<<endl;

	createBiTree(p,2);
	print(p);
	traverseTree(p,visit_tree);
	e1=root(T);
	int cOrder = 3;
	insertChild(T,e1,cOrder,p);
	print(T);
	traverseTree(T,visit_tree);
	e1 = 'C';
	cOrder = 1;
	deleteChild(T,e1,cOrder);
	print(T);
	traverseTree(T,visit_tree);
#else
	createBiTree(T);
#endif
	
#if CHAR
	
#else
	
#endif
}