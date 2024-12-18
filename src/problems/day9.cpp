#include "day9.h"
#include "../helper/parser.h"
#include "../helper/converter.h"

namespace adventofcode
{
Day9::Day9() : DaySolver(9) {
    // Data for tests
    test_data = R"(2333133121414131402)";
    test_results = { 1928, 2858 };
}

static int id_cnt = 0;
struct space
{
    int id;
    size_t size;
};

ResultType Day9::solvePart1() {
    const auto content = split(input_data, '\n');

    id_cnt = 0;
    std::vector<space> fs;
    std::vector<space> fs_new;
    bool last_was_free = true;
    for (auto const& c : content[0]) {
        fs.emplace_back(last_was_free ? id_cnt++ : -1, convert<size_t>(std::string { c }));
        last_was_free = !last_was_free;
    }
    auto fwd = 0;
    auto bwd = fs.size() - 1;

    while (fwd <= bwd) {
        auto& v_fwd = fs[fwd];
        auto& v_bwd = fs[bwd];

        if (v_fwd.id != -1) {
            fs_new.emplace_back(v_fwd);
            fwd++;
        } else {
            if (v_bwd.id == -1) {
                bwd--;
            } else {
                auto& free_space = v_fwd.size;
                auto& avail_file = v_bwd.size;

                auto file_new = space(v_bwd.id, 0);
                while (free_space > 0 and avail_file > 0) {
                    file_new.size++;
                    free_space--;
                    avail_file--;
                }
                fs_new.emplace_back(file_new);
                if (free_space == 0)
                    fwd++;
                if (avail_file == 0)
                    bwd--;
            }
        }
    }

    long result = 0;
    long idx = 0;
    for (auto const& c : fs_new) {
        for (auto i = 0u; i < c.size; i++) {
            // std::println("test: {}", idx*c.id);
            result += idx * c.id;
            idx++;
        }
    }
    return result;
}

ResultType Day9::solvePart2() {
	const auto content    =split(input_data, '\n');
    id_cnt = 0;
	std::vector<space> fs;
	std::vector<space> fs_new;
	bool last_was_free = true;
	for (auto const& c : content[0])
	{
			fs.emplace_back(last_was_free?id_cnt++:-1, convert<size_t>(std::string{c}));
			last_was_free = !last_was_free;
	}

	auto fwd = 0;

	while ( fwd < fs.size() )
	{
		auto& v_fwd = fs[fwd];
		if (v_fwd.id != -1)
		{
			fs_new.emplace_back(v_fwd);
			fwd++;
		}
		else if (v_fwd.id == -1 and v_fwd.size==0)
		{
			fwd++;
		}
		else
		{
			auto bwd = fs.size()-1;
			while (bwd > fwd)
			{
				auto &v_bwd = fs[bwd];
				if (v_bwd.id != -1 and v_bwd.size <= v_fwd.size)
				{
					fs_new.push_back(v_bwd);
					v_bwd.id = -1;
					v_fwd.size = v_fwd.size-v_bwd.size;
					break;
				}
				else
				{bwd--;}
			}
			if (bwd <= fwd)
			{
				fs_new.emplace_back(v_fwd);
				fwd++;
			}

		}
	}

	long result = 0;
	long idx = 0;
	for (auto const& c : fs_new)
	{
		for (auto i = 0u; i < c.size; i++)
		{
			if (c.id != -1)
			{
				//std::println("test: {}", idx*c.id);
				result += idx * c.id;
			}
			idx++;
		}
	}

    return result;
}

}

