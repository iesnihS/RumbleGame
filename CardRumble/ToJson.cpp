#include "./single_include/nlohmann/json.hpp"
#include "Card.h"

namespace ns {
	void to_json(json& j, const Card& c) {
		j = json{
			{"name", c._name},
			{"atk", c._atk},
			{"def", c._def} };
	}

	void from_json(const json& j, Card& c) {
		j.at("name").get_to(c._name);
		j.at("atk").get_to(c._atk);
		j.at("def").get_to(c._def);
	}
}