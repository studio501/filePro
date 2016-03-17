
#include "stdafx.h"

#include "testALGraph.h"
#include "queueTest.h"

namespace ALG{
typedef VRType QElemType;
//ȫ�ַ��ʱ�־
bool visited[MAX_VERTEXT_NUM];

//���ʺ���
void visit(VertexType i)
{
	cout<<i<<" ";
}

//����G�ж���u��λ��
int locateVex(ALGraph G,VertexType u)
{
	int i;
	for(i=0;i<G.vexnum;++i)
		if(strcmp(u,G.vertices[i].data)==0) return i;
	return -1;
}

//����ͼ
void createGraph(ALGraph &G)
{
	int i,j,k,w;
	VertexType va,vb;
	ArcNode *e;

	cout<<"������ͼ������(����ͼ:0,������:1,����ͼ:2,������:3):\n";
	cin>>G.kind;

	char filename[24];
	sprintf(filename,"GData6_%d.txt",G.kind);
	ifstream fin(filename,ios_base::in);
	if(fin.is_open())
	{
		
		fin>>G.vexnum>>G.arcnum;
		for(i=0;i<G.vexnum;++i)
		{
			fin>>G.vertices[i].data;
			G.vertices[i].firstarc=NULL;
		}
		
		ArcNode * t = NULL;
		for(k=0;k<G.arcnum;++k)//
		{
			if(G.kind%2)
				fin>>va>>vb>>w;
			else
				fin>>va>>vb;
			i=locateVex(G,va);
			j=locateVex(G,vb);
			e=(ArcNode *)malloc(sizeof(ArcNode));
			e->info=NULL;
			e->adjvex=j;
			if(G.kind%2)
			{
				e->info=(int *)malloc(sizeof(int));
				*(e->info)=w;
			}
			e->next=G.vertices[i].firstarc;
			G.vertices[i].firstarc=e;

			t=e;

			e=(ArcNode*)malloc(sizeof(ArcNode));
			e->info=NULL;
			e->adjvex=i;
			if(G.kind%2)
			{
				e->info=t->info;
			}
			e->next=G.vertices[j].firstarc;
			G.vertices[j].firstarc=e;
		}
		fin.close();
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

//����ͼ
void destroyGraph(MGraph &G)
{
	int i,j,k=0;
	if(G.kind%2)
		k=INFINITY;
	for(i=0;i<G.vexnum;++i)
		if(G.kind<2)
		{
			for(j=0;j<G.vexnum;++j)
				if(G.arcs[i][j].adj!=k)
					if(G.arcs[i][j].info)
					{
						free(G.arcs[i][j].info);
						G.arcs[i][j].info=NULL;
					}
		}
		else
		{
			for(j=i+1;j<G.vexnum;++j)
				if(G.arcs[i][j].adj!=k)
					if(G.arcs[i][j].info)
					{
						free(G.arcs[i][j].info);
						G.arcs[i][j].info=G.arcs[j][i].info=NULL;
					}
		}
	G.vexnum=0;
	G.arcnum=0;
}

//���ض������v��ֵ
VertexType & getVex(MGraph G,int v)
{
	if(v>=G.vexnum||v<0) exit(0);
	return G.vexs[v];
}

//��v���¸�ֵ
bool putVex(MGraph &G,VertexType v,VertexType value)
{
	
	return true;
}

//����v�ĵ�һ���ڽӶ�������
int firstAdjVex(MGraph G,VertexType v)
{
	
	return -1;
}

//����v�������w����һ���ڽӶ������,��w�����һ���ڽӶ��㷵��-1
int nextAdjVex(MGraph G,VertexType v,VertexType w)
{
	
	return -1;
}

//��������v(����������صĻ�)
void insertVex(MGraph &G,VertexType v)
{
	int i,j=0;
	if(G.kind%2)
		j=INFINITY;
	strcpy(G.vexs[G.vexnum],v);
	for(i=0;i<=G.vexnum;++i)
	{
		G.arcs[G.vexnum][i].adj= G.arcs[i][G.vexnum].adj=j;
		G.arcs[G.vexnum][i].info=G.arcs[i][G.vexnum].info=NULL;
	}
	++G.vexnum;
}

//ɾ������
bool deleteVex(MGraph &G,VertexType v)
{
	
	return true;
}

//������
bool insertArc(MGraph &G,VertexType v,VertexType w)
{
	
	return true;
}

//ɾ����
bool deleteArc(MGraph &G,VertexType v,VertexType w)
{
	
	return true;
}

//�ӵ�v����������ݹ��������ȱ���ͼG
void DFS(MGraph G,int v,visitFunc func)
{
	int w;
	visited[v]=true;
	func(G.vexs[v]);
	for(w=firstAdjVex(G,G.vexs[v]);w>=0;w=nextAdjVex(G,G.vexs[v],G.vexs[w]))
		if(!visited[w])
			DFS(G,w,func);
}

//�ӵ�1��������������ȱ���ͼ����ÿ��������÷��ʺ���һ��
void DFSTraverse(MGraph G,visitFunc func)
{
	int v;
	for(v=0;v<G.vexnum;++v)
		visited[v]=false;
	for(v=0;v<G.vexnum;++v)
		if(!visited[v])
			DFS(G,v,func);
	cout<<endl;
}

//��������ȷǵݹ����ͼG
void BFSTraverse(MGraph G,visitFunc func)
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
			func(G.vexs[v]);
			enQueue(q,v);
			while(!isQueueEmpty(q))
			{
				deQueue(q,u);
				for(w=firstAdjVex(G,G.vexs[u]);w>=0;w=nextAdjVex(G,G.vexs[u],G.vexs[w]))
					if(!visited[w])
					{
						visited[w]=true;
						func(G.vexs[w]);
						enQueue(q,w);
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

void testALGraphMain()
{
	using namespace ALG;
	ALGraph g;
	createGraph(g);
	printGraph(g);
}