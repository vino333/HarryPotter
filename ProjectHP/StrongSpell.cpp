#include "StrongSpell.h"
#include "Factory.h"
#include "StrongEnemy.h"
#include "WeakEnemy.h"

//=============================================================================

// strong spell c-tor
StrongSpell::StrongSpell(sf::Vector2f pos, sf::Vector2f direction)
	:Spell(pos, direction)
{
	m_images = Resources::getSource().getSpellSprites()[2];
}

//=============================================================================

StrongSpell::~StrongSpell()
{
}

//=============================================================================

// register to factory
bool StrongSpell::m_registerit = Factory<Spell, std::string, sf::Vector2f>::registerit("Sspell",
	[](sf::Vector2f i, sf::Vector2f j) -> std::shared_ptr<Spell>
{return std::make_unique<StrongSpell>(i, j); });



