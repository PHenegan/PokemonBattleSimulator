#include "GameLauncher.h"

using namespace std;

//the strings are the names of the files that will be loaded
GameLauncher::GameLauncher(string pokemonList, string movepool, string moveData)
{
	m_pokemonList.open(pokemonList);
	m_pokemonMovepool.open(movepool);
	m_moveData.open(moveData);

	if (this->checkFiles())
		throw("Game Launcher error: one or more of the files provided does not exist or could not be accessed.");
	this->fillDex();
}

//returns true if a file has failed
bool GameLauncher::checkFiles() const
{
	return (m_pokemonList.fail() || m_pokemonMovepool.fail() || m_moveData.fail());
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

//runs the game and gets the user's name
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
			cout << "Should a new save file be created with that name? (y/N): ";
			cin >> choice;
			cin.ignore();
			
			newSave = (tolower(choice) == 'y');
		}
	} while (!(isGood || newSave));
}

void GameLauncher::newTrainer(string name)
{
	player = Trainer(name);
	cout << "Since you don't have any Pokemon, why don't you catch one?" << endl;
	wildEncounter();
}

//The trainer encounters a random encounter and is prompted to decide whether or not they should catch it
void GameLauncher::wildEncounter() 
{
	Pokemon p = getEncounter();
	cout << "You found a Pokemon!" << endl;
	p.display();
}

//gets a random Pokemon with randomized EVs/IVs, a randomized level, and a randomized moveset
Pokemon GameLauncher::getEncounter()
{
	//gets the Pokemon species and creates the Pokemon
	int random = 0; //rand() % m_dexList.size();
	
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
	bool foundTarget = false;
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

	//Finds gets a random move from the movepool, adds it to the pokemon, and removes the move from the list
	//this prevents a move from getting picked twice
	for (int i = 0; i < pkmn::MAX_MOVES && moveList.size() != 0; i++)
	{
		random = rand() % moveList.size();
		Move m = getMove(moveList[random]);
		p.addMove(m);

		vector<string>::iterator position = moveList.begin() + random;
		moveList.erase(position);
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
			lineStream >> num; m.setSpecial(static_cast<bool>(num));
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

	return m;
}