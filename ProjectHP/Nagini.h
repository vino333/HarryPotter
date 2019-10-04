#pragma once
#include "StrongEnemy.h"

class Nagini :
	public StrongEnemy
{
public:
	Nagini(int i, int j);
	~Nagini();
	virtual vector<sf::Sprite> getSprites(GameState state)
	{
		return Resources::getSource().getNaginiSprites()[state];
	}
	virtual void move(sf::Vector2f)override;
private:
	static bool m_registerit;
};


