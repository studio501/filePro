
#include "stdafx.h"

#define m 3
#define N 16
#define MAX 5
typedef int keyType;

struct Others
{
	char info[MAX];
};
#include "b_tree.h"

#define myBNode BiTNode<Others>
#define myBTree BiTNode<Others>*
#define myRECORD Record<Others>
#define myRESULT Result<Others>
static void print(const myBNode& c,int i)
{
	printf("(%d,%s)\n",c.node[i].key,c.node[i].recptr->other_.info);
}

void testB_Tree()
{
	myRECORD r[N]={{24,"1"},{45,"2"},{53,"3"},{12,"4"},{37,"5"},{50,"6"},{61,"7"},{90,"8"},
	{100,"9"},{70,"10"},{3,"11"},{30,"12"},{26,"13"},{85,"14"},{3,"15"},
	{7,"16"}};
	myBTree t;
	myRESULT s;
	int i;
	initDSTable(t);
	for(i=0;i<N;++i)
	{
		s=searchBTree(t,r[i].key);
		if(!s.tag)
			insertBTree(t,&r[i],s.pt,s.i);
	}
	printf("按关键字的顺序遍历B_树:\n");
	traverseDSTable<Others>(t,print);
	printf("\n请输入待查找记录的关键字: ");
	cin>>i;
	s=searchBTree(t,i);
	if(s.tag)
		print(*(s.pt),s.i);
	else
		printf("没找到");
	cout<<endl;
	destroyDSTable(t);
	int a = 100;
}