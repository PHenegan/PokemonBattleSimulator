#include "Bot.h"
#include <cstdlib>

using namespace std;

Bot::Bot() : Trainer()
{}

Bot::Bot(string name) : Trainer(name)
{}

void Bot::getMoveChoice()
{
	int choice = rand() % getCurrentPokemon()->getNumMoves();
	bool validChoice = false;
	while (!validChoice)
	{
		if (getCurrentPokemon()->getMove(choice).getPP() != 0)
			validChoice = true;
	}
	getCurrentPokemon()->setCurrMove(choice);
}

//Gets switch in for previous pokemon
void Bot::battleSwitch()
{
	for (int i = 1; i < m_party.size(); i++)
		if (!m_party[i].isFainted())
		{
			m_party.switchMembers(0, i);
			break;
		}
	
}