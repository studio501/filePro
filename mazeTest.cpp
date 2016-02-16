
#include "stdafx.h"

#include "mazeTest.h"

#include <iostream>
using namespace std;

//Êä³öÃÔ¹¬µÄ½â
void print_m()
{
	for(int i=0;i<g_x;++i)
	{
		for(int j=0;j<g_y;++j)
			printf("%3d",m[i][j]);
		printf("\n");
	}
}

void mazeTest()
{
	cout<<"mazeTest";
}

