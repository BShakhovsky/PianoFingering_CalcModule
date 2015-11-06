# pragma once

namespace Visualizer
{
	class NodesLinker
	{
	public:
		NodesLinker();
		~NodesLinker() = default;

		typedef std::list<std::pair<char, float>> List_;
		std::list<List_> GetGraph() const
		{
			return graph_;
		}
		std::vector<int16_t> GetNotes() const
		{
			return notes_;
		}

		void CreateNewNodes();
		void LinkNewNodes();
	private:
		double MinPathFinder(std::pair<char, float> node);

		List_ newNodes_;
		std::list<List_> graph_;
		std::vector<std::list<List_>::const_iterator> minPaths_;

		const std::vector<int16_t> notes_;
	};
}