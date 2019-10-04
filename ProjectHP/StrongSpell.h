#pragma once
#include "Spell.h"
#include "General.h"

class StrongSpell :
	public Spell
{
public:
	StrongSpell(sf::Vector2f pos, sf::Vector2f direction);
	~StrongSpell();

private:
	static bool m_registerit;
};

