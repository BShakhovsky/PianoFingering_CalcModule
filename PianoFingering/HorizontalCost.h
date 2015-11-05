# pragma once

class HorizontalCost abstract : private boost::noncopyable
{
	HorizontalCost() = delete;
	~HorizontalCost() = delete;
public:
	static double Calculate(std::vector<std::pair<int16_t, char>> chord1,
		std::vector<std::pair<int16_t, char>> chord2, std::vector<std::pair<int16_t, char>> chord3);
private:
	static int CalcSingles(std::vector<std::pair<int16_t, char>> chord);
	static double CalcPairs(
		std::vector<std::pair<int16_t, char>> chord1,
		std::vector<std::pair<int16_t, char>> chord2);
	static float CalcTriples(
		std::vector<std::pair<int16_t, char>> chord1,
		std::vector<std::pair<int16_t, char>> chord2,
		std::vector<std::pair<int16_t, char>> chord3);
};