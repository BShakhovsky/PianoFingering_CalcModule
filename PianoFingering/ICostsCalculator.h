# pragma once

class ICostsCalculator abstract : private boost::noncopyable
{
public:
	virtual int CostOfSingle(char finger1) const = 0;
	virtual double CostOfPair(
		const std::pair<int16_t, char>& note1,
		const std::pair<int16_t, char>& note2) const = 0;
	virtual int CostOfThree(
		const std::pair<int16_t, char>& note1,
		const std::pair<int16_t, char>& note2,
		const std::pair<int16_t, char>& note3) const = 0;

	virtual ~ICostsCalculator() = 0 {}
protected:
	ICostsCalculator() = default;
};