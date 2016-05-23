
#include "stdafx.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>



using namespace std;
inline void swap_(int *a,int *b)
{
	int c = *a;
	*a=*b;
	*b=c;
}

//随机重新排列函数
void random_shuffle(int a[],int n)
{
	srand(time(NULL));
	for(int i=1;i<n;++i)
		swap_(&a[i],&a[rand()%(i+1)]);
}

void printf_intArr(int a[],int n)
{
	for(int i=0;i<n;++i)
		printf("%d ",a[i]);
	printf("\n");
}

void test1()
{
	int a[]={2,4,5,12,35,88,9,56,123,56};
	int len = sizeof(a)/sizeof(int);

	printf_intArr(a,len);

	random_shuffle(a,len);
	printf_intArr(a,len);

	random_shuffle(a,len);
	printf_intArr(a,len);


	random_shuffle(a,len);
	printf_intArr(a,len);

}


//从文件中随机取一行
void randomLine()
{
	int i,num,nChooseNum;
	const char * fileName = "in.txt";
	freopen(fileName,"r",stdin);
	srand(time(NULL));
	i=1;
	while(scanf("%d",&num)!=EOF)
	{
		
		if(rand()%i==0)
			nChooseNum=num;
		++i;
	}
	printf("line : %d is choosen",nChooseNum);
}


void testRandom()
{
	//test1();
	randomLine();
}