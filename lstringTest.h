#ifndef __LSTRINGTEST_HH_
#define __LSTRINGTEST_HH_

#include <malloc.h>
#include <process.h>
#include <iostream>


using namespace std;

namespace LS{

struct HString
{
	char *ch;
	int length;
};

#define CHUNK_SIZE 4
struct Chunk
{
	char ch[CHUNK_SIZE];
	Chunk *next;
	Chunk():next(NULL){}
};

struct LString
{
	Chunk *head,*tail;//串的头尾指针
	int curlen;
};
//生成一个其值等于chars的串T
bool strAssign(LString &T,char *chars)
{
	int i,j,k,m;
	Chunk *p,*q=NULL;
	i=strlen(chars);
	if(!i||strchr(chars,ctype_base::blank)) return false;

	T.curlen=i;
	j=i/CHUNK_SIZE;
	if(i%CHUNK_SIZE) ++j;
	for(k=0;k<j;++k)
	{
		p=(Chunk*)malloc(sizeof(Chunk));
		if(!p) return false;
		for(m=0;m<CHUNK_SIZE&&*chars;++m)
			*(p->ch+m)=*chars++;
		if(k==0) T.head=q=p;
		else
		{
			q->next=p;
			q=p;
		}
		if(!*chars)
		{
			T.tail=q;
			q->next=NULL;
			for(;m<CHUNK_SIZE;++m)
				*(q->ch+m)=ctype_base::blank;
		}
	}
	return true;
}

//将串T的内容转换为字符串
bool toChars(LString T,char *&chars)
{
	Chunk *p=T.head;
	int i;
	char *q;
	chars=(char*)malloc((T.curlen+1)*sizeof(char));
	if(!chars||!T.curlen) return false;
	q=chars;
	while(p)
	{
		for(i=0;i<CHUNK_SIZE;++i)
			if(p->ch[i]!=ctype_base::blank) *q++=(p->ch[i]);
		p=p->next;
	}
	chars[T.curlen]='\0';
	return true;
}

//将S复制到T
bool strCopy(LString &T,LString S)
{
	char *c=NULL;
	bool i;
	if(!toChars(S,c)) return false;
	i=strAssign(T,c);
	free(c);
	return true;
}

//判断串是否为空
bool isStrEmpty(LString S)
{
	if(S.curlen) return false;
	return true;
}

//比较串
int strCompare(LString S,LString T)
{
	char *s=NULL,*t=NULL;
	bool i;
	if(!toChars(S,s)) return false;
	if(!toChars(T,t)) return false;
	i=(bool)strcmp(s,t);
	free(s);
	free(t);
	return i;
}

//返回S的元素个数
int strLength(LString S)
{
	return S.curlen;
}

//将S清为空串
void clearString(LString S)
{
	Chunk *p,*q;
	p=S.head;
	while(p)
	{
		q=p->next;
		free(p);
		p=q;
	}
	S.head=S.tail=NULL;
	S.curlen=0;
}

//初始化字符串
void initString(LString &T)
{
	T.curlen=0;
	T.head=T.tail=NULL;
}

//将s1和s2拼接成t
bool concatStr(LString &T,LString S1,LString S2)
{
	LString a1,a2;
	initString(a1);
	initString(a2);
	if(!strCopy(a1,S1)||!strCopy(a2,S2)) return false;
	T.curlen=S1.curlen+S2.curlen;
	T.head=a1.head;
	a1.tail->next=a2.head;
	T.tail=a2.tail;
	return true;

}

//返回串中自第pos个字符起长度为len的子串
bool subString(LString &Sub,LString S,int pos=1,int len=1)
{
	char *b=NULL,*c=NULL;
	bool i;
	if(pos<1||pos>S.curlen||len<0||len>S.curlen-pos+1) return false;
	if(!toChars(S,c)) return false;
	b=c+pos-1;
	b[len]=0;
	i=strAssign(Sub,b);
	free(c);
	return i;
}



//返回子串在主串pos位置
int indexInMainStr(LString S,LString T,int pos)
{
	int i,n,m;
	LString sub;
	if(pos>=1&&pos<=strLength(S))
	{
		n=strLength(S);
		m=strLength(T);
		i=pos;
		while(i<=n-m+1)
		{
			subString(sub,S,i,m);
			if(strCompare(sub,T)) ++i;
			else return i;
		}
	}
	return 0;
}

//在串s的第pos个字符之前插入串T
bool strInsert(LString &S,int pos,LString T)
{
	char *b=NULL,*c=NULL;
	int i,j;
	bool k;
	if(pos<1||pos>S.curlen+1) return false;
	if(!toChars(S,c)||!toChars(T,b)) return false;
	j=(int)strlen(c);
	c=(char*)realloc(c,(j+strlen(b)+1)*sizeof(char));
	for(i=j;i>=pos-1;--i) c[i+strlen(b)]=c[i];
	for(i=0;i<(int)strlen(b);++i) c[pos+i-1]=b[i];
	initString(S);
	k=strAssign(S,c);
	free(b);
	free(c);
	return k;
}

//删除S中自第pos个字符起长度为len的子串
bool strDelete(LString &S,int pos,int len)
{
	char *c=NULL;
	int i;
	bool k;
	if(pos<1||pos>S.curlen-len+1||len<0) return false;
	if(!toChars(S,c)) return false;
	for(i=pos+len-1;i<=(int)strlen(c);++i) c[i-len]=c[i];
	initString(S);
	k=strAssign(S,c);
	free(c);
	return k;
}

//用V替换主串S中出现的所有与T相等的不重叠的子串
bool replaceStr(LString &S,LString T,LString V)
{
	int i=1;
	if(isStrEmpty(T)) return false;
	do 
	{
		i=indexInMainStr(S,T,i);
		if(i)
		{
			strDelete(S,i,strLength(T));
			strInsert(S,i,V);
			i+=strLength(V);
		}
	} while (i);
	return true;
}

//输出字串
void strPrint(LString T)
{
	int i=0,j;
	Chunk *h=T.head;
	while(i<T.curlen)
	{
		for(j=0;j<CHUNK_SIZE;++j)
			if(*(h->ch+j)!=ctype_base::blank)
			{
				cout<<*(h->ch+j);
				++i;
			}
		h=h->next;
	}
	cout<<endl;
}

};

#endif