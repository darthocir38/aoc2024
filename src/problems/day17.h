#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day17 final : public DaySolver {
    public:
        Day17();
        ~Day17() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
