#include "Malfoy.h"

//=============================================================================

Malfoy::Malfoy(int i, int j) :WeakEnemy(i, j)
{
	m_numOfPictures = 14;

	m_images = Resources::getSource().getMalfoySprites()[WALK];
}

//=============================================================================

Malfoy::~Malfoy()
{
}

//=============================================================================

// registering to factory
bool Malfoy::m_registerit = Factory<Enemy, char, int>::registerit('M',
	[](int i, int j) -> std::shared_ptr<Enemy> { return std::make_unique<Malfoy>(i, j); });

//=============================================================================

// moving malfoy
void Malfoy::move(sf::Vector2f step)
{
	DynamicObject::move(step);

	m_imageRight ? m_image.setTextureRect(sf::IntRect(90, 0, -90, 90)) :
		m_image.setTextureRect(sf::IntRect(0, 0, 90, 90));
}