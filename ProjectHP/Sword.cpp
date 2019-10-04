#include "Sword.h"
#include "StrongSpell.h"

Sword::Sword(int i, int j)
	:Weapon("sword", i,j)
{
}

//=============================================================================

Sword::~Sword()
{
}

//=============================================================================

// register to factory
bool Sword::m_registerit = Factory<StaticObject,char,int>::registerit('S',
		[](int i, int j) -> std::shared_ptr<StaticObject> { return std::make_unique<Sword>(i,j); });