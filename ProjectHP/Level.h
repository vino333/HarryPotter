#pragma once
#include "Harry.h"
#include "Board.h"

const int WIN_HEIGHT = 680;
const int WIN_WIDTH = 1200;

class Level
{
public:
	Level(sf::RenderWindow&window,int numOfLevel);
	~Level();
	void run();
	Direction getMoveFromUser();
	void display(sf::View& view);
	void handleEventFromUser();
	int getHarryEnergy() { return m_board.getHarryEnergy(); }

private:
	Board m_board;
	sf::RenderWindow& m_window;
	sf::RenderTexture  m_texture;
	sf::Vector2f viewPos;
	bool m_harryShoot;
		
};

