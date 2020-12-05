#include "Utils.hpp"

#include <vector>
#include <iostream>
#include <numeric>

int trees_in_slope(const std::vector<std::string>& slopes, int start_at_y, int start_at_x)
{
	constexpr auto TREE = '#';
	int size = slopes[0].size();
	int x_pos = start_at_x;
	int trees = 0;
	for (int y = start_at_y; y < slopes.size(); y += start_at_y)
	{
		const auto& line = slopes[y];
		if (line[x_pos] == TREE)
			++trees;

		x_pos = (x_pos + start_at_x) % size;
	}

	return trees;
}

int main()
{
	auto lines = Utils::read_lines("input.txt");

	auto trees = trees_in_slope(lines, 1, 3);
	std::cout << "Trees: " << trees << std::endl;


	auto trees_in_every_slope = {
		trees_in_slope(lines, 1, 1),
		trees_in_slope(lines, 1, 3),
		trees_in_slope(lines, 1, 5),
		trees_in_slope(lines, 1, 7),
		trees_in_slope(lines, 2, 1)
	};

	auto multiply_of_trees = std::accumulate(trees_in_every_slope.begin(), trees_in_every_slope.end(), 1, std::multiplies<int>());

	std::cout << "Trees [part 2]: " << multiply_of_trees;

	return 1;
}