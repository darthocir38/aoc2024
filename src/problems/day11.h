#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day11 final : public DaySolver {
    public:
        Day11();
        ~Day11() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
