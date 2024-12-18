#include "day11.h"
#include <map>
#include "../helper/parser.h"
#include "../helper/converter.h"

namespace adventofcode
{
Day11::Day11() : DaySolver(11) {
    // Data for tests
    test_data = R"(125 17)";
    test_results = { 55312, 65601038650482 };
}

using Cache = std::map<std::pair<long,int>,long>;

long blink(Cache& c, int blinks, long input) {

    // std::println("{}", blinks);
    if (blinks == 0)
        return 1;

    if (c.contains({ input, blinks })) {
        // std::printf("hit");
        return c[{ input, blinks }];
    }

    if (input == 0) {

        auto result = blink(c, blinks - 1, 1);
        c.insert({ { input, blinks }, result });
        return result;
    }
    auto str = std::format("{}", input);
    if (str.length() % 2 == 0) {
        auto str2 = std::format("{}", str.substr(0, str.length() / 2));
        auto str3 = std::format("{}", str.substr(str.length() / 2, str.length() - 1));
        auto result = blink(c, blinks - 1, convert<long>(str2)) + blink(c, blinks - 1, convert<long>(str3));
        c.insert({ { input, blinks }, result });
        return result;
    }
    auto result = blink(c, blinks - 1, (input * 2024));
    c.insert({ { input, blinks }, result });
    return result;
}

ResultType Day11::solvePart1() {
    const auto content = split(input_data, '\n');
    auto input = convert<long>(split(content[0], ' '));

    unsigned long result = 0;
    Cache c;

    for (const auto i : input) {
        result += blink(c, 25, i);
    }
    return result;
}

ResultType Day11::solvePart2() {
	const auto content    =split(input_data, '\n');
	auto input = convert<long>(split(content[0], ' '));


	unsigned long result = 0;
	Cache c;

	for(const auto i : input)
	{
			result += blink(c,75, i);
	}
    return result;
}

}

