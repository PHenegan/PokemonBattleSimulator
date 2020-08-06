#include "GameLauncher.h"

using namespace std;

//the strings are the names of the files that will be loaded
GameLauncher::GameLauncher(string pokemonList, string movepool, string moveData, string wildData)
{
	m_pokemonList.open(pokemonList);
	m_pokemonMovepool.open(movepool);
	m_moveData.open(moveData);
	m_wildData.open(wildData);

	this->fillDex();
}

//fills the pokedex with the numbers of available pokemon
void GameLauncher::fillDex()
{
	while (!m_pokemonList.eof())
	{
		string word;
		istringstream lineStream;
		string currentLine;
		int dexNum;

		getline(m_pokemonList, currentLine);
		lineStream = istringstream(currentLine);
		
		lineStream >> word;
		if (word == "@p")
		{
			lineStream >> dexNum;
			m_dexList.push_back(dexNum);
		}
			
	}
}

void GameLauncher::launch()
{
	string name;

	bool isGood;
	bool newSave;

	//prompts the user to enter their name
	do
	{
		cout << "Enter your name: ";
		getline(cin, name);
		name += ".txt";
		m_saveFile.open(name);


		isGood = !m_saveFile.fail();

		//if there is a problem, the user can either try again or create a new save
		if (!isGood)
		{
			char choice;
			cout << "A save file for that name was not found or could not be accessed." << endl;
			cout << "Enter 0 to create a new save file or anything else to try again";
			cin >> choice;
			cin.ignore();
			
			newSave = (choice == '0');
		}
	} while (!(isGood || newSave));
}

void GameLauncher::newTrainer(string name)
{
	player = Trainer(name);
	cout << "Since you don't have any Pokemon, why don't you catch one?" << endl;
	wildEncounter();
}

void GameLauncher::wildEncounter() 
{
	Pokemon p = getEncounter();
	cout << "You found a Pokemon!" << endl;
	p.display();

	bool shouldCatch;
	int choice;
	cout << "Enter 1 to catch the pokemon, or anything else to run away.";
	if (choice == 1)
	{

	}

}

//gets a random Pokemon with randomized EVs/IVs, a randomized level, and a randomized moveset
Pokemon GameLauncher::getEncounter()
{
	//gets the Pokemon species and creates the Pokemon
	int random = rand() % m_dexList.size();
	
	Pokemon p(m_dexList[random]);

	//randomizes stats and sets them to the pokemon
	int level = rand() % 16 + 85;
	for (pkmn::Stat s = pkmn::HP; s < pkmn::SPEED; s = static_cast<pkmn::Stat>(s + 1))
	{
		p.setEV(s, rand() % 253);
		p.setIV(s, rand() % 32);
	}
	p.setLevel(level);
	p.fillSpecies(m_pokemonList);

	//Gets movepool by looking through the pokemon's file
	vector<string> moveList;
	bool foundTarget;
	while (!m_pokemonMovepool.eof())
	{
		string line;
		getline(m_pokemonMovepool, line);
		//Once the next pokemon is reached, breaks
		if (line.substr(0, 2) == "@p" && foundTarget)
			break;
		//If the target is found, starts reading move names
		else if (line.substr(0, 2) == "@p")
			foundTarget = true;
		else if (foundTarget)
			moveList.push_back(line);
	}




	return p;
}

//Gets Move of specified name
Move GameLauncher::getMove(string name)
{
	//moves the file back to its beginning
	m_moveData.seekg(0);
	m_moveData.clear();

	Move m(name);

	string line;
	while (getline(m_moveData, line))
	{
		int num;
		string word;
		istringstream lineStream(line);
		lineStream >> word;

		//If the move's data has been found, writes it into the move's members
		if (word == name)
		{
			lineStream >> word; m.setType(name);
			lineStream >> num; m.setPower(num);
			lineStream >> num; m.setAccuracy(num);
			lineStream >> num; m.setMaxPP(num);
			lineStream >> num; m.setPriority(num);

			for (pkmn::Stat i = pkmn::HP; i < pkmn::SPEED; i = static_cast<pkmn::Stat>(i + 1))
			{
				lineStream >> num;
				m.setUserChanges(i, num);
			}
			for (pkmn::Stat i = pkmn::HP; i < pkmn::SPEED; i = static_cast<pkmn::Stat>(i + 1))
			{
				lineStream >> num;
				m.setTargetChanges(i, num);
			}
			//if the move has been found, there is no need to keep going through the loop
			break;
		}
	}
}