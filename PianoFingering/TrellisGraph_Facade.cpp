# include "stdafx.h"
# include "TrellisGraph_Facade.h"
# include "NodesLinker.h"

using namespace std;

struct TrellisGraph_pimpl : private boost::noncopyable
{
	bool leftHand, unused[3];	// three padding bytes
	size_t currStep;
	vector<vector<int16_t>> chords;
	vector<vector<pair<int16_t, string>>> result;
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

const vector<vector<pair<int16_t, string>>>& TrellisGraph::GetResult() const
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

	for (size_t i(0); i < pimpl_->trellis.GetResultedGraph().front().size(); ++i)
	{
		const auto& node(pimpl_->trellis.GetResultedGraph().front().at(i)->first);
		vector<pair<int16_t, string>> resChord(node.size());
		for (size_t j(0); j < node.size(); ++j) resChord.at(j).first = node.at(j).first;
		for (const auto& path : pimpl_->trellis.GetResultedGraph())
			for (size_t j(0); j < path.at(i)->first.size(); ++j)
				if (find(resChord.at(j).second.cbegin(), resChord.at(j).second.cend(),
						path.at(i)->first.at(j).second + '0') == resChord.at(j).second.cend())
					resChord.at(j).second += path.at(i)->first.at(j).second + '0';

		const auto& chord(pimpl_->chords.at(i));
		if (chord.size() > 5) transform(chord.cbegin() + 1, chord.cbegin()
				+ static_cast<int>(chord.size()) - 4, inserter(resChord, resChord.begin() + 1),
			[](int16_t note)
			{
				return make_pair(note, string("?"));
			});

		pimpl_->result.push_back(resChord);
	}
	
	if (pimpl_->leftHand)
		for (auto& chord : pimpl_->result) for (auto& note : chord) note.first = NOTE_MI - note.first;
}