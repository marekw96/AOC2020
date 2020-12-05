#include "Utils.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <iostream>

struct policy_pass
{
	int max;
	int min;
	char letter;
	std::string password;
};

policy_pass make_policy_and_pass(const std::string& line)
{
	policy_pass policy;

	std::sscanf(line.data(), "%d - %d %c", &policy.min, &policy.max, &policy.letter);
	auto pass_starts = line.find_first_of(':');
	policy.password = line.substr(pass_starts + 2);

	return policy;
}

int is_policy_ok(const policy_pass& policy)
{
	auto occurences = std::count(policy.password.begin(), policy.password.end(), policy.letter);

	return ((occurences <= policy.max) && (occurences >= policy.min));
}

int is_new_policy_ok(const policy_pass& policy)
{
	int first_check = policy.password[policy.min - 1] == policy.letter;
	int second_check = policy.password[policy.max - 1] == policy.letter;

	return (first_check + second_check) == 1;
}

int main()
{
	auto lines = Utils::read_lines("input.txt");
	std::vector<policy_pass> policies(lines.size());
	std::transform(lines.begin(), lines.end(), policies.begin(), make_policy_and_pass);

	auto correct = std::count_if(policies.begin(), policies.end(), is_policy_ok);
	std::cout << "Correct [part 1]: " << correct << std::endl;

	auto correct_2 = std::count_if(policies.begin(), policies.end(), is_new_policy_ok);
	std::cout << "Correct [part 2]: " << correct_2 << std::endl;

	return 0;
}