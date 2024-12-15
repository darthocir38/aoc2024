#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day10 final : public DaySolver {
    public:
        Day10();
        ~Day10() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
