#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day14 final : public DaySolver {
    public:
        Day14();
        ~Day14() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
