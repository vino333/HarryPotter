#include "Menu.h"
#include "GameButtons.h"

// menu c-tor
Menu::Menu()
{
	loadMenuImages();// loading menu images

	// buttons for menu
	add(std::make_unique<PlayGame>());
	add(std::make_unique<Exit>());
	add(std::make_unique<Help>());

	Resources::getSource().playMenuMusic();
}

//=============================================================================

// running the menu
void Menu::run()
{
	sf::RenderWindow window(sf::VideoMode(WIN_WIDTH,WIN_HEIGHT), "Harry Potter");
	int action;

	while (window.isOpen())
	{
		window.clear();

		drawMenu(window);// drawing the menu

		window.display();

		action = getOptionFromUser(window);// getting event from user

		performAction(action, window);// performing action
	}
}

//=============================================================================

// adding a button to the vector of buttons
void Menu::add( std::unique_ptr<Command> c)
{
	m_options.emplace_back (std::move(c));
}

//=============================================================================

// performing action from user
bool Menu::performAction(unsigned action, sf::RenderWindow& window)
{
	if (action >= m_options.size())
		return false;

	m_options[action]->execute(window);// executing action
	return true;
}

//=============================================================================

// loading menu images
void Menu::loadMenuImages()
{
	m_background.setTexture(Resources::getSource().getImage("menuBackground"));
}

//=============================================================================

// dawing the menu
void Menu::drawMenu(sf::RenderWindow& window)
{
	window.draw(m_background);
	for (auto&opt : m_options)
		opt->printMe(window);
}

//=============================================================================

// handling the players request
int Menu::getOptionFromUser(sf::RenderWindow& window)
{
	sf::Event event;

	if (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)// if player wants to exit
			return EXIT;

		if (event.type == sf::Event::MouseButtonPressed)
		{
			int m_x = event.mouseButton.x;
			int m_y = event.mouseButton.y;

			for (int i = 0; i < m_options.size(); i++)
				if (m_options[i]->buttonPressed(m_x, m_y))
					return i;
		}
	}
	return NOTHING;
}
