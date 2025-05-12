#include "Visualiser.h"
#include <sstream>
using json = nlohmann::json;

static std::string GetNameFromCtx(int ctx)
{
	switch (ctx)
	{
	case 0: return "Évolution du WinRate ";
	case 1: return "Évolution de l'attaque moyenne ";
	case 2: return "Évolution de la défense moyenne ";
	case 3: return "Évolution du coût moyen ";
	case 4: return "Évolution de la durée des parties ";
	case 5: return "Répartition des compétences finales ";
	case 6: return "Distribution des coûts finaux ";
	}

}
static std::string GetLabelFromCtx(int ctx, bool x)
{
	if (ctx < 5 && x) return "Passes d'optimisation";

	switch (ctx)
	{
	case 0: return "Winrate en %";
	case 1: return "Valeur d'attaque moyenne";
	case 2: return "Valeur de défense moyenne";
	case 3: return "Valeur du coût moyenne";
	case 4: return "Durée des parties";

	case 5: return x ? "Compétences" : "Nombre de cartes";
	case 6: return x ? "Coût" : "Nombre de cartes";
	}
}
static std::string GetColorFromCtx(int ctx)
{
	switch (ctx)
	{
	case 0: return "yellow";
	case 1: return "red";
	case 2: return "blue";
	case 3: return "cyan";
	case 4: return "green";
	case 5: return "magenta";
	case 6: return "blue";
	}
}
static std::vector < std::string> GetLabelsWithValues(const std::vector<double>& data)
{
	const std::vector<std::string> labels = { "Vanilla", "Taunt", "Trample", "Flying" };
	std::vector<std::string> res;
	for (int i = 0; i < data.size(); ++i)
	{
		std::ostringstream lss;
		lss << labels[i] << " (" << (int)((data[i]/Deck::NB_CARDS)*100) << "%)";
		res.push_back(lss.str());
	}
	return res;
}
static std::string GetFileName(std::string name, int idx)
{
	std::ostringstream oss;
	oss << "Metrics/" << name << "_" << idx << ".jpg";
	return oss.str();
}

void Visualiser::GenGraph(const std::vector<double>& data, int ctx)
{
	std::fstream dataFile("Data/data.json");
	if (!dataFile.good())
	{
		std::cout << "Pas de data, pas de graph" << std::endl;
		return;
	}
	json j = json::parse(dataFile);

	int idx = j["GenIdx"].template get<int>();
	std::string title = GetNameFromCtx(ctx);
	std::string color = GetColorFromCtx(ctx);

	// Quiet draw.
	auto f = matplot::figure(true);
	f->size(512, 512);
	auto ax = f->current_axes();
	if (ctx != 5)
	{
		ax->ylabel(GetLabelFromCtx(ctx, false));
		ax->xlabel(GetLabelFromCtx(ctx, true));
	}

	// Line plot.
	if (ctx < 5)
	{
		auto l = ax->plot(data);
		l->display_name(title);
		l->color(color);
	}
	else
	{
		// Histogram.
		if (ctx == 6)
		{
			auto b = ax->bar(data);
			b->display_name(title);
		}
		// Pie chart.
		else
		{
			auto p = ax->pie(data, GetLabelsWithValues(data));
			p->display_name(title);
		}
	}

	if(ctx == 0) matplot::yrange({ 0, 100 });
	matplot::save(GetFileName(title, ++idx));
	if (ctx == 5) matplot::show();
}




