#pragma once
#include "StaticObject.h"

class Collectable :
	public StaticObject
{
public:
	Collectable(std::string, int i, int j);
	~Collectable();
};

