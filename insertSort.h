#ifndef __INSERTSORT__HH__
#define __INSERTSORT__HH__
#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>
#include <functional>
#include "commonFunc.h"

using namespace std;

#define MAX_SIZE 20
#define SIZE 100
typedef int keyType;
typedef char keysType;

template<class IT>
struct RedType
{
	keyType key;
	IT otherinfo;
};

#define RDT RedType<IT>

template<class IT>
struct SLNode
{
	RDT rc;
	int next;
};

#define SLNODE SLNode<IT>

template<class IT>
struct SLinkListType
{
	SLNODE r[SIZE];
	int length;
};

#define SLKT SLinkListType<IT>

template<class IT>
struct SqList
{
	RDT r[MAX_SIZE+1];
	int length;
};

#define SQLIST SqList<IT>
#define MAX_NUM_OF_KEY 8
#define RADIX 10
#define MAX_SPACE 1000

template<class IT>
struct SLCell
{
	keysType keys[MAX_NUM_OF_KEY];
	IT otheritems;
	int next;
};

#define SLCELL SLCell<IT>

template<class IT>
struct SLList
{
	SLCELL r[MAX_SPACE];
	int keynum;
	int recnum;
};
#define SLLIST SLList<IT>

typedef int arrType[RADIX];



template<class IT>
void insertSort(SQLIST &L)
{
	int i,j;
	for(i=2;i<=L.length;++i)
		if LT(L.r[i].key,L.r[i-1].key)
		{
			L.r[0]=L.r[i];
			for(j=i-1;LT(L.r[0].key,L.r[j].key);--j)
				L.r[j+1]=L.r[j];
			L.r[j+1]=L.r[0];
		}
}

template<class IT>
void BInsertSort(SQLIST &L)
{
	int i,j,m,low,high;
	for(i=2;i<=L.length;++i)
	{
		L.r[0]=L.r[i];
		low=1;
		high=i-1;
		while(low<=high)
		{
			m=(low+high)/2;
			if LT(L.r[0].key,L.r[m].key)
				high=m-1;
			else
				low=m+1;
		}
		for(j=i-1;j>=high+1;--j)
			L.r[j+1]=L.r[j];
		L.r[high+1]=L.r[0];
	}
}

template<class IT>
void p2_insertSort(SQLIST &L)
{
	int i,j,first,final_;
	RDT *d;
	d=(RDT*)malloc(sizeof(RDT)*L.length);
	d[0]=L.r[1];
	first=final_=0;
	for(i=2;i<=L.length;++i)
		if(L.r[i].key<d[first].key)
		{
			first=(first-1+L.length)%L.length;
			d[first]=L.r[i];
		}
		else if(L.r[i].key>d[final_].key)
		{
			++final_;
			d[final_]=L.r[i];
		}
		else
		{
			j=final_++;
			while(L.r[i].key<d[j].key)
			{
				d[(j+1)%L.length]=d[j];
				j=(j-1+L.length)%L.length;
			}
			d[j+1]=L.r[i];
		}
	for(i=1;i<=L.length;++i)
		L.r[i]=d[(i+first-1)%L.length];
}


//±Ì≤Â»Î≈≈–Ú
template<class IT>
void tableInsert(SLKT &SL,RDT D[],int n)
{
	int i,p,q;
	SL.r[0].rc.key=INT_MAX;
	SL.r[0].next=0;
	for(i=0;i<n;++i)
	{
		SL.r[i+1].rc=D[i];
		q=0;
		p=SL.r[0].next;
		while(SL.r[p].rc.key<=SL.r[i+1].rc.key)
		{
			q=p;
			p=SL.r[p].next;
		}
		SL.r[i+1].next=p;
		SL.r[q].next=i+1;
	}
	SL.length=n;
}

template<class IT>
void arrange(SLKT &SL)
{
	int i,p,q;
	SLNODE t;
	p=SL.r[0].next;
	for(i=1;i<SL.length;++i)
	{
		while(p<i)
			p=SL.r[p].next;
		q=SL.r[p].next;
		if(p!=i)
		{
			t=SL.r[p];
			SL.r[p]=SL.r[i];
			SL.r[i]=t;
			SL.r[i].next=p;
		}
		p=q;
	}
}

template<class IT>
void sort(SLKT L,int adr[])
{
	int i=1,p=L.r[0].next;
	while(p)
	{
		adr[i++]=p;
		p=L.r[p].next;
	}
}

template<class IT>
void rearrange(SLKT &L,int adr[])
{
	int i,j,k;
	for(i=1;i<L.length;++i)
		if(adr[i]!=i)
		{
			j=i;
			L.r[0]=L.r[i];
			while(adr[j]!=i)
			{
				k=adr[j];
				L.r[j]=L.r[k];
				adr[j]=j;
				j=k;
			}
			L.r[j]=L.r[0];
			adr[j]=j;
		}
}

//œ£∂˚≈≈–Ú
template<class IT>
void shellInsert(SQLIST &L,int dk)
{
	int i,j;
	for(i=dk+1;i<=L.length;++i)
		if LT(L.r[i].key,L.r[i-dk].key)
		{
			L.r[0]=L.r[i];
			for(j=i-dk;j>0&&LT(L.r[0].key,L.r[j].key);j-=dk)
				L.r[j+dk]=L.r[j];
			L.r[j+dk]=L.r[0];
		}
}

template<class IT>
void shellSort(SQLIST &L,int dlta[],int t,const std::function<void(const SQLIST&)> &func)
{
	int k;
	for(k=0;k<t;++k)
	{
		shellInsert(L,dlta[k]);
		printf("µ⁄%dÃÀ≈≈–ÚΩ·π˚: ",k+1);
		func(L);
	}
}

//√∞≈›≈≈–Ú
void bubble_sort(int a[],int n,const std::function<void(int r[],const int &)> &func)
{
	int i,j,t;
	bool change;
	for(i=n-1,change=true;i>1&&change;--i)
	{
		change=false;
		for(j=0;j<i;++j)
			if(a[j]>a[j+1])
			{
				t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
				change=true;
			}
	}
	func(a,n);
}

//øÏÀŸ≈≈–Ú
template<class IT>
int partition(SQLIST &L,int low,int high)
{
	RDT t;
	keyType pivotkey;
	pivotkey=L.r[low].key;
	while(low<high)
	{
		while(low<high&&L.r[high].key>=pivotkey) --high;
		t=L.r[low];
		L.r[low]=L.r[high];
		L.r[high]=t;
		while(low<high&&L.r[low].key<=pivotkey) ++low;
		t=L.r[low];
		L.r[low]=L.r[high];
		L.r[high]=t;
	}
	return low;
}

template<class IT>
void qsort(SQLIST &L,int low,int high)
{
	int pivotloc;
	if(low<high)
	{
		pivotloc=partition(L,low,high);
		qsort(L,low,pivotloc-1);
		qsort(L,pivotloc+1,high);
	}
}

template<class IT>
void quickSort(SQLIST &L)
{
	qsort(L,1,L.length);
}

//—°‘Ò≈≈–Ú
template<class IT>
int selectMinKey(SQLIST L,int i)
{
	keyType min;
	int j,k;
	k=i;
	min=L.r[i].key;
	for(j=i+1;j<=L.length;++j)
		if(L.r[j].key<min)
		{
			k=j;
			min=L.r[j].key;
		}
	return k;
}

template<class IT>
void selectSort(SQLIST &L)
{
	int i,j;
	RDT t;
	for(i=1;i<L.length;++i)
	{
		j=selectMinKey(L,i);
		if(i!=j)
		{
			t=L.r[i];
			L.r[i]=L.r[j];
			L.r[j]=t;
		}
	}
}

// ˜–Œ—°‘Ò≈≈–Ú
template<class IT>
void treeSort(SQLIST &L)
{
	int i,j,j1,k,k1,l,n=L.length;
	RDT *t;
	l=(int)ceil(log(n)/log(2))+1;
	k=(int)pow(2,l)-1;
	k1=(int)pow(2,l-1)-1;
	t=(RDT*)malloc(k*sizeof(RDT));
	for(i=1;i<=n;++i) t[k1+i-1]=L.r[i];
	for(i=k1+n;i<k;++k) t[i].key=INT_MAX;
	j1=k1;
	j=k;
	while(j1)
	{
		for(i=j1;i<j;i+=2)
			t[i].key<t[i+1].key?(t[(i+1)/2-1]=t[i]):(t[(i+1)/2-1]=t[i+1]);
		j=j1;
		j1=(j1-1)/2;
	}
	for(i=0;i<n;++i)
	{
		L.r[i+1]=t[0];
		j1=0;
		for(j=1;j<l;++j)
			t[2*j1+1].key==t[j1].key?(j1=2*j1+1):(j1=2*j1+2);
		t[j1].key=INT_MAX;
		while(j1)
		{
			j1=(j1+1)/2-1;
			t[2*j1+1].key<=t[2*j1+2].key?(t[j1]=t[2*j1+1]):(t[j1]=t[2*j1+2]);
		}
	}
	free(t);
	t=NULL;
}

//∂—≈≈–Ú
#define HeapType SQLIST

template<class IT>
void heapAdjust(HeapType &H,int s,int m)
{
	RDT rc;
	int j;
	rc=H.r[s];
	for(j=2*s;j<=m;j*=2)
	{
		if(j<m&&LT(H.r[j].key,H.r[j+1].key)) ++j;
		if(!LT(rc.key,H.r[j].key)) break;
		H.r[s]=H.r[j];
		s=j;
	}
	H.r[s]=rc;
}

template<class IT>
void heapSort(HeapType &H)
{
	RDT t;
	int i;
	for(i=H.length/2;i>0;--i) heapAdjust(H,i,H.length);
	for(i=H.length;i>1;--i)
	{
		t=H.r[1];
		H.r[1]=H.r[i];
		H.r[i]=t;
		heapAdjust(H,1,i-1);
	}
}

//πÈ≤¢≈≈–Ú
template<class IT>
void merge(RDT SR[],RDT TR[],int i,int m,int n)
{
	int j,k,l;
	for(j=m+1,k=i;i<=m&&j<=n;++k)
		if LQ(SR[i].key,SR[j].key)
			TR[k]=SR[i++];
		else
			TR[k]=SR[j++];
	if(i<=m)
		for(l=0;l<=m-i;++l)
			TR[k+l]=SR[i+l];
	if(j<=n)
		for(l=0;l<=n-j;++l)
			TR[k+l]=SR[j+l];
}

template<class IT>
void msort(RDT SR[],RDT TR1[],int s,int t)
{
	int m;
	RDT TR2[MAX_SIZE+1];
	if(s==t) TR1[s]=SR[s];
	else
	{
		m=(s+t)/2;
		msort(SR,TR2,s,m);
		msort(SR,TR2,m+1,t);
		merge(TR2,TR1,s,m,t);
	}
}

template<class IT>
void mergeSort(SQLIST &L)
{
	msort(L.r,L.r,1,L.length);
}

template<class IT>
void intiList1_(SLLIST &L,RDT D[],int n)
{
	char c[MAX_NUM_OF_KEY],c1[MAX_NUM_OF_KEY];
	int i,j,max=D[0].key;
	for(i=1;i<n;++i)
		if(max<D[i].key)
			max=D[i].key;
	L.keynum=int(ceil(log10(max)));
	L.recnum=n;
	for(i=1;i<=n;++i)
	{
		L.r[i].otheritems=D[i-1].otherinfo;
		_itoa(D[i-1].key,c,10);
		for(j=strlen(c);j<L.keynum;++j)
		{
			strcpy(c1,"0");
			strcat(c1,c);
			strcpy(c,c1);
		}
		for(j=0;j<L.keynum;++j)
			L.r[i].keys[j]=c[L.keynum-1-j];
	}
}

int ord(char c)
{
	return c-'0';
}

template<class IT>
void distribute(SLCELL r[],int i,arrType f,arrType e)
{
	int j,p;
	for(j=0;j<RADIX;++j)
		f[j]=0;
	for(p=r[0].next;p;p=r[p].next)
	{
		j=ord(r[p].keys[i]);
		if(!f[j]) f[j]=p;
		else r[e[j]].next=p;
		e[j]=p;
	}
}

int succ(int i)
{
	return ++i;
}

template<class IT>
void collect(SLCELL r[],arrType f,arrType e)
{
	int j,t;
	for(j=0;!f[j];j=succ(j));
	r[0].next=f[j];
	t=e[j];
	while(j<RADIX-1)
	{
		for(j=succ(j);j<RADIX-1&&!f[j];j=succ(j));
		if(f[j])
		{
			r[t].next=f[j];
			t=e[j];
		}
	}
	r[t].next=0;
}

template<class IT>
void radixSort(SLLIST &L,const std::function<void(const SLLIST &)> &func)
{
	int i;
	arrType f,e;
	for(i=0;i<L.recnum;++i)
		L.r[i].next=i+1;
	L.r[L.recnum].next=0;
	for(i=0;i<L.keynum;++i)
	{
		distribute(L.r,i,f,e);
		collect(L.r,f,e);
		printf("µ⁄%dÃÀ ’ºØ∫Û:\n",i+1);
		func(L);
		printf("\n");
	}
}

template<class IT>
void sSort(SLLIST L,int adr[])
{
	int i=1,p=L.r[0].next;
	while(p)
	{
		adr[i++]=p;
		p=L.r[p].next;
	}
}

template<class IT>
void sRearrange(SLLIST &L,int adr[])
{
	int i,j,k;
	for(i=1;i<L.recnum;++i)
		if(adr[i]!=i)
		{
			j=i;
			L.r[0]=L.r[i];
			while(adr[j]!=i)
			{
				k=adr[j];
				L.r[j]=L.r[k];
				adr[j]=j;
				j=k;
			}
			L.r[j]=L.r[0];
			adr[j]=j;
		}
}
#endif // !__INSERTSORT__HH__
