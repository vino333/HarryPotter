#include "Resources.h"
#include <fstream>
#include <iostream>
#include "GameObject.h"

//=============================================================================

Resources::Resources()
{
	setStaticResources();;// loading images

	setDirections();// setting directions map

	setMusic();// setting music
}

//=============================================================================

// loading harry's images
vector<vector<sf::Sprite>> Resources::loadHarrySprites()
{
	m_harryTextures.assign(4, vector<sf::Texture>(14));

	vector<vector<sf::Sprite>> sprites;
	sprites.assign(4, vector<sf::Sprite>(14));

	string base = "HARRY";
	vector<string> end;
	end.push_back("");
	end.push_back("WAND");
	end.push_back("SWORD");
	end.push_back("SPELL");

	for (int i = 0; i < 4; i++)
	{
		string name = base + end[i];
		
		for(int j=0; j<14; j++)
		{
			m_harryTextures[i][j].loadFromFile(name + to_string(j + 1) + ".png");
				
			sprites[i][j].setTexture(m_harryTextures[i][j]);
		}
	}

	return sprites;
}

//=============================================================================

// loading filch's images
vector<vector<sf::Sprite>> Resources::loadFlitchSprites()
{
	m_FlitchTextures.assign(2, vector<sf::Texture>(9));

	vector<vector<sf::Sprite>> sprites;
	sprites.assign(2, vector<sf::Sprite>(9));

	string base = "FLITCH";
	vector<string> end;
	end.push_back("");
	end.push_back("WAND");

	for (int i = 0; i < 2; i++)
	{
		string name = base + end[i];

		for (int j = 0; j<9; j++)
		{
			m_FlitchTextures[i][j].loadFromFile(name + to_string(j + 1) + ".png");

			sprites[i][j].setTexture(m_FlitchTextures[i][j]);
		}
	}

	return sprites;
}

//=============================================================================

//loading nagini's images
vector<vector<sf::Sprite>> Resources::loadNaginiSprites()
{
	m_NaginiTextures.assign(2, vector<sf::Texture>(6));

	vector<vector<sf::Sprite>> sprites;
	sprites.assign(2, vector<sf::Sprite>(6));

	string base = "NAGINI";
	vector<string> end;
	end.push_back("");
	end.push_back("ATTAK");

	for (int i = 0; i < 2; i++)
	{
		string name = base + end[i];

		for (int j = 0; j<6; j++)
		{
			m_NaginiTextures[i][j].loadFromFile(name + to_string(j + 1) + ".png");

			sprites[i][j].setTexture(m_NaginiTextures[i][j]);
		}
	}

	return sprites;
}

//=============================================================================

//loading voldemort's images
vector<vector<sf::Sprite>> Resources::loadVoldemortSprites()
{
	m_VoldemortTextures.assign(2, vector<sf::Texture>(3));

	vector<vector<sf::Sprite>> sprites;
	sprites.assign(2, vector<sf::Sprite>(3));

	string base = "VOLDEMORT";

	for (int i = 0; i < 2; i++)
	{
		string name = base;

		for (int j = 0; j<3; j++)
		{
			m_VoldemortTextures[i][j].loadFromFile(name + to_string(j + 1) + ".png");

			sprites[i][j].setTexture(m_VoldemortTextures[i][j]);
		}
	}

	return sprites;
}

//=============================================================================

//loading malfoy's images
vector<vector<sf::Sprite>> Resources::loadMalfoySprites()
{
	m_MalfoyTextures.assign(2, vector<sf::Texture>(14));

	vector<vector<sf::Sprite>> sprites;
	sprites.assign(2, vector<sf::Sprite>(14));

	string base = "MALFOY";
	vector<string> end;
	end.push_back("");
	end.push_back("WAND");

	for (int i = 0; i < 2; i++)
	{
		string name = base + end[i];

		for (int j = 0; j<14; j++)
		{
			m_MalfoyTextures[i][j].loadFromFile(name + to_string(j + 1) + ".png");

			sprites[i][j].setTexture(m_MalfoyTextures[i][j]);
		}
	}

	return sprites;
}

//=============================================================================

//loading spells's images
vector<vector<sf::Sprite>> Resources::loadSpellSprites()
{
	m_spellTextures.assign(3, vector<sf::Texture>(10));

	vector<vector<sf::Sprite>> sprites;
	sprites.assign(3, vector<sf::Sprite>(10));

	string base = "SPELL";
	vector<string> end;
	end.push_back("");
	end.push_back("W");
	end.push_back("S");

	for (int i = 0; i < 3; i++)
	{
		string name = base + end[i];

		for (int j = 0; j<10; j++)
		{
			m_spellTextures[i][j].loadFromFile(name + to_string(j + 1) + ".png");

			sprites[i][j].setTexture(m_spellTextures[i][j]);
		}
	}

	return sprites;
}

//=============================================================================

sf::Clock Resources::m_clock;// game clock

//=============================================================================

Resources::~Resources()
{
}

//=============================================================================

// getting singletons instance
Resources& Resources ::getSource()
{
	static Resources m_imageResource;
	return m_imageResource;
};

//=============================================================================

// loading images to map from file
void Resources::setStaticResources()
{
	std::ifstream file;

	std::string nameObject;
	std::string nameFileTexture;

	file.open("sources.txt");

	std::getline(file, nameObject);// name of object

	while (nameObject != "-1")
	{
		std::getline(file, nameFileTexture);// name of image file
				
		sf::Texture texture;// Load the texture 

		if (!texture.loadFromFile(nameFileTexture))
			std::cout << "Failed to load texture" << std::endl;
		
		//Add it to the list of textures 
		this->m_resources[nameObject] = texture;

		std::getline(file, nameObject);
	}
	file.close();

	m_font.loadFromFile("font.ttf");
	m_weaponText.setFont(m_font);
	m_weaponText.setString("Weaponary");
	m_weaponText.setCharacterSize(53);

	m_scoreText.setFont(m_font);
	m_scoreText.setString("Score:");
	m_scoreText.setCharacterSize(60);
}

//=============================================================================

//will return a reference to the texture
const sf::Texture& Resources::getImage(const std::string& nameTexture) const
{
	return this->m_resources.at(nameTexture);
}

//=============================================================================

// setting directions map
void Resources::setDirections()
{
	m_directions[sf::Keyboard::Right] = RIGHT;
	m_directions[sf::Keyboard::Left] = LEFT;
	m_directions[sf::Keyboard::Up] = UP;
	m_directions[sf::Keyboard::Down] = DOWN;
	m_directions[sf::Keyboard::Space] = ATTACK;
	m_directions[sf::Keyboard::Tab] = WEAPON;
}

//============================================================================

// getting the direction name 
Direction Resources::getDirection(sf::Keyboard::Key direction)
{
	return m_directions.find(direction) == m_directions.end()
		? STAND : m_directions[direction];
}

//=============================================================================

// getting voldemort images
vector<vector<sf::Sprite>> Resources::getVoldemortSprites()
{
	static vector<vector<sf::Sprite>> images = loadVoldemortSprites();

	return images;
}

//=============================================================================

// getting nagini images
vector<vector<sf::Sprite>> Resources::getNaginiSprites()
{
	static vector<vector<sf::Sprite>> images = loadNaginiSprites();

	return images;
}

//=============================================================================

// getting harry images
vector<vector<sf::Sprite>> Resources::getHarrySprites()
{
	static vector<vector<sf::Sprite>> images = loadHarrySprites();

	return images;
}

//=============================================================================

// getting malfoy images
vector<vector<sf::Sprite>> Resources::getMalfoySprites()
{
	static vector<vector<sf::Sprite>> images = loadMalfoySprites();

	return images;
}

//=============================================================================

// getting filch images
vector<vector<sf::Sprite>> Resources::getFlitchSprites()
{
	static vector<vector<sf::Sprite>> images = loadFlitchSprites();

	return images;
}

//=============================================================================

// getting spell images
vector<vector<sf::Sprite>> Resources::getSpellSprites()
{
	static vector<vector<sf::Sprite>> images = loadSpellSprites();

	return images;
}

//=============================================================================

// setting the music for the game
void Resources::setMusic()
{
	m_menuMusic.openFromFile("menuMusic.ogg");
	m_levelMusic.openFromFile("levelMusic.ogg");
	m_openDoor.openFromFile("openDoor.ogg");
	m_coinCollect.openFromFile("coinSound.ogg");
	m_coinCollect.setVolume(1);
	m_spellShoot.openFromFile("spellShoot.ogg");
}
