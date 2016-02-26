#ifndef TEST_RLSMATRIX__HH_
#define TEST_RLSMATRIX__HH_
#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>
#include <stdarg.h>
#include "commonFunc.h"
using namespace std;

#define MAX_SM_SIZE 100
#define MAX_READ_CHAR 256
#define MAX_RC 20

template<class T>
struct Triple
{
	int i,j;
	T e;
};

template<class T>
struct TSMatrix
{
	Triple<T> data[MAX_SM_SIZE+1];//data[0]未用
	int mu,nu,tu;
	int rpos[MAX_RC+1];//各行第一个非零元素的位置表
};

template<class T>
struct RLSMatrix
{
	Triple<T> data[MAX_SM_SIZE+1];
	int rpos[MAX_RC+1];
	int mu,nu,tu;
};

//创建稀疏矩阵
template<class T>
bool createSMatrix(RLSMatrix<T> &M,int nMatrix=1,const char *fileName="matrix.txt")
{
	int i,m,n,j;
	T e;
	bool k;
	char buf[MAX_READ_CHAR];
	int curMatrix=0;
	ifstream fin(fileName,ios_base::in);
	if(fin.is_open())
	{
		while(curMatrix < nMatrix)
		{
			fin.getline(buf,MAX_READ_CHAR);
			if(buf[0]=='\0') ++curMatrix;

		}

		int t=0;
		m=1;
		string str;
		fin.getline(buf,MAX_READ_CHAR);
		while(buf[0])
		{
			i=n=0;
			while(buf[i])
			{
				if(buf[i]==' ')
				{
					e = stringToNum<T>(str);
					++n;
					if(e!=0)
					{
						++t;
						M.data[t].i=m;
						M.data[t].j=n;
						M.data[t].e=e;
					}
					str.clear();
				}
				else
				{
					str+=buf[i];
				}
				++i;
			}
			++m;
			fin.getline(buf,MAX_READ_CHAR);
		}
		M.mu=m-1;
		M.nu=n;
		M.tu=t;

		for(i=1;i<=M.mu;++i) M.rpos[i]=0;
		for(i=1;i<=M.tu;++i) ++M.rpos[M.data[i].i];
		for(i=M.mu;i>=1;--i)
		{
			M.rpos[i]=1;
			for(j=i-1;j>=1;--j)
				M.rpos[i]+=M.rpos[j];
		}
	}
	return true;
}

//销毁稀疏矩阵
template<class T>
void destroySMatrix(RLSMatrix<T> &M)
{
	M.mu=M.nu=M.tu=0;
}

//打印稀疏矩阵
template<class T>
void printSMatrix(RLSMatrix<T> M)
{
	int i;
	printf("%d行%d列%d个非零.\n",M.mu,M.nu,M.tu);
	printf("行  列  元素值\n");
	for(i=1;i<=M.tu;++i)
		printf("%2d%4d%8d\n",M.data[i].i,M.data[i].j,M.data[i].e);
	for(i=1;i<=M.mu;++i)
		printf("第%d行的第一个非零元素是本矩阵第%d个元素\n",i,M.rpos[i]);

}

//按矩阵形式输出M
template<class T>
void printSMatrix1(RLSMatrix<T> M)
{
	cout<<endl;
	int i,j,k=1;
	Triple<T> *p=M.data;
	++p;
	for(i=1;i<=M.mu;++i)
	{
		for(j=1;j<=M.nu;++j)
			if(k<=M.tu&&p->i==i&&p->j==j)
			{
				printf("%3d",p->e);
				++p;
				++k;
			}
			else
				printf("%3d",0);
		printf("\n");
	}
}

//由稀疏矩阵M复制得到T
template<class T>
void copySMatrix(RLSMatrix<T> M,RLSMatrix<T> &m)
{
	m=M;
}


//求稀疏矩阵的和
template<class T>
bool addSMatrix(RLSMatrix<T> M,RLSMatrix<T> N,RLSMatrix<T> &Q)
{
	int k,p,q,tm,tn;
	if(M.mu!=N.mu || M.nu!=N.nu) return false;
	Q.mu=M.mu;
	Q.nu=M.nu;
	Q.tu=0;
	for(k=1;k<=M.mu;++k)
	{
		Q.rpos[k]=Q.tu+1;
		p=M.rpos[k];
		q=N.rpos[k];
		if(k==M.mu)
		{
			tm=M.tu+1;
			tn=N.tu+1;
		}
		else
		{
			tm=M.rpos[k+1];
			tn=N.rpos[k+1];
		}
		while(p<tm&&q<tn)
			if(M.data[p].j==N.data[q].j)
			{
				if(M.data[p].e+N.data[q].e!=0)
				{
					Q.data[++Q.tu]=M.data[p];
					Q.data[Q.tu].e+=N.data[q].e;
				}
				++p;++q;
			}
			else if(M.data[p].j<N.data[q].j) Q.data[++Q.tu]=M.data[p++];
			else Q.data[++Q.tu]=N.data[q++];
		while(p<tm) Q.data[++Q.tu]=M.data[p++];
		while(q<tn) Q.data[++Q.tu]=N.data[q++];
	}
	if(Q.tu>MAX_SM_SIZE)
		return false;
	else
		return true;
}

//求稀疏矩阵的差
template<class T>
bool subtSMatrix(RLSMatrix<T> M,RLSMatrix<T> N,RLSMatrix<T> &Q)
{
	int i;
	for(i=1;i<N.tu;++i)
		N.data[i].e*=-1;
	return addSMatrix(M,N,Q);
}

//求稀疏矩阵M的转置矩阵T
template<class T>
void transposeSMatrix(RLSMatrix<T> M,RLSMatrix<T> &N)
{
	int p,q,t,col,*num;
	num=(int*)malloc((M.nu+1)*sizeof(int));
	N.mu=M.nu;
	N.nu=M.mu;
	N.tu=M.tu;
	if(N.tu)
	{
		for(col=1;col<=M.nu;++col) num[col]=0;
		for(t=1;t<=M.tu;++t) ++num[M.data[t].j];
		N.rpos[1]=1;
		for(col=2;col<=M.nu;++col) N.rpos[col]=N.rpos[col-1]+num[col-1];
		for(col=1;col<=M.nu;++col) num[col]=N.rpos[col];
		for(p=1;p<=M.tu;++p)
		{
			col=M.data[p].j;
			q=num[col];
			N.data[q].i=M.data[p].j;
			N.data[q].j=M.data[p].i;
			N.data[q].e=M.data[p].e;
			++num[col];
		}
	}
	free(num);
}


//求稀疏矩阵的乘积
template<class T>
bool multSMatrix(RLSMatrix<T> M,RLSMatrix<T> N,RLSMatrix<T> &Q)
{
	int arow,brow,p,q,ccol,ctemp[MAX_RC+1],t,tp;
	if(M.nu!=N.mu) return false;
	Q.mu=M.mu;
	Q.nu=N.nu;
	Q.tu=0;
	if(M.tu*N.tu==0) return false;
	for(arow=1;arow<=M.mu;++arow)
	{
		for(ccol=1;ccol<=Q.nu;++ccol)
			ctemp[ccol]=0;
		Q.rpos[arow]=Q.tu+1;
		if(arow<M.mu) tp=M.rpos[arow+1];
		else tp=M.tu+1;
		for(p=M.rpos[arow];p<tp;++p)
		{
			brow=M.data[p].j;
			if(brow<N.mu) t=N.rpos[brow+1];
			else t=N.tu+1;
			for(q=N.rpos[brow];q<t;++q)
			{
				ccol=N.data[q].j;
				ctemp[ccol]+=M.data[p].e*N.data[q].e;
			}
		}
		for(ccol=1;ccol<=Q.nu;++ccol)
			if(ctemp[ccol]!=0)
			{
				if(++Q.tu>MAX_SM_SIZE) return false;
				Q.data[Q.tu].i=arow;
				Q.data[Q.tu].j=ccol;
				Q.data[Q.tu].e=ctemp[ccol];
			}
	}
	return true;
}

#endif