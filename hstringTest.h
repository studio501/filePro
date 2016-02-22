#ifndef __HSTRINGTEST_HH_
#define __HSTRINGTEST_HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
using namespace std;

namespace HS{

struct HString
{
	char *ch;
	int length;
};

//生成一个其值等于chars的串T
bool strAssign(HString &T,char *chars)
{
	if(T.ch) free(T.ch);
	int i=strlen(chars);
	if(!i)
	{
		T.ch=NULL;
		T.length=0;
	}
	else
	{
		T.ch=(char *)malloc(i*sizeof(char));
		if(!T.ch) exit(OVERFLOW);
		for(int j=0;j<i;++j) T.ch[j]=chars[j];
		T.length=i;
	}
}

//将S复制到T
void strCopy(HString &T,HString S)
{
	if(T.ch) free(T.ch);
	T.ch=(char*)malloc(S.length*sizeof(char));
	if(!T.ch) exit(OVERFLOW);
	for(int i=0;i<S.length;++i) T.ch[i]=S.ch[i];
	T.length=S.length;
}

//判断串是否为空
bool isStrEmpty(HString S)
{
	if(S.length==0&&S.ch==NULL) return true;
	else return false;
}

//比较串
int strCompare(HString S,HString T)
{
	for(int i=0;i<S.length&&i<T.length;++i)
		if(S.ch[i]!=T.ch[i]) return S.ch[i]-T.ch[i];
	return S.length-T.length;
}

//返回S的元素个数
int strLength(HString S)
{
	return S.length;
}

//将S清为空串
void clearString(HString S)
{
	free(S.ch);
	S.ch=NULL;
	S.length=0;
}

//将s1和s2拼接成t
bool concatStr(HString &T,HString S1,HString S2)
{
	if(T.ch) free(T.ch);
	T.length=S1.length+S2.length;
	T.ch=(char*)malloc(sizeof(char)*T.length);
	if(!T.ch) exit(OVERFLOW);
	for(int i=0;i<S1.length;++i) T.ch[i]=S1.ch[i];
	for(int i=0;i<S2.length;++i) T.ch[S1.length+i]=S2.ch[i];
}

//返回串中自第pos个字符起长度为len的子串
bool subString(HString &Sub,HString S,int pos=1,int len=1)
{
	if(pos<1||pos>S.length||len<0||len>S.length-pos+1) return false;
	if(Sub.ch) free(Sub.ch);
	if(!len)
	{
		Sub.ch=NULL;
		Sub.length=0;
	}
	else
	{
		Sub.ch=(char*)malloc(sizeof(char)*len);
		if(!Sub.ch) exit(OVERFLOW);
		for(int i=0;i<=len-1;++i) Sub.ch[i]=S.ch[pos-1+i];
		Sub.length=len;
	}
	return true;
}

//初始化字符串
void initString(HString &T)
{
	T.length=0;
	T.ch=NULL;
}

//返回子串在主串pos位置
int indexInMainStr(HString S,HString T,int pos)
{
	HString sub;
	initString(sub);
	if(pos>0)
	{
		int n=strLength(S),m=strLength(T);
		int i=pos;
		while(i<=n-m+1)
		{
			subString(sub,S,i,m);
			if(strCompare(sub,T)!=0) ++i;
			else return i;
		}
	}
	return 0;
}

//在串s的第pos个字符之前插入串T
bool strInsert(HString &S,int pos,HString T)
{
	if(pos<1||pos>S.length+1) return false;
	if(T.length)
	{
		S.ch=(char *)realloc(S.ch,(S.length+T.length)*sizeof(char));
		if(!S.ch) exit(OVERFLOW);
		for(int i=S.length-1;i>=pos-1;--i)
			S.ch[i+T.length]=S.ch[i];
		for(int i=0;i<T.length;++i)
			S.ch[pos-1+i]=T.ch[i];
		S.length+=T.length;
	}
	return true;
}

//删除S中自第pos个字符起长度为len的子串
bool strDelete(HString &S,int pos,int len)
{
	if(S.length<pos+len-1) return false;
	for(int i=pos-1;i<=S.length-len;++i) S.ch[i]=S.ch[i+len];
	S.length-=len;
	S.ch=(char *)realloc(S.ch,S.length*sizeof(char));
	return true;
}

//用V替换主串S中出现的所有与T相等的不重叠的子串
bool replaceStr(HString &S,HString T,HString V)
{
	if(isStrEmpty(T)) return false;
	int i=1;
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
void strPrint(HString T)
{
	for(int i=0;i<T.length;++i)
		cout<<T.ch[i];
	cout<<endl;
}

};

#endif