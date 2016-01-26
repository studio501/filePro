// primerCpp_v3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

const int Name_Limit = 20;
struct employer
{
	char name[Name_Limit];
	int gender;
	float weight;
	float height;
	int age;
};
const char * file = "employer.data";
int _tmain(int argc, _TCHAR* argv[])
{
	ifstream fin;
	fin.open(file,ios_base::in | ios_base::binary);
	if(fin.is_open())
	{

	}
	//fin.open()
	system("pause");
	return 0;
}

