#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day9 final : public DaySolver {
    public:
        Day9();
        ~Day9() override = default;

        long solvePart1() override;
        long solvePart2() override;
    };
}
