#include "Player.h"
#include <stdexcept>

Player::Player(Deck* deck, std::string name)
{
	_deck = deck;
	_name = name;
}

bool Player::Draw()
{
	if (_deck->_cards.empty()) return false;
	_hand.push_back(_deck->GetFirstCard());
	return true;
}

void Player::PlayBestCard()
{
	if (_hand.size()<= 0)
		return;

	int index = -1;
	int compare = _currentMana;

	for(uint32_t i = 1; i < _hand.size(); i++)
	{
		int result = _currentMana - (int)_hand[i]._manaCost;
		if (result > compare || result < 0) continue;
		
		index = i;
		compare = result;

	}

	if (index < 0)return;
	PlayCard(index);
	if (_currentMana > 0)
		PlayBestCard();
}
void Player::PlayCard(uint32_t iHand)
{
	if (iHand < 0) return;

	Card card = _hand.at(iHand);
	if (card._manaCost > _currentMana)
		throw std::invalid_argument("Error with mana value");

	_hand.erase(_hand.begin() + iHand);
	_board.push_back(card);
	_currentMana -= card._manaCost;
}

void Player::AttackPlayer(Player* player)
{
	for(uint32_t i = 0; i < _board.size(); i++)
	{
		player->_pv -= _board[i]._atk;
	}
}