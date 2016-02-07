#include "stdafx.h"
#include <malloc.h>
#include <process.h>
#include <math.h>
#include <fstream>
#include "testLinkList.h"
#include <iostream>


//����յ����Ա�
void initList(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	if(!L) exit(OVERFLOW);
	L->next=NULL;
}

//�������Ա�
void destroyList(LinkList &L)
{
	LinkList q;
	while(L)
	{
		q=L->next;
		free(L);
		L=q;
	}
}

//��L����Ϊ�ձ�
void clearList(LinkList &L)
{
	LinkList p=L->next,q;
	while(p)
	{
		q=p->next;
		free(p);
		p=q;
	}
	L->next=NULL;
}

//���Ƿ�Ϊ��
bool isEmpty(LinkList &L)
{
	if(L->next) return false;
	else return true;
}

//���ر�
int listLength(LinkList &L)
{
	int i=0;
	LinkList p=L->next;
	while(p)
	{
		++i;
		p=p->next;
	}
	return i;
}

//��ȡλ��i��Ԫ��
bool getElemByIndex(LinkList &L,int i,ElemType &e)
{
	int j=1;
	LinkList p = L->next;
	while(p&&j<i)
	{
		p=p->next;
		++j;
	}
	if(!p||j>i) return false;
	e = p->data;
	return true;
}

//�ҵ�λ��i��Ԫ��
LinkList findElemByIndex(LinkList &L,int i)
{
	int j=1;
	LinkList p = L->next;
	while(p&&j<i)
	{
		p=p->next;
		++j;
	}
	if(!p||j>i) return  L->next;
	
	return p;
}

//������Ԫ�ص��ж� ����L�е�1����e����compare()��ϵ������Ԫ��λ��
int locateElem(LinkList &L,ElemType e,compare_func cFunc)
{
	int i=0;
	LinkList p=L->next;
	while(p)
	{
		++i;
		if(cFunc(p->data,e)) return i;
		p = p->next;
	}
	return 0;
}

//����cur_e��ǰ��
bool priorElem(LinkList &L,ElemType cur_e,ElemType &pre_e)
{
	LinkList q,p=L->next;
	while(p->next)
	{
		q=p->next;
		if(q->data==cur_e)
		{
			pre_e=p->data;
			return true;
		}
		p=q;
	}
	return false;
}

//����cur_e�ĺ��
bool nextElem(LinkList &L,ElemType cur_e,ElemType &next_e)
{
	LinkList p=L->next;
	while(p->next)
	{
		if(p->data==cur_e)
		{
			next_e = p->next->data;
			return true;
		}
		p=p->next;
	}
	return false;
}

//��λ��i����e
bool listInsert(LinkList &L,int i,ElemType e)
{
	LinkList p;
	if(listLength(L)<=0)
	{
		p = L;
	}
	else
	{
		--i;
		i = mymin(mymax(1,i),listLength(L));
		p = findElemByIndex(L,i);
		if(!p) return false;
	}
	
	LinkList t = (LinkList)malloc(sizeof(LNode));
	t->data = e;
	t->next = p->next;
	p->next = t;
	return true;
}

//ɾ��λ��iԪ��
bool listDelete(LinkList &L,int i,ElemType &e)
{
	i = mymin(mymax(1,i),listLength(L));
	LinkList p = findElemByIndex(L,i-1);
	if(!p) return false;
	LinkList t = p->next;
	p->next = p->next->next;
	e = t->data;
	free(t);
	return true;
}

//����list
void listTraverse(LinkList &L,vi_func vFunc)
{
	LinkList p=L->next;
	while(p)
	{
		vFunc(p->data);
		p=p->next;
	}
	printf("\n");
}

//��la lb ����
void listUnion(LinkList &La,LinkList &Lb)
{
	int aLen=listLength(La),bLen=listLength(Lb);
	ElemType e;
	for(int i=1;i<=bLen;++i)
	{
		getElemByIndex(Lb,i,e);
		if(!locateElem(La,e,compare_equal)) listInsert(La,++aLen,e);
	}
}

//ð������
void listBubleSort(LinkList &L,compare_func cFunc)
{
	if(isEmpty(L)) return;
	LinkList p = L->next;
	
	LinkList q;
	ElemType temp;
	while(p)
	{
		q = p->next;
		while(q)
		{
			if(!cFunc(p->data,q->data))
			{
				temp = p->data;
				p->data = q->data;
				q->data = temp;
			}
			q = q->next;
		}
		p = p->next;
	}
}

//��la,lb����鲢Ϊlc
void listMerge(LinkList &La,LinkList &Lb,LinkList &Lc)
{
	int aLen = listLength(La),bLen=listLength(Lb);
	ElemType ai,bj;
	initList(Lc);
	int i=1,j=1,k=0;
	while(i<=aLen && j<=bLen)
	{
		getElemByIndex(La,i,ai);
		getElemByIndex(Lb,j,bj);
		if(ai<=bj)
		{
			listInsert(Lc,++k,ai);
			++i;
		}
		else
		{
			listInsert(Lc,++k,bj);
			++j;
		}
	}

	while(i<=aLen)
	{
		getElemByIndex(La,i++,ai);
		listInsert(Lc,++k,ai);
	}
	while(j<=bLen)
	{
		getElemByIndex(Lb,j++,bj);
		listInsert(Lc,++k,bj);
	}
}

//��la,lb����鲢Ϊlc
void listMerge2(LinkList &La,LinkList &Lb,LinkList &Lc)
{
	LinkList pa=La->next,pb=Lb->next,pc;
	Lc=pc=La;

	while(pa&&pb)
	{
		if(pa->data<=pb->data )
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}

	pc->next=pa?pa:pb;
}

//���ļ����ȡ���ݴ�����
void createListWithFile(LinkList &L,const char * fileName)
{
	using namespace std;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	LinkList p;
	ifstream fin(fileName);
	if(fin.is_open())
	{
		ElemType e;
		while(fin>>e)
		{
			p = (LinkList)malloc(sizeof(LNode));
			p->data = e;
			p->next = L->next;
			L->next = p;
		}
	}
}

//���ļ����ȡ���ݴ�����
void createListWithFile2(LinkList &L,const char * fileName)
{
	using namespace std;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	LinkList p,q=L;
	ifstream fin(fileName);
	if(fin.is_open())
	{
		ElemType e;
		while(fin>>e)
		{
			p = (LinkList)malloc(sizeof(LNode));
			p->data = e;
			p->next=NULL;
			q->next = p;
			q = q->next;
		}
	}
}

//��̬������ز���
void testStaticList()
{
	using namespace std;
	sLinkList s = {{"",1},{"ZHAO",2},{"QIAN",3},{"SUN",4},{"LI",5},{"ZHOU",6},{"WU",7},{"ZHENG",8},{"WANG",0}};

	int i = s[0].cur;
	while(i)
	{
		cout<<s[i].data<<" ";
		i=s[i].cur;
	}
	cout<<endl;
	s[4].cur = 9;
	s[9].cur = 5;
	strcpy(s[9].data,"SHII");
	s[6].cur = 8;
	i=s[0].cur;
	while(i)
	{
		cout<<s[i].data<<" ";
		i=s[i].cur;
	}

}

//����һ���յ����Ա�
void initList_SL(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	if(!L) exit(OVERFLOW);
	L->next = L;
}

//�������Ա�
void destroyList_SL(LinkList &L)
{
	LinkList q,p = L->next;
	while(p!=L) //û����β
	{
		q = p->next;
		free(p);
		p = q;
	}
	free(L);
	L=NULL;
}

//��L�ÿ�
void clearList_SL(LinkList &L)
{
	LinkList p,q;
	L=L->next;
	p=L->next;
	while(p!=L)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = L;//ͷ�����ָ������
}

//�ж�L�Ƿ�Ϊ��
bool isEmpty_SL(LinkList &L)
{
	if(L->next == L) return true;
	else  return false;
}

//ȡ�ñ�
int listLength_SL(LinkList &L)
{
	int ii=0;
	LinkList p = L->next;
	while(p!=L)
	{
		++ii;
		p=p->next;
	}
	return ii;
}

//��ȡ��i��Ԫ��
bool getElemByIndex_SL(LinkList &L,int i,ElemType &e)
{
	int j=1;
	LinkList p = L->next->next;
	if(i<=0 || i>listLength_SL(L)) return false;
	while(j<i)
	{
		p=p->next;
		++j;
	}
	e=p->data;
	return true;
}

//������Ԫ�ص��ж� ����L�е�1����e����compare()��ϵ������Ԫ��λ��
int locateElem_SL(LinkList &L,ElemType e,compare_func cFunc)
{
	int i=0;
	LinkList p =L->next->next;
	while(p!=L->next)
	{
		++i;
		if(cFunc(p->data,e)) return i;
		p=p->next;
	}
	return 0;
}

//�ҵ�cur_e��ǰ��
bool priorElem_SL(LinkList &L,ElemType cur_e,ElemType &pre_e)
{
	LinkList q,p=L->next->next;
	q=p->next;
	while(q!=L->next)
	{
		if(q->data==cur_e)
		{
			pre_e = p->data;
			return true;
		}
		p=q;
		q=q->next;
	}
	return false;
}

//�ҵ�cur_e�ĺ��
bool nextElem_SL(LinkList &L,ElemType cur_e,ElemType &next_e)
{
	LinkList p=L->next->next;
	while(p!=L)
	{
		if(p->data==cur_e)
		{
			next_e = p->next->data;
			return true;
		}
		p=p->next;
	}
	return false;
}

//��iλ�ò���e
bool listInsert_SL(LinkList &L,int i,ElemType e)
{
	LinkList p=L->next,s;
	int j=0;
	int lenII = listLength_SL(L);
	if(i<=0||i>lenII+1) return false;
	while(j<i-1)
	{
		p=p->next;
		++j;
	}
	s=(LinkList)malloc(sizeof(LNode));
	s->data = e;
	
	s->next=p->next;
	p->next=s;
	
	if(p==L) L=s;
	return true;
}

//ɾ����i��λ��Ԫ��
bool listDelete_SL(LinkList &L,int i,ElemType &e)
{
	LinkList p=L->next,q;
	int j=0;
	if(i<=0||i>listLength_SL(L)) return false;
	while(j<i-1)
	{
		p=p->next;
		++j;
	}
	q=p->next;
	p->next = q->next;
	e=q->data;
	if(L==q) L=p;
	free(q);
	return true;
}

//����L
void listTraverse_SL(LinkList &L,vi_func vFunc)
{
	LinkList p=L->next->next;
	while(p!=L->next)
	{
		vFunc(p->data);
		p=p->next;
	}
	printf("\n");
}

//��Lb�ϲ���La�ı�β
void listMerge_SL(LinkList &La,LinkList &Lb)
{
	LinkList p = Lb->next;
	Lb->next = La->next;
	La->next = p->next;
	free(p);
	La = Lb;
}

//�����ձ�
void initList_Du(DuLinkList &L)
{
	L=(DuLinkList)malloc(sizeof(DuLinkList));
	if(!L) exit(OVERFLOW);
	L->next = L->prior = L;
}

//���ٱ�
void destroyList_Du(DuLinkList &L)
{
	DuLinkList q,p=L->next;
	while(p!=L)
	{
		q=p->next;
		free(p);
		p=q;
	}
	free(L);
	L = NULL;
}

//���ñ�
void clearList_Du(DuLinkList &L)
{
	DuLinkList q,p=L->next;
	while(p!=L)
	{
		q=p->next;
		free(p);
		p=q;
	}
	L->next=L->prior=L;
}

//�ж��Ƿ���
bool isEmpty_Du(DuLinkList &L)
{
	if(L->next==L && L->prior==L) return true;
	else return false;
}

///��ȡ����
int listLength_Du(DuLinkList &L)
{
	int i=0;
	DuLinkList p=L->next;
	while(p!=L)
	{
		++i;
		p=p->next;
	}
	return i;
}

//��ȡλ��i��Ԫ��
bool getElemByIndex_Du(DuLinkList &L,int i,ElemType &e)
{
	int j=1;
	DuLinkList p=L->next;
	while(p!=L && j<i)
	{
		p=p->next;
		++j;
	}
	if(p==L || j>i) return false;
	e = p->data;
	return true;
}

//���ص�1 ����e����compare��ϵ������
int locateElem_Du(DuLinkList &L,ElemType e,compare_func cFunc)
{
	int i=0;
	DuLinkList p = L->next;
	while(p!=L)
	{
		++i;
		if(cFunc(p->data,e)) return i;
		p=p->next;
	}
	return 0;
}

//����cur_e ��ǰ��
bool priorElem_Du(DuLinkList &L,ElemType cur_e,ElemType &pre_e)
{
	DuLinkList p=L->next->next;
	while(p!=L)
	{
		if(p->data==cur_e)
		{
			pre_e = p->prior->data;
			return true;
		}
		p=p->next;
	}
	return false;
}

//����cur_e �ĺ��
bool nextElem_Du(DuLinkList &L,ElemType cur_e,ElemType &next_e)
{
	DuLinkList p=L->next->next;
	while(p!=L)
	{
		if(p->prior->data==cur_e)
		{
			next_e = p->data;
			return true;
		}
		p=p->next;
	}
	return false;
}

//���ص�i��Ԫ�����ڵ�ַ
DuLinkList findElemByIndex_Du(DuLinkList &L,int i)
{
	DuLinkList p=L;
	if(i<0 || i>listLength_Du(L)) return NULL;
	for(int j=1;j<=i;++j) p=p->next;
	return p;
}

//��λ��i����e
bool listInsert_Du(DuLinkList &L,int i,ElemType e)
{
	DuLinkList p,s;
	if(i<1 || i>listLength_Du(L)+1) return false;
	p=findElemByIndex_Du(L,i-1);
	if(!p) return false;
	s=(DuLinkList)malloc(sizeof(DuLNode));
	if(!s) return false;
	s->data = e;
	s->prior = p;
	s->next = p->next;
	p->next->prior = s;
	p->next = s;
	return true;
}

//ɾ��λ��i ��Ԫ��
bool listDelete_Du(DuLinkList &l,int i,ElemType &e)
{
	DuLinkList p;
	if(i<1) return false;
	p=findElemByIndex_Du(l,i);
	if(!p) return false;
	e=p->data;
	p->prior->next=p->next;
	p->next->prior=p->prior;
	free(p);
	return true;
}

//������
void listTraverse_Du(DuLinkList &L,vi_func vFunc)
{
	DuLinkList p=L->next;
	while(p!=L)
	{
		vFunc(p->data);
		p=p->next;
	}
	printf("\n");
}

//���������
void listTraverseBack_Du(DuLinkList &L,vi_func vFunc)
{
	DuLinkList p=L->prior;
	while(p!=L)
	{
		vFunc(p->data);
		p=p->prior;
	}
	printf("\n");
}

//������pָ���ֵΪe�Ľ��
void makeNode(Link &p,ElemType e)
{
	p=(Link)malloc(sizeof(LNode));
	if(!p) exit(0);
	p->data = e;
}

//�ͷ�p��ָ�Ľ��
void freeNode(Link &p)
{
	free(p);
	p=NULL;
}

//����һ���յ����Ա�
void initList_RL(RLinkList &L)
{
	Link p;
	p=(Link)malloc(sizeof(LNode));
	if(p)
	{
		p->next=NULL;
		L.head=L.tail=p;
		L.len=0;
	}
	else
		exit(0);
}

//����L����Ϊ��
void clearList_RL(RLinkList &L)
{
	Link p,q;
	if(L.head!=L.tail)
	{
		p=q=L.head->next;
		L.head->next=NULL;
		while(p!=L.tail)
		{
			p=q->next;
			free(q);
			q=p;
		}
		free(q);
		L.tail=L.head;
		L.len=0;
	}
}

//�������Ա�L
void destroyList_RL(RLinkList &L)
{
	clearList_RL(L);
	freeNode(L.head);
	L.tail=NULL;
	L.len=0;
}

//hָ��L��һ�����,��h����ͷ���,��s��ָ�������ڵ�һ�����֮ǰ
void insertFirst(RLinkList &L,Link h,Link s)
{
	s->next=h->next;
	h->next =s;
	if(h==L.tail) L.tail=h->next;
	++L.len;
}

//hָ��L��һ�����,��h����ͷ���,ɾ�������еĵ�һ����㲢��q����
bool deleteFirst(RLinkList &L,Link h,Link &q)
{
	q=h->next;
	if(q)
	{
		h->next = q->next;
		if(!h->next) L.tail=h;
		--L.len;
		return true;
	}
	else return false;
}

//��s��ָ��һ�����������L�����һ�����֮��,���ı�����βָ��ָ���µĽ��
void appenList(RLinkList &L,Link s)
{
	int i=1;
	L.tail->next=s;
	while(s->next)
	{
		s=s->next;
		++i;
	}
	L.tail=s;
	L.len+=i;
}

//����pָ���ǰ��λ��
Position priorPos(RLinkList &L,Link p)
{
	Link q;
	q=L.head->next;
	if(q==p) return NULL;
	else
	{
		while(q->next!=p) q=q->next;
		return q;
	}
}

//ɾ��β��㲢��q����,�ı�L��βָ��ָ���µ�β���
bool removeList_RL(RLinkList &L,Link &q)
{
	Link p=L.head;
	if(L.len==0)
	{
		q=NULL;
		return false;
	}
	while(p->next!=L.tail)
		p=p->next;
	q=L.tail;
	p->next=NULL;
	L.tail=p;
	--L.len;
	return true;
}

//s��ָ������p��ָ���֮ǰ
void insBefore(RLinkList &L,Link &p,Link s)
{
	Link q;
	q=priorPos(L,p);
	if(!q) q=L.head;
	s->next=p;
	q->next=s;
	p=s;
	++L.len;
}

//s��ָ������p��ָ���֮��
void insAfter(RLinkList &L,Link &p,Link s)
{
	if(p==L.tail) L.tail=s;
	s->next=p->next;
	p->next=s;
	p=s;
	++L.len;
}

//��e����p��ָ�Ľ��
void setCurElem(Link p,ElemType e)
{
	p->data=e;
}

//��ȡp��ָ���Ԫ��
ElemType getCurElem(Link p)
{
	return p->data;
}

//�ж�L�Ƿ�Ϊ�ձ�
bool isEmpty_RL(RLinkList &L)
{
	if(L.len) return false;
	else return true;
}

//��ȡL��ͷ���
Position getHead(RLinkList L)
{
	return L.head;
}

//��ȡL��β���
Position getTail(RLinkList L)
{
	return L.tail;
}

//��һ��λ��
Position nextPos(Link p)
{
	return p->next;
}

//���ص�i������ָ��
bool locatePos(RLinkList L,int i,Link &p)
{
	if(i<0 || i>L.len) return false;
	else
	{
		p=L.head;
		for(int j=1;j<=i;++j)
			p=p->next;
		return true;
	}
}

//�������Ա��е�1����e���㺯��compare�ж���ϵԪ�ص�λ��
Position locateElem_RL(RLinkList L,ElemType e,compare_func cFunc)
{
	Link p=L.head;
	do 
		p=p->next;
	while(p&&!(cFunc(p->data,e)));
	return p;
}

//����L
void listTraverse_RL(RLinkList L,vi_func vFunc)
{
	if(L.len<=0) return;
	Link p=L.head->next;
	for(int j=1;j<=L.len;++j)
	{
		vFunc(p->data);
		p=p->next;
	}
	printf("\n");
}

//�������e
void orderInsert(RLinkList &L,ElemType e,compare_func cFunc)
{
	Link o,p,q;
	q=L.head;
	p=q->next;
	while(p!=NULL&&cFunc(p->data,e))
	{
		q=p;
		p=p->next;
	}

	o=(Link)malloc(sizeof(LNode));
	o->data=e;
	q->next=o;
	o->next=p;
	++L.len;
	if(!p) L.tail=o;
}

//���ص�һ����e�����ж������Ľ��λ��
bool locateElemPos_RL(RLinkList L,ElemType e,Position &q,compare_func cFunc)
{
	Link p=L.head,pp;
	do 
	{
		pp=p;
		p=p->next;
	} while (p&& !cFunc(p->data,e));

	if(!p||!cFunc(p->data,e))
	{
		q=pp;
		return false;
	}
	else
	{
		q=p;
		return true;
	}
}

//�ڵ�i��Ԫ��λ�ò���e
bool listInsert_RL(RLinkList &L,int i,ElemType e)
{
	Link h,s;
	if(!locatePos(L,i-1,h)) return false;
	makeNode(s,e);
	insertFirst(L,h,s);
	return true;
}

//�Ա�ʹ��ð������
void listBubbleSort_RL(RLinkList &L,compare_func cFunc)
{
	if(L.len<=1) return;
	Link p = L.head->next,q;
	ElemType temp;
	while(p!=L.tail->next)
	{
		q=p->next;
		while(q!=L.tail->next)
		{
			if(!cFunc(p->data,q->data))
			{
				temp = p->data;
				p->data=q->data;
				q->data=temp;
			}
			q=q->next;
		}
		p=p->next;
	}
}

//����鲢Ϊ�±�
void listMerge_RL(RLinkList &La,RLinkList &Lb,RLinkList &Lc,compare_func cFunc)
{
	Link ha=getHead(La),hb=getHead(Lb),pa,pb,q;
	ElemType a,b;
	initList_RL(Lc);
	pa=nextPos(ha);
	pb=nextPos(hb);
	while(pa&&pb)
	{
		a=getCurElem(pa);
		b=getCurElem(pb);
		if(cFunc(a,b))
		{
			deleteFirst(La,ha,q);
			q->next=NULL;
			appenList(Lc,q);
			pa=nextPos(ha);
		}
		else
		{
			deleteFirst(Lb,hb,q);
			q->next=NULL;
			appenList(Lc,q);
			pb=nextPos(hb);
		}
	}
	if(pa) appenList(Lc,pa);
	else appenList(Lb,pb);
	free(ha);
	La.head=La.tail=NULL;
	La.len=0;
	free(hb);
	Lb.head=Lb.tail=NULL;
	Lb.len=0;
}

//====================================һԪ����ʽӦ��====================================

int compare_term_status(term a,term b) //<:-1 =:0 >1
{
	if(a.expn==b.expn) return 0;
	else return (a.expn - b.expn)/abs(a.expn -b.expn);
}

//������pָ���ֵΪe�Ľ��
void makeNode_RLP(LPLink &p,PoElemType e)
{
	p=(LPLink)malloc(sizeof(LPNode));
	if(!p) exit(0);
	p->data = e;
}

//�ͷ�p��ָ�Ľ��
void freeNode_RLP(LPLink &p)
{
	free(p);
	p=NULL;
}

//hָ��L��һ�����,��h����ͷ���,��s��ָ�������ڵ�һ�����֮ǰ
void insertFirst_RLP(LPRLinkList &L,LPLink h,LPLink s)
{
	s->next=h->next;
	h->next =s;
	if(h==L.tail) L.tail=h->next;
	++L.len;
}

//
void initList_RLP(LPRLinkList &L)
{
	LPLink p;
	p=(LPLink)malloc(sizeof(LPNode));
	if(p)
	{
		p->next=NULL;
		L.head=L.tail=p;
		L.len=0;
	}
	else
		exit(0);
}

//�ж�һ�����Ƿ�Ϊ�ձ�
bool isEmpty_RLP(polynomial p)
{
	if(p.len) return false;
	else return true;
}

//����L����Ϊ��
void clearList_RLP(polynomial &L)
{
	LPLink p,q;
	if(L.head!=L.tail)
	{
		p=q=L.head->next;
		L.head->next=NULL;
		while(p!=L.tail)
		{
			p=q->next;
			free(q);
			q=p;
		}
		free(q);
		L.tail=L.head;
		L.len=0;
	}
}

//�������Ա�L
void destroyList_RLP(polynomial &L)
{
	clearList_RLP(L);
	freeNode_RLP(L.head);
	L.tail=NULL;
	L.len=0;
}

//��pb ��չpa
void appenList_RLP(polynomial L,LPLink s)
{
	int i=1;
	L.tail->next=s;
	while(s->next)
	{
		s=s->next;
		++i;
	}
	L.tail=s;
	L.len+=i;
}

//hָ��L��һ�����,��h����ͷ���,ɾ�������еĵ�һ����㲢��q����
bool deleteFirst_RLP(LPRLinkList &L,LPLink h,LPLink &q)
{
	q=h->next;
	if(q)
	{
		h->next = q->next;
		if(!h->next) L.tail=h;
		--L.len;
		return true;
	}
	else return false;
}

//���ص�һ����e�����ж������Ľ��λ��
bool locateElemPos_RLP(LPRLinkList L,PoElemType e,LPPosition &q,compare_term_func cFunc)
{
	LPLink p=L.head,pp;
	do 
	{
		pp=p;
		p=p->next;
	} while (p&& cFunc(p->data,e)<0 );

	if(!p||cFunc(p->data,e)>0)
	{
		q=pp;
		return false;
	}
	else
	{
		q=p;
		return true;
	}
}
//��e ���õ����к��ʵ�λ��
void orderInsertMerge(LPRLinkList &L,PoElemType e,compare_term_func cFunc)
{
	LPPosition q,s;
	if(locateElemPos_RLP(L,e,q,cFunc))//L�д��ڸ���
	{
		q->data.coef+=e.coef;//�ı䵱ǰ���ϵ��
		if(!q->data.coef) //ϵ��Ϊ0,ɾ����ǰ���
		{
			s=priorPos_RLP(L,q);
			if(!s) s=L.head;
			deleteFirst_RLP(L,s,q);
			freeNode_RLP(q);
		}
	}
	else//���ɸ�ָ�����������
	{
		makeNode_RLP(s,e);
		insertFirst_RLP(L,q,s);
	}
}

//����pָ���ǰ��λ��
LPPosition priorPos_RLP(LPRLinkList &L,LPLink p)
{
	LPLink q;
	q=L.head->next;
	if(q==p) return NULL;
	else
	{
		while(q->next!=p) q=q->next;
		return q;
	}
}

//�������ʽ�����ļ����к�,������ʾһԪ�������������p
void createPolyn(polynomial &P,const char *fileName,int mLine)
{
	using namespace std;
	int curLine=0;
	ifstream fin(fileName);
	char buffer[1024];
	term e;
	LPPosition q,s;
	initList_RLP(P);
	if(fin.is_open())
	{
		while(curLine <mLine)
		{
			fin.getline(buffer,sizeof(buffer));
			++curLine;
		}
		string str;
		int modeFlag = 0;
		int curChar = 0;
		while(buffer[curChar]!='\0')
		{
			if (buffer[curChar]==' ')
			{
				if(modeFlag%2 == 0)
				{
					e.coef = stringToNum<float>(str);
				}
				else
				{
					e.expn = stringToNum<int>(str);
					if(!locateElemPos_RLP(P,e,q,compare_term_status))
					{
						makeNode_RLP(s,e);
						insertFirst_RLP(P,q,s);
					}
				}
				str.clear();
				++modeFlag;
			}
			else
			{
				str+=buffer[curChar];
			}
			++curChar;
		}
	}
}

//��ӡ����ʽ
void printPolyn(polynomial P)
{
	printf("start print polynomial\n");
	LPLink q;
	q=P.head->next;
	while(q)
	{
		printf("%.2f    %d\n",q->data.coef,q->data.expn);
		q=q->next;
	}
}

//�����������
void addPolyn(polynomial &Pa,polynomial &Pb)
{
	LPPosition ha=Pa.head,hb=Pb.head,qa,qb;
	term a,b;
	qa=ha->next;
	qb=hb->next;
	while(!isEmpty_RLP(Pa)&&!isEmpty_RLP(Pb)&&qa)
	{
		a=qa->data;
		b=qb->data;

		int caseStatus = compare_term_status(a,b);
		switch(caseStatus)
		{
		case -1:
			ha=qa;
			qa=ha->next;
			break;
		case 0:
			qa->data.coef+=qb->data.coef;
			if(qa->data.coef==0)
			{
				deleteFirst_RLP(Pa,ha,qa);
				freeNode_RLP(qa);
			}
			else
			{
				ha = qa;
			}
			deleteFirst_RLP(Pb,hb,qb);
			freeNode_RLP(qb);
			qb=hb->next;
			qa=ha->next;
			break;
		case 1:
			deleteFirst_RLP(Pb,hb,qb);
			insertFirst_RLP(Pa,ha,qb);
			ha=ha->next;
			qb=hb->next;
			break;

		}
	}
	if(!isEmpty_RLP(Pb))
	{
		Pb.tail=hb;
		appenList_RLP(Pa,qb);
	}
	destroyList_RLP(Pb);

}

//��һ�����˸�����ʽ��ӵķ���
void addPolyn1(polynomial &Pa,polynomial &Pb)
{
	LPPosition qb;
	term b;
	qb=Pb.head->next;
	while(qb)
	{
		b=qb->data;
		orderInsertMerge(Pa,b,compare_term_status);
		qb=qb->next;
	}
	destroyList_RLP(Pb);
}