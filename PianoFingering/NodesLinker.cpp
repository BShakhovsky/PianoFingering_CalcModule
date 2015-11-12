# include "stdafx.h"
# include "NodesLinker.h"
# include "ChordFingVariations.h"
# include "HorizontalCost.h"

using namespace std;
using namespace GraphStruct;

void NodesLinker::LinkNewNodes(const vector<int16_t> chord)
{
	if (graph_.empty())
		for (const auto& node : ChordFingVariations::CreateCombinations(chord))
		{
			graph_.emplace_back(NodeList_({ node }));
			graph_.back().back()->second +=
				static_cast<float>(HorizontalCost::Calculate(graph_.back().back()->first, {}, {}));
		}
	else
	{
		vector<NodeList_> result;
		for (const auto& node : ChordFingVariations::CreateCombinations(chord))
		{
			const auto minVal(MinPathFinder(node));
			for (const auto& minPth : minPaths_)
			{
				result.push_back(*minPth);
				result.back().push_back(node);
			}
			node->second = static_cast<float>(minVal);
		}
		graph_.swap(result);
	}
}

double NodesLinker::MinPathFinder(const shared_ptr<Node_> node)
{
	auto minVal(DBL_MAX);

	minPaths_ = { graph_.cbegin() };
	for (auto path(graph_.cbegin()); path != graph_.cend(); ++path)
	{
		const auto newVal(path->back()->second + node->second + (path->size() >= 2
			? HorizontalCost::Calculate(path->at(path->size() - 2)->first,	path->back()->first, node->first)
			: HorizontalCost::Calculate(									path->back()->first, node->first, {})));

		if (newVal < minVal)
		{
			minVal = newVal;
			minPaths_ = { path };
		}
		else if (newVal == minVal)
			minPaths_.push_back(path);
	}

	return minVal;
}

class PathCompare
{
public:
	PathCompare() = default;
	PathCompare(const PathCompare&) = default;
	PathCompare& operator = (const PathCompare&) = default;
	~PathCompare() = default;

	bool operator () (const NodeList_& lhs, const NodeList_& rhs) const
	{
		return lhs.back()->second < rhs.back()->second;
	}
};

void NodesLinker::RemoveExpensivePaths()
{
	assert("CHORD MAY HAVE AT LEAST FIVE FINGER COMBINATION" && graph_.size() >= 5);
	for (auto i(2); graph_.cbegin() + (i - 1) != graph_.cend(); ++i)
	{
		partial_sort(graph_.begin(), graph_.begin() + i, graph_.end(), PathCompare());
		if (PathCompare()(graph_.front(), graph_.at(static_cast<size_t>(i - 1))))
		{
			graph_.erase(graph_.cbegin() + i - 1, graph_.cend());
			break;
		}
	}
}