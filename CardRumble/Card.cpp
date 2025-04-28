#include "Card.h"
#include "math.h"
#include <iostream>
#include <sstream>
#include <fstream>

uint32_t Card::_maxCost = 6;

void Card::InitAllPossibleCards()
{
	// Check if exists.
	std::ifstream check("assetList.json");
	if(check.good()) return;

	// If not : generate.
	std::ofstream tempFile{ "assetList.json" };
	json assetList;

	for (uint32_t atk = 0; atk < _maxCost * 2 - 1; atk++)
	{
		for(uint16_t def = 1; def < _maxCost * 2 - atk; def++)
		{
			std::ostringstream name;
			name << "Vanilla(" << atk << "," << def << ")";
			json card;
			card["name"] = name.str();
			card["attack"] = atk;
			card["defense"] = def;
			assetList.emplace_back(card);
		}
	}
	tempFile << assetList;
	tempFile.close();
}

Card::Card()
{
	_atk = rand() % (_maxCost + 1);
	_def = rand() % _maxCost + 1;
	std::ostringstream oss;
	oss << "Vanilla(" << _atk << "," << _def << ")";
	_name = oss.str();
	_manaCost = ceil((_atk + _def)/2);
}

Card::Card(json source)
{
	source["name"].get_to(_name);
	source["attack"].get_to(_atk);
	source["defense"].get_to(_def);

	_manaCost = ceil((_atk + _def) / 2);
}

void Card::PrintCard()
{
	std::ostringstream oss;
	oss << _name << " | " << _atk << " ATK | " << _def << " DEF";
	std::cout << oss.str() << std::endl;
}