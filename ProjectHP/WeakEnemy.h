#pragma once
#include "Enemy.h"
#include "Harry.h"
class StrongSpell;

class WeakEnemy :
	public Enemy
{
public:
	WeakEnemy(int i, int j);
	~WeakEnemy();
};

