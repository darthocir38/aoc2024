//
// Created by rico on 12/1/24.
//

#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include <ranges>
#include <print>
#include <sstream>

inline std::vector<std::string> split (auto const& s, const char delim) {
    std::vector<std::string> result;
    std::stringstream ss (std::string{s});
    std::string item;

    while (getline (ss, item, delim)) {
		if (item.empty()) continue;
    	result.push_back (item);
    }
    return result;
}



inline std::vector<std::vector<std::string>> split (std::vector<auto> const& data, const char delim) {
    std::vector<std::vector<std::string>> result;
    result.reserve(data.size());
    for (auto const &line: data) {
        result.push_back(split(line, delim));
    }

    return result;
}



#endif //PARSER_H
