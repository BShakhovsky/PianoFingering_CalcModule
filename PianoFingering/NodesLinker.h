# pragma once
# include "GraphStruct.h"

class NodesLinker : private boost::noncopyable
{
	GraphStruct::Graph_ graph_;
	std::vector<GraphStruct::Graph_::const_iterator> minPaths_;
	std::vector<std::vector<std::string>> result_;
public:
	NodesLinker() : noncopyable(),
		graph_(),
		minPaths_(),
		result_()
	{}
	~NodesLinker() = default;

	void ReserveResultSize(size_t sizeCount)
	{
		result_.reserve(sizeCount);
	}
	const std::vector<std::vector<std::string>>& GetResultedGraph() const
	{
		return result_;
	}
	void RemoveExpensivePaths();

	void LinkNewNodes(const std::vector<int16_t>& chord);
private:
	double MinPathFinder(std::shared_ptr<GraphStruct::Node_>);
	void RemoveDuplicates();
	void AppendResult(size_t howMany);
};