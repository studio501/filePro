#ifndef TEST_ARRAY__HH_
#define TEST_ARRAY__HH_
#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>
#include <stdarg.h>
#include "commonFunc.h"
using namespace std;


#define MAX_ARRAY_DIM 8
template<class T>
struct Array
{
	T *base;
	int dim,*bounds,*constants;
};

//构造相应的数组
template<class T>
bool initArray(Array<T> &A,int dim,...)
{
	int elemtotal=1,i;
	va_list ap;
	if(dim<1||dim>MAX_ARRAY_DIM) return false;
	A.dim=dim;
	A.bounds=(int*)malloc(dim*sizeof(int));
	if(!A.bounds) exit(OVERFLOW);
	va_start(ap,dim);
	for(i=0;i<dim;++i)
	{
		A.bounds[i]=va_arg(ap,T);
		if(A.bounds[i]<0) return UNDERFLOW;
		elemtotal*=A.bounds[i];
	}
	va_end(ap);
	A.base=(T*)malloc(elemtotal*sizeof(T));
	if(!A.base) exit(OVERFLOW);
	A.constants=(int*)malloc(dim*sizeof(int));
	if(!A.constants) exit(OVERFLOW);
	A.constants[dim-1]=1;
	for(i=dim-2;i>=0;--i)
		A.constants[i]=A.bounds[i+1]*A.constants[i+1];
	return true;
}

//销毁数组
template<class T>
void destroyArray(Array<T> &A)
{
	if(A.base) free(A.base);
	if(A.bounds) free(A.bounds);
	if(A.constants) free(A.constants);
	A.base=A.bounds=A.constants=NULL;
	A.dim=0;
}

//求出元素在A中的相对地址
template<class T>
bool Locate(Array<T> A,va_list ap,int &off)
{
	int i,ind;
	off=0;
	for(i=0;i<A.dim;++i)
	{
		ind=va_arg(ap,int);
		if(ind<0||ind>=A.bounds[i])
			return false;
		off+=A.constants[i]*ind;
	}
	return true;
}

//取下标所对应的值
template<class T>
bool Value(T &e,Array<T> A,...)
{
	va_list ap;
	int off;
	va_start(ap,A);
	if(!Locate(A,ap,off)) return false;
	e=*(A.base+off);
	return true;
}

//为下标赋值
template<class T>
bool Assign(Array<T> A,T e,...)
{
	va_list ap;
	int off;
	va_start(ap,e);
	if(!Locate(A,ap,off)) return false;
	*(A.base+off)=e;
	return true;
}

//返回num个数中的最大值
template<class T>
T Max(int num,...)
{
	va_list ap;
	int i;
	T m,n;
	
	if(num<1) exit(0);
	va_start(ap,num);
	m=va_arg(ap,T);
	for(i=1;i<num;++i)
	{
		n=va_arg(ap,T);
		if(m<n)
			m=n;
	}
	va_end(ap);
	return m;
}

#define MAX_SM_SIZE 100
#define MAX_READ_CHAR 256

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
};

//创建稀疏矩阵
template<class T>
bool createSMatrix(TSMatrix<T> &M,int nMatrix=1,const char *fileName="matrix.txt")
{
	int i,m,n;
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
	}
	return true;
}

//销毁稀疏矩阵
template<class T>
void destroySMatrix(TSMatrix<T> &M)
{
	M.mu=M.nu=M.tu=0;
}

//打印稀疏矩阵
template<class T>
void printSMatrix(TSMatrix<T> M)
{
	int i;
	printf("%d行%d列%d个非零.\n",M.mu,M.nu,M.tu);
	printf("行  列  元素值\n");
	for(i=1;i<=M.tu;++i)
		printf("%2d%4d%8d\n",M.data[i].i,M.data[i].j,M.data[i].e);
}

//按矩阵形式输出M
template<class T>
void printSMatrix1(TSMatrix<T> M)
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
void copySMatrix(TSMatrix<T> M,TSMatrix<T> &m)
{
	m=M;
}


//求稀疏矩阵的和
template<class T>
bool addSMatrix(TSMatrix<T> M,TSMatrix<T> N,TSMatrix<T> &Q)
{
	int m=1,n=1,q=0;
	if(M.mu!=N.nu||M.nu!=N.nu) return false;
	Q.mu=M.mu;
	Q.nu=M.nu;
	while(m<=M.tu&&n<=N.tu)
	{
		switch(comp(M.data[m].i,N.data[n].i))
		{
		case -1:
			Q.data[++q]=M.data[m++];
			break;
		case 0:
			switch (comp(M.data[m].j,N.data[n].j))
			{
			case -1:
				Q.data[++q]=M.data[m++];
				break;
			case 0:
				Q.data[++q]=M.data[m++];
				Q.data[q].e+=N.data[n++].e;
				if(Q.data[q].e==0)
					--q;
				break;
			case 1:
				Q.data[++q]=N.data[n++];
			}
			break;
		case 1:
			Q.data[++q]=N.data[n++];
			break;
		}
	}

	while(m<=M.tu) Q.data[++q]=M.data[m++];
	while(n<=N.tu) Q.data[++q]=N.data[n++];
	Q.tu=q;
	if(q>MAX_SM_SIZE) return false;
	return true;
}

//求稀疏矩阵的差
template<class T>
bool subtSMatrix(TSMatrix<T> M,TSMatrix<T> N,TSMatrix<T> &Q)
{
	int i;
	for(i=1;i<N.tu;++i)
		N.data[i].e*=-1;
	return addSMatrix(M,N,Q);
}

//求稀疏矩阵M的转置矩阵T
template<class T>
void transposeSMatrix(TSMatrix<T> M,TSMatrix<T> &N)
{
	int p,q,col;
	N.mu=M.nu;
	N.nu=M.mu;
	N.tu=M.tu;
	if(N.tu)
	{
		q=1;
		for(col=1;col<=M.nu;++col)
			for(p=1;p<=M.tu;++p)
				if(M.data[p].j==col)
				{
					N.data[q].i=M.data[p].j;
					N.data[q].j=M.data[p].i;
					N.data[q].e=M.data[p].e;
					++q;
				}
	}
}

//求稀疏矩阵M的转置矩阵T
template<class T>
void fastTransposeSMatrix(TSMatrix<T> M,TSMatrix<T> &N)
{
	int p,q,t,col,*num,*cpot;
	num=(int *)malloc((M.nu+1)*sizeof(int));
	cpot=(int *)malloc((M.nu+1)*sizeof(int));
	N.mu=M.nu;
	N.nu=M.mu;
	N.tu=M.tu;
	if(N.tu)
	{
		for(col=1;col<=M.nu;++col) num[col]=0;
		for(t=1;t<=M.tu;++t) ++num[M.data[t].j];
		cpot[1]=1;
		for(col=2;col<=M.nu;++col) cpot[col]=cpot[col-1]+num[col-1];
		for(p=1;p<=M.tu;++p)
		{
			col=M.data[p].j;
			q=cpot[col];
			N.data[q].i=M.data[p].j;
			N.data[q].j=M.data[p].i;
			N.data[q].e=M.data[p].e;
			++cpot[col];
		}
	}
	free(num);
	free(cpot);
}

//求稀疏矩阵的乘积
template<class T>
bool multSMatrix(TSMatrix<T> M,TSMatrix<T> N,TSMatrix<T> &Q)
{
	int i,j;
	T *Nc,*Tc;
	TSMatrix<T> temp;
	if(M.nu!=N.mu) return false;
	temp.nu=M.mu;
	temp.mu=N.nu;
	temp.tu=0;
	Nc=(T*)malloc((N.mu+1)*sizeof(T));
	Tc=(T*)malloc((M.nu+1)*sizeof(T));
	if(!Nc||!Tc) exit(OVERFLOW);
	for(i=1;i<=N.nu;++i)
	{
		for(j=1;j<=N.mu;++j) Nc[j]=0;
		for(j=1;j<=M.mu;++j) Tc[j]=0;
		for(j=1;j<=N.tu;++j)
			if(N.data[j].j==i)
				Nc[N.data[j].i]=N.data[j].e;
		for(j=1;j<=M.tu;++j)
			Tc[M.data[j].i]+=M.data[j].e*Nc[M.data[j].j];
		for(j=1;j<=M.mu;++j)
			if(Tc[j]!=0)
			{
				temp.data[++temp.tu].e=Tc[j];
				temp.data[temp.tu].i=i;
				temp.data[temp.tu].j=j;
			}
	}
	if(temp.tu>MAX_SM_SIZE) return false;
	transposeSMatrix(temp,Q);
	destroySMatrix(temp);
	free(Tc);
	free(Nc);
	return true;
}

#endif