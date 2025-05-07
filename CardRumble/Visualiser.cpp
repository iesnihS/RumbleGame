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

static std::string GetNameFromCtx(int ctx)
{
	switch (ctx)
	{
	case 0: return "�volution du WinRate ";
	case 1: return "�volution de l'attaque moyenne ";
	case 2: return "�volution de la d�fense moyenne ";
	case 3: return "�volution du co�t moyen ";
	case 4: return "�volution de la dur�e des parties ";
	case 5: return "R�partition des comp�tences finales ";
	case 6: return "Distribution des co�ts finaux ";
	}

}
static std::string GetLabelFromCtx(int ctx, bool x)
{
	if (ctx < 5 && x) return "Passes d'optimisation";

	switch (ctx)
	{
	case 0: return "Winrate en %";
	case 1: return "Valeur d'attaque moyenne";
	case 2: return "Valeur de d�fense moyenne";
	case 3: return "Valeur du co�t moyenne";
	case 4: return "Dur�e des parties";

	case 5: return x ? "Comp�tences" : "Nombre de cartes";
	case 6: return x ? "Co�t" : "Nombre de cartes";
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

void Visualiser::GenGraph(const std::vector<double>& x, int ctx)
{
	std::fstream data("Data/data.json");
	if (!data.good())
	{
		std::cout << "Pas de data, pas de graph" << std::endl;
		return;
	}
	json j = json::parse(data);
	int idx = j["GenIdx"].template get<int>();

	// Quiet draw.
	auto f = matplot::figure(true);
	f->size(512, 512);
	auto ax = f->current_axes();
	ax->ylabel(GetLabelFromCtx(ctx, false));
	ax->xlabel(GetLabelFromCtx(ctx, true));

	std::string title = GetNameFromCtx(ctx);
	std::string color = GetColorFromCtx(ctx);
	// Histogram.
	if (ctx > 4)
	{
		auto h = ax->hist(x);
		h->display_name(title);
		h->face_color("r");
		h->edge_color(color);
	}
	else
	{
		auto p = ax->plot(x);
		p->display_name(title);
		p->color(color);
	}

	if(ctx == 0) matplot::yrange({ 0, 100 });
	matplot::save(GetFileName(title, ++idx));
	j["GenIdx"] = idx;
	data << j;
}

std::string Visualiser::GetFileName(std::string name, int idx)
{
	std::ostringstream oss;
	oss << "Metrics/" << name << "_" << idx << ".jpg";
	return oss.str();
}


