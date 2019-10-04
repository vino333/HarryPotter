#include "Board.h"
#include <iostream>
#include <memory>
#include "CollisionHandling.h"
#include "Spell.h"


// c-tor of board game
Board::Board(sf::RenderWindow& window, int levelNumber)
	:m_harry(3, 4, *this), m_window(window), m_toolbar(),doorMessage(false)
{
	loadBoard(levelNumber);// loading board from file

	setHarryPosition();

	// setting message for not enough keys
	m_doorMessage.setTexture(Resources::getSource().getImage("message"));
}

//=============================================================================

Board::~Board()
{
}

//=============================================================================

// loading the board from the file
void Board::loadBoard(int levelNumber)
{
	std::ifstream myFile;
	char fileName[MAX_FILE_NAME];
	sprintf_s(fileName, MAX_FILE_NAME, "level%d.txt", levelNumber);
	myFile.open(fileName);// opening file

	if (myFile.fail())
		std::cout << "Could Not Open Level File";

	myFile >> m_boardWidth>> m_boardHeight  ;//reading boards size

	// resizing board
	m_board.resize(m_boardHeight);
	std::for_each(m_board.begin(), m_board.end(),
		[this](std::vector<std::shared_ptr<StaticObject>>&v) {v.resize(m_boardWidth); });

	if (myFile.peek() == '\n')
	myFile.get();

	for (int i = 0; i < m_boardHeight; i++)
	{
		for (int j = 0; j < m_boardWidth; j++)
		{
			char curr;
			myFile.get(curr);

			// factories for static objects and enemies
			std::shared_ptr<StaticObject> newStatic = Factory<StaticObject, char, int>::create(curr, i, j);
			std::shared_ptr<Enemy> newEnemy = Factory<Enemy, char, int>::create(curr, i, j);

			if (newStatic == nullptr)
				m_board[i][j] = nullptr;
			if (std::dynamic_pointer_cast<Door>(newStatic))
			{
				m_door = std::dynamic_pointer_cast<Door>(newStatic);
				m_door->setPosition(sf::Vector2f((float)(j + 3)*SQUARE_SIZE, (float)(i + 2)*SQUARE_SIZE));
				m_board[i][j] = nullptr;
			}
			else if (newStatic != nullptr)
			{
				m_board[i][j] = newStatic;
				m_board[i][j]->setPosition(sf::Vector2f((float)(j + 3)*SQUARE_SIZE, (float)(i + 2)*SQUARE_SIZE));
			}
			else if (newEnemy != nullptr)
			{
				newEnemy->setPosition(sf::Vector2f((float)(j + 3)*SQUARE_SIZE, (float)(i + 2)*SQUARE_SIZE));
				m_enemies.push_back(newEnemy);
			}
		}
	}
	myFile.close();// closing the file
}

//=============================================================================

// moving all objects on the board
void Board::moveObjects(Direction direction)
{
	m_harry.setCurrImageDir(direction);// setting Harry's image according to his direction

	m_harry.move(m_harry.getStepTo(direction));// moving the player

	checkCollision(m_harry.getStepTo(direction));// checking collisions of all objects

	moveEnemies();// moving enemies

	moveSpells();// moving spells
}

//=============================================================================

// moving the enemies
void Board::moveEnemies()
{
	for_each(m_enemies.begin(), m_enemies.end(), [&](shared_ptr<Enemy>& enemy)
	{enemyMove(enemy); });
}

//=============================================================================

// drawing the board
void Board::draw(sf::RenderTexture& background, sf::Vector2f viewPos)
{
	m_window.draw(sf::Sprite(background.getTexture()));// draw background

	for (int i = 0; i < m_boardHeight; i++)// drawing static objects
		for (int j = 0; j < m_boardWidth; j++)
			if (m_board[i][j])
				m_board[i][j]->draw(m_window);

	// drawing ene,ies
	for_each(m_enemies.begin(), m_enemies.end(), [&](shared_ptr<Enemy>& enemy)
	{enemy->draw(m_window); });

	m_harry.draw(m_window);// draw player

	// draw spells 
	for_each(m_spells.begin(), m_spells.end(), [&](shared_ptr<Spell>& spell)
	{spell->draw(m_window); });

	if (m_door != nullptr) m_door->draw(m_window);//draw door

	// draw tool bar
	m_toolbar.drawToolBar(m_window, viewPos, m_harry.getScore(), m_harry.getEnergy(),m_harry.getNumOfKeys());

	m_harry.drawWeapons(m_window, viewPos);// draw weapons

	if (doorMessage)// if player is trying to open the door without enough keys
	{
		if (Resources::getSource().getTime().asSeconds() - m_messageTime > 3)
			doorMessage = false;
		drawMessage(viewPos);
	}
}

//=============================================================================

// checking collisions of all objects in the game
void Board::checkCollision(sf::Vector2f step)
{
	if (checkStaticCollision(m_harry))// harry and static objects
		m_harry.move(-step);

	// enemies and harry
	for_each(m_enemies.begin(), m_enemies.end(), [&](shared_ptr<Enemy>& enemy)
	{if (enemy->getGlobalBounds().intersects(m_harry.getGlobalBounds()))
		processCollision(m_harry,*enemy);});

	// spells and static objects
	for_each(m_spells.begin(), m_spells.end(), [&](shared_ptr<Spell>&spell)
	{checkStaticCollision(*spell);});

	for (auto & enemy : m_enemies)//enemies and spells
		for (auto& spell : m_spells)
			if (spell->getGlobalBounds().intersects(enemy->getGlobalBounds()))
				processCollision(*enemy, *spell);

	for (auto& spell : m_spells)// spells and harry
		if (spell->getGlobalBounds().intersects(m_harry.getGlobalBounds()))
			processCollision(*spell, m_harry);

	if(m_door!=nullptr)// door and harry
	if (m_harry.getGlobalBounds().intersects(m_door->getGlobalBounds()))
	{
		processCollision(*m_door, m_harry);
		m_harry.move(-step);
	}
}

//=============================================================================

// checking if a dynamic objects is colliding with a static object
bool Board::checkStaticCollision(DynamicObject& object)
{
	sf::Vector2i area = (sf::Vector2i)object.getPosition() / SQUARE_SIZE;

	// checking colisions in a close area around the dynamic object
	for (int i = max(area.x - 3, 0); i < min(area.x + 3, m_boardWidth); i++)
		for (int j = max(area.y - 3, 0); j < min(area.y + 3, m_boardHeight); j++)
			if (m_board[j][i] && m_board[j][i]->getGlobalBounds().intersects(object.getGlobalBounds()))
			{
				processCollision(*m_board[j][i], object);
				return true;
			}
	return false;
}

//=============================================================================

// move an enemy
void Board::enemyMove(shared_ptr<Enemy>& enemy)
{
	//if possibale do spell loading
	if (enemy->AbleToShoot() && Resources::getSource().getTime().asSeconds() - enemy->getShootTime() > 2
		&& !enemy->spellLoaded(true))
	{
		enemy->AboutToShoot();
		enemy->graphixHandleInput(SHOOTATTAK);
		enemy->setShootTime(Resources::getSource().getTime().asSeconds());
	}

	//if its time, shoot
	if (enemy->timeToShoot())
		enemyShootSpell(enemy);

	//do the move
	sf::Vector2f step = enemy->moveControl();
	enemyCheckCollision(step, enemy);
	registerInHarryQueue(enemy);
}

//=============================================================================

//do the collision check for the enemies
bool Board::enemyCheckCollision(const sf::Vector2f& step, shared_ptr<Enemy>& enemy)
{
	if (checkStaticCollision(*enemy.get()) || enemy->outOfArea())
	{
		enemy->move(-step);
		return true;
	}
	return false;
}

//=============================================================================

//do the harry shoots
void Board::harryShoot()
{
	HarrySwordOff();

	sf::Vector2f p = m_harry.getPosition();

	if (m_harry.getIfRight())
		p.x += 1.7*SQUARE_SIZE;

	p.y = (float)(m_harry.getPosition().y + 0.5);

	string name = m_harry.spellName();
	
	if(name == "spell" || name == "Sspell")
		m_spells.push_back(m_harry.shootSpell(p, name, m_harry.Direction2Enemy()));

	m_harry.updateEnergy(-1);
}

//=============================================================================

// moving the spells
void Board::moveSpells()
{
	for (int i = 0; i < (signed)m_spells.size(); i++)// if a spell ended
		if (m_spells[i]->getIfTimeUp())
			m_spells.erase(m_spells.begin() + i);

	for (int i = 0; i < (signed)m_spells.size(); i++)// moving the spells
		m_spells[i]->moveSpell();
}

//=============================================================================

//shoot an enemy spell
void Board::enemyShootSpell(shared_ptr<Enemy>& enemy)
{
	sf::Vector2f p = enemy->getPosition();

	if (enemy->spellLoaded(false))
		m_spells.push_back(enemy->shootSpell(p, "enemySpell", enemy->direction2Harry()));
}

//=============================================================================

//give the enemies a pointer to harry's location
void Board::setHarryPosition()
{
	sf::Vector2f *harryPlace = m_harry.getP2Position();

	for_each(m_enemies.begin(), m_enemies.end(), [&harryPlace](shared_ptr<Enemy>& enemy)
	{enemy->setHarryPlace(harryPlace); });
}

//=============================================================================

//do register an enemy in harry enemies queue
void Board::registerInHarryQueue(shared_ptr<Enemy>& enemy)
{
	m_harry.addToQueue(enemy->getPosition(), m_enemies.size());
}

//=============================================================================

//load a spell or a sword for harry and set the right state
void Board::harryAboutToAttak()
{
	HarrySwordOn();

	m_harry.setName(m_harry.graphixHandleInput(m_harry.getWeapon()));

	if(m_harry.spellName() != "WALK")
		m_harry.AboutToShoot();
}

//=============================================================================

//return if its the time for harry to shoot or not
bool Board::harryTimeToShoot()
{
	return m_harry.timeToShoot();
}

//=============================================================================

// checking if an enemy died
void Board::checkEnemiesDie()
{
	for (int i = 0; i < (signed)m_enemies.size(); i++)
		if (m_enemies[i]->getIfDead())
		{
			m_harry.updateScore(20);// updating harrys score
			m_enemies.erase(m_enemies.begin() + i);// deleting the enemy
		}
}

//=============================================================================

// drawing the door message
void  Board::drawMessage(sf::Vector2f viewPos)
{
	m_doorMessage.setPosition(viewPos.x,viewPos.y+500);
	m_window.draw(m_doorMessage);
} 

//=============================================================================

// opening the door if player has enough keys
void Board::openDoor(int m_numOfKeys)
{
	if (!m_door->openDoor(m_numOfKeys))// if player has less than 3 keys
	{
		setMessageTime(Resources::getSource().getTime().asSeconds());
		setIfDrawMessage(true);
	}
	else// if player collected 3 keys
		m_door.reset();
}

//=============================================================================

//load a spell for harry
bool Board::harryloaded(bool newSet)
{
	return m_harry.spellLoaded(newSet);
}


