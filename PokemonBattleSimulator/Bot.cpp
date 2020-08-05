#include "Bot.h"
#include <cstdlib>

using namespace std;

Bot::Bot() : Trainer()
{
	m_reward = 500;
}
Bot::Bot(string name, int reward /*= 500*/) : Trainer(name)
{
	m_reward = reward;
}

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
		if (!m_party[i].isFeinted())
		{
			m_party.switchMembers(0, i);
			break;
		}
	
}

int Bot::getReward()
{
	return m_reward;
}