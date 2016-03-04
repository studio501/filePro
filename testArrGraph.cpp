
#include "stdafx.h"

#include "testArrGraph.h"
namespace AG{
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
};

void testArrGraphMain()
{
	using namespace AG;

	MGraph g;
	createFUDG(g);
}