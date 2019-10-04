#pragma once
#include "GameObject.h"

class StaticObject :
	public GameObject
{
public:
	StaticObject(string name, int i, int j);
	~StaticObject();
};

