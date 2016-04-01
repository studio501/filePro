
#include "stdafx.h"

#define NULL_KEY 0
#define N 10
typedef int keyType;
struct hdata
{
	keyType key;
	int ord;
};

#include "hashTable.h"

#define myHASHTABLE HashTable<hdata>

static void print(int p,const hdata&r)
{
	printf("address=%d (%d,%d)\n",p,r.key,r.ord);
}

void testHashTable()
{
	hdata r[N] = {{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{60,9},{13,10}};
	myHASHTABLE h;
	int i,p;
	bool j;
	keyType k;
	initHashTable(h);
	for(i=0;i<N-1;++i)
	{
		j=insertHash(h,r[i]);
		if(j==DUPLICATE)
			printf("表中已有关键字为%d的记录，无法再插入记录(%d,%d)\n",r[i].key,r[i].key,r[i].ord);
	}
	printf("按哈希地址的顺序遍历哈希表:\n");
	traverseHash<hdata>(h,print);
	printf("请输入待查找记录的关键字: ");
	cin>>k;
	j=find(h,k,p);
	if(j==SUCCESS)
		print(p,h.elem[p]);
	else
		printf("没找到\n");
	j=insertHash(h,r[i]);
	printf("按哈希地址的顺序遍历重建后的哈希表:\n");
	traverseHash<hdata>(h,print);
	printf("请输入待查找记录的关键字: ");
	cin>>k;
	j=find(h,k,p);
	if(j==SUCCESS)
		print(p,h.elem[p]);
	else
		printf("没找到\n");
	destroyHashTable(h);
}