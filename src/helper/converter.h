//
// Created by rico on 12/1/24.
//

#ifndef CONVERTER_H
#define CONVERTER_H
#include <algorithm>
#include <ranges>
#include <vector>

template <typename T> std::vector<std::vector<T>> by_column(std::vector<std::vector<T>> const& source) {
    std::vector<std::vector<T>> result;
    result.resize(source[0].size());
    for (auto row : source) {
        for (auto i = 0; i < row.size(); i++) {
            result[i].push_back(row[i]);
        }
    }
    return result;
}
template <typename T> T convert(const std::string_view s) {
    auto value = T {};

    auto [ptr, error] = std::from_chars(s.data(), s.data() + s.size(), value);

    if (error != std::errc {}) {
        // error with the conversion
    }

    return value;
}

template <typename T> inline std::vector<T> convert(std::vector<std::string> const& data) {
    return data | std::ranges::views::transform([](std::string const& x) { return convert<T>(x); }) |
           std::ranges::to<std::vector>();
}

template <typename T> inline std::vector<std::vector<T>> convert(std::vector<std::vector<std::string>> const& data) {
    return data | std::ranges::views::transform([](auto const& x) { return convert<T>(x); }) | std::ranges::to<std::vector>();
}

template <typename T> std::vector<T> split_by_char(std::string const& data) {
    return data | std::ranges::views::transform([](auto const& x) { return convert<T>(std::string { x }); }) |
           std::ranges::to<std::vector>();
}

template <typename T> std::vector<std::vector<T>> split_by_char(std::vector<std::string> const& data) {
    return data | std::ranges::views::transform([](auto const& x) { return split_by_char<T>(x); }) | std::ranges::to<std::vector>();
}

template <typename T> std::string to_str(std::vector<T> const& data, char delim = ',') {
    std::string s;
    for (auto i = 0; i < data.size(); i++) {
        if (i == data.size() - 1) {
            s += std::to_string(data[i]);
            continue;
        }
        s += std::to_string(data[i]);
        s+= delim;
    }
    return s;
}
#endif // CONVERTER_H
