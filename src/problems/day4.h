#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day4 final : public DaySolver {
    public:
        Day4();
        ~Day4() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
