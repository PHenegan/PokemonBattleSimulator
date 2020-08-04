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
	Move* m_currMove;

	int m_stats[pkmn::NUM_STATS];
	int m_currHP;
	int m_level;

	std::string m_name;
	int m_dexNum;

	void fillTypes(std::string s);
	void fillStats(std::string s);

public:
	Pokemon();
	Pokemon(int dexNum);

	void setDexNum(int dexNum);

	int getDexNum() const;
	std::string getName() const;
	int getStat(pkmn::Stat s) const;
	int currentHP() const;
	
	Move* getCurrMove() const;
	void setCurrMove(int index);

	Move getMove(int index) const;
	int getNumMoves() const;

	double calculateDamageMod(pkmn::Type t) const;
	void fillSpecies(std::ifstream& file);
	//void addMove(move m)
	//void delMove(move m)

	void display() const;
	void displayMoves() const;

	bool operator > (const Pokemon &p) const;
	bool operator < (const Pokemon &p) const;
	bool operator == (const Pokemon &p) const;
};

