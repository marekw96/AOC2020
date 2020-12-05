#include "Utils.hpp"

#include <algorithm>
#include <string>
#include <iostream>
#include <optional>
#include <utility>

std::optional<std::pair<int,int>> find_that_sums_to(const std::vector<int>& items, int sumto)
{
	for (auto item : items)
	{
		auto rest = sumto - item;
		if (std::binary_search(items.begin(), items.end(), rest))
		{
			return std::pair<int,int>{ item, rest };
			break;
		}
	}

	return std::nullopt;
}

int main()
{
	constexpr auto year = 2020;

	auto lines = Utils::read_lines("input.txt");
	std::vector<int> items(lines.size());
	std::transform(lines.begin(), lines.end(), items.begin(), [](const auto& i) { return std::stoi(i); });

	std::sort(items.begin(), items.end());

	auto element = find_that_sums_to(items, year);
	
	if (element)
		std::cout << "Result is: " << (element->first * element->second) << std::endl;
	else
		std::cout << "You idiot." << std::endl;

	for (auto item : items)
	{
		auto rest = year - item;

		auto el = find_that_sums_to(items, rest);
		if (el)
		{
			//std::cout << item << " " << el->first << " " << el->second << std::endl;
			std::cout << "Second result is: " <<  item * el->first * el->second << std::endl;
			break;
		}
	}

	return 0;
}