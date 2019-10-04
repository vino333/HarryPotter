#include "HumanObject.h"
#include "Factory.h"
#include "GraphixState.h"

// c-tor
HumanObject::HumanObject(int i, int j, int stepSize) :DynamicObject(i,j,stepSize),
m_energy(100), m_state(0), m_spellCasted(false),
m_currDirection(RIGHT), m_loaded(false), m_switchTime(0.075)
{
	m_graphix = make_shared<WalkState>();

	m_image.setPosition(j*SQUARE_SIZE, i*SQUARE_SIZE);
}

//=============================================================================

//d-tor
HumanObject::~HumanObject()
{
}

//=============================================================================

//this function manage the pictures of any human object in any situation
void HumanObject::setCurrImageDir(Direction direction)
{
	setDir(direction);
	
	if (Resources::getSource().getTime().asSeconds() - m_lastTime >m_switchTime)
	{
		if (m_imgIndex == 0)
			setState();

		sf::Vector2f pos = getPosition();
		m_image = m_images[m_imgIndex];
		m_image.setPosition(pos);
		m_imgIndex++;
		m_imgIndex %= m_numOfPictures;
		m_lastTime = Resources::getSource().getTime().asSeconds();
	}

	if (m_spellCasted && typeid(*m_graphix.get()) == typeid(WalkState) && m_imgIndex == m_numOfPictures-1)
		m_spellCasted = false;
}

//=============================================================================

//this function set the next state to the object
void HumanObject::setState()
{
	m_graphix->enter(*this);

	//it return the default state if nothing else choosed
	if (typeid(*m_graphix.get()) != typeid(WalkState))
		graphixHandleInput(WALK);
}

//=============================================================================

//signing shoot is loaded
void HumanObject::AboutToShoot()
{
	m_spellCasted = true;
}

//=============================================================================

//return if it is the right time to shoot
bool HumanObject::timeToShoot()
{
 	return m_spellCasted && m_imgIndex == m_numOfPictures-2 &&
		typeid(*m_graphix.get()) == typeid(WalkState);
}

//=============================================================================

// human object shooting a spell
shared_ptr<Spell> HumanObject::shootSpell(sf::Vector2f pos, std::string img, sf::Vector2f direction)
{
	return(Factory<Spell, std::string, sf::Vector2f>::create(img, pos,direction));
}

//=============================================================================

//this function get the current state and find the currect images
void HumanObject::setGraphixState(GameState state)
{
	m_images = getSprites(state);
}

//=============================================================================

//signing witch state should be the next
string HumanObject::graphixHandleInput(GameState input)
{
	shared_ptr<GraphixState> state = m_graphix->handleInput(input);
	
	if (state)
	{
		m_graphix = state;
		return state->name();
	}

	return "";
}

//=============================================================================

//this function get a coordinate of an object and return his distance from
//the current object
float HumanObject::findDistance(sf::Vector2f other)
{
	return sqrt(pow(float(m_position.x - other.x), 2) + pow(float(m_position.y - other.y), 2))/SQUARE_SIZE;
}

//=============================================================================

//this function get a coordinate of an object and return the unit vector from the
//current vector to him
sf::Vector2f HumanObject::findDirection(sf::Vector2f other)
{
	sf::Vector2f self = getPosition();

	sf::Vector2f vector(other.x - self.x, other.y - self.y);

	float modolus = sqrt(pow(vector.x, 2) + pow(vector.y, 2));

	vector = mulFVec(mulFVec(vector, pow(modolus, -1)), 3);
	
	return vector;
}

//=============================================================================

//activate the new state graphix
void HumanObject::graphixEnter() 
{
	m_graphix->enter(*this); 
}

//=============================================================================

//load a spell and return if a spell was loaded in write on resd technique
bool HumanObject::spellLoaded(bool newSet)
{
	swap(newSet, m_loaded);

	return newSet;
}

//=============================================================================
