#pragma once
#include "DynamicObject.h"

class GraphixState;
class MoveState;

//=============================================================================

class HumanObject :
	public DynamicObject
{
public:
	HumanObject(int i, int j, int stepSize);
	virtual ~HumanObject();

	bool getIfDead() { return(m_energy <= 0); };
	void setCurrImageDir(Direction direction);
	void setState();
	void AboutToShoot();
	bool timeToShoot();
	sf::Vector2f getStepTo(Direction direction) { return stepTo[direction]; }
	float findDistance(sf::Vector2f other);
	sf::Vector2f findDirection(sf::Vector2f);
	virtual shared_ptr<Spell> shootSpell(sf::Vector2f, std::string, sf::Vector2f direction);
	void setCurrDir(Direction dir) { m_currDirection = dir; }
	Direction getCurrDir() { return m_currDirection; }
	void setGraphixState(GameState state);
	void graphixEnter();
	string graphixHandleInput(GameState input);
	virtual vector<sf::Sprite> getSprites(GameState state)=0 ;
	bool spellLoaded(bool newSet);
	virtual void setDir(Direction dir){ m_imageRight = dir == RIGHT || dir == DOWN; }

protected:
	bool m_spellCasted;
	int m_energy;
	int m_state;
	std::vector<sf::Vector2f> stepTo = { { 0,1 },{ 0,-1 },{ 1,0 },{ -1,0 },{ 0,0 },{ 0,0 },{ 0,0 } };
	Direction m_currDirection;
	vector<sf::Sprite> m_images;
	bool m_loaded;

	shared_ptr<GraphixState> m_graphix;
	float m_switchTime;
};



