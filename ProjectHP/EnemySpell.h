#pragma once
#include "Spell.h"
class StrongSpell;

class EnemySpell:public Spell
{
public:
	EnemySpell(sf::Vector2f pos, sf::Vector2f direction);
	~EnemySpell();

private:
	static bool m_registerit;

};

