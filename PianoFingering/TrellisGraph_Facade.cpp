# include "stdafx.h"
# include "TrellisGraph_Facade.h"
# include "NodesLinker.h"

using namespace std;
using GraphStruct::Chord_;

struct TrellisGraph_pimpl : private boost::noncopyable
{
	bool leftHand, unused[3];	// three padding bytes
	size_t currStep;
	vector<vector<int16_t>> chords;
	vector<vector<Chord_>> result;
	NodesLinker trellis;
};

TrellisGraph::TrellisGraph(vector<vector<int16_t>> chords, const bool leftHand) :
	pimpl_(new TrellisGraph_pimpl)
{
	pimpl_->chords = chords;
	pimpl_->leftHand = leftHand;
	pimpl_->currStep = 0;
}

TrellisGraph::~TrellisGraph()
{
	delete pimpl_;
}

const vector<vector<Chord_>>& TrellisGraph::GetResult() const
{
	return pimpl_->result;
}

size_t TrellisGraph::NextStep()
{
	if (pimpl_->currStep >= pimpl_->chords.size()) return 0;

	const set<int16_t> sortedChord(pimpl_->chords.at(pimpl_->currStep).cbegin(),
		pimpl_->chords.at(pimpl_->currStep).cend());
	pimpl_->chords.at(pimpl_->currStep).assign(sortedChord.cbegin(), sortedChord.cend());

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

	pimpl_->result.reserve(pimpl_->trellis.GetResultedGraph().size());
	for (const auto& path : pimpl_->trellis.GetResultedGraph())
	{
		pimpl_->result.emplace_back(vector<Chord_>());
		pimpl_->result.back().reserve(path.size());
		for (size_t i(0); i < path.size(); ++i)
		{
			pimpl_->result.back().push_back(path.at(i)->first);
			if (pimpl_->leftHand) for (auto& note : pimpl_->result.back().back())
				note.first = NOTE_MI - note.first;
			if (pimpl_->chords.at(i).size() > 5)
				transform(pimpl_->chords.at(i).cbegin() + 1, pimpl_->chords.at(i).cbegin()
					+ static_cast<int>(pimpl_->chords.at(i).size()) - 4,
					inserter(pimpl_->result.back().back(), pimpl_->result.back().back().begin() + 1),
					[](int16_t note)
					{
						return make_pair(note, '\0');
					});
		}
	}
}