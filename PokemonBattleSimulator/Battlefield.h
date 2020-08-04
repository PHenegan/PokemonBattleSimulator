#pragma once

#include "Trainer.h"

class Battlefield
{
private:
	int m_turn;
	Trainer* m_tr1;
	Trainer* m_tr2;

	void sortPriority(Pokemon** list, int size);
	Battlefield();

public:
	Battlefield(Trainer* tr1, Trainer* tr2);
	void runTurn();
	void battle();

	void display() const;
};