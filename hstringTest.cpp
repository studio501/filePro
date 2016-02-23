
#include "stdafx.h"
#include "hstringTest.h"

void hstringTestMain()
{
	using namespace HS;

	int i;
	char c,*p="Good bye!",*q="Good luck!";
	HString t,s,r;
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

void apply_string()
{
	using namespace HS;
	bool s=true;
	int i,k;
	for(i=0;i<MAX_FILE_ROW_LEN;++i)
		initString(T[i]);
	while(s)
	{
		printf("请选择: \n");
		printf("	1.打开文件(新或旧) 2.显示文件内容\n");
		printf("	3.插入行4.删除行5.拷贝行6.修改行\n");
		printf("	7.查找字符串8.替换字符串\n");
		printf("	9.存盘退出0.放弃编辑\n");
		cin>>k;
		eatline();
		switch (k)
		{
		case 1:
			Open();
			break;
		case 2:
			List();
			break;
		case 3:
			Insert();
			break;
		case 4:
			Delete();
			break;
		case 5:
			Copy();
			break;
		case 6:
			Modify();
			break;
		case 7:
			Search();
			break;
		case 8:
			Replace();
			break;
		case 9:
			Save();
			break;
		case 0:
			s=false;
			break;
		default:
			s=false;
			break;
		}
	}
}