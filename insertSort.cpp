
#include "stdafx.h"
#include "insertSort.h"
#define N 8
#define myRDT RedType<int>
#define mySQLIST SqList<int>

#define mySLNODE SLNode<int>
#define mySLKT SLinkListType<int>


static void print(const mySQLIST & L)
{
	int i;
	for(i=1;i<=L.length;++i)
		printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
	printf("\n");
}

static void print2(mySLKT L)
{
	int i;
	for(i=1;i<=L.length;++i)
		printf("key=%d ord=%d next=%d\n",L.r[i].rc.key,L.r[i].rc.otherinfo,L.r[i].next);
}

static void print3(int r[],int n)
{
	for(int i=0;i<n;++i)
		printf("%d ",r[i]);
	printf("\n");
}

#define mySLCELL SLCell<int>
#define mySLLIST SLList<int>

static void print4(const mySLLIST &L)
{
	int i=L.r[0].next,j;
	while(i)
	{
		for(j=L.keynum-1;j>=0;--j)
			printf("%c",L.r[i].keys[j]);
		printf(" ");
		i=L.r[i].next;
	}
}

static void print5(const mySLLIST &L)
{
	int i,j;
	printf("keynum=%d recnum=%d\n",L.keynum,L.recnum);
	for(i=1;i<=L.recnum;++i)
	{
		printf("keys=");
		for(j=L.keynum-1;j>=0;--j)
			printf("%c",L.r[i].keys[j]);
		printf(" otheritems=%d next=%d\n",L.r[i].otheritems,L.r[i].next);
	}
}

void testInsertSort()
{
	myRDT d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
	mySQLIST l1,l2,l3,l4,l5,l6,l7,l8,l9;
	int i ;
	for(i=0;i<N;++i)
		l1.r[i+1]=d[i];
	l1.length=N;
	l2=l3=l1;
	l5=l1;
	l6=l1;
	l7=l1;
	l8=l1;
	l9=l1;
	printf("排序前:\n");
	print(l1);
	insertSort(l1);
	printf("直接插入排序后:\n");
	print(l1);
	BInsertSort(l2);
	printf("折半插入排序后:\n");
	print(l2);
	printf("2_路插入排序后:\n");
	p2_insertSort(l3);
	print(l3);

	mySLKT sl1,sl2;
	int *adr;
	tableInsert(sl1,d,N);
	sl2=sl1;
	printf("排序前:\n");
	print2(sl1);
	arrange(sl1);
	printf("l1排序后:\n");
	print2(sl1);
	adr=(int *)malloc((sl2.length+1)*sizeof(int));
	sort(sl2,adr);
	for(i=1;i<=sl2.length;++i)
		printf("adr[%d]=%d ",i,adr[i]);
	printf("\n");
	rearrange(sl2,adr);
	printf("l2排序后:\n");
	print2(sl2);

	int dt[]={5,3,1};
	for(i=0;i<N;++i)
		l4.r[i+1]=d[i];
	l4.length=N;
	printf("排序前: \n");
	shellSort<int>(l4,dt,3,print);
	printf("排序后: ");
	print(l4);

	int d1[N]= {1,2,4,5,6,77,88,99}; //{49,38,65,97,76,13,27,49};
	printf("排序前:\n");
	print3(d1,N);
	printf("排序后:\n");
	bubble_sort(d1,N,print3);

	printf("快速排序后: \n");
	quickSort(l5);
	print(l5);

	printf("选择排序后: \n");
	selectSort(l6);
	print(l6);

	printf("树形选择排序后: \n");
	treeSort(l7);
	print(l7);

	printf("堆排序后: \n");
	heapSort(l8);
	print(l8);

	printf("归并排序后: \n");
	mergeSort(l9);
	print(l9);

	myRDT d3[N+2]={{278,1},{109,2},{63,3},{930,4},{589,5},{184,6},{505,7},{269,8},{8,9},{83,10}};
	mySLLIST l10;
	int *adr1;
	intiList1_(l10,d3,N+2);
	printf("排序前(next域还没赋值):\n");
	print5(l10);
	radixSort<int>(l10,print4);
	printf("排序后(静态链表):\n");
	print5(l10);
	adr1=(int*)malloc(l10.recnum*sizeof(int));
	sSort(l10,adr1);
	sRearrange(l10,adr1);
	printf("排序后(重排记录):\n");
	print5(l10);
}