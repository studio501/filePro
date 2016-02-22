
#include "stdafx.h"
#include "lstringTest.h"

void lstringTestMain()
{
	using namespace LS;

	int i;
	char c,*p="Good bye!",*q="Good luck!";
	LString t,s,r;
	initString(t);
	initString(s);
	initString(r);

	strAssign(t,p);
	strPrint(t);

	strAssign(s,q);
	cout<<strCompare(s,t)<<endl;

	concatStr(r,t,s);
	strPrint(r);

	replaceStr(r,t,s);
	strPrint(r);

	strDelete(r,1,5);
	strPrint(r);
}