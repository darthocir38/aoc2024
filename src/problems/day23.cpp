#include "day23.h"

#include "../helper/converter.h"
#include "../helper/helper.h"
#include "../helper/parser.h"
#include "../helper/point.h"

#include <map>
#include <set>

namespace adventofcode
{
Day23::Day23()
    : DaySolver(23)
{
	// Data for tests
	test_data    = R"(kh-tc
qp-kh
de-cg
ka-co
yn-aq
qp-ub
cg-tb
vc-aq
tb-ka
wh-tc
yn-cg
kh-ub
ta-co
de-co
tc-td
tb-wq
wh-td
ta-ka
td-qp
aq-cg
wq-ub
ub-vc
de-ta
wq-aq
wq-vc
wh-yn
ka-de
kh-ta
co-tc
wh-qp
tb-vc
td-yn)";
	test_results = { 7uz, "co,de,ka,ta" };
}

using Network = std::map<std::string, std::set<std::string>>;

ResultType Day23::solvePart1()
{
	auto const connections = split(input_data, '\n');

	Network network;

	for (auto const& connection : connections)
	{
		auto        computers = split(connection, '-');
		auto const& c1        = computers[0];
		auto const& c2        = computers[1];

		network[c1].insert(c2);
		network[c2].insert(c1);
	}

	std::set<std::set<std::string>> circles;
	for (auto const& [c, conn] : network)
	{
		for (auto const& c2 : conn)
		{
			auto const& c2_conn = network.at(c2);
			for (auto const& c3 : c2_conn)
			{
				auto const& c3_conn = network.at(c3);
				for (auto const& c4 : c3_conn)
				{
					if (c4 == c)
					{
						std::set<std::string> circle{ c, c2, c3 };
						if (std::ranges::any_of(
						        circle, [&](auto const& computer) {
							        return computer[0] == 't';
						        }))
						{
							circles.insert(circle);
						}
					}
				}
			}
		}
	}

	return circles.size();
}

ResultType Day23::solvePart2()
{
	auto const connections = split(input_data, '\n');

	Network network;

	for (auto const& connection : connections)
	{
		auto        computers = split(connection, '-');
		auto const& c1        = computers[0];
		auto const& c2        = computers[1];

		network[c1].insert(c2);
		network[c2].insert(c1);
	}

	std::set<std::string> max_subnet = {};
	for (auto const& [computer, connected_to] : network)
	{
		std::set<std::string> subnet = { computer };
		for (auto const& connected_computer : connected_to)
		{
			if (connected_computer == computer) { continue; }

			if (std::ranges::all_of(subnet, [&](auto const& subnet_node) {
				    return network.at(subnet_node).contains(connected_computer);
			    }))
			{
				subnet.insert(connected_computer);
			}
		}

		if (subnet.size() > max_subnet.size()) max_subnet = subnet;
	}
	return set_join(max_subnet);
}

} // namespace adventofcode
