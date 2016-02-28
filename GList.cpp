
#include "stdafx.h"
#include "GList.h"

//创建空的广义表
void initGList(GList &L)
{
	L=NULL;
}

//采用头尾链表存储结构
void createGList(GList &L,SString S)
{

	SString sub,hsub,emp;
	GList p,q;
	strAssign(emp,"()");
	if(!strCompare(S,emp)) L=NULL;
	else
	{
		if(!(L=(GList)malloc(sizeof(GLNode)))) exit(OVERFLOW);
		if(strLength(S)==1) //S 为单原子,只会出现在递归调用中
		{
			L->tag=ATOM;
			L->atom=S[1];
		}
		else
		{
			L->tag=LIST;
			p=L;
			subString(sub,S,2,strLength(S)-2);
			do 
			{
				server(sub,hsub);
				createGList(p->ptr.hp,hsub);
				q=p;
				if(!isStrEmpty(sub))
				{
					if(!(p=(GLNode*)malloc(sizeof(GLNode)))) exit(OVERFLOW);
					p->tag=LIST;
					q->ptr.tp=p;
				}
			} while (!isStrEmpty(sub));
			q->ptr.tp=NULL;
		}
	}
}

//销毁链表
void destroyGList(GList &L)
{
	GList q1,q2;
	if(L)
	{
		if(L->tag==LIST)
		{
			q1=L->ptr.hp;
			q2=L->ptr.tp;
			destroyGList(q1);
			destroyGList(q2);
		}
		free(L);
		L=NULL;
	}
}

//拷贝表
void copyGList(GList &T,GList L)
{
	if(!L) T=NULL;
	else
	{
		T=(GList)malloc(sizeof(GLNode));
		if(!T) exit(OVERFLOW);
		T->tag=L->tag;
		if(L->tag==ATOM) T->atom=L->atom;
		else
		{
			copyGList(L->ptr.hp,L->ptr.hp);
			copyGList(L->ptr.tp,L->ptr.tp);
		}
	}
}

//获取表长度
int GListLength(GList L)
{
	int len=0;
	while(L)
	{
		L=L->ptr.tp;
		++len;
	}
	return len;
}

//求广义表的深度
int GListDepth(GList L)
{
	int max,depth;
	GList pp;
	if(!L) return 1;
	if(L->tag==ATOM) return 0;
	for(max=0,pp=L;pp;pp=pp->ptr.tp)
	{
		depth=GListDepth(pp->ptr.hp);
		if(depth>max) max=depth;
	}
	return max+1;
}

//判断广义表是否为空
bool GListEmpty(GList L)
{
	if(!L) return true;
	else return false;
}

//获取头或者尾 
GList getEdge(GList L,int side)
{
	GList p;
	if(!L) return NULL;
	if (side==0)
		copyGList(p,L->ptr.hp);
	else copyGList(p,L->ptr.tp);
	return p;
}

//插入元素e作为表的第一个元素
void insertFirst(GList &L,GList e)
{
	GList p=(GList)malloc(sizeof(GLNode));
	if(!p) exit(OVERFLOW);
	p->tag=LIST;
	p->ptr.hp=e;
	p->ptr.tp=L;
	L=p;
}

//删除第一个元素并用e返回其值
void deleteFirst(GList &L,GList &e)
{
	GList p=L;
	e=L->ptr.hp;
	L=L->ptr.tp;
	free(p);
}

//遍历广义表
void traverse_GL(GList &L,viGLFunc func)
{
	if(L)
		if(L->tag==ATOM)
			func(L->atom);
		else
		{
			traverse_GL(L->ptr.hp,func);
			traverse_GL(L->ptr.tp,func);
		}
}

void visit(AtomType e)
{
	printf("%c ",e);
}

void testGListMain()
{
	SString s;
	strAssign(s,"(a,(b,c,(m,n,l)),(d,e),())");
	GList l;
	initGList(l);
	createGList(l,s);
	traverse_GL(l,visit);
	cout<<"\nlength of list :"<<GListLength(l)<<endl;
	cout<<"depth of list :"<<GListDepth(l)<<endl;
}