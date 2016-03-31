#ifndef __SEARCHSEQ__HH__
#define __SEARCHSEQ__HH__
#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>

#include "commonFunc.h"

using namespace std;

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
};

typedef void(*visit)(ElemType);

static void print(ElemType c)
{
	printf("%-8ld%-8s%4d%5d%5d%5d%5d%5d%5d%5d\n",c.number,c.name,c.politics,
		c.Chinese,c.English,c.math,c.physics,c.chemistry,c.biology,c.total);
}

template<class T>
struct SSTable
{
	T *elem;
	int lenght;
};

template<class T>
void create_Seq(SSTable<T> &ST,T r[],int n)
{
	int i;
	ST.elem = (T*)calloc(n+1,sizeof(T));//动态生成n+1个数据元素空间,0元素不用
	if(!ST.elem) exit(0);
	for(i=1;i<=n;++i)
		ST.elem[i]=r[i-1];
	ST.lenght=n;
}

//升序排序
template<class T>
void ascend(SSTable<T> &ST)
{
	int i,j,k;
	for(i=1;i<ST.lenght;++i)
	{
		k=i;
		ST.elem[0]=ST.elem[i];
		for(j=i+1;j<=ST.lenght;++j)
			if(LT(ST.elem[j].key,ST.elem[0].key))
			{
				k=j;
				ST.elem[0]=ST.elem[j];
			}
		if(k!=i)
		{
			ST.elem[k]=ST.elem[i];
			ST.elem[i]=ST.elem[0];
		}
	}
}

//创建有序表
template<class T>
void create_Ord(SSTable<T> &ST,T r[],int n)
{
	create_Seq(ST,r,n);
	ascend(ST);
}

//销毁表
template<class T>
bool destroy(SSTable<T> &ST)
{
	free(ST.elem);
	ST.elem=NULL;
	ST.lenght=0;
	return true;
}

//查找,返回元素位置
template<class T>
int search_Seq(SSTable<T> ST,keyType key_)
{
	int i;
	ST.elem[0].key=key_;
	for(i=ST.lenght;!EQ(ST.elem[i].key,key_);--i);
	return i;//找不到为0(哨兵)
}

//折半查找
template<class T>
int seqrch_Bin(SSTable<T> ST,keyType key_)
{
	int low,high,mid;
	low=1;
	high=ST.lenght;
	while(low<=high)
	{
		mid=(low+high)/2;
		if EQ(key_,ST.elem[mid].key) return mid;
		else if LT(key_,ST.elem[mid].key) high=mid-1;
		else low=mid+1;
	}
	return 0;
}

//遍历表
template<class T>
void traverse(SSTable<T> ST,visit func)
{
	T *p;
	int i;
	p=++ST.elem;
	for(i=1;i<=ST.lenght;++i)
		func(*p++);
}
#endif