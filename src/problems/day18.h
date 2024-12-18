#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day18 final : public DaySolver {
    public:
        Day18();
        ~Day18() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
