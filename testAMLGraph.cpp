
#include "stdafx.h"

#include "testAMLGraph.h"
#include "queueTest.h"

namespace AMLG{
typedef int QElemType;
//全局访问标志
bool visitedArr[MAX_VERTEXT_NUM];

//访问函数
void visit(VertexType i)
{
	cout<<i<<" ";
}

//返回G中顶点u的位置
int locateVex(AMLGraph G,VertexType u)
{
	int i;
	for(i=0;i<G.vexnum;++i)
		if(strcmp(u,G.adjmulist[i].data)==0) return i;
	return -1;
}

//构造图(只针对有向)
void createGraph(AMLGraph &G)
{
	int i,j,k;
	int IncInfo;
	EBox *p;
	VertexType v1,v2;
	printf("请输入有向图的顶点数,弧数,是否为带权图(是:1，否:0): \n");
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

//置边的访问标记为未访问
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

//打印图
void printGraph(AMLGraph G)
{
	int i;
	EBox *p=NULL;
	markUnvizited(G);
	printf("%d个顶点：\n",G.vexnum);
	for(i=0;i<G.vexnum;++i)
		printf("%s ",G.adjmulist[i].data);
	printf("\n%d条边:\n",G.edgenum);
	for(i=0;i<G.vexnum;++i)
	{
		p=G.adjmulist[i].firstedg;
		while(p)
			if(p->ivex==i)
			{
				if(!p->mark)
				{
					printf("%s－%s ",G.adjmulist[i].data,G.adjmulist[p->jvex].data);
					p->mark=visited;
					if(p->info) printf("权值: %d ",*p->info);
				}
				p=p->ilink;
			}
			else
			{
				if(!p->mark)
				{
					printf("%s－%s ",G.adjmulist[p->ivex].data,G.adjmulist[i].data);
					p->mark=visited;
					if(p->info) printf("权值: %d ",*p->info);
				}
				p=p->jlink;
			}
		cout<<endl;
	}
}


//删除边链表第1个结点
bool listDeleteFirstVex(ArcBox * &p,ArcBox &e,int pos)
{
	if(!p || pos<0 ) return false;

	pos=1;
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

//销毁图
void destroyGraph(AMLGraph &G)
{
	int i;
	for(i=G.vexnum-1;i>=0;--i)
		deleteVex(G,G.adjmulist[i].data);
}

//返回顶点序号v的值
VertexType & getVex(AMLGraph G,int v)
{
	if(v>=G.vexnum||v<0) exit(0);
	return G.adjmulist[v].data;
}

//对v重新赋值
bool putVex(AMLGraph &G,VertexType v,VertexType value)
{
	int i= locateVex(G,v);
	if(i<0) return false;
	strcpy(G.adjmulist[i].data,value);
	return true;
}

//返回v的第一个邻接顶点的序号
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

//两条弧是否相等
bool equalvex(ElemType a,ElemType b)
{
	if(a.headvex==b.headvex) return true;
	return false;
}

//返回v的相对于w的下一个邻接顶面序号,若w是最后一个邻接顶点返回-1
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

//新增顶点v(但不增加相关的弧)
void insertVex(AMLGraph &G,VertexType v)
{
	strcpy(G.adjmulist[G.vexnum].data,v);
	G.adjmulist[G.vexnum++].firstedg=NULL;
}


//删除顶点
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

//新增弧
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
	printf("该边是否有权值(1:有0:无): \n");
	cin>>IncInfo;
	if(IncInfo)
	{
		p->info=(InfoType*)malloc(sizeof(InfoType));
		printf("请输入该边的权值: \n");
		cin>>*(p->info);
	}
	else
		p->info=NULL;
	++G.edgenum;
	return true;
}

//删除弧
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

//从第v个顶点出发递归地深度优先遍历图G
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

//从第1个顶点起深度优先遍历图并对每个顶点调用访问函数一次
void DFSTraverse(AMLGraph G,visitFunc func)
{
	int v;
	for(v=0;v<G.vexnum;++v)
		visitedArr[v]=false;
	for(v=0;v<G.vexnum;++v)
		if(!visitedArr[v]) DFS(G,v,func);
	cout<<endl;
}

//按广度优先非递归遍历图G
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