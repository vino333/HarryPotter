#pragma once
#include <iostream>
#include "Level.h"
#include "Harry.h"

class Controller
{
public:
	Controller(int, sf::RenderWindow &window);
	~Controller();
	void run();
	void endGame(sf::RenderWindow&);

private:
	
	int m_numOfLvel;
	sf::RenderWindow &m_window;
	int m_playerEnergy;
	sf::Sprite m_lose;
	sf::Sprite m_win;
};

