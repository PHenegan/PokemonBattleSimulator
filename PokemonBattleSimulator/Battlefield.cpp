#include "Battlefield.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Battlefield::Battlefield(Trainer* tr1, Trainer* tr2)
{
	m_turn = 0;
	this->m_tr1 = tr1;
	this->m_tr2 = tr2;
}

void Battlefield::battle()
{
	while (m_tr1->canFight() && m_tr2->canFight())
	{
		this->runTurn();
	}
}

void Battlefield::runTurn()
{
	//There will only ever be two pokemon on the field at one point
	const int NUM_POKE = 2;
	Pokemon* pokemon[] = { m_tr1->getCurrentPokemon(), m_tr2->getCurrentPokemon() };
	
	//sorts the move priority
	sortPriority(pokemon, NUM_POKE);

	m_turn++;
}

void Battlefield::display() const
{
	cout << m_tr2->getCurrentPokemon()->display();
	cout << "\n\n\n\n";
	cout << m_tr1->getCurrentPokemon()->display();
}

void Battlefield::sortPriority(Pokemon** list, int size)
{
	//Sorts the list based on priority or how fast the Pokemon is
	for (int sorted = 0; sorted < size; sorted++)
		for (int unsorted = sorted + 1; unsorted < size; unsorted++)
		{
			Move* m1 = list[sorted]->getCurrMove();
			Move* m2 = list[unsorted]->getCurrMove();

			//If priority is different
			if (m1->m_priority < m2->m_priority)
				swap(list[sorted], list[unsorted]);
			
			//If priority is the same and speed is different
			else if (m1->m_priority == m2->m_priority && *(list[sorted]) < *(list[unsorted]))
				swap(list[sorted], list[unsorted]);
			
			//If priority is the same and speed is the same, determines randomly
			else if (m1->m_priority == m2->m_priority && *(list[sorted]) == *(list[unsorted]))
			{
				int coin = rand() % 2;
				if (coin)
					swap(list[sorted], list[unsorted]);
			}

		}
}