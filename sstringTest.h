#ifndef __SSTRINGTEST_HH_
#define __SSTRINGTEST_HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
using namespace std;

#define MAX_STR_LEN 2048
//typedef char SString[MAX_STR_LEN+1];
typedef int SString[MAX_STR_LEN+1];

//生成一个其值等于chars的串T
bool strAssign(SString T,char *chars);


//将S复制到T
void strCopy(SString T,SString S);


//判断串是否为空
bool isStrEmpty(SString S);


//比较串
int strCompare(SString S,SString T);


//返回S的元素个数
int strLength(SString S);


//将S清为空串
void clearString(SString S);


//将s1和s2拼接成t
bool concatStr(SString T,SString S1,SString S2);


//返回串中自第pos个字符起长度为len的子串
bool subString(SString Sub,SString S,int pos=1,int len=1);


//返回子串在主串pos位置
int indexInMainStr(SString S,SString T,int pos);


//在串s的第pos个字符之前插入串T
bool strInsert(SString S,int pos,SString T);



//删除S中自第pos个字符起长度为len的子串
bool strDelete(SString S,int pos,int len);


//用V替换主串S中出现的所有与T相等的不重叠的子串
bool replaceStr(SString S,SString T,SString V);


//输出字串
void strPrint(SString T);


//求得模式串T的next函数值并存入数组next
void get_next(SString T,int next[]);

//模式串T的next函数修正值并存入数组nextval
void get_nextval(SString T,int nextval[]);


//利用模式串T的next函数求在主串S中第pos个字符之后的位置的kmp算法 
int index_KMP(SString S,SString T,int pos,int next[]);


//将非空串str分割成两部分：hstr为第一个′,′之前的子串，str为之后的子串
void server(SString str,SString hstr);

//将数字串转换为数字
long long ssToNumber(SString str);
#endif