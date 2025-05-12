#include <iostream>
#include <sstream>
#include "Player.h"
#include "Visualiser.h"

constexpr uint32_t NB_GAMES_PER_PASS = 1000;
constexpr uint32_t NB_OPTI_PASS = 2500;

constexpr bool DEBUG_PASS = false;
constexpr bool DEBUG_GAME = false;

Deck deckP1;
Deck deckReference;

std::vector<double> winRates;
std::vector<double> costAvgs;
std::vector<double> atkAvgs;
std::vector<double> defAvgs;
std::vector<double> durationAvgs;

std::vector<double> skillRep;
std::vector<double> costDst;
float durAvg = 0;

Player* p1;
Player* p2;

json data;

void AddCarteToData(std::string, Card&);

static bool PlayerTurn(Player* currentPlayer, Player* enemyPlayer)
{
	if (!currentPlayer->Draw())
	{
		if (DEBUG_GAME)
			std::cout << enemyPlayer->_name + " Win !";
		enemyPlayer->_nbOfGameWin++;
		return true;
	}

	currentPlayer->PlayBestCard();
	currentPlayer->AttackPlayer(enemyPlayer);
	if (enemyPlayer->_pv <= 0)
	{
		if (DEBUG_GAME)
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

	if (DEBUG_GAME)
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
	
	if (DEBUG_GAME)
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
	if (DEBUG_GAME)
		std::cout << "P1 pv : " << firstPlayer->_pv << " P2 pv : " << secondPlayer->_pv << "\n" << std::endl;
	durAvg += turn;
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
	p1->SetDeck(deckP1);
	p2->SetDeck(deckReference);
	
	int nbGames = 0;
	while (nbGames < NB_GAMES_PER_PASS)
	{
		Game();
		ResetGame();
		++nbGames;
	}

	float res1 = (float)p1->_nbOfGameWin / NB_GAMES_PER_PASS;
	float res2 = (float)p2->_nbOfGameWin / NB_GAMES_PER_PASS;
	p1->_nbOfGameWin = 0;
	p2->_nbOfGameWin = 0;


	float atkAvg = 0;
	float defAvg = 0;
	float costAvg = 0;
	float durationAvg = 0;
	for (Card c : deckP1._cards)
	{
		atkAvg += c._atk;
		defAvg += c._def;
		costAvg += c._manaCost;
	}
	int size = deckP1._cards.size();

	for (Card c : deckP1._cards) c._manaCost;
	
	winRates.push_back((double)res1 * 100);
	atkAvgs.push_back(atkAvg / size);
	defAvgs.push_back(defAvg / size);
	costAvgs.push_back(costAvg / size);
	durationAvgs.push_back(durAvg / NB_GAMES_PER_PASS);
	durAvg = 0;

	if (DEBUG_PASS)
	{
		std::ostringstream oss;
		oss << "Winrate " << p1->_name << " = " << res1 * 100 << "% " << " | Winrate "
			<< p2->_name << " = " << res2 * 100 << "% ";
		std::cout << oss.str() << std::endl;
	}
	
	std::ifstream f("Data/BestDeck.json");
	if (f.good())
	{
		json deckJ = json::parse(f);
		json setList;
		std::ifstream iset("Data/setList.json");
		setList = json::parse(iset);

		if (deckJ["WinRate"] > res1)
		{
			Card removedCard =Card(data["LastRemovedCard"]);
			Card addedCard = Card(data["LastAddedCard"]);
			deckP1.ChangeCard(addedCard._name, removedCard);
		}
		else
			deckP1.SaveDeckToJson("BestDeck", res1);

		Card removedCard = deckP1._cards[rand() % deckP1._cards.size()];
		Card addedCard = Card(setList[rand() % setList.size()]);
		while (true)
		{
			if(deckP1.FullOfCard(addedCard))
			{
				addedCard = Card(setList[rand() % setList.size()]);
				continue;
			}
			break;
		}
		AddCarteToData("LastRemovedCard",removedCard);
		AddCarteToData("LastAddedCard", addedCard);
		deckP1.ChangeCard(removedCard._name, addedCard);
	}
	else
		deckP1.SaveDeckToJson("BestDeck", res1);
}

void AddCarteToData(std::string dataName, Card& card)
{
	json lastCard;
	card.to_json(lastCard);
	data[dataName] = lastCard;
}

int main()
{
	std::ifstream i("Data/data.json");

	if (i.good())
		data = json::parse(i);
	else
	{
		std::ofstream o{ "Data/data.json" };
		Card temp1 = Card();
		temp1.Randomize();
		AddCarteToData("LastRemovedCard", temp1);
		Card temp2 = Card();
		temp2.Randomize();
		AddCarteToData("LastAddedCard", temp2);
		o << data;
	}
	
	Card::InitAllPossibleCards();

	deckReference = Deck("Data/reference_player2.json");
	deckP1.Randomize();// = Deck("Data/BestDeck.json");

	p1 = new Player(deckP1, "Samuel");
	p2 = new Player(deckReference, "Arthur");
	srand(time(0));

	for(uint32_t i = 0; i < NB_OPTI_PASS; i++)
	{
		OptiPass();
		std::cout << "Process at " << ((float)i / NB_OPTI_PASS * 100) << "%\n";
	}

	Visualiser::GenGraph(winRates, 0);
	Visualiser::GenGraph(atkAvgs, 1);
	Visualiser::GenGraph(defAvgs, 2);
	Visualiser::GenGraph(costAvgs, 3);
	Visualiser::GenGraph(durationAvgs, 4);

	costDst.assign(Card::_maxCost, 0);
	skillRep.assign(4, 0);

	Deck bestDeck = Deck("Data/BestDeck.json");
	for (Card c : bestDeck._cards)
	{
		++costDst[c._manaCost == 0 ? 1 : c._manaCost-1];
		if (c._ability == 0)
		{
			++skillRep[0];
			continue;
		}
		if ((c._ability & Taunt) != 0) ++skillRep[1];
		if ((c._ability & Trample) != 0) ++skillRep[2];
		if ((c._ability & Flying) != 0) ++skillRep[3];
	}
	for (int i = 0; i < costDst.size(); ++i)
		std::cout <<"Cost->"<< i << " = " << costDst[i] << std::endl;

	Visualiser::GenGraph(skillRep, 5);
	Visualiser::GenGraph(costDst, 6);
	std::ofstream o{ "Data/data.json" };
	data["GenIdx"] = data["GenIdx"].template get<int>()+1;
	o << data;
	std::cout << deckP1.DeckList() << std::endl;
}
