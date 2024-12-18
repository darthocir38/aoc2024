#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day3 final : public DaySolver {
    public:
        Day3();
        ~Day3() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
