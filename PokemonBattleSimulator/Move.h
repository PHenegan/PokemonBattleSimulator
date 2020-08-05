#pragma once
#include "type.h"
#include <string>
#include <ostream>

class Pokemon;

class Move
{
private:
	int m_userStatChanges[pkmn::NUM_STATS];
	int m_targetStatChanges[pkmn::NUM_STATS];
	pkmn::Type m_type;
	std::string m_name;
	int m_priority;
	int m_power;
	int m_accuracy;

	//power points - how many times the move can be used
	int m_maxPP;
	int m_PP;

	int statChanges[pkmn::NUM_STATS];
	bool m_isSpecial;
public:
	/*
	I had originally made these all private, but I realized that Most of the methods
	in the class ended up being 1-line accessor and mutator methods. Because most of the
	calculations will be done outside of the Move class (and are handled by the Battlefield)
	I made the data members public
	*/

	Move();
	Move(std::string name);

	void setName(std::string name);
	void setPower(int n);
	void setAccuracy(int n);
	void setType(pkmn::Type t);
	void setMaxPP(int n);
	void setSpecial(bool isSp);
	void setPriority(int n);

	void setUserChanges(int n[pkmn::NUM_STATS]);
	void setUserChanges(pkmn::Stat s, int value);
	void setTargetChanges(int n[pkmn::NUM_STATS]);
	void setTargetChanges(pkmn::Stat s, int value);

	int getPriority() const;
	int getPP() const;
	int getMaxPP() const;
	std::string getName() const;

	void heal();
	bool use(Pokemon* user, Pokemon* target);

	std::string display() const;
	
	bool operator == (const Move& m) const;
};

std::ostream& operator << (std::ostream& stream, const Move& m);

