
#include "stdafx.h"
#include "dymemory1.h"

#define Max_Space 1000
#define eSmall 10

#define N 100
Space_b r;



//�����㷨
//��pav���в�С��n�Ŀ��п�,�������Ӧ�Ĵ洢��,�������׵�ַ
static Space_b allocBuddy(FreeList avail,int n)
{
	int i,k;
	Space_b pa,pi,pre,suc;
	for(k=0;k<=m&&(avail[k].nodesize<n+1||!avail[k].first);++k);
	if(k>m) return NULL;
	else
	{
		pa=avail[k].first;
		pre=pa->llink;
		suc=pa->rlink;
		if(pa==suc) avail[k].first=NULL;
		else
		{
			pre->rlink=suc;
			suc->llink=pre;
			avail[k].first=suc;
		}
		for(i=1;avail[k-i].nodesize>=n+1;++i)
		{
			pi=pa+int(pow(2,k-i));
			pi->rlink=pi;
			pi->llink=pi;
			pi->tag=0;
			pi->kval=k-i;
			avail[k-i].first=pi;
		}
		pa->tag=1;
		pa->kval=k-(--i);
	}
	return pa;
}

//����p�Ļ����ʼ��ַ
static Space_b buddy(Space_b p)
{
	if((p-r)%int(pow(2,p->kval+1))==0) return p+int(pow(2,p->kval));
	else return p-int(pow(2,p->kval));
}

//�����㷨
//�߽��ʶ������ pָ����ڴ��
static void reclainm(FreeList pav,Space_b &p)
{
	Space_b s;
	s=buddy(p);
	while(s>=r&&s<r+pav[m].nodesize&&s->tag==0&&s->kval==p->kval)
	{
		if(s->rlink==s) pav[s->kval].first=NULL;
		else
		{
			s->llink->rlink=s->rlink;
			s->rlink->llink=s->llink;
			if(pav[s->kval].first==s)
				pav[s->kval].first=s->rlink;
		}
		if((p-r)%int(pow(2,p->kval+1))==0) p->kval++;
		else
		{
			s->kval=p->kval+1;
			p=s;
		}
		s=buddy(p);
	}
	p->tag=0;
	if(pav[p->kval].first==NULL) pav[p->kval].first=p->llink=p->rlink=p;
	else
	{
		p->rlink=pav[p->kval].first;
		p->llink=p->rlink->llink;
		p->rlink->llink=p;
		p->llink->rlink=p;
		pav[p->kval].first=p;
	}
	p=NULL;
}

//��ӡp��ָ��Ŀ����ÿռ��
static void printSpace(FreeList p)
{
	int i;
	Space_b h;
	for(i=0;i<=m;++i)
		if(p[i].first)
		{
			h=p[i].first;
			do 
			{
				printf("��Ĵ�С=%d ����׵�ַ=%u ",int(pow(2,h->kval)),h); // ��������Ϣ
				printf("���־=%d(0:����1:ռ��)\n",h->tag);
				h=h->rlink;
			}while (h!=p[i].first);
		}
}

//��ӡp��ָ����ѷ���ռ�
static void printUser(Space_b p[])
{
	for(int i=0;i<N;++i)
		if(p[i])
		{
			printf("��%d���׵�ַ=%u ",i,p[i]); // ��������Ϣ
			printf("��Ĵ�С=%d",int(pow(2,p[i]->kval)));
			printf(" ���־=%d(0:����1:ռ��)\n",p[i]->tag);
		}
}


static void checkMemory(FreeList pav,Space_b v[])
{
	printSpace(pav);
	printUser(v);
}

void testBudySys()
{
	int i,n;
	FreeList a;
	Space_b q[N]={NULL};
	printf("sizeof(WORD_b)=%u m=%u int(pow(2,m))=%u\n",sizeof(WORD_b),m,int(pow(2,m)));
	for(i=0;i<=m;++i)
	{
		a[i].nodesize=int(pow(2,i));
		a[i].first=NULL;
	}
	r=a[m].first=new WORD_b[a[m].nodesize];
	if(r)
	{
		r->llink=r->rlink=r;
		r->tag=0;
		r->kval=m;
		printSpace(a);
		n=100;
		q[0]=allocBuddy(a,n);
		printf("����%d���ֺ󣬿����ÿռ�Ϊ\n",n);
		checkMemory(a,q);
		n=200;
		q[1]=allocBuddy(a,n);
		printf("����%d���ֺ󣬿����ÿռ�Ϊ\n",n);
		checkMemory(a,q);
		n=220;
		q[2]=allocBuddy(a,n);
		printf("����%d���ֺ󣬿����ÿռ�Ϊ\n",n);
		checkMemory(a,q);
		reclainm(a,q[1]);
		printf("����q[1]�󣬿����ÿռ�Ϊ\n");
		checkMemory(a,q);
		reclainm(a,q[0]);
		printf("����q[0]�󣬿����ÿռ�Ϊ\n");
		checkMemory(a,q);
		reclainm(a,q[2]);
		checkMemory(a,q);
	}
	else cout<<"error \n";
}
