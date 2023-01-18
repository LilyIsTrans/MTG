#include "Deck.h"

std::ostream& operator<<(std::ostream& os, const Card& card)
{
	// TODO: insert return statement here
	os << card.name;
	return os;
}

Deck& operator<<(Deck& deck, const Card& card)
{
	// TODO: insert return statement here
	deck.cards.push_back(card);
	return deck;
}

Deck& operator>>(Deck& deck, Card& card)
{
	// TODO: insert return statement here
	card = deck.cards.back();
	deck.cards.pop_back();
	return deck;
}

Deck::Deck()
{
	cards.reserve(120);
}

Card& Deck::operator[](const size_t idx)
{
	return cards[idx];
}

const Card& Deck::operator[](const size_t idx) const
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

constexpr bool Card::operator==(const Card& other)
{
	return id == other.id;
}
