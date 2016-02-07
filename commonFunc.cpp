
#include "stdafx.h"
#include "commonFunc.h"


//计算时间差
long computeTime(timeb t1,timeb t2,const char * flagName)
{
	long temp = abs((t1.time*1000+t1.millitm) - (t2.time*1000+t2.millitm));
	cout<<"time in"<<flagName<<" spend "<<temp<<" mini seconds"<<endl;
	return temp;
}

// 计算1-1/x+1/x*x⋯
double diffCompute1(int n,double x)
{
	timeb t1,t2;
	double sum=1,temp;
	ftime(&t1);
	for(int i=1;i<=n;++i)
	{
		temp = 1;
		for(int j=1;j<=i;++j)
		{
			temp = temp*(-1)/x;
		}
		sum = sum + temp;
	}
	ftime(&t2);
	computeTime(t1,t2,"diffCompute1");
	return sum;
}

// 计算1-1/x+1/x*x⋯
double diffCompute2(int n,double x)
{
	timeb t1,t2;
	double sum=1,temp=1;
	ftime(&t1);
	for(int i=1;i<=n;++i)
	{
		temp *= (-1)/x;
		sum = sum + temp;
	}
	ftime(&t2);
	computeTime(t1,t2,"diffCompute1");
	return sum;
}
