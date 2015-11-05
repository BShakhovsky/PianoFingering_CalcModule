# pragma once
# include "ICostsCalculator.h"

class MonoCosts : public ICostsCalculator
{
public:
	MonoCosts() = default;
	virtual ~MonoCosts() override final = default;

	virtual int CostOfSingle(char finger) const override final;
	virtual double CostOfPair(
		std::pair<int16_t, char> note1,
		std::pair<int16_t, char> note2) const override final;
	virtual int CostOfThree(
		std::pair<int16_t, char> note1,
		std::pair<int16_t, char> note2,
		std::pair<int16_t, char> note3) const override final;
};