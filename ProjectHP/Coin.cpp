#include "Coin.h"
#include "Resources.h"

//=============================================================================

//coin C-tor
Coin::Coin(int i,int j)
	:Collectable("coin", i, j)
{
}

//=============================================================================

Coin::~Coin()
{
}

//=============================================================================

// registering to factory map
bool Coin::m_registerit = Factory<StaticObject, char, int>::registerit('C',
	[](int i, int j) -> std::shared_ptr<StaticObject> { return std::make_unique<Coin>(i, j); });

