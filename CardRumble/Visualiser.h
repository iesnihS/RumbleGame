#pragma once
#include <matplot/matplot.h>

class Visualiser
{
public:
	Visualiser();

	static void GenPieChart(const std::vector<double>& winRates);
};

