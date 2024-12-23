#include "day21.h"

#include "../helper/converter.h"
#include "../helper/helper.h"
#include "../helper/parser.h"
#include "../helper/point.h"

#include <climits>
#include <map>

namespace adventofcode
{
Day21::Day21()
    : DaySolver(21)
{
	// Data for tests
	test_data    = R"(029A
980A
179A
456A
379A)";
	test_results = { 126384, 154115708116294 };
}

std::map<char, std::vector<char>> num_conn = {
	{ 'A', { '0', '3' } },           { '0', { 'A', '2' } },
	{ '1', { '2', '4' } },           { '2', { '0', '1', '3', '5' } },
	{ '3', { 'A', '2', '6' } },      { '4', { '1', '5', '7' } },
	{ '5', { '2', '4', '6', '8' } }, { '6', { '3', '5', '9' } },
	{ '7', { '4', '8' } },           { '8', { '5', '7', '9' } },
	{ '9', { '6', '8' } },
};

std::map<char, Point> const num_map = {
	{ '7', { 0, 0 } }, { '8', { 1, 0 } }, { '9', { 2, 0 } }, { '4', { 0, 1 } },
	{ '5', { 1, 1 } }, { '6', { 2, 1 } }, { '1', { 0, 2 } }, { '2', { 1, 2 } },
	{ '3', { 2, 2 } }, { '0', { 1, 3 } }, { 'A', { 2, 3 } },
};

std::map<char, std::vector<char>> ctrl_conn = {
	{ '^', { 'A', 'v' } },      { 'A', { '^', '>' } }, { '<', { 'v' } },
	{ 'v', { '<', '^', '>' } }, { '>', { 'A', 'v' } },
};

std::map<char, Point> const ctrl_map = {
	{ '^', { 1, 0 } }, { 'A', { 2, 0 } }, { '<', { 0, 1 } },
	{ 'v', { 1, 1 } }, { '>', { 2, 1 } },
};

std::vector<std::string> dfs(
    std::string visited, char end, size_t& shortest, auto const& connections)
{
	auto const curr = visited.back();
	if (curr == end) { return { visited }; }

	std::vector<std::string> results;
	for (auto const& conn : connections.at(curr))
	{
		if (visited.find(conn) != std::string::npos) { continue; }
		auto paths = dfs(visited + conn, end, shortest, connections);

		for (auto const& path : paths)
		{
			if (path.size() < shortest)
			{
				results.clear();
				results.emplace_back(path);
				shortest = path.size();
				continue;
			}
			if (path.size() == shortest)
			{
				results.emplace_back(path);
				continue;
			}
		}
	}
	return results;
}

struct Robot
{
	explicit Robot(std::map<char, Point> m, std::map<char, std::vector<char>> c)
	    : keymap(std::move(m))
	    , connections(std::move(c)) {};
	std::map<char, Point> const       keymap;
	std::map<char, std::vector<char>> connections;

	char from_to(Point const start, Point const end)
	{
		auto const [x, y] = end - start;
		auto get_movement = [](auto const& d, std::string const& c) {
			return d < 0 ? c[0] : c[1];
		};

		return x != 0 ? get_movement(x, "<>") : get_movement(y, "^v");
	}

	std::vector<std::string> to(char const next)
	{
		auto shortest  = std::numeric_limits<size_t>::max();
		auto paths     = dfs(std::string{ last }, next, shortest, connections);
		last           = next;
		auto translate = [this](auto const& p) {
			std::stringstream ss;
			for (auto const& window : p | std::views::slide(2))
			{
				ss << from_to(keymap.at(window[0]), keymap.at(window[1]));
			}
			ss << "A";
			return ss.str();
		};

		auto result =
		    paths |
		    std::ranges::views::transform(
		        [translate](std::string const& x) { return translate(x); }) |
		    std::ranges::to<std::vector>();
		return result;
	}

	char last = 'A';
};

uint64_t find_min_length(
    std::string const&                               sequence,
    int                                              depth,
    int const                                        max_depth,
    std::map<std::pair<int, std::string>, uint64_t>& cache)
{
	if (depth == max_depth) {return sequence.size();}
	if (auto const it = cache.find({ depth, sequence }); it != cache.end())
	{
		return it->second;
	}

	uint64_t total_min_length{};

	Robot r(ctrl_map, ctrl_conn);
	for (char const c : sequence)
	{
		auto     paths      = r.to(c);
		uint64_t min_length = std::numeric_limits<uint64_t>::max();
		for (auto const& p : paths)
		{
			uint64_t length = find_min_length(p, depth + 1, max_depth, cache);
			min_length      = std::min(min_length, length);
		}
		total_min_length += min_length;
	}

	cache[{ depth, sequence }] = total_min_length;
	return total_min_length;
}

size_t find_min_length(std::string const& code, int const max_depth)
{
	Robot num(num_map, num_conn);

	std::vector<std::string> all_paths;
	all_paths.emplace_back("");

	for (char const c : code)
	{
		auto paths = num.to(c);

		std::vector<std::string> all_paths2;
		for (auto const& r : all_paths)
			for (auto const& p : paths) all_paths2.push_back(r + p);
		all_paths = all_paths2;
	}

	std::map<std::pair<int, std::string>, uint64_t> cache;

	uint64_t min_length = std::numeric_limits<uint64_t>::max();
	for (auto const& path : all_paths)
	{
		auto length = find_min_length(path, 0, max_depth, cache);
		min_length  = std::min(min_length, length);
	}

	return min_length;
}

ResultType Day21::solvePart1()
{
	auto const codes  = split(input_data, '\n');
	long       result = 0;

	for (auto const& code : codes)
	{
		auto length = find_min_length(code, 2);
		result += length * stoi(code.substr(0, length - 1));
	}
	return result;
}

ResultType Day21::solvePart2()
{
	auto const codes  = split(input_data, '\n');
	long       result = 0;

	for (auto const& code : codes)
	{
		auto length = find_min_length(code, 25);
		result += length * stoi(code.substr(0, length - 1));
	}
	return result;
}

} // namespace adventofcode
