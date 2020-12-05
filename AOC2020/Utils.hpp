#pragma once

#include <vector>
#include <string>
#include <string_view>

namespace Utils
{
	std::vector<std::string> read_lines(std::string_view file_name);
};

