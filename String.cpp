
#include "stdafx.h"
#include <iostream>
using namespace std;

#include "String.h"

int String::nCharArry;

String::String()
{
	str=NULL;
	_len=0;
	cout<<"in constructor , nCharArray = "<<nCharArry<<endl;
}

String::String(char *p)
{
	_len = strlen(p);
	str = new char[_len+1+1];
	strcpy(str+1,p);
	str[0]=1;
	nCharArry++;
	cout<<"in constructor , nCharArray = "<<nCharArry<<endl;
}

String::String(const String &s)
{
	str=s.str;
	_len = s._len;
	str[0]++;
	cout<<"in constructor , nCharArray = "<<nCharArry<<endl;
}

char & String::operator[](unsigned int idx)
{
	if(idx<0||idx>_len || str==NULL)
	{
		static char nullchar = 0;
		return nullchar;
	}
	if(str[0]>1)
	{
		char *buf = new char[_len+1+1];
		strcpy(buf+1,str+1);
		str[0]--;
		str=buf;
		str[0]=1;
		nCharArry++;
	}
	cout<<"in operator[],nCharArray = "<<nCharArry<<endl;
	return str[1+idx];
}

String & String::operator=(const String &s)
{
	if(!str)
	{
		_len=s._len;
		str=s.str;
		s.str[0]++;
	}
	else
	{
		str[0]--;
		if(!str[0])
		{
			cout<<"will destructor : ";
			for(int i=1;i<_len+1;++i)
				cout<<str[i];
			cout<<endl;
			delete []str;
			nCharArry--;
		}
		_len=s._len;
		str=s.str;
		str[0]++;
	}
	cout<<"in operator=,nCharArray = "<<nCharArry<<endl;
	return *this;
}

String::~String()
{
	if(str)
	{
		str[0]--;
		if(!str[0])
		{
			cout<<"will destructor : ";
			for(int i=1;i<_len+1;++i)
				cout<<str[i];
			cout<<endl;
			delete []str;
			nCharArry--;
		}
	}
	cout<<"in destructor,nCharArray = "<<nCharArry<<endl;
}

const char * String::c_str()
{
	return str+1;
}

