#ifndef __HSTRINGTEST_HH_
#define __HSTRINGTEST_HH_

#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>
using namespace std;

#include "testLinkList.h"
using namespace LL;
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


///////////////////////////串操作应用举例
#define MAX_FILE_ROW_LEN 25
#define MAX_LINE_COL_LEN 75
#define FILE_NAME_LEN 20

HString T[MAX_FILE_ROW_LEN];
char str[MAX_LINE_COL_LEN],filename[FILE_NAME_LEN]="";
int nLine=0;

inline void eatline(){while(cin.get()!='\n') continue;}
inline void eatlineFromFile(ifstream &fin){while(fin.get()!='\n') continue;}

//打开文件(新或旧)
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

//显示文本内容
void List()
{
	for(int i=0;i<nLine;++i)
	{
		cout<<i+1<<" : ";
		strPrint(T[i]);
	}
}

//插入行
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

//删除行
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

//拷贝行
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

//修改行
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

//查找字符串
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

//替换字符串
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

//存盘
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



typedef int ElemType;
#define MaxKeyNum 25
#define MaxLineLen 52
#define MaxNoIdx 10

struct WordListType //一个书目的词表(顺序表)和非索引词表(有序表)共用类型
{
	char *item[MaxNoIdx];//词表(字符串)指针数组
	int last;//词的数量
};

struct IdxTermType //索引类型
{
	HString key;//关键词
	RLinkList bnolist;//存放书号索引的链表
};

struct IdxListType
{
	IdxTermType item[MaxKeyNum+1];//索引项数组类型
	int last;//关键词的个数
};

#define MaxBookNum 10

struct BookTermType //书目项类型
{
	char bookname[MaxLineLen+1];//书名串
	int bookno;//书号
};

struct BookListType//书目表类型
{
	BookTermType item[MaxBookNum];
	int last;//书目数量
};

//一些全局变量
char buf[MaxLineLen+1];
WordListType wdlist,noidx;
const char *idxFile="NoIdx.txt";
const char *bookIdxFile="BookIdx.txt";
const char *bookInfoFile="BookInfo.txt";

//置索引表idxlist为空表,且在idxlist.item[0] 设一空串
void initIdxList(IdxListType &idxlist)
{
	idxlist.last=0;
	initString(idxlist.item[0].key);
	initList_RL(idxlist.item[0].bnolist);
}

//从buf中提取书名关键字到wdlist,书号存入BookNo
void ExtractKeyWord(int &BookNo)
{
	int i,l,f=1;
	char *s1,*s2;
	for(i=1;i<=wdlist.last;++i)
	{
		free(wdlist.item[i]);
		wdlist.item[i]=NULL;
	}
	wdlist.last=0;
	BookNo=atoi(buf);
	s1=&buf[4];
	while(f)
	{
		s2=strchr(s1,' ');
		if(!s2)
		{
			s2=strchr(s1,'\0');
			f=0;
		}
		l=s2-s1;
		if(s1[0]>='A' &&s1[0]<='Z')
		{
			wdlist.item[wdlist.last]=(char *)malloc((l+1)*sizeof(char));
			for(i=0;i<l;++i)
				wdlist.item[wdlist.last][i]=s1[i];
			wdlist.item[wdlist.last][l]='\0';
			for(i=0;i<noidx.last&&(l=strcmp(wdlist.item[wdlist.last],noidx.item[i]))>0;++i);
			if(!l)
			{
				free(wdlist.item[wdlist.last]);
				wdlist.item[wdlist.last]=NULL;
			}
			else
				++wdlist.last;
		}
		s1=s2+1;
	}
}

//用wd返回词表wdlist中第i个关键词
void GetWord(int i,HString &wd)
{
	strAssign(wd,wdlist.item[i]);
}

//在索引表idxlist中查询是否存在与wd相等的关键词,若存在 返回其在索引表中的位置
int Locate(IdxListType &idxlist,HString wd,bool &b)
{
	int i,m;
	for(i=idxlist.last;(m=strCompare(idxlist.item[i].key,wd))>0;--i);
	if(m==0)
	{
		b=true;
		return i;
	}
	else
	{
		b=false;
		return i+1;
	}
}

//在索引表idxlist的第i项上插入关键词wd,并初始化书号索引的链表为空表
void InsertNewKey(IdxListType &idxlist,int i,HString wd)
{
	int j;
	for(j=idxlist.last;j>=i;--j)
		idxlist.item[j+1]=idxlist.item[j];
	initString(idxlist.item[i].key);
	strCopy(idxlist.item[i].key,wd);
	initList_RL(idxlist.item[i].bnolist);
	++idxlist.last;
}

//在索引表idxlist的第i项中插入书号bno的索引
void InsertBook(IdxListType &idxlist,int i,int bno)
{
	Link p;
	makeNode(p,bno);
	p->next=NULL;
	appenList(idxlist.item[i].bnolist,p);
}

//将书号为bno的关键词插入索引表
void InsIdxList(IdxListType &idxlist,int bno)
{
	int i,j;
	bool b;
	HString wd;
	initString(wd);
	for(i=0;i<wdlist.last;++i)
	{
		GetWord(i,wd);
		j=Locate(idxlist,wd,b);
		if(!b) InsertNewKey(idxlist,j,wd);
		InsertBook(idxlist,j,bno);
	}
}

//将生成的索引表idxlist输出到文件
void PutText(IdxListType idxlist)
{
	int i,j;
	Link p;
	ofstream fout(bookIdxFile,ios_base::out);
	if(fout.is_open())
	{
		fout<<idxlist.last<<endl;
		for(i=1;i<=idxlist.last;++i)
		{
			for(j=0;j<idxlist.item[i].key.length;++j)
			{
				fout<<idxlist.item[i].key.ch[j];
			}
			fout<<endl<<idxlist.item[i].bnolist.len<<endl;
			p=idxlist.item[i].bnolist.head;
			for(j=1;j<=idxlist.item[i].bnolist.len;++j)
			{
				p=p->next;
				fout<<p->data<<" ";
			}
			fout<<endl;
		}
	}
}




};

#endif