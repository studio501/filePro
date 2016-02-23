#ifndef __SSTRINGTEST_HH_
#define __SSTRINGTEST_HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
using namespace std;

#define MAX_STR_LEN 40
typedef char SString[MAX_STR_LEN+1];

//生成一个其值等于chars的串T
bool strAssign(SString T,char *chars)
{
	if(strlen(chars)>MAX_STR_LEN) return false;
	else
	{
		T[0]=strlen(chars);
		for(int i=1;i<=T[0];++i) T[i]=*(chars+i-1);
		return true;
	}
}

//将S复制到T
void strCopy(SString T,SString S)
{
	for(int i=0;i<=S[0];++i) T[i]=S[i];
}

//判断串是否为空
bool isStrEmpty(SString S)
{
	if(S[0]==0) return true;
	else return false;
}

//比较串
int strCompare(SString S,SString T)
{
	for(int i=1;i<=S[0];++i)
		if(S[i]!=T[i]) return S[i]-T[i];
	return S[0]-T[0];
}

//返回S的元素个数
int strLength(SString S)
{
	return S[0];
}

//将S清为空串
void clearString(SString S)
{
	S[0]=0;
}

//将s1和s2拼接成t
bool concatStr(SString T,SString S1,SString S2)
{
	if(S1[0]+S1[0]<=MAX_STR_LEN)
	{
		for(int i=1;i<=S1[0];++i)
			T[i]=S1[i];
		for(int i=1;i<=S2[0];++i)
			T[S1[0]+i]=S2[i];
		T[0]=S1[0]+S2[0];
		return true;
	}
	else
	{
		for(int i=1;i<=S1[0];++i)
			T[i]=S1[i];
		for(int i=1;i<=MAX_STR_LEN-S1[0];++i)
			T[S1[0]+i]=S2[i];
		T[0]=MAX_STR_LEN;
		return false;
	}
}

//返回串中自第pos个字符起长度为len的子串
bool subString(SString Sub,SString S,int pos=1,int len=1)
{
	if(pos<1||pos>S[0] || len<0 || len > S[0]-pos+1) return false;
	for(int i=1;i<=len;++i)
		Sub[i]=S[pos+i-1];
	Sub[0]=len;
	return true;
}

//返回子串在主串pos位置
int indexInMainStr(SString S,SString T,int pos)
{
	int i,j;
	if(1<=pos && pos<=S[0])
	{
		i=pos;
		j=1;
		while(i<= S[0] && j<=T[0])
			if(S[i]==T[j])
			{
				++i;
				++j;
			}
			else
			{
				i=i-j+2;
				j=1;
			}
		if(j>T[0]) return i-T[0];
		else return 0;
	}
	else return 0;
}

//在串s的第pos个字符之前插入串T
bool strInsert(SString S,int pos,SString T)
{
	int i;
	if(pos<1||pos>S[0]+1) return false;
	if(S[0]+T[0]<=MAX_STR_LEN)
	{
		for(i=S[0];i>=pos;--i) S[i+T[0]]=S[i];
		for(i=pos;i<pos+T[0];++i) S[i]=T[i-pos+1];
		S[0]+=T[0];
		return true;
	}
	else
	{
		for(i=MAX_STR_LEN;i>=pos+T[0];--i)
			S[i]=S[i-T[0]];
		for(i=pos;i<pos+T[0]&&i<=MAX_STR_LEN;++i)
			S[i]=T[i-pos+1];
		S[0]=MAX_STR_LEN;
		return false;
	}
}

//删除S中自第pos个字符起长度为len的子串
bool strDelete(SString S,int pos,int len)
{
	int i;
	if(pos<1||pos>S[0]-len+1||len<0) return false;
	for(i=pos+len;i<=S[0];++i) S[i-len]=S[i];
	S[0]-=len;
	return true;
}

//用V替换主串S中出现的所有与T相等的不重叠的子串
bool replaceStr(SString S,SString T,SString V)
{
	int i=1;
	bool k;
	if(isStrEmpty(T)) return false;
	do 
	{
		i=indexInMainStr(S,T,i);
		if(i)
		{
			strDelete(S,i,strLength(T));
			k=strInsert(S,i,V);
			if(!k) return false;
			i+=strLength(V);
		}
	} while (i);
	return true;
}

//输出字串
void strPrint(SString T)
{
	for(int i=1;i<=T[0];++i)
		cout<<T[i];
	cout<<endl;
}


//求得模式串T的next函数值并存入数组next
void get_next(SString T,int next[])
{
	int i=1,j=0;
	next[1]=0;
	while(i<T[0])
		if(j==0||T[i]==T[j])
		{
			++i;
			++j;
			next[i]=j;
		}
		else
			j=next[j];
}

//模式串T的next函数修正值并存入数组nextval
void get_nextval(SString T,int nextval[])
{
	int i=1,j=0;
	nextval[1]=0;
	while(i<T[0])
		if(j==0||T[i]==T[j])
		{
			++i;++j;
			if(T[i]!=T[j]) nextval[i]=j;
			else nextval[i]=nextval[j];
		}
		else j=nextval[j];
}

//利用模式串T的next函数求在主串S中第pos个字符之后的位置的kmp算法 
int index_KMP(SString S,SString T,int pos,int next[])
{
	int i=pos,j=1;
	while(i<=S[0]&&j<=T[0])
		if(j==0||S[i]==T[j])
		{
			++i;++j;
		}
		else
			j=next[j];
	if(j>T[0]) return i-T[0];
	else return 0;
}

#endif