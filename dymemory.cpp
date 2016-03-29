
#include "stdafx.h"
#include "dymemory.h"

#define Max_Space 1000
#define eSmall 10

//�����㷨
//��pav���в�С��n�Ŀ��п�,�������Ӧ�Ĵ洢��,�������׵�ַ
Space allocBoundTag(Space &pav,int n)
{
	Space p,f;
	for(p=pav;p&&p->size<n&&p->rlink!=pav;p=p->rlink);//�ҵ���С��n�Ŀ��п� �״����
	if(!p||p->size<n) return NULL;
	else
	{
		f=FootLoc(p);
		pav=p->rlink;
		if(p->size-n<=eSmall) //����֮��û�д���eSmall������ ���������
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

//�����㷨
//�߽��ʶ������ pָ����ڴ��
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
		if(l==1&&r==1)//����Ϊռ�ÿ�
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
		else if(l==0&&r==1)//����� ��ռ��
		{
			s=(p-1)->uplink;
			s->size+=p->size;
			t=FootLoc(p);
			t->uplink=s;
			t->tag=0;
		}
		else if(l==1&&r==0)//�ҿ��� ��ռ��
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
		else //���Ҷ�Ϊ���п�
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

//��ӡp��ָ��Ŀ����ÿռ��
void printSpace(Space p)
{
	Space h,f;
	if(p)
	{
		h=p;
		f=FootLoc(h);
		do 
		{
			printf("��Ĵ�С=%d ����׵�ַ=%u ",h->size,f->uplink); // ��������Ϣ
			printf("���־=%d(0:����1:ռ��) �ڿ��׵�ַ=%u\n",h->tag,f+1);
			h=h->rlink;
			f=FootLoc(h);
		} while (h!=p);
	}
}

//��ӡp��ָ����ѷ���ռ�
void printUser(Space p[])
{
	for(int i=0;i<Max_Space/eSmall;++i)
		if(p[i])
		{
			printf("��%d���׵�ַ=%u ",i,p[i]); // ��������Ϣ
			printf("��Ĵ�С=%d ��ͷ��־=%d(0:����1:ռ��)",p[i]->size,p[i]->tag);
			printf(" ��β��־=%d\n",(FootLoc(p[i]))->tag);
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
	printf("�ṹ��WORDΪ%d���ֽ�\n",sizeof(_WORD));
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
	printf("��ʼ���󣬿����ÿռ��Ϊ\n");
	printSpace(pav);
	n=300;
	v[0]=allocBoundTag(pav,n);
	printf("����%u���洢�ռ�󣬿����ÿռ��Ϊ\n",n);
	checkMemory(pav,v);
	n=450;
	v[1]=allocBoundTag(pav,n);
	printf("����%u���洢�ռ��pavΪ\n",n);
	checkMemory(pav,v);
	n=300;
	v[2]=allocBoundTag(pav,n);
	printf("����%u���洢�ռ��(���ɹ�)��pavΪ\n",n);
	checkMemory(pav,v);
	n=242;
	v[2]=allocBoundTag(pav,n);
	printf("����%u���洢�ռ��(�������)��pavΪ\n",n);
	checkMemory(pav,v);
	printf("����v[0](%d)��(��pav��ʱ����)��pavΪ\n",v[0]->size);
	reclainm(pav,v[0]);
	checkMemory(pav,v);
	reclainm(pav,v[2]);
	checkMemory(pav,v);
	n=270;
	v[0]=allocBoundTag(pav,n);
	printf("����%u���洢�ռ��(���ҿռ��㹻��Ŀ�)��pavΪ\n",n);
	checkMemory(pav,v);
	n=30;
	v[2]=allocBoundTag(pav,n);
	printf("����%u���洢�ռ��(�ڵ�ǰ���Ϸ���)��pavΪ\n",n);
	checkMemory(pav,v);
}
