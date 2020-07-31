#pragma once
#include <fstream>

namespace pkmn
{
	//Pokemon Types
	enum Type
	{
		NORMAL, FIRE, WATER, GRASS, ELECTRIC, ICE,
		FIGHTING, POISON, GROUND, FLYING, PSYCHIC, BUG,
		ROCK, GHOST, DRAGON, DARK, STEEL, FAIRY
	};
	const std::string TYPE_NAMES[] =
	{
		"Normal", "Fire", "Water", "Grass", "Electric", "Ice",
		"Fighting", "Poison", "Ground", "Flying", "Psychic", "Bug",
		"Rock", "Ghost", "Dragon", "Dark", "Steel", "Fairy"
	};

	const int NUM_TYPES = 18;
	const int NUM_STATS = 6;

	//The first dimension represents the attacking type
	//The second dimension represents the defending type
	static double typeModifiers[NUM_TYPES][NUM_TYPES];

	void setTypeModifiers(std::ifstream& file);
}
