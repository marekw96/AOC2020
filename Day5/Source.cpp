#include "Utils.hpp"
#include <iostream>
#include <algorithm>
#include <set>

int seatId(const std::string& line)
{
	int row = 0;
	int column = 0;


	for (int i = 0, row_add = 64; i < 7; ++i, row_add /= 2)
	{
		auto letter = line[i];
		if (letter == 'B')
			row += row_add;
	}
	
	for (int i = 7, column_add = 4; i < 10; ++i, column_add /= 2)
	{
		auto letter = line[i];
		if (letter == 'R')
			column += column_add;
	}

	int seat = row * 8 + column;

//	std::cout << "row " << row << " column " << column << " seat " << seat << std::endl;

	return seat;
}

int main()
{
	auto lines = Utils::read_lines("input.txt");

	std::set<int> seats;
	for (const auto& line : lines)
	{
		seats.emplace(seatId(line));
	}

	auto max = *std::max_element(seats.begin(), seats.end());
	std::cout << "Max seat [part1]: " << max << std::endl;

	int missing = 0;
	for (int i = 81; i < 855; ++i)
	{
		if (seats.find(i) == seats.end())
		{
			missing = i;
			break;
		}
	}

	std::cout << "Missing seat [part2]: " << missing << std::endl;

	return 1;
}