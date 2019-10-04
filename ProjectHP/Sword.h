#pragma once
#include "Weapon.h"
#include "Factory.h"
class StrongSpell;

class Sword :
	public Weapon
{
public:
	Sword(int i, int j);
	~Sword();

	virtual GameState state() { return SWORDATTAK; }

private:
	static bool m_registerit;
};

