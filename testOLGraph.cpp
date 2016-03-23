
#include "stdafx.h"

#include "testOLGraph.h"
#include "queueTest.h"

namespace OLG{
typedef int QElemType;
//全局访问标志
bool visited[MAX_VERTEXT_NUM];

//访问函数
void visit(VertexType i)
{
	cout<<i<<" ";
}

//返回G中顶点u的位置
int locateVex(OLGraph G,VertexType u)
{
	int i;
	for(i=0;i<G.vexnum;++i)
		if(strcmp(u,G.xlist[i].data)==0) return i;
	return -1;
}

//构造图(只针对有向)
void createGraph(OLGraph &G)
{
	int i,j,k;
	int IncInfo;
	ArcBox *p;
	VertexType v1,v2;
	printf("请输入有向图的顶点数,弧数,是否为带权图(是:1，否:0): \n");
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

//插在表头
bool listInsertFirstVex(ArcNode * &p,ArcNode *e,int pos)
{
	pos=1;
	e->next=p->next;
	p->next=e;
	return true;
}

//删除边链表第1个结点
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

//定位链表中的元素e
int listLocateElem(ArcBox *p,ElemType e)
{
	while(p)
	{
		if(p->data.headvex == e.headvex) return true;
		else p=p->tlink;
	}
	return false;
}

//删除某个结点
ArcNode * listDeleteElem(ArcNode *p,ArcNode e)
{
	
	return NULL;
}

//在边链表中找出与e adjx相同的结点
ArcNode * point(ArcNode *p,ArcNode e,ArcNode * &p1)
{
	
	return NULL;
}

//销毁图
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

//返回顶点序号v的值
VertexType & getVex(OLGraph G,int v)
{
	if(v>=G.vexnum||v<0) exit(0);
	return G.xlist[v].data;
}

//对v重新赋值
bool putVex(OLGraph &G,VertexType v,VertexType value)
{
	int i= locateVex(G,v);
	if(i<0) return false;
	strcpy(G.xlist[i].data,value);
	return true;
}

//返回v的第一个邻接顶点的序号
int firstAdjVex(OLGraph G,VertexType v)
{
	int i;
	ArcBox *p;
	i=locateVex(G,v);
	p=G.xlist[i].firstout;
	if(p) return p->data.headvex;
	else return -1;
}

//两条弧是否相等
bool equalvex(ElemType a,ElemType b)
{
	if(a.headvex==b.headvex) return true;
	return false;
}

//返回v的相对于w的下一个邻接顶面序号,若w是最后一个邻接顶点返回-1
int nextAdjVex(OLGraph G,VertexType v,VertexType w)
{
	int i,j;
	ArcBox *p;
	i=locateVex(G,v);
	j=locateVex(G,w);
	p=G.xlist[i].firstout;
	while(p&&p->data.headvex!=j) p = p->tlink;
	if(p) p= p->tlink;//w不是v的最后一个邻接点
	if(p) return p->data.headvex;//有下一个邻接点
	else return -1;
}

//新增顶点v(但不增加相关的弧)
void insertVex(OLGraph &G,VertexType v)
{
	strcpy(G.xlist[G.vexnum].data,v);
	G.xlist[G.vexnum].firstin=NULL;
	G.xlist[G.vexnum].firstout=NULL;
	++G.vexnum;
}

//获取顶点的边链表长度
int lengthOfAdjVex(ALGraph G,VertexType v)
{
	
	return 0;
}

//获取顶点的边链表长度
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

//删除顶点
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

//新增弧
bool insertArc(ALGraph &G,VertexType v,VertexType w)
{
	
	return true;
}

//删除弧
bool deleteArc(ALGraph &G,VertexType v,VertexType w)
{
	
	return true;
}

//从第v个顶点出发递归地深度优先遍历图G
void DFS(ALGraph G,int v,visitFunc func)
{
	int w;
	visited[v]=true;
	func(G.vertices[v].data);
	for(w=firstAdjVex(G,G.vertices[v].data);w>=0;w=nextAdjVex(G,G.vertices[v].data,G.vertices[w].data))
		if(!visited[w])
			DFS(G,w,func);
}

//从第1个顶点起深度优先遍历图并对每个顶点调用访问函数一次
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

//从第v个顶点出发递归地深度优先遍历图G
void DFS1(ALGraph G,int v,visitFunc func)
{
	ArcNode *p;
	visited[v]=true;
	func(G.vertices[v].data);
	for(p=G.vertices[v].firstarc;p;p=p->next)
		if(!visited[p->adjvex])
			DFS1(G,p->adjvex,func);
}

//从第1个顶点起深度优先遍历图并对每个顶点调用访问函数一次
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

//按广度优先非递归遍历图G
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

//按广度优先非递归遍历图G
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

void testOLGraphMain()
{
	using namespace OLG;
	OLGraph g;
	createGraph(g);
	destroyGraph(g);
	int a=100;
}