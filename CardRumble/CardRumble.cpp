#include <iostream>
#include "Player.h"

Deck deckP1;
Deck deckReference;

bool PlayerTurn(Player*, Player*);

int main()
{
	
	srand(time(NULL));
	deckP1 = Deck();
	deckReference = Deck("reference_player.json");

	bool isFirst = rand() % 2;

	Player firstPlayer = Player(isFirst ? &deckP1 : &deckReference, "Samuel");
	Player secondPlayer = Player(!isFirst ? &deckP1 : &deckReference, "Arthur");

	uint32_t turn = 1;

	for(uint16_t i = 0; i < 5; i++)
	{
		firstPlayer.Draw();
		secondPlayer.Draw();
	}

	while(true)
	{
		if (PlayerTurn(&firstPlayer, &secondPlayer))
			break;
		if (PlayerTurn(&secondPlayer, &firstPlayer))
			break;
	}


}

bool PlayerTurn(Player* firstPlayer, Player* secondPlayer)
{
	firstPlayer->Draw();
	firstPlayer->PlayBestCard();
	firstPlayer->AttackPlayer(secondPlayer);
	if (secondPlayer->_pv <= 0)
	{
		std::cout << firstPlayer->_name + " Win !";
		return true;
	}
	return false;
}