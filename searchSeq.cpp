#include "stdafx.h"


#define N 5
typedef long keyType;
#define key number
struct ElemType
{
	long number;
	char name[9];
	int politics;
	int Chinese;
	int English;
	int math;
	int physics;
	int chemistry;
	int biology;
	int total;
	long t;
	long t1;
};


static void print(const ElemType& c)
{
	printf("%-8ld%-8s%4d%5d%5d%5d%5d%5d%5d%5d\n",c.number,c.name,c.politics,
		c.Chinese,c.English,c.math,c.physics,c.chemistry,c.biology,c.total);
}

#include "searchSeq.h"

void testSearchSeq()
{
	ElemType r[N]={{5,"何芳芳",85,89,98,100,93,80,47},
	{1,"陈红",85,86,88,100,92,90,45},
	{2,"陆华",78,75,90,80,95,88,37},
	{3,"张平",82,80,78,98,84,96,40},
	{4,"赵小怡",76,85,94,57,77,69,44}}; // 数组不按关键字有序

	SSTable<ElemType> st;
	int i;
	long s;
	for(i=0;i<N;++i)
		r[i].total=r[i].politics+r[i].Chinese+r[i].English+r[i].math+r[i].physics+
		r[i].chemistry+r[i].biology;
	create_Ord(st,r,N);
	printf("准考证号姓名政治语文外语数学物理化学生物总分\n");
	traverse<ElemType>(st,print);
	printf("请输入待查找人的考号: ");
	cin>>s;
	//i=search_Seq(st,s);
	i=seqrch_Bin(st,s);
	if(i)
		print(st.elem[i]);
	else
		printf("没找到\n");
	destroy(st);
}
