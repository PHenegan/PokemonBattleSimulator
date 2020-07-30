#pragma once

#include "type.h";
#include <fstream>
#include <vector>

class Pokemon
{
private:
	std::vector<pkmn::Type> m_types;
	//std::vector<Move> m_moves;
	int m_stats[6];
	int m_currHP;
	int m_level;

	std::string m_name;
	int m_dexNum;
public:
	Pokemon(int dexNum);

	int getDexNum();
	int calculateDamageMod(pkmn::Type t);
	std::string getName();
	
	int getAtk(bool isSpecial);
	int getDef(bool isSpecial);
	int getSpeed();

	void fillSpecies(std::ifstream& file);
	//void addMove(move m)
	//void delMove(move m)
};

