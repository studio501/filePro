
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
	ElemType e;
	cout<<"请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3):\n";
	cin>>G.kind;
	cout<<"请输入图的顶点数,边数:\n";
	cin>>G.vexnum>>G.arcnum;
	printf("请输入%d个顶点的值(<%d个字符):\n",G.vexnum,MAX_NAME);
	for(i=0;i<G.vexnum;++i)
	{
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc=NULL;
	}
	if(G.kind%2)//net
		printf("请输入每条弧(边)的权值、弧尾和弧头(以空格作为间隔):\n");
	else//graph
		printf("请输入每条弧(边)的弧尾和弧头(以空格作为间隔):\n");
	for(k=0;k<G.arcnum;++k)//
	{
		if(G.kind%2)
			cin>>w>>va>>vb;
		else
			cin>>va>>vb;
		i=locateVex(G,va);
		j=locateVex(G,vb);
		e.info=NULL;
		e.adjvex=j;
		if(G.kind%2)
		{
			e.info=(int *)malloc(sizeof(int));
			*(e.info)=w;
		}
	}
}

//销毁图
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

//返回顶点序号v的值
VertexType & getVex(MGraph G,int v)
{
	if(v>=G.vexnum||v<0) exit(0);
	return G.vexs[v];
}

//对v重新赋值
bool putVex(MGraph &G,VertexType v,VertexType value)
{
	
	return true;
}

//返回v的第一个邻接顶点的序号
int firstAdjVex(MGraph G,VertexType v)
{
	
	return -1;
}

//返回v的相对于w的下一个邻接顶面序号,若w是最后一个邻接顶点返回-1
int nextAdjVex(MGraph G,VertexType v,VertexType w)
{
	
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
	int w;
	visited[v]=true;
	func(G.vexs[v]);
	for(w=firstAdjVex(G,G.vexs[v]);w>=0;w=nextAdjVex(G,G.vexs[v],G.vexs[w]))
		if(!visited[w])
			DFS(G,w,func);
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
	

}