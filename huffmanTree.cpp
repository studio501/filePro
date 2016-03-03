
#include "stdafx.h"
#include "huffmanTree.h"

//返回i个结点中权值最小的树的根结点序号
int min(HuffmanTree t,int i)
{
	int j,flag;
	unsigned int k=UINT_MAX;
	for(j=1;j<=i;++j)
		if(t[j].weight<k&&t[j].parent==0)
			k=t[j].weight,flag=j;
	t[flag].parent=1;
	return flag;
}

//在i个结点中选择2个权值最小的树的根结点序号,s1为其中序号小的那个
void select(HuffmanTree t,int i,int &s1,int &s2)
{
	int j;
	s1=min(t,i);
	s2=min(t,i);
	if(s1>s2)
	{
		j=s1;
		s1=s2;
		s2=j;
	}
}

//构造huffman树
void huffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
{
	int m,i,s1,s2,start;
	unsigned c,f;
	HuffmanTree p;
	char *cd;
	if(n<=1) return ;
	m=2*n-1;
	HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));
	for(p=HT+1,i=1;i<=n;++i,++p,++w)
	{
		(*p).weight=*w;
		(*p).parent=0;
		(*p).lchild=0;
		(*p).rchild=0;
	}
	for(;i<=m;++i,++p) (*p).parent=0;
	for(i=n+1;i<=m;++i)
	{
		select(HT,i-1,s1,s2);
		HT[s1].parent=HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
	HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
	cd=(char*)malloc(n*sizeof(char));
	cd[n-1]='\0';
	for(i=1;i<=n;++i)
	{
		start=n-1;
		for(c=i,f=HT[i].parent;f!=0;f=HT[f].parent)
			if(HT[f].lchild==c)
				cd[--start]='0';
			else
				cd[--start]='1';
		HC[i]=(char *)malloc((n-start)*sizeof(char));
		strcpy(HC[i],&cd[start]);
	}
	free(cd);
}

//构造huffman树
void huffmanCoding1(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
{
	int m,i,s1,s2,start;
	unsigned c,f,cdlen;
	HuffmanTree p;
	char *cd;
	if(n<=1) return ;
	m=2*n-1;
	HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));
	for(p=HT+1,i=1;i<=n;++i,++p,++w)
	{
		(*p).weight=*w;
		(*p).parent=0;
		(*p).lchild=0;
		(*p).rchild=0;
	}
	for(;i<=m;++i,++p) (*p).parent=0;
	for(i=n+1;i<=m;++i)
	{
		select(HT,i-1,s1,s2);
		HT[s1].parent=HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
	HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
	cd=(char*)malloc(n*sizeof(char));
	c=m;
	cdlen=0;
	for(i=1;i<=m;++i) HT[i].weight=0;
	while(c)
	{
		if(HT[c].weight==0)
		{
			HT[c].weight=1;
			if(HT[c].lchild!=0)
			{
				c=HT[c].lchild;
				cd[cdlen++]='0';
			}
			else
			{
				HC[c]=(char *)malloc((cdlen+1)*sizeof(char));
				cd[cdlen]='\0';
				strcpy(HC[c],cd);
			}
		}
		else if(HT[c].weight==1)
		{
			HT[c].weight=2;
			if(HT[c].rchild!=0)
			{
				c=HT[c].rchild;
				cd[cdlen++]='1';
			}
		}
		else
		{
			HT[c].weight=0;
			c=HT[c].parent;
			--cdlen;
		}
	}
	free(cd);
}

//获取树数值
void getWeightArr(int * &w,int &len,int nLine,const char * hfile)
{
	ifstream fin(hfile,ios_base::in);
	int curLine=0,i=0,n=0,nc=0,t;
	char temp[MAX_LINE_SIZE];
	if(fin.is_open())
	{
		while(curLine<nLine)
		{
			fin.getline(temp,MAX_LINE_SIZE);
			++curLine;
		}
		while(temp[nc]!='\0')
		{
			if(temp[nc]==' ') ++i;
			++nc;
		}
		++i;
		n=i;
		len=n;
		w=(int*)malloc(n*sizeof(int));
		curLine=1;
		fin.clear();
		fin.seekg(ios_base::beg);
		i=0;
		while(curLine<nLine)
		{
			fin.getline(temp,MAX_LINE_SIZE);
			++curLine;
		}
		while(fin>>w[i++]);
		fin.close();
	}
}

void huffmanTreeMain()
{
	HuffmanTree HT,HT1;
	HuffmanCode HC,HC1;
	int *w=NULL,*w1=NULL,n,n1,i=0,temp;
	getWeightArr(w,n);
	getWeightArr(w1,n1,2);
	
	huffmanCoding(HT,HC,w,n);
	huffmanCoding1(HT1,HC1,w1,n1);
	for(i=1;i<=n;++i)
		cout<<HC[i]<<" ";
	cout<<endl;
	for(i=1;i<=n1;++i)
		cout<<HC1[i]<<" ";

	int a=100;
}