# pragma once
# include "ICostsCalculator.h"

class MonoCosts : public ICostsCalculator
{
public:
	MonoCosts() = default;
	virtual ~MonoCosts() override final = default;

	virtual int CostOfSingle(char finger) const override final;

	virtual double CostOfPair(
		const std::pair<int16_t, char>& note1,
		const std::pair<int16_t, char>& note2) const override final;
	virtual double CostOfPair_modified(
		const std::pair<int16_t, char>& note1,
		const std::pair<int16_t, char>& note2) const;

	virtual int CostOfThree(
		const std::pair<int16_t, char>& note1,
		const std::pair<int16_t, char>& note2,
		const std::pair<int16_t, char>& note3) const override final;
};