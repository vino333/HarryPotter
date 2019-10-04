#pragma once
#include "Harry.h"
#include "Enemy.h"
#include "StaticObject.h"
#include <memory>
#include <vector>
#include <fstream>
#include "General.h"
#include "ToolBar.h"
#include "WeakEnemy.h"


const int MAX_FILE_NAME = 20;

class Board
{
public:
	Board(sf::RenderWindow& window, int levelNumber);
	~Board();

	void setHarryPosition();
	void loadBoard(int);
	void moveObjects(Direction);
	void moveEnemies();
	void draw(sf::RenderTexture&, sf::Vector2f);
	sf::Vector2f getBoardSize() { return sf::Vector2f((float)m_boardHeight, (float)m_boardWidth); }
	void checkCollision(sf::Vector2f);
	bool checkStaticCollision(DynamicObject& object);
	void deleteCell(int i, int j) { m_board[j][i].reset(); }
	void enemyMove(shared_ptr<Enemy>& enemy);
	bool enemyCheckCollision(const sf::Vector2f& step, shared_ptr<Enemy>& enemy);
	void harryShoot();
	void moveSpells();
	void enemyShootSpell(shared_ptr<Enemy>& enemy);
	sf::Vector2f getHarryPos() { return m_harry.getPosition(); }
	void setHarryCurDir(Direction dir) { m_harry.setCurrDir(dir); }
	void registerInHarryQueue(shared_ptr<Enemy>& enemy);
	void harryAboutToAttak();
	bool harryTimeToShoot();
	void checkEnemiesDie();
	int getHarryEnergy() { return m_harry.getEnergy(); }
	void drawMessage(sf::Vector2f);
	void setMessageTime(float time) { m_messageTime = time; }
	void setIfDrawMessage(bool ifDraw) { doorMessage = ifDraw; }
	void openDoor(int m_numOfKeys);
	void harrySwitchWeapon() { m_harry.harrySwitchWeapon(); }
	bool harryloaded(bool newSet);
	void HarrySwordOn() { m_harry.swordAttakOn(); }
	void HarrySwordOff() { m_harry.swordAttakOff(); }
	void setState(){m_harry.setName(m_harry.graphixHandleInput(m_harry.getWeapon()));}

private:
	std::vector<std::vector<std::shared_ptr<StaticObject>>> m_board;
	std::vector<std::shared_ptr<Enemy>> m_enemies;
	vector<shared_ptr<Spell>> m_spells;
	int m_boardHeight;
	int m_boardWidth;
	sf::RenderWindow &m_window;
	Harry m_harry;
	ToolBar m_toolbar;
	sf::Sprite m_doorMessage;
	bool doorMessage;
	float m_messageTime;
	std::shared_ptr<Door> m_door;
};

