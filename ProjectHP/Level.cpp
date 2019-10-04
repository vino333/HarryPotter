#include "Level.h"
#include "Resources.h"
#include "StrongEnemy.h"

// level c-tor
Level::Level(sf::RenderWindow&window, int numOfLevel)
	:m_board(window, numOfLevel), m_window(window), m_harryShoot(false)
{
	Resources::getSource().playLevelMusic();// starting the levels music
	m_texture.create((m_board.getBoardSize().y + 2)*SQUARE_SIZE, (m_board.getBoardSize().x+1)*SQUARE_SIZE);
	m_texture.clear(sf::Color(79, 29, 18));

	viewPos = { 0,0 };
}

//=============================================================================

Level::~Level()
{
	Resources::getSource().stopLevelMusic();// stping the levels music
}

//=============================================================================

// main loop of level
void Level::run()
{
	sf::View view;// view of level

	// setting the view
	view.reset(sf::FloatRect(0, 0, WIN_WIDTH, WIN_HEIGHT));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	// while player has enough energy and didnt kill all enemies in the room
	while (m_window.isOpen() && m_board.getHarryEnergy() > 0 && StrongEnemy::getNumOfStrong()!=0)
	{
		m_board.checkEnemiesDie();// checking if any enemies died

		handleEventFromUser();// handling the request from user

		display(view);// displaying the view
	}
}

//=============================================================================

// getting event from user
Direction Level::getMoveFromUser()
{
	sf::Event event;

	if (m_window.pollEvent(event))
		if (event.type == sf::Event::Closed)
			m_window.close();
		else if (event.type == sf::Event::EventType::KeyPressed)
			return(Resources::getSource().getDirection(event.key.code));

	return STAND;
}

//=============================================================================

// handling the view
void Level::display(sf::View& view)
{
	m_window.clear();

	m_texture.display();

	m_board.draw(m_texture, viewPos);

	viewPos.x = m_board.getHarryPos().x - WIN_WIDTH / 2;
	viewPos.y = m_board.getHarryPos().y - WIN_HEIGHT / 2;

	if (viewPos.x < 0)
		viewPos.x = 0;
	if (viewPos.y < 0)
		viewPos.y = 0;
	if (viewPos.x + WIN_WIDTH - 2 * SQUARE_SIZE > m_board.getBoardSize().y*SQUARE_SIZE)
		viewPos.x = m_board.getBoardSize().y*SQUARE_SIZE - WIN_WIDTH + 2 * SQUARE_SIZE;
	if (viewPos.y + WIN_HEIGHT - 2*SQUARE_SIZE > m_board.getBoardSize().x*SQUARE_SIZE)
		viewPos.y = m_board.getBoardSize().x*SQUARE_SIZE - WIN_HEIGHT + 2*SQUARE_SIZE;
	
	view.reset(sf::FloatRect(viewPos.x, viewPos.y, WIN_WIDTH, WIN_HEIGHT));

	m_window.setView(view);
	m_window.display();
}

//=============================================================================

// handling event from user
void Level::handleEventFromUser()
{
	Direction direction = getMoveFromUser();

	if (direction == ATTACK && !m_board.harryloaded(true))// if player attacks
		m_board.harryAboutToAttak();

	if (direction == WEAPON)// if player changed weapon
		m_board.harrySwitchWeapon();

	m_board.setHarryCurDir(direction);// setting players current direction
	m_board.moveObjects(direction);// moving objects

	if (m_board.harryTimeToShoot() && m_board.harryloaded(false))// playes shoots
		m_board.harryShoot();
}