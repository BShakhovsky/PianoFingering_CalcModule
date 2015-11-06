# pragma once
# include "GraphStruct.h"

class TrellisGraph
{
	TrellisGraph() = delete;
public:
	explicit TrellisGraph(std::vector<std::vector<int16_t>> chords, bool leftHand = false);
	~TrellisGraph() = default;

	const std::vector<std::vector<GraphStruct::Chord_>>& GetResult() const
	{
		return result_;
	}
private:
	std::vector<std::vector<GraphStruct::Chord_>> result_;

	TrellisGraph(const TrellisGraph&) = delete;
	TrellisGraph(const TrellisGraph&&) = delete;
	TrellisGraph& operator=(const TrellisGraph&) = delete;
	TrellisGraph&& operator=(const TrellisGraph&&) = delete;
};