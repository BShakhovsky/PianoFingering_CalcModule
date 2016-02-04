# include "stdafx.h"
# include "CostRules.h"
# include "DistanceTable.h"
# include "BlackWhiteKeys.h"

using std::pair;

int CostRules::Rule1_StretchComf(const pair<int16_t, char>& note1, const pair<int16_t, char>& note2)
// Python-profiler bottle-neck
{
	if (note1.second == note2.second) return NULL;
	const auto distance(note1.second < note2.second ? note2.first - note1.first : note1.first - note2.first);

	// Slightly optimized:
	const auto maxLimit(DistanceTable::MaxComf(note1.second, note2.second));
	if (distance > maxLimit) return (distance - maxLimit) * 2;
	else
	{
		const auto minLimit(DistanceTable::MinComf(note1.second, note2.second));
		return distance < minLimit ? (minLimit - distance) * 2 : NULL;
	}
}
int CostRules::Rule2_SpanRel(const pair<int16_t, char>& note1, const pair<int16_t, char>& note2)
{
	if (note1.second == note2.second) return NULL;
	const auto distance(note1.second < note2.second ? note2.first - note1.first : note1.first - note2.first);

	// Slightly optimized:
	const auto maxLimit(DistanceTable::MaxRel(note1.second, note2.second));
	if (distance > maxLimit) return (distance - maxLimit) * (1 == note1.second || 1 == note2.second ? 1 : 2);
	else
	{
		const auto minLimit(DistanceTable::MinRel(note1.second, note2.second));
		return distance < minLimit ? (minLimit - distance) * (1 == note1.second || 1 == note2.second ? 1 : 2) : NULL;
	}
}

// not covered by unit tests:
int CostRules::Rule3_PositionChange(const pair<int16_t, char>& note1, const pair<int16_t, char>& note2,
	const pair<int16_t, char>& note3)	// Python-profiler bottle-neck
{
//	auto result(Rule4_PositionSize(note1, note3));
	// instead copy from Rule 1:
	auto result(NULL);
	auto distance(note3.first - note1.first);
	if (//note1.second == note2.second || note2.second == note3.second ||
		note3.second == note1.second)									return NULL;
	else if (note1.second > note3.second)								distance *= -1;

	const auto maxLimit(DistanceTable::MaxComf(note1.second, note3.second));
	if (distance > maxLimit) result = (distance - maxLimit);
	else
	{
		const auto minLimit(DistanceTable::MinComf(note1.second, note3.second));
		result = distance < minLimit ? (minLimit - distance) : NULL;
	}

	if (result) ++result;	// half-change
	if (1 == note2.second && (
		distance < DistanceTable::MinPrac(note1.second, note3.second) ||
		distance > DistanceTable::MaxPrac(note1.second, note3.second)
		) && (note1.first < note2.first && note2.first < note3.first ||
			note1.first > note2.first && note2.first > note3.first))	++result;	// full-change
	if (note1.first == note3.first /*&& note1.second != note3.second*/)	++result;

	return result;
}

char CostRules::Rule5_WeakFinger(const char finger)
{
	switch (finger)
	{
	case 1:	case 2:	case 3: return NULL;	break;
	case 4:	case 5:			return 1;		break;
	default: assert(!"WRONG FINGER NUMBER"); return NULL;
	}
}
char CostRules::Rule6_ThreeFourFive(const char finger1, const char finger2, const char finger3)
{
	if		(3 == finger1 && 4 == finger2 && 5 == finger3)	return 1;
	else if (3 == finger1 && 5 == finger2 && 4 == finger3)	return 1;
	else if (4 == finger1 && 5 == finger2 && 3 == finger3)	return 1;
	else if (4 == finger1 && 3 == finger2 && 5 == finger3)	return 1;
	else if (5 == finger1 && 3 == finger2 && 4 == finger3)	return 1;
	else if (5 == finger1 && 4 == finger2 && 3 == finger3)	return 1;
	else													return NULL;
}
char CostRules::Rule7_ThreeFour(const char finger1, const char finger2)
{
	if		(3 == finger1 && 4 == finger2)	return 1;
	else if (4 == finger1 && 3 == finger2)	return 1;
	else									return NULL;
}

char CostRules::Rule8_FourOnBlack(const pair<int16_t, char>& note1, const pair<int16_t, char>& note2)
{
	if		(3 == note1.second && 4 == note2.second
		&& BlackWhiteKeys::IsWhite(note1.first) && BlackWhiteKeys::IsBlack(note2.first))	return 1;
	else if (4 == note1.second && 3 == note2.second
		&& BlackWhiteKeys::IsBlack(note1.first) && BlackWhiteKeys::IsWhite(note2.first))	return 1;
	else																					return NULL;
}
float CostRules::Rule9_ThumbOnBlack(const pair<int16_t, char>& note1, const pair<int16_t, char>& note2)
{
	auto result(0.f);

	if (1 == note1.second && BlackWhiteKeys::IsBlack(note1.first))
	{
		result += 0.5;
		if (1 != note2.second && BlackWhiteKeys::IsWhite(note2.first))
			++result;
	}
	else if (1 == note2.second && BlackWhiteKeys::IsBlack(note2.first))
	{
		result += 0.5;
		if (1 != note1.second && BlackWhiteKeys::IsWhite(note1.first))
			++result;
	}

	return result;
}
char CostRules::Rule10_PinkyOnBlack(const pair<int16_t, char>& note1, const pair<int16_t, char>& note2)
{
	if		(5 == note1.second && BlackWhiteKeys::IsBlack(note1.first)
		&& 5 != note2.second && BlackWhiteKeys::IsWhite(note2.first))	return 1;
	else if (5 == note2.second && BlackWhiteKeys::IsBlack(note2.first)
		&& 5 != note1.second && BlackWhiteKeys::IsWhite(note1.first))	return 1;
	else																return NULL;
}

char CostRules::Rule11_ThumbPassing(const pair<int16_t, char>& note1, const pair<int16_t, char>& note2)
{
	auto distance(note2.first - note1.first);
	if 		(note1.second == note2.second)	return NULL;
	else if (note1.second > note2.second)	distance *= -1;

	if (distance < 0 && (1 == note1.second || 1 == note2.second) &&
		BlackWhiteKeys::IsBlack(note1.first) == BlackWhiteKeys::IsBlack(note2.first))	return 1;
	else																				return NULL;
}
char CostRules::Rule12_ThumbCross_Black(const pair<int16_t, char>& note1, const pair<int16_t, char>& note2)
{
	auto distance(note2.first - note1.first);
	if (note1.second == note2.second)		return NULL;
	else if (note1.second > note2.second)	distance *= -1;

	if (distance < 0)
		if		(1 == note1.second && BlackWhiteKeys::IsBlack(note1.first)
			&& BlackWhiteKeys::IsWhite(note2.first))	return 2;
		else if (1 == note2.second && BlackWhiteKeys::IsWhite(note1.first)
			&& BlackWhiteKeys::IsBlack(note2.first))	return 2;
		else											return NULL;
	else												return NULL;
}

char CostRules::Rule13_ThreeSameFinger(const pair<int16_t, char>& note1, const pair<int16_t, char>& note2,
	const pair<int16_t, char>& note3)
{
	if (note1.second == note3.second && (
		note1.first < note2.first && note2.first < note3.first ||
		note1.first > note2.first && note2.first > note3.first))	return 1;
	else															return NULL;
}

int CostRules::Rule14_MaxPractical(const pair<int16_t, char>& note1, const pair<int16_t, char>& note2)
{
	if (note1.second == note2.second) return NULL;
	const auto distance(note1.second < note2.second ? note2.first - note1.first : note1.first - note2.first);

	// Slightly optimized:
	const auto maxLimit(DistanceTable::MaxPrac(note1.second, note2.second));
	if (distance > maxLimit) return (distance - maxLimit) * 10;
	else
	{
		const auto minLimit(DistanceTable::MinPrac(note1.second, note2.second));
		return distance < minLimit ? (minLimit - distance) * 10 : NULL;
	}
}
char CostRules::Rule15_SameNote(const pair<int16_t, char>& note1, const pair<int16_t, char>& note2)
{
	if (note1.first == note2.first && note1.second != note2.second)	return 1;
	else															return NULL;
}

// my own rule, not tested:
char CostRules::Rule16_SameFinger(const pair<int16_t, char>& note1, const pair<int16_t, char>& note2)
{
	if (note1.first != note2.first && note1.second == note2.second)	return static_cast<char>(11);
		/* ******************************************************
		 * Cost of thumb-pinky with max practical interval of 15:
		 * Rule 1 = (15 - 10) * 1 = 5
		 * Rule 2 = (15 - 13) * 2 = 2 * 2 = 4
		 * Rule 9 (thumb on black) = 1.5 max
		 * 5 + 4 + 1.5 = 10.5 total
		 *
		 * Rule same finger gives more than 10.5 ==> 11
		 * *****************************************************/
	else															return NULL;
}