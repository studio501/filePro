#include "stdafx.h"

#include <iostream>

#include <fstream>
#include <stdio.h>
#include <string>

#include "testStack.h"

using namespace std;

void testStackMain()
{
	SqStack S;
	SElemType e;
	initStack(S);
	for(int j=1;j<=12;++j)
		pushStack(S,j);
	stackTraverse(S,print_stack);

	popStack(S,e);
	cout<<e<<endl;

	for(int i=0;i<3;++i)
	{
		popStack(S,e);
		cout<<e<<" ";
		if(i==2) cout<<endl;
	}

	getTop(S,e);
	cout<<e<<endl;

	stackTraverse(S,print_stack);
	clearStack(S);
	destroyStack(S);

	conversion_unit();

	conversion_unit(456,9);
	conversion_16(256);

	check_bracket();
	check_bracket("bracket.txt",2);
	check_bracket("bracket.txt",3);

	lineEdit();
}

void testMaze()
{

}





