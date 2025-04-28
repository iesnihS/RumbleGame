#include <iostream>
#include <sstream>
#include "Player.h"
constexpr uint32_t NB_GAMES_PER_PASS = 500;

Deck deckP1;
Deck deckReference;

Player p1("Samuel");
Player p2("Arthur");

static bool PlayerTurn(Player* firstPlayer, Player* secondPlayer)
{
	if (!firstPlayer->Draw())
	{
		std::cout << firstPlayer->_name + " Win !";
		return true;
	}
	firstPlayer->PlayBestCard();
	firstPlayer->AttackPlayer(secondPlayer);
	if (secondPlayer->_pv <= 0)
	{
		std::cout << firstPlayer->_name + " Win !";
		return true;
	}
	return false;
}

static int Game()
{
	bool isFirst = rand() % 2;
	Player* firstPlayer = isFirst ? &p1 : &p2;
	Player* secondPlayer = !isFirst ? &p1 : &p2;

	uint32_t turn = 1;
	for (uint16_t i = 0; i < 5; i++)
	{
		p1.Draw();
		p2.Draw();
	}

	int winnerIdx = -1;
	while (true)
	{
		if (PlayerTurn(&p1, &p2))
		{
			winnerIdx = 1;
			break;
		}
		if (PlayerTurn(&p2, &p1))
		{
			winnerIdx = 2;
			break;
		}
	}
	return winnerIdx;
}

static void OptiPass()
{
	deckP1 = Deck();
	p1.SetDeck(&deckP1);
	
	int nbGames = 0;
	std::vector<int> winIndices;
	while (nbGames < NB_GAMES_PER_PASS)
	{
		winIndices.push_back(Game());
		++nbGames;
	}

	float p1Win, p2Win;
	p1Win = p2Win = 0;
	for(int winIdx : winIndices)
	{
		if (winIdx == 1) ++p1Win;
		else ++p2Win;
	}

	p1Win /= NB_GAMES_PER_PASS;
	p2Win /= NB_GAMES_PER_PASS;

	std::ostringstream oss;
	oss << "Winrate " << p1._name << " = " << p1Win * 100 << "% " << " | Winrate " 
		<< p2._name << " = " << p2Win * 100 << "% ";
	std::cout << oss.str() << std::endl;
}

static void DrawTrace()
{

}

int main()
{
	Card::InitAllPossibleCards();
	deckReference = Deck("reference_player.json");
	p2.SetDeck(&deckReference);
	srand(time(NULL));

	OptiPass();


}
