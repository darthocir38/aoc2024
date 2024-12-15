#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day5 final : public DaySolver {
    public:
        Day5();
        ~Day5() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
