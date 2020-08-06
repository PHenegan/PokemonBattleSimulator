#include "Battlefield.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Battlefield::Battlefield(Trainer* tr1, Trainer* tr2)
{
	m_turn = 0;

	this->m_tr1 = tr1;
	this->m_tr2 = tr2;

	m_winner = nullptr;
	m_loser = nullptr;
}

void Battlefield::battle()
{
	//Any switches made in battle are reverted afterwards
	//Because of this, the parties are copied at the beginning of a battle
	Party p1 = m_tr1->getParty();
	Party p2 = m_tr2->getParty();


	while (m_tr1->canFight() && m_tr2->canFight())
	{
		this->runTurn();
	}

	cout << **m_winner << " defeated " << **m_loser << '!' << endl;

	//Parties are reset to their previous state
	//this also heals the pokemon because their HP gets reset to what it was before the battle
	m_tr1->setParty(p1);
	m_tr2->setParty(p1);
}

void Battlefield::runTurn()
{
	//There will only ever be two pokemon on the field at one point
	const int NUM_POKE = 2;
	
	display();

	Pokemon* pokemon[] = { m_tr1->getCurrentPokemon(), m_tr2->getCurrentPokemon() };

	m_tr1->getMoveChoice();
	m_tr2->getMoveChoice();

	//sorts the move priority
	sortPriority(pokemon, NUM_POKE);

	//each Pokemon will use their move on the opposite pokemon
	cout << pokemon[0]->getName() << " used " << *pokemon[0]->getCurrMove() << "!" << endl;
	if (!pokemon[0]->getCurrMove()->use(pokemon[0], pokemon[1]))
		cout << "It missed!" << endl;

	//If the first attack landed and didn't cause the pokemon to feint, the second pokemon uses its move
	if (!pokemon[1]->isFeinted())
	{
		cout << pokemon[1]->getName() << " used " << *pokemon[1]->getCurrMove() << "!" << endl;
		if (!pokemon[1]->getCurrMove()->use(pokemon[1], pokemon[0]))
			cout << "It missed!" << endl;
	}
	
	//If one of the pokemon feints, gets the next pokemon from the trainer

	if (m_tr1->getCurrentPokemon()->isFeinted() && m_tr1->canFight())
		m_tr1->battleSwitch();

	else if (!m_tr1->canFight())
	{
		m_winner = &m_tr2;
		m_loser = &m_tr2;
	}

	if (m_tr2->getCurrentPokemon()->isFeinted() && m_tr2->canFight())
		m_tr2->battleSwitch();
	
	else if (!m_tr2->canFight())
	{
		m_winner = &m_tr1;
		m_loser = &m_tr2;
	}

	m_turn++;
}

//displays the health of each Pokemon
void Battlefield::display() const
{
	cout << "\n";
	m_tr2->getCurrentPokemon()->display();
	cout << "\n\n";
	m_tr1->getCurrentPokemon()->display();
	cout << "\n";
}

void Battlefield::sortPriority(Pokemon** list, int size)
{
	//Sorts the list based on priority or how fast the Pokemon is
	//This is mostly future-proofing because right now it's only comparing two pokemon
	//If I ever add a "Doubles" mode, 4 pokemon would be on at a time, and this would be more useful
	for (int sorted = 0; sorted < size; sorted++)
		for (int unsorted = sorted + 1; unsorted < size; unsorted++)
		{
			Move* m1 = list[sorted]->getCurrMove();
			Move* m2 = list[unsorted]->getCurrMove();

			//If priority is different
			if (m1->getPriority() < m2->getPriority())
				swap(list[sorted], list[unsorted]);
			
			//If priority is the same and speed is different
			else if (m1->getPriority() == m2->getPriority() && *(list[sorted]) < *(list[unsorted]))
				swap(list[sorted], list[unsorted]);
			
			//If priority is the same and speed is the same, determines randomly
			else if (m1->getPriority() == m2->getPriority() && *(list[sorted]) == *(list[unsorted]))
			{
				int coin = rand() % 2;
				if (coin)
					swap(list[sorted], list[unsorted]);
			}

		}
}

