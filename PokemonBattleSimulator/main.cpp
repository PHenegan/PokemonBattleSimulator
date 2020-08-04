#include <iostream>
#include <sstream>
#include "type.h"
#include "Pokemon.h"

using namespace std;
using namespace pkmn;

int main()
{
	ifstream types("type_modifiers.txt");
	ifstream pokeList("pokemon_list.txt");

	setTypeModifiers(types);

	Pokemon p1(1);
	p1.fillSpecies(pokeList);

	p1.display();
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
			file >> typeModifiers[row][col];
}

