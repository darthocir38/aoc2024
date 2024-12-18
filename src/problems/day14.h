#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day14 final : public DaySolver {
    public:
        Day14();
        ~Day14() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}
