#pragma once
#include <matplot/matplot.h>
#include "./single_include/nlohmann/json.hpp"

class Visualiser
{
private:

public:
	Visualiser();

	static void GenPieChart(const std::vector<double>& winRates, int gameIdx);
	static void GenGraph(const std::vector<double>& winRates, int passIdx);
	static std::string GetFileName(std::string name, int idx);
};

