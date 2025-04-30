#include "Visualiser.h"
#include <sstream>
using json = nlohmann::json;

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
	std::fstream data("Data/data.json");
	if (!data.good())
	{
		std::cout << "Pas de data, pas de graph" << std::endl;
		return;
	}

	json j = json::parse(data);
	int idx = j["GenIdx"].template get<int>();
	auto f = matplot::figure(true);
	f->size(512, 512);
	auto ax = f->current_axes();
	ax->ylabel("Winrate en %");
	ax->xlabel("Numéro de passe d'optimisation");
	auto p = ax->plot(x);
	std::ostringstream graphName;
	graphName << "Évolution du WinRate _ " << ++idx;
	p->display_name(graphName.str());
	p->color("red");
	matplot::yrange({ 0, 100 });
	matplot::save(GetFileName("WinRateGraph", idx));
	j["GenIdx"] = idx;
	data << j;
}

std::string Visualiser::GetFileName(std::string name, int idx)
{
	std::ostringstream oss;
	oss << "Metrics/" << name << "_" << idx << ".jpg";
	return oss.str();
}
