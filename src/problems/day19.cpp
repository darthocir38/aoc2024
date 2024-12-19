#include "day19.h"

#include "../helper/converter.h"
#include "../helper/helper.h"
#include "../helper/parser.h"

#include <map>
namespace adventofcode
{
Day19::Day19() : DaySolver(19) {
    // Data for tests
    test_data = R"(r, wr, b, g, bwu, rb, gb, br

brwrr
bggr
gbbr
rrbgbr
ubwu
bwurrg
brgr
bbrgwb)";

    test_results = { 6, 16 };
}

bool is_possible(auto pattern, auto const& towels, std::map<std::string, bool> & is_possible_map) {

    for (auto const& t : towels) {
        if (not pattern.starts_with(t)) {
            continue;
        }
        if (t.size() > pattern.size()) {
            continue;
        }
        if (t.size() == pattern.size()) {
            is_possible_map[pattern] = true;
            return true;
        }
        auto remainder = pattern.substr(t.size());
        if (is_possible_map.contains(remainder)){return is_possible_map[remainder];}

        if (not is_possible(remainder, towels, is_possible_map)) {
            continue;
        }
        return true;
    }

    is_possible_map[pattern] = false;
    return false;
}

long count(const auto& pattern, auto const& towels, std::map<std::string, long> & is_possible_map) {

    long combinations = 0;

    for (auto const& t : towels) {
        if (not pattern.starts_with(t)) {
            continue;
        }
        if (t.size() > pattern.size()) {
            continue;
        }
        if (t.size() == pattern.size()) {
            combinations ++;
            continue;
        }
        auto remainder = pattern.substr(t.size());
        if (is_possible_map.contains(remainder)) {
            combinations += is_possible_map[remainder];
            continue;
        }
            combinations += count(remainder, towels, is_possible_map);

    }

    is_possible_map[pattern] = combinations;
    return combinations;
}

ResultType Day19::solvePart1() {
    const auto content = split(input_data, '\n');
    auto towels = split(content[0], ',');

    std::sort(towels.begin(), towels.end(),
              [](const std::string& first, const std::string& second) { return first.size() > second.size(); });

    int result = 0;
    std::map<std::string, bool> is_possible_map;
    for (auto i = 1; i < content.size(); i++) {
        if (is_possible(content[i], towels, is_possible_map)) {
            result++;
        }
    }
    return result;
}

ResultType Day19::solvePart2() {

    const auto content = split(input_data, '\n');
    auto towels = split(content[0], ',');

    std::sort(towels.begin(), towels.end(),
              [](const std::string& first, const std::string& second) { return first.size() > second.size(); });
    long result = 0;
    std::map<std::string, long> is_possible_map;

    for (auto i = 1; i < content.size(); i++) {
        auto comb = count(content[i], towels, is_possible_map);
        //std::println("{} : {}", content[i], comb);
        result += comb;
    }
    return result;
}

} // namespace adventofcode
