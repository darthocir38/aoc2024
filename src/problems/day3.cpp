#include "day3.h"
#include <regex>
#include <ranges>

namespace adventofcode
{
Day3::Day3() : DaySolver(3) {
    // Data for tests
    test_data = R"(xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5)))";
    test_results = { 161, 48 };
}

ResultType Day3::solvePart1() {
    int sum = 0;
    static const std::regex p1("mul\\(([0-9]{1,3})"
                               ","
                               "([0-9]{1,3})\\)");

	for (const auto word : std::views::split(input_data, '\n'))
	{
		std::string str{ word.data() };
        for (std::smatch sm; regex_search(str, sm, p1);) {
            sum += stoi(sm[1].str()) * stoi(sm[2].str());
            str = sm.suffix();
        }
    }
    return sum;
}

ResultType Day3::solvePart2() {
	static const std::regex p2(
		"(do\\(\\)|don't\\(\\))|mul\\(([0-9]{1,3}),([0-9]{1,3})\\)");
    bool enabled = true;
    int sum = 0;
	for (const auto word : std::views::split(input_data, '\n'))
	{
		std::string str{ word.data() };
	    for (std::smatch sm; regex_search(str, sm, p2);)
	    {
	        if (auto const& sm0 = sm[0].str(); sm0.starts_with("do()"))
	        {
	            enabled = true;
	        }
	        else if (sm0.starts_with("don't()")) { enabled = false; }
	        else { if (enabled) { sum += stoi(sm[2].str()) * stoi(sm[3].str()); } }
	        str = sm.suffix();
	    }
	}
	return sum;
}

}
