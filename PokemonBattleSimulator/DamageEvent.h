#pragma once
#include "FieldEvent.h"
#include "Pokemon.h"

class DamageEvent : public FieldEvent
{
private:
	Pokemon* m_target;
	int m_amount;
	bool m_isSpecial;
	pkmn::Type typeDamage;
public:
	DamageEvent(Pokemon* target, int amount, bool isSpecial, pkmn::Type type);
	bool run();
};

