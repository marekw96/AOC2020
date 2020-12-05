#include "Utils.hpp"

#include <iostream>
#include <string_view>
#include <charconv>

int count_valid_passports(const std::vector<std::string>& lines)
{
	int valid = 0;

	int current_passport_counts = 0;
	auto fields = { "byr:", "iyr:", "eyr:", "hgt:", "hcl:", "ecl:", "pid:" };

	for (const auto& line : lines)
	{
		if (line.empty())
		{
			if (current_passport_counts == 7)
			{
				++valid;
			}
			current_passport_counts = 0;
		}
		else
		{
			for (auto field : fields)
			{
				if (line.find(field) != std::string::npos)
					++current_passport_counts;
			}
		}
	}

	return valid;
}

bool validate_4digits(std::string_view value, int min, int max)
{
	if (value.size() != 4)
		return false;

	std::string str(value);
	try {
		int year = std::stoi(str);
		return (year >= min && year <= max);
	}
	catch (...)
	{
		return false;
	}
}

bool validate_hgt(std::string_view value)
{
	std::string str(value.begin(), value.begin() + value.size() - 2);
	try {
		int size = std::stoi(str);
		if (value.find("cm") != std::string_view::npos)
		{
			return (size >= 150 && size <= 193);
		}
		else
		{
			return (size >= 59 && size <= 76);
		}
	}
	catch (...)
	{
		return false;
	}
}

bool validate_hcl(std::string_view value)
{
	if (value[0] != '#')
		return false;

	if (value.size() != 7)
		return false;

	auto allowed = std::string("0123456789abcdef");

	for (int i = 1; i < value.size(); ++i)
	{
		if (allowed.find(value[i]) == std::string::npos)
		{
			return false;
		}
	}

	return true;
}

bool validate_ecl(std::string_view value)
{
	auto corrects = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };

	return std::find(corrects.begin(), corrects.end(), value) != corrects.end();
}

bool validate_pid(std::string_view value)
{
	if (value.size() != 9)
		return false;

	for (auto letter : value)
	{
		if (letter < '0' || letter > '9')
			return false;
	}

	return true;
}

int cound_passports_with_valid_field(const std::vector<std::string>& lines)
{
	int valid = 0;
	int current_passport_valid_fields = 0;

	for (const auto& line : lines)
	{
		if (line.empty())
		{
			if (current_passport_valid_fields == 7)
			{
				++valid;
			}
			current_passport_valid_fields = 0;
		}
		else
		{
			auto split_pos = 0;
			while ((split_pos = line.find_first_of(':', split_pos + 1)) != std::string::npos)
			{
				auto name = std::string_view(line.data() + split_pos - 3, 3);
				auto end_of_value = line.find_first_of(' ', split_pos + 1);
				if (end_of_value == std::string::npos)
					end_of_value = line.size();

				auto value = std::string_view(line.data() + split_pos + 1, end_of_value - split_pos -1);

				//std::cout << name << "-" << value << "_" << current_passport_valid_fields;
				
				if (name == "byr")
					current_passport_valid_fields += validate_4digits(value, 1920, 2002);
				else if (name == "iyr")
					current_passport_valid_fields += validate_4digits(value, 2010, 2020);
				else if (name == "eyr")
					current_passport_valid_fields += validate_4digits(value, 2020, 2030);
				else if (name == "hgt")
					current_passport_valid_fields += validate_hgt(value); 
				else if (name == "hcl")
					current_passport_valid_fields += validate_hcl(value);
				else if (name == "ecl")
					current_passport_valid_fields += validate_ecl(value);
				else if (name == "pid")
					current_passport_valid_fields += validate_pid(value);

				//std::cout << " -> " << current_passport_valid_fields << std::endl;
			}
		}
	}

	return valid;
}


int main()
{
	auto lines = Utils::read_lines("input.txt");


	std::cout << "Valid [part1]: " << count_valid_passports(lines) << std::endl;;
	std::cout << "Valid [part2]: " << cound_passports_with_valid_field(lines) << std::endl;


	return 1;
}