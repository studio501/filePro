#include "stdafx.h"
#include "DSList.h"

using namespace std;
template<class T>
TemplateTest<T>::TemplateTest()
{

}

template<class T>
TemplateTest<T>::~TemplateTest()
{

}

template<class T>
bool TemplateTest<T>::bFunction(const T &data)
{
	m_data.push_back(data);
	return true;
}

template<class T>
void TemplateTest<T>::printTemplateTest()
{
	using namespace std;
	for (int i=0;i<m_data.size();++i)
	{
		cout<<m_data[i]<<" ";
	}
	cout<<endl;
}

template<class T,int maxSize>
bool testQueue<T,maxSize>::push(T qItem)
{
	if (m_size>maxSize) 
	{
		std::cout<<"out of max size "<<maxSize<<endl;
		return false;
	}
	QueueItem *t = new QueueItem();
	t->item = qItem;
	
	if(!first)
	{
		first=t;
		t->next=NULL;
		last=first;
	}
	else
	{
		last->next=t;
		t->next=NULL;
		last=t;
	}
	++m_size;
	return true;
}

template<class T,int maxSize>
bool testQueue<T,maxSize>::get(T &qItem)
{
	if(empty()) return false;

	QueueItem *t = first;
	first = first->next;
	qItem = t->item;
	delete t;
	--m_size;
	return true;
}

template<class T,int maxSize>
void testQueue<T,maxSize>::visit()
{
	if(empty()) return;
	QueueItem *t = first;
	while(t!=last)
	{
		std::cout<<t->item<<" ";
		t = t->next;
	}
}

string & StringOperate::ltrim(string &str)
{
	cout<<"\nbefore ltrim\n"<<str<<endl;
	string::iterator pos = str.begin();
	for(;(pos!=str.end()) &&(*pos==' '||*pos=='\t');pos++);
	if (pos!=str.begin()) str.erase(str.begin(),pos);

			
	return str;
}

string & StringOperate::rtrim(string &str)
{
	cout<<"\nbefore rtrim\n"<<str<<"@"<<endl;
	string::reverse_iterator pos = str.rbegin();
	for(;(pos!=str.rend() && (*pos==' '||*pos=='\t'));pos++);
	if(pos!=str.rbegin()) str.erase(pos.base(),str.end());
	return str;
}


string & StringOperate::toUpper(string &str)
{
	cout<<"\nbefore toUpper\n"<<str<<endl;
	
	for(auto pos = str.begin();pos!=str.end();++pos)
		*pos = toupper(*pos);
	return str;
}

string & StringOperate::toLower(string &str)
{
	cout<<"\nbefore toLower\n"<<str<<endl;
	for(auto pos=str.begin();pos!=str.end();++pos)
	{
		*pos = tolower(*pos);
	}
	return str;
}

template<class T>
string StringOperate::toString(T var,bool sign/* =false */)
{
	ostringstream buffer;
	if(sign) buffer<<showpos;
	buffer<<fixed<<var;
	return buffer.str();
}