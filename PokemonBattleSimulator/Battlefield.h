#pragma once

#include "Trainer.h"

class Battlefield
{
private:
	int m_turn;
	Trainer* m_tr1;
	Trainer* m_tr2;

	Trainer** m_winner;
	Trainer** m_loser;

	void sortPriority(Pokemon** list, int size);
	Battlefield();

public:
	Battlefield(Trainer* tr1, Trainer* tr2);
	void runTurn();
	void battle();

	void display() const;
};