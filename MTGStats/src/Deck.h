#pragma once

#include <iostream>
#include <vector>
#include "MTG_UUID.h"
#include "imgui.h"
#include <unordered_map>

class Card
{
public:

	Card(std::string cardName);

	Card() {
		name = "";
		count = 0;
		id = MTG_UUID();
	}

	friend std::ostream& operator << (std::ostream& os, const Card& card);
	
	bool operator==(const Card& other);



public:
	std::string name;
	MTG_UUID id;
	int count;
};


class Deck
{
public:
	void RenderGui();

	Deck();
	Card& operator[](uuids::uuid idx);


	size_t size() const;

private:
	std::unordered_map<uuids::uuid, Card> cards;
	char newCardName[256];
	int newCardCount;
};