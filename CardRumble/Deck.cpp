#include "Deck.h"
#include <algorithm>
#include <random>

Deck::Deck()
{
	for(uint32_t i = 0; i < 30; i ++)
	{
		_cards.push_back(Card());
	}
}

void Deck::Shuffle()
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(_cards.begin(), _cards.end(), g);
}