#include "day12.h"
#include "../helper/converter.h"
#include "../helper/parser.h"
#include "../helper/point.h"
#include "../helper/helper.h"

#include <map>

namespace adventofcode
{
Day12::Day12() : DaySolver(12) {
    // Data for tests
    test_data = R"(RRRRIICCFF
RRRRIICCCF
VVRRRCCFFF
VVRCCCJFFF
VVVVCJJCFE
VVIVCCJJEE
VVIIICJJEE
MIIIIIJJEE
MIIISIJEEE
MMMISSJEEE)";
    test_results = { 1930, 1206 };
}

static const auto neighbors = std::vector<Point>{{ 0, -1 },{ 1, 0 },{ 0, 1 },{-1, 0 }};
struct Crop
{
    char sym;
    std::vector<Point> area;
};
struct Field
{
    int x;
    int y;
    std::vector<Crop> crops;
};

void add_to (auto const& data, auto& checked, Crop& c, Point p) {
        if ((not p.in_range(data[0].size()-1, data.size()-1)) or checked[p.y][p.x]) {return;}
        auto sym = data[p.y][p.x];
        if (sym != c.sym) return;

        checked[p.y][p.x] = true;
        c.area.push_back({ p.x, p.y });
        for (auto n : neighbors) {
            add_to(data, checked,c,p+n);
        }
    };

Field buildField(auto const& data) {
    Field field;
    field.x = data[0].size();
    field.y = data.size();
    std::vector<std::vector<bool>> checked(field.y, std::vector<bool>(field.x, false));


    for (auto y = 0; y < data.size(); y++) {
        for (auto x = 0; x < data[y].size(); x++) {
            if (checked[y][x]) {continue;}
            Crop  c = {data[y][x]};
            checked[y][x] = true;
            Point p = {x,y};
            c.area.push_back({ x, y });
            for (auto n : neighbors) {
                add_to(data, checked,c,p+n);
            }
            field.crops.push_back(c);
        }
    }
    return field;
}

long Day12::solvePart1() {
	const auto content    =split(input_data, '\n');
    Field field = buildField(content);

    int result = 0;
    for (auto const& crop : field.crops) {
        auto const& area = crop.area.size();
        int perimeter = 0;
        for (auto p : crop.area) {
            for (auto n : neighbors) {
                auto pn = p+n;
                if (not contains(crop.area, pn)) {perimeter++;}
            }
        }
        result += area*perimeter;
    }
    return result;
}

long Day12::solvePart2() {
	const auto content    =split(input_data, '\n');
    Field field = buildField(content);

    int result = 0;
    for (auto const& crop : field.crops) {
        auto const& area = crop.area.size();
        int ecken = 0;
        for (auto p : crop.area) {
            std::vector<Point> hor_n;
            for (auto n : {neighbors[0],neighbors[2]})
            {
                auto pn = p+n;
                if (not contains(crop.area, pn)) {continue;}
                hor_n.push_back(n);
            }
            std::vector<Point>ver_n;
            for (auto n : {neighbors[1],neighbors[3]})
            {
                auto pn = p+n;
                if (not contains(crop.area, pn)) {continue;}
                ver_n.push_back(n);
            }
            //std::println("blub {} {}", hor_n.size(),ver_n.size());

            //  single field:
            if (hor_n.empty() and ver_n.empty()) { ecken += 4;}

            // gerades stück
            else if (hor_n.empty() and ver_n.size() == 2) {
                    ecken += 0;
            }
            else if (hor_n.size() == 2 and ver_n.empty()) {
                    ecken += 0;
            }

            //end stücke
            else if (hor_n.empty() and ver_n.size() == 1) {
                    ecken += 2;
            }
            else if (hor_n.size() == 1 and ver_n.empty()) {
                    ecken += 2;
            }

            // L piece
            else if (hor_n.size() == 1 and ver_n.size() == 1) {
                ecken += 1;
                if (not contains(crop.area, p+hor_n[0]+ver_n[0])) { ecken += 1;}
            }


            // T Pieces
            else if (hor_n.size() == 2 and ver_n.size() == 1) {
                if (not contains(crop.area, p+hor_n[0]+ver_n[0])) { ecken += 1;}
                if (not contains(crop.area, p+hor_n[1]+ver_n[0])) { ecken += 1;}

            }
            else if (hor_n.size() == 1 and ver_n.size() == 2) {
                if (not contains(crop.area, p+hor_n[0]+ver_n[0])) { ecken += 1;}
                if (not contains(crop.area, p+hor_n[0]+ver_n[1])) { ecken += 1;}
            }
            else if (hor_n.size() == 2 and ver_n.size() == 2) {
                if (not contains(crop.area, p+hor_n[0]+ver_n[0])) { ecken += 1;}
                if (not contains(crop.area, p+hor_n[0]+ver_n[1])) { ecken += 1;}
                if (not contains(crop.area, p+hor_n[1]+ver_n[0])) { ecken += 1;}
                if (not contains(crop.area, p+hor_n[1]+ver_n[1])) { ecken += 1;}

            }
            else {
                std::println ("missing?: {} {} ", hor_n.size(), ver_n.size() );
            }

        }
        auto sides = ecken;
        result += area*sides;
    }
    return result;
}

}
