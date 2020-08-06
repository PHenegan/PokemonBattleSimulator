#pragma once
#include "Trainer.h"

class Bot : public Trainer
{
private:
	int m_reward;

public:

	Bot();
	Bot(std::string name);

	void getMoveChoice();
	void battleSwitch();
};

