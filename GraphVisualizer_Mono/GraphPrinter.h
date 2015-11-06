# pragma once

namespace Visualizer
{
	class GraphPrinter : private boost::noncopyable
	{
	public:
		GraphPrinter();
		~GraphPrinter();

		void Next(HDC);
	private:
		void DrawNewNodes(HDC) const;
		void DrawNewPaths(HDC) const;
		void ChangePen(HDC) const;

		const std::unique_ptr<class NodesLinker> pimpl_;
	};
}