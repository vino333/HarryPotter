#include "StrongEnemy.h"
#include "StrongSpell.h"


StrongEnemy::StrongEnemy(int i, int j)
	:Enemy(i,j,20)
{
	m_range = 8;
	m_numOfStorng++;// strong enemy created
}

//=============================================================================

StrongEnemy::~StrongEnemy()
{
	m_numOfStorng--;// strong enemy died
}

//=============================================================================

int StrongEnemy::m_numOfStorng = 0;// number of strong enemies

