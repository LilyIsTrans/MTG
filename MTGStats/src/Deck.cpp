#include "Deck.h"

std::ostream& operator<<(std::ostream& os, const Card& card)
{
	// TODO: insert return statement here
	os << card.name;
	return os;
}

Deck::Deck()
{
	cards.reserve(120);
	newCardName[0] = 0;
	newCardCount = 0;
}

Card& Deck::operator[](uuids::uuid idx)
{
	return cards[idx];
}


size_t Deck::size() const
{
	return cards.size();
}

Card::Card(std::string cardName)
{
	name = cardName;
	id = MTG_UUID();
}

bool Card::operator==(const Card& other)
{
	return id == other.id;
}
