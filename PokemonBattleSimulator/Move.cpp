#include "Move.h"
#include "Pokemon.h"
#include <cstdlib>
#include <sstream>
#include <iostream>

using namespace std;
using namespace pkmn;

//default constructor
Move::Move()
{
	m_name = "";
	m_type = NORMAL;
	m_power = 0;
	m_accuracy = 100;
	m_isSpecial = false;
	m_priority = 0;
	m_PP = m_maxPP;
	for (int i = 0; i < NUM_STATS; i++)
	{
		m_userStatChanges[i] = 0;
		m_targetStatChanges[i] = 0;
	}
}

//Initializes with given values
Move::Move(string name)
{
	m_name = name;
	m_type = NORMAL;
	m_power = 0;
	m_accuracy = 100;
	m_isSpecial = false;
	m_priority = 0;
	m_PP = m_maxPP;
	for (int i = 0; i < NUM_STATS; i++)
	{
		m_userStatChanges[i] = 0;
		m_targetStatChanges[i] = 0;
	}
}

//sets the name
void Move::setName(string name)
{
	this->m_name = name;
}

//sets the power of the move
void Move::setPower(int n)
{
	m_power = n;
}

//sets the move's accuracy
void Move::setAccuracy(int n)
{
	m_accuracy = n;
}

//sets the move's type
void Move::setType(Type t)
{
	m_type = t;
}

//sets the maximum amount of times a move can be used by a specific pokemon in one battle
void Move::setMaxPP(int n)
{
	m_maxPP = n;
	m_PP = n;
}

//sets whether or not the move is a special attack
void Move::setSpecial(bool isSp)
{
	m_isSpecial = isSp;
}

//sets the priority level of the move
void Move::setPriority(int n)
{
	m_priority = n;
}

//sets the changes to be made in the user's stats
void Move::setUserChanges(int stats[NUM_STATS])
{
	for (int i = 0; i < NUM_STATS; i++)
	{
		m_userStatChanges[i] = stats[i];
	}
}

//sets the value of an individual user stat to be changed i
void Move::setUserChanges(Stat s, int value)
{
	//ensures that the value is within the specified range
	if (value > STAT_DELTA)
		value = STAT_DELTA;
	else if (value < -STAT_DELTA)
		value = -STAT_DELTA;

	m_userStatChanges[s] = value;
}

//sets the changes to be made in the target's stats
void Move::setTargetChanges(int stats[NUM_STATS])
{
	for (int i = 0; i < NUM_STATS; i++)
	{
		m_targetStatChanges[i] = stats[i];
	}
}

//sets the value of an individual target stat to be changed
void Move::setTargetChanges(Stat s, int value)
{
	//ensures that the value is within the specified range
	if (value > STAT_DELTA)
		value = STAT_DELTA;
	else if (value < -STAT_DELTA)
		value = -STAT_DELTA;

	m_targetStatChanges[s] = value;
}

//accessor for the move's priority level
int Move::getPriority() const
{
	return m_priority;
}

//returns the amount of uses the move has left
int Move::getPP() const
{
	return m_PP;
}

//returns the maximum amount of uses the move can have
int Move::getMaxPP() const
{
	return m_maxPP;
}

//returns the move's name
string Move::getName() const
{
	return m_name;
}

//restores the move's number of uses to its maximum value
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
	Stat def = m_isSpecial ? SPDEF : DEF;
	Stat atk = m_isSpecial ? SPATK : SPDEF;
	
	double damage = 0;

	//modifier based on how effective the type is on the target
	double typeMod = target->calculateDamageMod(m_type);

	//This is based on the formular for damage calculations used in pokemon games.
	//I tried to break it up into several lines in order to make it more readable
	if (m_power > 0 && !miss)
	{
		//same-type attack bonus (STAB) is given when the move being used matches one of the user's types
		double stab = user->hasType(m_type) ? 1.5 : 1.0;

		//Attacks will do between 85% and 100% of their potential damage based on random rolls
		double dRoll = (static_cast<double>(rand() % 16) + 85) / 100;
		if (typeMod > 1.0)
			cout << "It's super-effective!" << endl;
		else if (typeMod == 0)
			cout << "It had no effect!" << endl;
		else if (typeMod < 1.0)
			cout << "It's not very effective..." << endl;

		double modifier = stab * dRoll * typeMod;

		double lvlMod = 0.4 * user->getLevel() + 2;
		damage = (lvlMod * m_power * static_cast<double>(user->getStat(atk)) / target->getStat(def)) / 50 + 2;
		damage *= modifier;

		//In the games, damage is rounded down to the nearest whole number
		*target -= static_cast<int>(damage);
	}

	//if the move only changes stats, this will be called
	if (!miss)
		for (Stat i = HP; i <= SPEED; i = static_cast<Stat>(i + 1))
		{
			user->addStatMod(i, m_userStatChanges[i]);
			if (typeMod != 0)
				target->addStatMod(i, m_targetStatChanges[i]);
		}

	m_PP--;

	return !miss;
}

//displays the move along with the amount of uses it has left
string Move::display() const
{
	string fName;
	ostringstream formatted;

	//gets rid of the underscore present in the move's name (if the name is multiple words)
	for (int i = 0; i < static_cast<int>(m_name.size()); i++)
	{
		if (m_name.at(i) == '_')
			fName += ' ';
		else
			fName += m_name.at(i);
	}

	formatted << "[" << TYPE_NAMES[m_type] << "] " << fName << " (" << m_PP << "/ " << m_maxPP << " PP)";
	return formatted.str();
}

//the only unique value in a move is its name, so that is the only thing needed to compare moves
bool Move::operator == (const Move& m) const
{
	return m.m_name == m_name;
}

//outputs the formatted name of the move to the stream
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