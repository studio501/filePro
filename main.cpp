// fileTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

#include "DSList.h"
#include <string>

#include "commonFunc.h"

using namespace std;
//int fileFunc(int m = 2);
//void testListMain();
//void testLinkListMain();
//void testStackMain();
//void mazeTest();
void queueTestMain();
void lQueueTestMain();

void sstringTestMain();
void hstringTestMain();
void lstringTestMain();

int _tmain(int argc, _TCHAR* argv[])
{
	/*cout<<diffCompute1()<<endl;
	cout<<diffCompute2()<<endl;*/
	//testLinkListMain();
	//testStackMain();
	//mazeTest();
	/*queueTestMain();
	lQueueTestMain();
	sstringTestMain();
	hstringTestMain();*/
	lstringTestMain();
	system("pause");
	return 0;
}
