#include "day18.h"
#include "../helper/converter.h"
#include "../helper/helper.h"
#include "../helper/parser.h"
#include "../helper/point.h"

#include <climits>
#include <map>

namespace adventofcode
{
Day18::Day18() : DaySolver(18) {
    // Data for tests
    test_data = R"(5,4
4,2
4,5
3,0
2,1
6,3
2,4
1,5
0,6
3,3
2,6
5,1
1,2
5,5
2,5
6,5
1,4
0,4
6,4
1,1
6,1
1,0
0,5
1,6
2,0)";
    test_results = { 22, 0 };
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
auto get_sym(Point const& p, auto const& data) { return data[p.y][p.x]; };

using Path = std::vector<Point>;
struct Step
{
    Point position;
    int score;
    Path path;
};

void print(auto const& maze) {
    for (auto const& l : maze) {
        std::println("{}", l);
    }
    std::println("");
}

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

ResultType Day18::solvePart1() {
    const auto content = split(input_data, '\n');

    std::pair<int, int> grid = content.size() < 100 ? std::make_pair(6, 6) : std::make_pair(70, 70);
    int nano_sec = content.size() < 100 ? 12 : 1024;

    Point start(0, 0);
    Point end(grid.first, grid.second);

    std::vector<std::string> maze(grid.second + 1, std::string(grid.first + 1, '.'));

    int cnt = 0;
    for (auto const& l : content) {
        auto vec = convert<int>(split(l, ','));

        if (cnt < nano_sec) {
            maze[vec[1]][vec[0]] = '#';
        }
        cnt++;
    }
    // print(maze);

    const auto path = find_path(maze, start, end);

    return (long)path.size() - 1;
}

ResultType Day18::solvePart2() {
    const auto content = split(input_data, '\n');
    std::pair<int, int> grid = content.size() < 100 ? std::make_pair(6, 6) : std::make_pair(70, 70);
    int nano_sec = content.size() < 100 ? 12 : 1024;

    Point start(0, 0);
    Point end(grid.first, grid.second);

    std::vector<std::string> maze(grid.second + 1, std::string(grid.first + 1, '.'));

    for (auto const& l : content) {
        auto vec = convert<int>(split(l, ','));
        maze[vec[1]][vec[0]] = '#';
        //print(maze);

        const auto path = find_path(maze, start, end);
        if (path.empty()) {
            std::println("Output: {}", l);
            break;
        }
    }

    return 0;
}

} // namespace adventofcode
