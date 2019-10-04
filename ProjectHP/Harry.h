#pragma once
#include <SFML\Graphics.hpp>
#include "HumanObject.h"
#include "Door.h"
#include "Weapon.h"
#include <memory>
#include "General.h"
#include "Factory.h"

class GraphixState;
class StrongSpell;
class Board;
class Wand;

class Harry:public HumanObject
{
public:
	Harry(int i, int j, Board&board);
	~Harry() {};

	sf::RectangleShape rect;
	float top, bottom, right, left;
	int getEnergy() { return m_energy; }
	vector<sf::Sprite> getSprites(GameState state){return Resources::getSource().getHarrySprites()[state]; }
	void move(sf::Vector2f step);
	bool getIfRight() { return m_imageRight; }
	void takeItem(sf::Vector2i item);
	void drawWeapons(sf::RenderWindow&,sf::Vector2f);
	void updateEnergy(int energy) { m_energy = min(m_energy + energy, 100); }
	void updateScore(int points) { m_score += points; }
	int getScore() { return m_score; }
	sf::Vector2f* getP2Position() { return &m_position; }
	sf::Vector2f Direction2Enemy();
	void addToQueue(sf::Vector2f enemy, int numOfEnemies);
	void harrySwitchWeapon() { m_weaponIndex = (m_weaponIndex+1)%(m_weapons.size()+1); }
	bool isSpell();
	GameState getWeapon() { return m_weaponIndex == 0? SHOOTATTAK: m_weapons[m_weaponIndex-1]->state(); }
	string spellName();
	string GraphixName();
	void setName(string name) { m_name = name; }
	int getNumOfKeys() { return m_numOfKeys; }
	void addWand(Wand& wand);
	void addSword(Sword& sword);
	void updateKeys() { m_numOfKeys++; }
	void openDoor(); 
	void setDir(Direction dir);
	void swordAttakOn();
	void swordAttakOff();
	bool isSword(bool newSet);
	

private:

	vector<std::shared_ptr<Weapon>> m_weapons;
	int m_weaponIndex;
	queue<sf::Vector2f> m_closeEnemies;
	vector<sf::Sprite> m_harryImg;
	static int m_score;
	int m_numOfKeys;
	Board& m_board;
	string m_name;
	sf::Sprite m_weaponBack;
	bool m_holdingSword;
};

