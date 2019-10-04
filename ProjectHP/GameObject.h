#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include "General.h"
#include "Resources.h"

class Harry;
class StrongEnemy;
class WeakEnemy;
class Wall;
class DoorKey;
class HarrySpell;
class EnemySpell;
class Door;
class Energy;
class Sword;
class Wand;
class Coin;
const int STEP_SIZE = 6;

class GameObject
{
public:
	GameObject(float i, float j);
	~GameObject();
	virtual void draw(sf::RenderWindow& window) { window.draw(m_image); }
	virtual void setPosition(sf::Vector2f pos) { m_image.setPosition(pos); }
	virtual sf::Vector2f getPosition() { return m_image.getPosition(); }
	sf::FloatRect getGlobalBounds() { return m_image.getGlobalBounds(); }

protected:
	sf::Sprite m_image;
	sf::Vector2f m_currPosition;
};

