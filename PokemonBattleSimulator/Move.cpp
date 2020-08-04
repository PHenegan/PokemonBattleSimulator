#include "Move.h"
#include <cstdlib>

using namespace std;
//default constructor
Move::Move()
{
	m_name = "";
	m_damage = 0;
	m_accuracy = 0;
	m_isSpecial = false;
	m_type = pkmn::NORMAL;
	m_priority = 0;
	m_maxUses = 0;
	m_usesLeft = m_maxUses;
}

//Initializes with given values
Move::Move(string name, pkmn::Type t, int damage, int priority /*= 0*/,int accuracy /*= 100*/, bool isSpecial /*= false*/)
{
	m_name = name;
	m_type = t;
	m_damage = damage;
	m_accuracy = accuracy;
	m_isSpecial = isSpecial;
	m_priority = priority;
	m_usesLeft = m_maxUses;
}

