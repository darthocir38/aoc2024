#pragma once
#include <fstream>
#include <sstream>
#include <string_view>

namespace adventofcode::cli
{

inline bool can_be_opened(std::string const& file_name)
{
	std::ifstream file(file_name);
	return file.is_open();
}

inline std::string read_file(std::string_view file_name)
{
	std::ifstream inFile;
	inFile.open(std::string(file_name)); // open the input file
	return { std::istreambuf_iterator<char>(inFile),
		     std::istreambuf_iterator<char>() };
}
} // namespace adventofcode::cli