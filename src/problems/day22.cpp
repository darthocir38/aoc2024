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
	test_results = { 37327623, 0 };
}

uint64_t next_number(uint64_t number)
{
	auto blub1 = ((number * 64) ^ number) % 16777216;
	auto blub2 = ((blub1 / 32) ^ blub1) % 16777216;
	auto blub3 = ((blub2 * 2048) ^ blub2) % 16777216;

	return blub3;
}

std::vector<uint64_t> gen_sequence(
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

std::tuple<int, int, int, int>
    diff_seq(auto const& vec, int i, std::tuple<int, int, int, int> const& t)
{
	auto [t0, t1, t2, t3] = t;
	std::tuple seq        = { t0 - vec[i - 1], t1 - t0, t2 - t1, t3 - t2 };
	return seq;
}

int bananas_of_sequence(auto const& data, auto const& seq_to_test)
{
	int result = 0;
	for (auto const& buyer : data)
	{
		for (int j{}; std::tuple t : buyer | std::views::adjacent<4>)
		{
			if (j == 0)
			{
				j++;
				continue;
			}
			if (diff_seq(buyer, j, t) == seq_to_test)
			{
				result += std::get<3>(t);
				break;
			}
			j++;
		}
	}
	return result;
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
	using sequence_t = std::tuple<int, int, int, int>;
	int                            max_bananas = 0;
	sequence_t max_sequence;
	std::map<sequence_t,int> chache;


	for (auto i = 0; i < sequences.size(); i++)
	{
		int j = 0;
		std::println("{}/{} {}/2000",i,sequences.size(),j);
		for (std::tuple t : sequences[i] | std::views::adjacent<4>)
		{
			if (j == 0)
			{
				j++;
				continue;
			}
			auto test_seq = diff_seq(sequences[i], j, t);
			if (chache.contains(test_seq)) continue;
			/*if (test_seq == std::tuple{ -2, 1, -1, 3 })
			{
				std::println("Hello there {}", j);
			}*/

			auto banana = bananas_of_sequence(sequences, test_seq);
			if (banana > max_bananas)
			{
				max_bananas  = banana;
				max_sequence = test_seq;
			}
			chache[test_seq] = banana;
			j++;
		}
	}

	std::print(
	    "Max bananas ={} {},{},{},{} ",
	    max_bananas,
	    std::get<0>(max_sequence),
	    std::get<1>(max_sequence),
	    std::get<2>(max_sequence),
	    std::get<3>(max_sequence));

	long result = 0;
	return result;
}

} // namespace adventofcode
