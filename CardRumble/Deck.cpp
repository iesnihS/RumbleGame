#include "Deck.h"
#include <algorithm>
#include <random>
#include "./single_include/nlohmann/json.hpp"
#include <sstream>
using json = nlohmann::json;

Deck::Deck()
{
	for(uint32_t i = 0; i < 30; i ++)
	{
		_cards.push_back(Card());
	}
}

Deck::Deck(std::string fileName)
{
	std::ifstream file;
	file.open(fileName);
	json in = json::parse(file);

	for (auto& el : in["deck"].items()) _cards.push_back(Card(el.value()));
}

void Deck::Shuffle()
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(_cards.begin(), _cards.end(), g);
}

Card Deck::GetFirstCard()
{
	Card card = _cards[_cards.size() - 1];
	_cards.pop_back();
	return card;
}

void Deck::SaveDeckToJson(std::string name, float winRate)
{
	std::ostringstream jsonName;
	jsonName << name << ".json";
	std::ofstream tempFile{ jsonName.str() };
	json deck;
	json cards;
	for(uint32_t i = 0; i < _cards.size(); i++)
	{
		json jCard;
		Card& card = _cards[i];
		jCard["name"] = card._name;
		jCard["atk"] = card._atk;
		jCard["def"] = card._def;
		cards.emplace_back(jCard);
	}
	json winJ;
	winJ["WinRate"] = winRate;
	deck.push_back(winJ);
	deck.emplace_back(cards);
	tempFile << deck;
}
