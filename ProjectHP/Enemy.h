#pragma once
#include "HumanObject.h"
#include "Factory.h"

class Board;

class Enemy:public HumanObject
{
public:
	Enemy(int i, int j,int power);
	~Enemy();
	
	float getPreviousTime();
	void setPreviousTime(float currentTime);
	void setHarryPlace(sf::Vector2f *harryPlace) { m_harryPlace = harryPlace; }
	bool outOfArea();
	void setStepSize(int stepSize) { m_stepSize = stepSize; }
	int getStepSize() { return m_stepSize; }
	sf::Vector2f direction2Harry();
	sf::Vector2f moveControl();
	virtual bool spellTime();
	bool AbleToShoot();
	void setShootTime(float shootTime) { m_shootTime = shootTime; }
	float getShootTime() { return m_shootTime; }
	void reduceEnergy(int energy) { m_energy -= energy; }

protected:
	float m_currentTime;
	sf::Vector2f m_originPlace;
	int m_stepSize;
	sf::Vector2f m_currentStep;
	sf::Vector2f *m_harryPlace;
	float m_shootTime;
	int m_power;
	int m_range;
	Direction m_direction;
};


