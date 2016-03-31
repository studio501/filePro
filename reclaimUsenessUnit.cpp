
#include "stdafx.h"
typedef char AtomType;
#include "reclaimUsenessUnit.h"

#include "sstringTest.h"

typedef void(&vFunc)(GList);

static void visit(GList p)
{
	if(p->tag==ATOM)
		printf("mark=%d %c\n",p->mark,p->atom);
	else
		printf("mark=%d list\n",p->mark);
}

//遍历广义表 对所有未加标志的结点加上标志
static void markList(GList GL)
{
	GList q,p=GL,t=NULL;
	bool finished=false;
	if(!GL) return;
	while(!finished)
	{
		while(p->mark!=1)
		{
			p->mark=1;
			q=p->ptr.hp;
			if(q&&q->mark!=1)
				if(q->tag==0)
					q->mark=1;
				else
				{
					p->ptr.hp=t;
					p->tag=ATOM;
					t=p;
					p=q;
				}
		}//完成对表头的标志
		q=p->ptr.tp;
		if(q&&q->mark!=1)
		{
			p->ptr.tp=t;
			t=p;
			p=q;
		}
		else
		{
			while(t&&t->tag==1)
			{
				q=t;
				t=q->ptr.tp;
				q->ptr.tp=p;
				p=q;
			}
			if(!t) finished=true;
			else
			{
				//从表头回溯
				q=t;
				t=q->ptr.hp;
				q->ptr.hp=p;
				p=q;
				p->tag=LIST;
			}
		}
	}
}

//递归遍历广义表
static void traverse_GL(GList L,vFunc func)
{
	if(L)
		if(L->tag==ATOM)
			func(L);
		else
		{
			func(L);
			traverse_GL(L->ptr.hp,func);
			traverse_GL(L->ptr.tp,func);
		}
}

static void createGList(GList &L,SString S)
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

void testReclaim()
{
	SString t;
	//char str[] = "(a,(b,c,d),(e,f),((g,h),k))";
	//char str[] = "(a,(b,c,d))";
	char str[] = "(((x),()),(),y,(z))";
	strAssign(t,str);
	GList l;
	createGList(l,t);
	markList(l);
	traverse_GL(l,visit);
}
