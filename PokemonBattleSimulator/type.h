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
	
	//Pokemon Statistics
	enum Stat 
	{ 
		HP, ATK, SPATK, 
		DEF, SPDEF, SPEED
	};
	const std::string STAT_NAMES[] = 
	{
		"HP", "Attack", "Special Attack", 
		"Defense", "Special Defense", "Speed"
	};

	const int NUM_STATS = 6;

	//Maximum values
	const int MAX_TYPES = 2;
	const int MAX_MOVES = 4;
	const int MAX_PARTY = 6;

	//The first dimension represents the attacking type
	//The second dimension represents the defending type
	static double typeModifiers[NUM_TYPES][NUM_TYPES];

	void setTypeModifiers(std::ifstream& file);
}
