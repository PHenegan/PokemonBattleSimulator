#pragma once
#include "Party.h"
#include <string>
#include <ostream>

class Trainer
{
private:
	std::string m_name;
	int m_money;
	Party m_party;
public:
	Trainer();
	Trainer(std::string name, int money = 0);

	std::string getName() const;
	Party getParty() const;
	int partySize() const;
	Pokemon* getCurrentPokemon() const;
	bool canFight() const;
	
	virtual int getReward() const;
	virtual void getMoveChoice();
	virtual void battleSwitch();

	void setParty(Party p);
	void addPokemon(Pokemon p);

	void addMoney(int howMuch);
	int getMoney() const;

	void heal();


};

std::ostream& operator << (std::ostream& stream, const Trainer& t);