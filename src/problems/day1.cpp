#include "day1.h"

#include "../helper/parser.h"
#include "../helper/converter.h"

#include <ranges>
#include <algorithm>

namespace adventofcode
{
Day1::Day1() : DaySolver(1) {
    // Data for tests
    test_data = R"(3   4
4   3
2   5
1   3
3   9
3   3)";
    test_results = { 11, 31 };
}

ResultType Day1::solvePart1() {

    const auto lines = split(input_data, '\n');
    const auto cols = by_column(split(lines, ' '));

    auto cols_int = convert<int>(cols);

    for (auto& col : cols_int) {
        std::ranges::sort(col);
    }

    int distance = 0;
    for (std::tuple<int&, int&> elem : std::views::zip(cols_int[0], cols_int[1])) {
        distance += std::abs(std::get<1>(elem) - std::get<0>(elem));
    }
    return distance;
}

ResultType Day1::solvePart2() {
	const auto lines    =split(input_data, '\n');
    const auto cols      = by_column(split(lines, ' '));

	auto cols_int = convert<int>(cols);

	for (auto& col : cols_int) { std::ranges::sort(col); }

    int similarity = 0;
	for (auto i : cols_int[0])
	{
		const auto cnt = std::ranges::count(cols_int[1], i);
		similarity += i * cnt;
	}
    return similarity;
}

}
