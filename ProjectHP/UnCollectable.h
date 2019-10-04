#pragma once
#include "StaticObject.h"
class UnCollectable:public StaticObject
{
public:
	UnCollectable(std::string, int i,int j);
	~UnCollectable();
};

