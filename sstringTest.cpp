
#include "stdafx.h"
#include "sstringTest.h"

void sstringTestMain()
{
	SString a;
	strAssign(a,"Hello_world");
	strPrint(a);

	SString t,s1,s2;
	strCopy(s1,a);
	strPrint(s1);
	strAssign(s2,"Hello_nerd");
	cout<<strCompare(s1,s2)<<endl;
	concatStr(t,s1,s2);
	strPrint(t);
	
	subString(s2,t,14,4);
	strPrint(s2);

	strDelete(t,2,5);
	strPrint(t);

	cout<<strInsert(s2,strLength(s2)/2,t);
	strPrint(s2);
}