#pragma once
#include "Trainer.h"

class Bot : public Trainer
{
public:
	Bot();
	Bot(std::string name);

	void getMoveChoice();
	void battleSwitch();
};

