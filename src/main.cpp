#include "cli/ArgsParser.h"
#include "cli/File.h"
#include "cli/Utils.h"

#include <optional>
#include <vector>

inline void printUsage()
{
	std::cout << "Usage: ./adventofcode [--day <number>] [--alldays] [--part "
	             "1|2] [--file <filename>] [--help]\n";
}

int main(int argc, char** argv)
{
	using namespace adventofcode;

	std::vector<std::string_view> const args(argv, argv + argc);

	if (cli::args_parser::has_option(args, "--help"))
	{
		printUsage();
		return 0;
	}

	if (cli::args_parser::has_option(args, "--alldays") ||
	    !cli::args_parser::has_option(args, "--day"))
	{
		for (int day = 1; day <= 25; ++day)
		{
			cli::utils::solveDay(day, std::nullopt, {});
		}
	}
	else
	{
		auto const file = cli::args_parser::has_option(args, "--file") ? cli::args_parser::get_option(args, "--file") : "";
		if (not file.empty() and not cli::can_be_opened(file.data()))
		{
				std::cout << "could not read file: " << file << "\n";
				printUsage();
				return 1;
		}
		auto const input_data = not file.empty() ? cli::read_file(file) : std::string{};

		auto day_str = cli::args_parser::get_option(args, "--day");
		if (auto day = cli::utils::getDay(day_str))
		{
			auto part_str = cli::args_parser::get_option(args, "--part");
			cli::utils::solveDay(
			    *day, cli::utils::getPart(part_str), input_data);
		}
		else
		{
			printUsage();
			return 1;
		}
	}

	return 0;
}
