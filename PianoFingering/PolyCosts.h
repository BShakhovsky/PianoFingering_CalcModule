# pragma once
# include "ICostsCalculator.h"

class PolyCosts : public ICostsCalculator
{
public:
	PolyCosts() = default;
	virtual ~PolyCosts() override final = default;

	virtual int CostOfSingle(char) const override final
	{
		assert(!"COST OF SINGLE NOTE IS NO USE FOR POLYPHONIC CHORD");
		return NULL;
	}

	virtual double CostOfPair(std::pair<int16_t, char> note1,
		std::pair<int16_t, char> note2) const override final;

	virtual int CostOfThree(std::pair<int16_t, char>, std::pair<int16_t, char>,
		std::pair<int16_t, char>) const override final
	{
		assert(!"COST OF THREE NOTES IS FOR SOME REASON NOT APPLICABLE"
			&& !"FOR POLYPHONIC CHORD ACCORDING TO CURRENT ALGORITHM");
		return NULL;
	}
};