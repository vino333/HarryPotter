#include "WeakEnemy.h"
#include "StrongSpell.h"

//=============================================================================

// weak enemy c-tor
WeakEnemy::WeakEnemy(int i, int j)
	:Enemy(i,j,10)
{
	m_range = 4;
}

//=============================================================================

WeakEnemy::~WeakEnemy()
{
}

