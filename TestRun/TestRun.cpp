# include "stdafx.h"
# include "..\PianoFingering\TrellisGraph_Facade.h"
# include "MidiParser_Facade.h"

int main()
{
	using std::vector;

	const MidiParser_Facade midi("../../Test.mid");
	vector<vector<int16_t>> chords;
	auto lastTime(-1);
	for (auto note(midi.GetNotes().at(1).cbegin()); note != midi.GetNotes().at(1).cend(); ++note)
	{
		const auto newTime(static_cast<int>(midi.GetMilliSeconds().at(1).at(
			static_cast<size_t>(note - midi.GetNotes().at(1).cbegin()))));
		if (newTime == lastTime)	chords.back().push_back(*note);
		else						chords.push_back({ *note });
	}

	puts("\nFingering calculations started...");
	const auto timeStart(clock());
	const TrellisGraph graph(chords);
	const auto duration(clock() - timeStart);
	printf("Fingering calculation time = %g seconds\n", static_cast<float>(duration) / CLOCKS_PER_SEC);
}