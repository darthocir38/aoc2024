#include "day7.h"
#include "../helper/parser.h"
#include "../helper/converter.h"

namespace adventofcode
{
Day7::Day7() : DaySolver(7) {
    // Data for tests
    test_data = R"(190: 10 19
3267: 81 40 27
83: 17 5
156: 15 6
7290: 6 8 6 15
161011: 16 10 13
192: 17 8 14
21037: 9 7 18 13
292: 11 6 16 20)";
    test_results = { 3749, 11387 };
}

bool is_possible_p1(unsigned long  result, unsigned long curr, auto idx, auto const& inputs)
{
	if (idx == inputs.size())
	{
		return curr == result;
	}

	auto i = inputs[idx];

	if (auto next = curr + i; next <= result and is_possible_p1(result, next,idx+1, inputs )) return true;
	if (auto next = curr * i; next <= result and is_possible_p1(result, next, idx+1, inputs )) return true;

	return false;
}

bool is_possible_p2(unsigned long result, unsigned long curr, auto idx, auto const& inputs) {
    if (idx == inputs.size()) {
        return curr == result;
    }

    auto i = inputs[idx];

    if (auto next = curr + i; next <= result and is_possible_p2(result, next, idx + 1, inputs))
        return true;
    if (auto next = curr * i; next <= result and is_possible_p2(result, next, idx + 1, inputs))
        return true;

    auto combine = [](auto const& a, auto const& b) { return stoul(std::format("{}{}", a, b)); };

    if (auto next = combine(curr, i); next <= result and is_possible_p2(result, next, idx + 1, inputs))
        return true;

    return false;
}

ResultType Day7::solvePart1() {
    const auto content = split(input_data, '\n');
    auto content_split = split(content, ':');

    unsigned long sum_p1 = 0;
    int line = 0;
    for (auto const& eq : content_split) {
        line++;
        const auto result = convert<long>(eq[0]);
        auto input = convert<int>(split(eq[1], ' '));

        if (is_possible_p1(result, input[0], 1, input)) {
            sum_p1 += result;
        }
    }
    return sum_p1;
}

ResultType Day7::solvePart2() {
	const auto content    =split(input_data, '\n');
	auto content_split = split(content, ':');

	unsigned long sum_p2 = 0;
	int line = 0;
	for (auto const& eq : content_split)
	{
		line++;
		const auto result = convert<long>(eq[0]);
		auto input = convert<int>(split(eq[1], ' '));

		if (is_possible_p2(result, input[0], 1, input))
		{
			sum_p2  +=  result;
		}
	}
    return sum_p2;
}

}