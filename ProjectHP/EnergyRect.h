#pragma once
#include <SFML\Graphics.hpp>

class EnergyRect
{
public:
	EnergyRect()// energy rectangle c-tor
	{
		m_cude.setSize(sf::Vector2f(65, 2));
		m_cude.setFillColor(sf::Color(76,153,0));
	}
	// drawing the energy rectangle
	void draw(sf::RenderWindow& window, sf::Vector2f pos)
	{
		m_cude.setPosition(pos);
		window.draw(m_cude);
	}
private:
	sf::RectangleShape m_cude;
};