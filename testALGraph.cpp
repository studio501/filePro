
#include "stdafx.h"

#include "testALGraph.h"
#include "queueTest.h"
#include "testCSTree.h"
using namespace CST;
using namespace ALG;
namespace ALG{
typedef int QElemType;
//typedef VertexType TElemType;
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

//创建图根据文件名
void createGraphWithFileName(ALGraph &G,const char *filename)
{
	int i,j,k,w;
	VertexType va,vb;
	ArcNode *e;

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

			if(G.kind>1)
			{
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
		}
		fin.close();
	}
}

//构造图
void createGraph(ALGraph &G)
{
	cout<<"请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3):\n";
	cin>>G.kind;

	char filename[24];
	sprintf(filename,"GData6_%d.txt",G.kind%2);
	createGraphWithFileName(G,filename);
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
				printf("%s(%d)->",G.vertices[p->adjvex].data,*(p->info) );
			else printf("%s->",G.vertices[p->adjvex].data);				//printf("%d->",p->adjvex);
			
			
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
bool listDeleteFirstVex(ArcNode * &p,ArcNode* &e,int pos)
{
	if(!p || pos<0 ) return false;

	pos = 1;
	int i=0;
	ArcNode *q = p;
	
	p = p->next;
	e=q;
	return true;
}

//删除某个结点
ArcNode * listDeleteElem(ArcNode *p,ArcNode e)
{
	ArcNode *q = p,*t=p;
	while(q)
	{
		if(equalvex(*q,e))
		{
			t->next=q->next;
			return q;
		}
		else
		{
			t=q;
			q=q->next;
		}
	}
	return NULL;
}

//在边链表中找出与e adjx相同的结点
ArcNode * point(ArcNode *p,ArcNode e,ArcNode * &p1)
{
	if(!p) return NULL;
	ArcNode * q = p;
	p1 = p;
	while(q)
	{
		if(equalvex(*q,e)) return q;
		else
		{
			p1=q;
			q=q->next;
		}
	}
	return NULL;
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
void insertVex(ALGraph &G,VertexType v)
{
	strcpy(G.vertices[G.vexnum].data,v);
	G.vertices[G.vexnum].firstarc=NULL;
	++G.vexnum;
}

//获取顶点的边链表长度
int lengthOfAdjVex(ALGraph G,VertexType v)
{
	int j = locateVex(G,v),i=0;
	if(j<0) return 0;
	ArcNode * p = G.vertices[j].firstarc;
	while(p)
	{
		p=p->next;
		++i;
	}
	return i;
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
bool deleteVex(ALGraph &G,VertexType v)
{
	int i=0,j,k;
	ArcNode *e=NULL,eNode,*p;
	j=locateVex(G,v);
	if(j<0) return false;
	
	i = lengthOfAdjVex1(G,j);
	G.arcnum-=i;
	
	while(G.vertices[j].firstarc)
	{
		listDeleteFirstVex(G.vertices[j].firstarc,e);
		if(G.kind%2 )
		{
			free(e->info);
			e->info=NULL;
		}
		free(e);
		e=NULL;
	}
	--G.vexnum;
	for(i=j;i<G.vexnum;++i)
		G.vertices[i]=G.vertices[i+1];

	for(i=0;i<G.vexnum;++i)
	{
		eNode.adjvex=j;
		p = point(G.vertices[i].firstarc,eNode,e);
		if(p)
		{
			if(e)
				e->next=p->next;
			else
				G.vertices[i].firstarc=p->next;
			if(G.kind<2)
			{
				--G.arcnum;
				if(G.kind==1)
				{
					free(p->info);
					p->info=NULL;
				}
			}
			free(p);
			p=NULL;
		}
		for(k=j+1;k<=G.vexnum;++k)
		{
			eNode.adjvex = k;
			p = point(G.vertices[i].firstarc,eNode,e);
			if(p)
				--p->adjvex;
		}
	}
	return true;
}

//新增弧
bool insertArc(ALGraph &G,VertexType v,VertexType w)
{
	ArcNode *e = (ArcNode*)malloc(sizeof(ArcNode));
	int i,j;
	i=locateVex(G,v);
	j=locateVex(G,w);
	if(i<0||j<0) return false;
	++G.arcnum;
	e->adjvex=j;
	e->info=NULL;
	if(G.kind%2)
	{
		e->info=(int *)malloc(sizeof(int));
		printf("请输入弧(边)%s→%s的权值: ",v,w);
		cin>>*(e->info);
	}

	listInsertFirstVex(G.vertices[i].firstarc,e);
	if(G.kind>1)
	{

		ArcNode *e1 = (ArcNode*)malloc(sizeof(ArcNode));
		e1->adjvex=i;
		e1->info=e->info;
		listInsertFirstVex(G.vertices[j].firstarc,e1);
	}

	return true;
}

//删除弧
bool deleteArc(ALGraph &G,VertexType v,VertexType w)
{
	int i,j;
	bool k;
	ArcNode e;
	i=locateVex(G,v);
	j=locateVex(G,w);
	if(i<0||j<0||i==j) return false;
	++G.arcnum;
	e.adjvex=j;
	ArcNode * p = listDeleteElem(G.vertices[i].firstarc,e);
	if(p)
	{
		--G.arcnum;
		if(G.kind%2)
		{
			free(p->info);
			p->info=NULL;
		}
		if(G.kind>2)
		{
			e.adjvex=i;
			p = listDeleteElem(G.vertices[j].firstarc,e);
		}
	}
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

//从第v 个顶点出发深度优先遍历图g,建立以T为根的生成树
void DFSTree(ALGraph G,int v,CSTree &T)
{
	bool first = true;
	int w;
	CSTree p=NULL,q=NULL;
	visited[v]=true;
	for(w=firstAdjVex(G,G.vertices[v].data);w>=0;w=nextAdjVex(G,G.vertices[v].data,G.vertices[w].data))
		if(!visited[w])
		{
			p=(CSTree)malloc(sizeof(CSNode));
			p->data=G.vertices[w].data[0];
			p->firstchild=NULL;
			p->nextsibling=NULL;
			if(first)
			{
				T->firstchild=p;
				first=false;
			}
			else
				q->nextsibling=p;
			q=p;
			DFSTree(G,w,q);
		}
}

//建立无向图的深度优先生成森林
void DFSForest(ALGraph G,CSTree &T)
{
	CSTree p=NULL,q=NULL;
	int v;
	T=NULL;
	for(v=0;v<G.vexnum;++v)
		visited[v]=false;
	for(v=0;v<G.vexnum;++v)
		if(!visited[v])
		{
			p=(CSTree)malloc(sizeof(CSNode));
			p->data=G.vertices[v].data[0];
			p->firstchild=NULL;
			p->nextsibling=NULL;
			if(!T) T=p;
			else
				q->nextsibling=p;
			q=p;
			DFSTree(G,v,p);
		}
}


void testALGraphMain()
{
	using namespace ALG;
	ALGraph g;
	createGraph(g);
	printGraph(g);
	cout<<g.vertices[firstAdjVex(g,"v1")].data;
	cout<<g.vertices[nextAdjVex(g,"v1","v4")].data<<"\n========\n";
	//deleteVex(g,"v1");
	printGraph(g);
	insertArc(g,"v2","v3");
	cout<<endl;
	//deleteArc(g,"v2","v3");
	printGraph(g);

	DFSTraverse(g,visit);
	BFSTraverse(g,visit);
	DFSTraverse1(g,visit);
	BFSTraverse1(g,visit);
	destroyGraph(g);
}

void testGraphToTree()
{
	ALGraph gt;
	CSTree t;

	gt.kind=UDG;//无向图
	createGraphWithFileName(gt,"GData7.txt");
	printGraph(gt);

	DFSForest(gt,t);
	cout<<"\n先序遍历:\n";
	preOrderTraverse(t,visit_tree);
	int a = 100;
}

int visited_intArr[MAX_VERTEXT_NUM];
int count_,lowcount=1;
int low[MAX_VERTEXT_NUM],lowOrder[MAX_VERTEXT_NUM];

//从第v0个顶点出发深度优先遍历图,查找并输出关节点
void DFSAtricul(ALGraph G,int v0)
{
	int min,w;
	ArcNode *p=NULL;
	visited_intArr[v0]=min=++count_;
	for(p=G.vertices[v0].firstarc;p;p=p->next)
	{
		w=p->adjvex;
		if(visited_intArr[w]==0)
		{
			DFSAtricul(G,w);
			if(low[w]<min) min=low[w];
			else if(low[w]>=visited_intArr[v0])
				printf("%d %s\n",v0,G.vertices[v0].data); // 输出关节点v0
		}
		else if(visited_intArr[w]<min) min=visited_intArr[w];
	}
	low[v0]=min;
	lowOrder[v0]=lowcount++;
}

//查找并输出图上全部关节点
void findArticul(ALGraph G)
{
	int i,v;
	ArcNode *p=NULL;
	count_=1;
	visited_intArr[0]=count_;
	for(i=1;i<G.vexnum;++i) visited_intArr[i]=0;
	p=G.vertices[0].firstarc;
	v=p->adjvex;
	DFSAtricul(G,v);
	if(count_<G.vexnum)
	{
		printf("%d %s\n",0,G.vertices[0].data); // 根是关节点，输出根
		while(p->next)
		{
			p=p->next;
			v=p->adjvex;
			if(visited_intArr[v]==0) DFSAtricul(G,v);
		}
	}
}


//测试连通图的关节点
void testJoint()
{
	int i;
	ALGraph gt;
	gt.kind=UDG;//无向图
	createGraphWithFileName(gt,"GData9.txt");
	printGraph(gt);
	printf("输出关节点：\n");
	findArticul(gt);
	printf(" i G.vertices[i].data visited[i] low[i] lowOrder[i]\n"); // 输出辅助变量
	for(i=0;i<gt.vexnum;++i)
		printf("%2d %9s %14d %8d %8d\n",i,gt.vertices[i].data,visited[i],low[i],lowOrder[i]);
}

//拓扑排序


//求顶点的入度
void findInDegree(ALGraph G,int indegree[])
{
	int i;
	ArcNode *p=NULL;
	for(i=0;i<G.vexnum;++i) indegree[i]=0;
	for(i=0;i<G.vexnum;++i)
	{
		p=G.vertices[i].firstarc;
		while(p)
		{
			indegree[p->adjvex]++;
			p=p->next;
		}
	}
}

#include "testStack.h"
//1.在有向图中选一个没有前驱的顶点输出
//2.从图中删除该顶点和所有以它为尾的弧(重复1,2)
bool topoLogicalSort(ALGraph G)
{
	int i,k,count=0;
	int indegree[MAX_VERTEXT_NUM];
	SqStack S;
	ArcNode *p=NULL;
	findInDegree(G,indegree);
	initStack(S);
	for(i=0;i<G.vexnum;++i)
		if(!indegree[i]) pushStack(S,i);
	while(!isStackEmpty(S))
	{
		popStack(S,i);
		printf("%s ",G.vertices[i].data); // 输出i号顶点
		++count;
		for(p=G.vertices[i].firstarc;p;p=p->next)
		{
			k=p->adjvex;
			if(!(--indegree[k])) pushStack(S,k);
		}
	}
	if(count<G.vexnum)
	{
		printf("此有向图有回路\n");
		return false;
	}
	else
	{
		printf("为一个拓扑序列。\n");
		return true;
	}
}

//拓扑排序
void testTopoLogicSort()
{
	ALGraph f;
	f.kind=DG;
	createGraphWithFileName(f,"GData10.txt");
	printGraph(f);
	topoLogicalSort(f);
}

//关键路径
int ve[MAX_VERTEXT_NUM];
bool topologicalOrder(ALGraph G,SqStack &T)
{
	int i,k,count=0;
	int indegree[MAX_VERTEXT_NUM];
	SqStack S;
	ArcNode *p=NULL;
	findInDegree(G,indegree);
	initStack(S);
	printf("拓扑序列：\n");
	for(i=0;i<G.vexnum;++i)
		if(!indegree[i]) pushStack(S,i);
	initStack(T);
	for(i=0;i<G.vexnum;++i) ve[i]=0;
	while(!isStackEmpty(S))
	{
		popStack(S,i);
		printf("%s ",G.vertices[i].data);
		pushStack(T,i);
		++count;
		for(p=G.vertices[i].firstarc;p;p=p->next)
		{
			k=p->adjvex;
			if(--indegree[k]==0) pushStack(S,k);
			if(ve[i]+*(p->info)>ve[k]) ve[k]=ve[i]+*(p->info);
		}
	}
	if(count<G.vexnum)
	{
		printf("此有向网有回路\n");
		return false;
	}
	else return true;
}

//输出G的各项关键活动
//计算弧的最早开始时间和最迟开始时间复杂度为O(e)
//求关键路径的时间复杂度为O(n+e)
bool criticalPath(ALGraph G)
{
	int vl[MAX_VERTEXT_NUM];
	SqStack T;
	int i,j,k,ee,e1,dut;
	ArcNode *p=NULL;
	if(!topologicalOrder(G,T)) return false;//有向环
	j=ve[0];
	for(i=1;i<G.vexnum;++i)
		if(ve[i]>j) j=ve[i];
	for(i=0;i<G.vexnum;++i)
		vl[i]=j;
	while(!isStackEmpty(T))
		for(popStack(T,j),p=G.vertices[j].firstarc;p;p=p->next)
		{
			k=p->adjvex;
			dut=*(p->info);
			if(vl[k]-dut<vl[j]) vl[j]=vl[k]-dut;
		}
	printf("\ni ve[i] vl[i]\n");
	for(i=0;i<G.vexnum;++i)
	{
		printf("%d %d %d",i,ve[i],vl[i]);
		if(ve[i]==vl[i]) printf(" 关键路径经过的顶点");
		printf("\n");
	}
	printf("j k 权值ee el\n");
	for(j=0;j<G.vexnum;++j)
		for(p=G.vertices[j].firstarc;p;p=p->next)
		{
			k=p->adjvex;
			dut=*(p->info);
			ee=ve[j];
			e1=vl[k]-dut;
			printf("%s→%s %3d %3d %3d ",G.vertices[j].data,G.vertices[k].data,dut,ee,e1);
			if(ee==e1)
				printf("关键活动");
			printf("\n");
		}
	return true;
}

void testCriticalPath()
{
	ALGraph h;
	h.kind=DN;
	createGraphWithFileName(h,"GData11.txt");
	printGraph(h);
	criticalPath(h);
}

