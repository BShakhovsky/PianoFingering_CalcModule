# include "stdafx.h"
# include "PianoFingering\NodesLinker.h"
# include "TrellisGraph_Common.h"

using gTest::TrellisGraph_Common;

class NodesLinker_F : public TrellisGraph_Common
{
public:
	NodesLinker_F() : TrellisGraph_Common() {}
	NodesLinker_F(const NodesLinker_F&) = default;
	NodesLinker_F& operator = (const NodesLinker_F&) = default;

	virtual ~NodesLinker_F() override = default;

	virtual void SetUp() override final
	{
		TrellisGraph_Common::SetUp();
	}
	virtual void TearDown() override final
	{
		TrellisGraph_Common::TearDown();
	}
};

/*******************************************************************************
TEST_F(NodesLinker_F, LinkNewNodes)
{
	using std::make_pair;

	NodesLinker graph;
	graph.LinkNewNodes({ 1i16, 2i16 });
	ASSERT_EQ(14, graph.GetResultedGraph().size());
	for (const auto& path : graph.GetResultedGraph()) ASSERT_EQ(1, path.size());
	ASSERT_EQ(NULL, graph.GetResultedGraph().front().front()->second);
	ASSERT_EQ(4, graph.GetResultedGraph().at(1).front()->second);
	ASSERT_EQ(9, graph.GetResultedGraph().at(2).front()->second);
	ASSERT_EQ(13, graph.GetResultedGraph().at(3).front()->second);

	ASSERT_EQ(4, graph.GetResultedGraph().at(4).front()->second);
	ASSERT_EQ(NULL, graph.GetResultedGraph().at(5).front()->second);
	ASSERT_EQ(9, graph.GetResultedGraph().at(6).front()->second);
	ASSERT_EQ(31, graph.GetResultedGraph().at(7).front()->second);

	ASSERT_EQ(8, graph.GetResultedGraph().at(8).front()->second);
	ASSERT_EQ(1, graph.GetResultedGraph().at(9).front()->second);
	ASSERT_EQ(9, graph.GetResultedGraph().at(10).front()->second);

	ASSERT_EQ(13, graph.GetResultedGraph().at(11).front()->second);
	ASSERT_EQ(2, graph.GetResultedGraph().at(12).front()->second);

	ASSERT_EQ(25, graph.GetResultedGraph().back().front()->second);


	graph.LinkNewNodes({ 3i16 });
	ASSERT_EQ(5, graph.GetResultedGraph().size());
	for (const auto& path : graph.GetResultedGraph())
	{
		ASSERT_EQ(2, path.size());
		ASSERT_EQ(1, path.back()->first.size());
		ASSERT_EQ(2, path.front()->first.size());
	}
	ASSERT_EQ(make_pair(3i16, '\1'), graph.GetResultedGraph().front().back()->first.front());
	ASSERT_EQ(make_pair(3i16, '\2'), graph.GetResultedGraph().at(1).back()->first.front());
	ASSERT_EQ(make_pair(3i16, '\3'), graph.GetResultedGraph().at(2).back()->first.front());
	ASSERT_EQ(make_pair(3i16, '\4'), graph.GetResultedGraph().at(3).back()->first.front());
	ASSERT_EQ(make_pair(3i16, '\5'), graph.GetResultedGraph().back().back()->first.front());

	ASSERT_EQ(make_pair(1i16, '\2'), graph.GetResultedGraph().front().front()->first.front());
	ASSERT_EQ(make_pair(2i16, '\3'), graph.GetResultedGraph().front().front()->first.back());
	ASSERT_EQ(6, graph.GetResultedGraph().front().back()->second);
	ASSERT_EQ(make_pair(1i16, '\1'), graph.GetResultedGraph().at(1).front()->first.front());
	ASSERT_EQ(make_pair(2i16, '\2'), graph.GetResultedGraph().at(1).front()->first.back());
	ASSERT_EQ(4.25, graph.GetResultedGraph().at(1).back()->second);
	ASSERT_EQ(make_pair(1i16, '\1'), graph.GetResultedGraph().at(2).front()->first.front());
	ASSERT_EQ(make_pair(2i16, '\2'), graph.GetResultedGraph().at(2).front()->first.back());
	ASSERT_EQ(0.75, graph.GetResultedGraph().at(2).back()->second);
	ASSERT_EQ(make_pair(1i16, '\2'), graph.GetResultedGraph().at(3).front()->first.front());
	ASSERT_EQ(make_pair(2i16, '\3'), graph.GetResultedGraph().at(3).front()->first.back());
	ASSERT_EQ(3, graph.GetResultedGraph().at(3).back()->second);
	ASSERT_EQ(make_pair(1i16, '\3'), graph.GetResultedGraph().back().front()->first.front());
	ASSERT_EQ(make_pair(2i16, '\4'), graph.GetResultedGraph().back().front()->first.back());
	ASSERT_EQ(3.5, graph.GetResultedGraph().back().back()->second);


	graph.LinkNewNodes({ 2i16 });
	ASSERT_EQ(5, graph.GetResultedGraph().size());
	for (const auto& path : graph.GetResultedGraph())
	{
		ASSERT_EQ(3, path.size());
		ASSERT_EQ(1, path.back()->first.size());
		ASSERT_EQ(2, path.front()->first.size());
		ASSERT_EQ(1, path.at(1)->first.size());
	}
	ASSERT_EQ(make_pair(2i16, '\1'), graph.GetResultedGraph().front().back()->first.front());
	ASSERT_EQ(make_pair(2i16, '\2'), graph.GetResultedGraph().at(1).back()->first.front());
	ASSERT_EQ(make_pair(2i16, '\3'), graph.GetResultedGraph().at(2).back()->first.front());
	ASSERT_EQ(make_pair(2i16, '\4'), graph.GetResultedGraph().at(3).back()->first.front());
	ASSERT_EQ(make_pair(2i16, '\5'), graph.GetResultedGraph().back().back()->first.front());

	ASSERT_EQ(make_pair(3i16, '\3'), graph.GetResultedGraph().front().at(1)->first.front());
	ASSERT_EQ(3.25, graph.GetResultedGraph().front().back()->second);
	ASSERT_EQ(make_pair(3i16, '\3'), graph.GetResultedGraph().at(1).at(1)->first.front());
	ASSERT_EQ(0.75, graph.GetResultedGraph().at(1).back()->second);
	ASSERT_EQ(make_pair(3i16, '\4'), graph.GetResultedGraph().at(2).at(1)->first.front());
	ASSERT_EQ(5, graph.GetResultedGraph().at(2).back()->second);
	ASSERT_EQ(make_pair(3i16, '\5'), graph.GetResultedGraph().at(3).at(1)->first.front());
	ASSERT_EQ(6, graph.GetResultedGraph().at(3).back()->second);
	ASSERT_EQ(make_pair(3i16, '\5'), graph.GetResultedGraph().back().at(1)->first.front());
	ASSERT_EQ(14, graph.GetResultedGraph().back().back()->second);


	graph.RemoveExpensivePaths();
	ASSERT_EQ(1, graph.GetResultedGraph().size());
	ASSERT_EQ(0.75, graph.GetResultedGraph().front().back()->second);
}
*******************************************************************************/

TEST_F(NodesLinker_F, RemoveExpensivePaths)
{
	NodesLinker graph;
	graph.LinkNewNodes({ 0i16 });
	graph.LinkNewNodes({ 9i16 });
	ASSERT_EQ(0, graph.GetResultedGraph().size());

	graph.RemoveExpensivePaths();
	ASSERT_EQ(2, graph.GetResultedGraph().size());
	ASSERT_STREQ("1", graph.GetResultedGraph().front().front().c_str());
	ASSERT_STREQ("54", graph.GetResultedGraph().back().front().c_str());
}

// http://ismir2007.ismir.net/proceedings/ISMIR2007_p355_kasimi.pdf

TEST_F(NodesLinker_F, Figure4)	// Page 2, Figure 4
{
	NodesLinker graph;
	graph.LinkNewNodes({ DO, MI, SO });
	graph.LinkNewNodes({ FA, LA });
	graph.RemoveExpensivePaths();
	ASSERT_EQ(2, graph.GetResultedGraph().size());
	ASSERT_STREQ("1", graph.GetResultedGraph().front().front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().front().at(1).c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().front().back().c_str());

	ASSERT_STREQ("3", graph.GetResultedGraph().back().front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().back().back().c_str());
}

TEST_F(NodesLinker_F, EllmenreichSpinningSong)	// Page 2, Figure 6
{
	NodesLinker graph;
	graph.LinkNewNodes({ LA });
	graph.LinkNewNodes({ SI_B });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ LA, FA_1 });
	graph.LinkNewNodes({ DO_1, SO_1 });
	graph.LinkNewNodes({ FA_1, LA_1 });

	graph.LinkNewNodes({ LA });
	graph.LinkNewNodes({ SI_B });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ LA, DO_1, FA_1 });
	graph.LinkNewNodes({ SI_B, DO_1, MI_1 });
	graph.LinkNewNodes({ LA, DO_1, FA_1 });

	graph.LinkNewNodes({ MI_1, SO_1 });
	graph.LinkNewNodes({ FA_1, LA_B_1 });
	graph.LinkNewNodes({ FA_S_1, LA_1 });
	graph.LinkNewNodes({ SO_1, SI_B_1 });
	graph.LinkNewNodes({ SI_B_1, RE_2 });
	graph.LinkNewNodes({ LA_1, DO_2 });
	graph.LinkNewNodes({ SO_1, SI_B_1 });
	graph.LinkNewNodes({ FA_1, LA_1 });
	graph.LinkNewNodes({ MI_1, SO_1 });
	graph.LinkNewNodes({ FA_1, SO_1, SI_1 });
	graph.LinkNewNodes({ MI_1, SO_1, DO_2 });

	graph.LinkNewNodes({ MI_1, SO_1 });
	graph.LinkNewNodes({ FA_1, LA_B_1 });
	graph.LinkNewNodes({ FA_S_1, LA_1 });
	graph.LinkNewNodes({ SO_1, SI_B_1 });
	graph.LinkNewNodes({ SI_B_1, RE_2 });
	graph.LinkNewNodes({ LA_1, DO_2 });
	graph.LinkNewNodes({ SO_1, SI_B_1 });
	graph.LinkNewNodes({ FA_1, LA_1 });
	graph.LinkNewNodes({ MI_1, SO_1 });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ SI_B });

	graph.LinkNewNodes({ LA });
	graph.LinkNewNodes({ SI_B });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ LA, FA_1 });
	graph.LinkNewNodes({ DO_1, SO_1 });
	graph.LinkNewNodes({ FA_1, LA_1 });

	graph.RemoveExpensivePaths();
	ASSERT_EQ(47, graph.GetResultedGraph().size());
	ASSERT_STREQ("1", graph.GetResultedGraph().front().front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(1).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(2).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(3).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(4).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(5).front().c_str());
//	ASSERT_STREQ("5", graph.GetResultedGraph().at(5).back().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(6).front().c_str());
//	ASSERT_STREQ("4", graph.GetResultedGraph().at(6).back().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(7).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(7).back().c_str());

	ASSERT_STREQ("1", graph.GetResultedGraph().at(8).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(9).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(10).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(11).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(12).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(13).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(13).at(1).c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(13).back().c_str());
//	ASSERT_STREQ("2", graph.GetResultedGraph().at(14).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(14).at(1).c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(14).back().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(15).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(15).at(1).c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(15).back().c_str());

//	ASSERT_STREQ("1", graph.GetResultedGraph().at(16).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(16).back().c_str());
//	ASSERT_STREQ("2", graph.GetResultedGraph().at(17).front().c_str());
//	ASSERT_STREQ("4", graph.GetResultedGraph().at(17).back().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(18).front().c_str());
//	ASSERT_STREQ("5", graph.GetResultedGraph().at(18).back().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(19).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(19).back().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(20).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(20).back().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(21).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(21).back().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(22).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(22).back().c_str());
//	ASSERT_STREQ("2", graph.GetResultedGraph().at(23).front().c_str());
//	ASSERT_STREQ("4", graph.GetResultedGraph().at(23).back().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(24).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(24).back().c_str());
//	ASSERT_STREQ("2", graph.GetResultedGraph().at(25).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(25).at(1).c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(25).back().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(26).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(26).at(1).c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(26).back().c_str());

	ASSERT_STREQ("1", graph.GetResultedGraph().at(27).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(27).back().c_str());
//	ASSERT_STREQ("2", graph.GetResultedGraph().at(28).front().c_str());
//	ASSERT_STREQ("4", graph.GetResultedGraph().at(28).back().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(29).front().c_str());
//	ASSERT_STREQ("5", graph.GetResultedGraph().at(29).back().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(30).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(30).back().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(31).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(31).back().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(32).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(32).back().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(33).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(33).back().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(34).front().c_str());
//	ASSERT_STREQ("5", graph.GetResultedGraph().at(34).back().c_str());
//	ASSERT_STREQ("2", graph.GetResultedGraph().at(35).front().c_str());
//	ASSERT_STREQ("4", graph.GetResultedGraph().at(35).back().c_str());
//	ASSERT_STREQ("1", graph.GetResultedGraph().at(36).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(37).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(38).front().c_str());

	ASSERT_STREQ("1", graph.GetResultedGraph().at(39).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(40).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(41).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(42).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(43).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(44).front().c_str());
//	ASSERT_STREQ("5", graph.GetResultedGraph().at(44).back().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(45).front().c_str());
//	ASSERT_STREQ("4", graph.GetResultedGraph().at(45).back().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().back().front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().back().back().c_str());
}

// http://web.cs.ucdavis.edu/~neff/papers/cav1477.pdf
// Page 9, Figure 13

TEST_F(NodesLinker_F, BilderEinerAusstellung)
{
	NodesLinker graph;
	graph.LinkNewNodes({ MI, SO, DO_1 });
	graph.LinkNewNodes({ DO, RE, FA, LA });
	graph.LinkNewNodes({ MI, SO, DO_1 });
	graph.LinkNewNodes({ FA, FA_1 });
	graph.LinkNewNodes({ MI_B, SO, SI_B, MI_B_1 });
	graph.LinkNewNodes({ RE, RE_1 });
	graph.RemoveExpensivePaths();
	ASSERT_EQ(6, graph.GetResultedGraph().size());
	ASSERT_STREQ("1", graph.GetResultedGraph().front().front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().front().at(1).c_str());
//	ASSERT_STREQ("4", graph.GetResultedGraph().front().back().c_str());

	ASSERT_STREQ("1", graph.GetResultedGraph().at(1).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(1).at(1).c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(1).at(2).c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(1).back().c_str());

	ASSERT_STREQ("1", graph.GetResultedGraph().at(2).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(2).at(1).c_str());
//	ASSERT_STREQ("4", graph.GetResultedGraph().at(2).back().c_str());

	ASSERT_STREQ("1", graph.GetResultedGraph().at(3).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(3).back().c_str());

	ASSERT_STREQ("1", graph.GetResultedGraph().at(4).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(4).at(1).c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(4).at(2).c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(4).back().c_str());

	ASSERT_STREQ("1", graph.GetResultedGraph().back().front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().back().back().c_str());
}

// http://www.diva-portal.org/smash/get/diva2:769592/FULLTEXT01.pdf
// Page 16

TEST_F(NodesLinker_F, Chopin_FirstScherzo)	// Figure 10
{
	NodesLinker graph;
	graph.LinkNewNodes({ FA });
	graph.LinkNewNodes({ FA_S });
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ LA_S });
	graph.LinkNewNodes({ DO_S_1 });
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ FA_S_1 });
	graph.LinkNewNodes({ SI_1 });
	graph.RemoveExpensivePaths();
	ASSERT_EQ(10, graph.GetResultedGraph().size());
	ASSERT_STREQ("1", graph.GetResultedGraph().front().front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(1).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(2).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(3).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(4).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(5).front().c_str());
//	ASSERT_STREQ("1", graph.GetResultedGraph().at(6).front().c_str());
//	ASSERT_STREQ("2", graph.GetResultedGraph().at(7).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(8).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().back().front().c_str());
}

TEST_F(NodesLinker_F, Entertainer)	// Figure 11
{
	NodesLinker graph1, graph2, graph3;
	graph1.LinkNewNodes({ RE });
	graph1.LinkNewNodes({ RE_S });
	graph1.LinkNewNodes({ MI });
	graph1.LinkNewNodes({ DO_1 });
	graph1.LinkNewNodes({ MI });
	graph1.LinkNewNodes({ DO_1 });
	graph1.LinkNewNodes({ MI });
	graph1.LinkNewNodes({ DO_1 });

	graph2.LinkNewNodes({ DO_1 });
	graph2.LinkNewNodes({ RE_1 });
	graph2.LinkNewNodes({ RE_S_1 });
	graph2.LinkNewNodes({ MI_1 });
	graph2.LinkNewNodes({ DO_1 });
	graph2.LinkNewNodes({ RE_1 });
	graph2.LinkNewNodes({ MI_1 });
	graph2.LinkNewNodes({ SI });
	graph2.LinkNewNodes({ RE_1 });
	graph2.LinkNewNodes({ DO_1 });
	
	graph3.LinkNewNodes({ RE });
	graph3.LinkNewNodes({ RE_S });
	graph3.LinkNewNodes({ MI });
	graph3.LinkNewNodes({ DO_1 });
	graph3.LinkNewNodes({ MI });
	graph3.LinkNewNodes({ DO_1 });
	graph3.LinkNewNodes({ MI });
	graph3.LinkNewNodes({ DO_1 });
	graph3.LinkNewNodes({ LA });
	graph3.LinkNewNodes({ SO });
	graph3.LinkNewNodes({ FA_S });
	graph3.LinkNewNodes({ LA });
	graph3.LinkNewNodes({ DO_1 });
	graph3.LinkNewNodes({ MI_1 });
	graph3.LinkNewNodes({ RE_1 });
	graph3.LinkNewNodes({ DO_1 });
	graph3.LinkNewNodes({ LA });
	graph3.LinkNewNodes({ RE_1 });

	graph1.RemoveExpensivePaths();
	graph2.RemoveExpensivePaths();
	graph3.RemoveExpensivePaths();
	ASSERT_EQ(8, graph1.GetResultedGraph().size());
	ASSERT_EQ(10, graph2.GetResultedGraph().size());
	ASSERT_EQ(18, graph3.GetResultedGraph().size());
	ASSERT_STREQ("1", graph1.GetResultedGraph().front().front().c_str());
	ASSERT_STREQ("2", graph1.GetResultedGraph().at(1).front().c_str());
	ASSERT_STREQ("1", graph1.GetResultedGraph().at(2).front().c_str());
	ASSERT_STREQ("5", graph1.GetResultedGraph().at(3).front().c_str());
	ASSERT_STREQ("1", graph1.GetResultedGraph().at(4).front().c_str());
	ASSERT_STREQ("5", graph1.GetResultedGraph().at(5).front().c_str());
	ASSERT_STREQ("1", graph1.GetResultedGraph().at(6).front().c_str());
	ASSERT_STREQ("5", graph1.GetResultedGraph().back().front().c_str());


	ASSERT_STREQ("1", graph2.GetResultedGraph().front().front().c_str());
	ASSERT_STREQ("2", graph2.GetResultedGraph().at(1).front().c_str());
	ASSERT_STREQ("3", graph2.GetResultedGraph().at(2).front().c_str());
	ASSERT_STREQ("4", graph2.GetResultedGraph().at(3).front().c_str());
	ASSERT_STREQ("1", graph2.GetResultedGraph().at(4).front().c_str());
//	ASSERT_STREQ("3", graph2.GetResultedGraph().at(5).front().c_str());
//	ASSERT_STREQ("4", graph2.GetResultedGraph().at(6).front().c_str());
	ASSERT_STREQ("1", graph2.GetResultedGraph().at(7).front().c_str());

//	ASSERT_EQ('4', graph2.GetResultedGraph().at(8).front().front());
	ASSERT_EQ('3', graph2.GetResultedGraph().at(8).front().back());
//	ASSERT_EQ('3', graph2.GetResultedGraph().back().front().front());
	ASSERT_EQ('2', graph2.GetResultedGraph().back().front().back());


	ASSERT_STREQ("1", graph3.GetResultedGraph().front().front().c_str());
	ASSERT_STREQ("2", graph3.GetResultedGraph().at(1).front().c_str());
	ASSERT_STREQ("1", graph3.GetResultedGraph().at(2).front().c_str());
	ASSERT_STREQ("5", graph3.GetResultedGraph().at(3).front().c_str());
	ASSERT_STREQ("1", graph3.GetResultedGraph().at(4).front().c_str());
	ASSERT_STREQ("5", graph3.GetResultedGraph().at(5).front().c_str());
	ASSERT_STREQ("1", graph3.GetResultedGraph().at(6).front().c_str());
	ASSERT_STREQ("5", graph3.GetResultedGraph().at(7).front().c_str());

	ASSERT_STREQ("3", graph3.GetResultedGraph().at(8).front().c_str()) << "may also be 4";
	ASSERT_STREQ("2", graph3.GetResultedGraph().at(9).front().c_str()) << "may also be 3";
	ASSERT_STREQ("1", graph3.GetResultedGraph().at(10).front().c_str()) << "may also be 2";
	ASSERT_STREQ("2", graph3.GetResultedGraph().at(11).front().c_str()) << "may also be 1";

	ASSERT_STREQ("3", graph3.GetResultedGraph().at(12).front().c_str());
	ASSERT_STREQ("5", graph3.GetResultedGraph().at(13).front().c_str());
//	ASSERT_STREQ("4", graph3.GetResultedGraph().at(14).front().c_str());
//	ASSERT_STREQ("3", graph3.GetResultedGraph().at(15).front().c_str());
//	ASSERT_STREQ("2", graph3.GetResultedGraph().at(16).front().c_str());

//	ASSERT_STREQ("54", graph3.GetResultedGraph().back().front().c_str());
}

TEST_F(NodesLinker_F, FurElise)	// Figure 12
{
	NodesLinker graph;
	graph.LinkNewNodes({ MI_1 });
	graph.LinkNewNodes({ RE_S_1 });
	graph.LinkNewNodes({ MI_1 });
	graph.LinkNewNodes({ RE_S_1 });
	graph.LinkNewNodes({ MI_1 });
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ LA });
	graph.LinkNewNodes({ DO });
	graph.LinkNewNodes({ MI });
	graph.LinkNewNodes({ LA });
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ MI });
	graph.LinkNewNodes({ SO_S });
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ DO });
	
	graph.LinkNewNodes({ MI });
	graph.LinkNewNodes({ MI_1 });
	graph.LinkNewNodes({ RE_S_1 });
	graph.LinkNewNodes({ MI_1 });
	graph.LinkNewNodes({ RE_S_1 });
	graph.LinkNewNodes({ MI_1 });
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ LA });
	graph.LinkNewNodes({ DO });
	graph.LinkNewNodes({ MI });
	graph.LinkNewNodes({ LA });
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ MI });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ LA });
	
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ MI_1 });
	graph.LinkNewNodes({ SO });
	graph.LinkNewNodes({ FA_1 });
	graph.LinkNewNodes({ MI_1 });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ FA });
	graph.LinkNewNodes({ MI_1 });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ MI });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ MI });
	graph.LinkNewNodes({ MI_1 });
	
	graph.RemoveExpensivePaths();
	ASSERT_EQ(53, graph.GetResultedGraph().size());
	ASSERT_STREQ("3", graph.GetResultedGraph().front().front().c_str()) << "may also be 5";
	ASSERT_STREQ("2", graph.GetResultedGraph().at(1).front().c_str()) << "may also be 4";
	ASSERT_STREQ("3", graph.GetResultedGraph().at(2).front().c_str()) << "may also be 5";
	ASSERT_STREQ("2", graph.GetResultedGraph().at(3).front().c_str()) << "may also be 4";
	ASSERT_STREQ("3", graph.GetResultedGraph().at(4).front().c_str()) << "may also be 5";
	ASSERT_STREQ("1", graph.GetResultedGraph().at(5).front().c_str()) << "may also be 2";
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(6).front().c_str()) << "may also be 4";
//	ASSERT_STREQ("2", graph.GetResultedGraph().at(7).front().c_str()) << "may also be 3";
	ASSERT_STREQ("2", graph.GetResultedGraph().at(8).front().c_str()) << "may also be 1";
	ASSERT_STREQ("1", graph.GetResultedGraph().at(9).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(10).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(11).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(12).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(13).front().c_str());

	ASSERT_STREQ("3", graph.GetResultedGraph().at(14).front().c_str()) << "may also be 2";
//	ASSERT_STREQ("4", graph.GetResultedGraph().at(15).front().c_str()) << "may also be 3";
//	ASSERT_STREQ("5", graph.GetResultedGraph().at(16).front().c_str()) << "may also be 4";

	ASSERT_STREQ("1", graph.GetResultedGraph().at(17).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(18).front().c_str()) << "may also be 3";
	ASSERT_STREQ("4", graph.GetResultedGraph().at(19).front().c_str()) << "may also be 2";
	ASSERT_STREQ("5", graph.GetResultedGraph().at(20).front().c_str()) << "may also be 3";
	ASSERT_STREQ("4", graph.GetResultedGraph().at(21).front().c_str()) << "may also be 2";
	ASSERT_STREQ("5", graph.GetResultedGraph().at(22).front().c_str()) << "may also be 3";
	ASSERT_STREQ("2", graph.GetResultedGraph().at(23).front().c_str()) << "may also be 1";
	ASSERT_STREQ("4", graph.GetResultedGraph().at(24).front().c_str()) << "may also be 3";
	ASSERT_STREQ("3", graph.GetResultedGraph().at(25).front().c_str()) << "may also be 2";
	ASSERT_STREQ("2", graph.GetResultedGraph().at(26).front().c_str()) << "may also be 1";
	ASSERT_STREQ("1", graph.GetResultedGraph().at(27).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(28).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(29).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(30).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(31).front().c_str());
//	ASSERT_STREQ("5", graph.GetResultedGraph().at(32).front().c_str());
//	ASSERT_STREQ("4", graph.GetResultedGraph().at(33).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(34).front().c_str());

	ASSERT_STREQ("2", graph.GetResultedGraph().at(35).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(36).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(37).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(38).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(39).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(40).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(41).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(42).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(43).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(44).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(45).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(46).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(47).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(48).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(49).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(50).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(51).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().back().front().c_str());
}

// http://www.scriptiebank.be/sites/default/files/webform/scriptie/balliauw-matteo-2014_0.pdf

TEST_F(NodesLinker_F, JSBach_Menuet4_BWVanh114)	// Page 27, Figure 12
{
	NodesLinker graph;
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ SO });
	graph.LinkNewNodes({ LA });
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ SO });
	graph.LinkNewNodes({ SO });
	
	graph.LinkNewNodes({ MI_1 });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ MI_1 });
	graph.LinkNewNodes({ FA_S_1 });
	graph.LinkNewNodes({ SO_1 });
	graph.LinkNewNodes({ SO });
	graph.LinkNewNodes({ SO });
	
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ LA });
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ LA });
	graph.LinkNewNodes({ SO });
	graph.LinkNewNodes({ FA_S });
	graph.LinkNewNodes({ SO });
	graph.LinkNewNodes({ LA });
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ SO });
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ LA });

	graph.RemoveExpensivePaths();
	ASSERT_EQ(33, graph.GetResultedGraph().size());
//	ASSERT_STREQ("5", graph.GetResultedGraph().front().front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(1).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(2).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(3).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(4).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(5).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(6).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(7).front().c_str());

	ASSERT_EQ('4', graph.GetResultedGraph().at(8).front().back());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(9).front().c_str()) << "may also be 2";
	ASSERT_STREQ("2", graph.GetResultedGraph().at(10).front().c_str()) << "may also be 1";
	ASSERT_STREQ("3", graph.GetResultedGraph().at(11).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(12).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(13).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(14).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(15).front().c_str());

//	ASSERT_STREQ("4", graph.GetResultedGraph().at(16).front().c_str());
//	ASSERT_STREQ("5", graph.GetResultedGraph().at(17).front().c_str());
//	ASSERT_STREQ("4", graph.GetResultedGraph().at(18).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(19).front().c_str());
//	ASSERT_STREQ("2", graph.GetResultedGraph().at(20).front().c_str());

//	ASSERT_STREQ("3", graph.GetResultedGraph().at(21).front().c_str()) << "may also be 4";
//	ASSERT_STREQ("4", graph.GetResultedGraph().at(22).front().c_str()) << "may also be 5";
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(23).front().c_str()) << "may also be 4";
	ASSERT_STREQ("2", graph.GetResultedGraph().at(24).front().c_str()) << "may also be 3";

	ASSERT_STREQ("1", graph.GetResultedGraph().at(25).front().c_str());

	ASSERT_STREQ("2", graph.GetResultedGraph().at(26).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(27).front().c_str());
//	ASSERT_STREQ("4", graph.GetResultedGraph().at(28).front().c_str());
//	ASSERT_STREQ("5", graph.GetResultedGraph().at(29).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(30).front().c_str()) << "may also be 2";
//	ASSERT_STREQ("5", graph.GetResultedGraph().at(31).front().c_str()) << "may also be 4";
//	ASSERT_STREQ("4", graph.GetResultedGraph().back().front().c_str()) << "may also be 3";
}

TEST_F(NodesLinker_F, GFHandel_DSuite_HWV437_Saraband)	// Page 28, Figure 14
{
	NodesLinker graph;
	graph.LinkNewNodes({ FA_1 });
	graph.LinkNewNodes({ LA });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ LA_1 });
	graph.LinkNewNodes({ SO_1 });
	graph.LinkNewNodes({ FA_1 });
	graph.LinkNewNodes({ MI_1 });
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ DO_S_1 });
	graph.LinkNewNodes({ LA_1 });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ FA_1 });
	graph.LinkNewNodes({ DO_2 });
	graph.LinkNewNodes({ SI_B_1 });
	graph.LinkNewNodes({ LA_1 });
	graph.LinkNewNodes({ SO_1 });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ MI_1 });
	
	graph.LinkNewNodes({ LA_1 });
	graph.LinkNewNodes({ SI_B_1 });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ SO_1 });
	graph.LinkNewNodes({ RE_2 });
	graph.LinkNewNodes({ DO_2 });
	graph.LinkNewNodes({ SI_B_1 });
	graph.LinkNewNodes({ LA_1 });

	graph.LinkNewNodes({ SO_1 });
	graph.LinkNewNodes({ FA_1 });
	graph.LinkNewNodes({ MI_1 });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ LA_1 });
	graph.LinkNewNodes({ LA_1, RE_2 });
	graph.LinkNewNodes({ LA_1 });
	graph.LinkNewNodes({ SO_1 });

	graph.LinkNewNodes({ FA_2 });
	graph.LinkNewNodes({ MI_2 });
	graph.LinkNewNodes({ RE_2 });
	graph.LinkNewNodes({ DO_S_2 });
	graph.LinkNewNodes({ MI_2 });
	graph.LinkNewNodes({ LA_1 });
	graph.LinkNewNodes({ DO_S_2 });
	graph.LinkNewNodes({ MI_1 });
	graph.LinkNewNodes({ SO_1 });

	graph.RemoveExpensivePaths();
	ASSERT_EQ(43, graph.GetResultedGraph().size());
	ASSERT_EQ('4', graph.GetResultedGraph().front().front().at(1));
	ASSERT_STREQ("1", graph.GetResultedGraph().at(1).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(2).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(3).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(4).front().c_str());
//	ASSERT_STREQ("1", graph.GetResultedGraph().at(5).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(6).front().c_str()) << "may also be 4";
	ASSERT_STREQ("1", graph.GetResultedGraph().at(7).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(8).front().c_str());

//	ASSERT_STREQ("4", graph.GetResultedGraph().at(9).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(10).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(11).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(12).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(13).front().c_str());
//	ASSERT_STREQ("1", graph.GetResultedGraph().at(14).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(15).front().c_str()) << "may also be 4";
	ASSERT_STREQ("1", graph.GetResultedGraph().at(16).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(17).front().c_str());

//	ASSERT_STREQ("2", graph.GetResultedGraph().at(18).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(19).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(20).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(21).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().at(22).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(23).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(24).front().c_str()) << "may also be 3";
	ASSERT_STREQ("1", graph.GetResultedGraph().at(25).front().c_str());

//	ASSERT_STREQ("4", graph.GetResultedGraph().at(26).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(27).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(28).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(29).front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(30).front().c_str());
//	ASSERT_STREQ("1", graph.GetResultedGraph().at(31).front().c_str());
//	ASSERT_STREQ("4", graph.GetResultedGraph().at(31).back().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(32).front().c_str()) << "may also be 3";
	ASSERT_STREQ("1", graph.GetResultedGraph().at(33).front().c_str());

	ASSERT_STREQ("5", graph.GetResultedGraph().at(34).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(35).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(36).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(37).front().c_str());
//	ASSERT_STREQ("5", graph.GetResultedGraph().at(38).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(39).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(40).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(41).front().c_str());
//	ASSERT_STREQ("5", graph.GetResultedGraph().back().front().c_str()) << "may also be 4";
}

// http://www.csc.kth.se/utbildning/kth/kurser/DD143X/dkand13/Group7Anders/final/Bassam.Alfarhan.David.Sandberg.report.pdf
// Page 14

TEST_F(NodesLinker_F, AllOfMe)	// Figure 4.1
{
	NodesLinker graph;
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ SO });
	graph.LinkNewNodes({ MI });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ RE_1 });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ SI });
	graph.LinkNewNodes({ SO_S });
	graph.LinkNewNodes({ MI });
	graph.RemoveExpensivePaths();
	ASSERT_EQ(9, graph.GetResultedGraph().size());
	ASSERT_STREQ("5", graph.GetResultedGraph().front().front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(1).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(2).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(3).front().c_str()) << "may also be 2";
	ASSERT_STREQ("5", graph.GetResultedGraph().at(4).front().c_str()) << "may also be 3";
	ASSERT_STREQ("4", graph.GetResultedGraph().at(5).front().c_str()) << "may also be 2";
	ASSERT_STREQ("3", graph.GetResultedGraph().at(6).front().c_str()) << "may also be 1";
	ASSERT_STREQ("2", graph.GetResultedGraph().at(7).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().back().front().c_str());
}

TEST_F(NodesLinker_F, AintMisbehavin)	// Figure 4.2
{
	NodesLinker graph;
	graph.LinkNewNodes({ MI_B });
	graph.LinkNewNodes({ FA });
	graph.LinkNewNodes({ MI_B });
	graph.LinkNewNodes({ SI_B });
	graph.LinkNewNodes({ SI_B });
	graph.LinkNewNodes({ FA });
	graph.LinkNewNodes({ SO });
	graph.LinkNewNodes({ FA });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ SI_B });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ SI_B });
	graph.LinkNewNodes({ MI_B_1 });
	graph.RemoveExpensivePaths();
	ASSERT_EQ(13, graph.GetResultedGraph().size());
//	ASSERT_STREQ("2", graph.GetResultedGraph().front().front().c_str());
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(1).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(2).front().c_str()) << "may also be 2";
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(3).front().c_str()) << "may also be 5";
//	ASSERT_STREQ("3", graph.GetResultedGraph().at(4).front().c_str()) << "may also be 5";
	ASSERT_STREQ("1", graph.GetResultedGraph().at(5).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(6).front().c_str()) << "may also be 3";
	ASSERT_STREQ("1", graph.GetResultedGraph().at(7).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(8).front().c_str()) << "may also be 5";
	ASSERT_STREQ("2", graph.GetResultedGraph().at(9).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(10).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(11).front().c_str());
	ASSERT_STREQ("5", graph.GetResultedGraph().back().front().c_str());
}

TEST_F(NodesLinker_F, AllaFaglarKommitRen)	// Figure 4.3
{
	NodesLinker graph;
	graph.LinkNewNodes({ DO });
	graph.LinkNewNodes({ MI });
	graph.LinkNewNodes({ SO });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ LA });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ LA });
	graph.LinkNewNodes({ SO });
	graph.LinkNewNodes({ FA });
	graph.LinkNewNodes({ SO });
	graph.LinkNewNodes({ MI });
	graph.LinkNewNodes({ DO });
	graph.LinkNewNodes({ RE });
	graph.LinkNewNodes({ DO });
	graph.RemoveExpensivePaths();
	ASSERT_EQ(14, graph.GetResultedGraph().size());
	ASSERT_STREQ("1", graph.GetResultedGraph().front().front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(1).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(2).front().c_str()) << "may also be 1";
	ASSERT_STREQ("5", graph.GetResultedGraph().at(3).front().c_str()) << "may also be 2";
	ASSERT_STREQ("3", graph.GetResultedGraph().at(4).front().c_str()) << "may also be 1";
	ASSERT_STREQ("5", graph.GetResultedGraph().at(5).front().c_str()) << "may also be 2";
	ASSERT_STREQ("3", graph.GetResultedGraph().at(6).front().c_str()) << "may also be 1";
	ASSERT_STREQ("2", graph.GetResultedGraph().at(7).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(8).front().c_str()) << "may also be 3";
//	ASSERT_STREQ("4", graph.GetResultedGraph().at(9).front().c_str()) << "may also be 2";
	ASSERT_STREQ("2", graph.GetResultedGraph().at(10).front().c_str()) << "may also be 1";
	ASSERT_STREQ("1", graph.GetResultedGraph().at(11).front().c_str()) << "may also be 2";
	ASSERT_STREQ("2", graph.GetResultedGraph().at(12).front().c_str()) << "may also be 3";
	ASSERT_STREQ("1", graph.GetResultedGraph().back().front().c_str()) << "may also be 2";
}

TEST_F(NodesLinker_F, InterleavedTriad)	// Figure 4.4
{
	NodesLinker graph;
	graph.LinkNewNodes({ SI_B_1 });
	graph.LinkNewNodes({ SO_1 });
	graph.LinkNewNodes({ MI_B_1 });
	graph.LinkNewNodes({ LA_B_1 });
	graph.LinkNewNodes({ FA_1 });
	graph.LinkNewNodes({ RE_B_1 });
	graph.LinkNewNodes({ DO_1, MI_B_1, SO_1 });
	graph.LinkNewNodes({ LA_B });
	graph.LinkNewNodes({ DO_1 });
	graph.LinkNewNodes({ RE_B_1 });
	graph.LinkNewNodes({ MI_B_1 });
	graph.LinkNewNodes({ RE_B_1 });
	graph.LinkNewNodes({ DO_1 });
	graph.RemoveExpensivePaths();
	ASSERT_EQ(13, graph.GetResultedGraph().size());
	ASSERT_STREQ("4", graph.GetResultedGraph().front().front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(1).front().c_str());
	ASSERT_STREQ("1", graph.GetResultedGraph().at(2).front().c_str());
//	ASSERT_STREQ("2", graph.GetResultedGraph().at(3).front().c_str());
//	ASSERT_STREQ("1", graph.GetResultedGraph().at(4).front().c_str());
//	ASSERT_STREQ("2", graph.GetResultedGraph().at(5).front().c_str());

//	ASSERT_STREQ("1", graph.GetResultedGraph().at(6).front().c_str());
//	ASSERT_STREQ("2", graph.GetResultedGraph().at(6).at(1).c_str());
//	ASSERT_STREQ("4", graph.GetResultedGraph().at(6).back().c_str());

	ASSERT_STREQ("1", graph.GetResultedGraph().at(7).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().at(8).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(9).front().c_str());
	ASSERT_STREQ("4", graph.GetResultedGraph().at(10).front().c_str());
	ASSERT_STREQ("3", graph.GetResultedGraph().at(11).front().c_str());
	ASSERT_STREQ("2", graph.GetResultedGraph().back().front().c_str());
}