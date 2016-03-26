#include "stdafx.h"

#include "testArrGraph.h"
#include "queueTest.h"

using namespace AG;
namespace AG{
	typedef VRType QElemType;
	//全局访问标志
	bool visited[MAX_VERTEXT_NUM];

	//访问函数
	void visit(VertexType i)
	{
		cout<<i<<" ";
	}

	//返回G中顶点u的位置
	int locateVex(MGraph G,VertexType u)
	{
		int i;
		for(i=0;i<G.vexnum;++i)
			if(strcmp(u,G.vexs[i])==0) return i;
		return -1;
	}

	//采用数组(邻接矩阵)表示法 构造无向图
	void createFUDG(MGraph &G,const char *filename)
	{
		int i,j,k;
		VertexType va,vb;
		ifstream fin(filename,ios_base::in);
		if(fin.is_open())
		{
			fin>>G.vexnum;
			fin>>G.arcnum;
			for(i=0;i<G.vexnum;++i)
				fin>>G.vexs[i];
			for(i=0;i<G.vexnum;++i)
				for(j=0;j<G.vexnum;++j)
				{
					G.arcs[i][j].adj=0;
					G.arcs[i][j].info=NULL;
				}
				for(k=0;k<G.arcnum;++k)
				{
					fin>>va>>vb;
					i=locateVex(G,va);
					j=locateVex(G,vb);
					G.arcs[i][j].adj=G.arcs[j][i].adj=1;
				}
				fin.close();
				G.kind=UDG;
		}
	}

	//采用数组(邻接矩阵)表示法 构造无向网
	void createFUDN(MGraph &G,const char *filename)
	{
		int i,j,k,w;
		VertexType va,vb;
		ifstream fin(filename,ios_base::in);
		if(fin.is_open())
		{
			fin>>G.vexnum;
			fin>>G.arcnum;
			for(i=0;i<G.vexnum;++i)
				fin>>G.vexs[i];
			for(i=0;i<G.vexnum;++i)
				for(j=0;j<G.vexnum;++j)
				{
					G.arcs[i][j].adj=INFINITY;
					G.arcs[i][j].info=NULL;
				}
				for(k=0;k<G.arcnum;++k)
				{
					fin>>va>>vb>>w;
					i=locateVex(G,va);
					j=locateVex(G,vb);
					G.arcs[i][j].adj=G.arcs[j][i].adj=w;
				}
				fin.close();
				G.kind=UDN;
		}
	}

	//采用数组(邻接矩阵)表示法 构造有向图
	void createDG(MGraph &G,const char *filename)
	{
		int i,j,k,l,incInfo;
		VertexType va,vb;
		ifstream fin(filename,ios_base::in);
		if(fin.is_open())
		{
			fin>>G.vexnum>>G.arcnum>>incInfo;
			for(i=0;i<G.vexnum;++i)
				fin>>G.vexs[i];
			for(i=0;i<G.vexnum;++i)
				for(j=0;j<G.vexnum;++j)
				{
					G.arcs[i][j].adj=0;
					G.arcs[i][j].info=NULL;
				}
				for(k=0;k<G.arcnum;++k)
				{
					fin>>va>>vb;
					i=locateVex(G,va);
					j=locateVex(G,vb);
					G.arcs[i][j].adj=1;
					if(incInfo)
					{
						G.arcs[i][j].info=(InfoType *)malloc(sizeof(InfoType)*MAX_INFO);
						fin>>G.arcs[i][j].info;
					}
				}
				G.kind=DG;
		}
	}

	//采用数组(邻接矩阵)表示法 构造有向网
	void createDN(MGraph &G,const char *filename)
	{
		int i,j,k,w,incInfo;
		VertexType va,vb;
		ifstream fin(filename,ios_base::in);
		if(fin.is_open())
		{
			fin>>G.vexnum>>G.arcnum>>incInfo;
			for(i=0;i<G.vexnum;++i)
				fin>>G.vexs[i];
			for(i=0;i<G.vexnum;++i)
				for(j=0;j<G.vexnum;++j)
				{
					G.arcs[i][j].adj=INFINITY;
					G.arcs[i][j].info=NULL;
				}
				for(k=0;k<G.arcnum;++k)
				{
					fin>>va>>vb>>w;
					i=locateVex(G,va);
					j=locateVex(G,vb);
					G.arcs[i][j].adj=w;
					if(incInfo)
					{
						G.arcs[i][j].info=(InfoType *)malloc(sizeof(InfoType)*MAX_INFO);
						fin>>G.arcs[i][j].info;
					}
				}
				G.kind=DN;
		}
	}

	//采用数组(邻接矩阵)表示法 构造有向网
	void createUDG(MGraph &G,const char *filename)
	{
		int i,j,k,w,incInfo;
		VertexType va,vb;
		ifstream fin(filename,ios_base::in);
		if(fin.is_open())
		{
			fin>>G.vexnum>>G.arcnum>>incInfo;
			for(i=0;i<G.vexnum;++i)
				fin>>G.vexs[i];
			for(i=0;i<G.vexnum;++i)
				for(j=0;j<G.vexnum;++j)
				{
					G.arcs[i][j].adj=0;
					G.arcs[i][j].info=NULL;
				}
				for(k=0;k<G.arcnum;++k)
				{
					fin>>va>>vb;
					i=locateVex(G,va);
					j=locateVex(G,vb);
					G.arcs[i][j].adj=G.arcs[j][i].adj=1;
					if(incInfo)
					{
						G.arcs[i][j].info=(InfoType *)malloc(sizeof(InfoType)*MAX_INFO);
						fin>>G.arcs[i][j].info;
					}
				}
				G.kind=UDG;
		}
	}

	//采用数组(邻接矩阵)表示法 构造无向网
	void createUDN(MGraph &G,const char *filename)
	{
		int i,j,k,w,incInfo;
		VertexType va,vb;
		ifstream fin(filename,ios_base::in);
		if(fin.is_open())
		{
			fin>>G.vexnum>>G.arcnum>>incInfo;
			for(i=0;i<G.vexnum;++i)
				fin>>G.vexs[i];
			for(i=0;i<G.vexnum;++i)
				for(j=0;j<G.vexnum;++j)
				{
					G.arcs[i][j].adj=INFINITY;
					G.arcs[i][j].info=NULL;
				}
				for(k=0;k<G.arcnum;++k)
				{
					fin>>va>>vb>>w;
					i=locateVex(G,va);
					j=locateVex(G,vb);
					G.arcs[i][j].adj=G.arcs[j][i].adj=w;
					if(incInfo)
					{
						G.arcs[i][j].info=(InfoType *)malloc(sizeof(InfoType)*MAX_INFO);
						fin>>G.arcs[i][j].info;
					}
				}
				G.kind=UDN;
		}
	}

	//构造图
	void createGraph(MGraph &G)
	{
		cout<<"请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3)"<<endl;
		int a;
		cin>>a;
		G.kind=(GraphKind)a;
		switch(G.kind)
		{
		case DG:
			createDG(G);
			break;
		case DN:
			createDN(G);
			break;
		case UDG:
			createUDG(G);
			break;
		case UDN:
			createUDN(G);
			break;
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
		int k = locateVex(G,v);
		if(k<0) return false;
		strcpy(G.vexs[k],value);
		return true;
	}

	//返回v的第一个邻接顶点的序号
	int firstAdjVex(MGraph G,VertexType v)
	{
		int i,j=0,k;
		k=locateVex(G,v);
		if(G.kind%2) j=INFINITY;
		for(i=0;i<G.vexnum;++i)
			if(G.arcs[k][i].adj!=j)
				return i;
		return -1;
	}

	//返回v的相对于w的下一个邻接顶面序号,若w是最后一个邻接顶点返回-1
	int nextAdjVex(MGraph G,VertexType v,VertexType w)
	{
		int i,j=0,k1,k2;
		k1=locateVex(G,v);
		k2=locateVex(G,w);
		if(G.kind%2)
			j=INFINITY;
		for(i=k2+1;i<G.vexnum;++i)
			if(G.arcs[k1][i].adj!=j)
				return i;
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
		int i,j,k;
		VRType m=0;
		if(G.kind%2) m=INFINITY;
		k=locateVex(G,v);
		if(k<0) return false;
		for(j=0;j<G.vexnum;++j)
			if(G.arcs[j][k].adj!=m)
			{
				if(G.arcs[j][k].info)
				{
					free(G.arcs[j][k].info);
					G.arcs[j][k].info=NULL;
					--G.arcnum;
				}
			}
			if(G.kind<2)
				for(j=0;j<G.vexnum;++j)
					if(G.arcs[k][j].adj!=m)
					{
						if(G.arcs[k][j].info)
						{
							free(G.arcs[k][j].info);
							G.arcs[k][j].info=NULL;
						}
						--G.arcnum;
					}
					for(j=k+1;j<G.vexnum;++j)
						strcpy(G.vexs[j-1],G.vexs[j]);
					for(i=0;i<G.vexnum;++i)
						for(j=k+1;j<G.vexnum;++j)
							G.arcs[i][j-1]=G.arcs[i][j];
					for(i=0;i<G.vexnum;++i)
						for(j=k+1;j<G.vexnum;++j)
							G.arcs[j-1][i]=G.arcs[j][i];
					--G.vexnum;
					return true;
	}

	//新增弧
	bool insertArc(MGraph &G,VertexType v,VertexType w)
	{
		int i,l,v1,w1;
		char s[MAX_INFO];
		v1=locateVex(G,v);
		w1=locateVex(G,w);
		if(v1<0||w1<0) return false;
		++G.arcnum;
		if(G.kind%2)
		{
			cout<<"请输入此弧或边的权值:"<<endl;
			cin>>G.arcs[v1][w1].adj;
		}
		else
			G.arcs[v1][w1].adj=1;
		cout<<"是否有该弧或边的相关信息(0:无1:有):"<<endl;
		cin>>i;
		if(i)
		{
			cout<<"请输入该弧或边的相关信息"<<endl;
			G.arcs[v1][w1].info=(InfoType*)malloc(sizeof(InfoType)*MAX_INFO);
			cin>>G.arcs[v1][w1].info;
		}
		if(G.kind>1)
		{
			G.arcs[w1][v1].adj=G.arcs[v1][w1].adj;
			G.arcs[w1][v1].info=G.arcs[v1][w1].info;
		}
		return true;
	}

	//删除弧
	bool deleteArc(MGraph &G,VertexType v,VertexType w)
	{
		int v1,w1,j=0;
		if(G.kind%2) j=INFINITY;
		v1=locateVex(G,v);
		w1=locateVex(G,w);
		if(v1<0||w1<0) return false;
		G.arcs[v1][w1].adj=j;
		if(G.arcs[v1][w1].info)
		{
			free(G.arcs[v1][w1].info);
			G.arcs[v1][w1].info=NULL;
		}
		if(G.kind>=2)
		{
			G.arcs[w1][v1].adj=j;
			G.arcs[w1][v1].info=NULL;
		}
		--G.arcnum;
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

void testArrGraphMain()
{
	using namespace AG;
	int i,j,k,n;
	MGraph g;
	VertexType v1,v2;
	printf("请顺序选择有向图,有向网,无向图,无向网\n");
	for(i=0;i<4;++i)
	{
		createGraph(g);
		display(g);
		printf("插入新顶点，请输入顶点的值: \n");
		cin>>v1;
		insertVex(g,v1);
		printf("插入与新顶点有关的弧或边，请输入弧或边数: \n");
		cin>>n;
		for(k=0;k<n;++k)
		{
			printf("请输入另一顶点的值: \n");
			cin>>v2;
			if(g.kind<=1)
			{
				printf("对于有向图或网，请输入另一顶点的方向(0:弧头1:弧尾): \n");
				cin>>j;
				if(j) insertArc(g,v2,v1);
				else insertArc(g,v1,v2);
			}
			else
				insertArc(g,v1,v2);
		}
		display(g);
		printf("删除顶点及相关的弧或边，请输入顶点的值: \n");
		cin>>v1;
		deleteVex(g,v1);
		display(g);
	}
	destroyGraph(g);
}


//最小生成树的prime算法

typedef struct 
{
	VertexType adjvex;
	VRType lowcost;
}miniside[MAX_VERTEXT_NUM];

int minimum(miniside SZ,MGraph G)
{
	int i=0,j,k,min;
	while(!SZ[i].lowcost) ++i;
	min = SZ[i].lowcost;
	k=i;
	for(j=i+1;j<G.vexnum;++j)
		if(SZ[j].lowcost>0&&min>SZ[j].lowcost)
		{
			min=SZ[j].lowcost;
			k=j;
		}
	return k;
}

void miniSpanTree_Prim(MGraph G,VertexType u)
{
	int i,j,k;
	miniside closedge;
	k=locateVex(G,u);
	for(j=0;j<G.vexnum;++j)
	{
		strcpy(closedge[j].adjvex,u);
		closedge[j].lowcost=G.arcs[k][j].adj;
	}
	closedge[k].lowcost=0;
	printf("最小代价生成树的各条边为\n");
	for(i=1;i<G.vexnum;++i)
	{
		k=minimum(closedge,G);
		printf("(%s-%s)\n",closedge[k].adjvex,G.vexs[k]); // 输出生成树的边
		closedge[k].lowcost=0;
		for(j=0;j<G.vexnum;++j)
			if(G.arcs[k][j].adj<closedge[j].lowcost)
			{
				strcpy(closedge[j].adjvex,G.vexs[k]);
				closedge[j].lowcost=G.arcs[k][j].adj;
			}
	}
}
void testPrime()
{
	MGraph g;
	createUDN(g,"GData8.txt");
	display(g);
	miniSpanTree_Prim(g,g.vexs[0]);
}

void kruskal(MGraph G)
{
	int set[MAX_VERTEXT_NUM],i,j;
	int k=0,a=0,b=0,min=G.arcs[a][b].adj;
	for(i=0;i<G.vexnum;++i) set[i]=i;
	printf("最小代价生成树的各条边为\n");
	while(k<G.vexnum-1)
	{
		for(i=0;i<G.vexnum;++i)
			for(j=i+1;j<G.vexnum;++j)
				if(G.arcs[i][j].adj<min)
				{
					min=G.arcs[i][j].adj;
					a=i;
					b=j;
				}
		min=G.arcs[a][b].adj=INFINITY;
		if(set[a]!=set[b])
		{
			printf("%s-%s\n",G.vexs[a],G.vexs[b]);
			++k;
			for(i=0;i<G.vexnum;++i)
				if(set[i]==set[b])
					set[i]=set[a];
		}
	}
}

void testCruskal()
{
	MGraph g;
	createUDN(g,"GData8.txt");
	display(g);
	kruskal(g);
}

//求最短路径
typedef int pathPatrix[MAX_VERTEXT_NUM][MAX_VERTEXT_NUM];
typedef int shortPathTable[MAX_VERTEXT_NUM];

//用dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径p[v]及带树长度
void shortestPath_DIJ(MGraph G,int v0,pathPatrix p,shortPathTable d)
{
	int v,w,i,j,min;
	bool final[MAX_VERTEXT_NUM];
	for(v=0;v<G.vexnum;++v)
	{
		final[v]=false;
		d[v]=G.arcs[v0][v].adj;
		for(w=0;w<G.vexnum;++w)
			p[v][w]=false;
		if(d[v]<INFINITY)
			p[v][v0]=p[v][v]=true;
	}
	d[v0]=0;
	final[v0]=true;
	for(i=1;i<G.vexnum;++i)
	{
		min=INFINITY;
		for(w=0;w<G.vexnum;++w)
			if(!final[w]&&d[w]<min)
			{
				v=w;
				min=d[w];
			}
		final[v]=true;
		for(w=0;w<G.vexnum;++w)
			if(!final[w]&&min<INFINITY&&G.arcs[v][w].adj<INFINITY&&(min+G.arcs[v][w].adj<d[w]))
			{
				d[w]=min+G.arcs[v][w].adj;
				for(j=0;j<G.vexnum;++j)
					p[w][j]=p[v][j];
				p[w][w]=true;
			}
	}
}


void testDijkstra()
{
	int i,j;
	MGraph g;
	pathPatrix p;
	shortPathTable d;
	createDN(g,"GData12.txt");
	display(g);
	shortestPath_DIJ(g,0,p,d);
	printf("最短路径数组p[i][j]如下:\n");
	for(i=0;i<g.vexnum;++i)
	{
		for(j=0;j<g.vexnum;++j)
			printf("%2d",p[i][j]);
		printf("\n");
	}
	printf("%s到各顶点的最短路径长度为\n",g.vexs[0]);
	for(i=0;i<g.vexnum;++i)
		if(i!=0)
			if(d[i]==INFINITY) printf("%s-%s:%s\n",g.vexs[0],g.vexs[i],"∞");
			else printf("%s-%s:%d\n",g.vexs[0],g.vexs[i],d[i]);
			
}

//每一对顶点之前的最短路径

typedef int pathMatrix[MAX_VERTEXT_NUM][MAX_VERTEXT_NUM][MAX_VERTEXT_NUM];
typedef int distanceMatrix[MAX_VERTEXT_NUM][MAX_VERTEXT_NUM];

//floyd算法求有向网v和w之间的最短路径
void shortestPath_FLOYD(MGraph G,pathMatrix p,distanceMatrix d)
{
	int u,v,w,i;
	for(v=0;v<G.vexnum;++v)
		for(w=0;w<G.vexnum;++w)
		{
			d[v][w]=G.arcs[v][w].adj;
			for(u=0;u<G.vexnum;++u) p[v][w][u]=false;
			if(d[v][w]<INFINITY)
				p[v][w][v]=p[v][w][w]=true;//有v到w的路径
		}
	for(u=0;u<G.vexnum;++u)
		for(v=0;v<G.vexnum;++v)
			for(w=0;w<G.vexnum;++w)
				if(d[v][u]<INFINITY&&d[u][w]<INFINITY&&d[v][u]+d[u][w]<d[v][w])
				{
					d[v][w]=d[v][u]+d[u][w];
					for(i=0;i<G.vexnum;++i)
						p[v][w][i]=p[v][u][i]||p[u][w][i];//从v到w的路径经过人v到u和从u到w的所有路径
				}
}

void testFloyd()
{
	MGraph g;
	int i,j,k,l,m,n;
	pathMatrix p;
	distanceMatrix d;
	createDN(g,"GData13.txt");
	for(i=0;i<g.vexnum;++i)
		g.arcs[i][i].adj=0;
	display(g);
	shortestPath_FLOYD(g,p,d);
	printf("d矩阵:\n");
	for(i=0;i<g.vexnum;++i)
	{
		for(j=0;j<g.vexnum;++j)
			printf("%6d",d[i][j]);
		printf("\n");
	}
	for(i=0;i<g.vexnum;++i)
		for(j=0;j<g.vexnum;++j)
			if(i!=j) printf("%s到%s的最短距离为%d\n",g.vexs[i],g.vexs[j],d[i][j]);
	printf("p矩阵:\n");
	for(i=0;i<g.vexnum;++i)
		for(j=0;j<g.vexnum;++j)
			if(i!=j)
			{
				printf("由%s到%s经过：",g.vexs[i],g.vexs[j]);
				for(k=0;k<g.vexnum;++k)
					if(p[i][j][k]) printf("%s ",g.vexs[k]);
				printf("\n");
			}
}

//地图查询
void pathMap(MGraph G,pathMatrix p,int i,int j)
{
	int k;
	int m=i;
	printf("依次经过的城市：\n");
	while(m!=j)
	{
		G.arcs[m][m].adj=INFINITY;
		for(k=0;k<G.vexnum;++k)
			if(G.arcs[m][k].adj<INFINITY&&p[m][j][k])
			{
				printf("%s ",G.vexs[m]);
				G.arcs[m][k].adj=G.arcs[k][m].adj=INFINITY;
				m=k;
				break;
			}
	}
}

void testMapChina()
{
	MGraph g;
	int i,j,k,l,q=1;
	pathMatrix p;
	distanceMatrix d;
	createUDN(g,"GData14.txt");
	for(i=0;i<g.vexnum;++i)
		g.arcs[i][i].adj=0;
	shortestPath_FLOYD(g,p,d);
	while(q)
	{
		printf("请选择：1 查询0 结束\n");
		cin>>q;
		if(q)
		{
			for(i=0;i<g.vexnum;++i)
			{
				printf("%2d %-9s",i+1,g.vexs[i]);
				if(i%6==5) // 输出6个数据就换行
					printf("\n");
			}
			printf("\n请输入要查询的起点城市代码终点城市代码: ");
			cin>>i>>j;
			if(d[i-1][j-1]<INFINITY)
			{
				printf("%s到%s的最短距离为%d\n",g.vexs[i-1],g.vexs[j-1],d[i-1][j-1]);
				pathMap(g,p,i-1,j-1); // 求最短路径上由起点城市到终点城市沿途所经过的城市
			}
			else
				printf("%s到%s没有路径可通\n",g.vexs[i-1],g.vexs[j-1]);
			/*printf("与%s到%s有关的p矩阵:\n",g.vexs[i-1],g.vexs[j-1]);
			for(k=0;k<g.vexnum;k++)
				printf("%2d",p[i-1][j-1][k]);*/
			printf("\n");
		}
	}
}