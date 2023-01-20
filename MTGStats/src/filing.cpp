#include "filing.h"
#include <string>
#include "Deck.h"
#include <fstream>
#include "MTG_UUID.h"
#include <iostream>

void load_deck_from_file(Deck& deck, std::string filename)
{
	std::ifstream file;
	file.open(filename, std::ios::in);
	std::cout << "Attempting to open file: " << filename << "as deck";
	std::string temp;
	std::string name;
	int count;
	int desired_amount;
	while (file.good())
	{
		while (temp.back() != '\r' && temp.back() != '\n')
		{
			file >> temp;
			name.append(temp);
			temp.clear();
			name.push_back(' ');
		}
		
		file >> count;
		file >> desired_amount;
		Card card = Card(name);
		card.count = count;
		card.desired_minimum = desired_amount;
	}
	file.close();
}
