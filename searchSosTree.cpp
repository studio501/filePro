
#include "stdafx.h"


#define N 9
typedef char keyType;
#define key symbo
struct ElemType1
{
	keyType symbo;
	int weight;
};

typedef struct BiTNode
{
	ElemType1 data;
	BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef void(*visit)(ElemType1);

static void print(const ElemType1& c)
{
	printf("(%c  %d)\n",c.key,c.weight);
}

#include "searchSeq.h"

//�ݹ鹹����Ų�����
bool secondOptimal(BiTree &T,ElemType1 R[],int sw[],int low,int high)
{
	int i,j;
	double min,dw;
	i=low;
	min=fabs(sw[high]-sw[low]+0.0);
	dw=sw[high]+sw[low-1];
	for(j=low+1;j<=high;++j)
		if(fabs(0.0+dw-sw[j]-sw[j-1])<min)
		{
			i=j;
			min=fabs(0.0+dw-sw[j]-sw[j-1]);
		}
	if(!(T=(BiTree)malloc(sizeof(BiTNode)))) return false;
	T->data=R[i];
	if(i==low) T->lchild=NULL;
	else
		secondOptimal(T->lchild,R,sw,low,i-1);
	if(i==high)
		T->rchild=NULL;
	else
		secondOptimal(T->rchild,R,sw,i+1,high);
	return true;
}

//��������и�Ԫ�ص�weight�����ۼ�Ȩֵ��
template<class T>
void findSW(int sw[],SSTable<T> ST)
{
	int i;
	sw[0]=0;
	for(i=1;i<=ST.lenght;++i)
		sw[i]=sw[i-1]+ST.elem[i].weight;
}

typedef BiTree SOSTree;

//���������һ�ô��Ų�����
template<class T>
void createSOSTree(SOSTree &Tree,SSTable<T> ST)
{
	int sw[N+1];
	if(ST.lenght==0) Tree=NULL;
	else
	{
		findSW(sw,ST);
		secondOptimal(Tree,ST.elem,sw,1,ST.lenght);
	}
}

//�ڴ��Ų������в��ҹؼ���
bool search_SOSTree(SOSTree &T,keyType key_)
{
	while(T)
		if(T->data.key==key_)
			return true;
		else if(T->data.key>key_)
			T=T->lchild;
		else
			T=T->rchild;
	return false;
}

void testSosTree()
{
	SSTable<ElemType1> st;
	SOSTree t;
	bool i;
	keyType s;
	ElemType1 a;
	a.weight=100;
	cout<<"size in test is "<<sizeof(ElemType1)<<endl;
	ElemType1 rr[N] = {{'A',1},{'B',1},{'C',2},{'D',5},{'E',3},{'F',4},{'G',4},{'H',3},{'I',5}};
	//char c = r[0].key;
	create_Ord(st,rr,N);
	//create_Seq<ElemType1>(st,rr,N);
	/*traverse<ElemType1>(st, [](const ElemType1& c){
		printf("(%c  %d)\n",c.key,c.weight);
	});*/
	traverse<ElemType1>(st, print);
	createSOSTree(t,st);

	cout<<"\n����������ҵ��ַ�:";
	cin>>s;
	
	i=search_SOSTree(t,s);
	if(i)
		printf("%c��Ȩֵ��%d\n",s,t->data.weight);
	else
		printf("���в����ڴ��ַ�\n");

}
