#pragma once
#include "type.h"
#include <string>

class Move
{
public:
	/*
	I had originally made these all private, but I realized that Most of the methods
	in the class ended up being 1-line accessor and mutator methods. Because most of the
	calculations will be done outside of the Move class (and are handled by the Battlefield)
	I made the data members public
	*/
	pkmn::Type m_type;
	std::string m_name;
	int m_priority;
	int m_damage;
	int m_accuracy;
	int m_maxUses;
	int m_usesLeft;
	bool m_isSpecial;

	Move();
	Move(std::string name, pkmn::Type t, int damage, int accuracy=100, int priority = 0, bool isSpecial = false);


};

