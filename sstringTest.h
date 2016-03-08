#ifndef __SSTRINGTEST_HH_
#define __SSTRINGTEST_HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
using namespace std;

#define MAX_STR_LEN 2048
//typedef char SString[MAX_STR_LEN+1];
typedef int SString[MAX_STR_LEN+1];

//����һ����ֵ����chars�Ĵ�T
bool strAssign(SString T,char *chars);


//��S���Ƶ�T
void strCopy(SString T,SString S);


//�жϴ��Ƿ�Ϊ��
bool isStrEmpty(SString S);


//�Ƚϴ�
int strCompare(SString S,SString T);


//����S��Ԫ�ظ���
int strLength(SString S);


//��S��Ϊ�մ�
void clearString(SString S);


//��s1��s2ƴ�ӳ�t
bool concatStr(SString T,SString S1,SString S2);


//���ش����Ե�pos���ַ��𳤶�Ϊlen���Ӵ�
bool subString(SString Sub,SString S,int pos=1,int len=1);


//�����Ӵ�������posλ��
int indexInMainStr(SString S,SString T,int pos);


//�ڴ�s�ĵ�pos���ַ�֮ǰ���봮T
bool strInsert(SString S,int pos,SString T);



//ɾ��S���Ե�pos���ַ��𳤶�Ϊlen���Ӵ�
bool strDelete(SString S,int pos,int len);


//��V�滻����S�г��ֵ�������T��ȵĲ��ص����Ӵ�
bool replaceStr(SString S,SString T,SString V);


//����ִ�
void strPrint(SString T);


//���ģʽ��T��next����ֵ����������next
void get_next(SString T,int next[]);

//ģʽ��T��next��������ֵ����������nextval
void get_nextval(SString T,int nextval[]);


//����ģʽ��T��next������������S�е�pos���ַ�֮���λ�õ�kmp�㷨 
int index_KMP(SString S,SString T,int pos,int next[]);


//���ǿմ�str�ָ�������֣�hstrΪ��һ����,��֮ǰ���Ӵ���strΪ֮����Ӵ�
void server(SString str,SString hstr);

//�����ִ�ת��Ϊ����
long long ssToNumber(SString str);
#endif