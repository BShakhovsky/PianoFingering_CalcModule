# include "stdafx.h"
# include "TrellisGraph_Facade.h"
# include "NodesLinker.h"

using namespace std;

struct TrellisGraph_pimpl : private boost::noncopyable
{
	bool leftHand, unused[3];	// three padding bytes
	size_t currStep;
	vector<vector<int16_t>> chords;
	vector<vector<string>> result;
	NodesLinker trellis;
};

TrellisGraph::TrellisGraph(const vector<set<int16_t>>& chords, const bool leftHand) :
	pimpl_(new TrellisGraph_pimpl)
{
	pimpl_->chords.reserve(chords.size());
	for (const auto& chord : chords)
		pimpl_->chords.emplace_back(vector<int16_t>(chord.cbegin(), chord.cend()));
	pimpl_->leftHand = leftHand;
	pimpl_->currStep = 0;
}

TrellisGraph::~TrellisGraph()
{
	delete pimpl_;
}

const vector<vector<string>>& TrellisGraph::GetResult() const
{
	return pimpl_->result;
}

size_t TrellisGraph::NextStep()
{
	if (pimpl_->currStep >= pimpl_->chords.size()) return 0;

	auto mirrowedChord(pimpl_->chords.at(pimpl_->currStep));
	if (mirrowedChord.size() > 5) mirrowedChord.erase(mirrowedChord.cbegin() + 1,
		mirrowedChord.cbegin() + static_cast<int>(mirrowedChord.size()) - 4);
	if (pimpl_->leftHand) transform(pimpl_->chords.at(pimpl_->currStep).crbegin(),
		pimpl_->chords.at(pimpl_->currStep).crend(), mirrowedChord.begin(),
		bind1st(minus<int16_t>(), NOTE_MI));
	pimpl_->trellis.LinkNewNodes(mirrowedChord);
	
	return ++pimpl_->currStep;
}

void TrellisGraph::Finish()
{
	pimpl_->trellis.RemoveExpensivePaths();

	pimpl_->result.reserve(pimpl_->chords.size());
	for (size_t i(0); i < pimpl_->trellis.GetResultedGraph().front().size(); ++i)
	{
		vector<string> resChord(pimpl_->trellis.GetResultedGraph().front().at(i)->first.size());
		for (const auto& path : pimpl_->trellis.GetResultedGraph())
			for (size_t j(0); j < path.at(i)->first.size(); ++j)
				if (find(resChord.at(j).cbegin(), resChord.at(j).cend(),
						path.at(i)->first.at(j).second + '0') == resChord.at(j).cend())
					resChord.at(j) += path.at(i)->first.at(j).second + '0';

		if (pimpl_->chords.at(i).size() > 5)
			resChord.insert(resChord.cbegin() + 1, string(pimpl_->chords.at(i).size() - 5, '?'));

		pimpl_->result.push_back(resChord);
	}
}