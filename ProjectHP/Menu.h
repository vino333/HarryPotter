#pragma once
#include <memory>
#include <string>
#include <vector>
#include <SFML\Graphics.hpp>
#include "Resources.h"
#include <iostream>
#include "Command.h"

class Menu
{
public:
	Menu();
	~Menu() {};
	void add(std::unique_ptr<Command>);
	bool performAction(unsigned n, sf::RenderWindow&);
	virtual int getOptionFromUser(sf::RenderWindow& window);
	void run();
	void loadMenuImages();
	void drawMenu(sf::RenderWindow& window);

protected:
	sf::Sprite m_background;
	sf::Sprite m_buttons[2];
	std::vector<std::unique_ptr<Command >> m_options;
};

