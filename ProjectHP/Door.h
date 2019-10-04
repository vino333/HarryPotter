#pragma once
#include "UnCollectable.h"
#include "Factory.h"
class StrongSpell;


class Door :
	public UnCollectable
{
public:
	Door(int i, int j);
	~Door();
	bool openDoor(int);

private:
	static bool m_registerit;
};

