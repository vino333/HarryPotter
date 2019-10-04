#pragma once
#include "Command.h"
#include "Controller.h"

// exit button class
class Exit :public Command
{
public:
	Exit() :Command("exitButton", sf::Vector2f(80, 360)) {}
	virtual void execute(sf::RenderWindow& window)// exiting the game
	{
		window.close();
	}
};

//=============================================================================

// play game button class
class PlayGame :public Command
{
public:
	PlayGame() :Command("playButton", sf::Vector2f(80, 55)) {}
	virtual void execute(sf::RenderWindow& window)// playing a new game
	{
		Resources::getSource().stopMenuMusic();
		Controller game(1, window);
		game.run();// running the game
	}
};

//=============================================================================

// help button class
class Help :public Command
{
public:
	Help() :Command("helpButton", sf::Vector2f(80, 200))
	{
		m_halp.setTexture(Resources::getSource().getImage("help"));
	}
	virtual void execute(sf::RenderWindow&window)// showing help screen
	{
		while (window.isOpen())
		{
			window.clear();

			sf::Event event;
			if (window.pollEvent(event))
				if (event.type == sf::Event::KeyPressed)// if player moved pacman
					if (sf::Keyboard::Space)
						break;

			window.draw(m_halp);

			window.display();
		}
		
	}
private:
	sf::Sprite m_halp;
};