#include "day15.h"
#include "../helper/converter.h"
#include "../helper/helper.h"
#include "../helper/parser.h"
#include "../helper/point.h"

#include <ranges>
#include <map>
#include <algorithm>

namespace adventofcode
{
Day15::Day15() : DaySolver(15) {
    // Data for tests

    test_data = R"(##########
#..O..O.O#
#......O.#
#.OO..O.O#
#..O@..O.#
#O#..O...#
#O..O..O.#
#.OO.O.OO#
#....O...#
##########

<vv>^<v^>v>^vv^v>v<>v^v<v<^vv<<<^><<><>>v<vvv<>^v^>^<<<><<v<<<v^vv^v>^
vvv<<^>^v^^><<>>><>^<<><^vv^^<>vvv<>><^^v>^>vv<>v<<<<v<^v>^<^^>>>^<v<v
><>vv>v^v^<>><>>>><^^>vv>v<^^^>>v^v^<^^>v^^>v^<^v>v<>>v^v^<v>v^^<^^vv<
<<v<^>>^^^^>>>v^<>vvv^><v<<<>^^^vv^<vvv>^>v<^^^^v<>^>vvvv><>>v^<<^^^^^
^><^><>>><>^^<<^^v>>><^<v>^<vv>>v>>>^v><>^v><<<<v>>v<v<v>vvv>^<><<>^><
^>><>^v<><^vvv<^^<><v<<<<<><^v<<<><<<^^<v<^^^><^>>^<v^><<<^>>^v<v^v<v^
>^>>^v>vv>^<<^v<>><<><<v<<v><>v<^vv<<<>^^v^>^^>>><<^v>>v^v><^^>>^<>vv^
<><^^>^^^<><vvvvv^v<v<<>^v<v>v<<^><<><<><<<^^<<<^<<>><<><^^^>^^<>^>v<>
^^>vv<^v^v<vv>^<><v<^v>^^^>>>^^vvv^>vvv<>>>^<^>>>>>^<<^v>^vvv<>^<><<v>
v^^>>><<^^<>>^v^<v^vv<>v^<<>^<^v^v><^<<<><<^<v><v<>vv>>v><v^<vv<>v^<<^)";
    test_results = { 10092, 9021 };
/*
    test_data = R"(########
#..O.O.#
##@.O..#
#...O..#
#.#.O..#
#...O..#
#......#
########

<^^>>>vv<v>>v<<)";
    test_results = { 2028, 0 };
    */
}

enum class DIR { UP, RIGHT, DOWN, LEFT };
constexpr DIR to_dir(const char d) {
    if (d == '^')
        return DIR::UP;
    if (d == '>')
        return DIR::RIGHT;
    if (d == 'v')
        return DIR::DOWN;
    if (d == '<')
        return DIR::LEFT;
}

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

std::pair<std::vector<std::string>, std::string> split_input(const auto& data) {
    std::vector<std::string> map;
    std::string movements;

    for (auto l : data) {
        if (l[0] == '#') {
            map.push_back(l);
        } else
            movements += l;
    }
    return std::make_pair(map, movements);
}

auto scale(auto const& map) {
    std::vector<std::string> new_map;
    for (auto y = 0; y < map.size(); ++y) {
        std::string new_line;
        for (auto x = 0; x < map[y].size(); ++x) {
            auto sym = get_sym({ x, y }, map);
            if (sym == '@')
                new_line += "@.";
            if (sym == '#')
                new_line += "##";
            if (sym == 'O')
                new_line += "[]";
            if (sym == '.')
                new_line += "..";
        }
        new_map.push_back(new_line);
    }
    return new_map;
}

Point get_robot(auto const& data) {
    for (auto y = 0; y < data.size(); ++y)
        for (auto x = 0; x < data[y].size(); ++x)
            if (get_sym({ x, y }, data) == '@')
                return { x, y };
    return { 0, 0 };
}

void get_connected_boxes(Point p, DIR d, std::map<Point,char> &boxes, auto const& map ) {
    auto sym = get_sym(p, map);
    if (sym == '#') return;
    if (sym == '.') return;
    if (sym == 'O') {
        boxes[p] = sym;
        get_connected_boxes(p+offset_coord(d), d, boxes, map);
        return;
    }
    if ((sym == '['  or sym == ']') and (d == DIR::LEFT or d == DIR::RIGHT)) {
        boxes[p] = sym;
        get_connected_boxes(p+offset_coord(d), d, boxes, map);
        return;
    }
    if (sym == '[') {
        boxes[p] = sym;
        boxes[p+Point(1,0)] = ']';
        get_connected_boxes(p+offset_coord(d), d, boxes, map);
        get_connected_boxes(p+Point(1,0)+offset_coord(d), d, boxes, map);
        return;
    }
    if (sym == ']') {
        boxes[p] = sym;
        boxes[p+Point(-1,0)] = '[';
        get_connected_boxes(p+offset_coord(d), d, boxes, map);
        get_connected_boxes(p+Point(-1,0)+offset_coord(d), d, boxes, map);
    }
}

void print(auto const& map) {

    std::println();
    for (auto const& l : map)
        std::println("{}", l);
    std::println();
}

void move_r(auto &map, Point &r, DIR d) {

    map[r.y][r.x] = '.';
    r = r+offset_coord(d);
    map[r.y][r.x] = '@';
}


void do_solve(auto& map, auto const& movements) {
    Point r = get_robot(map);
    //std::print("robot: {},{}", r.x, r.y);

    for (auto d : movements) {
        //print(map);
        auto dir = to_dir(d);
        std::map<Point, char> boxes;
        if (get_sym(r+offset_coord(dir), map) == '#') continue;

        get_connected_boxes(r+offset_coord(dir), dir, boxes, map);
        if (boxes.empty()) {
            move_r(map, r, dir);
            //print(map);
            continue;
        }

        if (std::ranges::any_of(boxes, [&](auto const& box) {return get_sym(box.first+offset_coord(dir), map) == '#';})) continue;

        for (auto const& box : boxes) {
            map[box.first.y][box.first.x] = '.';
        }
        for (auto const& box : boxes) {
            auto new_box = box.first +offset_coord(dir);
            map[new_box.y][new_box.x] = box.second;
        }
        move_r(map, r, dir);
        //print(map);
    }
}

long Day15::solvePart1() {
    const auto content = split(input_data, '\n');
    auto [map, movements] = split_input(content);

    do_solve(map, movements);
    long result = 0;
    for (auto y = 0; y < map.size(); ++y)
        for (auto x = 0; x < map[y].size(); ++x)
            if (get_sym({ x, y }, map) == 'O')
                result += 100 * y + x;
    return result;
}

long Day15::solvePart2() {
    const auto content = split(input_data, '\n');
    auto [map, movements] = split_input(content);
    map = scale(map);

    do_solve(map, movements);
    print(map);
    long result = 0;
    for (auto y = 0; y < map.size(); ++y)
        for (auto x = 0; x < map[y].size(); ++x)
            if (get_sym({ x, y }, map) == '[')
                result += 100 * y + x;

    return result;
    return 0;
}

} // namespace adventofcode
