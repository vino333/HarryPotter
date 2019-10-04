#pragma once
#include "Collectable.h"
class Weapon:public Collectable
{
public:
	Weapon(std::string, int i, int j);
	~Weapon();
	virtual GameState state() = 0;
};

