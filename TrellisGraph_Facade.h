# pragma once
# pragma comment(lib, "PianoFingering.lib")

class TrellisGraph
{
	static constexpr auto NOTE_MI = 136i16;
					// note "mi" for left hand is mirrow-equivalent to note "do" for right hand
	TrellisGraph() = delete;
public:
	explicit TrellisGraph(const std::vector<std::vector<int16_t>>& chords, bool leftHand = false);
	~TrellisGraph();

	size_t NextStep();
	void Finish();

	const std::vector<std::vector<std::pair<int16_t, std::string>>>& GetResult() const;
private:
	struct TrellisGraph_pimpl* pimpl_;

	TrellisGraph(const TrellisGraph&) = delete;
	TrellisGraph(const TrellisGraph&&) = delete;
	TrellisGraph& operator=(const TrellisGraph&) = delete;
	TrellisGraph&& operator=(const TrellisGraph&&) = delete;
};