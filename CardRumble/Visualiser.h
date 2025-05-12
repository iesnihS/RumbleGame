#pragma once
#include <matplot/matplot.h>
#include "./single_include/nlohmann/json.hpp"
#include "Deck.h"

static class Visualiser
{
public:
	static void GenGraph(const std::vector<double>& winRates, int passIdx);
};

