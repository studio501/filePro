
#pragma once
#include <iostream>

class singleton
{
private:
	static singleton *ins;
protected:
	singleton(){}
public:
	static singleton * getInstance(const char *name);
	virtual void show(){std::cout<<"singleton"<<std::endl;}
};

class handle
{
	class wrapped;
	wrapped * working;
public:
	handle();
	void create();
	int read();
	void change(int );
	void destroy();
	~handle();
};