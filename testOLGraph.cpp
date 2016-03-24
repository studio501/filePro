
#include "stdafx.h"

#include "testOLGraph.h"
#include "queueTest.h"

namespace OLG{
typedef int QElemType;
//ȫ�ַ��ʱ�־
bool visited[MAX_VERTEXT_NUM];

//���ʺ���
void visit(VertexType i)
{
	cout<<i<<" ";
}

//����G�ж���u��λ��
int locateVex(OLGraph G,VertexType u)
{
	int i;
	for(i=0;i<G.vexnum;++i)
		if(strcmp(u,G.xlist[i].data)==0) return i;
	return -1;
}

//����ͼ(ֻ�������)
void createGraph(OLGraph &G)
{
	int i,j,k;
	int IncInfo;
	ArcBox *p;
	VertexType v1,v2;
	printf("����������ͼ�Ķ�����,����,�Ƿ�Ϊ��Ȩͼ(��:1����:0): \n");
	cin>>IncInfo;
	IncInfo = IncInfo?1:0;
	char filename[24];
	sprintf(filename,"GData6_%d.txt",IncInfo);
	ifstream fin(filename,ios_base::in);
	if(fin.is_open())
	{
		fin>>G.vexnum>>G.arcnum;
		for(i=0;i<G.vexnum;++i)
		{
			fin>>G.xlist[i].data;
			G.xlist[i].firstin=NULL;
			G.xlist[i].firstout=NULL;
		}

		for(k=0;k<G.arcnum;++k)
		{
			fin>>v1>>v2;
			i=locateVex(G,v1);
			j=locateVex(G,v2);
			p=(ArcBox *)malloc(sizeof(ArcBox));
			p->data.tailvex=i;
			p->data.headvex=j;
			p->data.hlink=G.xlist[j].firstin;
			p->tlink=G.xlist[i].firstout;
			G.xlist[j].firstin=(ArcBox1 *)p;
			G.xlist[i].firstout=p;
			if(IncInfo)
			{
				p->data.info=(InfoType*)malloc(sizeof(InfoType));
				fin>>(*p->data.info);
			}
			else p->data.info=NULL;
		}
	}
}

//��ӡͼ
void printGraph(OLGraph G)
{
	if(G.vexnum<=0) return;
	int i;
	ArcBox *p=NULL;
	printf("��%d������: \n",G.vexnum);
	for(i=0;i<G.vexnum;++i)
		printf("%s ",G.xlist[i].data);
	printf("\n%d����:\n",G.arcnum);
	for(i=0;i<G.vexnum;++i)
	{
		p=G.xlist[i].firstout;
		while(p)
		{
			printf("%s��%s ",G.xlist[i].data,G.xlist[p->data.headvex].data);
			if(p->data.info)
				printf("Ȩֵ: %d ",*p->data.info);
			p=p->tlink;
		}
		printf("\n");
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
void destroyGraph(OLGraph &G)
{
	int i;
	ArcBox e;
	for(i=0;i<G.vexnum;++i)
		while(G.xlist[i].firstout)
		{
			listDeleteFirstVex(G.xlist[i].firstout,e);
			if(e.data.info)
			{
				free(e.data.info);
				e.data.info=NULL;
			}
				
		}
	G.arcnum=0;
	G.vexnum=0;
}

//���ض������v��ֵ
VertexType & getVex(OLGraph G,int v)
{
	if(v>=G.vexnum||v<0) exit(0);
	return G.xlist[v].data;
}

//��v���¸�ֵ
bool putVex(OLGraph &G,VertexType v,VertexType value)
{
	int i= locateVex(G,v);
	if(i<0) return false;
	strcpy(G.xlist[i].data,value);
	return true;
}

//����v�ĵ�һ���ڽӶ�������
int firstAdjVex(OLGraph G,VertexType v)
{
	int i;
	ArcBox *p;
	i=locateVex(G,v);
	p=G.xlist[i].firstout;
	if(p) return p->data.headvex;
	else return -1;
}

//�������Ƿ����
bool equalvex(ElemType a,ElemType b)
{
	if(a.headvex==b.headvex) return true;
	return false;
}

//����v�������w����һ���ڽӶ������,��w�����һ���ڽӶ��㷵��-1
int nextAdjVex(OLGraph G,VertexType v,VertexType w)
{
	int i,j;
	ArcBox *p;
	i=locateVex(G,v);
	j=locateVex(G,w);
	p=G.xlist[i].firstout;
	while(p&&p->data.headvex!=j) p = p->tlink;
	if(p) p= p->tlink;//w����v�����һ���ڽӵ�
	if(p) return p->data.headvex;//����һ���ڽӵ�
	else return -1;
}

//��������v(����������صĻ�)
void insertVex(OLGraph &G,VertexType v)
{
	strcpy(G.xlist[G.vexnum].data,v);
	G.xlist[G.vexnum].firstin=NULL;
	G.xlist[G.vexnum].firstout=NULL;
	++G.vexnum;
}


//ɾ������
bool deleteVex(OLGraph &G,VertexType v)
{
	int i,j,k;
	ElemType e1,e2;
	ArcBox *p;
	ArcBox1 *p1=NULL,*p2=NULL;
	k=locateVex(G,v);
	if(k<0) return false;

	ArcBox a1;
	a1.data.headvex = k;
	e1.headvex=k;
	for(j=0;j<G.vexnum;++j)//����v���뻡���������ĳ���
	{
		ArcBox * t = listDeleteElem(G.xlist[j].firstout,a1);
		if(t)
		{
			--G.arcnum;
			if(t->data.info)
			{
				free(t->data.info);
				t->data.info=NULL;
			}
		}
	}

	//ɾ������v�ĳ���
	for(j=0;j<G.vexnum;++j)
	{
		p1=G.xlist[j].firstin;
		while(p1&&p1->tialvex!=k)
		{
			p2=p1;
			p1=p1->hlink;
		}
		if(p1)
		{
			if(p1==G.xlist[j].firstin) G.xlist[j].firstin=p1->hlink;
			else p2->hlink=p1->hlink;
			if(p1->info)
			{
				free(p1->info);
				p1->info=NULL;
			}
				
			/*free(p1);
			p1=NULL;*/
			--G.arcnum;
		}
	}

	for(j=k+1;j<G.vexnum;++j)
		G.xlist[j-1]=G.xlist[j];
	--G.vexnum;
	for(j=0;j<G.vexnum;++j)
	{
		p=G.xlist[j].firstout;
		while(p)
		{
			if(p->data.tailvex>k)
				--p->data.tailvex;
			if(p->data.headvex>k)
				--p->data.headvex;
			p=p->tlink;
		}
	}
	return true;
}

//������
bool insertArc(OLGraph &G,VertexType v,VertexType w)
{
	int i,j;
	InfoType IncInfo;
	ArcBox *p=NULL;
	i=locateVex(G,v);
	j=locateVex(G,w);
	if(i<0||j<0) return false;
	p=(ArcBox*)malloc(sizeof(ArcBox));
	p->data.tailvex=i;
	p->data.headvex=j;
	p->data.hlink=G.xlist[j].firstin;
	p->tlink=G.xlist[i].firstout;
	G.xlist[j].firstin=(ArcBox1*)p;
	G.xlist[i].firstout=p;
	++G.arcnum;
	printf("Ҫ����Ļ��Ƿ��Ȩ(��: 1,��: 0): ");
	cin>>IncInfo;
	if(IncInfo)
	{
		p->data.info=(InfoType*)malloc(sizeof(InfoType));
		printf("������û���Ȩֵ: ");
		cin>>(*p->data.info);
	}
	else
		p->data.info=NULL;
	return true;
}

//ɾ����
bool deleteArc(OLGraph &G,VertexType v,VertexType w)
{
	int i,j,k;
	ElemType e;
	ArcBox1 *p1=NULL,*p2=NULL;
	i=locateVex(G,v);
	j=locateVex(G,w);
	if(i<0||j<0||i==j) return false;
	p1=G.xlist[j].firstin;
	while(p1&&p1->tialvex!=i)
	{
		p2=p1;
		p1=p1->hlink;
	}
	if(p1==G.xlist[j].firstin)
		G.xlist[j].firstin=p1->hlink;
	else
		p2->hlink=p1->hlink;
	e.headvex=j;
	ArcBox t;
	t.data.headvex=j;
	ArcBox *pt = listDeleteElem(G.xlist[i].firstout,t);
	if(pt)
	{
		if(pt->data.info)
		{
			free(pt->data.info);
			pt->data.info=NULL;
		}
		--G.arcnum;
	}

	return true;
}

//�ӵ�v����������ݹ��������ȱ���ͼG
void DFS(OLGraph G,int v,visitFunc func)
{
	ArcBox *p;
	visited[v]=true;
	func(G.xlist[v].data);
	p=G.xlist[v].firstout;
	while(p&&visited[p->data.headvex]) p=p->tlink;
	if(p&&!visited[p->data.headvex]) DFS(G,p->data.headvex,func);
}

//�ӵ�1��������������ȱ���ͼ����ÿ��������÷��ʺ���һ��
void DFSTraverse(OLGraph G,visitFunc func)
{
	int v;
	for(v=0;v<G.vexnum;++v) visited[v]=false;
	for(v=0;v<G.vexnum;++v)
		if(!visited[v]) DFS(G,v,func);
	cout<<endl;
}

//��������ȷǵݹ����ͼG
void BFSTraverse(OLGraph G,visitFunc func)
{
	int v,u,w;
	LinkQueue<QElemType> q;
	for(v=0;v<G.vexnum;++v) visited[v]=false;
	initQueue(q);
	for(v=0;v<G.vexnum;++v)
		if(!visited[v])
		{
			visited[v]=true;
			func(G.xlist[v].data);
			enQueue(q,v);
			while(!isQueueEmpty(q))
			{
				deQueue(q,u);
				for(w=firstAdjVex(G,G.xlist[u].data);w>=0;w=nextAdjVex(G,G.xlist[u].data,G.xlist[w].data))
					if(!visited[w])
					{
						visited[w]=true;
						func(G.xlist[w].data);
						enQueue(q,w);
					}
			}
		}
	cout<<endl;
}

};

void testOLGraphMain()
{
	using namespace OLG;
	OLGraph g;
	createGraph(g);
	printGraph(g);
	cout<<g.xlist[firstAdjVex(g,"v1")].data<<endl;
	cout<<g.xlist[nextAdjVex(g,"v1","v4")].data<<"\n========\n";
	//deleteVex(g,"v1");
	//printGraph(g);
	//insertArc(g,"v2","v3");
	//cout<<endl;
	//printGraph(g);
	DFSTraverse(g,visit);
	BFSTraverse(g,visit);
	destroyGraph(g);
	int a=100;
}