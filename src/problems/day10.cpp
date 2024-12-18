#include "day10.h"
#include "../helper/parser.h"
#include "../helper/point.h"
#include "../helper/converter.h"
#include "../helper/helper.h"

namespace adventofcode
{
Day10::Day10() : DaySolver(10) {
    // Data for tests
    test_data = R"(89010123
78121874
87430965
96549874
45678903
32019012
01329801
10456732)";
    test_results = { 36, 81 };
}

auto neighbors = std::vector<Point>{{ 0, -1 },{ 1, 0 },{ 0, 1 },{-1, 0 }};

std::vector<Point> find_paths(auto const& heights, Point const& curr)
{
	auto height = heights[curr.y][curr.x];
	if (height == 9)
	{
		return {curr};
	}

	std::vector<Point> found;
	for (auto n : neighbors)
	{
		auto next_p = curr + n;
		if (not next_p.in_range(heights[0].size()-1, heights.size()-1)) continue;
		auto nheight = heights[next_p.y][next_p.x];
		if (nheight == height+1)
		{
			auto bla = find_paths(heights, next_p);
			for (auto p : bla) add_to(found, p);
		}
	}

	return found;
}


int find_paths_p2(auto const& heights, Point const& curr) {
    auto height = heights[curr.y][curr.x];
    if (height == 9) {
        return 1;
    }

    int found = 0;
    for (auto n : neighbors) {
        auto next_p = curr + n;
        if (not next_p.in_range(heights[0].size() - 1, heights.size() - 1))
            continue;
        auto nheight = heights[next_p.y][next_p.x];
        if (nheight == height + 1) {
            found += find_paths_p2(heights, next_p);
        }
    }

    return found;
}

ResultType Day10::solvePart1() {
    const auto content = split(input_data, '\n');
    auto heights = split_by_char<int>(content);

    int result = 0;
    for (auto y = 0; y < heights.size(); y++)
        for (auto x = 0; x < heights[y].size(); x++) {
            auto height = heights[y][x];
            if (height == 0) {
                auto start = Point(x, y);
                auto paths = find_paths(heights, start);
                // std::println("start at {},{} -> {}", x,y, paths.size());
                result += paths.size();
            }
        }

    return result;
}

ResultType Day10::solvePart2() {
	const auto content    =split(input_data, '\n');
	auto heights = split_by_char<int>(content);

    int result = 0;
	for (auto y = 0; y < heights.size(); y++)
		for (auto x = 0; x < heights[y].size(); x++)
		{
			auto height = heights[y][x];
			if (height == 0)
			{
				auto start = Point(x, y);
				result += find_paths_p2(heights, start);
			}
		}

    return result;
}

}

/*






TEST_CASE("Day10")
{
	auto tcontent = read("../days/10/tinput");
	auto content = read("../days/10/input");


	std::println("{}", heights.size());

	int result = 0;
	int result_p2 = 0;
	for (auto y = 0; y < heights.size(); y++)
		for (auto x = 0; x < heights[y].size(); x++)
		{
			auto height = heights[y][x];
			if (height == 0)
			{
				auto start = Point(x, y);
				auto paths = find_paths(heights, start);
				//std::println("start at {},{} -> {}", x,y, paths.size());
				result += paths.size();
				result_p2 += find_paths_p2(heights, start);
			}
		}



	std::println("P1: {}", result);
	std::println("P2: {}", result_p2);
	/*REQUIRE(result == 6519155389266);
	REQUIRE(antinodes_p2.size() == 949);
}
	 */
