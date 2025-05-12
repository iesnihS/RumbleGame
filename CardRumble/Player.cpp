#include "Player.h"
#include <stdexcept>

Player::Player(Deck deck, std::string name) : _deck(deck), _name(name) {}

void Player::SetDeck(Deck deck) { _deck = deck; }

bool Player::Draw()
{
	if (_deck._cards.empty()) return false;
	_hand.push_back(_deck.GetFirstCard());
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

	if (index < 0) return;
	PlayCard(index);
	if (_currentMana > 0)
		PlayBestCard();
}
void Player::PlayCard(uint32_t iHand)
{
	Card card = _hand.at(iHand);
	if (card._manaCost > _currentMana)
		throw std::invalid_argument("Error with mana value");

	_hand.erase(_hand.begin() + iHand);
	_board.push_back(card);
	_currentMana -= card._manaCost;
}

void Player::AttackPlayer(Player* player)
{
	std::vector<Card*> tauntCards;
	for (Card c : player->_board) if (c.HasAbility(Taunt)) tauntCards.emplace_back(&c);

	for(uint32_t i = 0; i < _board.size(); i++)
	{
		Card currentCard = _board[i];
		// No Taunts ahead, every attack against enemy player.
		if (tauntCards.size() == 0)
		{
			player->_pv -= currentCard._atk;
			continue;
		}

		bool blocked = false;
		for (Card* c : tauntCards)
		{
			if (c->dead) continue;
			if (!currentCard.HasAbility(Flying) || 
				(currentCard.HasAbility(Flying) && c->HasAbility(Flying)))
			{
				player->_pv -= currentCard.Fight(c);
				blocked = true;
				break;
			}
		}
		if (!blocked) player->_pv -= currentCard._atk;
	}
	RemoveDeadCards();
	player->RemoveDeadCards();
}

void Player::PrintHand()
{
	std::cout << "Player " + _name + " hand :\n";
	for(uint32_t i = 0; i < _hand.size(); i ++)
	{
		_hand[i].PrintCard();
	}
}

void Player::Reset()
{
	_pv = 30;
	_currentMana = 1;
	_hand.clear();
	_board.clear();
}

void Player::RemoveDeadCards()
{
	std::vector<Card>::iterator boardIt = std::remove_if(_board.begin(), _board.end(),
		[](auto c) { return c.dead;});
	_board.erase(boardIt, _board.end());
}
