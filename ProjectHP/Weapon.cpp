#include "Weapon.h"

// weapon c-tor
Weapon::Weapon(std::string name, int i, int j)
	:Collectable(name,i,j)
{
}

//=============================================================================

Weapon::~Weapon()
{
}
