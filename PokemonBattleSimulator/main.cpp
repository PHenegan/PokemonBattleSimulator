#include <iostream>
#include "GameLauncher.h"
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace pkmn;

int main()
{
	srand(time(0));

	ifstream typeMods("type_modifiers.txt");
	setTypeModifiers(typeMods);
	try
	{
		GameLauncher game("data\\pokemon_list.txt", "data\\pokemon_movepool.txt", "data\\move_data.txt", "data\\name_list.txt");
		game.launch();
	}
	catch (string error)
	{
		cout << error << endl;
	}
}

