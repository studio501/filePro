// primerCpp_v3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class Object {
public:
	virtual ~Object(){};
	virtual string isA(){return "a";};
	Object(){};
protected:
	string _isA;
private:
	Object(string s)
		:_isA(s)
	{

	}
};

class ConcreteBase{
	
public:
	
	ConcreteBase(){};
	ConcreteBase(int a)
	{
		cout<<a<<endl;

		_id=a;
		cout<<_id<<endl;
	};
	virtual void print(ostream&){};
	static int Object_count(){};
protected:
	int _id;
	static int _object_count;
};

class c1 : public ConcreteBase{
public:
	c1(int val)
	{
		ConcreteBase::ConcreteBase(val);
	}
};
int _tmain(int argc, _TCHAR* argv[])
{
	c1 * p = new c1(101);
	system("pause");
	return 0;
}

