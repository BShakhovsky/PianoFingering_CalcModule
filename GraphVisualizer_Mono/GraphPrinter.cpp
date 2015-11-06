# include "stdafx.h"
# include "GraphPrinter.h"
# include "NodesLinker.h"

using namespace std;
using boost::lexical_cast;
using Visualizer::GraphPrinter;

GraphPrinter::GraphPrinter() :
	pimpl_(make_unique<NodesLinker>())
{}

GraphPrinter::~GraphPrinter() {}

void GraphPrinter::Next(const HDC hDC)
{
	pimpl_->CreateNewNodes();
	DrawNewNodes(hDC);

	pimpl_->LinkNewNodes();
	DrawNewPaths(hDC);
}


void GraphPrinter::DrawNewNodes(const HDC hDC) const
{
	const auto coordX(pimpl_->GetGraph().empty() ? 25 : 25 + 40 * pimpl_->GetGraph().front().size());
//	for (const auto& node : newNodes_)
	for (auto i(1); i <= 5; ++i)
	{
		const auto node(make_pair(i, i));

		Ellipse(hDC, static_cast<int>(coordX), node.first * 40, static_cast<int>(coordX) + 25, node.first * 40 + 25);
		TextOut(hDC, static_cast<int>(coordX) + 10, node.first * 40 + 5, lexical_cast<wstring>(node.second).c_str(),
			static_cast<int>(lexical_cast<wstring>(node.second).length()));
	}
}

void GraphPrinter::DrawNewPaths(const HDC hDC) const
{
	ChangePen(hDC);

	for (const auto& path : pimpl_->GetGraph())
	{
		auto pathEnd(path.cend());
		--pathEnd;
		auto i(NULL);
		for (auto node(path.cbegin()); node != pathEnd; ++node, ++i)
		{
			auto nextNode(node);
			++nextNode;
			MoveToEx(hDC, i * 40 + 25 + 12, node->first * 40 + 12, nullptr);
			LineTo(hDC, (i + 1) * 40 + 25 + 12, nextNode->first * 40 + 12);

			const auto coordX(25 + 40 * (i + 1));
			Ellipse(hDC, coordX, nextNode->first * 40, coordX + 25, nextNode->first * 40 + 25);
			TextOut(hDC, coordX + 10, nextNode->first * 40 + 5, lexical_cast<wstring>(nextNode->second).c_str(),
				static_cast<int>(lexical_cast<wstring>(nextNode->second).length()));
		}
	}
}

void GraphPrinter::ChangePen(const HDC hDC) const
{
	switch (pimpl_->GetGraph().front().size())
	{
	case 0: case 1:
	case 2: SelectObject(hDC, CreatePen(PS_SOLID, 1, RGB(0x80, 0x80, 0x80)));break;
	case 3: SelectObject(hDC, CreatePen(PS_SOLID, 2, RGB(0x80, 0x80, 0x80)));break;
	case 4: SelectObject(hDC, CreatePen(PS_SOLID, 3, RGB(0x80, 0x80, 0x80)));break;

	case 5: SelectObject(hDC, CreatePen(PS_SOLID, 1, RGB(0xFF, 0xFF, 0)));	break;
	case 6: SelectObject(hDC, CreatePen(PS_SOLID, 2, RGB(0xFF, 0xFF, 0)));	break;
	case 7: SelectObject(hDC, CreatePen(PS_SOLID, 3, RGB(0xFF, 0xFF, 0)));	break;

	case 8: SelectObject(hDC, CreatePen(PS_SOLID, 1, RGB(0, 0xFF, 0xFF)));	break;
	case 9: SelectObject(hDC, CreatePen(PS_SOLID, 2, RGB(0, 0xFF, 0xFF)));	break;
	case 10: SelectObject(hDC, CreatePen(PS_SOLID, 3, RGB(0, 0xFF, 0xFF)));	break;

	case 11: SelectObject(hDC, CreatePen(PS_SOLID, 1, RGB(0, 0xFF, 0)));	break;
	case 12: SelectObject(hDC, CreatePen(PS_SOLID, 2, RGB(0, 0xFF, 0)));	break;
	case 13: SelectObject(hDC, CreatePen(PS_SOLID, 3, RGB(0, 0xFF, 0)));	break;

	case 14: SelectObject(hDC, CreatePen(PS_SOLID, 1, RGB(0xFF, 0, 0xFF)));	break;
	case 15: SelectObject(hDC, CreatePen(PS_SOLID, 2, RGB(0xFF, 0, 0xFF)));	break;
	case 16: SelectObject(hDC, CreatePen(PS_SOLID, 3, RGB(0xFF, 0, 0xFF)));	break;

	case 17: SelectObject(hDC, CreatePen(PS_SOLID, 1, RGB(0, 0, 0xFF)));	break;
	case 18: SelectObject(hDC, CreatePen(PS_SOLID, 2, RGB(0, 0, 0xFF)));	break;
	case 19: SelectObject(hDC, CreatePen(PS_SOLID, 3, RGB(0, 0, 0xFF)));	break;

	case 20: SelectObject(hDC, CreatePen(PS_SOLID, 1, RGB(0xFF, 0, 0)));	break;
	case 21: SelectObject(hDC, CreatePen(PS_SOLID, 2, RGB(0xFF, 0, 0)));	break;
	case 22: SelectObject(hDC, CreatePen(PS_SOLID, 3, RGB(0xFF, 0, 0)));	break;

	case 23: SelectObject(hDC, CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));		break;
	case 24: SelectObject(hDC, CreatePen(PS_SOLID, 2, RGB(0, 0, 0)));		break;
	case 25: SelectObject(hDC, CreatePen(PS_SOLID, 3, RGB(0, 0, 0)));		break;

	case 26: SelectObject(hDC, CreatePen(PS_SOLID, 4, RGB(0, 0, 0)));		break;
	case 27: SelectObject(hDC, CreatePen(PS_SOLID, 5, RGB(0, 0, 0)));		break;
	case 28: SelectObject(hDC, CreatePen(PS_SOLID, 6, RGB(0, 0, 0)));		break;
	case 29: SelectObject(hDC, CreatePen(PS_SOLID, 7, RGB(0, 0, 0)));		break;
	case 30: SelectObject(hDC, CreatePen(PS_SOLID, 8, RGB(0, 0, 0)));		break;
	case 31: SelectObject(hDC, CreatePen(PS_SOLID, 9, RGB(0, 0, 0)));		break;
	case 32: SelectObject(hDC, CreatePen(PS_SOLID, 10, RGB(0, 0, 0)));
	default:																break;
	}
}