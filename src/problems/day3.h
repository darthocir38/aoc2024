#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day3 final : public DaySolver {
    public:
        Day3();
        ~Day3() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
