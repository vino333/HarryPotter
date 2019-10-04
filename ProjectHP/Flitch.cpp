#include "Flitch.h"


// c-tor
Flitch::Flitch(int i, int j) :WeakEnemy(i,j)
{
	stepTo[0] = { 1,0 };
	stepTo[1] = { -1,0 };

	m_numOfPictures = 9;

	m_images = Resources::getSource().getFlitchSprites()[WALK];
}

//=============================================================================

Flitch::~Flitch(){}

//=============================================================================

// registering to factory
bool Flitch::m_registerit = Factory<Enemy,char,int>::registerit('F',
	[](int i, int j) -> std::shared_ptr<Enemy> { return std::make_unique<Flitch>(i,j); });

//=============================================================================

// moving filch
void Flitch::move(sf::Vector2f step)
{
	DynamicObject::move(step);

	m_imageRight ? m_image.setTextureRect(sf::IntRect(0, 0, 80, 80)) :
		m_image.setTextureRect(sf::IntRect(80, 0, -80, 80));
}

