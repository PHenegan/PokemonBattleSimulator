#pragma once
#include <iostream>
#include <sstream>
#include "Battlefield.h"
#include "Bot.h"

//The only reason the methods aren't labeled as const is because most of them make use of
//the file streams, which count as modifications to the data members
class GameLauncher
{
private:
	std::ifstream m_pokemonList;
	std::ifstream m_pokemonMovepool;
	std::ifstream m_moveData;
	std::ifstream m_trainerNames;

	std::ifstream m_saveFile;

	std::vector<int> m_dexList;

	Trainer* m_player;

	GameLauncher();

	void fillDex();

	void newTrainer(std::string name);

	void loadSave(std::string name);
	void writeSave();
	Move getMove(std::string name);
	/*Pokemon getSpecies(int dexNum);
	void fillStats(Pokemon& p, string s);
	void fillTypes(Pokemon& p, string s);*/
	std::string getRandomName();

	void menu();
	void wildEncounter();
	void randomTrainerBattle();

	Pokemon getRandomPokemon();

public:
	GameLauncher(std::string pokemonList, std::string pokemonMovepool, std::string moveData, std::string trainerNames);
	~GameLauncher();

	bool checkFiles() const;

	void launch();
};