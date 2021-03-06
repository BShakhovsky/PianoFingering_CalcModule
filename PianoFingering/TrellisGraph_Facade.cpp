# include "stdafx.h"
# include "TrellisGraph_Facade.h"
# include "NodesLinker.h"

using namespace std;

#pragma warning(push)
#pragma warning(disable:26495) // leftHand uninitialized
struct TrellisGraph_pimpl : private boost::noncopyable
{
	bool leftHand, unused[3];	// three padding bytes
	size_t currStep;
	vector<vector<int16_t>> chords;
	vector<vector<string>> result;
	NodesLinker trellis;
};
#pragma warning(pop)

TrellisGraph::TrellisGraph(const vector<set<int16_t>>& chords, const bool leftHand) :
	pimpl_(new TrellisGraph_pimpl)
{
	pimpl_->chords.reserve(chords.size());
	for (const auto& chord : chords)
		pimpl_->chords.emplace_back(vector<int16_t>(chord.cbegin(), chord.cend()));
	pimpl_->trellis.ReserveResultSize(pimpl_->chords.size());
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
	if (pimpl_->leftHand) transform(pimpl_->chords.at(pimpl_->currStep).crbegin(),
		pimpl_->chords.at(pimpl_->currStep).crend(), mirrowedChord.begin(),
		bind(minus<int16_t>(), NOTE_MI, placeholders::_1));
	if (mirrowedChord.size() > 5) mirrowedChord.erase(mirrowedChord.cbegin() + 1,
		mirrowedChord.cbegin() + static_cast<int>(mirrowedChord.size()) - 4);
	pimpl_->trellis.LinkNewNodes(mirrowedChord);
	
	return ++pimpl_->currStep;
}

#pragma warning(push)
#pragma warning(disable:5045) // Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
void TrellisGraph::Finish()
{
	pimpl_->trellis.RemoveExpensivePaths();
	pimpl_->result = pimpl_->trellis.GetResultedGraph();
	for (size_t i(0); i < pimpl_->result.size(); ++i)
	{
		if (pimpl_->chords.at(i).size() > 5)
		{
			const vector<string> leftOutNotes(pimpl_->chords.at(i).size() - 5, "?");
			pimpl_->result.at(i).insert(pimpl_->result.at(i).cbegin() + 1,
				leftOutNotes.cbegin(), leftOutNotes.cend());
		}
		if (pimpl_->leftHand) reverse(pimpl_->result.at(i).begin(), pimpl_->result.at(i).end());
	}
}
#pragma warning(pop)