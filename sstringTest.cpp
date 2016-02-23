
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

	replaceStr(s2,t,s1);
	strPrint(s2);
}

void testKMP()
{
	int i,*p;
	SString s1,s2;
	strAssign(s1,"aaabaaaab");
	strAssign(s2,"aaaab");
	p=(int*)malloc((strLength(s2)+1)*sizeof(int));
	get_next(s2,p);
	cout<<"next [] is :\n";
	for(i=1;i<=strLength(s2);++i)
		cout<<*(p+i)<<" ";
	cout<<endl;
	i=index_KMP(s1,s2,1,p);
	if(i) cout<<"match succeed in pos "<<i<<endl;
	else cout<<"match failed\n";

	get_nextval(s2,p);
	cout<<"nextval [] is :\n";
	for(i=1;i<=strLength(s2);++i)
		cout<<*(p+i)<<" ";
	cout<<endl;
	cout<<"match succeed with nextval in pos "<<index_KMP(s1,s2,1,p)<<endl;
}