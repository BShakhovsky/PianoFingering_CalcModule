# pragma once

class VerticalCost abstract : private boost::noncopyable
{
	VerticalCost() = delete;
	~VerticalCost() = delete;
public:
	static double Calculate(std::vector<std::pair<int16_t, char>> notes_fingers);
};