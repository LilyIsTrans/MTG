#include "filing.h"
#include <string>
#include "Deck.h"
#include <fstream>
#include "uuid_utils.h"

void load_deck_from_file(Deck& deck, std::string filename)
{
	std::ifstream file;
	file.open(filename, std::ios::in);
	std::string temp;
	std::string name;
	int count;
	int desired_amount;
	while (!file.eof())
	{
		file >> name;
		while (file.peek() != '\r' && file.peek() != '\n')
		{
			name.push_back(file.get());
		}
		
		file >> count;
		file >> desired_amount;
		Card card = Card(name);
		card.count = count;
		card.desired_minimum = desired_amount;
		deck.cards[gen_uuid()] = card;
	}
	file.close();
}
