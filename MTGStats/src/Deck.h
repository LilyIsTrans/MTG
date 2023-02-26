#pragma once


#include <vector>
#include "uuid_utils.h"
#include "imgui.h"
#include <unordered_map>

// This helper function hashes a uuid down to a basic int. This is used for interacting with Dear ImGUI,
// which needs a unique int for each card in order to display them. 
int int_from_id(uuids::uuid id);


class Card
{
public:

	Card(std::string cardName);

	Card() {
		name = "";
		count = 0;
		desired_minimum = 0;
	}

	friend std::ostream& operator << (std::ostream& os, const Card& card);

public:
	std::string name;
	int count;
	int desired_minimum;
};


class Deck
{
public:

	Deck();
	Card& operator[](uuids::uuid idx);


	size_t size() const;

	uint64_t card_count() const;
	uint64_t desired_min_hand_size() const;

public:
	std::unordered_map<uuids::uuid, Card> cards;
	char newCardName[256];
	int newCardCount;
};