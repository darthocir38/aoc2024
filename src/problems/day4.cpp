#include "day4.h"

#include "../helper/point.h"
#include "../helper/parser.h"
#include <ranges>
#include <algorithm>
#include <map>

namespace adventofcode
{
Day4::Day4() : DaySolver(4) {
    // Data for tests
    test_data = R"(MMMSXXMASM
MSAMXMSMSA
AMXSXMAAMM
MSAMASMSMX
XMASAMXAMM
XXAMMXXAMA
SMSMSASXSS
SAXAMASAAA
MAMMMXMMMM
MXMXAXMASX)";
    test_results = { 18, 9 };
}

bool match_char(auto const& data, Point const& p, std::pair<char, Point> test)
{
	const auto [x, y] = p + test.second;
	return data[y][x] == test.first;
};

bool do_match_p1(auto const& data, Point const& p, const auto test_syms)
{
	if (auto P_s = p + test_syms.at('S'); not P_s.in_range(
		data[p.y].size() - 1,
		data.size() - 1)) { return false; }

	return std::ranges::all_of(test_syms, [&](auto const& test){return match_char(data, p,test);});
};

bool do_match_p2(auto const& data, Point const& p, const auto& offset)
{
	if (const auto P_max = p + Point(2, 2); not P_max.in_range(
		data[p.y].size() - 1,
		data.size() - 1)) { return false; }

	return std::ranges::all_of(offset, [&](auto const& test){return match_char(data, p,test);});
};

	using offset = std::map<char, Point>;
	using moffset = std::multimap<char, Point>;

	static const offset hor_f = { { 'X', { 0, 0 } }, { 'M', { 1, 0 } },
	                              { 'A', { 2, 0 } }, { 'S', { 3, 0 } } };
	static const offset hor_r = { { 'X', { 0, 0 } }, { 'M', { -1, 0 } },
	                              { 'A', { -2, 0 } }, { 'S', { -3, 0 } } };
	static const offset ver_d = { { 'X', { 0, 0 } }, { 'M', { 0, 1 } },
	                              { 'A', { 0, 2 } }, { 'S', { 0, 3 } } };
	static const offset ver_u = { { 'X', { 0, 0 } }, { 'M', { 0, -1 } },
	                              { 'A', { 0, -2 } }, { 'S', { 0, -3 } } };

	static const offset dia_fd = { { 'X', { 0, 0 } }, { 'M', { 1, 1 } },
	                               { 'A', { 2, 2 } }, { 'S', { 3, 3 } } };
	static const offset dia_fu = { { 'X', { 0, 0 } }, { 'M', { 1, -1 } },
	                               { 'A', { 2, -2 } }, { 'S', { 3, -3 } } };
	static const offset dia_rd = { { 'X', { 0, 0 } }, { 'M', { -1, 1 } },
	                               { 'A', { -2, 2 } }, { 'S', { -3, 3 } } };
	static const offset dia_ru = { { 'X', { 0, 0 } }, { 'M', { -1, -1 } },
	                               { 'A', { -2, -2 } },
	                               { 'S', { -3, -3 } } };

	static const moffset xmas1 = { { 'A', { 1, 1 } }, { 'M', { 0, 0 } },
	                              { 'S', { 2, 2 } },
	                              { 'M', { 0, 2 } }, { 'S', { 2, 0 } } };
	static const moffset xmas2 = { { 'A', { 1, 1 } }, { 'M', { 0, 0 } },
	                              { 'S', { 2, 2 } },
	                              { 'M', { 2, 0 } }, { 'S', { 0, 2 } } };
	static const moffset xmas3 = { { 'A', { 1, 1 } }, { 'M', { 2, 2 } },
	                              { 'S', { 0, 0 } },
	                              { 'M', { 0, 2 } }, { 'S', { 2, 0 } } };
	static const moffset xmas4 = { { 'A', { 1, 1 } }, { 'M', { 2, 2 } },
	                              { 'S', { 0, 0 } },
	                              { 'M', { 2, 0 } }, { 'S', { 0, 2 } } };

	static const std::vector<offset> combinations_p1 = {
		hor_f, hor_r, ver_d, ver_u, dia_fd, dia_fu, dia_rd, dia_ru };
	static const std::vector<moffset> combinations_p2 = {
		xmas1, xmas2, xmas3, xmas4 };
long Day4::solvePart1() {
	const auto content    =split(input_data, '\n');

    int result_p1 = 0;
	for (auto y = 0; y < content.size(); y++)
	{
		for (auto x = 0; x < content[y].size(); x++)
		{
			for (const auto& off : combinations_p1)
			{
				if (do_match_p1(content, { x, y }, off)) { result_p1++; }
			}
		}
	}
    return result_p1;
}

long Day4::solvePart2() {
	const auto content    =split(input_data, '\n');
	int result_p2 = 0;

	for (auto y = 0; y < content.size(); y++)
	{
		for (auto x = 0; x < content[y].size(); x++)
		{
			for (const auto& off : combinations_p2)
			{
				if (do_match_p2(content, { x, y }, off)) { result_p2++; }
			}
		}
	}
    return result_p2;
}

}
