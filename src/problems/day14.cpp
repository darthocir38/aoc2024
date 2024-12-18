#include "day14.h"
#include "../helper/converter.h"
#include "../helper/helper.h"
#include "../helper/parser.h"
#include "../helper/point.h"

#include <fstream>
#include <optional>
#include <regex>

namespace adventofcode
{
Day14::Day14() : DaySolver(14) {
    // Data for tests
    test_data = R"(p=0,4 v=3,-3
p=6,3 v=-1,-3
p=10,3 v=-1,2
p=2,0 v=2,-1
p=0,0 v=1,3
p=3,0 v=-2,-2
p=7,6 v=-1,-3
p=3,0 v=-1,-2
p=9,3 v=2,3
p=7,3 v=-1,2
p=2,4 v=2,-3
p=9,5 v=-3,-3)";
    test_results = { 12, 1 };
}

struct Robot
{
    Point location;
    Point velocity;
};

int wrap(const int x, const int max, const int adv) {
    const auto next = x + adv;
    if (next < 0) {
        return max + next;
    }
    if (next > max - 1) {
        return next - max;
    }
    return next;
}

void advance(const std::pair<int, int>& grid, Robot& robot) {
    Point p_new = { wrap(robot.location.x, grid.first, robot.velocity.x), wrap(robot.location.y, grid.second, robot.velocity.y) };
    robot.location = p_new;
}

std::vector<Robot> read_pos(auto content) {
    std::vector<Robot> robots;
    static const std::regex p1("p=([0-9]*),([0-9]**) v=(-?)([0-9]*),(-?)([0-9]*)");

    for (const auto& l : content) {
        std::smatch match;
        std::regex_search(l, match, p1);

        Point pos(stoi(match[1]), stoi(match[2]));
        Point vel(stoi(match[4]), stoi(match[6]));
        if (match[3] == '-') {
            vel.x = -vel.x;
        }
        if (match[5] == '-') {
            vel.y = -vel.y;
        }
        robots.emplace_back(pos, vel);
    }
    return robots;
}

ResultType Day14::solvePart1() {
    const auto content = split(input_data, '\n');
    const std::pair<int, int> grid = (content.size() == 12) ? std::make_pair(11, 7) : std::make_pair(101, 103);

    auto robots = read_pos(content);
    for (auto i = 0; i < 100; i++)
        for (auto& r : robots) {
            advance(grid, r);
        }

    std::array<int, 4> q = { 0, 0, 0, 0 };

    auto get_q = [&grid](const Robot& r) {
        auto const x_h = grid.first / 2;
        auto const y_h = grid.second / 2;

        if (r.location.x < x_h and r.location.y < y_h) {
            return 0;
        }
        if (r.location.x > x_h and r.location.y < y_h) {
            return 1;
        }
        if (r.location.x < x_h and r.location.y > y_h) {
            return 2;
        }
        if (r.location.x > x_h and r.location.y > y_h) {
            return 3;
        };
        return 4;
    };

    for (auto& r : robots) {
        if (auto a = get_q(r); a != 4)
            q[a]++;
    }

    return q[0] * q[1] * q[2] * q[3];
}

ResultType Day14::solvePart2() {

    const auto content = split(input_data, '\n');
    const std::pair<int, int> grid = (content.size() == 12) ? std::make_pair(11, 7) : std::make_pair(101, 103);

    auto robots = read_pos(content);

    auto do_print = [&](int sec) {
        std::vector<std::string> data { grid.second, std::string(grid.first, '.') };

        for (auto r : robots) {
            data[r.location.y][r.location.x] = '#';
        }

        auto bla = 0;
        for (auto l : data) {
            bla += std::count_if(l.begin(), l.end(), [](char c) { return c == '#'; });
        }
        if (bla == content.size()) {
            /*
            std::ofstream myfile;
            myfile.open(std::format("/tmp/aoc/{}.txt", sec));
            for (auto l : data) {
                myfile << l << "\n";
            }
            myfile.close();
            */
            return true;
        }
        return false;
    };

    for (auto i = 0; i < 10000; i++) {
        for (auto& r : robots) {
            advance(grid, r);
        }
        if(do_print(i)){return i+1;}
    }
    return 0;
}

} // namespace adventofcode
