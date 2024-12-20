#pragma once

#include "ArgsParser.h"
#include "Result.h"
#include "SolverFactory.h"

#include <iostream>
#include <optional>
#include <string>
#include <string_view>

namespace adventofcode::cli::utils
{

inline std::optional<int> parseNumber(std::string_view str)
{
	std::optional<int> number;
	try
	{
		number = std::stoi(std::string(str));
	}
	catch (...)
	{
		return std::nullopt;
	}
	return number;
}

inline std::optional<int> getDay(std::string_view day_str)
{
	if (day_str.empty())
	{
		std::cerr << "The day should be provided\n";
		return std::nullopt;
	}

	auto day = parseNumber(day_str);
	if (!day || *day < 1 || *day > 25)
	{
		std::cerr << "The day should be between 1 and 25\n";
		return std::nullopt;
	}
	return day;
}

inline std::optional<Part> getPart(std::string_view part_str)
{
	if (part_str.empty()) { return std::nullopt; }

	if (part_str == "1") { return Part::Part1; }
	if (part_str == "2") { return Part::Part2; }
	std::cerr << "The part should be either 1 or 2\n";
	return std::nullopt;
}

inline std::string getTestFilter(std::vector<std::string_view> const& args)
{
	std::string filter   = "solution_check/DaySolverTest.Part";
	auto        day_str  = args_parser::get_option(args, "--day");
	auto        part_str = args_parser::get_option(args, "--part");
	auto        part     = getPart(part_str);
	auto        day      = getDay(day_str);
	if (part) { filter += *part == Part::Part1 ? "1" : "2"; }
	else { filter += "*"; }
	filter += "/";
	if (day) { filter += std::to_string(*day - 1); }
	else { filter += "*"; }
	std::cout << "Filter: " << filter << "\n";
	return filter;
}

inline void solveDay(
    int const                              day,
    std::optional<Part> const              part,
    std::string  const& content)
{
	auto const solver = createSolver(day);
	if (!solver)
	{
		std::cerr << "No solver found for day " << day << "\n";
		return;
	}
	if (not content.empty())
	{
		solver->set_data(content);
	}

	auto solve_part = [&](Part p) {
		std::cout << "- Part " << (p == Part::Part1 ? "1" : "2") << " : ";
		auto const [result, duration] = solver->timed_solve(p);
		std::cout << "  -> Result: " << streamer{ result } << " (in "
		          << duration << " µs)\n";
	};

	std::cout << "# Day " << day << "\n";
	// If a specific part was provided just run that part.
	if (part)
	{
		solve_part(*part);
		return;
	}

	// Otherwise run both parts.
	solve_part(Part::Part1);
	solve_part(Part::Part2);
}

} // namespace adventofcode::cli::utils
