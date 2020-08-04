#pragma once
#include "Party.h"
#include <string>

class Trainer
{
private:
	std::string m_name;
	Party m_party;
	int m_money;

public:
	Trainer();
	Trainer(std::string name, int money = 0);

	Party getParty() const;
	Pokemon* getCurrentPokemon() const;
	void getMoveChoice();
	bool canFight() const;

	int getReward() const;
};