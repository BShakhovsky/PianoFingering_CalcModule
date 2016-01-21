# include "stdafx.h"
# include "TrellisGraph_Facade.h"
# include "MidiParser_Facade.h"

int main()
{
	using std::vector;

	const MidiParser_Facade midi("../../../Test.mid");
	vector<vector<int16_t>> chords({ { midi.GetNotes().at(1).front() } });
	auto lastTime(static_cast<int>(midi.GetMilliSeconds().at(1).front()));
	constexpr auto threshold(7);
	for (auto note(midi.GetNotes().at(1).cbegin() + 1); note != midi.GetNotes().at(1).cend(); ++note)
	{
		const auto newTime(static_cast<int>(midi.GetMilliSeconds().at(1).at(
			static_cast<size_t>(note - midi.GetNotes().at(1).cbegin()))));
		if (newTime - lastTime < threshold)
			chords.back().push_back(*note);
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
	for (const auto& path : graph.GetResult())
	{
		for (const auto& chord : path)
		{
			for (const auto& note : chord) printf("%d", note.second);
			printf(" ");
		}
		puts("\n");
	}
}