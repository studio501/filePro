#include "stdafx.h"

#include "testArrGraph.h"
#include "queueTest.h"
namespace AG{
	typedef VRType QElemType;
	//ȫ�ַ��ʱ�־
	bool visited[MAX_VERTEXT_NUM];

	//���ʺ���
	void visit(VertexType i)
	{
		cout<<i<<" ";
	}

	//����G�ж���u��λ��
	int locateVex(MGraph G,VertexType u)
	{
		int i;
		for(i=0;i<G.vexnum;++i)
			if(strcmp(u,G.vexs[i])==0) return i;
		return -1;
	}

	//��������(�ڽӾ���)��ʾ�� ��������ͼ
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

	//��������(�ڽӾ���)��ʾ�� ����������
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

	//��������(�ڽӾ���)��ʾ�� ��������ͼ
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

	//��������(�ڽӾ���)��ʾ�� ����������
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
					G.arcs[i][j].adj=1;
					if(incInfo)
					{
						G.arcs[i][j].info=(InfoType *)malloc(sizeof(InfoType)*MAX_INFO);
						fin>>G.arcs[i][j].info;
					}
				}
				G.kind=DN;
		}
	}

	//��������(�ڽӾ���)��ʾ�� ����������
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

	//��������(�ڽӾ���)��ʾ�� ����������
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

	//����ͼ
	void createGraph(MGraph &G)
	{
		cout<<"������ͼ������(����ͼ:0,������:1,����ͼ:2,������:3)"<<endl;
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
		int k = locateVex(G,v);
		if(k<0) return false;
		strcpy(G.vexs[k],value);
		return true;
	}

	//����v�ĵ�һ���ڽӶ�������
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

	//����v�������w����һ���ڽӶ������,��w�����һ���ڽӶ��㷵��-1
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

	//������
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
			cout<<"������˻���ߵ�Ȩֵ:"<<endl;
			cin>>G.arcs[v1][w1].adj;
		}
		else
			G.arcs[v1][w1].adj=1;
		cout<<"�Ƿ��иû���ߵ������Ϣ(0:��1:��):"<<endl;
		cin>>i;
		if(i)
		{
			cout<<"������û���ߵ������Ϣ"<<endl;
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

	//ɾ����
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

void testArrGraphMain()
{
	using namespace AG;
	int i,j,k,n;
	MGraph g;
	VertexType v1,v2;
	printf("��˳��ѡ������ͼ,������,����ͼ,������\n");
	for(i=0;i<4;++i)
	{
		createGraph(g);
		display(g);
		printf("�����¶��㣬�����붥���ֵ: \n");
		cin>>v1;
		insertVex(g,v1);
		printf("�������¶����йصĻ���ߣ������뻡�����: \n");
		cin>>n;
		for(k=0;k<n;++k)
		{
			printf("��������һ�����ֵ: \n");
			cin>>v2;
			if(g.kind<=1)
			{
				printf("��������ͼ��������������һ����ķ���(0:��ͷ1:��β): \n");
				cin>>j;
				if(j) insertArc(g,v2,v1);
				else insertArc(g,v1,v2);
			}
			else
				insertArc(g,v1,v2);
		}
		display(g);
		printf("ɾ�����㼰��صĻ���ߣ������붥���ֵ: \n");
		cin>>v1;
		deleteVex(g,v1);
		display(g);
	}
	destroyGraph(g);
}