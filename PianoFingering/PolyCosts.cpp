# include "stdafx.h"
# include "PolyCosts.h"
# include "CostRules.h"

using std::pair;

double PolyCosts::CostOfPair(const pair<int16_t, char>& note1, const pair<int16_t, char>& note2) const
{
	return CostRules::Rule1_StretchComf(note1, note2) * 2.0
		+ CostRules::Rule2_SpanRel(note1, note2) * 2.0
		+ CostRules::Rule14_MaxPractical(note1, note2);
}