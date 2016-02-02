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