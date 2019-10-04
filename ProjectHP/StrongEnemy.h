#pragma once
#include "Enemy.h"
#include "Harry.h"

class StrongSpell;

class StrongEnemy :
	public Enemy
{
public:
	StrongEnemy(int i, int j);
	~StrongEnemy();

    static int getNumOfStrong(){ return m_numOfStorng; }

private:
	static bool m_registerit;
	static int m_numOfStorng;
};

