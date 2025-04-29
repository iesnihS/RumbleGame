#include <iostream>
#include <sstream>
#include "Player.h"
constexpr uint32_t NB_GAMES_PER_PASS = 1000;
constexpr uint32_t NB_OPTI_PASS = 500;
constexpr bool DEBUG = false;

Deck deckP1;
Deck deckReference;

Player* p1;
Player* p2;

static bool PlayerTurn(Player* currentPlayer, Player* enemyPlayer)
{
	if (!currentPlayer->Draw())
	{
		if(DEBUG)
			std::cout << enemyPlayer->_name + " Win !";
		enemyPlayer->_nbOfGameWin++;
		return true;
	}
	currentPlayer->PlayBestCard();
	currentPlayer->AttackPlayer(enemyPlayer);
	if (enemyPlayer->_pv <= 0)
	{
		if (DEBUG)
			std::cout << currentPlayer->_name + " Win !";
		currentPlayer->_nbOfGameWin ++;
		return true;
	}
	return false;
}

void Game()
{
	bool isFirst = rand() % 2 == 0;
	

	Player* firstPlayer = isFirst ? p1 : p2;
	Player* secondPlayer = !isFirst ? p1 : p2;

	if (DEBUG)
	{
		std::cout << "FIRST PLAYER  " << firstPlayer->_name << std::endl;
		std::cout << "SECOND PLAYER  " << secondPlayer->_name << std::endl;
	}
	

	firstPlayer->_deck.Shuffle();
	secondPlayer->_deck.Shuffle();

	uint32_t turn = 1;
	for (uint16_t i = 0; i < 5; i++)
	{
		firstPlayer->Draw();
		secondPlayer->Draw();
	}

	firstPlayer->_currentMana = turn;
	secondPlayer->_currentMana = turn;
	
	if(DEBUG)
	{
		firstPlayer->PrintHand();
		secondPlayer->PrintHand();
	}
	

	while (true)
	{
		if (PlayerTurn(firstPlayer, secondPlayer))
			break;
		if (PlayerTurn(secondPlayer, firstPlayer))
			break;
		turn++;
		firstPlayer->_currentMana = turn;
		secondPlayer->_currentMana = turn;
	}
	if (DEBUG)
		std::cout << "P1 pv : " << firstPlayer->_pv << " P2 pv : " << secondPlayer->_pv << "\n" << std::endl;
	return;
}

void ResetGame()
{
	p1->Reset();
	p2->Reset();

	p1->SetDeck(deckP1);
	p2->SetDeck(deckReference);
}

void OptiPass()
{
	deckReference = Deck("reference_player.json");
	deckP1 = Deck();
	p1->SetDeck(deckP1);
	p2->SetDeck(deckReference);
	
	int nbGames = 0;
	while (nbGames < NB_GAMES_PER_PASS)
	{
		Game();
		ResetGame();
		++nbGames;
	}

	float res1 = (float) p1->_nbOfGameWin / NB_GAMES_PER_PASS;
	float res2 = (float) p2->_nbOfGameWin / NB_GAMES_PER_PASS;

	p1->_nbOfGameWin = 0;
	p2->_nbOfGameWin = 0;

	if (DEBUG)
	{
		std::ostringstream oss;
		oss << "Winrate " << p1->_name << " = " << res1 * 100 << "% " << " | Winrate "
			<< p2->_name << " = " << res2 * 100 << "% ";
		std::cout << oss.str() << std::endl;
	}
	


	std::ifstream f("Fromage.json");
	json data = json::parse(f);

	if (data["WinRate"] > res1)return;
	deckP1.SaveDeckToJson("Fromage", res1); 
}

static void DrawTrace()
{

}

int main()
{
	Card::InitAllPossibleCards();
	p1 = new Player(Deck(), "Samuel");
	p2 = new Player(Deck("reference_player.json"), "Arthur");
	srand(time(0));
	
	for(uint32_t i = 0; i < NB_OPTI_PASS; i++)
	{
		OptiPass();
		std::cout << "Process at " << ((float)i / NB_OPTI_PASS * 100) << "%\n";
	}
}
