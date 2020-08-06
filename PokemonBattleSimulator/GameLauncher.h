#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Trainer.h"
#include <vector>

class GameLauncher
{
private:
	std::ifstream m_pokemonList;
	std::ifstream m_pokemonMovepool;
	std::ifstream m_wildData;
	std::ifstream m_moveData;

	std::ifstream m_saveFile;

	std::vector<int> m_dexList;

	Trainer player;

	GameLauncher();

public:
	GameLauncher(std::string pokemonList, std::string pokemonMovepool, std::string moveData, std::string wildData);
	~GameLauncher();

	void launch();
	void fillDex();

	void newTrainer(std::string name);

	void loadSave(std::string name);
	void wildEncounter();
	Pokemon getEncounter();
	Move getMove(std::string name);

	void randomTrainerBattle();
};


