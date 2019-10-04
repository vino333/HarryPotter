#include "StaticObject.h"



StaticObject::StaticObject(string name, int i, int j)
	:GameObject(i, j)
{
	m_image.setTexture(Resources::getSource().getImage(name));
}


StaticObject::~StaticObject()
{
}
