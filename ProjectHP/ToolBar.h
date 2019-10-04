#pragma once
#include "General.h"
#include "EnergyRect.h"
#include "Resources.h"
class ToolBar
{
public:
	ToolBar();
	~ToolBar();
	void setSideBar();
	void drawToolBar(sf::RenderWindow&window, sf::Vector2f,int,int,int);
	void drawEnergy(sf::RenderWindow&window, sf::Vector2f,int);

private:
	vector<EnergyRect>m_energyContainer;

	sf::Text m_weaponText;
	sf::Text m_energyText;
	sf::RectangleShape topBar;
	sf::RectangleShape leftBar;
	sf::Text m_scoreText;
	sf::Text m_scoreNumber;
	sf::Text m_keysText;
	sf::Text m_keysNum;
	sf::Sprite frame;
};

