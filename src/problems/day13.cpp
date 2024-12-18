#include "day13.h"
#include "../helper/converter.h"
#include "../helper/parser.h"
#include "../helper/point.h"
#include "../helper/helper.h"
#include <regex>
#include <optional>


namespace adventofcode
{
Day13::Day13() : DaySolver(13) {
    // Data for tests
    test_data = R"(Button A: X+94, Y+34
Button B: X+22, Y+67
Prize: X=8400, Y=5400

Button A: X+26, Y+66
Button B: X+67, Y+21
Prize: X=12748, Y=12176

Button A: X+17, Y+86
Button B: X+84, Y+37
Prize: X=7870, Y=6450

Button A: X+69, Y+23
Button B: X+27, Y+71
Prize: X=18641, Y=10279)";
    test_results = { 480, 875318608908 };
}


struct P { int x; int y; };
struct machine{
    P a;
    P b;
    P prize;
};


std::optional<std::pair<long,long>> solve(machine m, auto const o) {
    auto const& [a,b,p] = m;

    auto off = o*a.x-o*a.y;

    auto p1 = (p.y*a.x - (p.x)*a.y+ off);
    auto p2 = (b.y*a.x-b.x*a.y);

    if (p1%p2 != 0)return std::nullopt;
    auto press_b = p1/p2;

    auto p3 = ((p.x+o)-press_b*b.x);
    if (p3%a.x != 0)return std::nullopt;

    auto press_a = p3 /a.x;

    return std::make_pair(press_a,press_b);
}


auto build_machines(auto const& data) {
    static const std::regex p1("X[+=]([0-9]*), Y[+=]([0-9]*)");

    std::vector<machine> machines;
    for (auto i = 0; i < data.size(); i = i + 3) {
        auto const& a = data[i];
        auto const& b = data[i + 1];
        auto const& p = data[i + 2];
        std::smatch match;
        std::regex_search(a, match, p1);
        P but_a(stoi(match[1]), stoi(match[2]));
        std::regex_search(b, match, p1);
        P but_b(stoi(match[1]), stoi(match[2]));
        std::regex_search(p, match, p1);
        P prize(stoi(match[1]), stoi(match[2]));
        machines.emplace_back(but_a, but_b, prize);
    }
    return machines;
}

ResultType Day13::solvePart1() {
    const auto content = split(input_data, '\n');
    auto machines = build_machines(content);

    auto result = 0;
    for (auto& m : machines) {
        if (auto res = solve(m, 0)) {
            result += 3 * (res->first) + res->second;
        }
    }
    return result;
}

ResultType Day13::solvePart2() {
	const auto content    =split(input_data, '\n');
    auto machines= build_machines(content);
    long result = 0;

    for (auto& m : machines) {
        auto res = solve(m, 10000000000000);
        if (res) {
            result += 3*(res->first) + res->second;
        }
    }
    return result;
}

}
