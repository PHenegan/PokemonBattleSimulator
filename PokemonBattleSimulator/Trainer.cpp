#include "Trainer.h"
#include <iostream>

using namespace std;

//Default constructor
Trainer::Trainer() : m_name(""), m_party(), m_money(0)
{}

//Constructor with values
Trainer::Trainer(string name, int money /*= 0*/)
{
	this->m_name = name;
	this->m_money = money;
}

//returns trainer name
string Trainer::getName() const 
{
	return m_name;
}

//returns the size of the trainer's party
int Trainer::partySize() const
{
	return m_party.size();
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

//Prompts the trainer to set the Current Pokemon's current move
void Trainer::getMoveChoice()
{
	getCurrentPokemon()->displayMoves();

	int choice;
	do
	{
		cout << "Pick a move: "; cin >> choice;
		cin.ignore();

		if (choice < 1 || choice > getCurrentPokemon()->getNumMoves())
			cout << "Invalid choice. Please pick one of the above options." << endl;

	} while (choice < 1 || choice > getCurrentPokemon()->getNumMoves());

	getCurrentPokemon()->setCurrMove(choice - 1);

}

//prompts the trainer to switch into a different Pokemon on their team
void Trainer::battleSwitch()
{
	m_party.display();
	
	int choice;
	bool validChoice = false;
	while (!validChoice)
	{
		cout << "Pick a Pokemon to switch into: "; cin >> choice;
		cin.ignore();

		if (choice < 1 || choice > m_party.size())
			cout << "Please enter the number of one of the above Pokemon." << endl;
		else if (m_party[choice].isFeinted())
			cout << "You cannot switch into a Pokemon that cannot Battle." << endl;
		else
			validChoice = true;
	} 
	m_party.switchMembers(0, choice - 1);

}

//sets the party
void Trainer::setParty(Party p)
{
	m_party = p;
}

//Adds the specified pokemon to the trainer's team
void Trainer::addPokemon(Pokemon p)
{
	if (m_party.size() < pkmn::MAX_PARTY)
		m_party.addMember(p);
}


//adds the specified amount to the trainer's wallet. howMuch can be negative
void Trainer::addMoney(int howMuch)
{
	m_money += howMuch;
	if (m_money < 0)
		m_money = 0;
}

//Heals all of the Pokemon in the trainer's party
void Trainer::heal()
{
	for (int i = 0; i < m_party.size(); i++)
		m_party[i].heal();
}

//Displays the trainer's name in a stream
ostream& operator << (ostream& stream, const Trainer& t)
{
	stream << t.getName();
	return stream;
}
