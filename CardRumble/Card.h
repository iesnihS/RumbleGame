#pragma once
#include <stdint.h>
#include <string>
#include "./single_include/nlohmann/json.hpp"
using json = nlohmann::json;

class Card
{
	public:
		static uint32_t _maxCost;
		uint32_t _manaCost = 0;
		uint32_t _atk = 0;
		uint32_t _def = 1;
		std::string _name;
		int _ability = 0;

		Card(json source);
		Card();

		static void InitAllPossibleCards();

		void PrintCard() const;

		void to_json(json& j);

		void from_json(const json& j);
};
