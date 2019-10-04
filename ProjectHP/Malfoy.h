#pragma once
#include "WeakEnemy.h"

class Malfoy :
	public WeakEnemy
{
public:
	Malfoy(int i, int j);
	~Malfoy();
	virtual vector<sf::Sprite> getSprites(GameState state)
	{
		return Resources::getSource().getMalfoySprites()[state];
	}
	virtual void move(sf::Vector2f)override;
private:
	static bool m_registerit;
};


