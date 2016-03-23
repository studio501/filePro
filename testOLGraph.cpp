
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
			p=(ArcBox *)malloc(sizeof(ArcNode));
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
void printGraph(ALGraph G)
{
	if(G.vexnum<=0) return;
	for(int i=0;i<G.vexnum;++i)
	{
		printf("%d->",i);
		ArcNode * p = G.vertices[i].firstarc;
		while(p!=NULL)
		{
			if(G.kind%2)
				printf("%d(%d)->",p->adjvex,*(p->info) );
			else printf("%d->",p->adjvex);
			
			
			p=p->next;
		}
		printf("NULL\n");
	}
}

//���ڱ�ͷ
bool listInsertFirstVex(ArcNode * &p,ArcNode *e,int pos)
{
	pos=1;
	e->next=p->next;
	p->next=e;
	return true;
}

//ɾ���������1�����
bool listDeleteFirstVex(ArcBox * &p,ArcBox &e,int pos)
{
	if(!p || pos<0 ) return false;

	pos = 1;
	int i=0;
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
ArcNode * listDeleteElem(ArcNode *p,ArcNode e)
{
	
	return NULL;
}

//�ڱ��������ҳ���e adjx��ͬ�Ľ��
ArcNode * point(ArcNode *p,ArcNode e,ArcNode * &p1)
{
	
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

//��ȡ����ı�������
int lengthOfAdjVex(ALGraph G,VertexType v)
{
	
	return 0;
}

//��ȡ����ı�������
int lengthOfAdjVex1(ALGraph G,int j)
{
	int i=0;
	if(j<0) return 0;
	ArcNode * p = G.vertices[j].firstarc;
	while(p)
	{
		p=p->next;
		++i;
	}
	return i;
}

//ɾ������
bool deleteVex(OLGraph &G,VertexType v)
{
	int i,j,k;
	ElemType e1,e2;
	ArcBox *p;
	ArcBox1 *p1,*p2;
	k=locateVex(G,v);
	if(k<0) return false;

	e1.headvex=k;
	for(j=0;j<G.vexnum;++j)
	{
		
	}
	return true;
}

//������
bool insertArc(ALGraph &G,VertexType v,VertexType w)
{
	
	return true;
}

//ɾ����
bool deleteArc(ALGraph &G,VertexType v,VertexType w)
{
	
	return true;
}

//�ӵ�v����������ݹ��������ȱ���ͼG
void DFS(ALGraph G,int v,visitFunc func)
{
	int w;
	visited[v]=true;
	func(G.vertices[v].data);
	for(w=firstAdjVex(G,G.vertices[v].data);w>=0;w=nextAdjVex(G,G.vertices[v].data,G.vertices[w].data))
		if(!visited[w])
			DFS(G,w,func);
}

//�ӵ�1��������������ȱ���ͼ����ÿ��������÷��ʺ���һ��
void DFSTraverse(ALGraph G,visitFunc func)
{
	int v;
	for(v=0;v<G.vexnum;++v)
		visited[v]=false;
	for(v=0;v<G.vexnum;++v)
		if(!visited[v])
			DFS(G,v,func);
	cout<<endl;
}

//�ӵ�v����������ݹ��������ȱ���ͼG
void DFS1(ALGraph G,int v,visitFunc func)
{
	ArcNode *p;
	visited[v]=true;
	func(G.vertices[v].data);
	for(p=G.vertices[v].firstarc;p;p=p->next)
		if(!visited[p->adjvex])
			DFS1(G,p->adjvex,func);
}

//�ӵ�1��������������ȱ���ͼ����ÿ��������÷��ʺ���һ��
void DFSTraverse1(ALGraph G,visitFunc func)
{
	int v;
	for(v=0;v<G.vexnum;++v)
		visited[v]=false;
	for(v=0;v<G.vexnum;++v)
		if(!visited[v])
			DFS1(G,v,func);
	cout<<endl;
}

//��������ȷǵݹ����ͼG
void BFSTraverse(ALGraph G,visitFunc func)
{
	int v,u,w;
	LinkQueue<QElemType> q;
	for(v=0;v<G.vexnum;++v)
		visited[v]=false;
	initQueue(q);
	for(v=0;v<G.vexnum;++v)
		if(!visited[v])
		{
			visited[v]=true;
			func(G.vertices[v].data);
			enQueue(q,v);
			while(!isQueueEmpty(q))
			{
				deQueue(q,u);
				for(w=firstAdjVex(G,G.vertices[u].data);w>=0;w=nextAdjVex(G,G.vertices[u].data,G.vertices[w].data))
					if(!visited[w])
					{
						visited[w]=true;
						func(G.vertices[w].data);
						enQueue(q,w);
					}
			}
		}
	cout<<endl;
}

//��������ȷǵݹ����ͼG
void BFSTraverse1(ALGraph G,visitFunc func)
{
	int v,u,w;
	ArcNode *p;
	LinkQueue<QElemType> q;
	for(v=0;v<G.vexnum;++v)
		visited[v]=false;
	initQueue(q);
	for(v=0;v<G.vexnum;++v)
		if(!visited[v])
		{
			visited[v]=true;
			func(G.vertices[v].data);
			enQueue(q,v);
			while(!isQueueEmpty(q))
			{
				deQueue(q,u);
				for(p=G.vertices[u].firstarc;p;p=p->next)
					if(!visited[p->adjvex])
					{
						visited[p->adjvex]=true;
						func(G.vertices[p->adjvex].data);
						enQueue(q,p->adjvex);
					}
			}
			
		}
		cout<<endl;
}

//����ڽӾ���洢�ṹ��ͼG
void display(MGraph G)
{
	int i,j;
	char s[7];
	switch(G.kind)
	{
	case DG:
		strcpy(s,"����ͼ");
		break;
	case DN:
		strcpy(s,"������");
		break;
	case UDG:
		strcpy(s,"����ͼ");
		break;
	case UDN:
		strcpy(s,"������");
	}
	printf("%d������%d���߻򻡵�%s������������: \n",G.vexnum,G.arcnum,s);
	for(i=0;i<G.vexnum;++i)
		cout<<G.vexs[i]<<" ";
	cout<<"\nG.arcs.adj:\n";
	for(i=0;i<G.vexnum;++i)
	{
		for(j=0;j<G.vexnum;++j)
			if(G.arcs[i][j].adj!=INFINITY)
			{
				printf("%11d",G.arcs[i][j].adj);
			}
			else printf("%11s","��");
			
		
			
		cout<<endl;
	}
	cout<<"G.arcs.info:\n";
	printf("����1(��β) ����2(��ͷ) �ñ߻򻡵���Ϣ��\n");
	for(i=0;i<G.vexnum;++i)
		if(G.kind<2)
		{
			for(j=0;j<G.vexnum;++j)
				if(G.arcs[i][j].info)
					printf("%5s %11s     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
		}
		else
			for(j=i+1;j<G.vexnum;++j)
				if(G.arcs[i][j].info)
					printf("%5s %11s     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);

}
};

void testOLGraphMain()
{
	using namespace OLG;
	OLGraph g;
	createGraph(g);
	destroyGraph(g);
	int a=100;
}