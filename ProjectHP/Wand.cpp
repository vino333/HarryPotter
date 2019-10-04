#include "Wand.h"
#include "StrongSpell.h"


Wand::Wand(int i, int j)
	:Weapon("wand",i,j)
{
}

//=============================================================================

Wand::~Wand()
{
}

//=============================================================================

// registering to factory
bool Wand::m_registerit = Factory<StaticObject,char,int>::registerit('W',
	[](int i, int j) -> std::shared_ptr<StaticObject> { return std::make_unique<Wand>(i,j); });