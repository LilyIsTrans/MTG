#include "Deck.h"

#include <ranges>


int int_from_id(const uuids::uuid id)
{
	int acc = 0;
	for (size_t i = 0; i < sizeof(id); ++i)
	{
		acc ^= (static_cast<int>(id.as_bytes()[i]) << (i % sizeof(int)) * 8);
	}
	return acc;
}


std::ostream& operator<<(std::ostream& os, const card& card)
{
	os << card.name;
	return os;
}

deck::deck()
{
	cards.reserve(120); // In MTG, the largest commonly used deck size I know of is 120, so I made sure the table could handle at least that many before needing to resize.
}


card& deck::operator[](const uuids::uuid& idx)
{
	return cards[idx];
}


size_t deck::size() const
{
	return cards.size();
}

uint64_t deck::card_count() const
{
	uint64_t acc = 0;
	for (auto& card : cards | std::views::values)
	{
		acc += card.count;
	}
	return acc;
}

uint64_t deck::desired_min_hand_size() const
{
	uint64_t acc = 0;
	for (auto card& : cards | std::views::values)
	{
		acc += card.desired_minimum;
	}
	return acc;
}

card::card(std::string card_name)
{
	name = std::move(card_name);
	count = 0;
	desired_minimum = 0;
}
