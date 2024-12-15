#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day6 final : public DaySolver {
    public:
        Day6();
        ~Day6() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
