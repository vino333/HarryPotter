#include "Nagini.h"

//=============================================================================

Nagini::Nagini(int i, int j) :StrongEnemy(i, j)
{
	stepTo[2] = { 0,1 };
	stepTo[3] = { 0,-1 };

	m_numOfPictures = 6;

	m_images = Resources::getSource().getNaginiSprites()[WALK];
}

//=============================================================================

Nagini::~Nagini()
{
}

//=============================================================================

// register to factory
bool Nagini::m_registerit = Factory<Enemy, char, int>::registerit('N',
	[](int i, int j) -> std::shared_ptr<Enemy> { return std::make_unique<Nagini>(i, j); });

//=============================================================================

// moving nagini
void Nagini::move(sf::Vector2f step)
{
	DynamicObject::move(step);
}