#include "Card.h"
#include "math.h"
#include <iostream>
#include <fstream>

uint32_t Card::_maxCost = 6;

void Card::InitAllPossibleCards()
{
	std::ofstream tempFile{"temp.txt"};
	
	for(uint32_t atk = 0; atk < _maxCost; atk++)
	{
		for(uint16_t def = 1; def < _maxCost; def++)
		{
			
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