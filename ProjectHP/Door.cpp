#include "Door.h"
//#include "Factory.h"


Door::Door(int i, int j)
	:UnCollectable("door", i,j)
{}

//=============================================================================

Door::~Door()
{
}

//=============================================================================

// registering to factory
bool Door::m_registerit = Factory<StaticObject,char,int>::registerit('D',
	[](int i, int j) -> std::shared_ptr<StaticObject> { return std::make_unique<Door>(i,j); });

//=============================================================================

// checking if can open the door
bool Door::openDoor(int numOfKeys)
{
	if (numOfKeys >= 3)
	{
		Resources::getSource().playOpenDoor();
		return true;
	}
	else
		return false;
};