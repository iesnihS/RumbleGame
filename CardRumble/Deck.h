#pragma once
#include <vector>
#include "Card.h"

class Deck
{
	public :
		std::vector<Card> _cards;
		Deck();
		void Shuffle();
		Card GetFirstCard();
};

