#include "Deck.h"

int int_from_id(uuids::uuid id)
{
	int acc = 0;
	for (size_t i = 0; i < sizeof(int); ++i)
	{
		acc |= ((int)(id.as_bytes()[i]) << i * 8);
	}
	return acc;
}

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

uint64_t Deck::card_count() const
{
	uint64_t acc = 0;
	for (auto [id, card] : cards)
	{
		acc += card.count;
	}
	return acc;
}

uint64_t Deck::desired_min_hand_size() const
{
	uint64_t acc = 0;
	for (auto [id, card] : cards)
	{
		acc += card.desired_minimum;
	}
	return acc;
}

Card::Card(std::string cardName)
{
	name = cardName;
	id = MTG_UUID();
	count = 0;
	desired_minimum = 0;
}

bool Card::operator==(const Card& other)
{
	return id == other.id;
}
