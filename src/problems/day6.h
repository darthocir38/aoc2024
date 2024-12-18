#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day6 final : public DaySolver {
    public:
        Day6();
        ~Day6() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
