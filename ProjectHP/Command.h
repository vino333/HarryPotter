#pragma once
#include <SFML\Graphics.hpp>
#include "Resources.h"

// abstarcat class for menu commands-buttons
class Command
{
public:
	Command(std::string name,sf::Vector2f pos) // c-tor
	{
		m_buttonImage.setTexture(Resources::getSource().getImage(name));
		m_buttonImage.setPosition(pos); 
	};
	virtual void execute(sf::RenderWindow&) = 0;// execute request
	virtual void printMe(sf::RenderWindow& window) { window.draw(m_buttonImage); };// printing button
	virtual bool buttonPressed(int x,int y)// checking if button pressed
	{
		if(m_buttonImage.getGlobalBounds().contains(x,y))
			return true;
		return false;
	};

protected:
	sf::Sprite m_buttonImage;// image of button
};



