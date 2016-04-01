
#include "stdafx.h"
#define N 16
struct myData
{
	int ord;
};

//typedef myData Others;
#include "keyTree.h"

#define myDLTNODE DLTNode<myData>
#define myDLTree DLTNode<myData>*
#define myRECORD Record<myData>
static void print(const myRECORD& e)
{
	int i;
	printf("(");
	for(i=0;i<e.key.num;++i)
		printf("%c",e.key.ch[i]);
	printf(",%d)",e.others.ord);
}

void testKeyTree()
{
	myDLTree t;
	int i;
	char s[MAX_KEY_LEN+1];
	keysType k;
	myRECORD *p;
	myRECORD r[N] = {{{"CAI"},1},{{"CAO"},2},{{"LI"},3},{{"LAN"},4},{{"CHA"},5},{{"CHANG"},6},
	{{"WEN"},7},{{"CHAO"},8},{{"YUN"},9},{{"YANG"},10},{{"LONG"},11},
	{{"WANG"},12},{{"ZHAO"},13},{{"LIU"},14},{{"WU"},15},{{"CHEN"},16}};

	initDSTable(t);
	for(i=0;i<N;++i)
	{
		r[i].key.num=strlen(r[i].key.ch);
		p=searchDLTree(t,r[i].key);
		if(!p)
			insertDSTable(t,&r[i]);
	}
	printf("∞¥πÿº¸◊÷∑˚¥ÆµƒÀ≥–Ú±È¿˙À´¡¥º¸ ˜:\n");
	traverseDSTable<myData>(t,print);
	printf("\n«Î ‰»Î¥˝≤È’“º«¬ºµƒπÿº¸◊÷∑˚¥Æ: ");
	cin>>s;
	k.num=strlen(s);
	strcpy(k.ch,s);
	p=searchDLTree(t,k);
	if(p)
		print(*p);
	else
		printf("√ª’“µΩ");
	printf("\n");
	destroyDSTable(t);
}