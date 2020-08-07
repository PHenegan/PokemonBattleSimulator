#include <iostream>
#include "GameLauncher.h"
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace pkmn;

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

int main()
{
	srand(time(0));
	ifstream typeMods("type_modifiers.txt");
	setTypeModifiers(typeMods);
	try
	{
		GameLauncher game("pokemon_list.txt", "pokemon_movepool.txt", "move_data.txt", "name_list.txt");
		game.launch();
	}
	catch (string error)
	{
		cout << error << endl;
	}
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

