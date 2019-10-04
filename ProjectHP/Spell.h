#pragma once#
#include "DynamicObject.h"
class Spell:public DynamicObject
{
public:
	Spell(sf::Vector2f pos, sf::Vector2f direction);
	~Spell();
	void setIndex(int i) { m_spellIndex = i; }
	int getIndex() { return m_spellIndex; }
	virtual void moveSpell();
	bool getIfTimeUp() { return m_timeUp; }
	void timeUp() { m_timeUp = true; }
	
protected:
	int m_spellIndex;
	sf::Vector2f m_direction;
	vector<sf::Sprite> m_images;
	bool m_timeUp;
};

