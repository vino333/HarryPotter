#include "Controller.h"

// controller c-tor
Controller::Controller(int numOfLevel, sf::RenderWindow &window)
	:m_numOfLvel(numOfLevel), m_window(window),m_playerEnergy(1)
{
	// setting texture of win and lose images
	m_lose .setTexture(Resources::getSource().getImage("lose"));
	m_win.setTexture(Resources::getSource().getImage("win"));
}

//=============================================================================

Controller::~Controller()
{
}

//=============================================================================

// main game loop
void Controller::run()
{
	// while player has enough energy and levels didnt finish
	while (m_window.isOpen() && m_playerEnergy>0 && m_numOfLvel <= NUM_OF_LEVELS)
	{
		Level level(m_window, m_numOfLvel);// creating new level
		level.run();// runnung level

		m_numOfLvel++;
	
		m_playerEnergy = level.getHarryEnergy();// checking playres energy
	}

	m_window.setView(m_window.getDefaultView());

	endGame(m_window);// eng of game
}

//=============================================================================

// end of game 
void  Controller::endGame(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		window.clear();

		if (m_numOfLvel ==NUM_OF_LEVELS+1)// if player won
			window.draw(m_win);
		if (m_playerEnergy <= 0)// if player lost
			window.draw(m_lose);
		window.display();

		sf::Event event;
		if (window.pollEvent(event))
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Space)
					return;	
	}
}


