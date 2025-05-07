#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "Card.h"
#include <string>

class Deck
{
	public :
		std::vector<Card> _cards;
		uint32_t _mxExample = 1;
		Deck();
		Deck(std::string fileName);

		bool FullOfCard(Card&);
		void Shuffle();
		Card GetFirstCard();
		void SaveDeckToJson(std::string name, float);
		void ChangeCard(std::string remove, Card add);

		std::string DeckList();
};

