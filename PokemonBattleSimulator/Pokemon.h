#pragma once

#include "type.h";
#include "Move.h";
#include <fstream>
#include <vector>

class Pokemon
{
private:
	std::vector<pkmn::Type> m_types;
	std::vector<Move> m_moves;
	int m_stats[pkmn::NUM_STATS];
	int m_currHP;
	int m_level;

	std::string m_name;
	int m_dexNum;

	void fillTypes(std::string s);
	void fillStats(std::string s);

public:
	Pokemon(int dexNum);

	int getDexNum() const;
	std::string getName() const;
	
	int getAtk(bool isSpecial) const;
	int getDef(bool isSpecial) const;
	int getSpeed();

	double calculateDamageMod(pkmn::Type t) const;
	void fillSpecies(std::ifstream& file);
	//void addMove(move m)
	//void delMove(move m)

	std::string display() const;
};

