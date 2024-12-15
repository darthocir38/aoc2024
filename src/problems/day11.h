#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day11 final : public DaySolver {
    public:
        Day11();
        ~Day11() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
