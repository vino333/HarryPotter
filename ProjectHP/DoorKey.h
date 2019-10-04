#pragma once
#include "Collectable.h"
#include "Factory.h"
class StrongSpell;

class DoorKey:public Collectable
{
public:
	DoorKey(int i, int j);
	~DoorKey();

private:
	static bool m_registerit;
};

