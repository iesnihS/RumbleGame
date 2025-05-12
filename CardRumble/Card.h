#pragma once
#include <stdint.h>
#include <string>
#include "./single_include/nlohmann/json.hpp"
using json = nlohmann::json;

enum Ability : int
{
	None = 0,
	Taunt = 1,
	Trample = 2,
	Flying = 4
};

class Card
{
public:
	static uint32_t _maxCost;
	uint32_t _manaCost = 0;
	uint32_t _atk = 0;
	uint32_t _def = 1;
	uint32_t currentDef = 1;
	std::string _name;
	int _ability = 0;
	bool dead = false;

	Card(json source);
	Card();

	void Randomize();
	static void InitAllPossibleCards();

	void PrintCard() const;

	void to_json(json& j);

	void from_json(const json& j);

	bool HasAbility(Ability a) const;

	int Fight(Card* otherCard);

	void RegainLife();
};
