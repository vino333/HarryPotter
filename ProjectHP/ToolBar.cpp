#include "ToolBar.h"

ToolBar::ToolBar()
{
	m_energyContainer.resize(100);// resizing enregy capacity to 100

	setSideBar();
}

//=============================================================================

ToolBar::~ToolBar()
{
}

//=============================================================================

// setting the strings for tool bar
void ToolBar::setSideBar()
{
	m_scoreText = Resources::getSource().getScroeText();
	m_scoreNumber = m_scoreText;
	m_keysText = m_scoreText;
	m_keysNum = m_scoreText;
	m_scoreNumber.setColor(sf::Color(5, 50, 23));
	m_scoreText.setColor(sf::Color(5, 50, 23));
	m_keysText.setColor(sf::Color(5, 50, 23));
	m_keysNum.setColor(sf::Color(5, 50, 23));

	frame.setTexture(Resources::getSource().getImage("frame"));
	m_weaponText = Resources::getSource().getFont();
	m_weaponText.setString("Weaponry");
	m_weaponText.setCharacterSize(50);
	m_weaponText.setFillColor(sf::Color(5, 50, 23));

	leftBar.setSize(sf::Vector2f(3 * SQUARE_SIZE, 680));
	topBar.setSize(sf::Vector2f(1200, 2 * SQUARE_SIZE));
	topBar.setOutlineThickness(3);
	leftBar.setOutlineThickness(3);
	topBar.setOutlineColor(sf::Color(5, 50, 23));
	leftBar.setOutlineColor(sf::Color(5, 50, 23));
	topBar.setFillColor(sf::Color(131, 28, 7));
	leftBar.setFillColor(sf::Color(131, 28, 7));

	m_energyText = m_weaponText;
	m_energyText.setString("Energy");
	m_energyText.setCharacterSize(55);

	m_keysText.setString("Keys");
	m_keysText.setCharacterSize(55);
	m_keysNum.setCharacterSize(55);
}

//=============================================================================

// drawing the tool bar
void ToolBar::drawToolBar(sf::RenderWindow&window, sf::Vector2f viewPos,int score,int energy,int keys)
{
	m_keysNum.setString(std::to_string(keys));
	m_scoreNumber.setString(std::to_string(score));

	m_scoreText.setPosition(viewPos.x + 4 * SQUARE_SIZE, viewPos.y);
	m_scoreNumber.setPosition(viewPos.x + 7 * SQUARE_SIZE, viewPos.y);
	frame.setPosition(viewPos.x + SQUARE_SIZE / 2, viewPos.y + 4.4* SQUARE_SIZE);
	topBar.setPosition(viewPos);
	leftBar.setPosition(viewPos);
	m_weaponText.setPosition(viewPos.x + 13 * SQUARE_SIZE, viewPos.y);
	m_energyText.setPosition(viewPos.x + SQUARE_SIZE / 3, viewPos.y + SQUARE_SIZE * 2);
	m_keysText.setPosition(viewPos.x + 25 * SQUARE_SIZE, viewPos.y);
	m_keysNum.setPosition(viewPos.x + 28 * SQUARE_SIZE, viewPos.y);

	window.draw(topBar);
	window.draw(leftBar);
	window.draw(m_scoreText);
	window.draw(m_scoreNumber);
	window.draw(frame);
	window.draw(m_keysText);
	window.draw(m_energyText);
	window.draw(m_weaponText);
	window.draw(m_keysNum);

	drawEnergy(window, viewPos, energy);
}

//=============================================================================

// drawing the enrgy
void ToolBar::drawEnergy(sf::RenderWindow&window, sf::Vector2f viewPos,int energy)
{
	//draw energy
	for (int i = 0; i < energy; i++)
		m_energyContainer[i].draw(window, sf::Vector2f(viewPos.x + SQUARE_SIZE * 0.70, viewPos.y + 10 * SQUARE_SIZE - i * 2));
}

//=============================================================================
