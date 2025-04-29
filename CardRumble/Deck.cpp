#include "Deck.h"
#include <algorithm>
#include <random>
#include "./single_include/nlohmann/json.hpp"
#include <sstream>
using json = nlohmann::json;

Deck::Deck()
{
	json setList;
	std::ifstream check("setList.json");
	if (check.good())
		setList = json::parse(check);
	else return;

	 

	for(uint32_t i = 0; i < 30; i ++)
	{
		Card currentLastCard = Card(setList[rand() % setList.size()]);
		while(true)
		{
			if (FullOfCard(currentLastCard))
			{
				currentLastCard = Card(setList[rand() % setList.size()]);
				continue;
			}
			break;
		}
		_cards.push_back(currentLastCard);
	}
}
bool Deck::FullOfCard(Card& card)
{
	uint32_t indexNb = 0;
	for (uint32_t i = 0; i < _cards.size(); i++)
	{
		if (_cards[i]._name == card._name)
		{
			indexNb++;
			if (indexNb == _mxExample)
				return true;
		}
	}
	return false;
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
	for(uint32_t i = 0; i < _cards.size(); i++)
	{
		json jCard;
		_cards[i].to_json(jCard);
		deck.emplace_back(jCard);
	}
	json dataDeck;
	dataDeck["deck"] = deck;
	dataDeck["WinRate"] = winRate;
	tempFile << dataDeck;
}

void Deck::ChangeCard(std::string remove, Card add)
{
	for(uint32_t i = 0; i < _cards.size(); i++)
	{
		if (_cards[i]._name != remove) continue;

		_cards[i] = add;
	}
}

