#include "HealEvent.h"

HealEvent::HealEvent(int amount, Pokemon* user)
{
	m_amount = amount;
	m_user = user;
}

bool HealEvent::run()
{
	int initHP = m_user->currentHP();
	
	m_user->addHP(m_amount);

	int finalHP = m_user->currentHP();

	//returns false if the HP amount did not change
	return finalHP - initHP;
}