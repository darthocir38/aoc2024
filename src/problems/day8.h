#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day8 final : public DaySolver {
    public:
        Day8();
        ~Day8() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
