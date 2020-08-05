#include <iostream>
#include <sstream>
#include "type.h"
#include "Pokemon.h"
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
	ifstream types("type_modifiers.txt");
	ifstream pokeList("pokemon_list.txt");

	pkmn::setTypeModifiers(types);

	Pokemon p1(637);
	p1.setLevel(100);
	p1.fillSpecies(pokeList);

	Pokemon p2(6);
	p2.setLevel(100);
	p2.fillSpecies(pokeList);

	Move m1("Flamethrower");
	m1.setPower(90);
	m1.setAccuracy(100);
	m1.setSpecial(true);
	m1.setMaxPP(15);
	m1.setType(pkmn::FIRE);

	Move m2("Air_Slash");
	m2.setPower(75);
	m2.setAccuracy(95);
	m2.setSpecial(true);
	m2.setMaxPP(15);
	m2.setType(pkmn::FLYING);

	p1.addMove(m1);
	p2.addMove(m1);
	p2.addMove(m2);

	p2.setCurrMove(1);
	p2.getCurrMove()->use(&p2, &p1);
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
		{
			file >> typeModifiers[row][col];
		}
}

