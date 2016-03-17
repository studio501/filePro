
#include "stdafx.h"

#include "testALGraph.h"
#include "queueTest.h"

namespace ALG{
typedef VRType QElemType;
//全局访问标志
bool visited[MAX_VERTEXT_NUM];

//访问函数
void visit(VertexType i)
{
	cout<<i<<" ";
}

//返回G中顶点u的位置
int locateVex(ALGraph G,VertexType u)
{
	int i;
	for(i=0;i<G.vexnum;++i)
		if(strcmp(u,G.vertices[i].data)==0) return i;
	return -1;
}

//构造图
void createGraph(ALGraph &G)
{
	int i,j,k,w;
	VertexType va,vb;
	ArcNode *e;

	cout<<"请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3):\n";
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

//打印图
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

//销毁图
void destroyGraph(ALGraph &G)
{
	int i;
	ArcNode e;
	for(i=0;i<G.vexnum;++i)
	{
		ArcNode * p = G.vertices[i].firstarc;
		while(p)
		{
			ArcNode *q = p->next;
			if(G.kind%2)
			{
				if(p->adjvex>i)
				{
					free(p->info);
					p->info=NULL;
				}
			}
			free(p);
			p=q;
		}
		G.vertices[i].firstarc = NULL;
		strcpy(G.vertices[i].data,"");
	}
	G.arcnum=G.vexnum=0;
	G.kind=0;
}

//返回顶点序号v的值
VertexType & getVex(ALGraph G,int v)
{
	if(v>=G.vexnum||v<0) exit(0);
	return G.vertices[v].data;
}

//对v重新赋值
bool putVex(ALGraph &G,VertexType v,VertexType value)
{
	int i;
	i=locateVex(G,v);
	if(i>-1)
	{
		strcpy(G.vertices[i].data,value);
		return true;
	}
	return false;
}

//返回v的第一个邻接顶点的序号
int firstAdjVex(ALGraph G,VertexType v)
{
	if(G.vexnum<=0) return -1;
	ArcNode *p;
	int v1 = locateVex(G,v);
	p=G.vertices[v1].firstarc;
	if(p) return p->adjvex;
	return -1;
}

//两条弧是否相等
bool equalvex(ArcNode a,ArcNode b)
{
	if(a.adjvex==b.adjvex) return true;
	return false;
}

//返回v的相对于w的下一个邻接顶面序号,若w是最后一个邻接顶点返回-1
int nextAdjVex(ALGraph G,VertexType v,VertexType w)
{
	ArcNode e;
	int v1;
	v1=locateVex(G,v);
	e.adjvex = locateVex(G,w);

	ArcNode * p = G.vertices[v1].firstarc;
	while(p)
	{
		if(p->adjvex==e.adjvex) break;
		p=p->next;
	}
	if(p)
	{
		if(p->next)
		{
			return p->next->adjvex;
		}
	}

	return -1;
}

//新增顶点v(但不增加相关的弧)
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

//删除顶点
bool deleteVex(MGraph &G,VertexType v)
{
	
	return true;
}

//新增弧
bool insertArc(MGraph &G,VertexType v,VertexType w)
{
	
	return true;
}

//删除弧
bool deleteArc(MGraph &G,VertexType v,VertexType w)
{
	
	return true;
}

//从第v个顶点出发递归地深度优先遍历图G
void DFS(MGraph G,int v,visitFunc func)
{
	
}

//从第1个顶点起深度优先遍历图并对每个顶点调用访问函数一次
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

//按广度优先非递归遍历图G
void BFSTraverse(MGraph G,visitFunc func)
{
	
}

//输出邻接矩阵存储结构的图G
void display(MGraph G)
{
	int i,j;
	char s[7];
	switch(G.kind)
	{
	case DG:
		strcpy(s,"有向图");
		break;
	case DN:
		strcpy(s,"有向网");
		break;
	case UDG:
		strcpy(s,"无向图");
		break;
	case UDN:
		strcpy(s,"无向网");
	}
	printf("%d个顶点%d条边或弧的%s。顶点依次是: \n",G.vexnum,G.arcnum,s);
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
			else printf("%11s","∞");
			
		
			
		cout<<endl;
	}
	cout<<"G.arcs.info:\n";
	printf("顶点1(弧尾) 顶点2(弧头) 该边或弧的信息：\n");
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
	cout<<g.vertices[firstAdjVex(g,"v1")].data;
	cout<<g.vertices[nextAdjVex(g,"v1","v4")].data;
	destroyGraph(g);
}