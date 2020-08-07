#include "Trainer.h"
#include <iostream>

using namespace std;

//Default constructor
Trainer::Trainer() : m_name(""), m_party()
{}

//Constructor with values
Trainer::Trainer(string name)
{
	this->m_name = name;
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

//Prompts the trainer to set the Current Pokemon's current move
void Trainer::getMoveChoice()
{
	getCurrentPokemon()->displayMoves();
	cout << endl;

	int choice;
	do
	{
		cout << "Pick a move: "; cin >> choice;
		cin.ignore();

		if (choice < 1 || choice > getCurrentPokemon()->getNumMoves())
			cout << "Invalid choice. Please pick one of the above options." << endl;

	} while (choice < 1 || choice > getCurrentPokemon()->getNumMoves());

	cout << endl;
	getCurrentPokemon()->setCurrMove(choice - 1);

}

//prompts the trainer to switch into a different Pokemon on their team
void Trainer::battleSwitch()
{
	cout << endl;
	m_party.display();
	
	int choice;
	bool validChoice = false;
	cout << endl;
	while (!validChoice)
	{
		cout << "Pick a Pokemon to switch into: "; cin >> choice;
		cin.ignore();

		if (choice < 1 || choice > m_party.size())
			cout << "Please enter the number of one of the above Pokemon." << endl;
		else if (m_party[choice - 1].isFainted())
			cout << "You cannot switch into a Pokemon that cannot Battle." << endl;
		else
			validChoice = true;
	} 
	m_party.switchMembers(0, choice - 1);

}

//If the trainer's team is full, gets a prompt to choose which pokemon to replace
//returns true if a pokemon has been replaced
bool Trainer::replacePokemon(Pokemon p)
{
	m_party.display();
	int choice;
	bool willContinue;

	//prompts the user to make a choice until they enter a valid input
	do
	{
		cout << "\nWhich pokemon would you like to replace? (Enter 0 to go back) ";
		cin >> choice;
		if (choice < 0 || choice > m_party.size())
			cout << "Please choose one of the options above." << endl;

	} while (choice < 0 || choice > m_party.size());
	
	willContinue = static_cast<bool>(choice);

	//If the trainer has chosen a pokemon to replace, replaces it with the given Pokemon
	if (willContinue)
		m_party.replaceMember(choice - 1, p);

	return willContinue;
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
