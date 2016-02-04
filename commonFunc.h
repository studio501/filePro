#ifndef COMMON_FUNC__H__
#define COMMON_FUNC__H__

// c1.h (程序名)
//#include<string.h>
//#include<ctype.h>
//#include<malloc.h> // malloc()等
//#include<limits.h> // INT_MAX等
//#include<stdio.h> // EOF(=^Z或F6),NULL
//#include<stdlib.h> // atoi()
//#include<io.h> // eof()
//#include<math.h> // floor(),ceil(),abs()
//#include<process.h> // exit()
//#include<iostream.h> // cout,cin

#include <stdio.h>
#include <sys/timeb.h>
#include <math.h>
#include <string>
#include <iostream>
using namespace std;

//计算时间差
long computeTime(timeb t1,timeb t2,const char * flagName="Default")
{
	long temp = abs((t1.time*1000+t1.millitm) - (t2.time*1000+t2.millitm));
	cout<<"time in"<<flagName<<" spend "<<temp<<" mini seconds"<<endl;
	return temp;
}

// 计算1-1/x+1/x*x⋯
double diffCompute1(int n=1234,double x= 1000)
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
double diffCompute2(int n=1234,double x= 1000)
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

template<class T>
T stringToNum(const string &str)
{
	istringstream iss(str);
	T num;
	iss>>num;
	return num;
}

#endif // !COMMON_FUNC__H__
