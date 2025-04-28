#pragma once
#include "Deck.h"
#include <vector>
class Player
{
public: 
	std::string _name;
	Deck* _deck;
	int _pv = 30;
	std::vector<Card> _hand;
	uint32_t _currentMana = 0;
	std::vector<Card> _board;
	Player(Deck* deck, std::string name);
	Player();
	void Draw();
	void PlayBestCard();
	void PlayCard(uint32_t);
	void AttackPlayer(Player*);
};

