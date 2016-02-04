# include "stdafx.h"
# include "TrellisGraph_Facade.h"
# include "MidiParser_Facade.h"

int main()
{
	using namespace std;

	const auto trackNo(0);

	const MidiParser_Facade midi("../../../Test.mid");
	vector<set<int16_t>> chords({ { midi.GetNotes().at(trackNo).front() } });
	auto lastTime(static_cast<int>(midi.GetMilliSeconds().at(trackNo).front()));
	constexpr auto threshold(USER_TIMER_MINIMUM);	// should not be less than 7
	for (auto note(midi.GetNotes().at(trackNo).cbegin() + 1);
		note != midi.GetNotes().at(trackNo).cend(); ++note)
	{
		const auto newTime(static_cast<int>(midi.GetMilliSeconds().at(trackNo).at(
			static_cast<size_t>(note - midi.GetNotes().at(trackNo).cbegin()))));
		if (newTime - lastTime < threshold)
			chords.back().insert(*note);
		else
			chords.push_back({ *note });
		lastTime = newTime;
	}

	puts("\nFingering calculations started...");
	const auto timeStart(clock());
	TrellisGraph graph(chords);
	for (size_t i(1); i; i = graph.NextStep()) printf("\r%zu%%", i * 100 / chords.size());
	graph.Finish();
	const auto duration(clock() - timeStart);
	printf("\nFingering calculation time = %g seconds\n", static_cast<float>(duration) / CLOCKS_PER_SEC);
	system("Pause");

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	for (const auto& chord : chords)
	{
		printf("|");
		for (const auto& note : chord) printf("%d|", note);
		printf("\t");
	}
	puts("\n");
	system("Pause");
	for (const auto& chord : graph.GetResult())
	{
		printf("|");
		for (const auto& note : chord) printf("%s|", note.c_str());
		printf("\t");
	}
	puts("\n");
}