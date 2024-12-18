#include "day2.h"
#include <ranges>
#include <algorithm>
#include "../helper/parser.h"
#include "../helper/converter.h"

namespace adventofcode
{
Day2::Day2() : DaySolver(2) {
    // Data for tests
    test_data = R"(7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9)";
    test_results = { 2, 4 };
}

bool is_rpt_sorted(auto const& rpt)
{
	return (std::ranges::is_sorted(rpt, std::greater<>()) or
	        std::ranges::is_sorted(rpt, std::less<>()));
};

bool is_distance_ok(auto const& rpt)
{
	auto const elems = rpt | std::views::slide(2);
	return std::ranges::all_of(
		elems,
		[](auto const& p) {
			auto diff = abs(p[0] - p[1]);
			return diff > 0 and diff <= 3;
		});
};

bool is_rpt_save(auto const& rpt)
{
	return is_rpt_sorted(rpt) and is_distance_ok(rpt);
};

ResultType Day2::solvePart1() {
    const auto content = split(input_data, '\n');
    auto reports = convert<int>(split(content, ' '));

    auto ret = std::ranges::remove_if(reports, [](auto const& r) { return is_rpt_save(r); });
    auto save_rpts = ret.size();

    return save_rpts;
}

ResultType Day2::solvePart2() {
	const auto content    =split(input_data, '\n');
	auto reports = convert<int>(split(content, ' '));

    auto ret = std::ranges::remove_if(
		reports,
		[](auto const& r) { return is_rpt_save(r); });
	auto save_rpts = ret.size();
	reports.erase(ret.begin(), ret.end());

    for (auto const& rpt : reports)
	{
		for (auto i = 0; i < rpt.size(); i++)
		{
			auto tst = rpt;
			tst.erase(tst.begin() + i);
			if (is_rpt_save(tst))
			{
				save_rpts++;
				break;
			}
		}
	}
    return save_rpts;
}

}
