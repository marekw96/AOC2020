#include "Utils.hpp"
#include <fstream>

std::vector<std::string> Utils::read_lines(std::string_view file_name)
{
	std::vector<std::string> lines;
	std::ifstream file(file_name.data());
	
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			lines.push_back(line);
		}
	}

	return lines;
}
