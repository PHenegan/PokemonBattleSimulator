#include "Trainer.h"
#include <iostream>

using namespace std;

Trainer::Trainer() : m_name(""), m_party(), m_money(0)
{}


Trainer::Trainer(string name, int money /*= 0*/)
{
	this->m_name = name;
	m_money = money;
}

//Gets the trainer's party
Party Trainer::getParty() const
{
	return m_party;
}

//Gets the pokemon that the trainer is currently using
Pokemon* Trainer::getCurrentPokemon() const
{
	return &m_party[0];
}

void Trainer::getMoveChoice()
{
	int choice;
	do 
	{
		cout << "Pick a move: "; cin >> choice;
		cin.ignore();

		if (choice < 1 || choice > getCurrentPokemon()->getNumMoves())
			cout << "Invalid choice. Please pick one of the above options." << endl;

	} while (choice < 1 || choice > getCurrentPokemon()->getNumMoves());

	

}

//returns whether or not the trainer has Pokemon that can still battle
bool Trainer::canFight() const
{
	bool canFight = false;
	for (int i = 0; i < m_party.size(); i++)
	{
		if (m_party[i].currentHP() > 0)
		{
			canFight = true;
			break;
		}
	}

	return canFight;
}

//gets the reward for defeating the trainer
int Trainer::getReward() const
{
	//rounded down
	return m_money / 5;
}