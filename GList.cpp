
#include "stdafx.h"
#include "GList.h"

//�����յĹ����
void initGList(GList &L)
{
	L=NULL;
}

//����ͷβ����洢�ṹ
void createGList(GList &L,int nline,const char *fileName)
{
	SString S;
	char buf[BASE_BUFF];
	ifstream fin(fileName,ios_base::in);
	if(fin.is_open())
	{

	}
	else
		exit(0);

	SString sub,hsub,emp;
	GList p,q;
	strAssign(emp,")");
	if(!strCompare(S,emp)) L=NULL;
	else
	{
		if(!(L=(GList)malloc(sizeof(GLNode)))) exit(OVERFLOW);
		if(strLength(S)==1) //S Ϊ��ԭ��,ֻ������ڵݹ������
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

void testGListMain()
{

}