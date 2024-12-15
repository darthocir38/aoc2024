#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day2 final : public DaySolver {
    public:
        Day2();
        ~Day2() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
