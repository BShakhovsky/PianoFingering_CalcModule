# include "stdafx.h"
# include "NodesLinker.h"
# include "ChordFingVariations.h"
# include "HorizontalCost.h"

using namespace std;
using namespace GraphStruct;

#pragma warning(push)
#pragma warning(disable:5045) // Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
void NodesLinker::LinkNewNodes(const vector<int16_t>& chord)
{
	if (graph_.empty())
		for (const auto& node : ChordFingVariations::CreateCombinations(chord))
		{
			graph_.emplace_back(NodeList_{ node });
			graph_.back().back()->second +=
				static_cast<float>(HorizontalCost::Calculate(graph_.back().back()->first, {}, {}));
		}
	else
	{
		Graph_ result;
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
		graph_ = result;

		if (graph_.front().size() >= 3) RemoveDuplicates();
	}
}
#pragma warning(pop)


double NodesLinker::MinPathFinder(const shared_ptr<Node_> node)
{
	auto minVal(DBL_MAX);

	minPaths_ = { graph_.cbegin() };
	for (auto path(graph_.cbegin()); path != graph_.cend(); ++path)
	{
		const auto newVal(static_cast<double>(path->back()->second) + node->second + (path->size() >= 2
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

#pragma warning(push)
#pragma warning(disable:5045) // Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
void NodesLinker::RemoveDuplicates()
{
	auto ind(graph_.front().size() - 2);
	for (; ind; --ind)
	{
		auto found(true);
		for (size_t i(1); i < graph_.size(); ++i)
			if (graph_.at(i).at(ind) != graph_.front().at(ind)) found = false;
		if (found) break;
	}
	if (ind) AppendResult(ind);
	assert("Wrong graph size" && graph_.size() >= 2);

	graph_.erase(unique(graph_.begin(), graph_.end(),
		[](const NodeList_& lhs, const NodeList_& rhs)
		{
			return equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
		}
	), graph_.cend());
}

void NodesLinker::AppendResult(const size_t sizeCount)
{
	for (size_t i(0); i < sizeCount; ++i)
	{
		result_.emplace_back(vector<string>(graph_.front().at(i)->first.size()));
		for (const auto& path : graph_)
			for (size_t j(0); j < path.at(i)->first.size(); ++j)
				if (find(result_.back().at(j).cbegin(), result_.back().at(j).cend(),
						path.at(i)->first.at(j).second + '0') == result_.back().at(j).cend())
					result_.back().at(j) += path.at(i)->first.at(j).second + '0';
	}
	for (auto& path : graph_)
	{
		path.erase(path.cbegin(), path.cbegin() + static_cast<int>(sizeCount));
		if (path.empty())
		{
			graph_.clear();
			break;
		}
	}
}
#pragma warning(pop)


void NodesLinker::RemoveExpensivePaths()
{
	assert("CHORD MAY HAVE AT LEAST FIVE FINGER COMBINATION" && graph_.size() >= 5);
	const auto PathCompare([](const NodeList_& lhs, const NodeList_& rhs)
	{
		return lhs.back()->second < rhs.back()->second;
	});
	for (auto i(2); graph_.cbegin() + (i - 1) != graph_.cend(); ++i)
	{
		partial_sort(graph_.begin(), graph_.begin() + i, graph_.end(), PathCompare);
		if (PathCompare(graph_.front(), graph_.at(static_cast<size_t>(i - 1))))
		{
			graph_.erase(graph_.cbegin() + i - 1, graph_.cend());
			break;
		}
	}
	AppendResult(graph_.front().size());
	assert("Wrong graph size" && !result_.empty() && graph_.empty());
}