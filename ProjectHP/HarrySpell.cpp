#include "HarrySpell.h"
#include "Factory.h"
#include "StrongEnemy.h"
#include "WeakEnemy.h"
#include "StrongSpell.h"

//=============================================================================

HarrySpell::HarrySpell(sf::Vector2f pos, sf::Vector2f direction)
	:Spell(pos, direction) 
{
	m_images = Resources::getSource().getSpellSprites()[0];
}

//=============================================================================

HarrySpell::~HarrySpell()
{
}

//=============================================================================

// registering to factory
bool HarrySpell::m_registerit = Factory<Spell, std::string, sf::Vector2f>::registerit("spell",
	[](sf::Vector2f i, sf::Vector2f j) -> std::shared_ptr<Spell> 
{return std::make_unique<HarrySpell>(i, j); });
