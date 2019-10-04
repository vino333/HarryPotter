#include "DoorKey.h"

//=============================================================================

DoorKey::DoorKey(int i, int j)
	:Collectable("doorKey", i,j)
{
}

//=============================================================================

DoorKey::~DoorKey()
{
}

//=============================================================================

// registering to factory
bool DoorKey::m_registerit = Factory<StaticObject,char,int>::registerit('K',
	[](int i, int j) -> std::shared_ptr<StaticObject> { return std::make_unique<DoorKey>(i,j); });

