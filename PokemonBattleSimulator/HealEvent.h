#pragma once
#include "Battlefield.h"
#include "FieldEvent.h"
#include "Party.h"

class HealEvent : public FieldEvent
{
private:
	int m_amount;
	Pokemon* m_user;

public:
	HealEvent(int amount, Pokemon* user);
	bool run();
};

