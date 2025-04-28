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

		Deck();
		Deck(std::string fileName);

		void Shuffle();
};

