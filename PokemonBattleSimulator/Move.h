#pragma once
#include "type.h"
#include <string>

class Pokemon;

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

	//Max power points - how many times the move can be used
	int m_maxPP;
	int m_PP;
	int statChanges[pkmn::NUM_STATS];
	bool m_isSpecial;

	Move();
	Move(std::string name);

	void setName(std::string name);
	void setDamage(int n);
	void setAccuracy(int n);
	void setType(pkmn::Type t);
	void setDamage(int n);
	void setMaxPP(int n);
	void setSpecial(bool isSp);
	void setPriority(int n);

	void heal();
	void use(Pokemon* target);
};

