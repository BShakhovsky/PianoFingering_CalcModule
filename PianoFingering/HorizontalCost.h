# pragma once

class HorizontalCost abstract : private boost::noncopyable
{
	HorizontalCost() = delete;
	~HorizontalCost() = delete;
public:
	static double Calculate(
		const std::vector<std::pair<int16_t, char>>& chord1,
		const std::vector<std::pair<int16_t, char>>& chord2,
		const std::vector<std::pair<int16_t, char>>& chord3);
private:
	static int CalcSingles(const std::vector<std::pair<int16_t, char>>& chord);
	static double CalcPairs(
		const std::vector<std::pair<int16_t, char>>& chord1,
		const std::vector<std::pair<int16_t, char>>& chord2);
	static float CalcTriples(
		const std::vector<std::pair<int16_t, char>>& chord1,
		const std::vector<std::pair<int16_t, char>>& chord2,
		const std::vector<std::pair<int16_t, char>>& chord3);
};