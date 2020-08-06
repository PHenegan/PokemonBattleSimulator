#include "GameLauncher.h"

using namespace std;
using namespace pkmn;

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

//closes the files and frees dynamically allocated memory
GameLauncher::~GameLauncher()
{
	m_pokemonList.close();
	m_moveData.close();
	m_pokemonMovepool.close();
	m_saveFile.close();

	delete m_player;
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
	bool newSave = false;

	//prompts the user to enter their name
	do
	{
		cout << "Enter your name: ";
		getline(cin, name);
		m_saveFile.open("trainers\\" + name + ".txt");

		//if there is a problem, the user can either try again or create a new save
		isGood = !m_saveFile.fail();
		if (!isGood)
		{
			m_saveFile.close();
			char choice;
			cout << "A save file for that name was not found or could not be accessed." << endl;
			cout << "Should a new save file be created with that name? (y/N): ";
			cin >> choice;
			cin.ignore();
			
			newSave = (tolower(choice) == 'y');
		}
	} while (!(isGood || newSave));

	if (isGood)
	{
		this->loadSave(name);
	}
	if (newSave)
		this->newTrainer(name);

	this->menu();
}

//initializes the trainer with a new file
void GameLauncher::newTrainer(string name)
{
	m_player = new Trainer(name);
	cout << "Welcome to the world of Pokemon " << name << "!" << endl
		<< "Since you don't have any Pokemon, why don't you catch one?" << endl;
	wildEncounter();
}

//initializes the trainer based on the save file of the given name
void GameLauncher::loadSave(string name)
{
	//resets to the beginning location in case the file was previously read from
	m_saveFile.seekg(0);
	m_saveFile.clear();

	int pokeCount = 0;
	int money; m_saveFile >> money;
	this->m_player = new Trainer(name, money);
	
	string line;
	Pokemon currentPokemon;
	
	try
	{
		while (getline(m_saveFile, line) && pokeCount < MAX_PARTY)
		{

			int num;
			string word;
			istringstream lineStream(line);
			lineStream >> word;

			if (word == "@p")
			{
				//If a pokemon has already been found, fills its stats and adds it to the party
				if (pokeCount > 0)
				{
					currentPokemon.fillSpecies(m_pokemonList);
					m_player->addPokemon(currentPokemon);
				}

				lineStream >> num; currentPokemon = Pokemon(num);
				lineStream >> num; currentPokemon.setLevel(num);

				pokeCount++;
			}
			else if (pokeCount > 0 && word == "IV")
				//iterates through the line and gets the stats
				for (Stat i = HP; i <= SPEED && !lineStream.eof(); i = static_cast<Stat>(i + 1))
				{
					lineStream >> num;
					currentPokemon.setIV(i, num);
				}

			else if (pokeCount > 0 && word == "EV")
				//iterates through the line and gets the stats
				for (Stat i = HP; i <= SPEED && !lineStream.eof(); i = static_cast<Stat>(i + 1))
				{
					lineStream >> num;
					currentPokemon.setEV(i, num);
				}
			else if (pokeCount > 0 && word.length() > 0)
			{
				Move m = getMove(word);
				currentPokemon.addMove(m);
			}
		}
		//The last Pokemon won't be added, so it is added here
		if (pokeCount > 0 && m_player->getParty().size() < MAX_PARTY)
		{
			currentPokemon.fillSpecies(m_pokemonList);
			m_player->addPokemon(currentPokemon);
		}
	}
	catch (string s)
	{
		string error = "Save File Error : incorrect formatting after Party Member " + to_string(pokeCount);
		error += "\n" + s;
		throw error;
	}
	catch (...)
	{
		throw ("Save File Error: incorrect formatting after Party Member " + to_string(pokeCount));
	}
}

void GameLauncher::writeSave()
{
	m_saveFile.close();
	ofstream out("trainers\\" + m_player->getName() + ".txt");


}

void GameLauncher::menu()
{
	bool exit = false;
	do
	{
		int choice;

		cout << endl << endl
			<< "o=============Menu=============o" << endl
			<< "| [1] : Battle a trainer       |" << endl
			<< "| [2] : Find a wild Pokemon    |" << endl
			<< "| [3] : View Trainer info      |" << endl
			<< "| [4] : Save and Exit the game |" << endl
			<< "o==============================o" << endl;
		cout << "\nWhat would you like to do? : "; cin >> choice;

		switch (choice)
		{
		case 1:
			if (m_player->partySize() > 0)
				wildEncounter();
			else
				cout << "You don't have any Pokemon! catch some in the wild first." << endl;
			break;
		case 2:
			wildEncounter();
			break;
		case 3:
			//display trainer info
			break;
		case 4:
			exit = true;
			break;
		default:
			cout << "That was not a valid input. Please enter one of the above numbers" << endl;
		}

	} while (!exit);

	//this->writeSave();
}

//The trainer encounters a random encounter and is prompted to decide whether or not they should catch it
void GameLauncher::wildEncounter() 
{
	Pokemon p = getEncounter();
	cout << "You found a Pokemon!" << endl;
	p.display();
	p.displayMoves();

	cout << "Catch it? (Y/n): ";
}

//Gets Move of specified name
Move GameLauncher::getMove(string name)
{
	//moves the file back to its beginning
	m_moveData.seekg(0);
	m_moveData.clear();

	Move m(name);
	bool found = false;
	string line;
	while (getline(m_moveData, line) && !found)
	{
		int num;
		string word;
		istringstream lineStream(line);
		lineStream >> word;

		//If the move's data has been found, writes it into the move's members
		if (word == name)
		{
			found = true;

			lineStream >> word; m.setType(word);
			lineStream >> num; m.setPower(num);
			lineStream >> num; m.setAccuracy(num);
			lineStream >> num; m.setMaxPP(num);
			lineStream >> num; m.setSpecial(static_cast<bool>(num));
			lineStream >> num; m.setPriority(num);

			//If stat changes are provided, iterates through them and adds them to the Move
			
			//The next 6 numbers (if present) will be the user stat changes
			for (Stat i = HP; i <= SPEED && !lineStream.eof(); i = static_cast<Stat>(i + 1))
			{
				lineStream >> num;
				m.setUserChanges(i, num);
			}
			//The next 6 numbers (if present) will be the target stat changes
			for (Stat i = HP; i <= SPEED && !lineStream.eof(); i = static_cast<Stat>(i + 1))
			{
				lineStream >> num;
				m.setTargetChanges(i, num);
			}
		}
	}

	return m;
}

//gets a random Pokemon with randomized EVs/IVs, a randomized level, and a randomized moveset
Pokemon GameLauncher::getEncounter()
{
	//clears the movepool file
	m_pokemonMovepool.clear();
	m_pokemonMovepool.seekg(0);

	//gets the Pokemon species and creates the Pokemon
	int random = 0; //rand() % m_dexList.size();

	Pokemon p(m_dexList[random]);

	//randomizes stats and sets them to the pokemon
	int level = rand() % 16 + 85;
	for (Stat s = HP; s <= SPEED; s = static_cast<Stat>(s + 1))
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
		else if (line.substr(0, 2) == "@p" && to_string(p.getDexNum()) == line.substr(3))
			foundTarget = true;
		else if (foundTarget)
			moveList.push_back(line);
	}

	//Finds gets a random move from the movepool, adds it to the pokemon, and removes the move from the list
	//this prevents a move from getting picked twice
	for (int i = 0; i < MAX_MOVES && moveList.size() != 0; i++)
	{
		random = rand() % moveList.size();
		Move m = getMove(moveList[random]);
		p.addMove(m);

		vector<string>::iterator position = moveList.begin() + random;
		moveList.erase(position);
	}

	return p;
}