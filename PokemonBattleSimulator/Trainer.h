#pragma once
#include "Party.h"
#include <string>
#include <ostream>

class Trainer
{
private:
	std::string m_name;
protected:
	Party m_party;
public:
	Trainer();
	Trainer(std::string name);

	std::string getName() const;
	Party getParty() const;
	int partySize() const;
	Pokemon* getCurrentPokemon() const;
	bool canFight() const;
	
	virtual void getMoveChoice();
	virtual void battleSwitch();
	bool replacePokemon(Pokemon p);

	void setParty(Party p);
	void addPokemon(Pokemon p);

	void heal();


};

std::ostream& operator << (std::ostream& stream, const Trainer& t);