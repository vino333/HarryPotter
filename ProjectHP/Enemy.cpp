#include "Enemy.h"
#include "Board.h"
#include "GraphixState.h";

//=============================================================================

//c-tor
Enemy::Enemy(int i, int j,int power)
	:HumanObject(i,j,1), m_originPlace(j, i), m_currentTime(0), m_stepSize(0),
m_shootTime(0),m_power(power){}

//=============================================================================

//d-tor
Enemy::~Enemy()
{
}

//=============================================================================

//get the peviouse time to help the move control function
float Enemy::getPreviousTime()
{
	return m_currentTime;
}

//=============================================================================

//save the time to help the move control function
void Enemy::setPreviousTime(float currentTime)
{
	m_currentTime = currentTime;
}

//=============================================================================

//return if the enemy is to far from his start point
bool Enemy::outOfArea()
{
	sf::Vector2i currentPlace = ((sf::Vector2i)getPosition()) / SQUARE_SIZE;

	return abs(currentPlace.x - m_originPlace.x) > m_range || abs(currentPlace.y - m_originPlace.y) > m_range;
}

//=============================================================================

//does the enemy move algorithem
sf::Vector2f Enemy::moveControl()
{
	if ((Resources::getSource().getTime().asSeconds() - getPreviousTime()) >= m_stepSize)
	{
		m_direction = m_spellCasted&&typeid(m_graphix) == typeid(WalkState)? STAND: Direction(rand() % 4);
		m_stepSize = rand() % 3;
		m_currentStep = getStepTo(m_direction);
		setPreviousTime(Resources::getSource().getTime().asSeconds());
	}

	setCurrImageDir(m_direction);

	move(m_currentStep);

	return m_currentStep;
}

//=============================================================================

//return if its a good time to shoot' to avoid to many shooting
bool Enemy::spellTime()
{
	if (Resources::getSource().getTime().asSeconds() - m_lastTime > 3)
	{
		m_lastTime = Resources::getSource().getTime().asSeconds();
		return true;
	}
	return false;
}

//=============================================================================

//return the direction vector for harry
sf::Vector2f Enemy::direction2Harry()
{
	if (findDistance(*m_harryPlace) < 10 && sameDirection(*m_harryPlace, m_imageRight))
		return findDirection(*m_harryPlace);

	return getStepTo(getCurrDir());
}

//=============================================================================

//return if harry is in the shooting range
bool Enemy::AbleToShoot()
{
	return findDistance(*m_harryPlace) < 10 && sameDirection(*m_harryPlace, m_imageRight);
}
