
#include "stdafx.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

//0 : 简单工厂模式  1:工厂方法模式 2:抽象工厂模式
#define Factory_Mode 2


#if Factory_Mode==0
enum CoreType{COREA,COREB,COREC};
class SingleCore
{
public:
	virtual void show()=0;
};

class SingleA : public SingleCore
{
public:
	void show(){cout<<"single A"<<endl;}
};

class SingleB : public SingleCore
{
public:
	void show(){cout<<"single B"<<endl;}
};

class SingleC : public SingleCore
{
public:
	void show(){cout<<"single C"<<endl;}
};

class Factory
{
public:
	static SingleCore * createSingleCore(CoreType ctype)
	{
		if(ctype==COREA) return new SingleA();
		else if(ctype==COREB) return new SingleB();
		else if(ctype==COREC) return new SingleC();
		else return NULL;
	}
};
#elif Factory_Mode==1
class SingleCore
{
public:
	virtual void show()=0;
};

class SingleA : public SingleCore
{
public:
	void show(){cout<<"single A"<<endl;}
};

class SingleB : public SingleCore
{
public:
	void show(){cout<<"single B"<<endl;}
};
class SingleC : public SingleCore
{
public:
	void show(){cout<<"single C"<<endl;}
};

class Factory
{
public:
	virtual SingleCore * createSingleCore()=0;
};

class FactoryA : public Factory
{
public:
	SingleCore * createSingleCore()
	{
		return new SingleA();
	}
};

class FactoryB : public Factory
{
public:
	SingleCore * createSingleCore()
	{
		return new SingleB();
	}
};

class FactoryC : public Factory
{
public:
	SingleCore * createSingleCore()
	{
		return new SingleC();
	}
};

#else
class SingleCore
{
public:
	virtual void show()=0;
};

class SingleA : public SingleCore
{
public:
	void show(){cout<<"single A"<<endl;}
};

class SingleB : public SingleCore
{
public:
	void show(){cout<<"single B"<<endl;}
};

class MultiCore
{
public:
	virtual void show()=0;
};

class MultiA : public MultiCore
{
public:
	void show(){cout<<"multi A"<<endl;}
};

class MultiB : public MultiCore
{
public:
	void show(){cout<<"multi B"<<endl;}
};

class Factory
{
	virtual SingleCore * createSingleCore()=0;
	virtual MultiCore * createMultiCore()=0;
};

class FactoryA : public Factory
{
public:
	virtual SingleCore * createSingleCore()
	{
		return new SingleA();
	}
	virtual MultiCore * createMultiCore()
	{
		return new MultiA();
	}
};

class FactoryB : public Factory
{
public:
	virtual SingleCore * createSingleCore()
	{
		return new SingleB();
	}
	virtual MultiCore * createMultiCore()
	{
		return new MultiB();
	}
};

#endif

void testFactory()
{
#if Factory_Mode==0
	auto product = Factory::createSingleCore(COREA);
	product->show();

	auto product1 = Factory::createSingleCore(COREB);
	product1->show();

	auto product2 = Factory::createSingleCore(COREC);
	product2->show();
#elif Factory_Mode==1
	auto fa = new FactoryA();
	auto fb = new FactoryB();
	auto fc = new FactoryC();

	auto p1 = fa->createSingleCore();
	p1->show();

	auto p2 = fb->createSingleCore();
	p2->show();

	auto p3 = fc->createSingleCore();
	p3->show();

#else
	auto fa = new FactoryA();
	auto fb = new FactoryB();

	auto p1 = fa->createSingleCore();
	auto p2 = fa->createMultiCore();
	auto p3 = fb->createSingleCore();
	auto p4 = fb->createMultiCore();
	
	p1->show();
	p2->show();
	p3->show();
	p4->show();

#endif
}
