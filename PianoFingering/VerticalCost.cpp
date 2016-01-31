# include "stdafx.h"
# include "VerticalCost.h"
# include "PolyCosts.h"

using namespace std;

// only asserts are tested:
double VerticalCost::Calculate(const vector<pair<int16_t, char>>& notes_fingers)
{
	assert("NUMBER OF NOTES IN A CHORD MUST BE BETWEEN TWO AND FIVE"
		&& notes_fingers.size() >= 2 && notes_fingers.size() <= 5);

	assert("NOTES SHOULD BE SORTED IN ASCENDING ORDER BEFORE CHORD COST CALCULATION"
		&& is_sorted(notes_fingers.cbegin(), notes_fingers.cend(),
			[](const pair<int16_t, char>& lhs, const pair<int16_t, char>& rhs)
			{
				return lhs.first < rhs.first;
			}));
	assert("ALL NOTES IN A CHORD MUST BE DIFFERENT"
		&& adjacent_find(notes_fingers.cbegin(), notes_fingers.cend(),
			[](const pair<int16_t, char>& lhs, const pair<int16_t, char>& rhs)
			{
				return lhs.first == rhs.first;
			}
		) == notes_fingers.cend());


	auto result(PolyCosts().CostOfPair(notes_fingers.at(0), notes_fingers.at(1)));
	if (notes_fingers.size() >= 3) result += PolyCosts().CostOfPair(notes_fingers.at(1), notes_fingers.at(2));
	if (notes_fingers.size() >= 4) result += PolyCosts().CostOfPair(notes_fingers.at(2), notes_fingers.at(3));
	if (notes_fingers.size() == 5) result += PolyCosts().CostOfPair(notes_fingers.at(3), notes_fingers.at(4));


	const auto SameFinger([](const pair<int16_t, char>& lhs, const pair<int16_t, char>& rhs)
	{
		return lhs.second == rhs.second;
	});
	assert("ALL FINGERS IN A CHORD MUST BE DIFFERENT"
		&& adjacent_find(notes_fingers.cbegin(), notes_fingers.cend(), SameFinger)
			== notes_fingers.cend());

	const auto FingersSort([](const pair<int16_t, char>& lhs, const pair<int16_t, char>& rhs)
	{
		return lhs.second < rhs.second;
	});
	const auto IsThumb([](const pair<int16_t, char>& note)
	{
		return 1 == note.second;
	});
	assert("THERE IS ONLY ONE THUMB IN A NORMAL HAND"
		&& count_if(notes_fingers.cbegin(), notes_fingers.cend(), IsThumb) <= 1);

	const auto thumb(find_if(notes_fingers.cbegin(), notes_fingers.cend(), IsThumb));
	if (thumb != notes_fingers.cbegin() && thumb != notes_fingers.cend())
	{
#ifdef _DEBUG
		auto temp(notes_fingers);
		const auto tempEnd(remove_if(temp.begin(), temp.end(), IsThumb));
		assert("ONLY THUMB PASSING IS ALLOWED BY CURRENT ALGORITHM"
			&& is_sorted(temp.begin(), tempEnd, FingersSort));
		assert("ALL FINGERS IN A CHORD MUST BE DIFFERENT"
			&& adjacent_find(temp.begin(), tempEnd, SameFinger) == tempEnd);
#endif
		for (auto iter(notes_fingers.cbegin()); iter != thumb - 1; ++iter)
			result += PolyCosts().CostOfPair(*iter, *thumb);
		if (thumb != notes_fingers.cend() - 1)
			result += PolyCosts().CostOfPair(*(thumb - 1), *(thumb + 1));
	}
	else
	{
		assert("ONLY THUMB PASSING IS ALLOWED BY CURRENT ALGORITHM"
			&& is_sorted(notes_fingers.cbegin(), notes_fingers.cend(), FingersSort));
	}

	return result;
}