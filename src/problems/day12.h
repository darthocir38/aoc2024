#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day12 final : public DaySolver {
    public:
        Day12();
        ~Day12() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
