#include "Wall.h"

Wall::Wall(int i, int j)
	:UnCollectable("wall",i,j)
{
}

//=============================================================================

Wall::~Wall()
{
}

//=============================================================================

// registering to factory
bool Wall::m_registerit = Factory<StaticObject,char,int>::registerit('B',
	[](int i, int j) -> std::shared_ptr<StaticObject> { return std::make_unique<Wall>(i,j); });