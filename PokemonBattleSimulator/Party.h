#pragma once
#include "Pokemon.h"
#include <initializer_list>

class Party
{
private:
	Pokemon* m_partyArray;
	int m_size;
public:
	Party();
	Party(std::initializer_list<Pokemon> list);
	Party(const Party& p);
	~Party();

	void addMember(Pokemon p);
	void replaceMember(int index, Pokemon p);
	void switchMembers(int index1, int index2);
	
	Pokemon at(int index) const;
	int getSize() const;

	Pokemon operator [] (int index) const;
};

