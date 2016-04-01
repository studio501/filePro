
#include "stdafx.h"
#include "insertSort.h"
#define N 8
#define myRDT RedType<int>
#define mySQLIST SqList<int>

static void print(const mySQLIST & L)
{
	int i;
	for(i=1;i<=L.length;++i)
		printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
	printf("\n");
}

void testInsertSort()
{
	myRDT d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
	mySQLIST l1,l2,l3;
	int i ;
	for(i=0;i<N;++i)
		l1.r[i+1]=d[i];
	l1.length=N;
	l2=l3=l1;
	printf("排序前:\n");
	print(l1);
	insertSort(l1);
	printf("直接插入排序后:\n");
	print(l1);
}