#pragma once

#include "Move.h";
#include <fstream>
#include <vector>

class Pokemon
{

	friend class Battlefield;
private:
	std::vector<pkmn::Type> m_types;
	std::vector<Move> m_moves;
	Move* m_currMove;

	int m_stats[pkmn::NUM_STATS];
	int m_EV[pkmn::NUM_STATS];
	int m_IV[pkmn::NUM_STATS];

	int m_currHP;
	int m_level;

	//A pokemon's stats can be changed in-battle by moves
	//Each stat has a max of +6 or -6
	int m_statModifiers[pkmn::NUM_STATS];


	std::string m_name;
	int m_dexNum;

	void fillTypes(std::string s);
	void fillStats(std::string s);

public:
	Pokemon();
	Pokemon(int dexNum);
	Pokemon(const Pokemon& p);

	void setDexNum(int dexNum);
	void setStat(pkmn::Stat s, int value);
	void setIV(pkmn::Stat s, int value);
	void setEV(pkmn::Stat s, int value);
	void setLevel(int n);

	int getDexNum() const;
	std::string getName() const;
	int getStat(pkmn::Stat s) const;
	int getIV(pkmn::Stat s) const;
	int getEV(pkmn::Stat s) const;
	int getLevel() const;

	void addStatMod(pkmn::Stat s, int value);
	void clearStatMods();
	
	int currentHP() const;
	void addHP(int howMuch);
	void subHP(int howMuch);

	Move* getCurrMove() const;
	void setCurrMove(int index);

	Move getMove(int index) const;
	int getNumMoves() const;

	bool hasType(pkmn::Type t) const;
	double calculateDamageMod(pkmn::Type t) const;
	void fillSpecies(std::ifstream& file);
	//void addMove(move m)
	//void delMove(move m)

	void display() const;
	void displayMoves() const;

	//comparison operators
	bool operator > (const Pokemon &p) const;
	bool operator < (const Pokemon &p) const;
	bool operator == (const Pokemon &p) const;

	void operator += (int n);
	void operator -= (int n);
};

