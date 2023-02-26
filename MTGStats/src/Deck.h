#pragma once
#include "uuid_utils.h"
#include <string>
#include <unordered_map>

/**
 * \brief Hashes a uuid to a normal int
 *
 * Takes in a uuid and hashes it into a regular int so that it can be used with Dear ImGUI.
 * \param id The uuid to be hashed
 * \return The int hash of the uuid
 */
int int_from_id(uuids::uuid id);

/**
 * \brief Holds information about an individual card.
 */
class Card
{
public:
	/**
	 * \brief Construct a new Card with the specified name.
	 *
	 * Constructs a new Card with the specified name, setting the count and desired minimum to 0.
	 * \param cardName The name of the new card
	 */
	[[nodiscard]] Card(std::string cardName);

	/**
	 * \brief Constructs a new blank Card
	 *
	 * Constructs a blank card with an empty name, a count of 0, and a desired minimum of 0.
	 */
	[[nodiscard]] Card() {
		name = "";
		count = 0;
		desired_minimum = 0;
	}

	
	[[nodiscard]] Card(std::string name, int count, int desired_minimum) : name(name), count(count), desired_minimum(desired_minimum) {}

	//Defining the << operator on instances of card allows them to be easily printed with the normal c++ syntax.
	friend std::ostream& operator << (std::ostream& os, const Card& card);

public:
	std::string name;
	int count; /*The number of copies of this card in the deck*/
	int desired_minimum; /*The minimum number of copies of this card in the initial hand*/
};

/**
 * \brief Holds information about a full deck of cards, with some helper functions for calculating totals across the deck.
 *
 * Mostly just wraps std::unordered_map.
 */
class Deck
{
public:
	/**
	 * \brief Construct an empty Deck
	 */
	[[nodiscard]] Deck();
	[[nodiscard]] Card& operator[](const uuids::uuid& idx);


	[[nodiscard]] size_t size() const;

	[[nodiscard]] uint64_t card_count() const;
	[[nodiscard]] uint64_t desired_min_hand_size() const;

	[[nodiscard]] auto begin() noexcept { return cards.begin(); }
	[[nodiscard]] auto end() noexcept { return cards.end(); }

public:
	std::unordered_map<uuids::uuid, Card> cards;
};