#pragma once
#include <map>
#include <SFML\Graphics.hpp>
#include <string>
#include <SFML\Audio.hpp>
#include <functional>
#include <memory>
#include "General.h"

class GameObject;
class Spell;

class Resources
{
public:
	~Resources();
	static Resources& getSource();
	void setMusic();
	const sf::Texture& getImage(const std::string& nameTexture) const;
	void setStaticResources();
	void setDirections();
	Direction getDirection(sf::Keyboard::Key direction);
	sf::Time getTime() const { return m_clock.getElapsedTime(); };
	sf::Text getFont() { return m_weaponText; }
	sf::Text getScroeText(){ return m_scoreText; }
	vector<vector<sf::Sprite>> getHarrySprites();
	vector<vector<sf::Sprite>> getFlitchSprites();
	vector<vector<sf::Sprite>> getNaginiSprites();
	vector<vector<sf::Sprite>> getSpellSprites();
	vector<vector<sf::Sprite>> getMalfoySprites();
	vector<vector<sf::Sprite>> getVoldemortSprites();
	void playMenuMusic() { m_menuMusic.play(); }
	void stopMenuMusic() { m_menuMusic.stop(); }
	void playLevelMusic() { m_levelMusic.play(); }
	void stopLevelMusic() { m_levelMusic.stop(); }
	void playOpenDoor() { m_openDoor.play(); }
	void playCoin() { m_coinCollect.play(); }
	void playSpell() { m_spellShoot.play(); }

	
private:
	Resources();
	Resources(const Resources&) = delete;
	Resources & operator=(const Resources&) = delete;
	std::map<std::string, sf::Texture> m_resources;
	vector<vector<sf::Texture>> m_harryTextures;
	vector<vector<sf::Texture>> m_FlitchTextures;
	vector<vector<sf::Texture>> m_MalfoyTextures;
	vector<vector<sf::Texture>> m_NaginiTextures;
	vector<vector<sf::Texture>> m_VoldemortTextures;
	vector<vector<sf::Texture>> m_spellTextures;
	vector<vector<sf::Sprite>> loadHarrySprites();
	vector<vector<sf::Sprite>> loadFlitchSprites();
	vector<vector<sf::Sprite>> loadVoldemortSprites();
	vector<vector<sf::Sprite>> loadNaginiSprites();
	vector<vector<sf::Sprite>> loadSpellSprites();
	vector<vector<sf::Sprite>> loadMalfoySprites();

	std::map<sf::Keyboard::Key, Direction> m_directions;
	static sf::Clock m_clock;
	sf::Font m_font;
	sf::Text m_weaponText;
	sf::Text m_scoreText;
	sf::Music m_menuMusic;
	sf::Music m_levelMusic;
	sf::Music m_openDoor;
	sf::Music m_coinCollect;
	sf::Music m_spellShoot;
};

