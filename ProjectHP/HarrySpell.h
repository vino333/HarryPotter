#pragma once
#include "Spell.h"
class StrongSpell;

class HarrySpell :public Spell
{
public:
	HarrySpell(sf::Vector2f pos, sf::Vector2f direction);
	~HarrySpell();

private:
	static bool m_registerit;
};

