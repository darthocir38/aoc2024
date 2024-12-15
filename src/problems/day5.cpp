#include "day5.h"
#include "../helper/parser.h"
#include "../helper/converter.h"
#include <ranges>
#include <algorithm>

namespace adventofcode
{
Day5::Day5() : DaySolver(5) {
    // Data for tests
    test_data = R"(47|53
97|13
97|61
97|47
75|29
61|13
75|53
29|13
97|29
53|29
61|53
97|53
61|29
47|13
75|47
97|75
47|61
75|61
47|29
75|13
53|13

75,47,61,53,29
97,61,53,29,13
75,29,13
75,97,47,61,53
61,13,29
97,13,75,29,47)";
    test_results = { 143, 123 };
}

struct Comp {
    explicit Comp(const std::vector<std::vector<int>>& rules) {
        for (auto element : rules) {
            _rules.emplace_back(element[0], element[1]);
        }
    }
     bool operator()(int a, int b) const {
        if (std::ranges::find(_rules, std::make_pair(a,b)) != _rules.end()) {
            return true;
        }
        return false;
    }
    std::vector<std::pair<int,int>> _rules;
};

std::pair<std::vector<std::string>, std::vector<std::string>> split_input(auto data) {
    std::vector<std::string> pages;
    std::vector<std::string> rules;

    for (auto l : data) {
        if (l[2] == '|') {
            rules.push_back(l);
        }
        else
            pages.push_back(l);
    }
    return std::make_pair(pages, rules);
}


long Day5::solvePart1() {
	const auto content    =split(input_data, '\n');
    auto const [data, rules] =split_input(content);
    auto cont_int = convert<int>(split(data, ','));
    const auto rules_int = convert<int>(split(rules, '|'));

    const Comp comp(rules_int);
    int result_p1 = 0;
    for (auto &report: cont_int) {
        if(std::ranges::is_sorted(report, comp)){
            result_p1 += report[report.size() / 2];
        }
    }

    return result_p1;
}

long Day5::solvePart2() {

	const auto content    =split(input_data, '\n');
    auto const [data, rules] =split_input(content);

    auto cont_int = convert<int>(split(data, ','));
    const auto rules_int = convert<int>(split(rules, '|'));

    const Comp comp(rules_int);
    int result_p2 = 0;
    for (auto &report: cont_int) {
        if(std::ranges::is_sorted(report, comp)){
        	continue;
        }
			std::ranges::sort(report, comp);
            result_p2 += report[report.size() / 2];
    }
    return result_p2;
}

}
