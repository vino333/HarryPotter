#pragma once
#include "StrongEnemy.h"

class Voldemort: public StrongEnemy
{
public:
	Voldemort(int i, int j);
	~Voldemort();
	virtual vector<sf::Sprite> getSprites(GameState state)
	{
		return Resources::getSource().getVoldemortSprites()[state];
	}

	virtual void move(sf::Vector2f)override;
private:
	static bool m_registerit;
};

