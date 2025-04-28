#include <iostream>
#include "Player.h"

Deck deckP1;
Deck deckReference;

int main()
{
	srand(time(NULL));
	deckP1 = Deck();
	deckReference = Deck("reference_player.json");

	Player firstPlayer;
	Player secondPlayer;

	if(rand() % 2 == 0)
	{
		
		//firstPlayer = pla;
		
		//secondPlayer
	}

	uint32_t turn = 1;
}