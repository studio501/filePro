
#include "stdafx.h"
#include "searchSeq.h"

void testSearchSeq()
{
	ElemType r[N]={{179328,"�η���",85,89,98,100,93,80,47},
	{1,"�º�",85,86,88,100,92,90,45},
	{2,"½��",78,75,90,80,95,88,37},
	{3,"��ƽ",82,80,78,98,84,96,40},
	{4,"��С��",76,85,94,57,77,69,44}}; // ���鲻���ؼ�������

	SSTable<ElemType> st;
	int i;
	long s;
	for(i=0;i<N;++i)
		r[i].total=r[i].politics+r[i].Chinese+r[i].English+r[i].math+r[i].physics+
		r[i].chemistry+r[i].biology;
	create_Ord(st,r,N);
	printf("׼��֤��������������������ѧ����ѧ�����ܷ�\n");
	traverse(st,print);
	printf("������������˵Ŀ���: ");
	cin>>s;
	//i=search_Seq(st,s);
	i=seqrch_Bin(st,s);
	if(i)
		print(st.elem[i]);
	else
		printf("û�ҵ�\n");
	destroy(st);
}