#include "day22.h"

#include "../helper/converter.h"
#include "../helper/helper.h"
#include "../helper/parser.h"
#include "../helper/point.h"

#include <functional>
#include <map>
#include <print>

namespace adventofcode
{
Day22::Day22()
    : DaySolver(22)
{
	// Data for tests
	test_data    = R"(1
10
100
2024)";
	test_results = { 37327623, 24 };
}

constexpr uint64_t next_number(uint64_t const number)
{
	auto blub1 = ((number * 64) ^ number) % 16777216;
	auto blub2 = ((blub1 / 32) ^ blub1) % 16777216;
	auto blub3 = ((blub2 * 2048) ^ blub2) % 16777216;

	return blub3;
}

constexpr std::vector<uint64_t> gen_sequence(
    uint64_t                                 buyer,
    std::function<uint64_t(uint64_t)> const& f = [](uint64_t const number) {
	    return number;
    })
{
	std::vector<uint64_t> sequence;
	sequence.reserve(2001);
	sequence.push_back(f(buyer));
	for (auto i = 0; i < 2000; i++)
	{
		buyer = next_number(buyer);
		sequence.push_back(f(buyer));
	}
	return sequence;
}

ResultType Day22::solvePart1()
{
	auto const buyers = convert<unsigned long>(split(input_data, '\n'));

	long result = 0;
	for (auto buyer : buyers)
	{
		auto sequence = gen_sequence(buyer);
		result += sequence.back();
	}

	return result;
}

constexpr inline std::tuple<int, int, int, int>
    diff_seq(std::tuple<int, int, int, int, int> const& t)
{
	auto [t0, t1, t2, t3, t4] = t;
	std::tuple seq            = { t1 - t0, t2 - t1, t3 - t2, t4 - t3 };
	return seq;
}

ResultType Day22::solvePart2()
{
	auto const buyers = convert<unsigned long>(split(input_data, '\n'));

	std::vector<std::vector<uint64_t>> sequences;
	sequences.reserve(buyers.size());
	for (auto buyer : buyers)
	{
		sequences.push_back(gen_sequence(
		    buyer, [](uint64_t const number) { return number % 10; }));
	}

	using sequence_t     = std::tuple<int, int, int, int>;
	uint64_t max_bananas = 0;

	std::map<sequence_t, uint64_t> global_cache;

	for (auto i = 0uz; i < sequences.size(); i++)
	{
		std::map<sequence_t, uint64_t> local_cache;
		for (std::tuple t : sequences[i] | std::views::adjacent<5>)
		{
			auto test_seq = diff_seq(t);

			if (local_cache.contains(test_seq)) continue;

			auto const banana     = std::get<4>(t);
			local_cache[test_seq] = banana;

			auto it = global_cache.find(test_seq);
			if (it == global_cache.end())
			{
				auto const [rit, _] =
				    global_cache.insert(std::make_pair(test_seq, banana));
				it = rit;
			}
			else
			{
				it->second += banana;
			}
			if (auto const current = it->second; current > max_bananas)
			{
				max_bananas = current;
			}
		}
	}

	return max_bananas;
}

} // namespace adventofcode
