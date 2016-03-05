// fileTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
//#include <cmath>
#include <sstream>
#include <string>

#include "sstringTest.h"
using namespace std;



void toolMain(int argc, _TCHAR* argv[])
{
	const char *filename="prince_log_20160224_132343.txt";
	ifstream fin(filename,ios_base::in);
	char temp[MAX_STR_LEN];
	if(fin.is_open())
	{
		SString T;
		while(fin.getline(temp,MAX_STR_LEN))
		{
			strAssign(T,temp);
			strPrint(T);
		}		
	}
	else
	{
		cout<<"can't open "<<filename<<endl;
		system("pause");
	}
}

