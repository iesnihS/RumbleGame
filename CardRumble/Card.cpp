#include "Card.h"
#include "math.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>

std::vector<int> possibleAbilities;
static bool ABILITIES_ON = true;

uint32_t Card::_maxCost = 6;
static json GenCard(std::string alias, uint32_t atk, uint32_t def, int ability)
{
	std::ostringstream name;
	name << alias << "(" << atk << "," << def << ")";
	json card;
	card["name"] = name.str();
	card["attack"] = atk;
	card["defense"] = def;
	card["skills"] = ability;
	return card;
}

static std::string GetCardAlias(int ability)
{
	std::ostringstream alias;
	if (ability & Taunt) alias << "Taunt";
	if (ability & Trample) alias << "Trample";
	if (ability & Flying) alias << "Flying";
	return alias.str();
}

void Card::InitAllPossibleCards()
{
	// Check if exists.
	std::ifstream check("Data/setList.json");
	if(check.good()) return;

	possibleAbilities.push_back(Taunt);
	possibleAbilities.push_back(Trample);
	possibleAbilities.push_back(Flying);

	json setList;
	for (uint32_t atk = 0; atk < _maxCost * 2 + 1; atk++)
	{
		for(uint16_t def = 1; def < _maxCost * 2 - atk +2; def++)
		{
			setList.emplace_back(GenCard("Vanilla", atk, def, 0));

			int cost = floor((atk + def) / 2.0f);
			int currentAbility = 0;
			std::ostringstream alias;
			if (!ABILITIES_ON) continue;
			if (cost+1 <= _maxCost)
			{
				for (int ab : possibleAbilities)
					setList.emplace_back(GenCard(GetCardAlias(ab), atk, def, ab));

				if (cost+2 <= _maxCost)
				{
					for (int i = 0; i < possibleAbilities.size(); ++i)
					{
						int ab;
						if (i == possibleAbilities.size() - 1)
							ab = possibleAbilities[0] | possibleAbilities[i];
						else ab = possibleAbilities[i] | possibleAbilities[i + 1];
						setList.emplace_back(GenCard(GetCardAlias(ab), atk, def, ab));
					}
					if (cost+3 <= _maxCost)
					{
						int ab = Taunt | Trample | Flying;
						setList.emplace_back(GenCard(GetCardAlias(ab), atk, def, ab));
					}
				}
			}
		}
	}

	std::ofstream tempFile{ "Data/setList.json" };
	tempFile << setList;
	tempFile.close();
}

Card::Card(){}

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

void Card::to_json(json& j)
{
	j = json
	{
		{"name", _name},
		{"attack", _atk},
		{"defense", _def},
		{"skills", _ability}
	};
}

void Card::from_json(const json& j)
{
	j["name"].get_to(_name);
	j["attack"].get_to(_atk);
	j["defense"].get_to(_def);
	currentDef = _def;
	if (ABILITIES_ON)
	{
		j["skills"].get_to(_ability);
		int abCost = (_ability & Taunt ? 1 : 0) +
			(_ability & Trample ? 1 : 0) +
			(_ability & Flying ? 1 : 0);
		_manaCost = floor((_atk + _def) / 2) + abCost;
	}
	else _manaCost = floor((_atk + _def) / 2);
}

bool Card::HasAbility(Ability a) const { return _ability & a; }

int Card::Fight(Card* otherCard)
{
	int trampleDmg = 0;
	if (HasAbility(Trample) && _atk > otherCard->currentDef) trampleDmg =  _atk - otherCard->currentDef;
	currentDef -= otherCard->_atk;
	otherCard->currentDef -= _atk;
	if (currentDef <= 0) dead = true;
	if (otherCard->currentDef <= 0) otherCard->dead = true;
	return trampleDmg;
}

void Card::RegainLife() { currentDef = _def; }

void Card::Randomize()
{
	json setList;
	std::ifstream check("Data/setList.json");
	if (check.good())
		setList = json::parse(check);
	else return;

	json source = setList[rand() % setList.size()];
	from_json(source);
}
