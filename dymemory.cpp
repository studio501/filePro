
#include "stdafx.h"
#include "dymemory.h"

#define Max_Space 1000
#define eSmall 10

//分配算法
//若pav中有不小于n的空闲块,则分配相应的存储块,并返回首地址
Space allocBoundTag(Space &pav,int n)
{
	Space p,f;
	for(p=pav;p&&p->size<n&&p->rlink!=pav;p=p->rlink);//找到不小于n的空闲块 首次拟合
	if(!p||p->size<n) return NULL;
	else
	{
		f=FootLoc(p);
		pav=p->rlink;
		if(p->size-n<=eSmall) //分配之后没有大于eSmall的余量 就整块分配
		{
			if(pav==p) pav=NULL;
			else
			{
				pav->llink=p->llink;
				p->llink->rlink=pav;
			}
		}
		else
		{
			f->tag=1;
			p->size-=n;
			f=FootLoc(p);
			f->tag=0;
			f->uplink=p;
			p=f+1;
			p->tag=1;
			p->size=n;
		}
		return p;
	}
}

//回收算法
//边界标识法回收 p指向的内存块
void reclainm(Space &pav,Space &p)
{
	Space s,t=p+p->size;
	int l=(p-1)->tag,r=(p+p->size)->tag;
	if(!pav)
	{
		pav=p->llink=p->rlink=p;
		p->tag=0;
		(FootLoc(p))->uplink=p;
		(FootLoc(p))->tag=0;
	}
	else
		if(l==1&&r==1)//左右为占用块
		{
			p->tag=0;
			(FootLoc(p))->uplink=p;
			(FootLoc(p))->tag=0;
			pav->llink->rlink=p;
			p->llink=pav->llink;
			p->rlink=pav;
			pav->llink=p;
			pav=p;
		}
		else if(l==0&&r==1)//左空闲 右占用
		{
			s=(p-1)->uplink;
			s->size+=p->size;
			t=FootLoc(p);
			t->uplink=s;
			t->tag=0;
		}
		else if(l==1&&r==0)//右空闲 左占用
		{
			p->tag=0;
			p->llink=t->llink;
			p->llink->rlink=p;
			p->rlink=t->rlink;
			p->rlink->llink=p;
			p->size+=t->size;
			(FootLoc(t))->uplink=p;
			if(pav==t) pav=p;
		}
		else //左右都为空闲块
		{
			t->llink->rlink=t->rlink;
			t->rlink->llink=t->llink;
			s=(p-1)->uplink;
			s->size+=p->size+t->size;
			(FootLoc(t))->uplink=s;
			if(pav==t) pav=s;
		}
	p=NULL;
}

//打印p所指向的可利用空间表
void printSpace(Space p)
{
	Space h,f;
	if(p)
	{
		h=p;
		f=FootLoc(h);
		do 
		{
			printf("块的大小=%d 块的首地址=%u ",h->size,f->uplink); // 输出结点信息
			printf("块标志=%d(0:空闲1:占用) 邻块首地址=%u\n",h->tag,f+1);
			h=h->rlink;
			f=FootLoc(h);
		} while (h!=p);
	}
}

//打印p所指向的已分配空间
void printUser(Space p[])
{
	for(int i=0;i<Max_Space/eSmall;++i)
		if(p[i])
		{
			printf("块%d的首地址=%u ",i,p[i]); // 输出结点信息
			printf("块的大小=%d 块头标志=%d(0:空闲1:占用)",p[i]->size,p[i]->tag);
			printf(" 块尾标志=%d\n",(FootLoc(p[i]))->tag);
		}
}


void checkMemory(Space pav,Space v[])
{
	printSpace(pav);
	printUser(v);
}

void testDynamicMemory()
{
	Space pav,p;
	Space v[Max_Space/eSmall]={NULL};
	int n;
	printf("结构体WORD为%d个字节\n",sizeof(_WORD));
	p= new _WORD[Max_Space+2];
	p->tag=1;
	pav=p+1;
	pav->rlink=pav->llink=pav;
	pav->tag=0;
	pav->size=Max_Space;
	p=FootLoc(pav);
	p->uplink=pav;
	p->tag=0;
	(p+1)->tag=1;
	printf("初始化后，可利用空间表为\n");
	printSpace(pav);
	n=300;
	v[0]=allocBoundTag(pav,n);
	printf("分配%u个存储空间后，可利用空间表为\n",n);
	checkMemory(pav,v);
	n=450;
	v[1]=allocBoundTag(pav,n);
	printf("分配%u个存储空间后，pav为\n",n);
	checkMemory(pav,v);
	n=300;
	v[2]=allocBoundTag(pav,n);
	printf("分配%u个存储空间后(不成功)，pav为\n",n);
	checkMemory(pav,v);
	n=242;
	v[2]=allocBoundTag(pav,n);
	printf("分配%u个存储空间后(整块分配)，pav为\n",n);
	checkMemory(pav,v);
	printf("回收v[0](%d)后(当pav空时回收)，pav为\n",v[0]->size);
	reclainm(pav,v[0]);
	checkMemory(pav,v);
	reclainm(pav,v[2]);
	checkMemory(pav,v);
	n=270;
	v[0]=allocBoundTag(pav,n);
	printf("分配%u个存储空间后(查找空间足够大的块)，pav为\n",n);
	checkMemory(pav,v);
	n=30;
	v[2]=allocBoundTag(pav,n);
	printf("分配%u个存储空间后(在当前块上分配)，pav为\n",n);
	checkMemory(pav,v);
}
