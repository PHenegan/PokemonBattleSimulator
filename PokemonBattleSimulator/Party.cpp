#include "Party.h"
#include "type.h"
#include <iostream>

using namespace std;

//Default constructor
Party::Party()
{
	m_size = 0;
	m_partyArray = new Pokemon[m_size];
}

//initializer list constructor
Party::Party(std::initializer_list<Pokemon> list)
{
	if (list.size() > pkmn::MAX_PARTY || list.size() == 0)
		throw("Error: Party size is not valid");

	m_size = static_cast<int>(list.size());
	m_partyArray = new Pokemon[m_size];

	Pokemon* ptr = m_partyArray;
	for (Pokemon p : list)
	{
		*ptr = p;
		ptr++;
	}
}

//copy constructor
Party::Party(const Party& p)
{
	this->m_size = p.size();
	for (int i = 0; i < m_size; i++)
	{
		m_partyArray[i] = p[i];
	}
}

//destructor
Party::~Party()
{
	if (m_size > 0)
		delete[] m_partyArray;
}

//Adds specified Pokemon to the party
void Party::addMember(Pokemon p)
{
	if (m_size >= pkmn::MAX_PARTY)
		throw("Error: cannot add members to a party that is already full");

	//Creates a new array, fills it with the previous pokemon, then adds the new one
	Pokemon* tempArray = new Pokemon[m_size + 1];

	for (int i = 0; i < m_size; i++)
		tempArray[i] = m_partyArray[i];

	tempArray[m_size] = p;

	if (m_size > 0)
		delete[] m_partyArray;
	m_partyArray = tempArray;
	
	m_size++;
}

//Replace the party member at the specified index with the specified Pokemon
void Party::replaceMember(int index, Pokemon p)
{
	if (index < 0 || index >= m_size)
		throw("Party Error: index does not exist");

	m_partyArray[index] = p;
}

//Swaps the members at the two specified indices
void Party::switchMembers(int index1, int index2)
{
	if (index1 >= m_size || index2 >= m_size || index1 < 0 || index2 < 0)
		throw("Party Error: index does not exist");
}

//returns the member at the specified index in the party
Pokemon Party::at(int index) const
{
	if (index < 0 || index >= m_size)
		throw("Party Error: index does not exist");
	
	return m_partyArray[index];
}

//returns how many Pokemon are in the party
int Party::size() const
{
	return m_size;
}

//returns a reference to the Pokemon at the specified index of the party
Pokemon& Party::operator [] (int index) const
{
	if (index < 0 || index >= m_size)
		throw("Party Error: index does not exist");

	return m_partyArray[index];
}

//Displays Each member of the party
void Party::display() const
{
	for (int i = 0; i < m_size; i++)
	{
		cout << "{" << i + 1 << "} : "; m_partyArray[i].display();
	}
}