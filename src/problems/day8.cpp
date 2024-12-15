#include "day8.h"
#include "../helper/parser.h"
#include "../helper/helper.h"
#include "../helper/point.h"

#include <map>

namespace adventofcode
{
Day8::Day8() : DaySolver(8) {
    // Data for tests
    test_data = R"(............
........0...
.....0......
.......0....
....0.......
......A.....
............
............
........A...
.........A..
............
............)";
    test_results = { 14, 34 };
}

long Day8::solvePart1() {
	const auto content    =split(input_data, '\n');
	int x_max = content[0].size()-1;
	int y_max = content.size()-1;

	std::map<char, std::vector<Point> > antennas;

	auto add_point = [&](auto & vec, auto const& point) {
		if (not point.in_range(x_max,y_max))
		{
			return;
		}
		if (not contains (vec, point))
		{
			vec.push_back(point);
		}
	};
	auto build_notes_p1=[&](auto const& locations, auto& nodes) {
		for (auto i = 0, n = locations.size(); i < n-1; i++)
			for (auto j = i + 1; j < n; j++)
			{
				auto p1 = locations[i];
				auto p2 = locations[j];

				Point diff = p1 - p2;
				Point n1 = p1 + diff;
				add_point(nodes,n1);

				Point n2 = p2-diff;
				add_point(nodes,n2);
			}
	};
	for (auto y = 0; y < content.size(); y++)
	{
		for (auto x = 0; x < content[y].size(); x++)
		{
			auto sym = content[y][x];
			if (sym == '.') { continue; }
			antennas[sym].push_back({x, y});

		}
	}

	std::vector<Point> antinodes_p1,  antinodes_p2;
	for (auto val : antennas | std::views::values)
	{
		build_notes_p1(val,antinodes_p1);
	}
    return antinodes_p1.size();
}

long Day8::solvePart2() {
	const auto content    =split(input_data, '\n');
	int x_max = content[0].size()-1;
	int y_max = content.size()-1;

	std::map<char, std::vector<Point> > antennas;

	auto add_point = [&](auto & vec, auto const& point) {
		if (not point.in_range(x_max,y_max))
		{
			return;
		}
		if (not contains (vec, point))
		{
			vec.push_back(point);
		}
	};
	auto build_notes_p2=[&](auto const& locations,auto& nodes) {
		for (auto i = 0, n = locations.size(); i < n-1; i++)
			for (auto j = i + 1; j < n; j++)
			{
				auto p1 = locations[i];
				auto p2 = locations[j];
				add_point(nodes,p1 );
				add_point(nodes,p2 );

				Point diff = p1 - p2;
				Point n1 = p1 + diff;

				while (n1.in_range(x_max,y_max))
				{
					add_point(nodes,n1);
					n1 = n1 + diff;
				}

				Point n2 = p2-diff;
				while (n2.in_range(x_max,y_max))
				{
					add_point(nodes,n2);
					n2 = n2 - diff;
				}
			}
	};
	for (auto y = 0; y < content.size(); y++)
	{
		for (auto x = 0; x < content[y].size(); x++)
		{
			auto sym = content[y][x];
			if (sym == '.') { continue; }
			antennas[sym].push_back({x, y});

		}
	}

	std::vector<Point> antinodes_p1;
	for (auto val : antennas | std::views::values)
	{
		build_notes_p2(val,antinodes_p1);
	}
    return antinodes_p1.size();
    return 0;
}
/*
TEST_CASE("Day8")
{
	auto content = read("../days/8/input");





	std::println("P1: {}", antinodes_p1.size());
	REQUIRE(antinodes_p1.size() == 269);
	std::println("P2: {}", antinodes_p2.size());
	REQUIRE(antinodes_p2.size() == 949);
}
*/

}
