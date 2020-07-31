#include "Pokemon.h"
#include <sstream>
#include <iostream>

using namespace std;

Pokemon::Pokemon(int dexNum) : m_name(""), m_currHP(0), m_level(0), m_dexNum(dexNum), m_stats()
{
	for (int i = 0; i < 6; i++)
		m_stats[i] = 0;
}

int Pokemon::getDexNum() const
{
	return m_dexNum;
}

string Pokemon::getName() const
{
	return m_name;
}

//getStats

//calculates the damage modifier a type has on this pokemon. Stacks for each type
double Pokemon::calculateDamageMod(pkmn::Type t) const
{
	int mod = 1;
	for (pkmn::Type type : m_types)
		mod *= pkmn::typeModifiers[t][type];

	return mod;
}

void Pokemon::fillSpecies(ifstream &file)
{
	string name;
	int stats[6];
	string temp;
	bool found = false;

	while (!file.eof())
	{
		//gets the current line and puts it into a string steam
		getline(file, temp);

		//If the target pokemon is found, adds species data into object
		if (temp.length() >= 4 && 
			temp.substr(0, 2) == "@p" &&
			temp.substr(3) == to_string(m_dexNum)
			)
		{
			found = true;
			getline(file, m_name);
			cout << "Found " << m_name << endl;


			//processes type line
			getline(file, temp); 
			fillTypes(temp);
			
			//processes stats line
			getline(file, temp); 
			fillStats(temp);

		}
	}
	if (!found)
	{
		//structured exception handling
	}
}

void Pokemon::fillTypes(string s)
{
	vector<string> types;
	string temp;
	int count = 0;

	istringstream line(s);
	while (!line.eof())
	{
		line >> temp;
		types.push_back(temp);
	}

	for (string name : types)
		for (int i = 0; i < pkmn::NUM_TYPES; i++)
			if (name == pkmn::TYPE_NAMES[i])
			{
				m_types.push_back(static_cast<pkmn::Type>(i));
				count++;
			}
	if (count == 0)
	{
		//Structured Exception Handling here
	}
}

void Pokemon::fillStats(string s)
{
	int i = 0;
	istringstream line(s);
	
	while (i < pkmn::NUM_STATS && !line.eof())
	{
		line >> m_stats[i++];
	}
	if (i < 6)
	{
		//structured exception handling here
	}
}

