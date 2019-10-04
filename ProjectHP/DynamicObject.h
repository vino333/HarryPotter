#pragma once
#include "GameObject.h"


class DynamicObject :
	public GameObject
{
public:
	DynamicObject(float i, float j, int stepSize);
	~DynamicObject();
	virtual void move(sf::Vector2f step);
	sf::Vector2f mulFVec(const sf::Vector2f& origin, float factor);
	float divIntsAsFloats(int x, int y);
	bool sameDirection(sf::Vector2f other, bool isRight);
	
protected:
	int m_stepSize;
	float m_lastTime;
	int m_imgIndex;
	sf::Vector2f m_position;
	int m_numOfPictures;
	bool m_imageRight;
};

