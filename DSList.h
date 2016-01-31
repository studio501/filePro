//
#ifndef _DSLIST__H_
#define _DSLIST__H_

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;
template<typename T>
struct LNode
{
	T data;
	LNode<T> *next;
};

template<class T1,class T2>
T1 computeSum(T1 a,T2 b)
{
	return (a+b);
}

template <class Array_Type>
void bubble_sort(Array_Type *arr,int len)
{
	int i,j;
	Array_Type temp;
	for (i=0;i<len;++i)
	{
		for (j=i+1;j<len;++j)
		{
			if (arr[i]>arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

template<class Array_Type>
void print_arr(Array_Type *arr,int len,bool isBefore = true)
{
	using namespace std;
	if (isBefore)
	{
		cout<<"Array before:\n";
	}
	else cout<<"Array after:\n";
	for(int i=0;i<len;++i)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

template<class Array_Type>
void test_arr(Array_Type *arr,int arrLen)
{
	//int arrLen = sizeof(arr)/sizeof(Array_Type);
	print_arr(arr,arrLen);
	bubble_sort(arr,arrLen);
	print_arr(arr,arrLen,false);
}


template<class T>
class TemplateTest
{
public:
	TemplateTest();
	~TemplateTest();

	bool bFunction(const T &data );
	void printTemplateTest();

private:
	std::vector<T> m_data;

};



class NoTemplate
{
public:
	NoTemplate(){};
	~NoTemplate(){};
	template<class T>
	void printSomething(T a);
};

template<class T>
void NoTemplate::printSomething(T a)
{
	std::cout<<a<<" ";
}

template<class T,int maxSize=1000>
class testQueue
{
	struct QueueItem
	{
		T item;
		QueueItem * next;
		QueueItem()
			:next(NULL)
		{

		}
	};
public:
	testQueue():m_size(0),first(NULL),last(NULL){};
	~testQueue(){};
	bool push(T qItem);
	bool get(T &qItem);
	int size(){return m_size;}
	bool empty(){return first==NULL;}
	void visit();
private:
	QueueItem *first,*last;
	int m_size;
};

class StringOperate
{
	
public:
	static string & ltrim(string &str);
	static string & rtrim(string &str);

	static string & toUpper(string &str);
	static string & toLower(string &str);

	template<class T>
	static string toString(T var,bool sign=false);
};


#include "DSList.hpp"
#endif // !_DSLIST__H_
