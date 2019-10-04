#include "DynamicObject.h"

//=============================================================================

//c-tor
DynamicObject::DynamicObject(float i, float j, int stepSize)
	:GameObject(i,j), m_stepSize(stepSize),m_lastTime(0),m_imgIndex(0)
{
}

//=============================================================================

//d-tor
DynamicObject::~DynamicObject()
{
}

//=============================================================================

// moving a dynamic object
void DynamicObject::move(sf::Vector2f step)
{
	float factor(pow(3,-1));

	sf::Vector2f stepToDo = sf::Vector2f(mulFVec(mulFVec(step , m_stepSize),factor));

	setPosition(getPosition() + stepToDo);

	m_position = getPosition();
}

//=============================================================================

//do multyple a sf::vector2f with a float 
sf::Vector2f DynamicObject::mulFVec(const sf::Vector2f & origin, float factor)
{
	sf::Vector2f vector = origin;

	vector.x *= factor;
	vector.y *= factor;

	return vector;
}

//=============================================================================

//return if the enemy is in the direction the object turn to and in a small enough angel
bool DynamicObject::sameDirection(sf::Vector2f other, bool isRight)
{
	sf::Vector2f self = m_position;

	return((other.x > self.x && isRight) ||
		(other.x < self.x && !isRight)) &&
		abs(other.x - self.x) > abs(other.y - self.y);
}

