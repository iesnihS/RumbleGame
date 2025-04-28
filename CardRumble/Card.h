#pragma once
#include <stdint.h>
#include <string>
class Card
{
	public:
		static uint32_t _maxCost;
		uint32_t _manaCost = 0;
		uint32_t _atk = 0;
		uint32_t _def = 1;
		std::string _name;

		Card();
		static void InitAllPossibleCards();
};

