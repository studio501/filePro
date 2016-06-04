
#pragma once
#include "singleton.h"

class singletonA : public singleton
{
	friend class singleton;	
public:
	void show(){printf("singletonA\n");}
private:
	singletonA(){};
};
