#ifndef __HSTRINGTEST_HH_
#define __HSTRINGTEST_HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>
using namespace std;

namespace HS{

struct HString
{
	char *ch;
	int length;
};

//����һ����ֵ����chars�Ĵ�T
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

//��S���Ƶ�T
void strCopy(HString &T,HString S)
{
	if(T.ch) free(T.ch);
	T.ch=(char*)malloc(S.length*sizeof(char));
	if(!T.ch) exit(OVERFLOW);
	for(int i=0;i<S.length;++i) T.ch[i]=S.ch[i];
	T.length=S.length;
}

//�жϴ��Ƿ�Ϊ��
bool isStrEmpty(HString S)
{
	if(S.length==0&&S.ch==NULL) return true;
	else return false;
}

//�Ƚϴ�
int strCompare(HString S,HString T)
{
	for(int i=0;i<S.length&&i<T.length;++i)
		if(S.ch[i]!=T.ch[i]) return S.ch[i]-T.ch[i];
	return S.length-T.length;
}

//����S��Ԫ�ظ���
int strLength(HString S)
{
	return S.length;
}

//��S��Ϊ�մ�
void clearString(HString S)
{
	free(S.ch);
	S.ch=NULL;
	S.length=0;
}

//��s1��s2ƴ�ӳ�t
bool concatStr(HString &T,HString S1,HString S2)
{
	if(T.ch) free(T.ch);
	T.length=S1.length+S2.length;
	T.ch=(char*)malloc(sizeof(char)*T.length);
	if(!T.ch) exit(OVERFLOW);
	for(int i=0;i<S1.length;++i) T.ch[i]=S1.ch[i];
	for(int i=0;i<S2.length;++i) T.ch[S1.length+i]=S2.ch[i];
}

//���ش����Ե�pos���ַ��𳤶�Ϊlen���Ӵ�
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

//��ʼ���ַ���
void initString(HString &T)
{
	T.length=0;
	T.ch=NULL;
}

//�����Ӵ�������posλ��
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

//�ڴ�s�ĵ�pos���ַ�֮ǰ���봮T
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

//ɾ��S���Ե�pos���ַ��𳤶�Ϊlen���Ӵ�
bool strDelete(HString &S,int pos,int len)
{
	if(S.length<pos+len-1) return false;
	for(int i=pos-1;i<=S.length-len;++i) S.ch[i]=S.ch[i+len];
	S.length-=len;
	S.ch=(char *)realloc(S.ch,S.length*sizeof(char));
	return true;
}

//��V�滻����S�г��ֵ�������T��ȵĲ��ص����Ӵ�
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

//����ִ�
void strPrint(HString T)
{
	for(int i=0;i<T.length;++i)
		cout<<T.ch[i];
	cout<<endl;
}


///////////////////////////������Ӧ�þ���
#define MAX_FILE_ROW_LEN 25
#define MAX_LINE_COL_LEN 75
#define FILE_NAME_LEN 20

HString T[MAX_FILE_ROW_LEN];
char str[MAX_LINE_COL_LEN],filename[FILE_NAME_LEN]="";
int nLine=0;

inline void eatline(){while(cin.get()!='\n') continue;}

//���ļ�(�»��)
void Open()
{
	if(filename[0]) cout<<"file exist\n";
	else
	{
		strcpy(filename,"apply_string.txt");
		ifstream fin(filename,ios_base::in);
		if(fin.is_open())
		{
			while(fin.getline(str,MAX_LINE_COL_LEN))
			{
				if(nLine>=MAX_FILE_ROW_LEN)
				{
					cout<<"file is too big\n";
					return;
				}
				strAssign(T[nLine++],str);
			}
			fin.close();
		}
	}
}

//��ʾ�ı�����
void List()
{
	for(int i=0;i<nLine;++i)
	{
		cout<<i+1<<" : ";
		strPrint(T[i]);
	}
}

//������
void Insert()
{
	int i,l_,m;
	cout<<"insert m lines before line l_ , please enter l_ m :";
	cin>>l_>>m;
	eatline();
	
	if(nLine+m>MAX_FILE_ROW_LEN)
	{
		cout<<"too much lines.\n";
		return;
	}
	if(nLine>=l_-1&&l_>0)
	{
		for(i=nLine-1;i>=l_-1;--i)
			T[i+m]=T[i];
		nLine+=m;
		cout<<"please enter line contents.\n";
		for(i=l_-1;i<l_-1+m;++i)
		{
			
			cin.getline(str,MAX_LINE_COL_LEN);
			initString(T[i]);
			strAssign(T[i],str);
			
		}
	}
	else
		cout<<"line is out of range.\n";

}

//ɾ����
void Delete()
{
	int i,l_,m;
	cout<<"delete m lines start with the line l_:\n";
	cin>>l_>>m;
	eatline();
	if(nLine>=l_+m-1&&l_>0)
	{
		for(i=l_-1;i<m;++i) clearString(T[i]);
		for(i=l_-1+m;i<nLine;++i)
		{
			//free(T[i-m].ch);
			//clearString(T[i-m]);
			T[i-m] =T[i];
		}
		for(i=nLine-m;i<nLine;++i)
			initString(T[i]);
		nLine-=m;
	}
	else
		cout<<"line is out of range.\n";
}

//������
void Copy()
{
	int i,l_,m,k;
	cout<<"copy m lines to k start with l_. enter l_ m k\n";
	cin>>l_>>m>>k;
	if(nLine+m>MAX_FILE_ROW_LEN)
	{
		cout<<"too much lines\n";
		return;
	}
	if(nLine>=k-1&&nLine>=l_-1+m&&(k>=l_+m||k<=l_))
	{
		for(i=nLine-1;i>=k-1;--i) T[i+m]=T[i];
		nLine+=m;
		if(k<=l_) l_+=m;
		for(i=l_-1;i<l_-1+m;++i)
		{
			initString(T[i+k-l_]);
			strCopy(T[i+k-l_],T[i]);
		}
	}
	else cout<<"line is out of range.\n";
}

//�޸���
void Modify()
{
	int i;
	cout<<"enter the line number you want to modify.\n";
	cin>>i;
	eatline();
	if(i>0&&i<=nLine)
	{
		cout<<i<<" : ";
		strPrint(T[i-1]);
		cout<<"please enter new contents.\n";
		cin.getline(str,MAX_LINE_COL_LEN);
		strAssign(T[i-1],str);
	}
	else cout<<"line is out of range.\n";
}

//�����ַ���
void Search()
{
	int i,k,f=1;
	char b;
	HString s;
	cout<<"please enter the string you want to find.\n";
	
	cin.getline(str,MAX_LINE_COL_LEN);
	initString(s);
	strAssign(s,str);
	for(i=0;i<nLine&&f;++i)
	{
		k=1;
		while(k)
		{
			k=indexInMainStr(T[i],s,k);
			if(k)
			{
				cout<<"line : "<<i+1;
				strPrint(T[i]);
				cout<<"find in "<<k<<" continue(Y/N)?"<<endl;
				cin>>b;
				if(b!='Y'&&b!='y')
				{
					f=0;
					break;
				}
				else ++k;
			}
		}
	}
	if(f) cout<<"can't find"<<endl;
}

//�滻�ַ���
void Replace()
{
	int i,k,f=1;
	char b;
	HString s,t;
	cout<<"enter the string you want to replace.\n";
	cin.getline(str,MAX_LINE_COL_LEN);
	initString(s);
	strAssign(s,str);
	cout<<"replace with:\n";
	cin.getline(str,MAX_LINE_COL_LEN);
	initString(t);
	strAssign(t,str);
	for(i=0;i<nLine&&f;++i)
	{
		k=1;
		while(k)
		{
			k=indexInMainStr(T[i],s,k);
			if(k)
			{
				cout<<"line : "<<i+1;
				strPrint(T[i]);
				cout<<"find in k: "<<k<<" will you replace it for sure(Y/N)?\n";
				cin>>b;

				if(b=='Y'||b=='y')
				{
					strDelete(T[i],k,strLength(s));
					strInsert(T[i],k,t);
				}
				cout<<"continue replacing(Y/N)?\n";
				cin>>b;
				if(b!='Y'&&b!='y')
				{
					f=0;
					break;
				}
				else
					k+=strLength(t);
			}
		}
	}
	if(f)
		cout<<"can't find it.\n";
}

//����
void Save()
{
	int i,j;
	ofstream fout(filename,ios_base::out);
	if(fout.is_open())
	{
		for(i=0;i<nLine;++i)
		{
			for(j=0;j<T[i].length;++j)
				fout<<T[i].ch[j];
			fout<<"\n";
			clearString(T[i]);
		}
		fout.close();
	}
	else
		cout<<"save failed.\n";
}

#include "testLinkList.h"

typedef int ElemType;
#define MaxKeyNum 25
#define MaxLineLen 52
#define MaxNoIdx 10

struct WordListType //һ����Ŀ�Ĵʱ�(˳���)�ͷ������ʱ�(�����)��������
{
	char *item[MaxNoIdx];//�ʱ�(�ַ���)ָ������
	int last;//�ʵ�����
};

struct IdxTermType //��������
{
	HString key;//�ؼ���
	LinkList bnolist;//����������������
};

struct IdxListType
{
	IdxTermType item[MaxKeyNum+1];//��������������
	int last;//�ؼ��ʵĸ���
};

//һЩȫ�ֱ���
char buf[MaxLineLen+1];
WordListType wdlist,noidx;

//��������idxlistΪ�ձ�,����idxlist.item[0] ��һ�մ�
void initIdxList(IdxListType &idxlist)
{
	idxlist.last=0;
	initString(idxlist.item[0].key);
	//initList(idxlist.item[0].bnolist);
}

};

#endif