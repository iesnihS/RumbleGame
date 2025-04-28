#pragma once
#include "Deck.h"
#include <vector>

class Player
{
public: 
	std::string _name;
	Deck _deck;

	int _pv = 30;
	std::vector<Card> _hand;
	uint32_t _currentMana = 0;
	std::vector<Card> _board;
	int _nbOfGameWin = 0;

	Player(Deck deck, std::string name);

	void SetDeck(Deck deck);

	bool Draw();
	void PlayBestCard();
	void PlayCard(uint32_t);
	void AttackPlayer(Player*);
	void Reset();

	void PrintHand();
};

