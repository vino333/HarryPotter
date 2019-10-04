#pragma once
#include "WeakEnemy.h"
class Flitch :
	public WeakEnemy
{
public:
	Flitch(int i, int j);
	~Flitch();
	virtual vector<sf::Sprite> getSprites(GameState state) 
	{ return Resources::getSource().getFlitchSprites()[state]; }
	virtual void move(sf::Vector2f)override;

private:
	static bool m_registerit;
};

