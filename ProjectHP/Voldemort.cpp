#include "Voldemort.h"

// voldemort c-tor
Voldemort::Voldemort(int i, int j) :StrongEnemy(i, j)
{
	m_numOfPictures = 3;

	m_images = Resources::getSource().getVoldemortSprites()[WALK];
}

//=============================================================================

Voldemort::~Voldemort()
{
}

//=============================================================================

// registering to factory
bool Voldemort::m_registerit = Factory<Enemy, char, int>::registerit('V',
	[](int i, int j) -> std::shared_ptr<Enemy> { return std::make_unique<Voldemort>(i, j); });

//=============================================================================

// moving voldemort
void  Voldemort::move(sf::Vector2f step)
{
	DynamicObject::move(step);

	m_imageRight ? m_image.setTextureRect(sf::IntRect(49, 0, -50, 49)) :
		m_image.setTextureRect(sf::IntRect(0, 0, 45, 49));
}