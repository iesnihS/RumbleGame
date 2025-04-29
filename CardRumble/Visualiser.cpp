#include "Visualiser.h"
#include <cmath>
#include <random>


Visualiser::Visualiser()
{

}

void Visualiser::GenPieChart(const std::vector<double>& winRates)
{
	matplot::pie(winRates);
	matplot::show();
}