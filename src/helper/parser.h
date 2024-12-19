//
// Created by rico on 12/1/24.
//

#ifndef PARSER_H
#define PARSER_H
#include <print>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

inline std::string_view trim(std::string_view s)
{
    s.remove_prefix(std::min(s.find_first_not_of(" \t\r\v\n"), s.size()));
    s.remove_suffix(std::min(s.size() - s.find_last_not_of(" \t\r\v\n") - 1, s.size()));
    return s;
}

// trim from start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

inline std::vector<std::string> split (auto const& s, const char delim) {
    std::vector<std::string> result;
    std::stringstream ss (std::string{s});
    std::string item;

    while (getline (ss, item, delim)) {
        trim(item);
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
