#include "day20.h"
#include "../helper/converter.h"
#include "../helper/helper.h"
#include "../helper/parser.h"
#include "../helper/point.h"
#include <algorithm>
#include <climits>
#include <map>
#include <ranges>

namespace adventofcode
{
Day20::Day20() : DaySolver(20) {
    // Data for tests
    test_data = R"(###############
#...#...#.....#
#.#.#.#.#.###.#
#S#...#.#.#...#
#######.#.#.###
#######.#.#...#
#######.#.###.#
###..E#...#...#
###.#######.###
#...###...#...#
#.#####.#.###.#
#.#...#.#.#...#
#.#.#.#.#.#.###
#...#...#...###
###############)";
    test_results = { 44, 0 };
}
enum class DIR { UP, RIGHT, DOWN, LEFT };
constexpr Point offset_coord(const DIR dir) {
    switch (dir) {
    case DIR::UP:
        return { 0, -1 };
    case DIR::RIGHT:
        return { 1, 0 };
    case DIR::DOWN:
        return { 0, 1 };
    case DIR::LEFT:
        return { -1, 0 };
    }
    return { 0, 0 };
}
enum class TYPE { WALL, PATH };
auto get_sym(Point const& p, auto const& data) { return data[p.y][p.x]; };

using Path = std::vector<Point>;
struct Step
{
    Point position;
    int score;
    Path path;
};
Path find_path(auto const& maze, Point const& start, Point const& end) {

    std::vector<std::vector<int>> values(maze.size(), std::vector<int>(maze[0].size(), INT_MAX));

    Step starter;
    starter.position = start;
    starter.score = 0;
    starter.path = { start };
    std::vector<Step> steps;
    steps.push_back(starter);

    int min_score = INT_MAX;
    Path best_paths;

    do {
        std::vector<Step> new_steps;
        int i = 1;
        for (const auto& [position, score, path] : steps) {
            // std::println("{} / {}", i++, steps.size());
            if (position == end) {
                if (score < min_score) {
                    min_score = score;
                    best_paths.clear();
                    for (const auto& p : path) {
                        best_paths.push_back(p);
                    }
                }
                continue;
            }
            // maze[position.y][position.x] = 'o';
            for (const auto& dir : { DIR::UP, DIR::RIGHT, DIR::DOWN, DIR::LEFT }) {
                const auto new_pos = position + offset_coord(dir);

                if (not new_pos.in_range(maze.size() - 1, maze[0].size() - 1)) {
                    continue;
                }
                if (get_sym(new_pos, maze) == '#') {
                    continue;
                }
                auto& value = values[new_pos.y][new_pos.x];
                auto new_value = score + 1;
                if (new_value < value) {
                    if (new_value < value) {
                        value = new_value;
                    }
                    Step new_step;
                    new_step.position = new_pos;
                    new_step.score = new_value;
                    new_step.path = path;
                    new_step.path.push_back(new_pos);
                    new_steps.push_back(new_step);
                }
            }
        }
        // print(maze);
        steps = new_steps;
    } while (steps.size() > 0);

    return best_paths;
}

std::pair<Point, Point> build_maze(auto const& data) {
    Point start;
    Point end;
    for (auto y = 0; y < data.size(); ++y)
        for (auto x = 0; x < data[y].size(); ++x) {
            if (get_sym({ x, y }, data) == 'S') {
                start = { x, y };
                continue;
            }
            if (get_sym({ x, y }, data) == 'E') {
                end = { x, y };
                continue;
            }
        }
    return { start, end };
}

ResultType Day20::solvePart1() {
    const auto maze = split(input_data, '\n');
    auto [start, end] = build_maze(maze);
    const auto path = find_path(maze, start, end);

    auto is_shortcut = [&path](auto const& a, auto const& b) {
        auto const diff = a - b;
        if (diff.x == 0 and abs(diff.y) == 2) {
            // y shortcut
            if (not contains(path, Point(a.x, a.y - (diff.y / 2)))) {
                return true;
            }
        } else if (diff.y == 0 and abs(diff.x) == 2) {
            // x shortcurt
            if (not contains(path, Point(a.x - (diff.x / 2), a.y))) {
                return true;
            }
        }

        return false;
    };

    std::map<int, int> shots;
    for (auto i = 0; i < path.size() - 1; ++i) {
        for (auto j = i + 1; j < path.size(); ++j) {
            auto const& a = path[i];
            auto const& b = path[j];

            if (is_shortcut(a, b)) {
                auto save = j - i - 2;
                // std::println("found shortcut: {},{} -> {},{} : {}", a.x, a.y, b.x, b.y, save);
                if (shots.contains(save))
                    shots[save] += 1;
                else
                    shots[save] = 1;
            }
        }
    }

    auto bla = 0;
    for (auto [k, v] : shots) {
        // std::println("{} -> {}", k, v);
        if (k >= 100)
            bla += v;
    }
    return bla;
}

ResultType Day20::solvePart2() {
    const auto maze = split(input_data, '\n');
    auto [start, end] = build_maze(maze);
    const auto path = find_path(maze, start, end);

    std::map<int, int> shots;
    std::vector<std::pair<Point, Point>> existings;

    for (auto i = 0; i < path.size() - 1; ++i) {
        for (auto j = i + 1; j < path.size(); ++j) {
            auto const& a = path[i];
            auto const& b = path[j];

            auto const distance = a.distance(b);
            if (distance > 20) {
                continue;
            }
            if (not contains(path, b)) {
                continue;
            }
            auto save = j - i - distance;
            std::println("found shortcut: {},{} -> {},{} : {}", a.x, a.y, b.x, b.y, save);
            if (save == 0) {continue;}
            //if (contains(existings, {a,b})) {
            //    continue;
            //}
            //existings.push_back({a, b});
            if (shots.contains(save))
                shots[save] += 1;
            else
                shots[save] = 1;
        }
    }

    auto bla = 0;
    for (auto [k, v] : shots) {
        std::println("{} -> {}", k, v);
        if (k >= 100)
            bla += v;
    }
    return bla;
}

} // namespace adventofcode
