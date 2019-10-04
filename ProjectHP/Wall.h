#pragma once
#include "UnCollectable.h"
#include "Factory.h"
class Wall :
	public UnCollectable
{
public:
	Wall(int i, int j);
	~Wall();

private:
	static bool m_registerit;
};

