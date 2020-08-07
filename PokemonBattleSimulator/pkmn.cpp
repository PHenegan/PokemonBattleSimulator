#include "pkmn.h"
#include <iostream>

using namespace pkmn;
using namespace std;

namespace pkmn
{
	const int MAX_TYPES = 2;
	const int MAX_MOVES = 4;
	const int MAX_PARTY = 6;
	const int STAT_DELTA = 6;
	const int MAX_IV = 31;
	const int MAX_EV = 252;

	double typeModifiers[NUM_TYPES][NUM_TYPES];
}

//reads type modifiers from a file and checks that the final array is valid
void pkmn::setTypeModifiers(ifstream& file)
{
	//TODO: implement structured exception handling
	if (file.fail())
	{
		cout << "Error: failed to read Type Modifier file" << endl;
		exit(-1);
	}

	for (int row = 0; row < NUM_TYPES && !file.eof(); row++)
		for (int col = 0; col < NUM_TYPES && !file.eof(); col++)
		{
			file >> typeModifiers[row][col];
		}
}

//gets the corresponding type when given a string
Type pkmn::getType(string s)
{
	Type t = NORMAL;
	for (int i = 0; i < pkmn::NUM_TYPES; i++)
		if (s == pkmn::TYPE_NAMES[i])
		{
			t = static_cast<Type>(i);
			break;
		}
	return t;
}

//gets the corresponding type when given a string
Stat pkmn::getStat(string s)
{
	Stat stat = HP;
	for (int i = 0; i < pkmn::NUM_TYPES; i++)
		if (s == pkmn::TYPE_NAMES[i])
		{
			stat = static_cast<Stat>(i);
			break;
		}
	return stat;
}