#include "Pokemon.h"
#include <sstream>
#include <iostream>

using namespace std;
using namespace pkmn;

//initializes blank pokemon
Pokemon::Pokemon() : m_name(""), m_currHP(0), m_level(0), m_dexNum(0), m_stats(), m_EV(), m_IV(), m_statModifiers(), m_currMove(nullptr)
{
	//Initializes array values to 0
	for (int i = 0; i < NUM_STATS; i++)
	{
		m_stats[i] = 0;
		m_statModifiers[i] = 0;
		m_IV[i] = 0;
		m_EV[i] = 0;
	}
}

//initializes blank Pokemon but specifies the species
Pokemon::Pokemon(int dexNum) : m_name(""), m_currHP(0), m_level(0), m_dexNum(dexNum), m_stats(), m_EV(), m_IV(), m_statModifiers(), m_currMove(nullptr)
{
	for (int i = 0; i < NUM_STATS; i++)
	{
		m_stats[i] = 0;
		m_statModifiers[i] = 0;
		m_IV[i] = 0;
		m_EV[i] = 0;
	}
}

//copy constructor
Pokemon::Pokemon(const Pokemon& p)
{
	this->m_name = p.m_name;
	this->m_dexNum = p.m_dexNum;
	this->m_currHP = p.m_currHP;
	this->m_level = p.m_level;
	this->m_currMove = nullptr;

	for (int i = 0; i < p.getNumMoves(); i++)
	{
		m_moves.push_back(p.m_moves[i]);
		if (p.getCurrMove() != nullptr && m_moves[i] == *(p.getCurrMove()))
			this->m_currMove = &m_moves[i];
	}

	for (Type t : p.m_types)
	{
		this->m_types.push_back(t);
	}

	for (int i = 0; i < NUM_STATS; i++)
	{
		this->m_stats[i] = p.m_stats[i];
		this->m_statModifiers[i] = p.m_statModifiers[i];
		this->m_IV[i] = p.m_IV[i];
		this->m_EV[i] = p.m_EV[i];
	}
	
}

//Sets the pokemon's pokedex number
void Pokemon::setDexNum(int dexNum)
{
	this->m_dexNum = dexNum;
}

//Sets the Pokemon's name to the given string
void Pokemon::setName(string s)
{
	m_name = s;
}

//Adds the given type to the Pokemon's types
void Pokemon::addType(Type t)
{
	if (static_cast<int>(m_types.size()) > MAX_TYPES)
	{
		throw(string("Error: Pokemon " + to_string(m_dexNum) + " cannot have more than 2 types."));
	}
	m_types.push_back(t);

}

//sets the Pokemon's stat value when given a base stat value
void Pokemon::setStat(Stat s, int value)
{
	//this is how the calculation is actually done in Pokemon games
	//the integer truncation is intended, as that is done in the games as well
	m_stats[s] = (2 * value + m_IV[s] + (m_EV[s] / 4)) * m_level / 100;

	if (s == HP)
		m_stats[s] += m_level + 10;
	else
		m_stats[s] += 5;

}

//Sets the Pokemon's IV value for a given stat
void Pokemon::setIV(Stat s, int value)
{
	//ensures IVs are within the proper bounds
	if (value > MAX_IV)
		value = MAX_IV;
	else if (value < 0)
		value = 0;

	m_IV[s] = value;
}

//Sets the Pokemon's EV value for a given stat
void Pokemon::setEV(Stat s, int value)
{
	//ensures EVs are within the proper bounds
	if (value > MAX_EV)
		value = MAX_EV;
	else if (value < 0)
		value = 0;

	m_EV[s] = value;
}

//sets the Pokemon's level
void Pokemon::setLevel(int level)
{
	if (level > 100)
		level = 100;
	else if (level < 0)
		level = 0;
	this->m_level = level;
}

//Returns the Pokemon's pokedex number
int Pokemon::getDexNum() const
{
	return m_dexNum;
}

//returns the Pokemon's species name
string Pokemon::getName() const
{
	return m_name;
}

//Gets the Pokemon's value for a given stat
int Pokemon::getStat(Stat s) const
{
	//this is the formula for how in-battle stat modifications are applied in the games
	int numer = 2;
	int denom = 2;
	
	if (m_statModifiers[s] > 0)
		numer += m_statModifiers[s];
	else
		denom -= m_statModifiers[s];
	double modifier = static_cast<double>(numer) / denom;

	return static_cast<int> (m_stats[s] * modifier);
}

//Gets the Pokemon's IV (Individual Value) for a given stat 
int Pokemon::getIV(Stat s) const
{
	return m_IV[s];
}

//Gets the pokemon's EV (Effort Value) for a given stat
int Pokemon::getEV(Stat s) const
{
	return m_EV[s];
}

//gets the Pokemon's level
int Pokemon::getLevel() const
{
	return m_level;
}

//adds the specified value for a given stat to the stat Modifiers array
void Pokemon::addStatMod(Stat s, int value)
{
	if (value < 0)
		cout << getName() << "'s " << STAT_NAMES[s] << " was lowered!" << endl;
	else if (value > 0)
		cout << getName() << "'s " << STAT_NAMES[s] << " was raised!" << endl;

	m_statModifiers[s] += value;

	if (m_statModifiers[s] > STAT_DELTA)
		m_statModifiers[s] = STAT_DELTA;
	else if (m_statModifiers[s] < -STAT_DELTA)
		m_statModifiers[s] = -STAT_DELTA;
}

//Clears all stat modifications
void Pokemon::clearStatMods()
{
	for (int i = 0; i < NUM_STATS; i++)
		m_statModifiers[i] = 0;
}

//returns how much HP the Pokemon currently has
int Pokemon::currentHP() const
{
	return m_currHP;
}

//adds HP to the Pokemon's current HP
void Pokemon::addHP(int howMuch)
{
	m_currHP += howMuch;

	if (m_currHP > m_stats[HP])
		m_currHP = m_stats[HP];
}

//removes HP from the Pokemon's current HP
void Pokemon::subHP(int howMuch)
{
	m_currHP -= howMuch;

	if (m_currHP < 0)
		m_currHP = 0;
}

//Returns whether or not the Pokemon's HP is above 0
bool Pokemon::isFainted() const
{
	return !(m_currHP > 0);
}

//Returns the move that the pokemon has selected
Move* Pokemon::getCurrMove() const
{
	return m_currMove;
}

//Sets the current move to the move at the specified index in the move list
void Pokemon::setCurrMove(int index)
{
	if (index > m_moves.size() || index < 0)
		throw(string("setCurrMove() Error: specified index does not exist"));
	
	m_currMove = &m_moves[index];
}

//returns the move at the specified index in the move list
Move Pokemon::getMove(int index) const
{
	if (index > m_moves.size() || index < 0)
		throw(string("getMove() Error: specified index does not exist"));

	return m_moves[index];
}

//returns the number of moves the Pokemon has
int Pokemon::getNumMoves() const
{
	return static_cast<int>(m_moves.size());
}

//returns whether or not the pokemon has a specified type
bool Pokemon::hasType(Type t) const
{
	bool result = false;
	for (Type m_type : m_types)
		if (m_type == t)
		{
			result = true;
			break;
		}

	return result;
}

//calculates the damage modifier a type has on this pokemon. Stacks for each type
double Pokemon::calculateDamageMod(Type t) const
{
	double mod = 1;
	for (Type type : m_types)
		mod *= typeModifiers[t][type];

	return mod;
}

//Adds specified move to move list
void Pokemon::addMove(Move m)
{
	if (static_cast<int>(m_moves.size()) < MAX_MOVES)
		m_moves.push_back(m);
}

//returns a string formatted with the object's level, name, type(s), and HP
void Pokemon::display() const
{
	//prints out level, name, typing, and HP
	cout << "Lvl. " << m_level << " " << m_name << " [";
	for (int i = 0; i < m_types.size(); i++)
	{
		cout << TYPE_NAMES[m_types[i]];
		if (i != m_types.size() - 1)
			cout << "-";
	}
	cout << "] (" << m_currHP << "/" << m_stats[HP] << " HP)";

	cout << endl;
}

//Outputs all of the Pokemon's moves
void Pokemon::displayMoves() const
{
	for (int i = 0; i < m_moves.size(); i++)
		cout << "[" << i + 1 << "] : " << m_moves[i].display() << endl;
}

//Heals the pokemon by restoring its HP and moves
void Pokemon::heal()
{
	m_currHP = m_stats[HP];

	for (int i = 0; i < static_cast<int>(m_moves.size()); i++)
		m_moves[i].heal();
}

//Compares speed of Pokemon
bool Pokemon::operator > (const Pokemon& p) const
{
	return m_stats[SPEED] > p.getStat(SPEED);
}

//Compares speed of Pokemon
bool Pokemon::operator < (const Pokemon& p) const
{
	return p > *this;
}

//Compares speed of Pokemon
bool Pokemon::operator == (const Pokemon& p) const
{
	return !(*this > p || *this < p);
}

//Adds HP to Pokemon
void Pokemon::operator += (int n)
{
	this->addHP(n);
}

//Subtracts HP from Pokemon
void Pokemon::operator -= (int n)
{
	this->subHP(n);
}