#include "Move.h"
#include "Pokemon.h"
#include <cstdlib>
#include <sstream>
#include <iostream>

using namespace std;
//default constructor
Move::Move()
{
	m_name = "";
	m_type = pkmn::NORMAL;
	m_power = 0;
	m_accuracy = 100;
	m_isSpecial = false;
	m_priority = 0;
	m_PP = m_maxPP;
	for (int i = 0; i < pkmn::NUM_STATS; i++)
	{
		m_userStatChanges[i] = 0;
		m_targetStatChanges[i] = 0;
	}
}

//Initializes with given values
Move::Move(string name)
{
	m_name = name;
	m_type = pkmn::NORMAL;
	m_power = 0;
	m_accuracy = 100;
	m_isSpecial = false;
	m_priority = 0;
	m_PP = m_maxPP;
	for (int i = 0; i < pkmn::NUM_STATS; i++)
	{
		m_userStatChanges[i] = 0;
		m_targetStatChanges[i] = 0;
	}
}

void Move::setName(string name)
{
	this->m_name = name;
}

void Move::setPower(int n)
{
	m_power = n;
}

void Move::setAccuracy(int n)
{
	m_accuracy = n;
}

void Move::setType(pkmn::Type t)
{
	m_type = t;
}

//sets the maximum amount of times a move can be used by a specific pokemon in one battle
void Move::setMaxPP(int n)
{
	m_maxPP = n;
	m_PP = n;
}

void Move::setSpecial(bool isSp)
{
	m_isSpecial = isSp;
}

void Move::setPriority(int n)
{
	m_priority = n;
}

void Move::setUserChanges(int stats[pkmn::NUM_STATS])
{
	for (int i = 0; i < pkmn::NUM_STATS; i++)
	{
		m_userStatChanges[i] = stats[i];
	}
}

void Move::setUserChanges(pkmn::Stat s, int value)
{
	//ensures that the value is within the specified range
	if (value > pkmn::STAT_DELTA)
		value = pkmn::STAT_DELTA;
	else if (value < -pkmn::STAT_DELTA)
		value = -pkmn::STAT_DELTA;

	m_userStatChanges[s] = value;
}

void Move::setTargetChanges(int stats[pkmn::NUM_STATS])
{
	for (int i = 0; i < pkmn::NUM_STATS; i++)
	{
		m_targetStatChanges[i] = stats[i];
	}
}

void Move::setTargetChanges(pkmn::Stat s, int value)
{
	//ensures that the value is within the specified range
	if (value > pkmn::STAT_DELTA)
		value = pkmn::STAT_DELTA;
	else if (value < -pkmn::STAT_DELTA)
		value = -pkmn::STAT_DELTA;

	m_targetStatChanges[s] = value;
}

int Move::getPriority() const
{
	return m_priority;
}

int Move::getPP() const
{
	return m_PP;
}

int Move::getMaxPP() const
{
	return m_maxPP;
}

string Move::getName() const
{
	return m_name;
}

void Move::heal()
{
	m_PP = m_maxPP;
}

//returns whether or not the move hit
bool Move::use(Pokemon* user, Pokemon* target)
{
	//if accuracy is -1, the move will never miss
	//otherwise, and random number is generated and compared to the move's accuracy in order to determine whether or not it misses
	bool miss = (m_accuracy == -1) ? false : (rand() % 100 + 1 > m_accuracy);

	//figures out which attack stat to use
	pkmn::Stat def = m_isSpecial ? pkmn::SPDEF : pkmn::DEF;
	pkmn::Stat atk = m_isSpecial ? pkmn::SPATK : pkmn::SPDEF;
	
	double damage = 0;
	//This is based on the formular for damage calculations used in pokemon games.
	//I tried to break it up into several lines in order to make it more readable
	if (m_power > 0 && !miss)
	{
		//same-type attack bonus (STAB) is given when the move being used matches one of the user's types
		double stab = user->hasType(m_type) ? 1.5 : 1.0;

		//Attacks will do between 85% and 100% of their potential damage based on random rolls
		double dRoll = static_cast<double>(rand() % 16 + 85) / 100;

		//modifier based on how effective the type is on the target
		double typeMod = target->calculateDamageMod(m_type);

		double modifier = stab * dRoll * typeMod;

		double lvlMod = 0.4 * user->getLevel() + 2;
		damage = (lvlMod * m_power * static_cast<double>(user->getStat(atk)) / target->getStat(def)) / 50 + 2;
		damage *= modifier;

		//In the games, damage is rounded down to the nearest whole number
		*target -= static_cast<int>(damage);
	}

	//if the move only changes stats, this will be called
	if (!miss)
		for (pkmn::Stat i = pkmn::HP; i <= pkmn::SPEED; i = static_cast<pkmn::Stat>(i + 1))
		{
			user->addStatMod(i, m_userStatChanges[i]);
			target->addStatMod(i, m_targetStatChanges[i]);
		}

	m_PP--;

	return !miss;
}

string Move::display() const
{
	string fName;
	ostringstream formatted;
	for (int i = 0; i < static_cast<int>(m_name.size()); i++)
	{
		if (m_name.at(i) == '_')
			fName += ' ';
		else
			fName += m_name.at(i);
	}

	formatted << fName << " (" << m_PP << "/ " << m_maxPP << " PP)";
	return formatted.str();
}

//the only unique value in a move is its name, so that is the only thing needed to compare moves
bool Move::operator == (const Move& m) const
{
	return m.m_name == m_name;
}

ostream& operator << (std::ostream& stream, const Move& m)
{
	string name = m.getName();
	string formatted;
	for (int i = 0; i < static_cast<int>(name.size()); i++)
	{
		if (name.at(i) == '_')
			formatted += ' ';
		else
			formatted += name.at(i);
	}
	stream << formatted;
	return stream;
}