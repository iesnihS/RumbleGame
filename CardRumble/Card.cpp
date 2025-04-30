#include "Card.h"
#include "math.h"
#include <iostream>
#include <sstream>
#include <fstream>


uint32_t Card::_maxCost = 6;

void Card::InitAllPossibleCards()
{
	// Check if exists.
	std::ifstream check("setList.json");
	if(check.good()) return;

	// If not : generate.
	std::ofstream tempFile{ "setList.json" };

	json assetList;

	for (uint32_t atk = 0; atk < _maxCost * 2 + 1; atk++)
	{
		for(uint16_t def = 1; def < _maxCost * 2 - atk +2; def++)
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
	json setList;
	std::ifstream check("setList.json");
	if (check.good())
		setList = json::parse(check);
	else return;

	json source = setList[rand() % setList.size()];
	from_json(source);
}
Card::Card(json source)
{
	from_json(source);
}

void Card::PrintCard() const
{
	std::ostringstream oss;
	oss << _name << " | " << _atk << " ATK | " << _def << " DEF";
	std::cout << oss.str() << std::endl;
}

void Card::to_json(json& j) {
	j = json{
		{"name", _name},
		{"attack", _atk},
		{"defense", _def} };
}

void Card::from_json(const json& j) {
	j["name"].get_to(_name);
	j["attack"].get_to(_atk);
	j["defense"].get_to(_def);
	_manaCost = ceil((_atk + _def) / 2);
}