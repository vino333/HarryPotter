#include "Harry.h"
#include "Board.h"
#include "Wand.h"
#include "Energy.h"
#include "DoorKey.h"
#include "Sword.h"
#include "Coin.h"
#include "GraphixState.h";

// harry c-tor
Harry::Harry(int i, int j, Board& board)
	: HumanObject(i, j, 30), m_board(board), m_weaponIndex(0)
	, m_numOfKeys(0), m_holdingSword(false)
{
	m_numOfPictures = 14;

	m_harryImg.resize(10);

	m_switchTime = 0.05;

	m_images = Resources::getSource().getHarrySprites()[WALK];

	m_weaponBack.setTexture(Resources::getSource().getImage("weaponHighlight"));
}

//=============================================================================

int Harry::m_score = 0;// harry score

//=============================================================================

// moving the player
void Harry::move(sf::Vector2f step)
{
	if (step != sf::Vector2f(0, 0))
		DynamicObject::move(step);

	m_imageRight ? m_image.setTextureRect(sf::IntRect(90, 0, -90, 90)) :
		m_image.setTextureRect(sf::IntRect(0, 0, 90, 90));
}

//=============================================================================

// deleting an item from board when the player collects it
void Harry::takeItem(sf::Vector2i item)
{
	m_board.deleteCell(item.x, item.y);
}

//=============================================================================

// drawing the weapons the player has
void Harry::drawWeapons(sf::RenderWindow& window, sf::Vector2f viewPos)
{
	for (int i = 0; i < m_weapons.size(); i++)
	{
		if (m_weaponIndex == i + 1)// highlighting current weapon
		{
			m_weaponBack.setPosition(sf::Vector2f(viewPos.x + 16 * SQUARE_SIZE + (1 + i)*SQUARE_SIZE, viewPos.y + SQUARE_SIZE / 2));

			window.draw(m_weaponBack);
		}
		m_weapons[i]->setPosition(sf::Vector2f(viewPos.x + 16 * SQUARE_SIZE + (1 + i)*SQUARE_SIZE, viewPos.y + SQUARE_SIZE / 2));
		m_weapons[i]->draw(window);
	}
}

//=============================================================================

//turn on the sword hurt
void Harry::swordAttakOn()
{
	m_holdingSword = m_weaponIndex != 0 && std::dynamic_pointer_cast<Sword>(m_weapons[m_weaponIndex - 1]).get();
}

//=============================================================================

//turn off the sword hurt
void Harry::swordAttakOff()
{
	m_holdingSword = false;
}

//=============================================================================

//get if the state is a sword or not
bool Harry::isSword(bool newSet)
{
	swap(m_holdingSword, newSet);

	return newSet;
}

//=============================================================================

//get the direction vector to the first reachable enemy
sf::Vector2f Harry::Direction2Enemy()
{
	sf::Vector2f direction;

	while (m_closeEnemies.size() > 0 && (findDistance(m_closeEnemies.front()) > 10
		|| !sameDirection(m_closeEnemies.front(), m_imageRight)))
		m_closeEnemies.pop();

	if (m_closeEnemies.size() > 0)
	{
		direction = findDirection(m_closeEnemies.front());
		m_closeEnemies.pop();
		return direction;
	}

	return m_imageRight ? getStepTo(RIGHT) : getStepTo(LEFT);
}

//=============================================================================

//get a coordinate of an enemy and add it to ahrry enemies queue
void Harry::addToQueue(sf::Vector2f enemy, int numOfEnemies)
{
	if (m_closeEnemies.size() < numOfEnemies)
		m_closeEnemies.push(enemy);
}

//=============================================================================

//get the last state name saved
string Harry::spellName() { return m_name; }

//=============================================================================

//get the spell name for the use of the factory
string Harry::GraphixName() { return m_graphix->name(); }

//=============================================================================

// adding a wand to weponary when player collects it
void Harry::addWand(Wand& wand)
{
	m_weapons.push_back(make_shared<Wand>(wand));
}

//=============================================================================

// adding a sword to weponary when player collects it
void Harry::addSword(Sword& sword)
{
	m_weapons.push_back(make_shared<Sword>(sword));
}

//=============================================================================

// opening the door
void Harry::openDoor()
{
	m_board.openDoor(m_numOfKeys);
}

//=============================================================================

//set the direction the image shoude turn to
void Harry::setDir(Direction dir)
{
	if (dir == RIGHT) m_imageRight = true;
	if (dir == LEFT) m_imageRight = false;
}