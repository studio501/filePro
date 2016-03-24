
#include "stdafx.h"

#include "testAMLGraph.h"
#include "queueTest.h"

namespace AMLG{
typedef int QElemType;
//ȫ�ַ��ʱ�־
bool visitedArr[MAX_VERTEXT_NUM];

//���ʺ���
void visit(VertexType i)
{
	cout<<i<<" ";
}

//����G�ж���u��λ��
int locateVex(AMLGraph G,VertexType u)
{
	int i;
	for(i=0;i<G.vexnum;++i)
		if(strcmp(u,G.adjmulist[i].data)==0) return i;
	return -1;
}

//����ͼ(ֻ�������)
void createGraph(AMLGraph &G)
{
	int i,j,k;
	int IncInfo;
	EBox *p;
	VertexType v1,v2;
	printf("����������ͼ�Ķ�����,����,�Ƿ�Ϊ��Ȩͼ(��:1����:0): \n");
	cin>>IncInfo;
	IncInfo = IncInfo?1:0;
	char filename[24];
	sprintf(filename,"GData6_%d.txt",IncInfo);
	ifstream fin(filename,ios_base::in);
	if(fin.is_open())
	{
		fin>>G.vexnum>>G.edgenum;
		for(i=0;i<G.vexnum;++i)
		{
			fin>>G.adjmulist[i].data;
			G.adjmulist[i].firstedg=NULL;
		}

		for(k=0;k<G.edgenum;++k)
		{
			fin>>v1>>v2;
			i=locateVex(G,v1);
			j=locateVex(G,v2);
			p=(EBox *)malloc(sizeof(EBox));
			p->mark=unvisited;
			p->ivex=i;
			p->ilink=G.adjmulist[i].firstedg;
			G.adjmulist[i].firstedg=p;
			p->jvex=j;
			p->jlink=G.adjmulist[j].firstedg;
			G.adjmulist[j].firstedg=p;
	
			if(IncInfo)
			{
				p->info=(InfoType*)malloc(sizeof(InfoType));
				fin>>(*p->info);
			}
			else p->info=NULL;
		}
	}
}

//�ñߵķ��ʱ��Ϊδ����
void markUnvizited(AMLGraph G)
{
	int i;
	EBox *p;
	for(i=0;i<G.vexnum;++i)
	{
		p=G.adjmulist[i].firstedg;
		while(p)
		{
			p->mark=unvisited;
			if(p->ivex==i) p=p->ilink;
			else p=p->jlink;
		}
	}
}

//��ӡͼ
void printGraph(AMLGraph G)
{
	int i;
	EBox *p=NULL;
	markUnvizited(G);
	printf("%d�����㣺\n",G.vexnum);
	for(i=0;i<G.vexnum;++i)
		printf("%s ",G.adjmulist[i].data);
	printf("\n%d����:\n",G.edgenum);
	for(i=0;i<G.vexnum;++i)
	{
		p=G.adjmulist[i].firstedg;
		while(p)
			if(p->ivex==i)
			{
				if(!p->mark)
				{
					printf("%s��%s ",G.adjmulist[i].data,G.adjmulist[p->jvex].data);
					p->mark=visited;
					if(p->info) printf("Ȩֵ: %d ",*p->info);
				}
				p=p->ilink;
			}
			else
			{
				if(!p->mark)
				{
					printf("%s��%s ",G.adjmulist[p->ivex].data,G.adjmulist[i].data);
					p->mark=visited;
					if(p->info) printf("Ȩֵ: %d ",*p->info);
				}
				p=p->jlink;
			}
		cout<<endl;
	}
}


//ɾ���������1�����
bool listDeleteFirstVex(ArcBox * &p,ArcBox &e,int pos)
{
	if(!p || pos<0 ) return false;

	pos=1;
	ArcBox *q = p;
	p = p->tlink;
	e=*q;
	return true;
}

//��λ�����е�Ԫ��e
int listLocateElem(ArcBox *p,ElemType e)
{
	while(p)
	{
		if(p->data.headvex == e.headvex) return true;
		else p=p->tlink;
	}
	return false;
}

//ɾ��ĳ�����
ArcBox * listDeleteElem(ArcBox * p,ArcBox e)
{
	ArcBox *q = p,*t=p;
	while(q)
	{
		if(equalvex((*q).data,e.data))
		{
			t->tlink=q->tlink;
			return q;
		}
		else
		{
			t=q;
			q=q->tlink;
		}
	}
	return NULL;
}

//����ͼ
void destroyGraph(AMLGraph &G)
{
	int i;
	for(i=G.vexnum-1;i>=0;--i)
		deleteVex(G,G.adjmulist[i].data);
}

//���ض������v��ֵ
VertexType & getVex(AMLGraph G,int v)
{
	if(v>=G.vexnum||v<0) exit(0);
	return G.adjmulist[v].data;
}

//��v���¸�ֵ
bool putVex(AMLGraph &G,VertexType v,VertexType value)
{
	int i= locateVex(G,v);
	if(i<0) return false;
	strcpy(G.adjmulist[i].data,value);
	return true;
}

//����v�ĵ�һ���ڽӶ�������
int firstAdjVex(AMLGraph G,VertexType v)
{
	int i=locateVex(G,v);
	if(i<0) return -1;
	if(G.adjmulist[i].firstedg)
		if(G.adjmulist[i].firstedg->ivex==i)
			return G.adjmulist[i].firstedg->jvex;
		else
			return G.adjmulist[i].firstedg->ivex;
	else
		return -1;
}

//�������Ƿ����
bool equalvex(ElemType a,ElemType b)
{
	if(a.headvex==b.headvex) return true;
	return false;
}

//����v�������w����һ���ڽӶ������,��w�����һ���ڽӶ��㷵��-1
int nextAdjVex(AMLGraph G,VertexType v,VertexType w)
{
	int i,j;
	EBox *p;
	i=locateVex(G,v);
	j=locateVex(G,w);
	if(i<0||j<0) return -1;
	p=G.adjmulist[i].firstedg;
	while(p)
		if(p->ivex==i&&p->jvex!=j)
			p=p->ilink;
		else if(p->jvex==i&&p->ivex!=j)
			p=p->jlink;
		else
			break;
	if(p&&p->ivex==i&&p->jvex==j)
	{
		p=p->ilink;
		if(p&&p->ivex==i) return p->jvex;
		else if(p&&p->jvex==i) return p->ivex;
	}

	if(p&&p->ivex==j&&p->jvex==i)
	{
		p=p->jlink;
		if(p&&p->ivex==i) return p->jvex;
		else if(p&&p->jvex==i) return p->ivex;
	}
	return -1;
}

//��������v(����������صĻ�)
void insertVex(AMLGraph &G,VertexType v)
{
	strcpy(G.adjmulist[G.vexnum].data,v);
	G.adjmulist[G.vexnum++].firstedg=NULL;
}


//ɾ������
bool deleteVex(AMLGraph &G,VertexType v)
{
	int i,j;
	EBox *p;
	i=locateVex(G,v);
	if(i<0) return false;
	for(j=0;j<G.vexnum;++j) deleteArc(G,v,G.adjmulist[j].data);
	for(j=i+1;j<G.vexnum;++j) G.adjmulist[j-1]=G.adjmulist[j];
	--G.vexnum;
	for(j=i;j<G.vexnum;++j)
	{
		p=G.adjmulist[j].firstedg;
		if(p)
			if(p->ivex==j+1)
			{
				--p->ivex;
				p=p->ilink;
			}
			else
			{
				--p->jvex;
				p=p->jlink;
			}
	}
	return true;
}

//������
bool insertArc(AMLGraph &G,VertexType v,VertexType w)
{
	int i,j,IncInfo;
	EBox *p;
	i=locateVex(G,v);
	j=locateVex(G,w);
	if(i<0||j<0||i==j) return false;
	p=(EBox*)malloc(sizeof(EBox));
	p->mark=unvisited;
	p->ivex=i;
	p->ilink=G.adjmulist[i].firstedg;
	G.adjmulist[i].firstedg=p;
	p->jvex=j;
	p->jlink=G.adjmulist[j].firstedg;
	G.adjmulist[j].firstedg=p;
	printf("�ñ��Ƿ���Ȩֵ(1:��0:��): \n");
	cin>>IncInfo;
	if(IncInfo)
	{
		p->info=(InfoType*)malloc(sizeof(InfoType));
		printf("������ñߵ�Ȩֵ: \n");
		cin>>*(p->info);
	}
	else
		p->info=NULL;
	++G.edgenum;
	return true;
}

//ɾ����
bool deleteArc(AMLGraph &G,VertexType v,VertexType w)
{
	int i,j;
	EBox *p=NULL,*q=NULL;
	i=locateVex(G,v);
	j=locateVex(G,w);
	if(i<0||j<0||i==j) return false;
	p=G.adjmulist[i].firstedg;
	if(p&&p->jvex==j) G.adjmulist[i].firstedg=p->ilink;
	else if(p&&p->ivex==j) G.adjmulist[i].firstedg=p->jlink;
	else
	{
		while(p)
			if(p->ivex==i&&p->jvex!=j)
			{
				q=p;
				p=p->ilink;
			}
			else if(p->jvex==i&&p->ivex!=j)
			{
				q=p;
				p=p->jlink;
			}
			else break;
		if(!p) return false;
		if(p->ivex==i&&p->jvex==j)
			if(q->ivex==i) q->ilink=p->ilink;
			else q->jlink=p->ilink;
		else if(p->ivex==j&&p->jvex==i)
			if(q->ivex==i) q->ilink=p->jlink;
			else q->jlink=p->jlink;
	}
	p=G.adjmulist[j].firstedg;
	if(p->jvex==i) G.adjmulist[j].firstedg=p->ilink;
	else if(p->ivex==i) G.adjmulist[j].firstedg=p->jlink;
	else
	{
		while(p)
			if(p->ivex==j&&p->jvex!=i)
			{
				q=p;
				p=p->ilink;
			}
			else if(p->jvex==j&&p->ivex!=i)
			{
				q=p;
				p=p->jlink;
			}
			else break;
		if(p->ivex==i&&p->jvex==j)
			if(q->ivex==j)
				q->ilink=p->jlink;
			else
				q->jlink=p->jlink;
		else if(p->ivex==j&&p->jvex==i)
			if(q->ivex==j)
				q->ilink=p->ilink;
			else
				q->jlink=p->ilink;
	}
	if(p->info)
	{
		free(p->info);
		p->info=NULL;
	}
	free(p);
	p=NULL;
	--G.edgenum;
	return true;
}

//�ӵ�v����������ݹ��������ȱ���ͼG
void DFS(AMLGraph G,int v,visitFunc func)
{
	int j;
	EBox *p;
	func(G.adjmulist[v].data);
	visitedArr[v]=true;
	p=G.adjmulist[v].firstedg;
	while(p)
	{
		j=p->ivex==v?p->jvex:p->ivex;
		if(!visitedArr[j]) DFS(G,j,func);
		p=p->ivex==v?p->ilink:p->jlink;
	}
}

//�ӵ�1��������������ȱ���ͼ����ÿ��������÷��ʺ���һ��
void DFSTraverse(AMLGraph G,visitFunc func)
{
	int v;
	for(v=0;v<G.vexnum;++v)
		visitedArr[v]=false;
	for(v=0;v<G.vexnum;++v)
		if(!visitedArr[v]) DFS(G,v,func);
	cout<<endl;
}

//��������ȷǵݹ����ͼG
void BFSTraverse(AMLGraph G,visitFunc func)
{
	int v,u,w;
	LinkQueue<QElemType> q;
	for(v=0;v<G.vexnum;++v)
		visitedArr[v]=false;
	initQueue(q);
	for(v=0;v<G.vexnum;++v)
		if(!visitedArr[v])
		{
			visitedArr[v]=true;
			func(G.adjmulist[v].data);
			enQueue(q,v);
			while(!isQueueEmpty(q))
			{
				deQueue(q,u);
				for(w=firstAdjVex(G,G.adjmulist[u].data);w>=0;w=nextAdjVex(G,G.adjmulist[u].data,G.adjmulist[w].data))
					if(!visitedArr[w])
					{
						visitedArr[w]=true;
						func(G.adjmulist[w].data);
						enQueue(q,w);
					}
			}
		}
	cout<<endl;
}

};

void testAMLGraphMain()
{
	using namespace AMLG;
	AMLGraph g;
	createGraph(g);
	printGraph(g);
	cout<<g.adjmulist[firstAdjVex(g,"v1")].data<<endl;
	cout<<g.adjmulist[nextAdjVex(g,"v1","v4")].data<<"\n========\n";
	//deleteVex(g,"v1");
	//printGraph(g);
	insertArc(g,"v2","v3");
	cout<<endl;
	printGraph(g);
	DFSTraverse(g,visit);
	BFSTraverse(g,visit);
	destroyGraph(g);
	int a=100;
}