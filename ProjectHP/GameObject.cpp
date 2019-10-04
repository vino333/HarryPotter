#include "GameObject.h"
#include "Resources.h"


// game object c-tor
GameObject::GameObject(float i, float j)
{
	m_currPosition = sf::Vector2f(j*SQUARE_SIZE, i*SQUARE_SIZE);
}


GameObject::~GameObject()
{
}

