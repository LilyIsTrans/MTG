#pragma once

#include <iostream>
#include <vector>
#include "MTG_UUID.h"
#include "imgui.h"

class Card
{
public:

	Card(std::string cardName);

	

	friend std::ostream& operator << (std::ostream& os, const Card& card);
	
	constexpr bool operator==(const Card& other);

public:
	std::string name;
	MTG_UUID id;
};


class Deck
{
public:
	void RenderGui();

	Deck();

	Card& operator[](const size_t idx);
	const Card& operator[](const size_t idx) const;


	size_t size() const;

	friend Deck& operator << (Deck& deck, const Card& card);
	friend Deck& operator >> (Deck& deck, Card& card);

private:
	std::vector<Card> cards;
	char newCardName[256];
};