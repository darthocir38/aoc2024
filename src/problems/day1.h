#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day1 final : public DaySolver {
    public:
        Day1();
        ~Day1() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
