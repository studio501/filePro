#include "stdafx.h"
#include <malloc.h>
#include <process.h>
#include <math.h>
#include <fstream>
#include "testLinkList.h"
#include <iostream>


//构造空的线性表
void initList(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	if(!L) exit(OVERFLOW);
	L->next=NULL;
}

//销毁线性表
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

//将L重置为空表
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

//表是否为空
bool isEmpty(LinkList &L)
{
	if(L->next) return false;
	else return true;
}

//返回表长
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

//获取位置i的元素
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

//找到位置i的元素
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

//是数据元素的判定 返回L中第1个与e满足compare()关系的数据元素位序
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

//返回cur_e的前驱
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

//返回cur_e的后继
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

//在位置i插入e
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

//删除位置i元素
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

//遍历list
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

//求la lb 并集
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

//冒泡排序
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

//按la,lb有序归并为lc
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

//按la,lb有序归并为lc
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

//从文件里读取数据创建表
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

//从文件里读取数据创建表
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

//静态链表相关测试
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

//构造一个空的线性表
void initList_SL(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	if(!L) exit(OVERFLOW);
	L->next = L;
}

//销毁线性表
void destroyList_SL(LinkList &L)
{
	LinkList q,p = L->next;
	while(p!=L) //没到表尾
	{
		q = p->next;
		free(p);
		p = q;
	}
	free(L);
	L=NULL;
}

//将L置空
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
	L->next = L;//头结点域指向自身
}

//判断L是否为空
bool isEmpty_SL(LinkList &L)
{
	if(L->next == L) return true;
	else  return false;
}

//取得表长
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

//获取第i个元素
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

//是数据元素的判定 返回L中第1个与e满足compare()关系的数据元素位序
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

//找到cur_e的前驱
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

//找到cur_e的后继
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

//在i位置插入e
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

//删除第i个位置元素
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

//遍历L
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

//将Lb合并到La的表尾
void listMerge_SL(LinkList &La,LinkList &Lb)
{
	LinkList p = Lb->next;
	Lb->next = La->next;
	La->next = p->next;
	free(p);
	La = Lb;
}

//创建空表
void initList_Du(DuLinkList &L)
{
	L=(DuLinkList)malloc(sizeof(DuLinkList));
	if(!L) exit(OVERFLOW);
	L->next = L->prior = L;
}

//销毁表
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

//重置表
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

//判断是否表空
bool isEmpty_Du(DuLinkList &L)
{
	if(L->next==L && L->prior==L) return true;
	else return false;
}

///获取表长度
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

//获取位置i的元素
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

//返回第1 个与e满足compare关系的数据
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

//返回cur_e 的前驱
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

//返回cur_e 的后继
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

//返回第i个元素所在地址
DuLinkList findElemByIndex_Du(DuLinkList &L,int i)
{
	DuLinkList p=L;
	if(i<0 || i>listLength_Du(L)) return NULL;
	for(int j=1;j<=i;++j) p=p->next;
	return p;
}

//在位置i插入e
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

//删除位置i 的元素
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

//遍历表
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

//逆序遍历表
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

//分配由p指向的值为e的结点
void makeNode(Link &p,ElemType e)
{
	p=(Link)malloc(sizeof(LNode));
	if(!p) exit(0);
	p->data = e;
}

//释放p所指的结点
void freeNode(Link &p)
{
	free(p);
	p=NULL;
}

//构造一个空的线性表
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

//将表L重置为空
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

//销毁线性表L
void destroyList_RL(RLinkList &L)
{
	clearList_RL(L);
	freeNode(L.head);
	L.tail=NULL;
	L.len=0;
}

//h指向L的一个结点,把h当做头结点,将s所指结点插入在第一个结点之前
void insertFirst(RLinkList &L,Link h,Link s)
{
	s->next=h->next;
	h->next =s;
	if(h==L.tail) L.tail=h->next;
	++L.len;
}

//h指向L的一个结点,把h当做头结点,删除链表中的第一个结点并以q返回
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

//将s所指的一串结点链接在L的最后一个结点之后,并改变链表尾指针指向新的结点
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

//返回p指向的前驱位置
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

//删除尾结点并以q返回,改变L的尾指针指向新的尾结点
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

//s所指结点插入p所指结点之前
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

//s所指结点插入p所指结点之后
void insAfter(RLinkList &L,Link &p,Link s)
{
	if(p==L.tail) L.tail=s;
	s->next=p->next;
	p->next=s;
	p=s;
	++L.len;
}

//用e更新p所指的结点
void setCurElem(Link p,ElemType e)
{
	p->data=e;
}

//获取p所指向的元素
ElemType getCurElem(Link p)
{
	return p->data;
}

//判断L是否为空表
bool isEmpty_RL(RLinkList &L)
{
	if(L.len) return false;
	else return true;
}

//获取L的头结点
Position getHead(RLinkList L)
{
	return L.head;
}

//获取L的尾结点
Position getTail(RLinkList L)
{
	return L.tail;
}

//下一个位置
Position nextPos(Link p)
{
	return p->next;
}

//返回第i个结点的指针
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

//返回线性表中第1个与e满足函数compare判定关系元素的位置
Position locateElem_RL(RLinkList L,ElemType e,compare_func cFunc)
{
	Link p=L.head;
	do 
		p=p->next;
	while(p&&!(cFunc(p->data,e)));
	return p;
}

//遍历L
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

//按序插入e
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

//返回第一个与e满足判定函数的结点位置
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

//在第i个元素位置插入e
bool listInsert_RL(RLinkList &L,int i,ElemType e)
{
	Link h,s;
	if(!locatePos(L,i-1,h)) return false;
	makeNode(s,e);
	insertFirst(L,h,s);
	return true;
}

//对表使用冒泡排序
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

//有序归并为新表
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