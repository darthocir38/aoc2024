#include "day6.h"
#include "../helper/parser.h"
#include "../helper/point.h"
#include "../helper/helper.h"

namespace adventofcode
{
Day6::Day6() : DaySolver(6) {
    // Data for tests
    test_data = R"(....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#.........
......#...)";
    test_results = { 41, 6 };
}

enum class DIR { UP, RIGHT, DOWN, LEFT };
Point guard;

constexpr Point offset_coord(const DIR dir)
{
	switch (dir)
	{
	case DIR::UP:
		return { 0, -1 };
	case DIR::RIGHT:
		return { 1, 0 };
	case DIR::DOWN:
		return { 0, 1 };
	case DIR::LEFT:
		return { -1, 0 };
	}
	return { 0, 0 };
}

constexpr auto next_direction(const DIR dir)
{
	switch (dir)
	{
	case DIR::UP:
		return DIR::RIGHT;
	case DIR::RIGHT:
		return DIR::DOWN;
	case DIR::DOWN:
		return DIR::LEFT;
	case DIR::LEFT:
		return DIR::UP;
	}
	return dir;
}

constexpr auto to_sym(DIR dir, char curr)
{
	if (curr == '+') return curr;
	switch (dir)
	{
	case DIR::DOWN:
	case DIR::UP:
		return curr == '-' ? '+' : '|';
	case DIR::RIGHT:
	case DIR::LEFT:
		return curr == '|' ? '+' : '-';
	}
	return ' ';
}

auto get_sym(Point const& p, std::vector<std::string> const& data)
{
	return data[p.y][p.x];
};

bool has_loop (const int x_max, const int y_max, Point g, DIR dir, const std::vector<std::string>& array) {
		std::vector<std::pair<Point, DIR> > visited;

		auto next_guard = g + offset_coord(dir);
		while (next_guard.in_range(x_max, y_max))
		{
			if (contains(visited, { next_guard, dir })) { return true; }

			auto const sym = get_sym(next_guard, array);

			if (sym == '#') { dir = next_direction(dir); }
			else
			{
				visited.emplace_back(next_guard, dir);
				g = next_guard;
			}
			next_guard = g + offset_coord(dir);
		}
		return false;
	};

std::pair<std::vector<Point>, std::vector<DIR>> path_and_dir(auto const& content) {

    Point guard = [&]() -> Point {
		for (auto y = 0; y < content.size(); y++)
		{
			for (auto x = 0; x < content[y].size(); x++)
			{
				if (content[y][x] == '^') { return { x, y }; }
			}
		}
		return { 0, 0 };
	}();
	const int x_max = content[0].size() - 1;
	const int y_max = content.size() - 1;

	auto dir = DIR::UP;
	std::vector<Point> path;
	std::vector<DIR> dirs;

	auto next_guard = guard + offset_coord(dir);
	while (next_guard.in_range(x_max, y_max))
	{
		auto const sym = get_sym(next_guard, content);
		if (sym == '#') { dir = next_direction(dir); }
		else
		{
			if (not contains(path, next_guard))
			{
				path.emplace_back(next_guard);
				dirs.emplace_back(dir);
			}
			guard = next_guard;
		}
		next_guard = guard + offset_coord(dir);
	}
    return {path, dirs};
}


long Day6::solvePart1() {
	const auto content    =split(input_data, '\n');
    return path_and_dir(content).first.size();
}

long Day6::solvePart2() {
	auto content    =split(input_data, '\n');
    auto const& [path, dirs] = path_and_dir(content);
	const int x_max = content[0].size() - 1;
	const int y_max = content.size() - 1;

    auto result = 0;

	for (auto element = path.begin() + 1; element != path.end(); ++element)
	{
		auto p = *element;
		auto old_char     = content[p.y][p.x];
		content[p.y][p.x] = '#';


		const auto start_guard = *(element-1);
		const auto start_dir = dirs[(element -1)-path.begin()];

		if (has_loop(x_max, y_max, start_guard, start_dir , content))
		{
			result++;
		}
		content[p.y][p.x] = old_char;
	}
    return result;
}

/*

TEST_CASE("Day6")
{
	std::vector<std::string> content = read("../days/6/input");



	std::println("result: {} ", result);

	REQUIRE(result == 1911);
}
*/
}
