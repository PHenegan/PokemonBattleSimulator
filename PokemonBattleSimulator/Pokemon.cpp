#include "Pokemon.h"
#include <sstream>
#include <iostream>

using namespace std;

Pokemon::Pokemon() : m_name(""), m_currHP(0), m_level(0), m_dexNum(0), m_stats(), m_currMove(nullptr)
{
	for (int i = 0; i < pkmn::NUM_STATS; i++)
		m_stats[i] = 0;
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

int Pokemon::getDexNum() const
{
	return m_dexNum;
}

string Pokemon::getName() const
{
	return m_name;
}

//getStats

int Pokemon::getStat(pkmn::Stat s) const
{
	return m_stats[s];
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
Move Pokemon::getMove(int index)
{
	if (index > m_moves.size() || index < 0)
		throw("getMove() Error: specified index does not exist");

	return m_moves[index];
}


//calculates the damage modifier a type has on this pokemon. Stacks for each type
double Pokemon::calculateDamageMod(pkmn::Type t) const
{
	int mod = 1;
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

//returns a string formatted with the object's name, type(s), and HP
string Pokemon::display() const
{
	ostringstream out;
	//prints out name, typing, and HP
	out << "Lvl. " << m_level << " " << m_name << " [";
	for (int i = 0; i < m_types.size(); i++)
	{
		out << pkmn::TYPE_NAMES[m_types[i]];
		if (i != m_types.size() - 1)
			out << "-";
	}
	out << "] (" << m_currHP << "/" << m_stats[pkmn::HP] << " HP)";

	return out.str();
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

