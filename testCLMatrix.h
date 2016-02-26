#ifndef TEST_CLMATRIX__HH_
#define TEST_CLMATRIX__HH_
#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>
#include <stdarg.h>
#include "commonFunc.h"
using namespace std;

#define MAX_SM_SIZE 100
#define MAX_READ_CHAR 256
#define MAX_RC 6

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

template<class T>
struct OLNode
{
	int i,j;
	T e;
	OLNode *right,*down;
};

template<class T>
struct CrossList
{
	OLNode<T> **rhead,**chead;
	int mu,nu,tu;
};

//初始化十字链表
template<class T>
void initSMatrix(CrossList<T> &M)
{
	M.rhead=M.chead=NULL;
	M.mu=M.nu=M.tu=0;
};

//初始化十字链表头指针向量
template<class T>
void initSMatrixList(CrossList<T> &M)
{
	int i;
	if(!(M.rhead=(OLNode<T> **)malloc((MAX_RC+1)*sizeof(OLNode<T>*)))) exit(OVERFLOW);
	if(!(M.chead=(OLNode<T> **)malloc((MAX_RC+1)*sizeof(OLNode<T>*)))) exit(OVERFLOW);
	
	for(i=0;i<=MAX_RC;++i) 
	{
		M.rhead[i]=NULL;
		int a = 100;
	}
		
	for(i=1;i<=MAX_RC;++i) M.chead[i]=NULL;
}

//将p插入M
template<class T>
void insertAscend(CrossList<T> &M,OLNode<T> *p)
{
	OLNode<T> * q=M.rhead[p->i];
	if(!q||p->j<q->j)
	{
		p->right=M.rhead[p->j];
		M.rhead[p->i]=p;
	}
	else
	{
		while(q->right&&q->right->j<p->j) q=q->right;
		p->right=q->right;
		q->right=p;
	}
	q=M.chead[p->j];
	if(!q||p->i<q->i)
	{
		p->down=M.chead[p->j];
		M.chead[p->j]=p;
	}
	else
	{
		while(q->down&&q->down->i<p->i) q=q->down;
		p->down=q->down;
		q->down=p;
	}
	++M.tu;
}

//创建稀疏矩阵
template<class T>
bool createSMatrix(CrossList<T> &M,int nMatrix=1,const char *fileName="matrix.txt")
{
	OLNode<T> *p;
	int i,m,n;
	T e;
	if(M.rhead) destroySMatrix(M);
	initSMatrixList(M);

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
						p=(OLNode<T>*)malloc(sizeof(OLNode<T>));
						p->i=m;
						p->j=n;
						p->e=e;
						insertAscend(M,p);
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
	}
	return true;
}

//销毁稀疏矩阵
template<class T>
void destroySMatrix(CrossList<T> &M)
{
	int i;
	OLNode<T> *p,*q;
	for(i=1;i<=M.mu;++i)
	{
		p=*(M.rhead+i);
		while(p)
		{
			q=p;
			p=p->right;
			free(q);
		}
	}
	free(M.rhead);
	free(M.chead);
	initSMatrix(M);
}

//打印稀疏矩阵
template<class T>
void printSMatrix(CrossList<T> M)
{
	int j;
	OLNode<T> *p;
	printf("%d行%d列%d个非零.\n",M.mu,M.nu,M.tu);
	for(j=1;j<=M.nu;++j)
	{
		p=M.rhead[j];
		while(p)
		{
			cout<<p->i<<"行"<<p->j<<"列值为:"<<p->e<<endl;
			p=p->right;
		}
	}

}

//按矩阵形式输出M
template<class T>
void printSMatrix1(CrossList<T> M)
{
	cout<<endl;
	int i,j,k=1;
	OLNode<T> *p;
	
	for(i=1;i<=M.mu;++i)
	{
		p=M.rhead[i];
		for(j=1;j<=M.nu;++j)
			if(!p||p->j!=j)
				printf("%3d",0);
			else
			{
				printf("%3d",p->e);
				p=p->right;
			}
		printf("\n");
	}
}

//由稀疏矩阵M复制得到T
template<class T>
void copySMatrix(CrossList<T> M,CrossList<T> &m)
{
	int i;
	OLNode<T> *p,*q;
	if(m.rhead)
		destroySMatrix(m);
	m.mu=M.mu;
	m.nu=M.nu;
	initSMatrixList(m);
	for(i=1;i<=M.mu;++i)
	{
		p=M.rhead[i];
		while(p)
		{
			if(!(q=(OLNode<T>*)malloc(sizeof(OLNode<T>)))) exit(OVERFLOW);
			*q=*p;
			insertAscend(m,q);
			p=p->right;
		}
	}
}


//求稀疏矩阵的和
template<class T>
void addSMatrix(CrossList<T> M,CrossList<T> N,CrossList<T> &Q)
{
	int i;
	OLNode<T> *pq,*pm,*pn;
	if(M.mu!=N.mu||M.nu!=N.nu) exit(OVERFLOW);
	Q.mu=M.mu;
	Q.nu=M.nu;
	Q.tu=0;
	initSMatrixList(Q);
	for(i=1;i<=M.mu;++i)
	{
		pm=M.rhead[i];
		pn=N.rhead[i];
		while(pm&&pn)
		{
			pq=(OLNode<T> *)malloc(sizeof(OLNode<T>));
			switch (comp(pm->j,pn->j))
			{
			case -1:
				*pq=*pm;
				insertAscend(Q,pq);
				pm=pm->right;
				break;
			case 0:
				*pq=*pm;
				pq->e+=pn->e;
				if(pq->e!=0) insertAscend(Q,pq);
				else
					free(pq);
				pm=pm->right;
				pn=pn->right;
				break;
			case 1:
				*pq=*pn;
				insertAscend(Q,pq);
				pn=pn->right;
			default:
				break;
			}
		}

		while(pm)
		{
			pq=(OLNode<T> *)malloc(sizeof(OLNode<T>));
			*pq=*pm;
			insertAscend(Q,pq);
			pm=pm->right;
		}
		while(pn)
		{
			pq=(OLNode<T> *)malloc(sizeof(OLNode<T>));
			*pq=*pn;
			insertAscend(Q,pq);
			pn=pn->right;
		}
	}
	if(Q.tu==0) destroySMatrix(Q);
}

//求稀疏矩阵的差
template<class T>
bool subtSMatrix(CrossList<T> M,CrossList<T> N,CrossList<T> &Q)
{
	int i;
	OLNode<T> *pq,*pm,*pn;
	if(M.mu!=N.mu||M.nu!=N.nu) return false;
	Q.mu=M.mu;
	Q.nu=M.nu;
	Q.tu=0;
	initSMatrixList(Q);
	for(i=1;i<=M.mu;++i)
	{
		pm=M.rhead[i];
		pn=N.rhead[i];
		while(pm&&pn)
		{
			pq=(OLNode<T> *)malloc(sizeof(OLNode<T>));
			switch (comp(pm->j,pn->j))
			{
			case -1:
				*pq=*pm;
				insertAscend(Q,pq);
				pm=pm->right;
				break;
			case 0:
				*pq=*pm;
				pq->e-=pn->e;
				if(pq->e!=0) insertAscend(Q,pq);
				else
					free(pq);
				pm=pm->right;
				pn=pn->right;
				break;
			case 1:
				*pq=*pn;
				pq->e*=-1;
				insertAscend(Q,pq);
				pn=pn->right;
			default:
				break;
			}
		}

		while(pm)
		{
			pq=(OLNode<T> *)malloc(sizeof(OLNode<T>));
			*pq=*pm;
			insertAscend(Q,pq);
			pm=pm->right;
		}
		while(pn)
		{
			pq=(OLNode<T> *)malloc(sizeof(OLNode<T>));
			*pq=*pn;
			pq->e*=-1;
			insertAscend(Q,pq);
			pn=pn->right;
		}
	}
	if(Q.tu==0) destroySMatrix(Q);
	return true;
}

//求稀疏矩阵M的转置矩阵T
template<class T>
void transposeSMatrix(CrossList<T> M,CrossList<T> &N)
{
	int u,i;
	OLNode<T> **head,*p,*q,*r;
	copySMatrix(M,N);
	u=N.mu;
	N.mu=N.nu;
	N.nu=u;
	head=N.rhead;
	N.rhead=N.chead;
	N.chead=head;
	for(u=1;u<=N.mu;++u)
	{
		p=N.rhead[u];
		while(p)
		{
			q=p->down;
			i=p->i;
			p->i=p->j;
			p->j=i;
			r=p->down;
			p->down=p->right;
			p->right=r;
			p=q;
		}
	}
}


//求稀疏矩阵的乘积
template<class T>
bool multSMatrix(CrossList<T> M,CrossList<T> N,CrossList<T> &Q)
{
	int i,j,e;
	OLNode<T> *pq,*pm,*pn;
	initSMatrix(Q);
	Q.mu=M.mu;
	Q.nu=N.nu;
	Q.tu=0;
	initSMatrixList(Q);
	for(i=1;i<=Q.mu;++i)
		for(j=1;j<=Q.nu;++j)
		{
			pm=M.rhead[i];
			pn=N.chead[j];
			e=0;
			while(pm&&pn)
				switch (comp(pn->i,pm->j))
			{
				case -1:
					pn=pn->down;
					break;
				case 0:
					e+=pm->e*pn->e;
					pn=pn->down;
					pm=pm->right;
					break;
				case 1:
					pm=pm->right;
				default:
					break;
			}
			if(e)
			{
				pq=(OLNode<T> *)malloc(sizeof(OLNode<T>));
				if(!pq) exit(OVERFLOW);
				pq->i=i;
				pq->j=j;
				pq->e=e;
				insertAscend(Q,pq);
			}
		}
		if(Q.tu==0) destroySMatrix(Q);
		return true;
}

#endif