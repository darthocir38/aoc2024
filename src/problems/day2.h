#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day2 final : public DaySolver {
    public:
        Day2();
        ~Day2() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
