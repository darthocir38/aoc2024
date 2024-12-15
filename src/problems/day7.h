#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day7 final : public DaySolver {
    public:
        Day7();
        ~Day7() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
