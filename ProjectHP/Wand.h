#pragma once
#include "Weapon.h"
#include "Factory.h"

class StrongSpell;

class Wand :
	public Weapon
{
public:
	Wand(int i, int j);
	~Wand();

	virtual GameState state() { return WANDATTAK; }

private:
	static bool m_registerit;
};

