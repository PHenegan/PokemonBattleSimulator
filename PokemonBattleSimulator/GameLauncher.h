#pragma once
#include <iostream>
#include <sstream>
#include "Trainer.h"

class GameLauncher
{
private:
	std::ifstream m_pokemonList;
	std::ifstream m_pokemonMovepool;
	std::ifstream m_moveData;

	std::ifstream m_saveFile;

	std::vector<int> m_dexList;

	Trainer* m_player;

	GameLauncher();

public:
	GameLauncher(std::string pokemonList, std::string pokemonMovepool, std::string moveData);
	~GameLauncher();

	bool checkFiles() const;

	void launch();
	void fillDex();

	void newTrainer(std::string name);

	void loadSave(std::string name);
	void writeSave();
	void wildEncounter();
	
	Pokemon getEncounter();
	Move getMove(std::string name);

	void randomTrainerBattle();
};