#include "EnemySpell.h"
#include "Factory.h"
#include "Harry.h"

//=============================================================================

EnemySpell::EnemySpell(sf::Vector2f pos, sf::Vector2f direction)
	: Spell(pos, direction)
{
	m_images = Resources::getSource().getSpellSprites()[1];
}

//=============================================================================

EnemySpell::~EnemySpell()
{
}

//=============================================================================

bool EnemySpell::m_registerit = Factory<Spell, std::string, sf::Vector2f>::registerit("enemySpell",
	[](sf::Vector2f i, sf::Vector2f j) -> std::shared_ptr<Spell> { return std::make_unique<EnemySpell>(i, j); });

//=============================================================================
