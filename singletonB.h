
#pragma once
#include "singleton.h"

class singletonB : public singleton
{
	friend class singleton;	
public:
	void show(){printf("singletonB\n");}
private:
	singletonB(){};
};