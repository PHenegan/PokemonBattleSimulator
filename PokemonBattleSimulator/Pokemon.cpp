#include "Pokemon.h"
#include <sstream>
#include <iostream>

using namespace std;

Pokemon::Pokemon() : m_name(""), m_currHP(0), m_level(0), m_dexNum(0), m_stats(), m_currMove(nullptr)
{
	//Initializes array values to 0
	for (int i = 0; i < pkmn::NUM_STATS; i++)
	{
		m_stats[i] = 0;
		m_IV[i] = 0;
		m_EV[i] = 0;
	}
}

Pokemon::Pokemon(int dexNum) : m_name(""), m_currHP(0), m_level(0), m_dexNum(dexNum), m_stats(), m_currMove(nullptr)
{
	for (int i = 0; i < pkmn::NUM_STATS; i++)
		m_stats[i] = 0;
}

void Pokemon::setDexNum(int dexNum)
{
	this->m_dexNum = dexNum;
}

//sets the Pokemon's stat value when given a base stat value
void Pokemon::setStat(pkmn::Stat s, int value)
{
	//this is how the calculation is actually done in Pokemon games
	//the integer truncation is intended, as that is done in the games as well
	m_stats[s] = (2 * value + m_IV[s] + (m_EV[s] / 4)) * m_level / 100;

	if (s == pkmn::HP)
		m_stats[s] += m_level + 10;
	else
		m_stats[s] += 5;

}

void Pokemon::setIV(pkmn::Stat s, int value)
{
	//ensures IVs are within the proper bounds
	if (value > pkmn::MAX_IV)
		value = pkmn::MAX_IV;
	else if (value < 0)
		value = 0;

	m_IV[s] = value;
}

void Pokemon::setEV(pkmn::Stat s, int value)
{
	//ensures EVs are within the proper bounds
	if (value > pkmn::MAX_EV)
		value = pkmn::MAX_EV;
	else if (value < 0)
		value = 0;

	m_EV[s] = value;
}

void Pokemon::setLevel(int n)
{
	m_level = n;
}

int Pokemon::getDexNum() const
{
	return m_dexNum;
}

string Pokemon::getName() const
{
	return m_name;
}

int Pokemon::getStat(pkmn::Stat s) const
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

int Pokemon::getIV(pkmn::Stat s) const
{
	return m_IV[s];
}

int Pokemon::getEV(pkmn::Stat s) const
{
	return m_EV[s];
}

int Pokemon::getLevel() const
{
	return m_level;
}

void Pokemon::addStatMod(pkmn::Stat s, int value)
{
	m_statModifiers[s] += value;

	if (m_statModifiers[s] > pkmn::STAT_DELTA)
		m_statModifiers[s] = pkmn::STAT_DELTA;
	else if (m_statModifiers[s] < -pkmn::STAT_DELTA)
		m_statModifiers[s] = -pkmn::STAT_DELTA;
}

//returns how much HP the Pokemon currently has
int Pokemon::currentHP() const
{
	return m_currHP;
}

void Pokemon::addHP(int howMuch)
{
	m_currHP += howMuch;

	if (m_currHP > m_stats[pkmn::HP])
		m_currHP = m_stats[pkmn::HP];
}

void Pokemon::subHP(int howMuch)
{
	m_currHP += howMuch;

	if (m_currHP < 0)
		m_currHP = 0;
}



Move* Pokemon::getCurrMove() const
{
	return m_currMove;
}

//Sets the current move to the move at the specified index in the move list
void Pokemon::setCurrMove(int index)
{
	if (index > m_moves.size() || index < 0)
		throw("setCurrMove() Error: specified index does not exist");
	
	m_currMove = &m_moves[index];
}

//returns the move at the specified index in the move list
Move Pokemon::getMove(int index) const
{
	if (index > m_moves.size() || index < 0)
		throw("getMove() Error: specified index does not exist");

	return m_moves[index];
}

int Pokemon::getNumMoves() const
{
	return m_moves.size();
}

bool Pokemon::hasType(pkmn::Type t) const
{
	bool result = false;
	for (pkmn::Type m_type : m_types)
		if (m_type == t)
		{
			result = true;
			break;
		}
	return result;
}

//calculates the damage modifier a type has on this pokemon. Stacks for each type
double Pokemon::calculateDamageMod(pkmn::Type t) const
{
	double mod = 1;
	for (pkmn::Type type : m_types)
		mod *= pkmn::typeModifiers[t][type];

	return mod;
}

void Pokemon::fillSpecies(ifstream &file)
{
	string name;
	string temp;
	bool found = false;

	while (!file.eof())
	{
		//gets the current line and puts it into a string steam
		getline(file, temp);

		//If the target pokemon is found, adds species data into object
		if (temp.length() >= 4 && 
			temp.substr(0, 2) == "@p" &&
			temp.substr(3) == to_string(m_dexNum))
		{
			found = true;
			getline(file, m_name);

			//processes type line
			getline(file, temp); 
			fillTypes(temp);
			
			//processes stats line
			getline(file, temp); 
			fillStats(temp);

		}
	}
	if (!found)
	{
		//structured exception handling
	}
}

void Pokemon::fillTypes(string s)
{
	istringstream line(s);
	vector<string> types;
	string temp;
	int count = 0;
	
	while (!line.eof())
	{
		line >> temp;
		types.push_back(temp);
	}

	for (string name : types)
		for (int i = 0; i < pkmn::NUM_TYPES; i++)
			if (name == pkmn::TYPE_NAMES[i])
			{
				m_types.push_back(static_cast<pkmn::Type>(i));
				count++;
			}
	if (count == 0 || count > pkmn::MAX_TYPES)
	{
		//Structured Exception Handling here
	}
}

void Pokemon::fillStats(string s)
{
	int i = 0;
	istringstream line(s);
	
	while (i < pkmn::NUM_STATS && !line.eof())
	{
		line >> m_stats[i++];
	}
	if (i < pkmn::NUM_STATS)
	{
		//structured exception handling here
	}
	m_currHP = m_stats[pkmn::HP];
}

//returns a string formatted with the object's level, name, type(s), and HP
void Pokemon::display() const
{
	//prints out level, name, typing, and HP
	cout << "Lvl. " << m_level << " " << m_name << " [";
	for (int i = 0; i < m_types.size(); i++)
	{
		cout << pkmn::TYPE_NAMES[m_types[i]];
		if (i != m_types.size() - 1)
			cout << "-";
	}
	cout << "] (" << m_currHP << "/" << m_stats[pkmn::HP] << " HP)";

	cout << endl;
}

void Pokemon::displayMoves() const
{
	for (int i = 0; i < m_moves.size(); i++)
		cout << "[" << i + 1 << "]" << " : " << m_moves[i].display();
}

bool Pokemon::operator > (const Pokemon& p) const
{
	return m_stats[pkmn::SPEED] > p.getStat(pkmn::SPEED);
}

bool Pokemon::operator < (const Pokemon& p) const
{
	return p > *this;
}

bool Pokemon::operator == (const Pokemon& p) const
{
	return !(*this > p || *this < p);
}

void Pokemon::operator += (int n)
{
	this->addHP(n);
}

void Pokemon::operator -= (int n)
{
	this->subHP(n);
}
