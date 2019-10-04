#include "CollisionHandling.h"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "Harry.h"
#include "Door.h"
#include "DoorKey.h"
#include "StrongEnemy.h"
#include "EnemySpell.h"
#include "HarrySpell.h"
#include "WeakEnemy.h"
#include "Energy.h"
#include "Sword.h"
#include "Wall.h"
#include "StrongSpell.h"
#include "Wand.h"
#include "Coin.h"
#include "Nagini.h"
#include "Voldemort.h"
#include "Flitch.h"
#include "Malfoy.h"

using HitFunctionPtr = void(*)(GameObject&, GameObject&);
using Key = std::pair<std::type_index, std::type_index>;
using HitMap = std::map<Key, HitFunctionPtr>;

namespace { // unnamed namespace — the standard way to make function "static"

	// primary collision-processing functions
	void harryNagini(GameObject& harry, GameObject& nagini)
	{
		Harry& m_harry = dynamic_cast<Harry&>(harry);
		Nagini&m_nagini = dynamic_cast<Nagini&>(nagini);

		if (m_harry.isSword(false))
			m_nagini.reduceEnergy(65);
	}
	void harryVoldemort(GameObject& harry, GameObject& voldemort)
	{
		Harry& m_harry = dynamic_cast<Harry&>(harry);
		Voldemort& m_vold = dynamic_cast<Voldemort&>(voldemort);

		if (m_harry.isSword(false))
			m_vold.reduceEnergy(65);
	}
	void harryMalfoy(GameObject& harry, GameObject& malfoy)
	{
		Harry& m_harry = dynamic_cast<Harry&>(harry);
		Malfoy& m_malfoy = dynamic_cast<Malfoy&>(malfoy);

		if (m_harry.isSword(false))
			m_malfoy.reduceEnergy(100);
	}
	void harryFilch(GameObject& harry, GameObject& filch)
	{
		Harry& m_harry = dynamic_cast<Harry&>(harry);
		Flitch& m_filch = dynamic_cast<Flitch&>(filch);

		if (m_harry.isSword(false))
			m_filch.reduceEnergy(100);
	}
	void harryWall(GameObject& harry, GameObject& wall) {}
	void harryEnergy(GameObject& harry, GameObject& energy)
	{
		Harry& m_harry = dynamic_cast<Harry&>(harry);
		sf::Vector2i e = (sf::Vector2i)energy.getPosition() / SQUARE_SIZE;
		m_harry.takeItem(sf::Vector2i(e.x - 3, e.y - 2));
		m_harry.updateEnergy(5);
	}
	void harryWand(GameObject& harry, GameObject& wand)
	{
		Harry& m_harry = dynamic_cast<Harry&>(harry);
		Wand& m_wand = dynamic_cast<Wand&>(wand);
		m_harry.addWand(m_wand);
		sf::Vector2i e = (sf::Vector2i)wand.getPosition() / SQUARE_SIZE;
		m_harry.takeItem(sf::Vector2i(e.x - 3, e.y - 2));
	}
	void harrySword(GameObject& harry, GameObject& sword)
	{
		Harry& m_harry = dynamic_cast<Harry&>(harry);
		Sword& m_sword = dynamic_cast<Sword&>(sword);
		m_harry.addSword(m_sword);
		sf::Vector2i e = (sf::Vector2i)sword.getPosition() / SQUARE_SIZE;
		m_harry.takeItem(sf::Vector2i(e.x - 3, e.y - 2));
	}
	void harryDoorKey(GameObject& harry, GameObject& doorKey)
	{
		Harry& m_harry = dynamic_cast<Harry&>(harry);
		sf::Vector2i e = (sf::Vector2i)doorKey.getPosition() / SQUARE_SIZE;
		m_harry.takeItem(sf::Vector2i(e.x - 3, e.y - 2));
		m_harry.updateKeys();
	}
	void harryDoor(GameObject& harry, GameObject& door)
	{
		Harry& m_harry = dynamic_cast<Harry&>(harry);
		m_harry.openDoor();
	}
	void harrySpell(GameObject& harry, GameObject& enemySpell)
	{
		Harry& m_harry = dynamic_cast<Harry&>(harry);
		EnemySpell& m_spell = dynamic_cast<EnemySpell&>(enemySpell);
		m_harry.updateEnergy(-5);
		m_spell.timeUp();
	}
	void enemyWall(GameObject& enemy, GameObject& wall) {}
	void wallWeakEnemy(GameObject& wall, GameObject& weakEnemy) {}
	void wallStrongEnemy(GameObject& wall, GameObject& strongEney) {}
	void harrySpellWall(GameObject& harrySpell, GameObject& wall)
	{
		HarrySpell& m_spell = dynamic_cast<HarrySpell&>(harrySpell);
		m_spell.timeUp();
	}
	void enemySpellWall(GameObject& enemySpell, GameObject& wall)
	{
		EnemySpell& m_spell = dynamic_cast<EnemySpell&>(enemySpell);
		m_spell.timeUp();
	}
	void harryCoin(GameObject&harry, GameObject&coin)
	{
		Harry& m_harry = dynamic_cast<Harry&>(harry);
		Resources::getSource().playCoin();
		m_harry.updateScore(1);
		sf::Vector2i e = (sf::Vector2i)coin.getPosition() / SQUARE_SIZE;
		m_harry.takeItem(sf::Vector2i(e.x - 3, e.y - 2));
	}
	void strongSpellWall(GameObject&strongSpell, GameObject&wall)
	{
		StrongSpell& m_spell = dynamic_cast<StrongSpell&>(strongSpell);
		m_spell.timeUp();
	}
	void harrySpellNagini(GameObject&harrySpell, GameObject&nagini)
	{
		HarrySpell& m_spell = dynamic_cast<HarrySpell&>(harrySpell);
		Nagini& m_nagini = dynamic_cast<Nagini&>(nagini);
		m_spell.timeUp();
		m_nagini.reduceEnergy(20);
	}
	void harrySpellVoldemort(GameObject&harrySpell, GameObject&voldemort)
	{
		HarrySpell& m_spell = dynamic_cast<HarrySpell&>(harrySpell);
		Voldemort& m_vold = dynamic_cast<Voldemort&>(voldemort);
		m_vold.reduceEnergy(20);
		m_spell.timeUp();
	}
	void harrySpellMalfoy(GameObject&harrySpell, GameObject&malfoy)
	{
		HarrySpell& m_spell = dynamic_cast<HarrySpell&>(harrySpell);
		Malfoy& m_malfoy = dynamic_cast<Malfoy&>(malfoy);
		m_malfoy.reduceEnergy(35);
		m_spell.timeUp();
	}
	void harrySpellFlitch(GameObject&harrySpell, GameObject&filtch)
	{
		HarrySpell& m_spell = dynamic_cast<HarrySpell&>(harrySpell);
		Flitch& m_filch = dynamic_cast<Flitch&>(filtch);
		m_filch.reduceEnergy(35);
		m_spell.timeUp();
	}
	void strongSpellNagini(GameObject&strongSpell, GameObject&nagini)
	{
		StrongSpell& m_spell = dynamic_cast<StrongSpell&>(strongSpell);
		Nagini& m_nagini = dynamic_cast<Nagini&>(nagini);
		m_spell.timeUp();
		m_nagini.reduceEnergy(35);
	}
	void strongSpellVoldemort(GameObject&strongSpell, GameObject&voldemort)
	{
		StrongSpell& m_spell = dynamic_cast<StrongSpell&>(strongSpell);
		Voldemort& m_vold = dynamic_cast<Voldemort&>(voldemort);
		m_spell.timeUp();
		m_vold.reduceEnergy(35);
	}
	void strongSpellMalfoy(GameObject&strongSpell, GameObject&malfoy)
	{
		StrongSpell& m_spell = dynamic_cast<StrongSpell&>(strongSpell);
		Malfoy& m_malfoy = dynamic_cast<Malfoy&>(malfoy);
		m_spell.timeUp();
		m_malfoy.reduceEnergy(50);
	}
	void strongSpellFlitch(GameObject&strongSpell, GameObject& filch)
	{
		StrongSpell& m_spell = dynamic_cast<StrongSpell&>(strongSpell);
		Flitch& m_filch = dynamic_cast<Flitch&>(filch);
		m_spell.timeUp();
		m_filch.reduceEnergy(50);
	}


	void naginiHarry(GameObject& nagini, GameObject& harry) { harryNagini(harry, nagini); }
	void voldemortHarry(GameObject& voldemort, GameObject& harry) { harryVoldemort(harry, voldemort); }
	void malfoyHarry(GameObject& malfoy, GameObject& harry) { harryMalfoy(harry, malfoy); }
	void filchHarry(GameObject& filch, GameObject& harry) { harryFilch(harry, filch); }
	void WallHarry(GameObject& wall, GameObject& harry) { harryWall(harry, wall); }
	void energyHarry(GameObject& energy, GameObject& harry) { harryEnergy(harry, energy); }
	void wandHarry(GameObject& wand, GameObject& harry) { harryWand(harry, wand); }
	void swordHarry(GameObject& sword, GameObject& harry) { harrySword(harry, sword); }
	void doorKeyHarry(GameObject& doorKey, GameObject& harry) { harryDoorKey(harry, doorKey); }
	void doorHarry(GameObject& door, GameObject& harry) { harryDoor(harry, door); }
	void spellHarry(GameObject& spell, GameObject& harry) { harrySpell(harry, spell); }
	void wallEnemy(GameObject& wall, GameObject& enemy) { enemyWall(enemy, wall); }
	void weakEnemyWall(GameObject& weakEnemy, GameObject& wall) { wallWeakEnemy(wall, weakEnemy); }
	void strongEnemyWall(GameObject& strongEenemy, GameObject& wall) { wallStrongEnemy(wall, strongEenemy); }
	void wallEnemySpell(GameObject& wall, GameObject& enemySpell) { enemySpellWall(enemySpell, wall); }
	void wallHarrySpell(GameObject& wall, GameObject& harrySpell) { harrySpellWall(harrySpell, wall); }
	void coinHarry(GameObject&coin, GameObject&harry) { harryCoin(harry, coin); }
	void wallStrongSpell(GameObject&wall, GameObject&strongSpell) { strongSpellWall(strongSpell, wall); }
	void naginiHarrySpell(GameObject&nagini, GameObject&harrySpell) { harrySpellNagini(harrySpell, nagini); }
	void voldemortHarrySpell(GameObject&voldemort, GameObject&harrySpell) { harrySpellVoldemort(harrySpell, voldemort); }
	void malfoyHarrySpell(GameObject&malfoy, GameObject&harrySpell) { harrySpellMalfoy(harrySpell, malfoy); }
	void flitchHarrySpell(GameObject&filch, GameObject&harrySpell) { harrySpellFlitch(harrySpell, filch); }
	void naginiStrongSpell(GameObject&nagini, GameObject&strongSpell) { strongSpellNagini(strongSpell, nagini); }
	void voldemortStrongSpell(GameObject&voldemort, GameObject&strongSpell) { strongSpellVoldemort(strongSpell, voldemort); }
	void malfoyStrongSpell(GameObject&malfoy, GameObject&strongSpell) { strongSpellMalfoy(strongSpell, malfoy); }
	void flitchStrongSpell(GameObject&filch, GameObject&strongSpell) { strongSpellFlitch(strongSpell, filch); }


	HitMap initializeCollisionMap()
	{
		HitMap phm;

		phm[Key(typeid(Harry), typeid(Nagini))] = &harryNagini;
		phm[Key(typeid(Harry), typeid(Voldemort))] = &harryVoldemort;
		phm[Key(typeid(Harry), typeid(Malfoy))] = &harryMalfoy;
		phm[Key(typeid(Harry), typeid(Flitch))] = &harryFilch;
		phm[Key(typeid(Harry), typeid(Wall))] = &harryWall;
		phm[Key(typeid(Harry), typeid(Energy))] = &harryEnergy;
		phm[Key(typeid(Harry), typeid(Wand))] = &harryWand;
		phm[Key(typeid(Harry), typeid(Sword))] = &harrySword;
		phm[Key(typeid(Harry), typeid(DoorKey))] = &harryDoorKey;
		phm[Key(typeid(Harry), typeid(Door))] = &harryDoor;
		phm[Key(typeid(Harry), typeid(EnemySpell))] = &harrySpell;
		phm[Key(typeid(Enemy), typeid(Wall))] = &enemyWall;
		phm[Key(typeid(Wall), typeid(WeakEnemy))] = &wallWeakEnemy;
		phm[Key(typeid(Wall), typeid(StrongEnemy))] = &wallStrongEnemy;
		phm[Key(typeid(HarrySpell), typeid(Wall))] = &harrySpellWall;
		phm[Key(typeid(EnemySpell), typeid(Wall))] = &enemySpellWall;
		phm[Key(typeid(Harry), typeid(Coin))] = &harryCoin;
		phm[Key(typeid(StrongSpell), typeid(Wall))] = &strongSpellWall;
		phm[Key(typeid(HarrySpell), typeid(Nagini))] = &harrySpellNagini;
		phm[Key(typeid(HarrySpell), typeid(Voldemort))] = &harrySpellVoldemort;
		phm[Key(typeid(HarrySpell), typeid(Malfoy))] = &harrySpellMalfoy;
		phm[Key(typeid(HarrySpell), typeid(Flitch))] = &harrySpellFlitch;
		phm[Key(typeid(StrongSpell), typeid(Nagini))] = &strongSpellNagini;
		phm[Key(typeid(StrongSpell), typeid(Voldemort))] = &strongSpellVoldemort;
		phm[Key(typeid(StrongSpell), typeid(Malfoy))] = &strongSpellMalfoy;
		phm[Key(typeid(StrongSpell), typeid(Flitch))] = &strongSpellFlitch;


		phm[Key(typeid(Nagini), typeid(Harry))] = &naginiHarry;
		phm[Key(typeid(Voldemort), typeid(Harry))] = &voldemortHarry;
		phm[Key(typeid(Malfoy), typeid(Harry))] = &malfoyHarry;
		phm[Key(typeid(Flitch), typeid(Harry))] = &filchHarry;
		phm[Key(typeid(Wall), typeid(Harry))] = &WallHarry;
		phm[Key(typeid(Energy), typeid(Harry))] = &energyHarry;
		phm[Key(typeid(Wand), typeid(Harry))] = &wandHarry;
		phm[Key(typeid(Sword), typeid(Harry))] = &swordHarry;
		phm[Key(typeid(DoorKey), typeid(Harry))] = &doorKeyHarry;
		phm[Key(typeid(Door), typeid(Harry))] = &doorHarry;
		phm[Key(typeid(EnemySpell), typeid(Harry))] = &spellHarry;
		phm[Key(typeid(Wall), typeid(Enemy))] = &wallEnemy;
		phm[Key(typeid(WeakEnemy), typeid(Wall))] = &weakEnemyWall;
		phm[Key(typeid(StrongEnemy), typeid(Wall))] = &strongEnemyWall;
		phm[Key(typeid(Wall), typeid(EnemySpell))] = &wallEnemySpell;
		phm[Key(typeid(Wall), typeid(HarrySpell))] = &wallHarrySpell;
		phm[Key(typeid(Coin), typeid(Harry))] = &coinHarry;
		phm[Key(typeid(Wall), typeid(StrongSpell))] = &wallStrongSpell;
		phm[Key(typeid(Nagini), typeid(HarrySpell))] = &naginiHarrySpell;
		phm[Key(typeid(Voldemort), typeid(HarrySpell))] = &voldemortHarrySpell;
		phm[Key(typeid(Malfoy), typeid(HarrySpell))] = &malfoyHarrySpell;
		phm[Key(typeid(Flitch), typeid(HarrySpell))] = &flitchHarrySpell;
		phm[Key(typeid(Nagini), typeid(StrongSpell))] = &naginiStrongSpell;
		phm[Key(typeid(Voldemort), typeid(StrongSpell))] = &voldemortStrongSpell;
		phm[Key(typeid(Malfoy), typeid(StrongSpell))] = &malfoyStrongSpell;
		phm[Key(typeid(Flitch), typeid(StrongSpell))] = &flitchStrongSpell;


		return phm;
	}

	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
	{
		static HitMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
		{
			return nullptr;
		}
		return mapEntry->second;
	}

} // end namespace

void processCollision(GameObject& object1, GameObject& object2)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	if (!phf)
		return;

	phf(object1, object2);
}

