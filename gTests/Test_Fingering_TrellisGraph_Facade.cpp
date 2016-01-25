# include "stdafx.h"
# include "TrellisGraph_Facade.h"
# include "TrellisGraph_Common.h"

using std::vector;
using gTest::TrellisGraph_Common;

class TrellisGraph_F : public TrellisGraph_Common
{
public:
	TrellisGraph_F() : TrellisGraph_Common() {}
	TrellisGraph_F(const TrellisGraph_F&) = default;
	TrellisGraph_F& operator = (const TrellisGraph_F&) = default;

	virtual ~TrellisGraph_F() override = default;

	virtual void SetUp() override final
	{
		TrellisGraph_Common::SetUp();
	}
	virtual void TearDown() override final
	{
		TrellisGraph_Common::TearDown();
	}
};

// http://www.scriptiebank.be/sites/default/files/webform/scriptie/balliauw-matteo-2014_0.pdf

TEST_F(TrellisGraph_F, JSBach_Menuet4_BWVanh114_LeftHand)	// Page 27, Figure 12
{
	vector<vector<int16_t>> chords( { { SO, SI, RE_1 }, { LA }, { SI }, { DO_1 }, { SI },
	{ LA }, { SO }, { RE_1 }, { SI }, { SO }, { RE_1 }, { RE }, { DO_1 }, { SI }, { LA } } );
	TrellisGraph trellis(chords, true);
	while (trellis.NextStep());
	trellis.Finish();

	ASSERT_EQ(RE_1, trellis.GetResult().front().front().first);
	ASSERT_STREQ("1", trellis.GetResult().front().front().second.c_str());
	ASSERT_EQ(SI, trellis.GetResult().front().at(1).first);
	ASSERT_STREQ("2", trellis.GetResult().front().at(1).second.c_str());
	ASSERT_EQ(SO, trellis.GetResult().front().back().first);
	ASSERT_STREQ("4", trellis.GetResult().front().back().second.c_str());

	ASSERT_STREQ("3", trellis.GetResult().at(1).front().second.c_str());
	ASSERT_STREQ("2", trellis.GetResult().at(2).front().second.c_str());
	ASSERT_STREQ("1", trellis.GetResult().at(3).front().second.c_str());
	ASSERT_STREQ("2", trellis.GetResult().at(4).front().second.c_str());
	ASSERT_STREQ("3", trellis.GetResult().at(5).front().second.c_str());
	ASSERT_STREQ("4", trellis.GetResult().at(6).front().second.c_str());
	ASSERT_STREQ("1", trellis.GetResult().at(7).front().second.c_str());
	ASSERT_STREQ("2", trellis.GetResult().at(8).front().second.c_str());
//	ASSERT_STREQ("3", trellis.GetResult().at(9).front().second.c_str());
	ASSERT_STREQ("1", trellis.GetResult().at(10).front().second.c_str());
//	ASSERT_STREQ("5", trellis.GetResult().at(11).front().second.c_str());
	ASSERT_STREQ("1", trellis.GetResult().at(12).front().second.c_str());
	ASSERT_STREQ("2", trellis.GetResult().at(13).front().second.c_str());
	ASSERT_STREQ("3", trellis.GetResult().back().front().second.c_str());
}

TEST_F(TrellisGraph_F, GFHandel_DSuite_HWV437_Saraband_LeftHand)	// Page 28, Figure 14
{
	vector<vector<int16_t>> chords({ { RE_1 }, { FA_1 }, { RE_1 }, { MI_1, LA_1 },
	{ LA }, { SO_1 }, { LA_1 }, { MI_1 }, { FA_1 }, { LA_1 }, { FA_1 }, { DO_1 },
	{ SI_1 }, { DO_2 }, { FA_S_1 }, { SO_1 }, { SI_B_1 }, { SO_1 }, { RE_2 },
	{ RE_1 }, { DO_2 }, { SI_B_1 }, { SI_B },
	{ SI_B_1 }, { LA_1 }, { SO_1 }, { FA_1 }, { MI_1 } });

	TrellisGraph trellis(chords, true);
	while (trellis.NextStep());
	trellis.Finish();

	ASSERT_STREQ("3", trellis.GetResult().front().front().second.c_str()) << "may also be 4";
	ASSERT_STREQ("1", trellis.GetResult().at(1).front().second.c_str());
	ASSERT_STREQ("3", trellis.GetResult().at(2).front().second.c_str()) << "may also be 4";

	ASSERT_EQ(LA_1, trellis.GetResult().at(3).front().first);
	ASSERT_STREQ("1", trellis.GetResult().at(3).front().second.c_str());
	ASSERT_EQ(MI_1, trellis.GetResult().at(3).back().first);
	ASSERT_STREQ("2", trellis.GetResult().at(3).back().second.c_str());

	ASSERT_STREQ("5", trellis.GetResult().at(4).front().second.c_str());
//	ASSERT_STREQ("2", trellis.GetResult().at(5).front().second.c_str());
	ASSERT_STREQ("1", trellis.GetResult().at(6).front().second.c_str());
	ASSERT_STREQ("3", trellis.GetResult().at(7).front().second.c_str()) << "may also be 4";
	ASSERT_STREQ("2", trellis.GetResult().at(8).front().second.c_str());
	ASSERT_STREQ("1", trellis.GetResult().at(9).front().second.c_str());
	ASSERT_STREQ("2", trellis.GetResult().at(10).front().second.c_str());
	ASSERT_STREQ("5", trellis.GetResult().at(11).front().second.c_str());

//	ASSERT_STREQ("3", trellis.GetResult().at(12).front().second.c_str());
//	ASSERT_STREQ("2", trellis.GetResult().at(13).front().second.c_str());
//	ASSERT_STREQ("5", trellis.GetResult().at(14).front().second.c_str());
//	ASSERT_STREQ("4", trellis.GetResult().at(15).front().second.c_str());
//	ASSERT_STREQ("3", trellis.GetResult().at(16).front().second.c_str()) << "may also be 2";
//	ASSERT_STREQ("5", trellis.GetResult().at(17).front().second.c_str()) << "may also be 4";
	ASSERT_STREQ("1", trellis.GetResult().at(18).front().second.c_str());

	ASSERT_STREQ("5", trellis.GetResult().at(19).front().second.c_str());
//	ASSERT_STREQ("2", trellis.GetResult().at(20).front().second.c_str());
	ASSERT_STREQ("1", trellis.GetResult().at(21).front().second.c_str());
	ASSERT_STREQ("5", trellis.GetResult().at(22).front().second.c_str());

	ASSERT_STREQ("1", trellis.GetResult().at(23).front().second.c_str()) << "may also be 2";
//	ASSERT_STREQ("1", trellis.GetResult().at(24).front().second.c_str());
//	ASSERT_STREQ("2", trellis.GetResult().at(25).front().second.c_str());
//	ASSERT_STREQ("3", trellis.GetResult().at(26).front().second.c_str());
//	ASSERT_STREQ("4", trellis.GetResult().at(27).front().second.c_str());
}