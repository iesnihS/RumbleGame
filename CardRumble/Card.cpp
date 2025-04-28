#include "Card.h"
#include "math.h"
#include <iostream>
#include <sstream>
#include <fstream>


uint32_t Card::_maxCost = 6;

void Card::InitAllPossibleCards()
{
	std::ofstream tempFile{ "temp.txt" };
	json assetList, card;

	for(uint32_t atk = 0; atk < _maxCost; atk++)
	{
		for(uint16_t def = 1; def < _maxCost; def++)
		{
			std::ostringstream name;
			name << "Vanilla(atk=" << atk << ",def=" << def << ")";
			card["name"] = name.str();
			card["attack"] = atk;
			card["defense"] = def;

			//tempFile << "atk"  + atk + " def" + def;
		}
	}
	tempFile.close();
}

Card::Card()
{
	_atk = rand() % (_maxCost + 1);
	_def = rand() % _maxCost + 1;

	_manaCost = ceil((_atk + _def)/2);
}

Card::Card(json source)
{
	source["name"].get_to(_name);
	source["attack"].get_to(_atk);
	source["defense"].get_to(_def);

	_manaCost = ceil((_atk + _def) / 2);

	std::cout << _name;
	std::cout << _atk;
	std::cout << _def;
	std::cout << _manaCost << std::endl;
}

void Card::PrintCard()
{
	std::ostringstream oss;
	oss << _name << " | " << _atk << " ATK | " << _def << " DEF";
	std::cout << oss.str() << std::endl;
}