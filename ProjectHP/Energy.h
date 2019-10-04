#pragma once
#include "Collectable.h"
#include "Factory.h"

class Energy :
	public Collectable
{
public:
	Energy(int i, int j);
	~Energy();

private:
	static bool m_registerit;
};

