# include "stdafx.h"
# include "NodesLinker.h"
# include "..\PianoFingering\HorizontalCost.h"

using namespace std;
using namespace Visualizer;

enum NOTE_NAMES { C_, C1_, D_, D1_, E_, F_, F1_, G_, G1_, A_, A1_, B_ };

NodesLinker::NodesLinker() :
	newNodes_(),
	graph_(),
	minPaths_(),
//	notes_({ F_, F1_, B_, D_ + 12i16, A1_, C1_ + 12i16, B_, D_ + 12i16, F1_ + 12i16, B_ + 12i16 })	// Chopin's first Scherzo
//	notes_({ C_ + 12i16, G_, E_, C_ + 12i16, D_ + 12i16, C_ + 12i16, B_, G1_, E_ })					// All of Me
//	notes_({ D1_, F_, D1_, A1_, A1_, F_, G_, F_, C_ + 12i16, A1_, C_ + 12i16, A1_, D1_ + 12i16 })	// Ain't Misbehavin'
//	notes_({ C_, E_, G_, C_ + 12i16, A_, C_ + 12i16, A_, G_, F_, G_, E_, C_, D_, C_ })				// Alla faglar kommit ren

//	notes_({ A1_ + 12i16, G_ + 12i16, D1_ + 12i16, G1_ + 12i16, F_ + 12i16, C1_ + 12i16, G_ + 12i16,
//		G1_, C_ + 12i16, C1_ + 12i16, D1_ + 12i16, C1_ + 12i16, C_ + 12i16 })	// Interleaved Triad
//	notes_({ D_, D1_, E_, C_ + 12i16, E_, C_ + 12i16, E_,
//		C_ + 12i16, C_ + 12i16, D_ + 12i16, D1_ + 12i16, E_ + 12i16, C_ + 12i16,
//		D_ + 12i16, E_ + 12i16, B_, D_ + 12i16, C_ + 12i16
//		, D_, D1_, E_, C_ + 12i16, E_, C_ + 12i16, E_
//		, A_, G_, F1_, A_, C_ + 12i16, E_ + 12i16, D_ + 12i16, C_ + 12i16, A_, D_ + 12i16 })	// The Entertainer

//	notes_({ E_ + 12i16, D1_ + 12i16, E_ + 12i16, D1_ + 12i16, E_ + 12i16, B_, D_ + 12i16, C_ + 12i16, A_
//		, C_, E_, A_, B_, E_, G1_, B_, C_ + 12i16, E_
//		, E_ + 12i16, D1_ + 12i16, E_ + 12i16, D1_ + 12i16, E_ + 12i16, B_, D_ + 12i16, C_ + 12i16, A_
//		, C_, E_, A_, B_, E_, C_ + 12i16, B_, A_
//		, B_, C_ + 12i16, D_ + 12i16, E_ + 12i16, G_, F_ + 12i16, E_ + 12i16, D_ + 12i16
//		, F_, E_ + 12i16, D_ + 12i16, C_ + 12i16, E_, D_ + 12i16, C_ + 12i16, B_, E_, E_ + 12i16 })	// Fur Elise

//	notes_({ D_ + 12i16, G_, A_, B_, C_ + 12i16, D_ + 12i16, G_, G_, E_ + 12i16
//		, C_ + 12i16, D_ + 12i16, E_ + 12i16, F1_ + 12i16, G_ + 12i16, G_, G_
//		, C_ + 12i16, D_ + 12i16, C_ + 12i16, B_, A_, B_, C_ + 12i16, B_, A_, G_, F1_, G_, A_, B_, G_, B_, A_ }) // Bach Menuet 4

	notes_({ F_ + 12i16, A_, D_ + 12i16, A_ + 12i16, G_ + 12i16, F_ + 12i16, E_ + 12i16, B_, C1_ + 12i16
		, A_ + 12i16, C_ + 12i16, F_ + 12i16, C_ + 24i16, A1_ + 12i16, A_ + 12i16, G_ + 12i16, D_ + 12i16, E_ + 12i16
		, A_ + 12i16, A1_ + 12i16, D_ + 12i16, G_ + 12i16, D_ + 24i16, C_ + 24i16, A1_ + 12i16
		, A_ + 12i16, G_ + 12i16, F_ + 12i16, E_ + 12i16, D_ + 12i16, A_ + 12i16, D_ + 24i16, A_ + 12i16, G_ + 12i16
		, F_ + 24i16, E_ + 24i16, D_ + 24i16, C1_ + 24i16, E_ + 24i16, A_ + 12i16, C_ + 24i16, E_ + 12i16, G_ + 12i16 })	// Handel - Suite in D minor: Saraband
{
//	srand(static_cast<int>(time(NULL)));

//	FreeConsole();
//	AllocConsole();
//	FILE* stream(nullptr);
//	if (freopen_s(&stream, "CON", "w", stdout)) throw runtime_error("CANNOT OPEN CONSOLE WINDOW");
}


void NodesLinker::CreateNewNodes()
{
	newNodes_.clear();
	//	for (auto i(1); i < 16; ++i)
	//		newNodes_.emplace_back(make_pair(i, rand() % 10));
	for (char i('\1'); i <= '\5'; ++i)
		newNodes_.emplace_back(make_pair(i, 0.0f));
}

void NodesLinker::LinkNewNodes()
{
	list<List_> result;

	if (graph_.empty())	for (const auto& node : newNodes_)
	{
		result.emplace_back(List_({ node }));
		result.back().back().second = static_cast<float>(HorizontalCost::Calculate({
			make_pair(notes_.front(), node.first) }, {}, {}));
	}
	else				for (const auto& node : newNodes_)
	{
		const auto minVal(MinPathFinder(node));
		for (const auto& minPth : minPaths_)
		{
			result.push_back(*minPth);
			result.back().push_back(node);
			result.back().back().second += static_cast<float>(minVal);
		}
	}

	graph_.swap(result);
}

double NodesLinker::MinPathFinder(const pair<char, float> node)
{
	auto minVal(DBL_MAX);
	minPaths_ = { graph_.cbegin() };
	for (auto path(graph_.cbegin()); path != graph_.cend(); ++path)
	{
		auto newVal(0.0);
		if (path->size() >= 2)
		{
			auto pathPrev(path->crbegin());
			++pathPrev;
			newVal = path->back().second + HorizontalCost::Calculate
				({ make_pair(notes_.at(path->size() - 2), pathPrev->first) },
				{ make_pair(notes_.at(path->size() - 1), path->back().first) },
				{ make_pair(notes_.at(path->size()), node.first) });
		}
		else newVal = path->back().second + HorizontalCost::Calculate
			({ make_pair(notes_.front(), path->back().first) }, { make_pair(notes_.at(1), node.first) }, {});

		if (newVal < minVal)
		{
			minVal = newVal;
			minPaths_.clear();
			minPaths_.push_back(path);
		}
		else if (newVal == minVal)
			minPaths_.push_back(path);
	}

	return minVal;
}