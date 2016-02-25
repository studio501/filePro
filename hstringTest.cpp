
#include "stdafx.h"
#include "hstringTest.h"
using namespace HS;
void hstringTestMain()
{
	

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
	
	bool s=true;
	int i,k;
	for(i=0;i<MAX_FILE_ROW_LEN;++i)
		initString(T[i]);
	while(s)
	{
		printf("��ѡ��: \n");
		printf("	1.���ļ�(�»��) 2.��ʾ�ļ�����\n");
		printf("	3.������4.ɾ����5.������6.�޸���\n");
		printf("	7.�����ַ���8.�滻�ַ���\n");
		printf("	9.�����˳�0.�����༭\n");
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

//����BookIdx.txt�ļ�����������
void BnoTestMain()
{
	IdxListType idxlist;
	int BookNo;
	int k;
	ifstream fin(idxFile,ios_base::in);
	if (fin.is_open())
	{
		fin>>noidx.last;
		for(k=0;k<noidx.last;++k)
		{
			fin>>buf;
			noidx.item[k]=(char *)malloc((strlen(buf)+1)*sizeof(char));
			strcpy(noidx.item[k],buf);
		}
		fin.close();
	}

	fin.open(bookInfoFile,ios_base::in);
	if(fin.is_open())
	{
		initIdxList(idxlist);
		while(fin.getline(buf,MaxLineLen))
		{
			ExtractKeyWord(BookNo);
			InsIdxList(idxlist,BookNo);
		}
		fin.close();
	}
	ofstream fout(bookIdxFile,ios_base::out);
	if(fout.is_open())
	{
		PutText(idxlist);
		fout.close();
	}
}

//�Թؼ��ּ�����Ŀ Ҫ���Դ˳��� ��Ҫ������BnoTestMain ����BookIdx.txt
//���������ĿҲҪ����BnoTestMain
void bookTestMain()
{
	IdxListType idxlist;//������
	BookListType booklist;//��Ŀ��
	char buf[MaxLineLen+5];//��ǰ��Ŀ��
	HString ch;//�����ַ���
	int BookNo;//���
	Link p;
	int i=0,j=0,k=0,flag=1;
	initString(ch);
	ifstream fin(bookIdxFile,ios_base::in);
	if(fin.is_open())
	{
		fin>>idxlist.last;
		eatlineFromFile(fin);
		for(k=0;k<idxlist.last;++k)
		{
			fin.getline(buf,MaxLineLen);
			i=0;
			while(buf[i]) buf[i++]=tolower(buf[i]);
			initString(idxlist.item[k].key);
			strAssign(idxlist.item[k].key,buf);
			initList_RL(idxlist.item[k].bnolist);
			fin>>i;
			for(j=0;j<i;++j)
			{
				fin>>BookNo;
				makeNode(p,BookNo);
				p->next=NULL;
				appenList(idxlist.item[k].bnolist,p);
			}
			eatlineFromFile(fin);
		}
		fin.close();
	}

	fin.open(bookInfoFile,ios_base::in);
	if(fin.is_open())
	{
		i=0;
		while(fin.getline(buf,MaxLineLen))
		{
			booklist.item[i].bookno=atoi(buf);
			strcpy(booklist.item[i++].bookname,&buf[4]);
		}
		booklist.last=i;
		while(flag)
		{
			cout<<"��������Ŀ�Ĺؼ���(һ��)\n";
			
			cin>>buf;
			
			i=0;
			while(buf[i]) buf[i++]=tolower(buf[i]);
			strAssign(ch,buf);
			i=0;
			do 
			{
				k=strCompare(ch,idxlist.item[i++].key);
			} while (k&&i<=idxlist.last);
			if(!k)
			{
				p=idxlist.item[--i].bnolist.head->next;
				while(p)
				{
					j=0;
					while(j<booklist.last&&p->data!=booklist.item[j].bookno) ++j;
					if(j<booklist.last)
						cout<<booklist.item[j].bookno<<"   "<<booklist.item[j].bookname<<endl;
					p=p->next;
				}
			}
			else
				cout<<"û���ҵ�\n";
			cout<<"��������������1,�˳�����������0:\n";
			
			cin>>flag;
			cin.clear();
			eatline();
		}
	}
}

//