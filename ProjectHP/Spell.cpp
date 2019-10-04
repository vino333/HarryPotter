#include "Spell.h"


// spell c-tor
Spell::Spell(sf::Vector2f pos,sf::Vector2f direction)
	:DynamicObject(0,0, 8),m_timeUp(false)
{	
	m_numOfPictures = 10;

	m_image.setPosition(pos);
	m_direction = direction;	
}

//=============================================================================

Spell::~Spell()
{
}

//=============================================================================

// moving the spell
void Spell::moveSpell()
{
	if (Resources::getSource().getTime().asSeconds() - m_lastTime >0.075)
	{
		sf::Vector2f pos = getPosition();
		m_image = m_images[m_imgIndex];
		m_image.setPosition(pos);
		m_imgIndex++;		
		m_imgIndex %= m_numOfPictures;

		if (m_imgIndex == 0)
			m_timeUp = true;

		m_lastTime = Resources::getSource().getTime().asSeconds();
	}

	move(m_direction);
}
