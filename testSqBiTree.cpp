
#include "stdafx.h"
#include "testSqBiTree.h"
#include "queueTest.h"

//��ӡ����
void visit_tree(TElemType e)
{
	cout<<e<<" ";
}

//����ն�����T
void initBiTree(SqBiTree T)
{
	int i;
	for(i=0;i<MAX_TREE_SIZE;++i)
		T[i]=Nil;
}

//�����˳������������еĽ��ֵ
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
	for(i=1;i<MAX_TREE_SIZE;++i)
		if(i!=0&&T[(i+1)/2-1]==Nil&&T[i]!=Nil)
		{
			cout<<"������˫�׵ķǸ����"<<T[i]<<endl;
			system("pause");
		}
}

//�ж϶������Ƿ�Ϊ��
bool biTreeEmpty(SqBiTree T)
{
	if(T[0]==Nil)
		return true;
	else return false;
}

//���������
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

//�������ĸ�
bool root(SqBiTree T,TElemType &e)
{
	if(biTreeEmpty(T)) return false;
	else
	{
		e=T[0];
		return true;
	}
}

//���ش���λ��e�Ľ���ֵ
TElemType value(SqBiTree T,position e)
{
	return T[(int)(pow(2,e.level-1)+e.order-2)];
}

//������e��λ�ø���ֵ
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

//��e�����ķǸ����,�򷵻�����˫��,���򷵻ؿ�
TElemType parent(SqBiTree T,TElemType e)
{
	int i;
	if(T[0]==Nil) return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;++i)
		if(T[i]==e)
			return T[(i+1)/2-1];
	return Nil;
}

//����e������
TElemType leftChild(SqBiTree T,TElemType e)
{
	int i;
	if(biTreeEmpty(T)) return Nil;
	for(i=0;i<=MAX_TREE_SIZE-1;++i)
		if(T[i]==e)
			return T[i*2+1];
	return Nil;
}

//����e���Һ���
TElemType rightChild(SqBiTree T,TElemType e)
{
	int i;
	if(biTreeEmpty(T)) return Nil;
	for(i=0;i<=MAX_TREE_SIZE-1;++i)
		if(T[i]==e)
			return T[i*2+2];
	return Nil;
}

//����e�����ӻ��߿�
TElemType leftSibling(SqBiTree T,TElemType e)
{
	int i;
	if(biTreeEmpty(T)) return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;++i)
		if(T[i]==e&&i%2==0)
			return T[i-1];
	return Nil;
}

//����e�����ֵܻ��߿�
TElemType rightSibling(SqBiTree T,TElemType e)
{
	int i;
	if(biTreeEmpty(T)) return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;++i)
		if(T[i]==e&&i%2)
			return T[i+1];
	return Nil;
}

//�Ѵ�q��j��㿪ʼ��������Ϊ��T��i��㿪ʼ������
void move(SqBiTree q,int j,SqBiTree T,int i)
{
	if(q[2*j+1]!=Nil)
		move(q,(2*j+1),T,(2*i+1));
	if(q[2*j+2]!=Nil)
		move(q,2*j+2,T,2*i+2);
	T[i]=q[j];
	q[j]=Nil;
}

//����cΪT��p�������������
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

//����LRΪ1 ��0,ɾ��T��p��ָ�������������
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

//���������
void preTraverse(SqBiTree T,int e,visitFunc func)
{
	func(T[e]);
	if(T[2*e+1]!=Nil)
		preTraverse(T,2*e+1,func);
	if(T[2*e+2]!=Nil)
		preTraverse(T,2*e+2,func);
}

//���������
void preOrderTraverse(SqBiTree T,visitFunc func)
{
	cout<<"preorder traverse tree:\n";
	if(!biTreeEmpty(T))
		preTraverse(T,0,func);
	cout<<endl;
}

//����������
void inTraverse(SqBiTree T,int e,visitFunc func)
{
	if(T[2*e+1]!=Nil)
		inTraverse(T,2*e+1,func);
	func(T[e]);
	if(T[2*e+2]!=Nil)
		inTraverse(T,2*e+2,func);
}

//���������
void inOrderTraverse(SqBiTree T,visitFunc func)
{
	cout<<"inoreder traverse tree:\n";
	if(!biTreeEmpty(T))
		inTraverse(T,0,func);
	cout<<endl;
}

//����������
void postTraverse(SqBiTree T,int e,visitFunc func)
{
	if(T[2*e+1]!=Nil)
		postTraverse(T,2*e+1,func);
	if(T[2*e+2]!=Nil)
		postTraverse(T,2*e+2,func);
	func(T[e]);
}

//���������
void postOrderTraverse(SqBiTree T,visitFunc func)
{
	cout<<"postorder traverse tree:\n";
	if(!biTreeEmpty(T))
		postTraverse(T,0,func);
	cout<<endl;
}

//���������
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

//���,��������������
void print(SqBiTree T)
{
	int j,k;
	position p;
	TElemType e;
	for(j=1;j<=biTreeDepth(T);++j)
	{
		cout<<"��"<<j<<"��: ";
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

//���Զ�����������
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