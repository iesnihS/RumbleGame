#include "Visualiser.h"
#include <sstream>


Visualiser::Visualiser()
{

}

void Visualiser::GenPieChart(const std::vector<double>& x, int gameIdx)
{
	auto f = matplot::figure(true);
	auto ax = f->current_axes();
	auto p = ax->pie(x);
	matplot::save(GetFileName("Game", gameIdx));
}

void Visualiser::GenGraph(const std::vector<double>& x, int passIdx)
{
	//std::vector<int> y;
	//for (int i = 0; i < 1000; ++i) y.push_back(i);
	auto f = matplot::figure(true);
	auto ax = f->current_axes();
	auto p = ax->plot(x);
	p->color("red").line_width(2);
	matplot::save(GetFileName("WinRateGraph", passIdx));

}

std::string Visualiser::GetFileName(std::string name, int idx)
{
	std::ostringstream oss;
	oss << "Metrics/" << name << "_" << idx << ".jpg";
	return oss.str();
}
