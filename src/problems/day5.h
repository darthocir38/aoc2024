#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day5 final : public DaySolver {
    public:
        Day5();
        ~Day5() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
