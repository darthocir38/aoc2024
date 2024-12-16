#include "day16.h"
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
Day16::Day16() : DaySolver(16) {
    // Data for tests
    /*
    test_data = R"(###############
#.......#....E#
#.#.###.#.###.#
#.....#.#...#.#
#.###.#####.#.#
#.#.#.......#.#
#.#.#####.###.#
#...........#.#
###.#.#####.#.#
#...#.....#.#.#
#.#.#.###.#.#.#
#.....#...#.#.#
#.###.#.#.#.#.#
#S..#.....#...#
###############)";
*/
    test_data = R"(#################
#...#...#...#..E#
#.#.#.#.#.#.#.#.#
#.#.#.#...#...#.#
#.#.#.#.###.#.#.#
#...#.#.#.....#.#
#.#.#.#.#.#####.#
#.#...#.#.#.....#
#.#.#####.#.###.#
#.#.#.......#...#
#.#.###.#####.###
#.#.#...#.....#.#
#.#.#.#####.###.#
#.#.#.........#.#
#.#.#.#########.#
#S#.............#
#################)";
    test_results = { 11048, 64 };
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

std::pair<Point, Point> build_maze(auto const& data, std::map<Point, TYPE>& maze, std::map<Point, int>& values) {
    Point start;
    Point end;
    for (auto y = 0; y < data.size(); ++y)
        for (auto x = 0; x < data[y].size(); ++x) {
            if (get_sym({ x, y }, data) == 'S') {
                maze[{ x, y }] = TYPE::PATH;
                values[{ x, y }] = INT_MAX;
                start = { x, y };
                continue;
            }
            if (get_sym({ x, y }, data) == 'E') {
                maze[{ x, y }] = TYPE::PATH;
                values[{ x, y }] = INT_MAX;
                end = { x, y };
                continue;
            }
            if (get_sym({ x, y }, data) == '#') {
                maze[{ x, y }] = TYPE::WALL;
                values[{ x, y }] = -1;
                continue;
            }
            Point p = { x, y };
            maze[p] = TYPE::PATH;
            values[{ x, y }] = INT_MAX;
        }
    return { start, end };
}

using Path = std::vector<Point>;

struct Step
{
    Point position;
    int score;
    DIR direction;
    Path path;
};

auto solve(auto const& input_data) {
    const auto content = split(input_data, '\n');
    std::map<Point, TYPE> maze;
    std::map<Point, int> values;
    auto se = build_maze(content, maze, values);

    Step starter;
    starter.position = se.first;
    starter.direction = DIR::RIGHT;
    starter.score = 0;
    starter.path = { se.first };
    std::vector<Step> steps;
    steps.push_back(starter);

    int min_score = INT_MAX;
    Path best_paths;

    do {
        std::vector<Step> new_steps;
        for (const auto& [position, score, direction, path] : steps) {
            if (position == se.second) {
                if (score < min_score) {
                    min_score = score;
                    best_paths.clear();
                    for (const auto& p : path) {
                        best_paths.push_back(p);
                    }
                } else if (score == min_score) {
                    for (const auto& p : path) {
                        if (contains(best_paths, p)) {
                            continue;
                        }
                        best_paths.push_back(p);
                    }
                }
                continue;
            }
            for (const auto& dir : { DIR::UP, DIR::RIGHT, DIR::DOWN, DIR::LEFT }) {
                const auto new_pos = position + offset_coord(dir);
                if (maze.at(new_pos) == TYPE::WALL) {
                    continue;
                }
                auto& value = values[new_pos];
                auto new_value = score + 1;
                if (direction != dir) {
                    new_value += 1000;
                }
                if (new_value - 1000 <= value) {
                    // wenn ich hier schonmal war habe ich jetzt eine andere Richtung. Daher muss mein Wert min 1000 kleiner sein
                    // weil ich einen Richtungswechsel machen muss um auf diesem Pfad weiter zu laufen
                    if (new_value < value) {
                        value = new_value;
                    }
                    Step new_step;
                    new_step.direction = dir;
                    new_step.position = new_pos;
                    new_step.score = new_value;
                    new_step.path = path;
                    new_step.path.push_back(new_pos);
                    new_steps.push_back(new_step);
                }
            }
        }
        steps = new_steps;
    } while (steps.size() > 0);

    return std::make_pair(values[se.second], best_paths.size()); // score;
}

long Day16::solvePart1() { return solve(input_data).first; }

long Day16::solvePart2() { return solve(input_data).second; }

} // namespace adventofcode
