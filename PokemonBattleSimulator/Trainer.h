#pragma once
#include "Party.h"
#include <string>
#include <ostream>

class Trainer
{
private:
	std::string m_name;
	Party m_party;
	int m_money;

public:
	Trainer();
	Trainer(std::string name, int money = 0);

	std::string getName() const;
	Party getParty() const;
	Pokemon* getCurrentPokemon() const;
	bool canFight() const;
	int getReward() const;
	
	void getMoveChoice();
	void battleSwitch();

	void setParty(Party p);
	void addPokemon(Pokemon p);

	void addMoney(int howMuch);
};

std::ostream& operator << (std::ostream& stream, const Trainer& t);