#pragma once
#include "Collectable.h"
#include "Factory.h"
class Coin:public Collectable
{
public:
	Coin(int i,int j);
	~Coin();

private:
	static bool m_registerit;
};

