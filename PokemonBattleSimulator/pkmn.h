#pragma once
#include <fstream>
#include <string>

namespace pkmn
{
	//Pokemon Types
	//When I tried changing "enum" to "enum class" the warnings didn't go away, but I also ended up
	//with a bunch of errors. Because of that, I left both of them as "enum"
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
		HP, ATK, DEF, 
		SPATK, SPDEF, SPEED
	};
	const std::string STAT_NAMES[] =
	{
		"HP", "Attack", "Defense",
		"Special Attack", "Special Defense", "Speed"
	};

	const int NUM_STATS = 6;

	//Maximum values
	const extern int MAX_TYPES;
	const extern int MAX_MOVES;
	const extern int MAX_PARTY;
	const extern int STAT_DELTA;
	const extern int MAX_IV;
	const extern int MAX_EV;


	//I'm fairly certain that there's a warning coming from this declaration, but since I'm reading this
	//from a file I don't really know how else I could resolve this error.

	//The first dimension represents the attacking type
	//The second dimension represents the defending type
	extern double typeModifiers[NUM_TYPES][NUM_TYPES];

	void setTypeModifiers(std::ifstream& file);
	Type getType(std::string s);
	Stat getStat(std::string s);
}
