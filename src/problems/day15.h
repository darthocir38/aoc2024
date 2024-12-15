#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day15 final : public DaySolver {
    public:
        Day15();
        ~Day15() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
