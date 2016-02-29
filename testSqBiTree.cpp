
#include "stdafx.h"
#include "testSqBiTree.h"
#include "queueTest.h"

//打印函数
void visit_tree(TElemType e)
{
	cout<<e<<" ";
}

//构造空二叉树T
void initBiTree(SqBiTree T)
{
	int i;
	for(i=0;i<MAX_TREE_SIZE;++i)
		T[i]=Nil;
}

//按层次顺序输入二叉树中的结点值
void createBiTree(SqBiTree T,int nLine)
{
	int i=0;
	initBiTree(T);
#if CHAR
	int l;
	char s[MAX_TREE_SIZE];
	ifstream fin("charBitTree.txt",ios_base::in);
	if(fin.is_open())
	{
		int curLine=0;
		while(curLine<nLine)
		{
			fin.getline(s,MAX_TREE_SIZE);
			++curLine;
		}

		while(s[i]!='\0')
		{
			if(s[i]=='#')
			{
				T[i]=Nil;
			}
			else T[i]=s[i];
			++i;
		}
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
	for(i=1;i<MAX_TREE_SIZE;++i)
		if(i!=0&&T[(i+1)/2-1]==Nil&&T[i]!=Nil)
		{
			cout<<"出现无双亲的非根结点"<<T[i]<<endl;
			system("pause");
		}
}

//判断二叉树是否为空
bool biTreeEmpty(SqBiTree T)
{
	if(T[0]==Nil)
		return true;
	else return false;
}

//求树的深度
int biTreeDepth(SqBiTree T)
{
	int i,j=-1;
	for(i=MAX_TREE_SIZE-1;i>=0;--i)
		if(T[i]!=Nil)
			break;
	++i;
	do 
	{
		++j;
	} while (i>=pow(2,j));
	return j;
}

//返回树的根
bool root(SqBiTree T,TElemType &e)
{
	if(biTreeEmpty(T)) return false;
	else
	{
		e=T[0];
		return true;
	}
}

//返回处于位置e的结点的值
TElemType value(SqBiTree T,position e)
{
	return T[(int)(pow(2,e.level-1)+e.order-2)];
}

//给处于e的位置赋新值
bool assign(SqBiTree T,position e,TElemType value)
{
	int i=int(pow(2,e.level-1)+e.order-2);
	if(value!=Nil&&T[(i+1)/2-1]==Nil)
		return false;
	else if(value==Nil&&(T[i*2+1]!=Nil||T[i*2+2]!=Nil))
		return false;
	T[i]=value;
	return true;
}

//若e是树的非根结点,则返回它的双亲,否则返回空
TElemType parent(SqBiTree T,TElemType e)
{
	int i;
	if(T[0]==Nil) return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;++i)
		if(T[i]==e)
			return T[(i+1)/2-1];
	return Nil;
}

//返回e的左孩子
TElemType leftChild(SqBiTree T,TElemType e)
{
	int i;
	if(biTreeEmpty(T)) return Nil;
	for(i=0;i<=MAX_TREE_SIZE-1;++i)
		if(T[i]==e)
			return T[i*2+1];
	return Nil;
}

//返回e的右孩子
TElemType rightChild(SqBiTree T,TElemType e)
{
	int i;
	if(biTreeEmpty(T)) return Nil;
	for(i=0;i<=MAX_TREE_SIZE-1;++i)
		if(T[i]==e)
			return T[i*2+2];
	return Nil;
}

//返回e的左孩子或者空
TElemType leftSibling(SqBiTree T,TElemType e)
{
	int i;
	if(biTreeEmpty(T)) return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;++i)
		if(T[i]==e&&i%2==0)
			return T[i-1];
	return Nil;
}

//返回e的右兄弟或者空
TElemType rightSibling(SqBiTree T,TElemType e)
{
	int i;
	if(biTreeEmpty(T)) return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;++i)
		if(T[i]==e&&i%2)
			return T[i+1];
	return Nil;
}

//把从q的j结点开始的子树移为从T的i结点开始的子树
void move(SqBiTree q,int j,SqBiTree T,int i)
{
	if(q[2*j+1]!=Nil)
		move(q,(2*j+1),T,(2*i+1));
	if(q[2*j+2]!=Nil)
		move(q,2*j+2,T,2*i+2);
	T[i]=q[j];
	q[j]=Nil;
}

//插入c为T中p结点的左或右子树
void insertChild(SqBiTree T,TElemType p,int LR,SqBiTree c)
{
	int j,k,i=0;
	for(j=0;j<int(pow(2,biTreeDepth(T)))-1;++j)
		if(T[j]==p)
			break;
	k=2*j+1+LR;
	if(T[k]!=Nil)
		move(T,k,T,2*k+2);
	move(c,i,T,k);
}

//根据LR为1 或0,删除T中p所指结点的左或右子树
bool deleteChild(SqBiTree T,position p,int LR)
{
	int i;
	bool k=true;
	LinkQueue<int> q;
	initQueue(q);
	i=(int)pow(2,p.level-1)+p.order-2;
	if(T[i]==Nil) return false;
	i=i*2+1+LR;
	while(k)
	{
		if(T[2*i+1]!=Nil)
			enQueue(q,2*i+1);
		if(T[2*i+2]!=Nil)
			enQueue(q,2*i+2);
		T[i]=Nil;
		k=deQueue(q,i);
	}
	return true;
}

//先序遍历树
void preTraverse(SqBiTree T,int e,visitFunc func)
{
	func(T[e]);
	if(T[2*e+1]!=Nil)
		preTraverse(T,2*e+1,func);
	if(T[2*e+2]!=Nil)
		preTraverse(T,2*e+2,func);
}

//先序遍历树
void preOrderTraverse(SqBiTree T,visitFunc func)
{
	cout<<"preorder traverse tree:\n";
	if(!biTreeEmpty(T))
		preTraverse(T,0,func);
	cout<<endl;
}

//中序遍历结点
void inTraverse(SqBiTree T,int e,visitFunc func)
{
	if(T[2*e+1]!=Nil)
		inTraverse(T,2*e+1,func);
	func(T[e]);
	if(T[2*e+2]!=Nil)
		inTraverse(T,2*e+2,func);
}

//中序遍历树
void inOrderTraverse(SqBiTree T,visitFunc func)
{
	cout<<"inoreder traverse tree:\n";
	if(!biTreeEmpty(T))
		inTraverse(T,0,func);
	cout<<endl;
}

//后序遍历结点
void postTraverse(SqBiTree T,int e,visitFunc func)
{
	if(T[2*e+1]!=Nil)
		postTraverse(T,2*e+1,func);
	if(T[2*e+2]!=Nil)
		postTraverse(T,2*e+2,func);
	func(T[e]);
}

//后序遍历树
void postOrderTraverse(SqBiTree T,visitFunc func)
{
	cout<<"postorder traverse tree:\n";
	if(!biTreeEmpty(T))
		postTraverse(T,0,func);
	cout<<endl;
}

//层序遍历树
void levelOrderTraverse(SqBiTree T,visitFunc func)
{
	cout<<"level traverse tree:\n";
	int i=MAX_TREE_SIZE-1,j;
	while(T[i]==Nil) --i;
	for(j=0;j<=i;++j)
		if(T[j]!=Nil)
			func(T[j]);
	cout<<endl;
		
}

//逐层,按序号输出二叉树
void print(SqBiTree T)
{
	int j,k;
	position p;
	TElemType e;
	for(j=1;j<=biTreeDepth(T);++j)
	{
		cout<<"第"<<j<<"层: ";
		for(k=1;k<=pow(2,j-1);++k)
		{
			p.level=j;
			p.order=k;
			e=value(T,p);
			if(e!=Nil)
				cout<<k<<": "<<e<<" ";
		}
		cout<<endl;
	}
}

//测试二叉树主函数
void testSqBiTreeMain()
{
#if CHAR
	SqBiTree T;
	createBiTree(T,2);
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